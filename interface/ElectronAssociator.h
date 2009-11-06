#ifndef ElectronAssociator_h
#define ElectronAssociator_h

#include <memory>
#include <string>
#include <iostream>
#include <map>

#include "../interface/TRootElectron.h"
#include "../interface/TRootSuperCluster.h"

#include "TClonesArray.h"


class ElectronAssociator
{

   public:
      ElectronAssociator();
      ~ElectronAssociator();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      void associateSuperCluster(TClonesArray* electrons, TClonesArray* superClusters);
      void printElectrons(TClonesArray* electrons, TClonesArray* superClusters,  Int_t type);
      void fullPrintElectrons(TClonesArray* electrons, TClonesArray* superClusters, TClonesArray* basicClusters,  Int_t type);

   private:
      int verbosity_;

};

#endif
