#ifndef ClusterAssociator_h
#define ClusterAssociator_h

#include <memory>
#include <string>
#include <iostream>
#include <map>
#include <cassert>

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "../interface/TRootCluster.h"
#include "../interface/TRootSuperCluster.h"

#include "TClonesArray.h"


class ClusterAssociator
{

   public:
      ClusterAssociator();
      ClusterAssociator(const edm::ParameterSet& config);
      ~ClusterAssociator();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      void process(TClonesArray* superClusters, TClonesArray* basicClusters);
      void printSuperClusters(TClonesArray* superClusters, TClonesArray* basicClusters, Int_t type);

   private:
      int verbosity_;
      bool doCracksCorrection_;

};

#endif
