#ifndef TRootRun_h
#define TRootRun_h

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

#include "Rtypes.h"
#include "TObject.h"
#include "TVector3.h"

using namespace std;

class TRootRun : public TObject
{

   public:

      TRootRun() :
      xsection_(-1.)
      ,description_("MVCM")
		,nL1Events_(0)
		,nL1Accept_(0)
		,nPhysicsL1Accept_(0)
		,nTechnicalL1Accept_(0)
		,physicsL1Names_()
		,physicsL1PrescaleFactors_()
		,physicsL1Mask_()
		,physicsL1MaskVeto_()
		,physicsL1CumulatedPass_(0)
		,technicalL1Names_()
		,technicalL1PrescaleFactors_()
		,technicalL1Mask_()
		,technicalL1MaskVeto_()
		,technicalL1CumulatedPass_(0)
		,nHLTEvents_(0)
      ,nHLTWasRun_(0)
      ,nHLTAccept_(0)
      ,nHLTErrors_(0)
      ,hltWasRun_(0)
      ,hltAccept_(0)
      ,hltErrors_(0)
      ,hltNames_(0)
      {;}

      ~TRootRun() {;}

      Double_t xsection() const { return xsection_; }
      std::string description() const { return description_; }
		
		unsigned int nPhysicsL1Paths() const { return physicsL1Names_.size(); }
		unsigned int nTechnicalL1Paths() const { return technicalL1Names_.size(); }
		
		unsigned int nL1Events() const { return nL1Events_; }
		unsigned int nL1Accept() const { return nL1Accept_; }
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
		
		
      unsigned int  nHLTPaths() const { return hltNames_.size(); }
      unsigned int  nHLTEvents() const { return nHLTEvents_; }
      unsigned int  nHLTWasRun() const { return nHLTWasRun_; }
      unsigned int  nHLTAccept() const { return nHLTAccept_; }
      unsigned int  nHLTErrors() const { return nHLTErrors_; }

      std::vector<unsigned int> hltWasRun() const { return hltWasRun_; }
      std::vector<unsigned int> hltAccept() const { return hltAccept_; }
      std::vector<unsigned int> hltErrors() const { return hltErrors_; }
      std::vector<std::string>  hltNames() const { return hltNames_; }

      unsigned int hltWasRun(unsigned ipath) const { return (hltWasRun_.size()>ipath ?  hltWasRun_.at(ipath) : 0 ); }
      unsigned int hltAccept(unsigned ipath) const { return (hltAccept_.size()>ipath ?  hltAccept_.at(ipath) : 0 ); }
      unsigned int hltErrors(unsigned ipath) const { return (hltErrors_.size()>ipath ?  hltErrors_.at(ipath) : 0 ); }
      std::string hltNames(unsigned ipath) const { return (hltNames_.size()>ipath ?  hltNames_.at(ipath) : "noname" ); }
		
		void printL1Summary();
		void printHLTSummary();
		
		
      void setXsection(Double_t xsection) { xsection_ = xsection; }
      void setDescription(std::string description) { description_ = description; }
		
		void setNL1Events(unsigned int nL1Events) { nL1Events_ = nL1Events; }
		void setNL1Accept(unsigned int nL1Accept) { nL1Accept_ = nL1Accept; }
		void setNPhysicsL1Accept(unsigned int nPhysicsL1Accept) { nPhysicsL1Accept_ = nPhysicsL1Accept; }
		void setNTechnicalL1Accept(unsigned int nTechnicalL1Accept) { nTechnicalL1Accept_ = nTechnicalL1Accept; }
		
		void setPhysicsL1Names(std::map<int,std::string> physicsL1Names) { physicsL1Names_ = physicsL1Names; }
		void setPhysicsL1PrescaleFactors(std::map<int,int> physicsL1PrescaleFactors) { physicsL1PrescaleFactors_ = physicsL1PrescaleFactors; }
		void setPhysicsL1Mask(std::map<int,unsigned int> physicsL1Mask) { physicsL1Mask_ = physicsL1Mask; }
		void setPhysicsL1MaskVeto(std::map<int,unsigned int> physicsL1MaskVeto) { physicsL1MaskVeto_ = physicsL1MaskVeto; }
		void setPhysicsL1CumulatedPass(std::vector<unsigned int> physicsL1CumulatedPass) { physicsL1CumulatedPass_ = physicsL1CumulatedPass; }
		
		void setTechnicalL1Names(std::map<int,std::string> technicalL1Names) { technicalL1Names_ = technicalL1Names; }
		void setTechnicalL1PrescaleFactors(std::map<int,int> technicalL1PrescaleFactors) { technicalL1PrescaleFactors_ = technicalL1PrescaleFactors; }
		void setTechnicalL1Mask(std::map<int,unsigned int> technicalL1Mask) { technicalL1Mask_ = technicalL1Mask; }
		void setTechnicalL1MaskVeto(std::map<int,unsigned int> technicalL1MaskVeto) { technicalL1MaskVeto_ = technicalL1MaskVeto; }
		void setTechnicalL1CumulatedPass(std::vector<unsigned int> technicalL1CumulatedPass) { technicalL1CumulatedPass_ = technicalL1CumulatedPass; }
		
		void setNHLTEvents(unsigned int nHLTEvents) { nHLTEvents_ = nHLTEvents; }
		void setNHLTWasRun(unsigned int nHLTWasRun) { nHLTWasRun_ = nHLTWasRun; }
		void setNHLTAccept(unsigned int nHLTAccept) { nHLTAccept_ = nHLTAccept; }
		void setNHLTErrors(unsigned int nHLTErrors) { nHLTErrors_ = nHLTErrors; }
		
		void setHLTWasRun(std::vector<unsigned int> hltWasRun)
      {
         hltWasRun_.resize(hltWasRun.size());
         hltWasRun_=hltWasRun;
      }

      void setHLTAccept(std::vector<unsigned int> hltAccept)
      {
         hltAccept_.resize(hltAccept.size());
         hltAccept_=hltAccept;
      }

      void setHLTErrors(std::vector<unsigned int> hltErrors)
      {
         hltErrors_.resize(hltErrors.size());
         hltErrors_=hltErrors;
      }

      void setHLTNames(std::vector<std::string> hltNames)
      {
         hltNames_.resize(hltNames.size());
         hltNames_=hltNames;
      }


   private:

      Double_t xsection_;        // dataset cross-section
      std::string description_;  // dataset description
		
		unsigned int nL1Events_;                             // number of events processed by L1
		unsigned int nL1Accept_;                             // Number of events accepted by global L1
		unsigned int nPhysicsL1Accept_;                      // Number of events accepted by global physics L1
		unsigned int nTechnicalL1Accept_;                    // Number of events accepted by global technical L1
		
		std::map<int,std::string> physicsL1Names_;           // name of each physics L1 algorithm
		std::map<int,int> physicsL1PrescaleFactors_;         // Prescale factor for a given physics L1 path
		std::map<int,unsigned int> physicsL1Mask_;           // Mask status for a given physics L1 path
		std::map<int,unsigned int> physicsL1MaskVeto_;       // Veto status for a given physics L1 path
		std::vector<unsigned int> physicsL1CumulatedPass_;   // Number of events accepted for a given physics L1 path
		
		std::map<int,std::string> technicalL1Names_;         // name of each technical L1 algorithm
		std::map<int,int> technicalL1PrescaleFactors_;       // Prescale factor for a given L1 path
		std::map<int,unsigned int> technicalL1Mask_;         // Mask status for a given technical L1 path
		std::map<int,unsigned int> technicalL1MaskVeto_;     // Veto status for a given technical L1 path
		std::vector<unsigned int> technicalL1CumulatedPass_; // Number of events accepted for a given technical L1 path
		
		unsigned int nHLTEvents_; // Nb of events
      unsigned int nHLTWasRun_; // Nb of events where at least one HLT was run
      unsigned int nHLTAccept_; // Nb of accepted events
      unsigned int nHLTErrors_; // Nb of events where at least one HLT had error

      std::vector<unsigned int> hltWasRun_; // # where HLT[i] was run
      std::vector<unsigned int> hltAccept_; // # of events accepted by HLT[i]
      std::vector<unsigned int> hltErrors_; // # of events with error in HLT[i]
      std::vector<std::string>  hltNames_;  // name of each HLT algorithm

      ClassDef (TRootRun,3);

};

#endif
