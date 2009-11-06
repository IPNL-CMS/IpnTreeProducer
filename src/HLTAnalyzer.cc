#include "../interface/HLTAnalyzer.h"

using namespace std;

HLTAnalyzer::HLTAnalyzer(const edm::ParameterSet& producersNames, int verbosity) :
verbosity_(verbosity)
,triggerNames_()
,nEvents_(0)
,nWasRun_(0)
,nAccept_(0)
,nErrors_(0)
,hltWasRun_(0)
,hltAccept_(0)
,hltErrors_(0)
,hltNames_(0)
{
   triggerResultsTag_ = producersNames.getParameter<edm::InputTag> ("hltProducer");
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}


bool HLTAnalyzer::init(const edm::Event& iEvent, TRootEvent* rootEvent)
{
   
   try
   {
      edm::Handle<edm::TriggerResults> trigResults;
      iEvent.getByLabel(triggerResultsTag_,trigResults);
      triggerNames_.init(*trigResults);
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  HLTAnalyzer::init => No TriggerResults #####"<<endl;
         throw exception;
      }
      return false;
   }
   
   hltNames_=triggerNames_.triggerNames();
   const unsigned int n(hltNames_.size());
   if(verbosity_>4) cout << "   Number of HLT paths = " << n << endl;
   hltWasRun_.resize(n);
   hltAccept_.resize(n);
   hltErrors_.resize(n);
   for (unsigned int i=0; i!=n; ++i)
   {
      if(verbosity_>4) cout << "   Name of HLT path " << i << ": " << hltNames_[i] << endl;
      hltWasRun_[i]=0;
      hltAccept_[i]=0;
      hltErrors_[i]=0;
   }
   
   return true;
}


bool HLTAnalyzer::process(const edm::Event& iEvent, TRootEvent* rootEvent)
{
   nEvents_++;
   edm::Handle<edm::TriggerResults> trigResults;
   try
   {
      iEvent.getByLabel(triggerResultsTag_,trigResults);
      if (trigResults.isValid()) {
         if (trigResults->wasrun()) nWasRun_++;
         const bool accept(trigResults->accept());
         if(verbosity_>1) cout << "   HLT decision: " << accept << endl;
         rootEvent->setGlobalHLT(accept);
         if (accept) ++nAccept_;
         if (trigResults->error() ) nErrors_++;
      }
      else
      {
         cout << "   HLT results not found!" << endl;;
         nErrors_++;
         return false;
      }
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  HLTAnalyzer::process => No TriggerResults #####"<<endl;
         throw exception;
      }
      cout << "   HLT results not found!" << endl;;
      nErrors_++;
      return false;
   }
   
   // decision for each HLT algorithm
   const unsigned int n(hltNames_.size());
   std::vector<Bool_t> hltDecision(n, false);
   for (unsigned int i=0; i!=n; ++i)
   {
      //if(verbosity_>4) cout << "   Trigger result for HLT path " << i << " = "<< (trigResults->accept(i)) << endl;
      if (trigResults->wasrun(i)) hltWasRun_[i]++;
      if (trigResults->error(i) ) hltErrors_[i]++;
      if (trigResults->accept(i))
      {
         hltAccept_[i]++;
         hltDecision[i]=true;
      }
   }
   
   rootEvent->setTrigHLT(hltDecision);
   
   return true;
}


void HLTAnalyzer::printStats()
{
   // final printout of accumulated statistics
   const unsigned int n(hltNames_.size());
   
   cout << dec << endl;
   cout << "HLTAnalyzer-Summary " << "---------- Event  Summary ------------\n";
   cout << "HLTAnalyzer-Summary"
   << " Events total = " << nEvents_
   << " wasrun = " << nWasRun_
   << " passed = " << nAccept_
   << " errors = " << nErrors_
   << "\n";
   
   cout << endl;
   cout << "HLTAnalyzer-Summary " << "---------- HLTrig Summary ------------\n";
   cout << "HLTAnalyzer-Summary "
   << right << setw(10) << "HLT  Bit#" << " "
   << right << setw(10) << "WasRun" << " "
   << right << setw(10) << "Passed" << " "
   << right << setw(10) << "Errors" << " "
   << "Name" << "\n";
   
   for (unsigned int i=0; i!=n; ++i)
   {
      cout << "HLTAnalyzer-Summary "
      << right << setw(10) << i << " "
      << right << setw(10) << hltWasRun_[i] << " "
      << right << setw(10) << hltAccept_[i] << " "
      << right << setw(10) << hltErrors_[i] << " "
      << hltNames_[i] << "\n";
   }
   
   cout << endl;
   cout << "HLTAnalyzer-Summary end!" << endl;
   cout << endl;
   
   return;
}

void HLTAnalyzer::copySummary(TRootRun* runInfos)
{
   if(verbosity_>4) cout << "   Copying HLT Summary table in TRootRun" << endl;
   
   runInfos->setNHLTEvents(nEvents_) ;
   runInfos->setNHLTWasRun(nWasRun_) ;
   runInfos->setNHLTAccept(nAccept_) ;
   runInfos->setNHLTErrors(nErrors_) ;
   
   runInfos->setHLTWasRun(hltWasRun_) ;
   runInfos->setHLTAccept(hltAccept_) ;
   runInfos->setHLTErrors(hltErrors_) ;
   runInfos->setHLTNames(hltNames_) ;
   
}
