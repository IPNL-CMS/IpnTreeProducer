#ifndef SuperClusterAnalyzer_h
#define SuperClusterAnalyzer_h

// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"

#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/EcalAlgo/interface/EcalPreshowerGeometry.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "DataFormats/EgammaReco/interface/ClusterShape.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"

#include "../interface/TRootEvent.h"
#include "../interface/TRootSuperCluster.h"

#include "TClonesArray.h"


class SuperClusterAnalyzer
{

   public:
      SuperClusterAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
      ~SuperClusterAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
		bool process(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent, TClonesArray* rootSuperClusters, const string moduleLabel, const string instanceName, const int clusterType);
		float getESRatio(reco::CaloClusterPtr& seed, const edm::Event& iEvent, const edm::EventSetup& iSetup);
		
   private:
      int verbosity_;
      int iClus_;
      std::string dataType_ ;
      bool allowMissingCollection_;
      bool patEncapsulation_;

};

#endif
