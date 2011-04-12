#include "../interface/HLTAnalyzer.h"

using namespace std;

HLTAnalyzer::HLTAnalyzer(const edm::ParameterSet& producersNames, int verbosity) :
verbosity_(verbosity)
,tableName_("noname")
,triggerNames_()
,nEvents_(0)
,nWasRun_(0)
,nAccept_(0)
,nErrors_(0)
,hltWasRun_(0)
,hltL1s_(0)
,hltPre_(0)
,hltAccept_(0)
,hltErrors_(0)
,hltNames_(0)
,posL1s_(0)
,posPre_(0)
,hltConfig_()
{
   dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
   triggerResultsTag_ = producersNames.getParameter<edm::InputTag> ("hltProducer");
   triggerEventsTag_ = producersNames.getParameter<edm::InputTag> ("hltEvent");
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
}


bool HLTAnalyzer::init(const edm::Run & iRun, const edm::EventSetup & iSetup)
{
   
   bool changed (true);
   
   if (hltConfig_.init(iRun,iSetup,triggerResultsTag_.process(),changed))
   {
      if (changed)
      {
         if(verbosity_>0)
         {
            const unsigned int nPaths(hltConfig_.size());
            
            cout << endl << "HLTAnalyzer-Init ---------------------------- HLT Menu ----------------------------------\n";
            cout << "HLTAnalyzer-Init Table name:  " << hltConfig_.tableName() << endl;
            cout << "HLTAnalyzer-Init" << endl;
            cout << "HLTAnalyzer-Init "
            << right << setw(5) << "Path#" << " "
            <<  left << setw(50) << "Name" << " "
            << right << setw(40) << "  ---------------- Prescales ---------------"
            << right << setw(10) << "L1Seed" << "\n";
            
            const std::vector<std::string> labels = hltConfig_.prescaleLabels();
            const unsigned int nPrescaleSets(labels.size());
            cout <<  left << setw(73) << "HLTAnalyzer-Init";
            
            for (unsigned int iset=0; iset!=nPrescaleSets; ++iset)
            {
               cout << right << setw(9) << labels.at(iset);
            }
            cout << endl;
            
            //const std::map<std::string,std::vector<unsigned int> >& hltPrescaleTable_ = hltConfig_.prescaleTable();
            const std::vector<std::vector<std::pair<bool,std::string> > >& hltL1GTSeeds_ = hltConfig_.hltL1GTSeeds();
            for (unsigned int ipath=0; ipath!=nPaths; ++ipath)
            {
               const std::string& name = hltConfig_.triggerNames().at(ipath);
               cout << "HLTAnalyzer-Init "
               << right << setw(5) << ipath << " "
               <<  left << setw(50) << name << " ";
               for (unsigned int iset=0; iset!=nPrescaleSets; ++iset)
               {
                  cout << right << setw(8) << hltConfig_.prescaleValue(iset,name) << " ";
               }
               if(verbosity_>4)
               {
                  for (unsigned int iseed=0; iseed!=hltL1GTSeeds_[ipath].size(); ++iseed)
                  {
                     if(iseed==0) cout << " Seed" << iseed;
                     else cout << endl << "HLTAnalyzer-Init " << right << setw(103) << " Seed" << iseed;
                     cout << " = "<< hltL1GTSeeds_[ipath][iseed].first
                     << "/" << hltL1GTSeeds_[ipath][iseed].second;
                  }
               }
               cout << endl;
            }
         }
         
         if(verbosity_>4)
         {
            const std::vector<std::string>& datasetNames_ = hltConfig_.datasetNames();
            const std::vector<std::vector<std::string> >& datasetContents_ = hltConfig_.datasetContents();
            const unsigned int nDatasets(datasetNames_.size());
            cout << endl << endl << "HLTAnalyzer-Init ------------------------- Datasets content ----------------------------------\n";
            for (unsigned int idataset=0; idataset!=nDatasets; ++idataset)
            {
               const unsigned int nElements(datasetContents_[idataset].size());
               cout << "  Dataset[" << idataset << "]  " << datasetNames_[idataset] << " " << nElements << endl;
               for (unsigned int iElement=0; iElement!=nElements; ++iElement)
               {
                  cout << "       " << iElement << " " << datasetContents_[idataset][iElement] << endl;
               }
            }
         }
         
         //hltConfig_.dump("TriggerSeeds");
         //hltConfig_.dump("Modules");
         //hltConfig_.dump("StreamNames");
         //hltConfig_.dump("Streams");
         //hltConfig_.dump("DatasetNames");
         //hltConfig_.dump("Datasets");
         //hltConfig_.dump("PrescaleTable");
         
         tableName_=hltConfig_.tableName();
         nEvents_=0;
         nWasRun_=0;
         nAccept_=0;
         nErrors_=0;
         // const edm::TriggerNames & triggerNames = iEvent.triggerNames(*HLTR);
         hltNames_=hltConfig_.triggerNames();
         const unsigned int n(hltNames_.size());
         hltWasRun_.resize(n);
         hltL1s_.resize(n);
         hltPre_.resize(n);
         hltAccept_.resize(n);
         hltErrors_.resize(n);
         posL1s_.resize(n);
         posPre_.resize(n);
         for (unsigned int i=0; i!=n; ++i) {
            hltWasRun_[i]=0;
            hltL1s_[i]=0;
            hltPre_[i]=0;
            hltAccept_[i]=0;
            hltErrors_[i]=0;
            posL1s_[i]=-1;
            posPre_[i]=-1;
            const std::vector<std::string>& moduleLabels(hltConfig_.moduleLabels(i));
            for (unsigned int j=0; j<moduleLabels.size(); ++j) {
               if (hltConfig_.moduleType(moduleLabels[j])=="HLTLevel1GTSeed") {
                  posL1s_[i]=j;
               }
               if (hltConfig_.moduleType(moduleLabels[j])=="HLTPrescaler"   ) {
                  posPre_[i]=j;
               }
            }
         }
      }
   }
   else
   {
      std::cout << "  ##### ERROR in  HLTAnalyzer::init => HLT menu not initialized #####" << std::endl;
      tableName_="not initialized";
      nEvents_=0;
      nWasRun_=0;
      nAccept_=0;
      nErrors_=0;
      hltWasRun_.clear();
      hltL1s_.clear();
      hltPre_.clear();
      hltAccept_.clear();
      hltErrors_.clear();
      posL1s_.clear();
      posPre_.clear();
      hltNames_.clear();
   }
   
   return true;
}


bool HLTAnalyzer::process(const edm::Event& iEvent, const edm::EventSetup & iSetup, TRootEvent* rootEvent)
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
         if (accept) nAccept_++;
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
         cout << "  ##### ERROR in HLTAnalyzer::process => No TriggerResults #####"<<endl;
         throw exception;
      }
      cout << "   HLT results not found!" << endl;;
      nErrors_++;
      return false;
   }
   
   // decision for each HLT algorithm
   //const unsigned int n(hltNames_.size());
   // FIXME - As a temporary fix, copy hlt path names in each rootEvent....
   const unsigned int n(trigResults->size());
   if(n != hltConfig_.size()) cout << "  ##### ERROR in HLTAnalyzer::process => edm::TriggerResults and HLTConfigProvider have different sizes #####" << endl;
   std::vector<std::string> hltAcceptNames;
   std::vector<Bool_t> hltDecision(n, false);
   std::vector<UInt_t> prescaleHLT(n, false);
   for (unsigned int i=0; i!=n; ++i)
   {
      prescaleHLT[i] = hltConfig_.prescaleValue(iEvent, iSetup, hltNames_.at(i));
      //if(verbosity_>4) cout << "   Trigger result for HLT path " << i << " = "<< (trigResults->accept(i)) << endl;
      if (trigResults->wasrun(i)) hltWasRun_[i]++;
      if (trigResults->error(i) ) hltErrors_[i]++;
      const int index(static_cast<int>(trigResults->index(i)));
      if (trigResults->accept(i))
      {
         hltAcceptNames.push_back(hltNames_.at(i));
         hltAccept_[i]++;
         hltDecision[i]=true;
         if (index>=posL1s_[i]) hltL1s_[i]++;
         if (index>=posPre_[i]) hltPre_[i]++;
      }
      else
      {
         if (index> posL1s_[i]) hltL1s_[i]++;
         if (index> posPre_[i]) hltPre_[i]++;
      }
   }
   
   rootEvent->setHltAcceptNames(hltAcceptNames);
   rootEvent->setTrigHLT(hltDecision);
   rootEvent->setPrescaleHLT(prescaleHLT);
   
   return true;
}


bool HLTAnalyzer::keepTriggerObjects(const edm::Event& iEvent, const edm::ParameterSet& producersNames, TClonesArray* rootHLTObjects)
{
   if( dataType_=="PAT" )
   {
      edm::Handle< pat::TriggerEvent > trigEvt;
      int nObject = 0;
      
      try
      {
         iEvent.getByLabel( triggerEventsTag_,trigEvt );
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "  ##### ERROR in HLTAnalyzer::keepTriggerObjects => No TriggerEvents #####"<<endl;
            throw exception;
         }
         cout << "   Pat HLT event not found!" << endl;
         return false;
      }
      
      /// get trigger path, ... from trigger event
      const pat::TriggerPathCollection * PatTrigPath = trigEvt->paths();
      
      if(verbosity_>4){cout<<"boucle sur les "<<PatTrigPath->size()<<" trigger path de l'evt"<<endl;}
      
      /// Loop over Trigger path
      for(unsigned int path_iter =0 ; path_iter<PatTrigPath->size() ; path_iter++)
      {
         if(verbosity_>4)
         {
            cout<<endl<<"path numero : "<<path_iter<<endl;
            cout<<"nom : "<<(PatTrigPath->at(path_iter)).name().data()<<endl;
         }
         
         /// Get trigger filter from a specific trigger path
         pat::TriggerFilterRefVector filter_ref = trigEvt->pathFilters((PatTrigPath->at(path_iter)).name().data());
         
         if(verbosity_>4){cout<<"Boucle sur les filter_ref"<<endl;}
         
         /// Loop over "filter_ref" sub-collection
         for(pat::TriggerFilterRefVectorIterator iFilter = filter_ref.begin() ; iFilter!=filter_ref.end() ; ++iFilter )
         {
            if(verbosity_>4){cout<<"filter : "<<(*iFilter)->label()<<endl;}
            
            /// Get trigger object from a specific trigger filter
            pat::TriggerObjectRefVector object_fil = trigEvt->filterObjects((*iFilter)->label());
            
            /// Loop over "object_fil" sub-sub-collection
            for(pat::TriggerObjectRefVectorIterator iObject=object_fil.begin() ; iObject!=object_fil.end() ; ++iObject)
            {
               if(verbosity_>4){cout<<"objet : "<<(*iObject)->collection().data()<<endl;}
               nObject++;
               TRootHLTObject trigger_obj("test_path","test_filter","test_algo",(*iObject)->px(),(*iObject)->py(),(*iObject)->pz(),(*iObject)->energy(),(*iObject)->vx(),(*iObject)->vy(),(*iObject)->vz(),(*iObject)->pdgId(),(*iObject)->charge());
               trigger_obj.setHLTPath((PatTrigPath->at(path_iter)).name().data());
               trigger_obj.setHLTFilter((*iFilter)->label().data());
               new( (*rootHLTObjects)[nObject-1] ) TRootHLTObject(trigger_obj);
            }
         }
      }
   }
   else if( dataType_=="RECO" ) {
        int nObject = 0;
	std::vector<std::string> filterList = producersNames.getParameter<std::vector<std::string> >("HLTfilterToSave");
	std::cout << "taille = " << filterList.size() << std::endl;
	edm::Handle<trigger::TriggerEvent> trEv;
	iEvent.getByLabel("hltTriggerSummaryAOD" ,trEv);
	const trigger::TriggerObjectCollection& TOCol(trEv->getObjects());
	trigger::Keys KEYS;
	string label;
	const trigger::size_type nFilt(trEv->sizeFilters());
	for (unsigned int i = 0 ; i < filterList.size() ; i ++){
		int pathFound = 0;
		for (trigger::size_type iFilt=0; iFilt!=nFilt; iFilt++){
			label = trEv->filterTag(iFilt).label();
		        if (label==filterList[i]){
				pathFound = 1;
	           		KEYS=trEv->filterKeys(iFilt);
				break;
		         }
		}
		if (pathFound == 0) continue;
		trigger::size_type nReg=KEYS.size();
		for (trigger::size_type iReg=0; iReg<nReg; iReg++){
			const trigger::TriggerObject& TObj(TOCol[KEYS[iReg]]);
               		nObject++;
//			cout << "on a trouve " << label << "px " << TObj.px() << " py " << TObj.py() << " pz " << TObj.pz() << endl;
               		TRootHLTObject trigger_obj("test_path","test_filter","test_algo",TObj.px(),TObj.py(),TObj.pz(),TObj.energy(),TObj.particle().vx(),TObj.particle().vy(),TObj.particle().vz(),TObj.particle().pdgId(),TObj.particle().charge());
               		trigger_obj.setHLTFilter(label);
               		new( (*rootHLTObjects)[nObject-1] ) TRootHLTObject(trigger_obj);
				
		}
	}
			


   }
   return true;
}


void HLTAnalyzer::printSummary()
{
   // final printout of accumulated statistics
   const unsigned int n(hltNames_.size());
   
   cout << dec << endl;
   cout << "HLTAnalyzer-Summary " << "---------- Event  Summary ------------\n";
   cout << "HLTAnalyzer-Summary Table name:  " << tableName_ << endl;
   cout << "HLTAnalyzer-Summary"
   << " Events total = " << nEvents_
   << " wasrun = " << nWasRun_
   << " passed = " << nAccept_
   << " errors = " << nErrors_
   << "\n";
   
   cout << endl;
   cout << "HLTAnalyzer-Summary " << "---------- HLTrig Summary ------------\n";
   cout << "HLTAnalyzer-Summary "
   << right << setw(7) << "HLT #" << " "
   << right << setw(7) << "WasRun" << " "
   << right << setw(7) << "L1S" << " "
   << right << setw(7) << "Pre" << " "
   << right << setw(7) << "HLT" << " "
   << right << setw(9) << "%L1sPre" << " "
   << right << setw(7) << "Errors" << " "
   << "Name" << endl;
   
   for (unsigned int i=0; i!=n; ++i)
   {
      cout << "HLTAnalyzer-Summary "
      << right << setw(7) << i << " "
      << right << setw(7) << hltWasRun_[i] << " "
      << right << setw(7) << hltL1s_[i] << " "
      << right << setw(7) << hltPre_[i] << " "
      << right << setw(7) << hltAccept_[i] << " "
      << right << setw(9) << fixed << setprecision(5)
      << static_cast<float>(100*hltAccept_[i])/static_cast<float>(max(hltPre_[i],1u)) << " "
      << right << setw(7) << hltErrors_[i] << " "
      << hltNames_[i] << endl;
   }
   
   cout << endl;
   cout << "HLTAnalyzer-Summary end!" << endl;
   cout << endl;
   
   return;
}

void HLTAnalyzer::copySummary(TRootRun* runInfos)
{
   if(verbosity_>4) cout << "   Copying HLT Summary table in TRootRun" << endl;
   
   runInfos->setHltTableName(tableName_) ;
   runInfos->setNHLTEvents(nEvents_) ;
   runInfos->setNHLTWasRun(nWasRun_) ;
   runInfos->setNHLTAccept(nAccept_) ;
   runInfos->setNHLTErrors(nErrors_) ;
   
   runInfos->setHLTWasRun(hltWasRun_) ;
   runInfos->setHLTAccept(hltAccept_) ;
   runInfos->setHLTL1s(hltL1s_) ;
   runInfos->setHLTPre(hltPre_) ;
   runInfos->setHLTErrors(hltErrors_) ;
   runInfos->setHLTNames(hltNames_) ;
   
}
