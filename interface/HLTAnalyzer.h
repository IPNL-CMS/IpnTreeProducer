#ifndef HLTAnalyzer_h
#define HLTAnalyzer_h

// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files
//#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"
//#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "../interface/TRootRun.h"
#include "../interface/TRootEvent.h"

#include <iomanip>


class HLTAnalyzer
{

   public:

      HLTAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
      ~HLTAnalyzer() {;}

      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      bool init(const edm::Event& iEvent, TRootEvent* rootEvent);
      bool process(const edm::Event& iEvent, TRootEvent* rootEvent);
      void printStats();
      void copySummary(TRootRun* runInfos);

      unsigned int  nHLTPaths() const { return hltNames_.size(); }

      unsigned int  nEvents() const { return nEvents_; }
      unsigned int  nWasRun() const { return nWasRun_; }
      unsigned int  nAccept() const { return nAccept_; }
      unsigned int  nErrors() const { return nErrors_; }

      std::vector<unsigned int> hltWasRun() const { return hltWasRun_; }
      std::vector<unsigned int> hltAccept() const { return hltAccept_; }
      std::vector<unsigned int> hltErrors() const { return hltErrors_; }
      std::vector<std::string>  hltNames() const { return hltNames_; }

      unsigned int hltWasRun(unsigned ipath) const { return (hltWasRun_.size()>ipath ?  hltWasRun_.at(ipath) : 0 ); }
      unsigned int hltAccept(unsigned ipath) const { return (hltAccept_.size()>ipath ?  hltAccept_.at(ipath) : 0 ); }
      unsigned int hltErrors(unsigned ipath) const { return (hltErrors_.size()>ipath ?  hltErrors_.at(ipath) : 0 ); }
      std::string hltNames(unsigned ipath) const { return (hltNames_.size()>ipath ?  hltNames_.at(ipath) : "noname" ); }

   private:

      int verbosity_;

      edm::InputTag triggerResultsTag_;      // Input tag for TriggerResults
      //edm::TriggerNames triggerNames_;       // TriggerNames class
      const edm::TriggerNames triggerNames_;       // TriggerNames class
      
      unsigned int  nEvents_;                // number of events processed
      unsigned int  nWasRun_;                // # where at least one HLT was run
      unsigned int  nAccept_;                // # of accepted events
      unsigned int  nErrors_;                // # where at least one HLT had error

      std::vector<unsigned int> hltWasRun_;  // # where HLT[i] was run
      std::vector<unsigned int> hltAccept_;  // # of events accepted by HLT[i]
      std::vector<unsigned int> hltErrors_;  // # of events with error in HLT[i]
      std::vector<std::string>  hltNames_;   // name of each HLT algorithm

      bool allowMissingCollection_;

};

#endif
