#include "../interface/ElectronAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

ElectronAnalyzer::ElectronAnalyzer(const edm::InputTag& electronProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):LeptonAnalyzer(producersNames, myConfig, verbosity)
{
  useMC_ = myConfig.getUntrackedParameter<bool>("doElectronMC");
  electronProducer_ = electronProducer;
  barrelEcalRecHitCollection_ = producersNames.getParameter<edm::InputTag>("barrelEcalRecHitCollection");
}

ElectronAnalyzer::~ElectronAnalyzer()
{
}

bool ElectronAnalyzer::process(const edm::Event& iEvent, TRootBeamSpot* rootBeamSpot, TClonesArray* rootElectrons, EcalClusterLazyTools* lazyTools)
{
   
   unsigned int nElectrons=0;
   
   bool doElectronID = true;
   edm::Handle < std::vector <reco::GsfElectron> > recoElectrons;
   const edm::ValueMap<float> * eidRobustLooseMap = 0;
   const edm::ValueMap<float> * eidRobustTightMap = 0;
   const edm::ValueMap<float> * eidRobustHighEnergyMap = 0;
   const edm::ValueMap<float> * eidLooseMap = 0;
   const edm::ValueMap<float> * eidTightMap = 0;
   if( dataType_=="RECO" )
   {
      try
      {
         iEvent.getByLabel(electronProducer_, recoElectrons);
         nElectrons = recoElectrons->size();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  ElectronAnalyzer::process => reco::GsfElectron collection is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No reco::GsfElectron collection, skip electrons info" << endl;
         return false;
      }
      
      // Electron identification
      std::vector<edm::Handle<edm::ValueMap<float> > > electronIDmap(5);
      try
      {
         iEvent.getByLabel( "eidRobustLoose", electronIDmap[0] );
         eidRobustLooseMap = electronIDmap[0].product();
         iEvent.getByLabel( "eidRobustTight", electronIDmap[1] );
         eidRobustTightMap = electronIDmap[1].product();
         iEvent.getByLabel( "eidRobustHighEnergy", electronIDmap[2] );
         eidRobustHighEnergyMap = electronIDmap[2].product();
         iEvent.getByLabel( "eidLoose", electronIDmap[3] );
         eidLooseMap = electronIDmap[3].product();
         iEvent.getByLabel( "eidTight", electronIDmap[4] );
         eidTightMap = electronIDmap[4].product();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  ElectronAnalyzer::process => missing electronID #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> missing electronID, skip electronID info" << endl;
         doElectronID = false;
      }
      
      
   }
   
   edm::Handle < std::vector <pat::Electron> > patElectrons;
   //rechits used for swiss cross
   edm::Handle < EcalRecHitCollection > ebRecHitsHandle;
   iEvent.getByLabel(barrelEcalRecHitCollection_, ebRecHitsHandle );
   const    EcalRecHitCollection *myRecHits = ebRecHitsHandle.product();

   if( dataType_=="PAT" )
   {
      try
      {
         iEvent.getByLabel(electronProducer_, patElectrons);
         nElectrons = patElectrons->size();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  ElectronAnalyzer::process => pat::Electron collection is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No pat::Electron collection, skip electrons info" << endl;
         return false;
      }
   }
   
   if(verbosity_>1) std::cout << "   Number of electrons = " << nElectrons << "   Label: " << electronProducer_.label() << "   Instance: " << electronProducer_.instance() << std::endl;
   
   for (unsigned int j=0; j<nElectrons; j++)
   {
      const reco::GsfElectron* electron = 0;
      if( dataType_=="RECO" ) electron =  &((*recoElectrons)[j]);
      if( dataType_=="PAT" ) electron = (const reco::GsfElectron*) ( & ((*patElectrons)[j]) );
      
      TRootElectron localElectron(
      electron->px()
      ,electron->py()
      ,electron->pz()
      ,electron->energy()
      ,electron->vx()
      ,electron->vy()
      ,electron->vz()
      ,electron->pdgId()
      ,electron->charge()
      );
      
      // Variables from reco::GsfElectron
      localElectron.setClassification(electron->classification());
      localElectron.setFbrem(electron->fbrem());
      localElectron.setNumberOfBrems(electron->numberOfBrems());
      localElectron.setCaloEnergy(electron->ecalEnergy());
      localElectron.setCaloEnergyError(electron->ecalEnergyError());
      if ( electron->trackMomentumAtVtx().Mag2()>0 ) localElectron.setTrackMomentum(sqrt(electron->trackMomentumAtVtx().Mag2()));
      localElectron.setTrackMomentumError(electron->trackMomentumError());
      localElectron.setTrackMissedInnerLayers(electron->gsfTrack()->trackerExpectedHitsInner().numberOfHits());
      localElectron.setHadOverEm(electron->hadronicOverEm());
      localElectron.setDeltaEtaIn(electron->deltaEtaSuperClusterTrackAtVtx());
      localElectron.setDeltaPhiIn(electron->deltaPhiSuperClusterTrackAtVtx());
      localElectron.setEnergySuperClusterOverPin(electron->eSuperClusterOverP());
      localElectron.setDeltaEtaOut(electron->deltaEtaSeedClusterTrackAtCalo());
      localElectron.setDeltaPhiOut(electron->deltaPhiSeedClusterTrackAtCalo());
      localElectron.setEnergySeedClusterOverPout(electron->eSeedClusterOverPout());
      localElectron.setEnergyScaleCorrected(electron->isEnergyScaleCorrected());
      localElectron.setMomentumCorrected(electron->isMomentumCorrected());
      
      localElectron.setDr03TkSumPt(electron->dr03TkSumPt());
      localElectron.setDr03EcalRecHitSumEt(electron->dr03EcalRecHitSumEt());
      localElectron.setDr03HcalDepth1TowerSumEt(electron->dr03HcalDepth1TowerSumEt());
      localElectron.setDr03HcalDepth2TowerSumEt(electron->dr03HcalDepth2TowerSumEt());
      
      // Variables from reco::GsfTrack
      reco::GsfTrackRef gsfTrack = electron->gsfTrack();
      if ( gsfTrack.isNonnull() )
      {
         const reco::HitPattern& hit = gsfTrack->hitPattern();
         localElectron.setPixelLayersWithMeasurement(hit.pixelLayersWithMeasurement());
         localElectron.setStripLayersWithMeasurement(hit.stripLayersWithMeasurement());
         
         if (vertexPoint_!=0)
         {
            const reco::TrackBase::Point point( vertexPoint_->x(), vertexPoint_->y(), vertexPoint_->z() );
            localElectron.setD0( -1.*(gsfTrack->dxy(point)) );
            localElectron.setDsz( gsfTrack->dsz(point) );
         }
         else
         {
            localElectron.setD0( -1.*(gsfTrack->dxy()) );
            localElectron.setDsz( gsfTrack->dsz() );
         }

         // Get the distance to the beamline corresponding to dB for pat::electrons
         if(doBeamSpot_)
         {
             const reco::TrackBase::Point point( rootBeamSpot->x(), rootBeamSpot->y(), rootBeamSpot->z() );
             localElectron.setDB( -1.*(gsfTrack->dxy(point)) );
         }
         else
         {
             localElectron.setDB( -1.*(gsfTrack->dxy()) );
         }
                  
         // FIXME - Add Vertex error quadratically
         localElectron.setD0Error(gsfTrack->d0Error());
         localElectron.setDszError(gsfTrack->dszError());
         
         localElectron.setNormalizedChi2(gsfTrack->normalizedChi2());
         localElectron.setPtError(gsfTrack->ptError());
         localElectron.setEtaError(gsfTrack->etaError());
         localElectron.setPhiError(gsfTrack->phiError());
         
         if(doPrimaryVertex_)
         {
            // FIXME - TSOS not working with gsfTrack ???
            //const reco::TransientTrack transtrack = trackBuilder_->build( gsfTrack ) ;
            //float sig3d = ip3DSignificance(transtrack);
            //localElectron.setIP3DSignificance(sig3d);
         }
      }
      
      // Variables from reco::SuperCluster
      reco::SuperClusterRef superCluster = electron->superCluster();
      //const reco::SuperCluster* sc = superCluster.get();
      if ( superCluster.isNonnull() )
      {
         localElectron.setNbClusters(superCluster->clustersSize());
         localElectron.setSuperClusterRawEnergy(superCluster->rawEnergy());
         localElectron.setPreshowerEnergy(superCluster->preshowerEnergy());
         localElectron.setCaloPosition(
         superCluster->position().X()
         ,superCluster->position().Y()
         ,superCluster->position().Z()
         );
         
         // FIXME - associator supercluster <-> electron
         //localElectron.setSCRef(superCluster->toto());
      }
      
      
      // Cluster Shape variables
      // need reco::SuperCluster and reco::BasicCluster
      if ( superCluster.isNonnull() )
      {
         edm::Ptr<reco::CaloCluster> seedBasicCluster = superCluster->seed();
         if ( seedBasicCluster.isNonnull() ) localElectron.setClusterAlgo(seedBasicCluster->algo());
         
         // dR of the cone centered on the reco::GsfElectron and containing all its basic clusters constituents
         bool atLeastOneBC = false;
         Float_t caloConeSize = 0;
         for (reco::CaloCluster_iterator basicCluster = (*superCluster).clustersBegin(); basicCluster != (*superCluster).clustersEnd(); ++basicCluster )
         {
            atLeastOneBC = true;
            Float_t dR = localElectron.DeltaR(TLorentzVector( (*basicCluster)->position().x(), (*basicCluster)->position().y(), (*basicCluster)->position().z(), 0. ) );
            if (dR > caloConeSize) caloConeSize = dR;
         }
         if (! atLeastOneBC) caloConeSize = -999.;
         localElectron.setCaloConeSize(caloConeSize);
         
         // need reduced Ecal RecHits Collections for EcalClusterLazyTools
         if ( seedBasicCluster.isNonnull() && lazyTools != 0 )
         {
            localElectron.setE2x2(lazyTools->e2x2(*seedBasicCluster));
            localElectron.setE3x3(lazyTools->e3x3(*seedBasicCluster));
            localElectron.setE5x5(lazyTools->e5x5(*seedBasicCluster));
            localElectron.setEMax(lazyTools->eMax(*seedBasicCluster));
         }
      }
      
      
      if( dataType_=="RECO" )
      {
         // Some specific methods requiring  RECO / AOD format
         // Do association to genParticle ?
         // Isolation ?
         
         // New 2.2.X electron ID
         // Only Cut Based ID available by default (4 sequential cuts on H/E, DeltaEta, DeltaPhi, SigmaEtaEta)
         // "Robust" ids (eidRobustLoose, eidRobustTight, eidRobustHighEnergy) corresponds to fixed threshold
         // eidLoose and eidTight corresponds to the catagory based identification (E/p, fBrem)
         if (doElectronID)
         {
            edm::Ref<reco::GsfElectronCollection> electronRef(recoElectrons,j);
            if (eidRobustLooseMap) localElectron.setIDCutBasedFixedThresholdLoose( int( (*eidRobustLooseMap)[electronRef] ) );
            if (eidRobustTightMap) localElectron.setIDCutBasedFixedThresholdTight( int( (*eidRobustTightMap)[electronRef] ) );
            if (eidRobustHighEnergyMap) localElectron.setIDCutBasedFixedThresholdHighEnergy( int( (*eidRobustHighEnergyMap)[electronRef] ) );
            if (eidLooseMap) localElectron.setIDCutBasedCategorizedLoose( int( (*eidLooseMap)[electronRef] ) );
            if (eidTightMap) localElectron.setIDCutBasedCategorizedTight( int( (*eidTightMap)[electronRef] ) );
            //localElectron.setIDLikelihood();
            //localElectron.setIDNeuralNet();
         }
         // TODO
         // Add iso
         
      }
      
      if( dataType_=="PAT" )
      {
         // Some specific methods to pat::Electron
         const pat::Electron *patElectron = dynamic_cast<const pat::Electron*>(&*electron);
         std::string electronType="RecoElectron";
         if ((patElectron->pfCandidateRef()).isNonnull()) electronType="PFElectron";
         
         // Isolation
	 localElectron.setTrackIso( patElectron->trackIso() );  //corresponds to dr03TkSumPt
         localElectron.setEcalIso( patElectron->ecalIso() );  //corresponds to dr03EcalRecHitSumEt
         localElectron.setHcalIso( patElectron->hcalIso() );  //corresponds to dr03HcalTowerSumEt
	 //	 if(patElectron->ecalDrivenSeed() && fabs(patElectron->superCluster()->eta())<1.4442){
	 if(fabs(patElectron->superCluster()->eta())<1.4442){
	   const reco::CaloClusterPtr    seed =    patElectron->superCluster()->seed(); // seed cluster                                 
	   const   DetId seedId = seed->seed();
	   EcalSeverityLevelAlgo severity;
	   localElectron.setSwissCross(severity.swissCross(seedId, *myRecHits)); 
	 }




         // Electron ID (updated for 2.2.X)
         // Only Cut Based ID available by default (4 sequential cuts on H/E, DeltaEta, DeltaPhi, SigmaEtaEta)
         // "Robust" ids (eidRobustLoose, eidRobustTight, eidRobustHighEnergy) corresponds to fixed threshold
         // eidLoose and eidTight corresponds to the catagory based identification (E/p, fBrem)
         if ( patElectron->isElectronIDAvailable("eidRobustLoose") ) localElectron.setIDCutBasedFixedThresholdLoose(int(patElectron->electronID("eidRobustLoose")));
         if ( patElectron->isElectronIDAvailable("eidRobustTight") ) localElectron.setIDCutBasedFixedThresholdTight(int(patElectron->electronID("eidRobustTight")));
         if ( patElectron->isElectronIDAvailable("eidRobustHighEnergy") ) localElectron.setIDCutBasedFixedThresholdHighEnergy(int(patElectron->electronID("eidRobustHighEnergy")));
         if ( patElectron->isElectronIDAvailable("eidLoose") ) localElectron.setIDCutBasedCategorizedLoose(int(patElectron->electronID("eidLoose")));
         if ( patElectron->isElectronIDAvailable("eidTight") ) localElectron.setIDCutBasedCategorizedTight(int(patElectron->electronID("eidTight")));
         if ( patElectron->isElectronIDAvailable("likelihood") ) localElectron.setIDLikelihood(patElectron->electronID("likelihood"));
         if ( patElectron->isElectronIDAvailable("neuralnet") ) localElectron.setIDNeuralNet(patElectron->electronID("neuralnet"));
         // VBTF ele-ID 361patchX
	 if( patElectron->isElectronIDAvailable("simpleEleId70cIso")) localElectron.setIDCutBasedsimpleEleId70cIso(patElectron->electronID("simpleEleId70cIso")); 
	 if( patElectron->isElectronIDAvailable("simpleEleId95cIso")) localElectron.setIDCutBasedsimpleEleId95cIso(patElectron->electronID("simpleEleId95cIso")); 
	 if( patElectron->isElectronIDAvailable("simpleEleId70relIso")) localElectron.setIDCutBasedsimpleEleId70relIso(patElectron->electronID("simpleEleId70relIso")); 
	 if( patElectron->isElectronIDAvailable("simpleEleId95relIso")) localElectron.setIDCutBasedsimpleEleId95relIso(patElectron->electronID("simpleEleId95relIso")); 

         if (electronType=="PFElectron")
         {
            localElectron.setPFParticleIso(patElectron->particleIso());
            localElectron.setPFChargedHadronIso(patElectron->chargedHadronIso());
            localElectron.setPFNeutralHadronIso(patElectron->neutralHadronIso());
            localElectron.setPFPhotonIso(patElectron->photonIso());
         }
         
         // Matched genParticle
         if(useMC_)
         {
            // MC truth associator index
            if ((patElectron->genParticleRef()).isNonnull()) {
               localElectron.setGenParticleIndex((patElectron->genParticleRef()).index());
            } else {
               localElectron.setGenParticleIndex(-1);
            }
         }
         
      }
      
      new( (*rootElectrons)[j] ) TRootElectron(localElectron);
      if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localElectron << endl;
   }
   
   return true;
}
