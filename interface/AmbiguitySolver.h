#ifndef AmbiguitySolver_h
#define AmbiguitySolver_h

#include <memory>
#include <string>
#include <iostream>

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "../interface/TRootElectron.h"
#include "../interface/TRootPhoton.h"
#include "../interface/TRootSuperCluster.h"

#include "TClonesArray.h"


class AmbiguitySolver
{
   
   public:
      AmbiguitySolver(const edm::ParameterSet& config, int verbosity);
      ~AmbiguitySolver();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      void processElectronsPhotons(TClonesArray* superClusters, TClonesArray* electrons, TClonesArray* photons);
      
   private:
      int verbosity_;
      //bool doPhotonMC_;
      
};

#endif
