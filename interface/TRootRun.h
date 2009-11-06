#ifndef TRootRun_h
#define TRootRun_h

#include <string>
#include <iostream>
#include <vector>

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

      void setXsection(Double_t xsection) { xsection_=xsection; }
      void setDescription(std::string description) { description_=description; }
      void setNHLTEvents(unsigned int nHLTEvents) { nHLTEvents_=nHLTEvents; }
      void setNHLTWasRun(unsigned int nHLTWasRun) { nHLTWasRun_=nHLTWasRun; }
      void setNHLTAccept(unsigned int nHLTAccept) { nHLTAccept_=nHLTAccept; }
      void setNHLTErrors(unsigned int nHLTErrors) { nHLTErrors_=nHLTErrors; }

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
      std::string description_; // dataset description

      unsigned int nHLTEvents_; // Nb of events
      unsigned int nHLTWasRun_; // Nb of events where at least one HLT was run
      unsigned int nHLTAccept_; // Nb of accepted events
      unsigned int nHLTErrors_; // Nb of events where at least one HLT had error

      std::vector<unsigned int> hltWasRun_; // # where HLT[i] was run
      std::vector<unsigned int> hltAccept_; // # of events accepted by HLT[i]
      std::vector<unsigned int> hltErrors_; // # of events with error in HLT[i]
      std::vector<std::string>  hltNames_;  // name of each HLT algorithm

      ClassDef (TRootRun,2);

};

#endif
