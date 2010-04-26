#include "../interface/ClusterAssociator.h"

ClusterAssociator::ClusterAssociator():verbosity_(0)
{
}

ClusterAssociator::~ClusterAssociator()
{
}

void ClusterAssociator::process(TClonesArray* superClusters, TClonesArray* basicClusters)
{
   if(verbosity_>1) cout << endl << "Associating BasicClusters with SuperClusters... " << endl;
   
   std::map<Int_t, Int_t> bcMap; // map <BC uid , index of BC in TCloneArray>
   
   for (int ibc=0; ibc<basicClusters->GetEntriesFast(); ibc++)
   {
      bcMap[( (TRootCluster*)basicClusters->At(ibc))->uid()]=ibc;
      if(verbosity_>4) cout << "BC[" << ibc << "] uid=" << ( (TRootCluster*)basicClusters->At(ibc))->uid() << endl;
   }
   
   //for (std::map<Int_t, Int_t>::iterator it=bcMap.begin() ; it != bcMap.end(); it++ ) cout << "     " << (*it).first << " => " << (*it).second << endl;
   
   TRootCluster* aBC;
   TRootSuperCluster* aSC;
   
   for (int isc=0; isc<superClusters->GetEntriesFast(); isc++)
   {
      aSC = (TRootSuperCluster*) superClusters->At(isc);
      
      for (unsigned int isub=0; isub<aSC->subBasicClusterUIDVector().size(); isub++)
      {
         assert( bcMap.count(aSC->subBasicClusterUIDVector().at(isub)) != 0 );
         unsigned int iBasicCluster = (bcMap.find(aSC->subBasicClusterUIDVector().at(isub)))->second;
         if(verbosity_>4) cout << "SC[" << isc << "] uid(" << isub << ")=" << aSC->subBasicClusterUIDVector().at(isub) << " associated to BC[" << iBasicCluster << "]" << endl;
         aSC->addSubBasicClusterIndex( iBasicCluster );
         aSC->addSubBasicCluster( (TRootCluster*)basicClusters->At(iBasicCluster) );
         // TODO - Add ref to SC in BC
      }
      
      if ( aSC->seedBasicClusterIndex() >= 0 )
      {
         aBC = (TRootCluster*)basicClusters->At(aSC->seedBasicClusterIndex());
         aSC->setE3x3( aBC->e3x3() );
         aSC->setE5x5( aBC->e5x5() );
         aSC->setEmax( aBC->eMax() );
			aSC->setE2nd( aBC->e2nd() );
			aSC->setS4( aBC->s4() );
			aSC->setSeedBasicCluster( aBC );
			aSC->setHits( aBC->hits() );
			// TODO - Add ref to SC in seedBC
      }
      else
      {
         cout << "  ##### ERROR IN ClusterAssociator::process - No Seed Basic Cluster associated to the Supercluster #####" << endl;
      }
   }
   
   bcMap.clear();
}

void ClusterAssociator::printSuperClusters(TClonesArray* superClusters, TClonesArray* basicClusters, Int_t type)
{
   Int_t subIdx;
   for (int isc=0; isc<superClusters->GetEntriesFast(); isc++)
   {
      if ( type==0 || ((TRootSuperCluster*) superClusters->At(isc))->det()==type)
      {
         cout << "[" << isc << "] " << *( (TRootSuperCluster*) superClusters->At(isc) ) << endl;
         for (unsigned int isub=0; isub<((TRootSuperCluster*) superClusters->At(isc))->subBasicClusterIndexVector().size(); isub++)
         {
            subIdx=((TRootSuperCluster*) superClusters->At(isc))->subBasicClusterIndexVector().at(isub);
            cout << "        [" << subIdx << "] " << *( (TRootCluster*) basicClusters->At(subIdx) ) << endl;
         }
      }
   }
}
