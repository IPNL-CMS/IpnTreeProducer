#include "../interface/ClusterAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

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


bool ClusterAnalyzer::process(const edm::Event& iEvent, TRootEvent* rootEvent, EcalClusterLazyTools* lazyTools, TClonesArray* rootClusters, const string moduleLabel, const string instanceName, const int clusterType)
{

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
      iEvent.getByLabel(moduleLabel, instanceName, basicClustersHandle);
      nBasicClusters = basicClustersHandle->size();
      basicClusters = basicClustersHandle.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => reco::BasicCluster collection is missing for Producer: " << moduleLabel << " : " << instanceName << " #####" << endl;
         throw exception;
      }
      if(verbosity_>1) cout << endl << "   ===> No reco::BasicCluster collection for Producer: " << moduleLabel << " : " << instanceName << " , skip basic clusters info" << endl;
      return false;
   }
   
   
   if(verbosity_>1) cout << endl << "   Producer: " << moduleLabel << " : " << instanceName << " - Number of BasicClusters (type " << clusterType << ") = " << nBasicClusters << std::endl;
   
   Int_t iClusType=0;
   
   for( reco::BasicClusterCollection::const_iterator  aClus = basicClusters->begin(); aClus != basicClusters->end(); aClus++)
   {
      TRootCluster localClus( aClus->energy(), aClus->eta(), aClus->phi(), aClus->x(), aClus->y(), aClus->z(), clusterType);
		localClus.setE2x2( lazyTools->e2x2(*aClus) );
		localClus.setE3x3( lazyTools->e3x3(*aClus) );
      localClus.setE5x5( lazyTools->e5x5(*aClus) );
      localClus.setEmax( lazyTools->eMax(*aClus) );
      localClus.setE2nd( lazyTools->e2nd(*aClus) );
      localClus.setNxtals( (aClus->hitsAndFractions()).size() );
		if ( (aClus->hitsAndFractions()).size()>0 ) localClus.setUid( (aClus->hitsAndFractions()).at(0).first() );

		if (doRecHits_)
		{
			
			std::vector<int> hitsDetector;
			std::vector<int> hitsFlag;
			std::vector<float> hitsEnergy;
			std::vector<float> hitsTime;
			std::vector<int> hitsPosition1;
			std::vector<int> hitsPosition2;
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
					hitsDetector.push_back(detId.subdetId());
					hitsFlag.push_back((*hit).recoFlag());
					hitsEnergy.push_back((*hit).energy());
					hitsTime.push_back((*hit).time());
					hitsPosition1.push_back(ebDet.ieta());
					hitsPosition2.push_back(ebDet.iphi());
					TRootEcalRecHit localHit(
						detId.subdetId()
						,(*hit).recoFlag()
						,(*hit).energy()
						,(*hit).time()
						,ebDet.ieta()
						,ebDet.iphi()
					);
					hits.push_back(localHit);					
				}
				else if (detId.subdetId() == EcalEndcap)
				{
					EcalRecHitCollection::const_iterator hit = reducedEERecHits->find(detId);
					if (hit == reducedEERecHits->end()) continue;
					EEDetId eeDet = (EEDetId)(detId);
					hitsDetector.push_back(detId.subdetId());
					hitsFlag.push_back((*hit).recoFlag());
					hitsEnergy.push_back((*hit).energy());
					hitsTime.push_back((*hit).time());
					hitsPosition1.push_back(eeDet.ix());
					hitsPosition2.push_back(eeDet.iy());
					TRootEcalRecHit localHit(
					detId.subdetId()
					,(*hit).recoFlag()
					,(*hit).energy()
					,(*hit).time()
					,eeDet.ix()
					,eeDet.iy()
					);
					hits.push_back(localHit);
				}
				else
				{
					if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => SubDetId=" << detId.subdetId() << " is not EcalBarrel or EcalEndcap #####" << endl;
					continue;
				}
			}
			
			//Sort rechits by energy using Lambda (BOOST Library)
			using boost::lambda::_1;
			using boost::lambda::_2;
			using boost::lambda::var;
			
			typedef boost::counting_iterator<int> index_iter;
			std::vector<int> iv(index_iter(0), index_iter(hitsEnergy.size()));
			std::sort(iv.begin(), iv.end(), var(hitsEnergy)[_1]>var(hitsEnergy)[_2] );
			
			std::vector<int> sortedHitsDetector;
			std::vector<int> sortedHitsFlag;
			std::vector<float> sortedHitsEnergy;
			std::vector<float> sortedHitsTime;
			std::vector<int> sortedHitsPosition1;
			std::vector<int> sortedHitsPosition2;
			std::vector<TRootEcalRecHit> sortedHits;
			for(std::vector<int>::const_iterator it = iv.begin(); it != iv.end(); ++it)
			{
				sortedHitsDetector.push_back( hitsDetector.at(*it));
				sortedHitsFlag.push_back( hitsFlag.at(*it));
				sortedHitsEnergy.push_back( hitsEnergy.at(*it));
				sortedHitsTime.push_back( hitsTime.at(*it));
				sortedHitsPosition1.push_back( hitsPosition1.at(*it));
				sortedHitsPosition2.push_back( hitsPosition2.at(*it));
				sortedHits.push_back( hits.at(*it));
				if (! keepClusterizedEcalRecHits_ ) break;
			}
			
			//for_each(hitsEnergy.begin(), hitsEnergy.end(), std::cout << "Before sort, hitsEnergy=(" << _1 << ","); cout << ")" << endl;
			//for_each(sortedHitsEnergy.begin(), sortedHitsEnergy.end(), std::cout << "After sort, sortedHitsEnergy=(" << _1 << ","); cout << ")" << endl;
			localClus.setHitsDetector(sortedHitsDetector);
			localClus.setHitsFlag(sortedHitsFlag);
			localClus.setHitsEnergy(sortedHitsEnergy);
			localClus.setHitsTime(sortedHitsTime);
			localClus.setHitsPosition1(sortedHitsPosition1);
			localClus.setHitsPosition2(sortedHitsPosition2);
			localClus.setHits(sortedHits);
			
		}
		
      new( (*rootClusters)[iClus_] ) TRootCluster(localClus);
      if(verbosity_>3) cout << "   ["<< setw(3) << iClus_ << "] " << localClus << endl;
	  
      iClus_++;
      iClusType++;
   }
   rootEvent->setNBasicClusters(clusterType,iClusType);
   return true;
}
