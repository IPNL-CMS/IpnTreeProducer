#ifndef EcalRecHitsAnalyzer_h
#define EcalRecHitsAnalyzer_h

// system include files
#include <memory>
#include <string>
#include <iostream>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

#include "../interface/TRootEcalRecHit.h"

#include "TClonesArray.h"


class EcalRecHitsAnalyzer
{
   
   public:
		EcalRecHitsAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
      ~EcalRecHitsAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
		bool process(const edm::Event& iEvent, TClonesArray* rootEcalRecHits);
      
   private:
      int verbosity_;
		unsigned int iRecHit_;
		edm::InputTag barrelEcalRecHitCollection_;
		edm::InputTag endcapEcalRecHitCollection_;
		bool allowMissingCollection_;
		
};

#endif
