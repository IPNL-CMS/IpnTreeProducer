#ifndef PhotonAssociator_h
#define PhotonAssociator_h

#include <memory>
#include <string>
#include <iostream>
#include <map>

#include "../interface/TRootPhoton.h"
#include "../interface/TRootSuperCluster.h"

#include "TClonesArray.h"


class PhotonAssociator
{

   public:
      PhotonAssociator();
      ~PhotonAssociator();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      void associateSuperCluster(TClonesArray* photons, TClonesArray* superClusters);
      void printPhotons(TClonesArray* photons, TClonesArray* superClusters,  Int_t type);
      void fullPrintPhotons(TClonesArray* photons, TClonesArray* superClusters, TClonesArray* basicClusters,  Int_t type);
      void fullPrintPhotonsAndRecHits(TClonesArray* photons, TClonesArray* superClusters, TClonesArray* basicClusters,  Int_t type);
      
   private:
      int verbosity_;

};

#endif
