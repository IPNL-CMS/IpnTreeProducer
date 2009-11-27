#include "../interface/SuperClusterAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;


SuperClusterAnalyzer::SuperClusterAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity), iClus_(0)
{
   dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
   patEncapsulation_ = false;
   if( dataType_=="PAT" )
   {
      patEncapsulation_ = producersNames.getUntrackedParameter<bool>("patEncapsulation", false);
   }
}


SuperClusterAnalyzer::~SuperClusterAnalyzer()
{
}


bool SuperClusterAnalyzer::process(const edm::Event& iEvent, TRootEvent* rootEvent, TClonesArray* rootSuperClusters, const string moduleLabel, const string instanceName, const int clusterType)
{

   // TODO - Use supercluster encapsulated in pat::Photon if patEncapsulation_ = true
   
   unsigned int nSuperClusters=0;
   const reco::SuperClusterCollection *superClusters = 0;
   try
   {
      edm::Handle<reco::SuperClusterCollection> superClustersHandle;
      iEvent.getByLabel(moduleLabel, instanceName, superClustersHandle);
      superClusters = superClustersHandle.product();
      nSuperClusters = superClusters->size();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  SuperClusterAnalyzer::process => reco::SuperCluster collection is missing #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No reco::SuperCluster collection, skip superclusters info" << endl;
      return false;
   }
   
   if(verbosity_>1) cout << endl << "   Producer: " << moduleLabel << " : " << instanceName << " - Number of SuperClusters (type " << clusterType << ") = " << nSuperClusters << std::endl;
   
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
		unsigned int seedUID = 0;
      if ( (aSuperClus->hitsAndFractions()).size()>0 ) seedUID = (aSuperClus->hitsAndFractions()).at(0).first();
      
      int iSubCluster=0;
      for( reco::CaloCluster_iterator  aBasicClus = aSuperClus->clustersBegin(); aBasicClus != aSuperClus->clustersEnd(); aBasicClus++)
      {
			unsigned int basicClusterUID = 0;
         if ( (aBasicClus->get()->hitsAndFractions()).size()>0 ) basicClusterUID = (aBasicClus->get()->hitsAndFractions()).at(0).first();
         localClus.addSubBasicClusterUID( basicClusterUID );
         if ( basicClusterUID==seedUID ) localClus.setSeedBasicClusterVectorIndex(iSubCluster);
         iSubCluster++;
      }
      
      new( (*rootSuperClusters)[iClus_] ) TRootSuperCluster(localClus);
      if(verbosity_>3) cout << "   ["<< setw(3) << iClus_ << "] " << localClus << endl;
      
      iClus_++;
      iClusType++;
      
   }
   rootEvent->setNSuperClusters(clusterType,iClusType);
   return true;
}
