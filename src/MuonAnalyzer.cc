#include "../interface/MuonAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

MuonAnalyzer::MuonAnalyzer(const edm::InputTag& muonProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):LeptonAnalyzer(producersNames, myConfig, verbosity)
{
   useMC_ = myConfig.getUntrackedParameter<bool>("doMuonMC");
   muonProducer_ = muonProducer;
   primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
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
   
   
   const reco::Vertex* primaryVertex = 0;
   edm::Handle< reco::VertexCollection > recoVertices;
   try
   {
      iEvent.getByLabel(primaryVertexProducer_, recoVertices);
      int nVertices = recoVertices->size();
      if(nVertices>0) primaryVertex = & ((*recoVertices)[0]);
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  MuonAnalyzer::process => Vertex collection is missing #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No primaryVertex collection, skip vertex info" << endl;
      return false;
   }
   
   
   
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
      
      localMuon.setMuonType(
         muon->isGlobalMuon() 
         ,muon->isTrackerMuon() 
         ,muon->isStandAloneMuon() 
         ,muon->isCaloMuon() 
         ,muon->isPFMuon() 
         ,muon->isRPCMuon() 
      );
      
      localMuon.setValidity(
         muon->isEnergyValid()
         ,muon->isIsolationValid()
         ,muon->isPFIsolationValid()
         ,muon->isQualityValid()
      );
      
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
      
      
      localMuon.setNumberOfChambers( muon->numberOfChambers() );
      localMuon.setNumberOfMatches( muon->numberOfMatches() );
      localMuon.setNumberOfMatchedStations( muon->numberOfMatchedStations() );
      localMuon.setTimeDirection( muon->time().direction() );
      
      localMuon.setCaloEnergy(
         muon->calEnergy().em * sintheta
         ,muon->calEnergy().emS9 * sintheta
         ,muon->calEnergy().emS25 * sintheta
         ,muon->calEnergy().emMax * sintheta
         ,muon->calEnergy().had * sintheta
         ,muon->calEnergy().hadS9 * sintheta
         ,muon->calEnergy().hadMax * sintheta
         ,muon->calEnergy().ho * sintheta
         ,muon->calEnergy().hoS9 * sintheta
         ,muon->caloCompatibility()
      );
      
      localMuon.setPfIsoR04(
         muon->pfIsolationR04().sumChargedHadronPt
         ,muon->pfIsolationR04().sumChargedParticlePt
         ,muon->pfIsolationR04().sumNeutralHadronEt
         ,muon->pfIsolationR04().sumPhotonEt
         ,muon->pfIsolationR04().sumNeutralHadronEtHighThreshold
         ,muon->pfIsolationR04().sumPhotonEtHighThreshold
         ,muon->pfIsolationR04().sumPUPt
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

      
      
      // Variables from reco::Track
      
      // Inner Track (Tracker only)
      reco::TrackRef innerTrack = muon->innerTrack();
      if ( innerTrack.isNonnull() )
      {
         //cout << "innerTK (px,py,pz)=" << innerTrack->px() <<" , " << innerTrack->py() <<" , " << innerTrack->pz() <<" )" << endl;
         localMuon.setXYZTInnerTrack( innerTrack->px(), innerTrack->py(), innerTrack->pz(), innerTrack->p() );
         const reco::HitPattern& hit = innerTrack->hitPattern();
         localMuon.setNumberOfValidPixelHitsInInnerTrack(hit.numberOfValidPixelHits());
         localMuon.setNumberOfValidTrackerHitsInInnerTrack(hit.numberOfValidTrackerHits());
         localMuon.setPixelLayersWithMeasurementInInnerTrack(hit.pixelLayersWithMeasurement());
         localMuon.setStripLayersWithMeasurementInInnerTrack(hit.stripLayersWithMeasurement());
         
         localMuon.setNormalizedChi2InnerTrack(innerTrack->normalizedChi2());
         localMuon.setPtErrorInnerTrack(innerTrack->ptError());
         localMuon.setEtaErrorInnerTrack(innerTrack->etaError());
         localMuon.setPhiErrorInnerTrack(innerTrack->phiError());
         
         if (primaryVertex!=0)
         {
            localMuon.setInnerTrackDxy( fabs(innerTrack->dxy(primaryVertex->position())) );
            localMuon.setInnerTrackDz( fabs(innerTrack->dz(primaryVertex->position())) );
         }
         else
         {
            cout << "  ##### ERROR IN  MuonAnalyzer::process => Vertex collection is missing #####"<<endl;
            localMuon.setInnerTrackDxy( fabs(innerTrack->dxy()) );
            localMuon.setInnerTrackDz( fabs(innerTrack->dz()) );
         }
         
         if(doPrimaryVertex_)
         {
            // FIXME - Should be Tracker track... what if STA muon ?
            const reco::TransientTrack transtrack = trackBuilder_->build( innerTrack ) ;
            float sig3d = ip3DSignificance(transtrack);
            localMuon.setIP3DSignificance(sig3d);
         }
      }
      
      
      // Outer Track (muon detector only)
      reco::TrackRef outerTK = muon->outerTrack();
      if ( outerTK.isNonnull() )
      {
         //cout << "outerTK (px,py,pz)=" << outerTK->px() <<" , " << outerTK->py() <<" , " << outerTK->pz() <<" )" << endl;
         localMuon.setXYZTOuterTrack( outerTK->px(), outerTK->py(), outerTK->pz(), outerTK->p() );
      }
      
      
      // Global Track (tracker + muon detector)
      reco::TrackRef globalTK = muon->globalTrack();
      if ( globalTK.isNonnull() )
      {
         //cout << "globalTK (px,py,pz)=" << globalTK->px() <<" , " << globalTK->py() <<" , " << globalTK->pz() <<" )" << endl;
         localMuon.setXYZTGlobalTrack( globalTK->px(), globalTK->py(), globalTK->pz(), globalTK->p() );
         localMuon.setNumberOfValidMuonHitsInGlobalTrack(globalTK->hitPattern().numberOfValidMuonHits());
         localMuon.setNormalizedChi2GlobalTrack(globalTK->normalizedChi2());
      }
      
      
      // Best Track
      reco::TrackRef bestTrack = muon->muonBestTrack();
      if ( bestTrack.isNonnull() )
      {
         if (primaryVertex!=0)
         {
            localMuon.setBestTrackDxy( fabs(bestTrack->dxy(primaryVertex->position())) );
            localMuon.setBestTrackDz( fabs(bestTrack->dz(primaryVertex->position())) );
         }
         else
         {
            cout << "  ##### ERROR IN  MuonAnalyzer::process => Vertex collection is missing #####"<<endl;
            localMuon.setBestTrackDxy( fabs(bestTrack->dxy()) );
            localMuon.setBestTrackDz( fabs(bestTrack->dz()) );
         }
      }
      

      // PF Muon
      localMuon.setXYZTPfTrack( muon->pfP4().Px(), muon->pfP4().Py(), muon->pfP4().Pz(), muon->pfP4().P() );
      
      
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
