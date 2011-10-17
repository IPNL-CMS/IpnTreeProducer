#include "../interface/SuperClusterAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;


SuperClusterAnalyzer::SuperClusterAnalyzer(const edm::ParameterSet& config, const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity), iClus_(0), doHcal_(true)
{
   dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
   caloTowerCollection_ = producersNames.getParameter<edm::InputTag>("caloTowerCollection");
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
   doCracksCorrection_ = config.getUntrackedParameter<bool>("doCracksCorrection", false);
   patEncapsulation_ = false;
   if( dataType_=="PAT" )
   {
      patEncapsulation_ = producersNames.getUntrackedParameter<bool>("patEncapsulation", false);
   }
}


SuperClusterAnalyzer::~SuperClusterAnalyzer()
{
}


bool SuperClusterAnalyzer::process(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent, TClonesArray* rootSuperClusters, const edm::InputTag& superClusterProducer, const int clusterType, TClonesArray* rootBasicClusters)
{
   
   // TODO - Use supercluster encapsulated in pat::Photon if patEncapsulation_ = true
   
   unsigned int nSuperClusters=0;
   const reco::SuperClusterCollection *superClusters = 0;
   try
   {
      edm::Handle<reco::SuperClusterCollection> superClustersHandle;
      iEvent.getByLabel(superClusterProducer, superClustersHandle);
      superClusters = superClustersHandle.product();
      nSuperClusters = superClusters->size();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  SuperClusterAnalyzer::process => reco::SuperCluster collection is missing Producer: " << superClusterProducer << " #####" << endl;
         throw exception;
      }
      if(verbosity_>1) cout << endl << "   ===> No reco::SuperCluster collection for Producer: " << superClusterProducer << " , skip superclusters info" << endl;
      return false;
   }
   
   // get Hcal towers
   const CaloTowerCollection* hcalTowers = 0;
   edm::Handle<CaloTowerCollection> hcalTowersHandle;
   try
   {
      iEvent.getByLabel(caloTowerCollection_, hcalTowersHandle);
      hcalTowers = hcalTowersHandle.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => CaloTowerCollection is missing #####" << endl;
         throw exception;
      }
      if(verbosity_>1) cout << endl << "   ===> No CaloTowerCollection, skip HCAL isolation info" << endl;
      doHcal_ = false;
   }
   
   
   if(verbosity_>1) cout << endl << "   Producer: " << superClusterProducer << " - Number of SuperClusters (type " << clusterType << ") = " << nSuperClusters << std::endl;
   
   Int_t iClusType=0;
   
   for( reco::SuperClusterCollection::const_iterator  aSuperClus = superClusters->begin(); aSuperClus != superClusters->end(); aSuperClus++)
   {
      TRootSuperCluster localClus( aSuperClus->energy(), aSuperClus->eta(), aSuperClus->phi(), aSuperClus->x(), aSuperClus->y(), aSuperClus->z(), clusterType);
      localClus.setNBasicClusters( aSuperClus->clustersSize() );
      localClus.setNxtals( (aSuperClus->hitsAndFractions()).size() );
      localClus.setPreshowerEnergy( aSuperClus->preshowerEnergy() );
      localClus.setRawEnergy( aSuperClus->rawEnergy() );
      localClus.setEtaWidth( aSuperClus->etaWidth() );
      localClus.setPhiWidth( aSuperClus->phiWidth() );
      
      // Get ES Plane ratio E3/E21
      reco::CaloClusterPtr seedCaloCluster = aSuperClus->seed();
      if (fabs(aSuperClus->eta())>1.62 && seedCaloCluster.isNonnull() )
      {
         float esratio = getESRatio(seedCaloCluster, iEvent, iSetup);
         localClus.setESratio( esratio );
      }
      
      unsigned int seedUID = 0;
      // The CaloCluster inherited by SuperCluster is not always the seed CaloCluster of the SuperCluster !!!!!
      //if ( (aSuperClus->hitsAndFractions()).size()>0 ) seedUID = (aSuperClus->hitsAndFractions()).at(0).first();
      if ( (aSuperClus->seed()->hitsAndFractions()).size()>0 ) seedUID = (aSuperClus->seed()->hitsAndFractions()).at(0).first();
      
      int iSubCluster=0;
      for( reco::CaloCluster_iterator  aBasicClus = aSuperClus->clustersBegin(); aBasicClus != aSuperClus->clustersEnd(); aBasicClus++)
      {
         unsigned int basicClusterUID = 0;
         if ( (aBasicClus->get()->hitsAndFractions()).size()>0 ) basicClusterUID = (aBasicClus->get()->hitsAndFractions()).at(0).first();
         localClus.addSubBasicClusterUID( basicClusterUID );
         if ( basicClusterUID==seedUID ) localClus.setSeedBasicClusterVectorIndex(iSubCluster);
         iSubCluster++;
      }
      
      if (doHcal_)
      {
         // size of the cone and Et threshold for H/E calculation
         // taken from RecoEgamma/EgammaPhotonProducers/src/PhotonProducer.cc
         // and RecoEgamma/EgammaPhotonProducers/python/photons_cfi.py
         double intRadius = 0.;
         double extRadius = 0.15;
         double etLow = 0.;
         EgammaTowerIsolation towerIso1(extRadius, intRadius, etLow, 1, hcalTowers) ;
         EgammaTowerIsolation towerIso2(extRadius, intRadius, etLow, 2, hcalTowers) ;
         double hoe1=towerIso1.getTowerESum(&(*aSuperClus))/aSuperClus->energy();
         double hoe2=towerIso2.getTowerESum(&(*aSuperClus))/aSuperClus->energy();
         localClus.setHoe1(hoe1);
         localClus.setHoe2(hoe2);
      }
      
      
      new( (*rootSuperClusters)[iClus_] ) TRootSuperCluster(localClus);
      if(verbosity_>3) cout << "   ["<< setw(3) << iClus_ << "] " << localClus << endl;
      
      iClus_++;
      iClusType++;
      
   }
   rootEvent->setNSuperClusters(clusterType,iClusType);
   return true;
   
   
}


float SuperClusterAnalyzer::getESRatio(reco::CaloClusterPtr& seed, const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   
   //get Geometry
   ESHandle<CaloGeometry> caloGeometry;
   iSetup.get<CaloGeometryRecord>().get(caloGeometry);
   const CaloSubdetectorGeometry *geometry = caloGeometry->getSubdetectorGeometry(DetId::Ecal, EcalPreshower);
   const CaloSubdetectorGeometry *& geometry_p = geometry;
   
   // Get ES rechits
   edm::Handle<EcalRecHitCollection> PreshowerRecHits;
   
   try
   {
      iEvent.getByLabel(InputTag("ecalPreshowerRecHit","EcalRecHitsES"), PreshowerRecHits);
      if(! PreshowerRecHits.isValid() )
      {
         if(verbosity_>1) cout << endl << "  ##### ERROR IN  SuperClusterAnalyzer::getESRatio ===> No valid ecalPreshowerRecHit collection, skip rechits infos" << endl;
         return -1.;
      }
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         if(verbosity_>1) cout << endl << "  ##### ERROR IN  SuperClusterAnalyzer::getESRatio => ecalPreshowerRecHit is missing #####" << endl;
         throw exception;
      }
      if(verbosity_>1) cout << endl << "   ===> No ecalPreshowerRecHit, skip ES Ratio calculation" << endl;
      return -1.;
   }
   
   EcalRecHitCollection preshowerHits(*PreshowerRecHits);
   Float_t esratio=-1.;
   
   //reco::CaloCluster cluster = (*seed);
   const GlobalPoint phopoint(seed->x(), seed->y(), seed->z());
   
   DetId photmp1 = (dynamic_cast<const EcalPreshowerGeometry*>(geometry_p))->getClosestCellInPlane(phopoint, 1);
   DetId photmp2 = (dynamic_cast<const EcalPreshowerGeometry*>(geometry_p))->getClosestCellInPlane(phopoint, 2);
   ESDetId esfid = (photmp1 == DetId(0)) ? ESDetId(0) : ESDetId(photmp1);
   ESDetId esrid = (photmp2 == DetId(0)) ? ESDetId(0) : ESDetId(photmp2);
   
   int gs_esfid = -99;
   int gs_esrid = -99;
   gs_esfid = esfid.six()*32+esfid.strip();
   gs_esrid = esrid.siy()*32+esrid.strip();
   
   float esfe3 = 0.;
   float esfe21 = 0.;
   float esre3 = 0.;
   float esre21 = 0.;
   
   const ESRecHitCollection *ESRH = PreshowerRecHits.product();
   EcalRecHitCollection::const_iterator esrh_it;
   for ( esrh_it = ESRH->begin(); esrh_it != ESRH->end(); esrh_it++) {
      ESDetId esdetid = ESDetId(esrh_it->id());
      if ( esdetid.plane()==1 ) {
         if ( esdetid.zside() == esfid.zside() &&
            esdetid.siy() == esfid.siy() ) {
            int gs_esid = esdetid.six()*32+esdetid.strip();
         int ss = gs_esid-gs_esfid;
         if ( TMath::Abs(ss)<=10) {
            esfe21 += esrh_it->energy();
         }
         if ( TMath::Abs(ss)<=1) {
            esfe3 += esrh_it->energy();
         }
         }
      }
      if (esdetid.plane()==2 ){
         if ( esdetid.zside() == esrid.zside() &&
            esdetid.six() == esrid.six() ) {
            int gs_esid = esdetid.siy()*32+esdetid.strip();
         int ss = gs_esid-gs_esrid;
         if ( TMath::Abs(ss)<=10) {
            esre21 += esrh_it->energy();
         }
         if ( TMath::Abs(ss)<=1) {
            esre3 += esrh_it->energy();
         }
         }
      }
   }
   
   if( (esfe21+esre21) == 0.) {
      esratio = 1.;
   }else{
      esratio = (esfe3+esre3) / (esfe21+esre21);
   }
   
   
   if ( esratio>1.) {
      cout << "es numbers " << esfe3 << " " << esfe21 << " " << esre3 << " " << esre21 << endl;
   }
   
   return esratio;
   
}
