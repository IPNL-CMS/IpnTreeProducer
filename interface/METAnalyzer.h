#ifndef METAnalyzer_h
#define METAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

//#include "DataFormats/METReco/interface/MET.h"
//#include "DataFormats/METReco/interface/METFwd.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "../interface/TRootEvent.h"
#include "../interface/TRootMET.h"

#include "TClonesArray.h"


class METAnalyzer
{

   public:
      METAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
      ~METAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      bool process(const edm::Event& iEvent, TClonesArray* rootMET);

   private:
      int verbosity_;
      std::string dataType_ ;
      edm::InputTag metProducer_;
      bool useMC_;
      bool allowMissingCollection_;

};

#endif
