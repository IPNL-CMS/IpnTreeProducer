#include "../interface/MCAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;


MCAnalyzer::MCAnalyzer(const edm::ParameterSet& config, const edm::ParameterSet& producersNames) : verbosity_(0)
{
   doPhotonMC_ = config.getUntrackedParameter<bool>("doPhotonMC", false);
   photonMC_etaMax_ = config.getParameter<double>("photonMC_etaMax");
   photonMC_ptMin_ = config.getParameter<double>("photonMC_ptMin");
   
   doElectronMC_ = config.getUntrackedParameter<bool>("doElectronMC", false);
   electronMC_etaMax_ = config.getParameter<double>("electronMC_etaMax");
   electronMC_ptMin_ = config.getParameter<double>("electronMC_ptMin");
   
   doMuonMC_ = config.getUntrackedParameter<bool>("doMuonMC", false);
   muonMC_etaMax_ = config.getParameter<double>("muonMC_etaMax");
   muonMC_ptMin_ = config.getParameter<double>("muonMC_ptMin");
   
   doOtherStablePartsMC_ = config.getUntrackedParameter<bool>("doOtherStablePartsMC", false);
   otherStablePartMC_etaMax_ = config.getParameter<double>("otherStablePartMC_etaMax");
   otherStablePartMC_ptMin_ = config.getParameter<double>("otherStablePartMC_ptMin");
   
   doJetMC_ = config.getUntrackedParameter<bool>("doJetMC", false);
   jetMC_etaMax_ = config.getParameter<double>("jetMC_etaMax");
   jetMC_ptMin_ = config.getParameter<double>("jetMC_ptMin");
   
   doMETMC_ = config.getUntrackedParameter<bool>("doMETMC", false);
   
   doUnstablePartsMC_ = config.getUntrackedParameter<bool>("doUnstablePartsMC", false);
   
   signalGenerator_ = config.getUntrackedParameter<string>("signalGenerator","noname");
   genParticlesProducer_ = producersNames.getParameter<edm::InputTag>("genParticlesProducer");
   genJetsProducer_ = producersNames.getParameter<edm::InputTag>("genJetsProducer");
   genMETsProducer_ = producersNames.getParameter<edm::InputTag>("genMETsProducer");
   
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}



MCAnalyzer::~MCAnalyzer()
{
}



void MCAnalyzer::drawMCTree(const edm::Event& iEvent, const edm::EventSetup& iSetup, const edm::ParameterSet& config, const edm::ParameterSet& producersNames)
{
   cout << endl << " ----- ParticleTreeDrawer -----" << endl;
   ParticleTreeDrawer* ptd = new ParticleTreeDrawer(config, producersNames);
   ptd->analyze( iEvent, iSetup );
   delete ptd;
}



bool MCAnalyzer::pdfInfo(const edm::Event& iEvent, TRootEvent* rootEvent)
{
   edm::Handle<GenEventInfoProduct> genEvent;
   try
   {
      iEvent.getByLabel("generator", genEvent);
      if(! genEvent.isValid())
      {
         if(verbosity_>1) cout <<  "   ===> No Valid GenEventInfoProduct, skip PDF Infos" << endl;
         return false;
      }
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  MCAnalyzer::pdfInfo => No GenEventInfoProduct #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No GenEventInfoProduct, skip PDF Infos" << endl;
      return false;
   }
   
   rootEvent->setProcessID( genEvent->signalProcessID() );
   if ( genEvent->binningValues().size()>0 ) rootEvent->setPtHat( genEvent->binningValues()[0] );
   if ( genEvent->weights().size()>0 ) rootEvent->setWeight( genEvent->weight() );
   rootEvent->setEventScale( genEvent->qScale() );
   
   if ( genEvent->hasPDF() )
   {
      if (verbosity_>1)
      {
         cout << "   First incoming parton:  flavour=" << genEvent->pdf()->id.first << " x1 = " << genEvent->pdf()->x.first << " xPDF1 = " << genEvent->pdf()->xPDF.first << endl;
         cout << "   Second incoming parton:  flavour=" << genEvent->pdf()->id.second << " x2 = " << genEvent->pdf()->x.second << " xPDF2 = " << genEvent->pdf()->xPDF.second << endl;
         cout << "   PDF Scale = " << genEvent->pdf()->scalePDF << endl;
      }
      rootEvent->setIdParton1(genEvent->pdf()->id.first);
      rootEvent->setXParton1(genEvent->pdf()->x.first);
      rootEvent->setXPDF1(genEvent->pdf()->xPDF.first);
      rootEvent->setIdParton2(genEvent->pdf()->id.second);
      rootEvent->setXParton2(genEvent->pdf()->x.second);
      rootEvent->setXPDF2(genEvent->pdf()->xPDF.second);
      rootEvent->setPdfScale(genEvent->pdf()->scalePDF);
   }
   
   return true;
}



bool MCAnalyzer::processMCParticle(const edm::Event& iEvent, TClonesArray* rootMCParticles)
{
   // Fill TCloneArrays with preselected MC Electrons, Muons and Photons, and with the primary decaying particles
   if(verbosity_>1) cout << endl << "   Process MC Particles..." << endl;
   
   int iPhoton=0; int iElectron=0; int iMuon=0; int iOtherStableParticle=0; int iUnstableParticle=0;
   int iPartSel=0; int iPhotonSel=0; int iElectronSel=0; int iMuonSel=0; int iOtherStableParticleSel=0;
   
   edm::Handle <reco::GenParticleCollection> genParticles;
   try
   {
      iEvent.getByLabel( genParticlesProducer_, genParticles );
      int nGenParticles = genParticles->size();
      if(verbosity_>1) std::cout << endl << "   Number of genParticles = " << nGenParticles << "   Label: " << genParticlesProducer_.label() << "   Instance: " << genParticlesProducer_.instance() << std::endl;
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  MCAnalyzer::processMCParticle => No genParticles #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No genParticles, skip MC Particles processing" << endl;
      return false;
   }
   
   for(unsigned int j=0; j<genParticles->size(); ++j )
   {
      const reco::GenParticle & p = (*genParticles)[ j ];
      //find the mother ID
      Int_t motherID = 0; Int_t grannyID = 0; Int_t oldgrannyId = 0;
      if (p.numberOfMothers() > 0 )
      {
         //sanity check
         const Candidate * mom = p.mother();
         motherID = mom->pdgId();
         if (mom->numberOfMothers() > 0)
         {
            const Candidate * granny = mom->mother();
            grannyID = granny->pdgId();
            if (granny->numberOfMothers() > 0) oldgrannyId = (granny->mother())->pdgId();
         }
      }
      
      if ( doPhotonMC_ && p.pdgId() == 22 && p.status()==1 )
      {
         iPhoton++;
         if ( abs(p.eta()>photonMC_etaMax_) || p.pt()<photonMC_ptMin_ ) continue;
         new( (*rootMCParticles)[iPartSel] ) TRootMCParticle( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, oldgrannyId, 0, 0, 0, 0, j );
         if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] MC Photon  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
         iPartSel++;
         iPhotonSel++;
      }
      
      if ( doElectronMC_ && abs(p.pdgId()) == 11 && p.status()==1 )
      {
         iElectron++;
         if ( abs(p.eta()>electronMC_etaMax_) || p.pt()<electronMC_ptMin_ ) continue;
         new( (*rootMCParticles)[iPartSel] ) TRootMCParticle( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, oldgrannyId, 0, 0, 0, 0, j );
         if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] MC Electron  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
         iPartSel++;
         iElectronSel++;
      }
      
      if ( doMuonMC_ && abs(p.pdgId()) == 13 && p.status()==1 )
      {
         iMuon++;
         if ( abs(p.eta()>muonMC_etaMax_) || p.pt()<muonMC_ptMin_ ) continue;
         new( (*rootMCParticles)[iPartSel] ) TRootMCParticle( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, oldgrannyId, 0, 0, 0, 0, j );
         if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] MC Muon  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
         iPartSel++;
         iMuonSel++;
      }
      
      // Optionnaly keep all other stable MC particles
      if ( doOtherStablePartsMC_ && p.status()==1 && p.pdgId() != 22 && abs(p.pdgId()) != 11 && abs(p.pdgId()) != 13 )
      {
         iOtherStableParticle++;
         if ( abs(p.eta()>otherStablePartMC_etaMax_) || p.pt()<otherStablePartMC_ptMin_ ) continue;
         new( (*rootMCParticles)[iPartSel] ) TRootMCParticle( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, oldgrannyId, 0, 0, 0, 0, j );
         if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] other MC stable particles  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
         iPartSel++;
         iOtherStableParticleSel++;
      }
      
      // add information on primary unstable particles: keep quarks, taus, Z, W, Higgs and susy particles, with status 3
      if ( doUnstablePartsMC_ && (abs(p.pdgId()) < 7 || (abs(p.pdgId()) > 10 && abs(p.pdgId()) < 17 )  ||
         (abs(p.pdgId()) > 20 && abs(p.pdgId()) < 38) || (abs(p.pdgId()) > 1000000 && abs(p.pdgId()) < 3000000) )
         && p.status()==3 )
      {
         iUnstableParticle++;
         Int_t daug0Id = 0;
         Int_t daug1Id = 0;
         Int_t daug2Id = 0;
         Int_t daug3Id = 0;
         if (p.numberOfDaughters() > 0) daug0Id = p.daughter( 0 )->pdgId();
         if (p.numberOfDaughters() > 1) daug1Id = p.daughter( 1 )->pdgId();
         if (p.numberOfDaughters() > 2) daug2Id = p.daughter( 2 )->pdgId();
         if (p.numberOfDaughters() > 3) daug3Id = p.daughter( 3 )->pdgId();
         
         new( (*rootMCParticles)[iPartSel] ) TRootMCParticle( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(),p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, oldgrannyId, daug0Id, daug1Id, daug2Id, daug3Id, j );
         if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] unstable particle  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
         iPartSel++;
         
      }
      
   }
   
   if(verbosity_>1)
   {
      cout << endl;
      cout << "   Number of MC photons = " << iPhoton << ", preselected = " << iPhotonSel << endl;
      cout << "   Number of MC electrons = " << iElectron << ", preselected = " << iElectronSel << endl;
      cout << "   Number of MC muons = " << iMuon << ", preselected = " << iMuonSel << endl;
      cout << "   Number of other MC stable particles = " << iOtherStableParticle << ", preselected = " << iOtherStableParticleSel << endl;
      cout << "   Number of primary unstable particles dumped in the ntuple = " << iUnstableParticle << endl;
   }
   
   return true;
}



bool MCAnalyzer::processGenJets(const edm::Event& iEvent, TClonesArray* rootGenJets)
{
   edm::Handle < std::vector <reco::GenJet> > genJets;
   try
   {
      iEvent.getByLabel(genJetsProducer_, genJets);
      int nGenJets = genJets->size();
      if(verbosity_>1) std::cout << endl << "   Number of genJets = " << nGenJets << "   Label: " << genJetsProducer_.label() << "   Instance: " << genJetsProducer_.instance() << std::endl;
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  MCAnalyzer::processGenJets => No genJets #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No genJets, skip MC Jets processing" << endl;
      return false;
   }
   
   int iGenJet=0; int iGenJetSel=0;
   
   for(unsigned int j=0; j<genJets->size(); ++j )
   {
      const reco::GenJet & jet = (*genJets)[ j ];
      // FIXME - Do we prefer TRootJet instead of TRootParticle ?
      TRootParticle localGenJet(
         jet.px()
         ,jet.py()
         ,jet.pz()
         ,jet.energy()
         ,jet.vx()
         ,jet.vy()
         ,jet.vz()
         ,jet.pdgId()
         ,jet.charge()
      );
      
      iGenJet++;
      if ( abs(jet.eta()>jetMC_etaMax_) || jet.pt()<jetMC_ptMin_ ) continue;
      
      new( (*rootGenJets)[j] ) TRootParticle(localGenJet);
      if(verbosity_>2) cout << "   ["<< setw(3) << j << "] GenJet - Charge=" << setw(2) << jet.charge() << " (Et,eta,phi)=("<< setw(10) << localGenJet.Et() <<","<< setw(10) << localGenJet.Eta() <<","<< setw(10) << localGenJet.Phi() << ")"
         << " vertex(x,y,z)=("<< localGenJet.vx() <<","<< localGenJet.vy() <<","<< localGenJet.vz() << ")" <<endl;
      iGenJetSel++;
   }
   
   if(verbosity_>1) cout << endl << "   Number of GenJets = " << iGenJet << ", preselected = " << iGenJetSel << endl;
   
   return true;
}



bool MCAnalyzer::processGenMETs(const edm::Event& iEvent, TClonesArray* rootGenMETs)
{
   edm::Handle < std::vector <reco::GenMET> > genMETs;
   try
   {
      iEvent.getByLabel(genMETsProducer_, genMETs);
      int nGenMETs = genMETs->size();
      if(verbosity_>1) std::cout << endl << "   Number of genMETs = " << nGenMETs << "   Label: " << genMETsProducer_.label() << "   Instance: " << genMETsProducer_.instance() << std::endl;
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  MCAnalyzer::processGenMETs => No genMETs #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No genMETs, skip MC MET processing" << endl;
      return false;
   }
   
   for(unsigned int j=0; j<genMETs->size(); ++j )
   {
      const reco::GenMET & met = (*genMETs)[ j ];
      // FIXME - Do we prefer TRootMET instead of TRootParticle ?
      TRootParticle localGenMET(
         met.px()
         ,met.py()
         ,met.pz()
         ,met.energy()
         ,met.vx()
         ,met.vy()
         ,met.vz()
         ,met.pdgId()
         ,met.charge()
      );
      
      new( (*rootGenMETs)[j] ) TRootParticle(localGenMET);
      if(verbosity_>2) cout << "   ["<< setw(3) << j << "] GenMET  (Pt,Px,Py,Phi)=(  "<< localGenMET.Pt() <<",  "<< localGenMET.Px() <<",  "<< localGenMET.Py()  <<",  "<< localGenMET.Phi() << ")" << endl;
   }
   
   return true;
}



bool MCAnalyzer::processConvertedPhoton(const edm::Event& iEvent, TClonesArray* rootMCPhotons)
{
   
   // Get MC infos (sim tracks and vertices) on converted photons
   if(verbosity_>1) std::cout  << std::endl << "   MCAnalyzer::ProcessConvertedPhoton... Looking for MC truth " << std::endl;
   
   std::vector<SimTrack> theSimTracks;
   std::vector<SimVertex> theSimVertices;
   
   try
   {
      edm::Handle<SimTrackContainer> SimTk;
      edm::Handle<SimVertexContainer> SimVtx;
      iEvent.getByLabel("g4SimHits",SimTk);
      iEvent.getByLabel("g4SimHits",SimVtx);
      theSimTracks.insert(theSimTracks.end(),SimTk->begin(),SimTk->end());
      theSimVertices.insert(theSimVertices.end(),SimVtx->begin(),SimVtx->end());
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  MCAnalyzer::processConvertedPhoton => No g4SimHits #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No g4SimHits, skip MC info on converted photons" << endl;
      return false;
   }
   
   PhotonMCTruthFinder* thePhotonMCTruthFinder_ = new PhotonMCTruthFinder();
   std::vector<PhotonMCTruth> mcPhotons=thePhotonMCTruthFinder_->find (theSimTracks,  theSimVertices);
   if(verbosity_>1) std::cout << "   MCAnalyzer::ProcessConvertedPhoton mcPhotons size " <<  mcPhotons.size() << std::endl;
   unsigned int iphot=0;
   
   for ( std::vector<PhotonMCTruth>::const_iterator mcPho=mcPhotons.begin(); mcPho !=mcPhotons.end(); mcPho++)
   {
      // keep only photon in acceptance and with visible conversion
      if (  (*mcPho).isAConversion() == 0 ) continue;
      if ( (*mcPho).fourMomentum().et() < photonMC_ptMin_ ) continue;
      if ( fabs((*mcPho).fourMomentum().pseudoRapidity()) > photonMC_etaMax_ ) continue;
      
      std::vector<ElectronMCTruth> mcElectrons = (*mcPho).electrons();
      std::vector<TLorentzVector> lorentzElectrons;
      for ( std::vector<ElectronMCTruth>::const_iterator mcEle=mcElectrons.begin(); mcEle !=mcElectrons.end(); mcEle++)
      {
         lorentzElectrons.push_back( TLorentzVector( (*mcEle).fourMomentum().px(), (*mcEle).fourMomentum().py(), (*mcEle).fourMomentum().pz(), (*mcEle).fourMomentum().e() ) );
      }

      if (verbosity_>4)
         cout << "   ConvertedMCPhoton (Et,eta,phi)=("
         << (*mcPho).fourMomentum().et() << ","
         << (*mcPho).fourMomentum().eta() << ","
         << (*mcPho).fourMomentum().phi() << ")"
         << " conv_vertex=("
         << (*mcPho).vertex().x() << ","
         << (*mcPho).vertex().y() << ","
         << (*mcPho).vertex().z() << ")"
         << " nTracks=" <<  mcElectrons.size()
         << endl;
        
      TRootMCPhoton localMCPhoton(
         TLorentzVector(
            (*mcPho).fourMomentum().px(),
                        (*mcPho).fourMomentum().py(),
                        (*mcPho).fourMomentum().pz(),
                        (*mcPho).fourMomentum().e()
         ),
         TVector3(
            (*mcPho).primaryVertex().x(),
                  (*mcPho).primaryVertex().y(),
                  (*mcPho).primaryVertex().z()
         ),
         TVector3(
            (*mcPho).vertex().x(),
                  (*mcPho).vertex().y(),
                  (*mcPho).vertex().z()
         ),
         lorentzElectrons, 22, 0
      );
      
      new( (*rootMCPhotons)[iphot] ) TRootMCPhoton(localMCPhoton);
      if(verbosity_>2) cout << "   ["<< setw(3) << iphot << "] " << localMCPhoton << endl;
                                          iphot++;
   }
   
   delete thePhotonMCTruthFinder_;
   return true;
}


bool MCAnalyzer::processMCElectron(const edm::Event& iEvent, TClonesArray* rootMCElectron)
{
	
	// Get MC infos (sim tracks and vertices) on converted photons
	if(verbosity_>1) std::cout  << std::endl << "   MCAnalyzer::ProcessMonteCarloElectron... Looking for MC truth " << std::endl;
	
	std::vector<SimTrack> theSimTracks;
	std::vector<SimVertex> theSimVertices;
        std::cout << "on va regarder la MC truth ! ! " << std::endl;	
	try
	{
		edm::Handle<SimTrackContainer> SimTk;
		edm::Handle<SimVertexContainer> SimVtx;
		iEvent.getByLabel("g4SimHits",SimTk);
		iEvent.getByLabel("g4SimHits",SimVtx);
		theSimTracks.insert(theSimTracks.end(),SimTk->begin(),SimTk->end());
		theSimVertices.insert(theSimVertices.end(),SimVtx->begin(),SimVtx->end());
	}
	catch (cms::Exception& exception)
	{
		if ( !allowMissingCollection_ )
		{
			cout << "  ##### ERROR IN  MCAnalyzer::processConvertedPhoton => No g4SimHits #####"<<endl;
			throw exception;
		}
		if(verbosity_>1) cout <<  "   ===> No g4SimHits, skip MC info on converted photons" << endl;
		return false;
	}
	ElectronMCTruthFinder* theElectronMCTruthFinder_ = new ElectronMCTruthFinder();
	std::vector<ElectronMCTruth> mcElectrons = theElectronMCTruthFinder_->find (theSimTracks,  theSimVertices);
	//if(verbosity_>1) std::cout << "   MCAnalyzer::ProcessMonteCarloElectrons mcElectrons size " <<  mcElectrons.size() << std::endl;
	unsigned int ielect=0;	
	for( std::vector<ElectronMCTruth>::const_iterator mcEl = mcElectrons.begin(); mcEl !=mcElectrons.end() ; mcEl++)
	{
				TRootMCElectron theMCElectron(
											  (*mcEl).fourMomentum().px(),
											  (*mcEl).fourMomentum().py(),
											  (*mcEl).fourMomentum().pz(),
											  (*mcEl).fourMomentum().e(),
											  (*mcEl).primaryVertex().x(),
											  (*mcEl).primaryVertex().y(),
											  (*mcEl).primaryVertex().z());
				 std:vector<TVector3> AllBremVtx;
				 std::vector<CLHEP::Hep3Vector> lesBremVtx = (*mcEl).bremVertices();
				 for (unsigned j = 0 ; j < lesBremVtx.size() ; j++){
					TVector3 OneBremVtx(lesBremVtx[j].x(),lesBremVtx[j].y(),lesBremVtx[j].z());
					AllBremVtx.push_back(OneBremVtx);
				}
				theMCElectron.setBremPosition(AllBremVtx);
				std::vector<TLorentzVector> AllBremMomentum;
				std::vector<CLHEP::HepLorentzVector> lesBremMomentum = (*mcEl).bremMomentum();
				for (unsigned j = 0 ; j < lesBremMomentum.size() ; j++){
					TLorentzVector OneBremMomentum(lesBremMomentum[j].x(),lesBremMomentum[j].y(),lesBremMomentum[j].z(),lesBremMomentum[j].t());
					AllBremMomentum.push_back(OneBremMomentum);
				}
			    theMCElectron.setBremMomentum(AllBremMomentum);
			    theMCElectron.setEnergyLoss((*mcEl).eloss());
			    cout << "ielect = " << ielect << endl;
	         	    new( (*rootMCElectron)[ielect] ) TRootMCElectron(theMCElectron);
			    ielect++;
	}
	delete theElectronMCTruthFinder_;
	return true;
}

bool MCAnalyzer::processMuMuGammaEvent(const edm::Event& iEvent, TRootSignalEvent* rootSignalEvent)
{
   // Get MC infos for Z->mu mu gamma signal
   if(verbosity_>1) std::cout  << std::endl << "   MCAnalyzer::processMuMuGammaEvent... Looking for Z->mu mu gamma MC info" << std::endl;
   edm::Handle <reco::GenParticleCollection> genParticles;
   try
   {
      iEvent.getByLabel( genParticlesProducer_, genParticles );
      int nGenParticles = genParticles->size();
      if(verbosity_>5) std::cout << endl << "   Number of genParticles = " << nGenParticles << "   Label: " << genParticlesProducer_.label() << "   Instance: " << genParticlesProducer_.instance() << std::endl;
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  MCAnalyzer::processMuMuGammaEvent => No genParticles #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No genParticles, skip MC infos for Z->mu mu gamma signal" << endl;
      return false;
   }
   
   // Find Z->mumu(gamma) + ISR photons
   if (signalGenerator_=="PYTHIA")
   {
      
      if(verbosity_>1) cout << endl << "      Looking for Z->mumu(gamma) in PYTHIA MC info" << endl;
      for(unsigned int j=0; j<genParticles->size(); ++j )
      {
         const reco::Candidate &p = (*genParticles)[ j ];
         
         if ( p.pdgId() == 23 && p.status() == 3 ) // temp Z0
         {
            for(unsigned int izdaug = 0; izdaug < p.numberOfDaughters(); ++izdaug )
            {
               const reco::Candidate* zdaug = p.daughter( izdaug );
               
               if ( zdaug->pdgId() == 13 && zdaug->status() == 3 ) // temp mu-
               {
                  for(unsigned int imudaug = 0; imudaug < zdaug->numberOfDaughters(); ++imudaug )
                  {
                     const reco::Candidate* mudaug = zdaug->daughter( imudaug );
                     if ( mudaug->pdgId() == 13 && mudaug->status() == 1 ) // final mu-
                     {
                        rootSignalEvent->addMuminus( new TRootParticle(mudaug->px(), mudaug->py(), mudaug->pz(), mudaug->energy(), mudaug->vx(), mudaug->vy(), mudaug->vz(), 13, -1.) );
                        if(verbosity_>2) cout << "      ----> final mu-   pt=" << mudaug->pt() << " eta=" << mudaug->eta() << " phi=" << mudaug->phi() << endl;
                     }
                     if ( mudaug->pdgId() == 22 && mudaug->status() == 1 ) // FSR photon from final mu-
                     {
                        rootSignalEvent->addFSR( new TRootParticle(mudaug->px(), mudaug->py(), mudaug->pz(), mudaug->energy(), mudaug->vx(), mudaug->vy(), mudaug->vz(), 22, 0.) );
                        if(verbosity_>2) cout << "      ----> FSR photon from final mu-   pt=" << mudaug->pt() << " eta=" << mudaug->eta() << " phi=" << mudaug->phi() << endl;
                     }
                  }
               }
               
               if ( zdaug->pdgId() == -13 && zdaug->status() == 3 ) // temp mu+
               {
                  for(unsigned int imudaug = 0; imudaug < zdaug->numberOfDaughters(); ++imudaug )
                  {
                     const reco::Candidate* mudaug = zdaug->daughter( imudaug );
                     if ( mudaug->pdgId() == -13 && mudaug->status() == 1 ) // final mu+
                     {
                        rootSignalEvent->addMuplus( new TRootParticle(mudaug->px(), mudaug->py(), mudaug->pz(), mudaug->energy(), mudaug->vx(), mudaug->vy(), mudaug->vz(), 13, 1.) );
                        if(verbosity_>2) cout << "      ----> final mu+   pt=" << mudaug->pt() << " eta=" << mudaug->eta() << " phi=" << mudaug->phi() << endl;
                     }
                     if ( mudaug->pdgId() == 22 && mudaug->status() == 1 ) // FSR photon from final mu+
                     {
                        rootSignalEvent->addFSR( new TRootParticle(mudaug->px(), mudaug->py(), mudaug->pz(), mudaug->energy(), mudaug->vx(), mudaug->vy(), mudaug->vz(), 22, 0.) );
                        if(verbosity_>2) cout << "      ----> FSR photon from final mu+   pt=" << mudaug->pt() << " eta=" << mudaug->eta() << " phi=" << mudaug->phi() << endl;
                     }
                  }
               }
               
               if ( zdaug->pdgId() == 23 && zdaug->status() == 2 ) // final Z0
               {
                  rootSignalEvent->addBosonZ( new TRootParticle(zdaug->px(), zdaug->py(), zdaug->pz(), zdaug->energy(), zdaug->vx(), zdaug->vy(), zdaug->vz(), 23, 0.) );
                  if(verbosity_>2) cout << "      ----> Z0   pt=" << zdaug->pt() << " eta=" << zdaug->eta() << " phi=" << zdaug->phi() << endl;
               }
               
            } // temp Z0 daughters loop
            
            
            // Find ISR photons (1)
            const reco::Candidate* zmoth = p.mother(); // only take first mother of the temp Z0 to avoid double-counting
            for(unsigned int ipartondaugh = 0; ipartondaugh < zmoth->numberOfDaughters(); ++ipartondaugh )
            {
               const reco::Candidate* partondaugh = zmoth->daughter( ipartondaugh );
               if ( abs(partondaugh->pdgId()) < 6 || partondaugh->pdgId() == 21 ) // temp Z sister (u,d,s,c,b or gluon)
               {
                  for(unsigned int idd = 0; idd < partondaugh->numberOfDaughters(); ++idd )
                  {
                     const reco::Candidate* daudaugh = partondaugh->daughter( idd );
                     if ( daudaugh->pdgId() == 22 && daudaugh->status() == 1 ) // "Z0" ISR photon
                     {
                        rootSignalEvent->addISR( new TRootParticle(daudaugh->px(), daudaugh->py(), daudaugh->pz(), daudaugh->energy(), daudaugh->vx(), daudaugh->vy(), daudaugh->vz(), 22, 0.) );
                        if(verbosity_>2) cout << "      ----> (\"Z0\") ISR photon   pt=" << daudaugh->pt() << " eta=" << daudaugh->eta() << " phi=" << daudaugh->phi() << endl;
                     }
                  }
               }
            }
            
            // Find ISR photons (2)
            for(unsigned int izmoth = 0; izmoth < p.numberOfMothers(); ++izmoth )
            {
               const reco::Candidate* zmoth = p.mother(izmoth); // temp Z0 mothers
               if ( zmoth->numberOfMothers() > 0 )
               {
                  const reco::Candidate* zgrandmoth = zmoth->mother(); // temp Z0 grand mother
                  
                  for(unsigned int ipartondaugh = 0; ipartondaugh < zgrandmoth->numberOfDaughters(); ++ipartondaugh )
                  {
                     const reco::Candidate* partondaugh = zgrandmoth->daughter( ipartondaugh );
                     if ( partondaugh->pdgId() == 22 && partondaugh->status() == 1 ) // ISR photon
                        //if ( partondaugh->pdgId() == 21 && partondaugh->status() == 2 ) // ISR gluon
                     {
                        rootSignalEvent->addISR( new TRootParticle(partondaugh->px(), partondaugh->py(), partondaugh->pz(), partondaugh->energy(), partondaugh->vx(), partondaugh->vy(), partondaugh->vz(), 22, 0.) );
                        if(verbosity_>2) cout << "      ----> ISR photon   pt=" << partondaugh->pt() << " eta=" << partondaugh->eta() << " phi=" << partondaugh->phi() << endl;
                     }
                  }
               }
            }
         } // temp Z0
      } // genParticles loop
   } // signalGenerator = "PYTHIA"

   // Find Z->mumu(gamma) + ISR photons
   if (signalGenerator_=="COMPHEP" || signalGenerator_=="ALPGEN")
   {

      if(verbosity_>1) cout << endl << "      Looking for Z->mumu(gamma) in " << signalGenerator_ << " MC info" << endl;
      for(unsigned int j=0; j<genParticles->size(); ++j )
      {
         const reco::Candidate &p = (*genParticles)[ j ];
         if ( p.pdgId() == 13 && p.status() == 3 ) // temp mu-
         {
            if ( p.numberOfMothers()>0)
            {
               const reco::Candidate* quark = p.mother();
               if ( quark->status() == 3 && abs(quark->pdgId()) > 0 && abs(quark->pdgId()) < 6 ) // mu mother is a quark
               {
                  for(unsigned int idaug = 0; idaug < quark->numberOfDaughters(); ++idaug )
                  {
                     const reco::Candidate* daug = quark->daughter( idaug );
                     if ( daug->pdgId() == 13 && daug->status() == 3 ) // temp daughter mu-
                     {
                        for(unsigned int imudaug = 0; imudaug < daug->numberOfDaughters(); ++imudaug )
                        {
                           const reco::Candidate* daudaug = daug->daughter(imudaug);
                           if ( daudaug->pdgId() == 13 && daudaug->status() == 1 ) // final daughter mu-
                           {
                              rootSignalEvent->addMuminus( new TRootParticle(daudaug->px(), daudaug->py(), daudaug->pz(), daudaug->energy(), daudaug->vx(), daudaug->vy(), daudaug->vz(), 13, -1.) );
                              if(verbosity_>2) cout << "      ----> final mu-   pt=" << daudaug->pt() << " eta=" << daudaug->eta() << " phi=" << daudaug->phi() << endl;
                           }
                           if ( daudaug->pdgId() == 22 && daudaug->status() == 1 ) // FSR photon from final mu-
                           {
                              rootSignalEvent->addFSR( new TRootParticle(daudaug->px(), daudaug->py(), daudaug->pz(), daudaug->energy(), daudaug->vx(), daudaug->vy(), daudaug->vz(), 13, -1.) );
                              if(verbosity_>2) cout << "      ----> FSR photon from final mu-  pt=" << daudaug->pt() << " eta=" << daudaug->eta() << " phi=" << daudaug->phi() << endl;
                           }
                        }
                     }

                     if ( daug->pdgId() == -13 && daug->status() == 3 ) // temp daughter mu+
                     {
                        for(unsigned int imudaug = 0; imudaug < daug->numberOfDaughters(); ++imudaug )
                        {
                           const reco::Candidate* daudaug = daug->daughter(imudaug);
                           if ( daudaug->pdgId() == -13 && daudaug->status() == 1 ) // final daughter mu-+
                           {
                              rootSignalEvent->addMuplus( new TRootParticle(daudaug->px(), daudaug->py(), daudaug->pz(), daudaug->energy(), daudaug->vx(), daudaug->vy(), daudaug->vz(), 13, -1.) );
                              if(verbosity_>2) cout << "      ----> final mu+   pt=" << daudaug->pt() << " eta=" << daudaug->eta() << " phi=" << daudaug->phi() << endl;
                           }
                           if ( daudaug->pdgId() == 22 && daudaug->status() == 1 ) // FSR photon from final mu+
                           {
                              rootSignalEvent->addFSR( new TRootParticle(daudaug->px(), daudaug->py(), daudaug->pz(), daudaug->energy(), daudaug->vx(), daudaug->vy(), daudaug->vz(), 13, -1.) );
                              if(verbosity_>2) cout << "      ----> FSR photon from final mu+  pt=" << daudaug->pt() << " eta=" << daudaug->eta() << " phi=" << daudaug->phi() << endl;
                           }
                        }
                     }

                     if ( daug->pdgId() == 22 && daug->status() == 3 ) // temp ISR photon
                     {
                        for(unsigned int iphotdaug = 0; iphotdaug < daug->numberOfDaughters(); ++iphotdaug )
                        {
                           const reco::Candidate* daudaug = daug->daughter(iphotdaug);
                           if ( daudaug->pdgId() == 22 && daudaug->status() == 1 ) // final ISR photon
                           {
                              rootSignalEvent->addISR( new TRootParticle(daudaug->px(), daudaug->py(), daudaug->pz(), daudaug->energy(), daudaug->vx(), daudaug->vy(), daudaug->vz(), 13, -1.) );
                              if(verbosity_>2) cout << "      ----> ISR photon   pt=" << daudaug->pt() << " eta=" << daudaug->eta() << " phi=" << daudaug->phi() << endl;
                           }
                        }
                     }
                  }
               }
            }
         }
      } // genParticles loop
   } // signalGenerator = "COMPHEP" || "ALPGEN"
                                       
   // Find Z->mumu(gamma) + ISR photons
   if (signalGenerator_=="POWHEG")
   {
      if(verbosity_>1) cout << endl << "\tLooking for Z->mumu(gamma) in POWHEG MC info" << endl;
      for(unsigned int j=0; j<genParticles->size(); ++j )
      {
         const reco::Candidate &p = (*genParticles)[ j ];
         // Z0
         if ( p.pdgId() == 23 && p.status() == 3 ) // temp Z0
         {
            if(verbosity_>5) cout << endl << "\t\tFound a Z0 of status 3, studying its daughters" << endl;
            for(unsigned int izdaug = 0; izdaug < p.numberOfDaughters(); ++izdaug )
            {
               const reco::Candidate* zdaug = p.daughter( izdaug );
               // ** status 3 muon
               if ( zdaug->pdgId() == 13 && zdaug->status() == 3 ) // temp mu-
               {// Found a muon
                  if(verbosity_>5) cout << "\t\t\tFound a mu- of status 3" << endl;
                  bool theFinalMuonHasBeenFound = false;
                  unsigned int nbOfLevels = 0;
                  const reco::Candidate* finalMuonCandidate = p.daughter( izdaug ); // Initialize with muon of status 3
                  while( ! theFinalMuonHasBeenFound )
                  {
                     bool thereIsAHiddenLevel = false;
                     const reco::Candidate* temp = finalMuonCandidate->daughter( 0 );
                     const reco::Candidate* temp2 = finalMuonCandidate->daughter( 0 );
                     for( unsigned int iter = 0; iter < finalMuonCandidate->numberOfDaughters(); ++iter )
                     {
                        temp = finalMuonCandidate->daughter( iter );
                        if ( temp->pdgId() == 13 && temp->status() == 1 ) // final mu-
                        {
                           if(verbosity_>5) cout << "found the final muon! There was " << nbOfLevels << " levels of status 2 muons" << endl;
                           theFinalMuonHasBeenFound = true;
                           rootSignalEvent->addMuminus( new TRootParticle(temp->px(), temp->py(), temp->pz(), temp->energy(), temp->vx(), temp->vy(), temp->vz(), 13, -1.) );
                           if(verbosity_>2) cout << "\t\t\t\tfinal mu-  pt=" << temp->pt() << " eta=" << temp->eta() << " phi=" << temp->phi() << endl;
                        }
                        if ( temp->pdgId() == 13 && temp->status() == 2 ) // temp mu
                        {
                           thereIsAHiddenLevel = true;
                           temp2 = temp; // Save the current level 2 muon to temp2, since we need to look the other daughters for FSR photons, we cannot break the loop
                        }
                        if( temp->pdgId() == 22 && temp->status() == 1 ) // FSR photon from final mu-
                        {
                           rootSignalEvent->addFSR( new TRootParticle(temp->px(), temp->py(), temp->pz(), temp->energy(), temp->vx(), temp->vy(), temp->vz(), 22, 0.) );
                           if(verbosity_>2) cout << "\t\t\tFSR photon from final mu-  pt=" << temp->pt() << " eta=" << temp->eta() << " phi=" << temp->phi() << endl;
                        }
                     }
                     if( thereIsAHiddenLevel )
                     {
                        nbOfLevels++;
                        finalMuonCandidate = temp2;
                     }
                  } // end of while( ! theFinalMuonHasBeenFound )
               }

               if ( zdaug->pdgId() == -13 && zdaug->status() == 3 ) // temp mu+
               {// Found a antimuon
                  if(verbosity_>5) cout << "\t\t\tFound a mu+ of status 3" << endl;
                  bool theFinalAntimuonHasBeenFound = false;
                  unsigned int nbOfLevels = 0;
                  const reco::Candidate* finalMuonCandidate = p.daughter( izdaug ); // Initialize with antimuon of status 3
                  while( ! theFinalAntimuonHasBeenFound )
                  {
                     bool thereIsAHiddenLevel = false;
                     const reco::Candidate* temp = finalMuonCandidate->daughter( 0 );
                     const reco::Candidate* temp2 = finalMuonCandidate->daughter( 0 );
                     for( unsigned int iter = 0; iter < finalMuonCandidate->numberOfDaughters(); ++iter )
                     {
                        temp = finalMuonCandidate->daughter( iter );
                        if ( temp->pdgId() == -13 && temp->status() == 1 ) // final mu+
                        {
                           if(verbosity_>5) cout << "found the final antimuon! There was " << nbOfLevels << " levels of status 2 antimuons" << endl;
                           theFinalAntimuonHasBeenFound = true;
                           rootSignalEvent->addMuplus( new TRootParticle(temp->px(), temp->py(), temp->pz(), temp->energy(), temp->vx(), temp->vy(), temp->vz(), -13, -1.) );
                           if(verbosity_>2) cout << "\t\t\t\tfinal mu+  pt=" << temp->pt() << " eta=" << temp->eta() << " phi=" << temp->phi() << endl;
                        }
                        if ( temp->pdgId() == -13 && temp->status() == 2 ) // temp mu
                        {
                           thereIsAHiddenLevel = true;
                           temp2 = temp; // Save the current level 2 antimuon to temp2, since we need to look the other daughters for FSR photons, we cannot break the loop
                        }
                        if( temp->pdgId() == 22 && temp->status() == 1 ) // FSR photon from final mu+
                        {
                           rootSignalEvent->addFSR( new TRootParticle(temp->px(), temp->py(), temp->pz(), temp->energy(), temp->vx(), temp->vy(), temp->vz(), 22, 0.) );
                           if(verbosity_>2) cout << "\t\t\tFSR photon from final mu+  pt=" << temp->pt() << " eta=" << temp->eta() << " phi=" << temp->phi() << endl;
                        }
                     }
                     if( thereIsAHiddenLevel )
                     {
                        nbOfLevels++;
                        finalMuonCandidate = temp2;
                     }
                  }// end of while( ! theFinalAntimuonHasBeenFound )
               }

               if ( zdaug->pdgId() == 23 && zdaug->status() == 2 ) // final Z0
               {
                  if(verbosity_>5) cout << endl << "        Found the final Z0 of status 2" << endl;
                  rootSignalEvent->addBosonZ( new TRootParticle(zdaug->px(), zdaug->py(), zdaug->pz(), zdaug->energy(), zdaug->vx(), zdaug->vy(), zdaug->vz(), 23, 0.) );
                  if(verbosity_>2) cout << "       ----> Z0  pt=" << zdaug->pt() << " eta=" << zdaug->eta() << " phi=" << zdaug->phi() << endl;
               }
            } // temp Z0 daughters loop
         } // temp Z0
      } // genParticles loop
   } // signalGenerator = "POWHEG"

   return true;
}


bool MCAnalyzer::processTopTopEvent(const edm::Event& iEvent, TClonesArray* rootMCTopTop)
{
   // Get MC infos for t tbar signal
   if(verbosity_>1) std::cout  << std::endl << "   MCAnalyzer::processTopTopEvent... Looking for ttbar signal MC info" << std::endl;
   edm::Handle<GenJetCollection> genJets;
   try
   {
      iEvent.getByLabel(genJetsProducer_, genJets);
      int nGenJets = genJets->size();
      if(verbosity_>5) std::cout << endl << "   Number of genJets = " << nGenJets << "   Label: " << genJetsProducer_.label() << "   Instance: " << genJetsProducer_.instance() << std::endl;
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  MCAnalyzer::processTopTopEvent => No genJets #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No genJets, skip MC infos for ttbar signal" << endl;
      return false;
   }

   edm::Handle<GenParticleCollection> genPart;
   try
   {
      iEvent.getByLabel(genParticlesProducer_,genPart);
      int nGenParticles = genPart->size();
      if(verbosity_>5) std::cout << endl << "   Number of genParticles = " << nGenParticles << "   Label: " << genParticlesProducer_.label() << "   Instance: " << genParticlesProducer_.instance() << std::endl;
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  MCAnalyzer::processTopTopEvent => No genParticles #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No genParticles, skip MC infos for ttbar signal" << endl;
      return false;
   }

   int iEntry = 0;
   int top = 0;
   std::vector<Float_t> topPx;
   std::vector<Float_t> topPy;
   std::vector<Float_t> topPz;
   std::vector<Float_t> topEnergy;
   std::vector<Int_t> topnW;
   std::vector<Int_t> topnE;
   std::vector<Int_t> topnMu;
   std::vector<Int_t> topnTau;
   std::vector<Int_t> topnb;
   std::vector<Int_t> topnQQ;
   std::vector<Int_t> topMother;
   std::vector<Int_t> topNDau;
   std::vector<Int_t> WNDau;
   std::vector<Int_t> topIndexInList;
   topPx.clear();
   topPy.clear();
   topPz.clear();
   topEnergy.clear();
   topnW.clear();
   topnE.clear();
   topnMu.clear();
   topnTau.clear();
   topnb.clear();
   topnQQ.clear();
   topMother.clear();
   topNDau.clear();
   topIndexInList.clear();
   WNDau.clear();
   Int_t decayType = 0;
   Int_t hiGenJetCount10 = 0;
   Int_t hiGenJetCount50 = 0;

   if (genJets.isValid())
   {
      if(genJets->size() > 1)
      {
         for(size_t Jets = 0; Jets < genJets->size(); Jets++)
         {
            const Candidate & J1 = (*genJets)[Jets];
            // Count the number of gen jets above 10 GeV
            if (J1.pt() > 10) hiGenJetCount10++;
            // Count the number of gen jets above 50 GeV
            if (J1.pt() > 50) hiGenJetCount50++;
         }
      }
   }

   for(size_t q = 0; q < genPart->size(); q++)
   {
      const Candidate & p = (*genPart)[q];
      int id = p.pdgId();
      int stat = p.status();
      if(abs(id) == 6 && (abs(stat) > 60 || stat == 3) ) // need the distinction because P8 and P6 treat the status differently
      {
         top++;
         topPx.push_back(p.px());
         topPy.push_back(p.py());
         topPz.push_back(p.pz());
         topEnergy.push_back(p.energy());
         if (p.numberOfMothers() > 0) topMother.push_back((p.mother())->pdgId());
         topNDau.push_back(p.numberOfDaughters());
         int nW = 0; int nE = 0; int nMu = 0; int nTau = 0; int nb = 0; int nQQ = 0;
         // distinguish between cases where daughters are 2 or 3 in order to patch a misbehaviour of MadGraph:
         // sometimes the W does not show up in the daughters list
         if(verbosity_>2) cout << "Top N daughters: " << p.numberOfDaughters() << endl;
         if (p.numberOfDaughters() >= 2)
         {
            const reco::Candidate* daug0 = p.daughter( 0 );
            const reco::Candidate* daug1 = p.daughter( 1 );
            if(verbosity_>2) cout << "Top daughters: " << daug0->pdgId() << " " << daug1->pdgId() << endl;
            if(abs(daug0->pdgId()) == 24)
            {
               //explicitely look for top -> W + quark and W to leptons or W to qqbar
               WNDau.push_back(daug0->numberOfDaughters());
               nW = 1;
               if(verbosity_>2) cout << "W0 daughters: " << (daug0->daughter(0))->pdgId() << " " << (daug0->daughter(1))->pdgId() << endl;
               if (abs((daug0->daughter(0))->pdgId()) == 11 || abs((daug0->daughter(1))->pdgId()) == 11) nE = 1;
               if (abs((daug0->daughter(0))->pdgId()) == 13 || abs((daug0->daughter(1))->pdgId()) == 13) nMu = 1;
               if (abs((daug0->daughter(0))->pdgId()) == 15 || abs((daug0->daughter(1))->pdgId()) == 15) nTau = 1;
               if (abs((daug0->daughter(0))->pdgId()) < 6 && abs((daug0->daughter(1))->pdgId()) < 6) nQQ = 1;
            }
            else if (abs(daug1->pdgId()) == 24)
            {
               WNDau.push_back(daug1->numberOfDaughters());
               nW = 1;
               if(verbosity_>2) cout << "W1 daughters: " << (daug1->daughter(0))->pdgId() << " " << (daug1->daughter(1))->pdgId() << endl;
               if (abs((daug1->daughter(0))->pdgId()) == 11 || abs((daug1->daughter(1))->pdgId()) == 11) nE = 1;
               if (abs((daug1->daughter(0))->pdgId()) == 13 || abs((daug1->daughter(1))->pdgId()) == 13) nMu = 1;
               if (abs((daug1->daughter(0))->pdgId()) == 15 || abs((daug1->daughter(1))->pdgId()) == 15) nTau = 1;
               if (abs((daug1->daughter(0))->pdgId()) < 6 && abs((daug1->daughter(1))->pdgId()) < 6) nQQ = 1;
            }
            if (abs(daug0->pdgId()) == 5 || abs(daug1->pdgId()) == 5) nb = 1;
         }
         topnW.push_back(nW);
         topnE.push_back(nE);
         topnMu.push_back(nMu);
         topnTau.push_back(nTau);
         topnb.push_back(nb);
         topnQQ.push_back(nQQ);
         topIndexInList.push_back(q);
         if(verbosity_>2) cout << "top chain " << nW << " " << nE << " " << nMu << " " << nTau << " " << nb << " " << nQQ << " " << endl;
      }
      else
      {
         continue;
      }
   }
   if (top == 2)
   {
      size_t top1 = 0; //first top index
      size_t top2 = top1+1; // second top index
      TLorentzVector MyTop1(topPx[top1],topPy[top1],topPz[top1],topEnergy[top1]);
      TLorentzVector MyTop2(topPx[top2],topPy[top2],topPz[top2],topEnergy[top2]);
      // classification of the event topology
      decayType = 0;
      if (topnW[top1] == 1 && topnW[top2] == 0)  { // one top decays to W, the other to something else
         if(topnb[top1] == 1) {//top1 -> W + b, top2 -> other
            decayType = 10;// top1 -> W (-> not leptonic and not qq) b , top2 -> other (no W)
            if(topnE[top1] == 1) decayType = 11; // top1 -> W (-> e nu) b , top2 -> other (no W)
            if(topnMu[top1] == 1) decayType = 12; // top1 -> W (-> mu nu) b , top2 -> other (no W)
            if(topnTau[top1] == 1) decayType = 13; // top1 -> W (-> tau nu) b , top2 -> other (no W)
            if(topnQQ[top1] == 1) decayType = 14; // top1 -> W (-> qqbar) b , top2 -> other (no W)
         } else { //top1 -> W + q (q not b), top2 -> other
            decayType = 14;// top1 -> W (-> not leptonic and not qq) q (q not b), top2 -> other (no W)
            if(topnE[top1] == 1) decayType = 15;// top1 -> W (-> e nu) q (q not b) , top2 -> other (no W)
            if(topnMu[top1] == 1) decayType = 16;// top1 -> W (-> mu nu) q (q not b) , top2 -> other (no W)
            if(topnTau[top1] == 1) decayType = 17;// top1 -> W (-> tau nu) q (q not b) , top2 -> other (no W)
            if(topnQQ[top1] == 1) decayType = 18; // top1 -> W (-> qqbar) q' (q' not b) , top2 -> other (no W)
         }
      } else if (topnW[top2] == 1 && topnW[top1] == 0) {
         if(topnb[top2] == 1) {//top1 -> W + b, top2 -> other
            decayType = 10;// top2 -> W (-> not leptonic and not qq) b, top1 -> other (no W)
            if(topnE[top2] == 1) decayType = 11;// top2 -> W (-> e nu) b , top1 -> other (no W)
            if(topnMu[top2] == 1) decayType = 12;// top2 -> W (-> mu nu) b , top1 -> other (no W)
            if(topnTau[top2] == 1) decayType = 13;// top2 -> W (-> tau nu) b , top1 -> other (no W)
            if(topnQQ[top2] == 1) decayType = 14;// top2 -> W (-> qqbar) b , top1 -> other (no W)
         } else {
            decayType = 14;// top2 -> W (-> not leptonic and not qq) q (q not b), top1 -> other (no W)
            if(topnE[top2] == 1) decayType = 15;// top2 -> W (-> e nu) q (q not b) , top1 -> other (no W)
            if(topnMu[top2] == 1) decayType = 16;// top2 -> W (-> mu nu) q (q not b) , top1 -> other (no W)
            if(topnTau[top2] == 1) decayType = 17;// top2 -> W (-> tau nu) q (q not b) , top1 -> other (no W)
            if(topnQQ[top2] == 1) decayType = 18;// top2 -> W (-> qqbar) q' (q' not b) , top1 -> other (no W)
         }
      }
      if (topnW[top1] == 1 && topnW[top2] == 1) {// both top decayed to W
         if (topnE[top1] == 1 && topnE[top2] == 1) {
            decayType = 20;// top1 -> W (-> e nu) b, top2 -> W (-> e nu) b
         } else if (topnMu[top1] == 1 && topnMu[top2] == 1) {
            decayType = 21;// top1 -> W (-> mu nu) b, top2 -> W (-> mu nu) b
         } else if (topnTau[top1] == 1 && topnTau[top2] == 1) {
            decayType = 22;// top1 -> W (-> tau nu) b, top2 -> W (-> tau nu) b
         } else if (topnQQ[top1] == 1 && topnQQ[top2] == 1) {
            decayType = 23;// top1 -> W (-> qq) b, top2 -> W (-> q'q') b
         } else if ( (topnE[top1] == 1 && topnMu[top2] == 1) || (topnE[top2] == 1 && topnMu[top1] == 1) ) {
            decayType = 24;// top1 -> W (-> e nu) b, top2 -> W (-> mu nu) b or viceversa
         } else if ( (topnE[top1] == 1 && topnTau[top2] == 1) || (topnE[top2] == 1 && topnTau[top1] == 1) ) {
            decayType = 25;// top1 -> W (-> e nu) b, top2 -> W (-> tau nu) b or viceversa
         } else if ( (topnE[top1] == 1 && topnQQ[top2] == 1) || (topnE[top2] == 1 && topnQQ[top1] == 1) ) {
            decayType = 26;// top1 -> W (-> e nu) b, top2 -> W (-> qq) b or viceversa
         } else if ( (topnTau[top1] == 1 && topnMu[top2] == 1) || (topnTau[top2] == 1 && topnMu[top1] == 1) ) {
            decayType = 27;// top1 -> W (-> tau nu) b, top2 -> W (-> mu nu) b or viceversa
         } else if ( (topnQQ[top1] == 1 && topnMu[top2] == 1) || (topnQQ[top2] == 1 && topnMu[top1] == 1) ) {
            decayType = 28;// top1 -> W (-> qq) b, top2 -> W (-> mu nu) b or viceversa
         } else if ( (topnTau[top1] == 1 && topnQQ[top2] == 1) || (topnTau[top2] == 1 && topnQQ[top1] == 1) ) {
            decayType = 29;// top1 -> W (-> tau nu) b, top2 -> W (-> qq) b or viceversa
         } else if ( (topnE[top1] == 1 && topnE[top2] == 0 && topnMu[top2] == 0 && topnTau[top2] == 0 && topnQQ[top2] == 0) || (topnE[top2] == 1 && topnE[top1] == 0 && topnMu[top1] == 0 && topnTau[top1] == 0 && topnQQ[top1] == 0) ) {
            decayType = 30;// top1 -> W (-> e nu) b, top2 -> W (-> not leptonic and not qq) b or viceversa
         } else if ( (topnMu[top1] == 1 && topnE[top2] == 0 && topnMu[top2] == 0 && topnTau[top2] == 0  && topnQQ[top2] == 0) || (topnMu[top2] == 1 && topnE[top1] == 0 && topnMu[top1] == 0 && topnTau[top1] == 0 && topnQQ[top1] == 0) ) {
            decayType = 31;// top1 -> W (-> mu nu) b, top2 -> W (-> not leptonic and not qq) b or viceversa
         } else if ( (topnTau[top1] == 1 && topnE[top2] == 0 && topnMu[top2] == 0 && topnTau[top2] == 0  && topnQQ[top2] == 0) || (topnTau[top2] == 1 && topnE[top1] == 0 && topnMu[top1] == 0 && topnTau[top1] == 0 && topnQQ[top1] == 0) ) {
            decayType = 32;// top1 -> W (-> tau nu) b, top2 -> W (-> not leptonic and not qq) b or viceversa
         } else if ( (topnQQ[top1] == 1 && topnE[top2] == 0 && topnMu[top2] == 0 && topnTau[top2] == 0  && topnQQ[top2] == 0) || (topnQQ[top2] == 1 && topnE[top1] == 0 && topnMu[top1] == 0 && topnTau[top1] == 0 && topnQQ[top1] == 0) ) {
            decayType = 33;// top1 -> W (-> qq) b, top2 -> W (-> not leptonic and not qq) b or viceversa
         } else {
            decayType = 34;// top1 -> W (-> not leptonic and not qq) b, top2 -> W (-> not leptonic and not qq) b
         }
         if ( (topnb[top1] == 1 && topnb[top2] == 0) || (topnb[top1] == 0 && topnb[top2] == 1)) {
            decayType = decayType + 20;//top1 -> W + b, top2 -> W + q (q not b) or viceversa
         } else if (topnb[top1] == 0 && topnb[top2] == 0) {
            decayType = decayType + 40; //top1 -> W + q, top2 -> W + q' (q and q' not b)
         }

      }
      if (topnW[top1] == 0 && topnW[top2] == 0) decayType = 80; // no W at all

         TLorentzVector TTbarmom(topPx[top1]+topPx[top2],topPy[top1]+topPy[top2],topPz[top1]+topPz[top2],topEnergy[top1]+topEnergy[top2]);
      new( (*rootMCTopTop)[iEntry] ) TRootTopTop(TTbarmom,topIndexInList[top1],topIndexInList[top2],topMother[top1],topMother[top2],decayType,hiGenJetCount10,hiGenJetCount50);
      iEntry++;
   }

   return true;
}
