#include "../interface/PhotonAssociator.h"

PhotonAssociator::PhotonAssociator():verbosity_(0)
{
}

PhotonAssociator::~PhotonAssociator()
{
}

void PhotonAssociator::associateSuperCluster(TClonesArray* photons, TClonesArray* superClusters)
{
   
   TRootPhoton* localPhoton;
   TRootSuperCluster* localSuperCluster;
   if(verbosity_>1) cout << endl << "Associating SuperClusters with Photons... " << endl;
   
   Double_t energy5x5;
   multimap<Double_t,Int_t> scMap;
   multimap<Double_t,Int_t>::iterator it;
   pair<multimap<Double_t,Int_t>::iterator,multimap<Double_t,Int_t>::iterator> rangeIt;
   
   for (int isc=0; isc<superClusters->GetEntriesFast(); isc++)
   {
      energy5x5= ((TRootSuperCluster*) superClusters->At(isc))->e5x5();
      scMap.insert ( pair<Double_t,Int_t>(energy5x5,isc) );
   }
   
   for (int iphot=0; iphot<photons->GetEntriesFast(); iphot++)
   {
      localPhoton = (TRootPhoton*)photons->At(iphot);
      energy5x5= localPhoton->e5x5();
      rangeIt=scMap.equal_range(energy5x5);
      for (it=rangeIt.first; it!=rangeIt.second; ++it)
      {
         localSuperCluster = (TRootSuperCluster*) superClusters->At((*it).second);
         localPhoton->setSCIndex( localSuperCluster->type(), (*it).second );
         localPhoton->setSCRef( localSuperCluster->type(), localSuperCluster );
         localSuperCluster->setPhotonIndex( iphot );
         localSuperCluster->setPhoton( localPhoton );
      }
   }
   
   scMap.clear();
}



//TODO - methode AssociateConversionMC => matching entre TRootPhoton et TRootMCPhoton...
// Ajouter IndexMC a TRootPhoton et remplir TRootMCPhoton.recoPhotonIndex_



void PhotonAssociator::printPhotons(TClonesArray* photons, TClonesArray* superClusters, Int_t type)
{
   TRootPhoton* localPhoton;
   map<Int_t,Int_t>  idxMap;
   map<Int_t,Int_t>::iterator iter;
   
   cout << endl;
   for (int iphot=0; iphot<photons->GetEntriesFast(); iphot++)
   {
      localPhoton = (TRootPhoton*)photons->At(iphot);
      
      cout << "   [" << iphot << "] " << *localPhoton << endl;
      
      idxMap=localPhoton->scIndexMap();
      for( iter = idxMap.begin(); iter != idxMap.end(); iter++ )
      {
         if ( (type==0) || (iter->first==type) )
         {
            cout << "       [" << iter->second << "] " << *( (TRootSuperCluster*) superClusters->At(iter->second) ) << endl;
         }
      }
   }
}


void PhotonAssociator::fullPrintPhotons(TClonesArray* photons, TClonesArray* superClusters, TClonesArray* basicClusters, Int_t type)
{
   TRootPhoton* localPhoton;
   TRootSuperCluster* localSC;
   map<Int_t,Int_t>  idxMap;
   map<Int_t,Int_t>::iterator iter;
   Int_t subIdx;
   
   for (int iphot=0; iphot<photons->GetEntriesFast(); iphot++)
   {
      localPhoton = (TRootPhoton*)photons->At(iphot);
      
      cout << endl << "   [" << iphot << "] "; localPhoton->Print(); cout << endl;
      
      idxMap=localPhoton->scIndexMap();
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
