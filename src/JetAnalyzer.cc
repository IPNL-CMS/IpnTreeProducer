#include "../interface/JetAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

JetAnalyzer::JetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	jetProducer_ = producersNames.getParameter<edm::InputTag>("jetProducer");
	useMC_ = myConfig.getUntrackedParameter<bool>("doJetMC");
	allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}

JetAnalyzer::~JetAnalyzer()
{
}

bool Rsortrule (std::pair <double,double> p1, std::pair <double,double> p2 )
{
	return p1.second<p2.second;
}

bool JetAnalyzer::process(const edm::Event& iEvent, TClonesArray* rootJets)
{
	
	unsigned int nJets=0;
	
	// reco::CaloJet or reco::PFJet ?
	std::string jetType = "BASIC";
	if( jetProducer_.label()=="kt4CaloJets"
		|| jetProducer_.label()=="kt6CaloJets"
		|| jetProducer_.label()=="iterativeCone5CaloJets"
		|| jetProducer_.label()=="sisCone5CaloJets"
		|| jetProducer_.label()=="sisCone7CaloJets"
		|| jetProducer_.label()=="antikt5CaloJets"
		) jetType="CALO";
	
	if( jetProducer_.label()=="kt4PFJets"
		|| jetProducer_.label()=="kt6PFJets"
		|| jetProducer_.label()=="iterativeCone5PFJets"
		|| jetProducer_.label()=="sisCone5PFJets"
		|| jetProducer_.label()=="sisCone7PFJets"
		|| jetProducer_.label()=="antikt5PFJets"
		) jetType="PF";
	
	edm::Handle < std::vector <reco::CaloJet> > recoCaloJets;
	if( dataType_=="RECO" && jetType=="CALO" )
	{
		try
		{
			iEvent.getByLabel(jetProducer_, recoCaloJets);
			nJets = recoCaloJets->size();
		}
		catch (cms::Exception& exception)
		{
			if ( !allowMissingCollection_ )
			{
				cout << "  ##### ERROR IN  JetAnalyzer::process => reco::CaloJet collection is missing #####"<<endl;
				throw exception;
			}
			if(verbosity_>1) cout <<  "   ===> No reco::CaloJet collection, skip jet info" << endl;
			return false;
		}
	}
	
	edm::Handle < std::vector <reco::PFJet> > recoPFJets;
	if( dataType_=="RECO" && jetType=="PF" )
	{
		try
		{
			iEvent.getByLabel(jetProducer_, recoPFJets);
			nJets = recoPFJets->size();
		}
		catch (cms::Exception& exception)
		{
			if ( !allowMissingCollection_ )
			{
				cout << "  ##### ERROR IN  JetAnalyzer::process => reco::PFJet collection is missing #####"<<endl;
				throw exception;
			}
			if(verbosity_>1) cout <<  "   ===> No reco::PFJet collection, skip jet info" << endl;
			return false;
		}
	}
	
	edm::Handle < std::vector <pat::Jet> > patJets;
	if( dataType_=="PAT" )
	{
		try
		{
			iEvent.getByLabel(jetProducer_, patJets);
			nJets = patJets->size();
		}
		catch (cms::Exception& exception)
		{
			if ( !allowMissingCollection_ )
			{
				cout << "  ##### ERROR IN  JetAnalyzer::process => pat::Jet collection is missing #####"<<endl;
				throw exception;
			}
			if(verbosity_>1) cout <<  "   ===> No pat::Jet collection, skip jet info" << endl;
			return false;
		}
	}
	
	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << "   Label: " << jetProducer_.label() << "   Instance: " << jetProducer_.instance() << std::endl;
	
	for (unsigned int j=0; j<nJets; j++)
	{
		const reco::Jet* jet = 0;
		if( dataType_=="RECO" && jetType=="CALO" ) jet = (const reco::Jet*) ( & ((*recoCaloJets)[j]) );
		if( dataType_=="RECO" && jetType=="PF" ) jet = (const reco::Jet*) ( & ((*recoPFJets)[j]) );
		if( dataType_=="PAT" )
		{
			jet = (const reco::Jet*) ( & ((*patJets)[j]) );
			if( (*patJets)[j].isCaloJet() ) jetType="CALO";
			if( (*patJets)[j].isPFJet() ) jetType="PF";
		}
		
		TRootJet localJet(
		jet->px()
		,jet->py()
		,jet->pz()
		,jet->energy()
		,jet->vx()
		,jet->vy()
		,jet->vz()
		,jet->pdgId()
		,jet->charge()
		);
		
		localJet.setNConstituents(jet->nConstituents());
		//std::vector< edm::Ptr <Candidate> > constituents = jet->getJetConstituents();
		localJet.setN90(jet->nCarrying(0.9));
		localJet.setN60(jet->nCarrying(0.6));
		localJet.setJetArea(jet->jetArea());
		localJet.setPileupEnergy(jet->pileup());
		localJet.setMaxDistance(jet->maxDistance());
		float totalEnergy = jet->etInAnnulus(0.,999.);
		if(totalEnergy!=0)
		{
			localJet.setDR01EnergyFraction( jet->etInAnnulus(0.,0.1) / totalEnergy );
			localJet.setDR02EnergyFraction( jet->etInAnnulus(0.,0.2) / totalEnergy );
			localJet.setDR03EnergyFraction( jet->etInAnnulus(0.,0.3) / totalEnergy );
			localJet.setDR04EnergyFraction( jet->etInAnnulus(0.,0.4) / totalEnergy );
			localJet.setDR05EnergyFraction( jet->etInAnnulus(0.,0.5) / totalEnergy );
		}
		
		
		if( dataType_=="RECO" )
		{
			// Some specific methods to reco::Jet
			// Do association to genParticle ?
			
			if( jetType=="CALO" )
			{
				// Variables from reco::CaloJet
				const reco::CaloJet *caloJet = dynamic_cast<const reco::CaloJet*>(&*jet);
				localJet.setJetType(1);
				localJet.setEcalEnergyFraction(caloJet->emEnergyFraction());
				localJet.setHcalEnergyFraction(caloJet->energyFractionHadronic());
				//std::vector<CaloTowerPtr> getCaloConstituents () const;
			}
			
			if( jetType=="PF" )
			{
				// Variables from reco::PFJet
				const reco::PFJet *pfJet = dynamic_cast<const reco::PFJet*>(&*jet);
				localJet.setJetType(2);
				localJet.setEcalEnergyFraction(pfJet->chargedEmEnergyFraction() + pfJet->neutralEmEnergyFraction());
				localJet.setHcalEnergyFraction(pfJet->chargedHadronEnergyFraction() + pfJet->neutralHadronEnergyFraction());
				if(pfJet->energy() != 0) localJet.setChargedEnergyFraction( (pfJet->chargedEmEnergy() + pfJet->chargedHadronEnergy() + pfJet->chargedMuEnergy() ) / pfJet->energy());
				localJet.setChargedMultiplicity((int)pfJet->chargedMultiplicity()) ;
				//std::vector <const reco::PFCandidate*> getPFConstituents () const;
			}
			
		}
		
		
		if( dataType_=="PAT" )
		{
			// Some specific methods to pat::Jet
			const pat::Jet *patJet = dynamic_cast<const pat::Jet*>(&*jet);
			
			// Variables from pat::Jet (Basic)
			localJet.setBtag_trackCountingHighEff(patJet->bDiscriminator("trackCountingHighEffBJetTags"));
			localJet.setBtag_trackCountingHighPur(patJet->bDiscriminator("trackCountingHighPurBJetTags"));
			localJet.setBtag_jetProbability(patJet->bDiscriminator("jetProbabilityBJetTags"));
			
			// see DataFormats/PatCandidates/interface/JetCorrFactors.h
			localJet.setBCorrection(patJet->corrFactor("part","b"));
			localJet.setCCorrection(patJet->corrFactor("part","c"));
			localJet.setUDSCorrection(patJet->corrFactor("part","uds"));
			localJet.setGCorrection(patJet->corrFactor("part","glu"));
			
			// Use  associated tracks to calculate charged broadness of the jet
			// FIXME - Check generalTracks collection is present
			reco::TrackRefVector tracks =  patJet->associatedTracks() ;
			Float_t deltaR = 0.;
			Float_t pTrackerTot = 0.;
			Float_t pTrackerCone01 = 0.;
			Float_t pTrackerCone02 = 0.;
			Float_t pTrackerCone03 = 0.;
			Float_t pTrackerCone04 = 0.;
			Float_t pTrackerCone05 = 0.;
			// TODO - Use std::map....
			vector < pair < Float_t , Float_t > > tracksVPair ;
			pair < Float_t , Float_t > tracksPair;
			
			for(unsigned int iTracks = 0; iTracks< patJet->associatedTracks().size() ; iTracks++)
			{
				deltaR = localJet.DeltaR(TLorentzVector(tracks[iTracks]->px(),tracks[iTracks]->py(),tracks[iTracks]->pz(),0));
				pTrackerTot += tracks[iTracks]->p();
				tracksPair.first = tracks[iTracks]->p();
				tracksPair.second = deltaR;
				tracksVPair.push_back(tracksPair);
				if(deltaR < 0.5) pTrackerCone05 += tracks[iTracks]->p();
				if(deltaR < 0.4) pTrackerCone04 += tracks[iTracks]->p();
				if(deltaR < 0.3) pTrackerCone03 += tracks[iTracks]->p();
				if(deltaR < 0.2) pTrackerCone02 += tracks[iTracks]->p();
				if(deltaR < 0.1) pTrackerCone01 += tracks[iTracks]->p();
			}
			sort(tracksVPair.begin(), tracksVPair.end(), Rsortrule);
			Float_t Rmin = 0;
			Float_t pDummy = 0;
			for(std::vector<std::pair< Float_t,Float_t > >::iterator i = tracksVPair.begin(); i!=tracksVPair.end(); i++)
			{
				pDummy+=(*i).first;
				if (pDummy>0.75*(pTrackerTot))
				{
					Rmin = (*i).second;
					break;
				}
			}
			if (Rmin<1e-5) {Rmin=0.;}
			localJet.setChargedBroadness(Rmin);
			if(pTrackerTot !=0)
			{
				localJet.setChargedBroadnessDR01(pTrackerCone01/pTrackerTot);
				localJet.setChargedBroadnessDR02(pTrackerCone02/pTrackerTot);
				localJet.setChargedBroadnessDR03(pTrackerCone03/pTrackerTot);
				localJet.setChargedBroadnessDR04(pTrackerCone04/pTrackerTot);
				localJet.setChargedBroadnessDR05(pTrackerCone05/pTrackerTot);
			}
			
			
			if ( patJet->isCaloJet() ) {
				// Variables from pat::Jet (CaloSpecific)
				localJet.setJetType(1);
				localJet.setEcalEnergyFraction(patJet->emEnergyFraction());
				localJet.setHcalEnergyFraction(patJet->energyFractionHadronic());
				localJet.setChargedMultiplicity(patJet->associatedTracks().size()) ;
				//std::vector<CaloTowerPtr> getCaloConstituents () const;
			}
			
			if(patJet->isPFJet()) {
				// Variables from pat::Jet (PFSpecific)
				localJet.setJetType(2);
				localJet.setEcalEnergyFraction(patJet->chargedEmEnergyFraction() + patJet->neutralEmEnergyFraction());
				localJet.setHcalEnergyFraction(patJet->chargedHadronEnergyFraction() + patJet->neutralHadronEnergyFraction());
				if(patJet->energy() != 0) localJet.setChargedEnergyFraction( (patJet->chargedEmEnergy() + patJet->chargedHadronEnergy() + patJet->chargedMuEnergy() ) / patJet->energy());
				localJet.setChargedMultiplicity((int)patJet->chargedMultiplicity()) ;
				//std::vector <const reco::PFCandidate*> getPFConstituents () const;
			}
			
			// Matched genParticle
			if (useMC_)
			{
				// MC truth associator index
				if ((patJet->genParticleRef()).isNonnull()) {
					localJet.setGenParticleIndex((patJet->genParticleRef()).index());
				} else {
					localJet.setGenParticleIndex(-1);
				}
				
				// check if jet comes from a top
				bool IsTopJet =  false;
				if(patJet->genParton())
				{
					const reco::Candidate* gen = patJet->genParton();
					while(gen->mother())
					{
						if(abs((gen->mother())->pdgId()) == 6)
						{
							IsTopJet =  true;
							break;
						}
						else
						{
							gen = (gen->mother() );
						}
					}
				}
				localJet.setIsTopJet(IsTopJet);
				
				// Matched generated jet
				if ( patJet->genJet() != NULL )
				{
					localJet.setGenJetEnergy( patJet->genJet()->energy() );
				}
				
			}
		}
		
		new( (*rootJets)[j] ) TRootJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;
	}
	
	return true;
}
