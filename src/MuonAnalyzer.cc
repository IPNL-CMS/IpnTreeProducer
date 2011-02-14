#include "../interface/MuonAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

MuonAnalyzer::MuonAnalyzer(const edm::InputTag& muonProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):LeptonAnalyzer(producersNames, myConfig, verbosity)
{
   useMC_ = myConfig.getUntrackedParameter<bool>("doMuonMC");
   muonProducer_ = muonProducer;
}

MuonAnalyzer::~MuonAnalyzer()
{
}

bool MuonAnalyzer::process(const edm::Event& iEvent, TRootBeamSpot* rootBeamSpot, TClonesArray* rootMuons)
{
   
   Float_t sintheta = 0.;
   unsigned int nMuons=0;
   edm::Handle < std::vector <reco::Muon> > recoMuons;
   if( dataType_=="RECO" )
   {
      try
      {
         iEvent.getByLabel(muonProducer_, recoMuons);
         nMuons = recoMuons->size();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  MuonAnalyzer::process => reco::Muon collection is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No reco::Muon collection, skip muon info" << endl;
         return false;
      }
   }
   
   edm::Handle < std::vector <pat::Muon> > patMuons;
   if( dataType_=="PAT" )
   {
      try
      {
         iEvent.getByLabel(muonProducer_, patMuons);
         nMuons = patMuons->size();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  MuonAnalyzer::process => pat::Muon collection is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No pat::Muon collection, skip muon info" << endl;
         return false;
      }
   }
   
   if(verbosity_>1) std::cout << "   Number of muons = " << nMuons << "   Label: " << muonProducer_.label() << "   Instance: " << muonProducer_.instance() << std::endl;
   
   for (unsigned int j=0; j<nMuons; j++)
   {
      const reco::Muon* muon = 0;
      if( dataType_=="RECO" ) muon =  &((*recoMuons)[j]);
      if( dataType_=="PAT" ) muon = (const reco::Muon*) ( & ((*patMuons)[j]) );
      
      TRootMuon localMuon(
      muon->px()
      ,muon->py()
      ,muon->pz()
      ,muon->energy()
      ,muon->vx()
      ,muon->vy()
      ,muon->vz()
      ,muon->pdgId()
      ,muon->charge()
      );
      
      // Variables from reco::Muon
      sintheta = sin( localMuon.Theta() );
      
      localMuon.setNumberOfChambers( muon->numberOfChambers() );
      localMuon.setNumberOfMatches( muon->numberOfMatches() );
      
      localMuon.setCaloEnergy(
      muon->calEnergy().em * sintheta
      ,muon->calEnergy().emS9 * sintheta
      ,muon->calEnergy().emS25 * sintheta
      ,muon->calEnergy().emMax * sintheta
      ,muon->calEnergy().had * sintheta
      ,muon->calEnergy().hadS9 * sintheta
      ,muon->calEnergy().ho * sintheta
      ,muon->calEnergy().hoS9 * sintheta
      ,muon->caloCompatibility()
      );
      
      localMuon.setIsoR03(
      muon->isolationR03().emEt
      ,muon->isolationR03().hadEt
      ,muon->isolationR03().hoEt
      ,muon->isolationR03().sumPt
      ,muon->isolationR03().nTracks
      ,muon->isolationR03().nJets
      );
      
      localMuon.setIsoR05(
      muon->isolationR05().emEt
      ,muon->isolationR05().hadEt
      ,muon->isolationR05().hoEt
      ,muon->isolationR05().sumPt
      ,muon->isolationR05().nTracks
      ,muon->isolationR05().nJets
      );
      
      localMuon.setValidity(
      muon->isEnergyValid()
      ,muon->isMatchesValid()
      ,muon->isIsolationValid()
      );
      
      localMuon.setDirection( muon->time().direction() );
      localMuon.setAlgo( muon->type() );
      localMuon.setID(
      //         int( muon::isGoodMuon( &muon, muon::AllGlobalMuons ) )
      //         ,int( muon::isGoodMuon( &muon, muon::AllStandAloneMuons ) )
      //         ,int( muon::isGoodMuon( &muon, muon::AllTrackerMuons ) )
      int( muon::isGoodMuon( *muon, muon::TrackerMuonArbitrated ) )
      ,int( muon::isGoodMuon( *muon, muon::AllArbitrated ) )
      ,int( muon::isGoodMuon( *muon, muon::GlobalMuonPromptTight ) )
      ,int( muon::isGoodMuon( *muon, muon::TMLastStationLoose ) )
      ,int( muon::isGoodMuon( *muon, muon::TMLastStationTight ) )
      ,int( muon::isGoodMuon( *muon, muon::TM2DCompatibilityLoose ) )
      ,int( muon::isGoodMuon( *muon, muon::TM2DCompatibilityTight ) )
      //         ,int( muon::isGoodMuon( &muon, muon::TMOneStationLoose ) )
      //         ,int( muon::isGoodMuon( &muon, muon::TMOneStationTight ) )
      //         ,int( muon::isGoodMuon( &muon, muon::TMLastStationOptimizedLowPtLoose ) )
      //         ,int( muon::isGoodMuon( &muon, muon::TMLastStationOptimizedLowPtTight ) )
      );
      
      // Variables from reco::Track
      // Track in muon detector only
      reco::TrackRef outerTK = muon->outerTrack();
      if ( outerTK.isNonnull() )
      {
         //cout << "outerTK (px,py,pz)=" << outerTK->px() <<" , " << outerTK->py() <<" , " << outerTK->pz() <<" )" << endl;
         localMuon.setXYZTOuterTrack( outerTK->px(), outerTK->py(), outerTK->pz(), outerTK->p() );
      }
      
      // Track in tracker + muon detector
      reco::TrackRef globalTK = muon->globalTrack();
      if ( globalTK.isNonnull() )
      {
         //cout << "globalTK (px,py,pz)=" << globalTK->px() <<" , " << globalTK->py() <<" , " << globalTK->pz() <<" )" << endl;
         localMuon.setXYZTGlobalTrack( globalTK->px(), globalTK->py(), globalTK->pz(), globalTK->p() );
         localMuon.setNumberOfValidGlobalHits(globalTK->hitPattern().numberOfValidMuonHits());
         localMuon.setNormalizedGlobalChi2(globalTK->normalizedChi2());
      }
      
      // Track in tracker only
      reco::TrackRef track = muon->innerTrack();
      if ( track.isNonnull() )
      {
         //cout << "innerTK (px,py,pz)=" << track->px() <<" , " << track->py() <<" , " << track->pz() <<" )" << endl;
         localMuon.setXYZTInnerTrack( track->px(), track->py(), track->pz(), track->p() );
         const reco::HitPattern& hit = track->hitPattern();
         localMuon.setNumberOfValidPixelHits(hit.numberOfValidPixelHits());
         localMuon.setNumberOfValidTrackerHits(hit.numberOfValidTrackerHits());
         localMuon.setPixelLayersWithMeasurement(hit.pixelLayersWithMeasurement());
         localMuon.setStripLayersWithMeasurement(hit.stripLayersWithMeasurement());
         
         if (vertexPoint_!=0)
         {
            const reco::TrackBase::Point point( vertexPoint_->x(), vertexPoint_->y(), vertexPoint_->z() );
            localMuon.setD0( -1.*(track->dxy(point)) );
            localMuon.setDsz( track->dsz(point) );
         }
         else
         {
            localMuon.setD0( -1.*(track->dxy()) );
            localMuon.setDsz( track->dsz() );
         }
         
         // FIXME - Add Vertex error quadratically
         localMuon.setD0Error(track->d0Error());
         localMuon.setDszError(track->dszError());
         
         localMuon.setNormalizedChi2(track->normalizedChi2());
         localMuon.setPtError(track->ptError());
         localMuon.setEtaError(track->etaError());
         localMuon.setPhiError(track->phiError());
         
         if(doPrimaryVertex_)
         {
            // FIXME - Should be Tracker track... what if STA muon ?
            const reco::TransientTrack transtrack = trackBuilder_->build( track ) ;
            float sig3d = ip3DSignificance(transtrack);
            localMuon.setIP3DSignificance(sig3d);
         }
         
         // Get the distance to the beamline corresponding to dB for pat::muons
         if(doBeamSpot_)
         {
            const reco::TrackBase::Point point( rootBeamSpot->x(), rootBeamSpot->y(), rootBeamSpot->z() );
            localMuon.setDB( -1.*(track->dxy(point)) );
         }
      }
      
      
      if( dataType_=="RECO" )
      {
         // Some specific methods requiring  RECO / AOD format
         // Do association to genParticle ?
      }
      
      if( dataType_=="PAT" )
      {
         // Some specific methods to pat::Muon
         const pat::Muon *patMuon = dynamic_cast<const pat::Muon*>(&*muon);
         std::string muonType="RecoMuon";
         if ((patMuon->pfCandidateRef()).isNonnull()) muonType="PFMuon";
         
         localMuon.setTrackIso(patMuon->trackIso());
         localMuon.setEcalIso(patMuon->ecalIso());
         localMuon.setHcalIso(patMuon->hcalIso());
         
         if (muonType=="RecoMuon")
         {
            localMuon.setEcalCandEnergy(patMuon->ecalIsoDeposit()->candEnergy() );
            localMuon.setHcalCandEnergy(patMuon->hcalIsoDeposit()->candEnergy() );
         }
         
         if (muonType=="PFMuon")
         {
            localMuon.setPFParticleIso(patMuon->particleIso());
            localMuon.setPFChargedHadronIso(patMuon->chargedHadronIso());
            localMuon.setPFNeutralHadronIso(patMuon->neutralHadronIso());
            localMuon.setPFPhotonIso(patMuon->photonIso());
         }
         
         // Use existing reference to genParticle [ pat::PATObject::genParticleRef() ] ?
         // Alternative methode for isolation (isoDeposit) ?
         //
         // leptonID apparently not initialised in PAT...
         // cout << "Valeur pourrie du leptonID=" << patMuon->leptonID() << endl;
         
         if(useMC_)
         {
            // MC truth associator index
            if ((patMuon->genParticleRef()).isNonnull()) {
               localMuon.setGenParticleIndex((patMuon->genParticleRef()).index());
            } else {
               localMuon.setGenParticleIndex(-1);
            }
         }
      }
      
      new( (*rootMuons)[j] ) TRootMuon(localMuon);
      if(verbosity_>2 && verbosity_<4) cout << "   ["<< setw(3) << j << "] " << localMuon << endl;
      if(verbosity_>=4) { cout << "   ["<< setw(3) << j << "] ";  localMuon.Print(); cout << endl; }
   }
   
   return true;
}
