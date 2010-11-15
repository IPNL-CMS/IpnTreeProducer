#include "../interface/PhotonAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;


PhotonAnalyzer::PhotonAnalyzer(const edm::InputTag& photonProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity), iconvtrack_(0)
{
   dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
   photonProducer_ = photonProducer;
   reducedBarrelEcalRecHitCollection_ = producersNames.getParameter<edm::InputTag>("reducedBarrelEcalRecHitCollection");
   reducedEndcapEcalRecHitCollection_ = producersNames.getParameter<edm::InputTag>("reducedEndcapEcalRecHitCollection");
   doPhotonConversion_ = myConfig.getUntrackedParameter<bool>("doPhotonConversion", false);
   doVertexCorrection_ = myConfig.getUntrackedParameter<bool>("doPhotonVertexCorrection", false);
   useMC_ = myConfig.getUntrackedParameter<bool>("doMuonMC", false);
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}


PhotonAnalyzer::~PhotonAnalyzer()
{
}


bool PhotonAnalyzer::process(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent, TClonesArray* rootPhotons, TClonesArray* conversionTracks, ConversionLikelihoodCalculator* convLikelihoodCalculator, EcalClusterLazyTools* lazyTools)
{
   
   unsigned int nPhotons=0;

   bool doRecHits = true;
   const EcalRecHitCollection *reducedEBRecHits = 0;
   const EcalRecHitCollection *reducedEERecHits = 0;
   
   bool doPhotonID = true;
   edm::Handle< reco::PhotonCollection > recoPhotons;
   const edm::ValueMap<Bool_t> *looseEMPhotonIdMap = 0;
   const edm::ValueMap<Bool_t> *loosePhotonIdMap = 0;
   const edm::ValueMap<Bool_t> *tightPhotonIdMap = 0;
   
   if( dataType_=="RECO" )
   {
      try
      {
         iEvent.getByLabel(photonProducer_, recoPhotons);
         nPhotons = recoPhotons->size();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  PhotonAnalyzer::process => reco::Photon collection is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No reco::Photon collection, skip photons info" << endl;
         return false;
      }
      
      try
      {
         edm::Handle < EcalRecHitCollection > redEBRecHits;
         edm::Handle < EcalRecHitCollection > redEERecHits;
         iEvent.getByLabel(reducedBarrelEcalRecHitCollection_, redEBRecHits );
         reducedEBRecHits = redEBRecHits.product();
         iEvent.getByLabel(reducedEndcapEcalRecHitCollection_, redEERecHits ) ;
         reducedEERecHits = redEERecHits.product();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            if(verbosity_>1) cout << endl << "  ##### ERROR IN  PhotonAnalyzer::process => reduced EcalRecHitCollections are missing #####" << endl;
            throw exception;
         }
         if(verbosity_>1) cout << endl << "   ===> No reduced EcalRecHitCollections, skip photon rechits infos" << endl;
         doRecHits = false;
      }
      
      try
      {
         edm::Handle< edm::ValueMap<Bool_t> > looseEMPhotonId;
         iEvent.getByLabel("PhotonIDProd", "PhotonCutBasedIDLooseEM", looseEMPhotonId);
         looseEMPhotonIdMap = looseEMPhotonId.product();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  PhotonAnalyzer::process => PhotonCutBasedIDLooseEM is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No PhotonCutBasedIDLooseEM collection, skip photonID info" << endl;
         doPhotonID = false;
      }
      
      try
      {
         edm::Handle< edm::ValueMap<Bool_t> > loosePhotonId;
         iEvent.getByLabel("PhotonIDProd", "PhotonCutBasedIDLoose", loosePhotonId);
         loosePhotonIdMap = loosePhotonId.product();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  PhotonAnalyzer::process => PhotonCutBasedIDLoose is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No PhotonCutBasedIDLoose collection, skip photonID info" << endl;
         doPhotonID = false;
      }
      
      try
      {
         edm::Handle< edm::ValueMap<Bool_t> > tightPhotonId;
         iEvent.getByLabel("PhotonIDProd", "PhotonCutBasedIDTight", tightPhotonId);
         tightPhotonIdMap = tightPhotonId.product();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  PhotonAnalyzer::process => PhotonCutBasedIDTight is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No PhotonCutBasedIDTight collection, skip photonID info" << endl;
         doPhotonID = false;
      }
   }
   
   edm::Handle < std::vector <pat::Photon> > patPhotons;
   if( dataType_=="PAT" )
   {
      try
      {
         iEvent.getByLabel(photonProducer_, patPhotons);
         nPhotons = patPhotons->size();
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR IN  PhotonAnalyzer::process => pat::Photon collection is missing #####"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No pat::Photon collection, skip photons info" << endl;
         return false;
      }
   }
   
   if(verbosity_>1) std::cout << "   Number of photons = " << nPhotons << "   Label: " << photonProducer_.label() << "   Instance: " << photonProducer_.instance() << std::endl;
   
   
   // TODO - add Pi0Disc... not implemented in 2.X.X
   //edm::Handle<reco::PhotonPi0DiscriminatorAssociationMap>  pi0map;
   //iEvent.getByLabel("piZeroDiscriminators","PhotonPi0DiscriminatorAssociationMap",  pi0map);
   //reco::PhotonPi0DiscriminatorAssociationMap::const_iterator pi0mapIter;
   //Double_t pi0nn;
   
   
   for (unsigned int j=0; j<nPhotons; j++)
   {
      const reco::Photon* photon = 0;
      if( dataType_=="RECO" ) photon =  &((*recoPhotons)[j]);
      if( dataType_=="PAT" ) photon = (const reco::Photon*) ( & ((*patPhotons)[j]) );
      
      TRootPhoton localPhoton(
         photon->px()
         ,photon->py()
         ,photon->pz()
         ,photon->energy()
         ,photon->vx()
         ,photon->vy()
         ,photon->vz()
         ,photon->pdgId()
         ,photon->charge()
      );
      
      // TODO - Nicolas
      //- HCAL energy autour des traces converties dans un cone de dR<0.1... utile ?
      
      // Variables from reco::Photon
      localPhoton.setCaloPosition( photon->caloPosition().X(), photon->caloPosition().Y(), photon->caloPosition().Z() );
      localPhoton.setHoE(photon->hadronicOverEm());
      localPhoton.setHasPixelSeed( photon->hasPixelSeed() );
      localPhoton.setSigmaEtaEta(photon->sigmaEtaEta());
      localPhoton.setSigmaIetaIeta(photon->sigmaIetaIeta());
      
      
      // Variables from reco::SuperCluster
      reco::SuperClusterRef superCluster = photon->superCluster();
      if ( superCluster.isNonnull() )
      {
         localPhoton.setNbClusters(superCluster->clustersSize());
         localPhoton.setSuperClusterRawEnergy( superCluster->rawEnergy() );
         localPhoton.setPreshowerEnergy(superCluster->preshowerEnergy());
      }
      
      
      // Cluster Shape variables
      // need reco::SuperCluster and reco::CaloCluster
      if ( superCluster.isNonnull() )
      {
         reco::CaloClusterPtr seedCaloCluster = superCluster->seed();
         if ( seedCaloCluster.isNonnull() ) localPhoton.setClusterAlgo(seedCaloCluster->algo());
         
         // dR of the cone centered on the reco::Photon and containing all its basic clusters constituents
         bool atLeastOneBC = false;
         Float_t caloConeSize = 0.;
         for (reco::CaloCluster_iterator caloCluster = (*superCluster).clustersBegin(); caloCluster != (*superCluster).clustersEnd(); ++caloCluster )
         {
            atLeastOneBC = true;
            // Take SC position which is not vertex corrected
            TVector3 scPosition( superCluster->position().x(), superCluster->position().y(), superCluster->position().z() );
            Float_t dR = scPosition.DeltaR( TVector3( (*caloCluster)->position().x(), (*caloCluster)->position().y(), (*caloCluster)->position().z() ) );
            if (dR > caloConeSize) caloConeSize = dR;
         }
         if (! atLeastOneBC) caloConeSize = -999.;
         localPhoton.setCaloConeSize(caloConeSize);
         
         // need reduced Ecal RecHits Collections for EcalClusterLazyTools
         if ( seedCaloCluster.isNonnull() && lazyTools != 0 )
         {
            localPhoton.setE2x2(lazyTools->e2x2(*seedCaloCluster));
            localPhoton.setE3x3( lazyTools->e3x3(*seedCaloCluster) );
            localPhoton.setE5x5( lazyTools->e5x5(*seedCaloCluster) );
            localPhoton.setEMax( lazyTools->eMax(*seedCaloCluster) );
            localPhoton.setE2nd(lazyTools->e2nd(*seedCaloCluster));
            localPhoton.setCovEtaEta( (lazyTools->covariances(*seedCaloCluster)).at(0) );
            localPhoton.setCovEtaPhi( (lazyTools->covariances(*seedCaloCluster)).at(1) );
            localPhoton.setCovPhiPhi( (lazyTools->covariances(*seedCaloCluster)).at(2) );
            localPhoton.setEtaLAT((lazyTools->lat(*seedCaloCluster)).at(0));
            localPhoton.setPhiLAT((lazyTools->lat(*seedCaloCluster)).at(1));
            localPhoton.setLAT((lazyTools->lat(*seedCaloCluster)).at(2));
            localPhoton.setZernike20(lazyTools->zernike20(*seedCaloCluster));
            localPhoton.setZernike42(lazyTools->zernike42(*seedCaloCluster));
         }
         
         // FIXME - 2nd Moments implemented in EB only 
         if( fabs( seedCaloCluster->eta() ) < 1.479 )
         {
            Cluster2ndMoments moments =  EcalClusterTools::cluster2ndMoments( *seedCaloCluster, *reducedEBRecHits, 0.8, 4.7, true);
            localPhoton.setSecondMomentMaj(moments.sMaj);
            localPhoton.setSecondMomentMin(moments.sMin);
            localPhoton.setSecondMomentAlpha(moments.alpha);
         }
      }
      
      
      // Photon conversions
      // Variables from reco::Conversion
      if( doPhotonConversion_ )
      {
         // If more than one associated convertedPhotons is found, then
         // if nTracks=2, select the convertedPhoton with greatest Likelihood value using Ted's weights file
         // if nTracks=1, select the convertedPhoton with E/p closest to 1
         double eoverp;
         double best_eoverp = 999999.;
         double likely;
         double best_likely = -1.;
         int best_iconv = -1;
         int  best_iconv_likely = -1;
         int  best_iconv_eoverp = -1;
         
         reco::ConversionRefVector conversions = photon->conversions();
         for (unsigned int iconv=0; iconv<conversions.size(); iconv++)
         {
            if(verbosity_>4) cout << "   ["<< setw(3) << iconv << "] Conversion - "
               << " conv_vertex (x,y,z)=(" << conversions[iconv]->conversionVertex().x()
               << "," << conversions[iconv]->conversionVertex().y()
               << "," << conversions[iconv]->conversionVertex().z()
               << ")  isConverted=" << conversions[iconv]->isConverted()
               << "  nTracks=" << conversions[iconv]->nTracks()
               << "  primary_vtx_z=" << conversions[iconv]->zOfPrimaryVertexFromTracks()
               << "  inv_mass=" << conversions[iconv]->pairInvariantMass()
               << "  E/p=" << conversions[iconv]->EoverP()
               << "  cotanTheta=" << conversions[iconv]->pairCotThetaSeparation()
               << "  likely=" << convLikelihoodCalculator->calculateLikelihood(conversions[iconv], iSetup)
               << endl;
               
               likely = convLikelihoodCalculator->calculateLikelihood(conversions[iconv], iSetup);
               if ( likely>best_likely )
               {
                  best_iconv_likely = iconv;
                  best_likely = likely;
               }
               
               eoverp = conversions[iconv]->EoverP();
               if ( abs(eoverp-1)<abs(best_eoverp-1) )
               {
                  best_iconv_eoverp = iconv;
                  best_eoverp = eoverp;
               }
         }
         
         best_iconv = (best_iconv_likely==-1 ?  best_iconv_eoverp : best_iconv_likely);
         
         // Update Photon object with conversion infos
         if ( best_iconv != -1 )
         {
            if(verbosity_>4) cout
               << "   ===> TRootPhoton[" << j << "] associated to Conversion[" << best_iconv
               << "] with E/p="  << conversions[best_iconv]->EoverP()
               << "  likely=" << convLikelihoodCalculator->calculateLikelihood(conversions[best_iconv], iSetup)
               << endl;
            
            localPhoton.setConvNTracks( conversions[best_iconv]->nTracks() );
            localPhoton.setConvEoverP( conversions[best_iconv]->EoverP() );
            localPhoton.setConvMass( conversions[best_iconv]->pairInvariantMass() );
            localPhoton.setConvCotanTheta( conversions[best_iconv]->pairCotThetaSeparation() );
            localPhoton.setConvLikely( convLikelihoodCalculator->calculateLikelihood(conversions[best_iconv], iSetup) );
            localPhoton.setConvVertex( conversions[best_iconv]->conversionVertex().x(), conversions[best_iconv]->conversionVertex().y(), conversions[best_iconv]->conversionVertex().z() );
            std::vector<math::XYZPoint>  impactVector = conversions[best_iconv]->ecalImpactPosition();
            if ( impactVector.size()>0 ) localPhoton.setConvEcalImpactPosition1( impactVector.at(0).x(), impactVector.at(0).y(), impactVector.at(0).z() );
            if ( impactVector.size()>1 ) localPhoton.setConvEcalImpactPosition2( impactVector.at(1).x(), impactVector.at(1).y(), impactVector.at(1).z() );
            
            if ( conversionTracks!=0 )  // Check branch is activated
            {
               if ( conversions[best_iconv]->nTracks()>0 )
               {
                  std::vector<reco::TrackRef> tracks = conversions[best_iconv]->tracks();
                  reco::TrackRef tk1 = tracks.at(0);
                  const reco::HitPattern& hit1 = tk1->hitPattern();
                  new( (*conversionTracks)[iconvtrack_] ) TRootTrack( tk1->px(), tk1->py(), tk1->pz(), tk1->p(), tk1->vx(), tk1->vy(), tk1->vz(), 0, tk1->charge()
                  ,hit1.pixelLayersWithMeasurement(), hit1.stripLayersWithMeasurement(), tk1->chi2(), tk1->d0(), tk1->d0Error(), tk1->dz(), tk1->dzError() );
                  localPhoton.setConvIndexTrack1(iconvtrack_);
                  localPhoton.setConvTrack1((*conversionTracks)[iconvtrack_]);
                  iconvtrack_++;
                  
                  if ( conversions[best_iconv]->nTracks()>1 )
                  {
                     reco::TrackRef tk2 = tracks.at(1);
                     const reco::HitPattern& hit2 = tk2->hitPattern();
                     new( (*conversionTracks)[iconvtrack_] ) TRootTrack( tk2->px(), tk2->py(), tk2->pz(), tk2->p(), tk2->vx(), tk2->vy(), tk2->vz(), 0, tk2->charge()
                     ,hit2.pixelLayersWithMeasurement(), hit2.stripLayersWithMeasurement(), tk2->chi2(), tk2->d0(), tk2->d0Error(), tk2->dz(), tk2->dzError() );
                     localPhoton.setConvIndexTrack2(iconvtrack_);
                     localPhoton.setConvTrack2((*conversionTracks)[iconvtrack_]);
                     iconvtrack_++;
                  }
               }
            }
         }
         else
         {
            localPhoton.setConvNTracks(0);
         }
         
      }
      
      
      // Photon isolation calculated by PhotonID
      // now embeded in reco::Photon
      localPhoton.setDR03Isolation(
         photon->ecalRecHitSumEtConeDR03()
         ,photon->hcalTowerSumEtConeDR03()
         ,photon->trkSumPtSolidConeDR03()
         ,photon->trkSumPtHollowConeDR03()
         ,photon->nTrkSolidConeDR03()
         ,photon->nTrkHollowConeDR03()
      );
      
      localPhoton.setDR04Isolation(
         photon->ecalRecHitSumEtConeDR04()
         ,photon->hcalTowerSumEtConeDR04()
         ,photon->trkSumPtSolidConeDR04()
         ,photon->trkSumPtHollowConeDR04()
         ,photon->nTrkSolidConeDR04()
         ,photon->nTrkHollowConeDR04()
      );
      
      
      if( dataType_=="RECO" )
      {
         // Some specific methods requiring  RECO / AOD format
         // Do association to genParticle ?
         
         if (doPhotonID)
         {
            // Photon ID
            // need corresponding PhotonID ValueMap
            edm::Ref<reco::PhotonCollection> photonRef(recoPhotons,j);
            Bool_t looseEMID = (*looseEMPhotonIdMap)[photonRef];
            Bool_t looseID = (*loosePhotonIdMap)[photonRef];
            Bool_t tightID = (*tightPhotonIdMap)[photonRef];
            localPhoton.setBitsID(
               looseEMID
               ,looseID
               ,tightID
               ,photon->isEB()
               ,photon->isEE()
               ,photon->isEBGap()
               ,photon->isEEGap()
               ,photon->isEBEEGap()
            );
         }
         
         /*
          *         if(verbosity_>4) std::cout << "seed E5x5=" << lazyTools->e5x5( *seedCaloCluster )
          *         //<< " pi0NN=" << pi0nn
          *         << " photonID->isolationEcalRecHit()=" << photonID->isolationEcalRecHit()
          *         << " photonID->r9()=" << photonID->r9()
          *         << " e3x3 / SC->energy()=" << ( lazyTools->e3x3( *seedCaloCluster ) / photon->superCluster()->energy() )
          *         << " e3x3 / SC->rawEnergy()=" << ( lazyTools->e3x3( *seedCaloCluster ) / photon->superCluster()->rawEnergy() )
          *         << " sc->pos=" << photon->superCluster()->position().X() << " , " <<  photon->superCluster()->position().Y() << " , " << photon->superCluster()->position().Z()
          *         << " photon->caloPos=" << photon->caloPosition().X() << " , " <<  photon->caloPosition().Y() << " , " << photon->caloPosition().Z()             << std::endl;
          */
      }
      
      
      if( dataType_=="PAT" )
      {
         // Some specific methods to pat::Photon
         const pat::Photon *patPhoton = dynamic_cast<const pat::Photon*>(&*photon);
         
         // Photon ID
         // Use the PhotonID pairs embeded in pat::Photon
         Bool_t looseEMID = false;
         Bool_t looseID = false;
         Bool_t tightID = false;
         if (patPhoton->isPhotonIDAvailable("PhotonCutBasedIDLooseEM")) looseEMID = patPhoton->photonID("PhotonCutBasedIDLooseEM");
         if (patPhoton->isPhotonIDAvailable("PhotonCutBasedIDLoose")) looseID = patPhoton->photonID("PhotonCutBasedIDLoose");
         if (patPhoton->isPhotonIDAvailable("PhotonCutBasedIDTight")) tightID = patPhoton->photonID("PhotonCutBasedIDTight");
         localPhoton.setBitsID(
            looseEMID
            ,looseID
            ,tightID
            ,patPhoton->isEB()
            ,patPhoton->isEE()
            ,patPhoton->isEBGap()
            ,patPhoton->isEEGap()
            ,patPhoton->isEBEEGap()
         );
         
         if(useMC_)
         {
            // MC truth associator index
            if ((patPhoton->genParticleRef()).isNonnull()) {
               localPhoton.setGenParticleIndex((patPhoton->genParticleRef()).index());
            } else {
               localPhoton.setGenParticleIndex(-1);
            }
         }
      }
      
      
      // FIXME - Add pi0nn
      //pi0mapIter = pi0map->find(edm::Ref<reco::PhotonCollection>(recoPhotons,iPhoton));
      //pi0nn = ( pi0mapIter == pi0map->end() ? -1 : pi0mapIter->val );
      //localPhoton.setPi0nn( pi0nn );
      
      
      // Vertex correction to photon - Assume photon is coming from primary vertex
      if( doVertexCorrection_)
      {
         if(verbosity_>3) cout << "   Before vertex correction  ["<< setw(3) << j << "] " << localPhoton << endl;
         if( rootEvent->primaryVertex()!=0 )
         {
            TVector3 vertex( rootEvent->primaryVertex()->x(), rootEvent->primaryVertex()->y(), rootEvent->primaryVertex()->z() );
            localPhoton.setVertex(vertex);
         }
         else
         {
            cout << "  PhotonAnalyzer - NO SELECTED PRIMARY VERTEX FOUND !!!" << endl;
         }
      }
      
      
      // Stock new TRootPhoton in TCloneArray
      new( (*rootPhotons)[j] ) TRootPhoton(localPhoton);
      if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localPhoton << endl;
   }
   
   return true;
}
