#ifndef ClusterAnalyzer_h
#define ClusterAnalyzer_h

// system include files
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "boost/lambda/lambda.hpp"
#include "boost/iterator/counting_iterator.hpp"

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

#include "../interface/TRootEvent.h"
#include "../interface/TRootCluster.h"

#include "TClonesArray.h"


class ClusterAnalyzer
{
   
   public:
		ClusterAnalyzer(const edm::ParameterSet& config, const edm::ParameterSet& producersNames, int verbosity);
      ~ClusterAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      bool process(const edm::Event& iEvent, TRootEvent* rootEvent, EcalClusterLazyTools* lazyTools,  TClonesArray* rootClusters, const string moduleLabel, const string instanceName, const int clusterType);
      
   private:
      int verbosity_;
      int iClus_;
		bool doRecHits_;
      std::string dataType_ ;
		edm::InputTag reducedBarrelEcalRecHitCollection_;
		edm::InputTag reducedEndcapEcalRecHitCollection_;
		bool keepClusterizedEcalRecHits_;
		bool allowMissingCollection_;
		
};

#endif
