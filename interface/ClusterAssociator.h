#ifndef ClusterAssociator_h
#define ClusterAssociator_h

#include <memory>
#include <string>
#include <iostream>
#include <map>

#include "../interface/TRootCluster.h"
#include "../interface/TRootSuperCluster.h"

#include "TClonesArray.h"


class ClusterAssociator
{

   public:
      ClusterAssociator();
      ~ClusterAssociator();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      void process(TClonesArray* superClusters, TClonesArray* basicClusters);
      void printSuperClusters(TClonesArray* superClusters, TClonesArray* basicClusters, Int_t type);

   private:
      int verbosity_;

};

#endif
