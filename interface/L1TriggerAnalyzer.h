#ifndef L1TriggerAnalyzer_h
#define L1TriggerAnalyzer_h

// system include files
#include <memory>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/L1TObjects/interface/L1GtAlgorithm.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"

#include "CondFormats/L1TObjects/interface/L1GtPrescaleFactors.h"
#include "CondFormats/DataRecord/interface/L1GtPrescaleFactorsAlgoTrigRcd.h"
#include "CondFormats/DataRecord/interface/L1GtPrescaleFactorsTechTrigRcd.h"

#include "CondFormats/L1TObjects/interface/L1GtTriggerMask.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskAlgoTrigRcd.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskTechTrigRcd.h"

#include "CondFormats/DataRecord/interface/L1GtTriggerMaskVetoAlgoTrigRcd.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMaskVetoTechTrigRcd.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "FWCore/Framework/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "../interface/TRootRun.h"
#include "../interface/TRootEvent.h"


class L1TriggerAnalyzer
{

   public:

      L1TriggerAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
      ~L1TriggerAnalyzer() {;}

      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
		bool init(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent);
      bool process(const edm::Event& iEvent, TRootEvent* rootEvent);
      void printStats();
      void copySummary(TRootRun* runInfos);

		unsigned int nPhysicsL1Paths() const { return physicsL1Names_.size(); }
		unsigned int nTechnicalL1Paths() const { return technicalL1Names_.size(); }

      unsigned int nEvents() const { return nEvents_; }
		unsigned int nPhysicsL1Accept() const { return nPhysicsL1Accept_; }
		unsigned int nTechnicalL1Accept() const { return nTechnicalL1Accept_; }
		
		std::map<int,std::string> physicsL1Names() const { return physicsL1Names_; }
		std::map<int,int> physicsL1PrescaleFactors() const { return physicsL1PrescaleFactors_; }
		std::map<int,unsigned int> physicsL1Mask() const { return physicsL1Mask_; }
		std::map<int,unsigned int> physicsL1MaskVeto() const { return physicsL1MaskVeto_; }
		std::vector<unsigned int> physicsL1Pass() const { return physicsL1CumulatedPass_; };

		std::string physicsL1Names(unsigned ipath)
		{
			std::map<int,std::string>::iterator it=physicsL1Names_.find(ipath);
			return ( it==physicsL1Names_.end() ? "NOTFOUND" : (*it).second );
		}
		
		int physicsL1PrescaleFactors(unsigned ipath)
		{
			std::map<int,int>::iterator it=physicsL1PrescaleFactors_.find(ipath);
			return ( it==physicsL1PrescaleFactors_.end() ? -1 : (*it).second );
		}
		
		unsigned int physicsL1Mask(unsigned ipath)
		{
			std::map<int,unsigned int>::iterator it=physicsL1Mask_.find(ipath);
			return ( it==physicsL1Mask_.end() ? 999999 : (*it).second );
		}
		
		unsigned int physicsL1MaskVeto(unsigned ipath)
		{
			std::map<int,unsigned int>::iterator it=physicsL1MaskVeto_.find(ipath);
			return ( it==physicsL1MaskVeto_.end() ? 999999 : (*it).second );
		}
		
		unsigned int physicsL1Pass(unsigned ipath) const { return (physicsL1CumulatedPass_.size()>ipath ?  physicsL1CumulatedPass_.at(ipath) : 0 ); }
		
		
		std::map<int,std::string> technicalL1Names() const { return technicalL1Names_; }
		std::map<int,int> technicalL1PrescaleFactors() const { return technicalL1PrescaleFactors_; }
		std::map<int,unsigned int> technicalL1Mask() const { return technicalL1Mask_; }
		std::map<int,unsigned int> technicalL1MaskVeto() const { return technicalL1MaskVeto_; }
		std::vector<unsigned int> technicalL1Pass() const { return technicalL1CumulatedPass_; };
		
		std::string technicalL1Names(unsigned ipath)
		{
			std::map<int,std::string>::iterator it=technicalL1Names_.find(ipath);
			return ( it==technicalL1Names_.end() ? "NOTFOUND" : (*it).second );
		}
		
		int technicalL1PrescaleFactors(unsigned ipath)
		{
			std::map<int,int>::iterator it=technicalL1PrescaleFactors_.find(ipath);
			return ( it==technicalL1PrescaleFactors_.end() ? -1 : (*it).second );
		}
		
		unsigned int technicalL1Mask(unsigned ipath)
		{
			std::map<int,unsigned int>::iterator it=technicalL1Mask_.find(ipath);
			return ( it==technicalL1Mask_.end() ? 999999 : (*it).second );
		}
		
		unsigned int technicalL1MaskVeto(unsigned ipath)
		{
			std::map<int,unsigned int>::iterator it=technicalL1MaskVeto_.find(ipath);
			return ( it==technicalL1MaskVeto_.end() ? 999999 : (*it).second );
		}
		
		unsigned int technicalL1Pass(unsigned ipath) const { return (technicalL1CumulatedPass_.size()>ipath ?  technicalL1CumulatedPass_.at(ipath) : 0 ); }
		
		
	private:

      int verbosity_;

		//  L1 Info for the run
		unsigned int  nEvents_;                              // number of events processed
		unsigned int  nL1Accept_;                            // Number of events accepted by global L1
		std::map<int,std::string> physicsL1Names_;           // name of each physics L1 algorithm
		std::map<int,int> physicsL1PrescaleFactors_;         // Prescale factor for a given physics L1 path
		std::map<int,unsigned int> physicsL1Mask_;           // Mask status for a given physics L1 path
		std::map<int,unsigned int> physicsL1MaskVeto_;       // Veto status for a given physics L1 path
		unsigned int nPhysicsL1Accept_;                      // Number of events accepted by global physics L1
		std::vector<unsigned int> physicsL1CumulatedPass_;   // Number of events accepted for a given physics L1 path

		std::map<int,std::string> technicalL1Names_;         // name of each technical L1 algorithm
		std::map<int,int> technicalL1PrescaleFactors_;       // Prescale factor for a given L1 path
		std::map<int,unsigned int> technicalL1Mask_;         // Mask status for a given technical L1 path
		std::map<int,unsigned int> technicalL1MaskVeto_;     // Veto status for a given technical L1 path
		unsigned int nTechnicalL1Accept_;                    // Number of events accepted by global technical L1
		std::vector<unsigned int> technicalL1CumulatedPass_; // Number of events accepted for a given technical L1 path

		edm::InputTag l1Producer_;                           // Input tag for TriggerResults
		bool allowMissingCollection_;                        // continue or exit TotoAnalyzer if a collection is missing

};

#endif
