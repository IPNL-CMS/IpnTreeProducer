#include "../interface/ClusterAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

bool operator< (const TRootEcalRecHit & left, const TRootEcalRecHit & right) { return left.energy()<right.energy(); }
bool decrease(const TRootEcalRecHit & left, const TRootEcalRecHit & right) { return left.energy()>right.energy(); }

ClusterAnalyzer::ClusterAnalyzer(const edm::ParameterSet& config, const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity), iClus_(0), doRecHits_(true)
{
   dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
   reducedBarrelEcalRecHitCollection_ = producersNames.getParameter<edm::InputTag>("reducedBarrelEcalRecHitCollection");
   reducedEndcapEcalRecHitCollection_ = producersNames.getParameter<edm::InputTag>("reducedEndcapEcalRecHitCollection");
   keepClusterizedEcalRecHits_ = config.getUntrackedParameter<bool>("keepClusterizedEcalRecHits", false);
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}


ClusterAnalyzer::~ClusterAnalyzer()
{
}


bool ClusterAnalyzer::process(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent, EcalClusterLazyTools* lazyTools, TClonesArray* rootClusters, const edm::InputTag& basicClusterProducer, const int clusterType)
{
   
   // get Ecal rechits
   if(verbosity_>1) cout << endl << "Loading egamma LazyTools..." << endl;
   const EcalRecHitCollection *reducedEBRecHits = 0;
   const EcalRecHitCollection *reducedEERecHits = 0;
   edm::Handle < EcalRecHitCollection > redEBRecHits;
   edm::Handle < EcalRecHitCollection > redEERecHits;
   try
   {
      iEvent.getByLabel(reducedBarrelEcalRecHitCollection_, redEBRecHits );
      reducedEBRecHits = redEBRecHits.product();
      iEvent.getByLabel(reducedEndcapEcalRecHitCollection_, redEERecHits ) ;
      reducedEERecHits = redEERecHits.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => reduced EcalRecHitCollections are missing #####" << endl;
         throw exception;
      }
      if(verbosity_>1) cout << endl << "   ===> No reduced EcalRecHitCollections, skip cluster rechits infos" << endl;
      doRecHits_ = false;
   }
   
   unsigned int nBasicClusters=0;
   
   edm::Handle<reco::BasicClusterCollection> basicClustersHandle;
   const reco::BasicClusterCollection *basicClusters = 0;
   try
   {
      iEvent.getByLabel(basicClusterProducer, basicClustersHandle);
      nBasicClusters = basicClustersHandle->size();
      basicClusters = basicClustersHandle.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => reco::BasicCluster collection is missing for Producer: " << basicClusterProducer << " #####" << endl;
         throw exception;
      }
      if(verbosity_>1) cout << endl << "   ===> No reco::BasicCluster collection for Producer: " << basicClusterProducer << " , skip basic clusters info" << endl;
      return false;
   }
   
   edm::ESHandle<EcalSeverityLevelAlgo> severityLevelAlgo;
   if (doRecHits_) iSetup.get<EcalSeverityLevelAlgoRcd>().get(severityLevelAlgo);
   
   // get the channel status from the DB
   //edm::ESHandle<EcalChannelStatus> chStatus;
   //iSetup.get<EcalChannelStatusRcd>().get(chStatus);
   //const EcalChannelStatus* channelStatus = 0;
   //if( chStatus.isValid() ) channelStatus = chStatus.product();
   
   if(verbosity_>1) cout << endl << "   Producer: " << basicClusterProducer << " - Number of BasicClusters (type " << clusterType << ") = " << nBasicClusters << std::endl;
   
   Int_t iClusType=0;
   
   for( reco::BasicClusterCollection::const_iterator  aClus = basicClusters->begin(); aClus != basicClusters->end(); aClus++)
   {
      TRootCluster localClus( aClus->energy(), aClus->eta(), aClus->phi(), aClus->x(), aClus->y(), aClus->z(), clusterType);
      localClus.setE2x2( lazyTools->e2x2(*aClus) );
      localClus.setE3x3( lazyTools->e3x3(*aClus) );
      localClus.setE5x5( lazyTools->e5x5(*aClus) );
      localClus.setEmax( lazyTools->eMax(*aClus) );
      localClus.setE2nd( lazyTools->e2nd(*aClus) );
      localClus.setS4( lazyTools->eLeft(*aClus) + lazyTools->eRight(*aClus) + lazyTools->eTop(*aClus) + lazyTools->eBottom(*aClus) );
      localClus.setNxtals( (aClus->hitsAndFractions()).size() );
      if ( (aClus->hitsAndFractions()).size()>0 ) localClus.setUid( (aClus->hitsAndFractions()).at(0).first() );
      
      if (doRecHits_)
      {
         
         std::vector<TRootEcalRecHit> hits;
         
         for(std::vector<std::pair<DetId,float> >::const_iterator detIdPair = (aClus->hitsAndFractions()).begin(); detIdPair != (aClus->hitsAndFractions()).end(); ++detIdPair)
         {
            DetId detId = detIdPair->first;
            if (detId.det() != DetId::Ecal)
            {
               if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => DetId=" << detId.det() << " is not ECAL #####" << endl;
               continue;
            }
            
            if (detId.subdetId() == EcalBarrel)
            {
               EcalRecHitCollection::const_iterator hit = reducedEBRecHits->find(detId);
               if (hit == reducedEBRecHits->end()) continue;
               EBDetId ebDet = (EBDetId)(detId);
               
               int iflag;
               for (iflag=EcalRecHit::kUnknown; ; --iflag)
               {
                  if ((*hit).checkFlag(iflag)) break;
                  if (iflag==0) break;
               }
               
               TRootEcalRecHit localHit(
                  detId.subdetId()
                  ,iflag
                  ,(*hit).energy()
                  ,(*hit).time()
                  ,ebDet.ieta()
                  ,ebDet.iphi()
                  ,(*hit).chi2()
                  ,(*hit).outOfTimeEnergy()
                  ,(*hit).outOfTimeChi2()
                  ,severityLevelAlgo->severityLevel(detId, *reducedEBRecHits)
               );
               hits.push_back(localHit);
            }
            else if (detId.subdetId() == EcalEndcap)
            {
               EcalRecHitCollection::const_iterator hit = reducedEERecHits->find(detId);
               if (hit == reducedEERecHits->end()) continue;
               EEDetId eeDet = (EEDetId)(detId);
               
               int iflag;
               for (iflag=EcalRecHit::kUnknown; ; --iflag)
               {
                  if ((*hit).checkFlag(iflag)) break;
                  if (iflag==0) break;
               }
               
               TRootEcalRecHit localHit(
               detId.subdetId()
               ,iflag
               ,(*hit).energy()
               ,(*hit).time()
               ,eeDet.ix()
               ,eeDet.iy()
               ,(*hit).chi2()
               ,(*hit).outOfTimeEnergy()
               ,(*hit).outOfTimeChi2()
               ,severityLevelAlgo->severityLevel(detId, *reducedEERecHits)
               );
               hits.push_back(localHit);
            }
            else
            {
               if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => SubDetId=" << detId.subdetId() << " is not EcalBarrel or EcalEndcap #####" << endl;
               continue;
            }
         }
         
         // FIXME - Implement ordering method in TRootEcalRecHit.h
         //std::sort(hits.begin(), hits.end());
         std::sort(hits.begin(), hits.end(), decrease);
         // if keepClusterizedEcalRecHits_=false, then keep only rechit associated to seed crystal
         if (! keepClusterizedEcalRecHits_ ) hits.resize(1);
         localClus.setHits(hits);
      }
      
      new( (*rootClusters)[iClus_] ) TRootCluster(localClus);
      if(verbosity_>3) cout << "   ["<< setw(3) << iClus_ << "] " << localClus << endl;
      
      iClus_++;
      iClusType++;
   }
   rootEvent->setNBasicClusters(clusterType,iClusType);
   return true;
}
