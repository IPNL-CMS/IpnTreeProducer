#ifndef JetAnalyzer_h
#define JetAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"

#include "../interface/TRootJet.h"

#include "RecoJets/JetProducers/interface/JetIDHelper.h"

#include "TClonesArray.h"


class JetAnalyzer
{

   public:
		JetAnalyzer(const edm::InputTag& jetProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
      ~JetAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      bool process(const edm::Event& iEvent, TClonesArray* rootJets);
      //      reco::helper::JetIDHelper jetIDHelper;

   private:
      int verbosity_;
      std::string dataType_ ;
      edm::InputTag jetProducer_;
      edm::InputTag mcProducer_;
      //      edm::ParameterSet jetID_;
      bool useMC_;
      bool allowMissingCollection_;

};

#endif
