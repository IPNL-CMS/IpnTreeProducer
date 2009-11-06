#include "../interface/ElectronAssociator.h"

ElectronAssociator::ElectronAssociator():verbosity_(0)
{
}

ElectronAssociator::~ElectronAssociator()
{
}

void ElectronAssociator::associateSuperCluster(TClonesArray* electrons, TClonesArray* superClusters)
{
   
   TRootElectron* localElectron;
   TRootSuperCluster* localSuperCluster;
   if(verbosity_>1) cout << endl << "Associating SuperClusters with Electrons... " << endl;
   
   Double_t energy5x5;
   multimap<Double_t,Int_t> scMap;
   multimap<Double_t,Int_t>::iterator it;
   pair<multimap<Double_t,Int_t>::iterator,multimap<Double_t,Int_t>::iterator> rangeIt;
   
   for (int isc=0; isc<superClusters->GetEntriesFast(); isc++)
   {
      energy5x5= ((TRootSuperCluster*) superClusters->At(isc))->e5x5();
      scMap.insert ( pair<Double_t,Int_t>(energy5x5,isc) );
   }
   
   for (int iele=0; iele<electrons->GetEntriesFast(); iele++)
   {
      localElectron = (TRootElectron*)electrons->At(iele);
      energy5x5= localElectron->e5x5();
      rangeIt=scMap.equal_range(energy5x5);
      for (it=rangeIt.first; it!=rangeIt.second; ++it)
      {
         localSuperCluster = (TRootSuperCluster*) superClusters->At((*it).second);
         localElectron->setSCIndex( localSuperCluster->type(), (*it).second );
         localElectron->setSCRef( localSuperCluster->type(), localSuperCluster );
         localSuperCluster->setElectronIndex( iele );
         localSuperCluster->setElectron( localElectron );
      }
   }
   
   scMap.clear();
}


void ElectronAssociator::printElectrons(TClonesArray* electrons, TClonesArray* superClusters, Int_t type)
{
   TRootElectron* localElectron;
   map<Int_t,Int_t>  idxMap;
   map<Int_t,Int_t>::iterator iter;
   
   cout << endl;
   for (int iele=0; iele<electrons->GetEntriesFast(); iele++)
   {
      localElectron = (TRootElectron*)electrons->At(iele);
      
      cout << "   [" << iele << "] " << *localElectron << endl;
      
      idxMap=localElectron->scIndexMap();
      for( iter = idxMap.begin(); iter != idxMap.end(); iter++ )
      {
         if ( (type==0) || (iter->first==type) )
         {
            cout << "       [" << iter->second << "] " << *( (TRootSuperCluster*) superClusters->At(iter->second) ) << endl;
         }
      }
   }
}


void ElectronAssociator::fullPrintElectrons(TClonesArray* electrons, TClonesArray* superClusters, TClonesArray* basicClusters, Int_t type)
{
   TRootElectron* localElectron;
   TRootSuperCluster* localSC;
   map<Int_t,Int_t>  idxMap;
   map<Int_t,Int_t>::iterator iter;
   Int_t subIdx;
   
   for (int iele=0; iele<electrons->GetEntriesFast(); iele++)
   {
      localElectron = (TRootElectron*)electrons->At(iele);
      
      cout << endl << "   [" << iele << "] "; localElectron->Print(); cout << endl;
      
      idxMap=localElectron->scIndexMap();
      for( iter = idxMap.begin(); iter != idxMap.end(); iter++ )
      {
         if ( (type==0) || (iter->first==type) )
         {
            localSC =  (TRootSuperCluster*) superClusters->At(iter->second);
            cout << "       [" << iter->second << "] " << *localSC << endl;
            
            for (unsigned int isub=0; isub<localSC->subBasicClusterIndexVector().size(); isub++)
            {
               subIdx=localSC->subBasicClusterIndexVector().at(isub);
               cout << "           [" << subIdx << "] " << *( (TRootCluster*) basicClusters->At(subIdx) ) << endl;
            }
         }
      }
   }
}
