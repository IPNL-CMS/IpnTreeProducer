#include "../interface/ClusterAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

ClusterAnalyzer::ClusterAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity), iClus_(0)
{
   dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}


ClusterAnalyzer::~ClusterAnalyzer()
{
}


bool ClusterAnalyzer::process(const edm::Event& iEvent, TRootEvent* rootEvent, EcalClusterLazyTools* lazyTools, TClonesArray* rootClusters, const string moduleLabel, const string instanceName, const int clusterType)
{
   
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
      localClus.setE3x3( lazyTools->e3x3(*aClus) );
      localClus.setE5x5( lazyTools->e5x5(*aClus) );
      localClus.setEmax( lazyTools->eMax(*aClus) );
      localClus.setE2nd( lazyTools->e2nd(*aClus) );
      localClus.setNxtals( (aClus->hitsAndFractions()).size() );
      if ( (aClus->hitsAndFractions()).size()>0 ) localClus.setUid( (aClus->hitsAndFractions()).at(0).first() );
      
      new( (*rootClusters)[iClus_] ) TRootCluster(localClus);
      if(verbosity_>3) cout << "   ["<< setw(3) << iClus_ << "] " << localClus << endl;
		//if(verbosity_>3) cout << "====> seed=" << aClus->seed() << " caloID=" << aClus->caloID() << "first hit ID=" << (aClus->hitsAndFractions()).at(0).first() << endl;
	  
      iClus_++;
      iClusType++;
   }
   rootEvent->setNBasicClusters(clusterType,iClusType);
   return true;
}
