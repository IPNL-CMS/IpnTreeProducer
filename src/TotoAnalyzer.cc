#include "../interface/TotoAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

typedef std::vector<edm::InputTag> vtag;
typedef std::vector<int> vint32;

TotoAnalyzer::TotoAnalyzer(const edm::ParameterSet& iConfig)
{
   startTime_ = time(0);
   time_t t = time(0);
   char ts[] = "dd-Mon-yyyy hh:mm:ss TZN     ";
   strftime(ts, strlen(ts) + 1, "%d-%b-%Y %H:%M:%S %Z", localtime(&t));
   std::cout << std::endl << "START TOTOANALYZER AT " << ts << std::endl << std::endl;
   
   myConfig_ = iConfig.getParameter<ParameterSet>("myConfig");
   std::cout << "myConfig parameters:" << std::endl << "===================" << std::endl << std::endl << myConfig_ << std::endl;
   dataType_ = myConfig_.getUntrackedParameter<string>("dataType","unknown");
   if( dataType_=="RECO" )          producersNames_ = iConfig.getParameter<ParameterSet>("producersNamesRECO");
   else if( dataType_=="PAT" )         producersNames_ = iConfig.getParameter<ParameterSet>("producersNamesPAT");
   else { std::cout << "TotoAnalyzer::TotoAnalyzer...   dataType is unknown...  exiting..." << std::endl; exit(1); }
   std::cout << std::endl << "Producers used:" << std::endl << "==============" << std::endl << std::endl << producersNames_ << std::endl;
   
   rootRun_ = 0;
   rootEvent_ = 0;
   l1TriggerAnalyzer_ = 0;
   hltAnalyzer_ = 0;
   rootHLTObjects_ = 0;
   rootMCParticles_ = 0;
   rootGenJets_ = 0;
   rootGenMETs_ = 0;
   rootMuMuGammaEvent_ = 0;
   rootMCTopTop_ = 0;
   rootMCPhotons_ = 0;
   rootBeamSpot_ = 0;
   rootVertices_ = 0;
   rootZeeVertices_ = 0;
   rootTracks_ = 0;
   nJetsArrays_ = 0;
   nMuonsArrays_ = 0;
   nElectronsArrays_ = 0;
   nTausArrays_ = 0;
   nPhotonsArrays_ = 0;
   rootBasicClusters_ = 0;
   rootSuperClusters_ = 0;
   rootEcalRecHits_ = 0;
   rootConversionTracks_ = 0;
   nMETsArrays_ = 0;
   rootBardak_ = 0;
}


TotoAnalyzer::~TotoAnalyzer()
{
   time_t endTime = time(0);
   char ts[] = "dd-Mon-yyyy hh:mm:ss TZN     ";
   strftime(ts, strlen(ts) + 1, "%d-%b-%Y %H:%M:%S %Z", localtime(&endTime));
   std::cout << std::endl << std::endl << "END TOTOANALYZER AT " << ts << std::endl;
   if (nTotEvt_>0) std::cout << "===> " << float(endTime-startTime_)/float(nTotEvt_) << " s/evt" << std::endl;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Method called at the start of TotoAna Job
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TotoAnalyzer::beginJob()
{
   // Load Config parameters
   verbosity_ = myConfig_.getUntrackedParameter<int>("verbosity", 0);
   allowMissingCollection_ = producersNames_.getUntrackedParameter<bool>("allowMissingCollection", false);
   rootFileName_ = myConfig_.getUntrackedParameter<string>("RootFileName","noname.root");
   datasetXsection_ = myConfig_.getUntrackedParameter<double>("xsection");
   datasetDesciption_ = myConfig_.getUntrackedParameter<string>("description","Pas de description");
   doLHCInfo_ = myConfig_.getUntrackedParameter<bool>("doLHCInfo",false);
   doL1_ = myConfig_.getUntrackedParameter<bool>("doL1",false);
   doHLT_ = myConfig_.getUntrackedParameter<bool>("doHLT",false);
   doHLTObject_ = myConfig_.getUntrackedParameter<bool>("doHLTObject",false);
   doMC_ = myConfig_.getUntrackedParameter<bool>("doMC",false);
   doJetMC_ = myConfig_.getUntrackedParameter<bool>("doJetMC",false);
   doMETMC_ = myConfig_.getUntrackedParameter<bool>("doMETMC",false);
   doPDFInfo_ = myConfig_.getUntrackedParameter<bool>("doPDFInfo",false);
   doSignalMuMuGamma_ = myConfig_.getUntrackedParameter<bool>("doSignalMuMuGamma",false);
   doSignalTopTop_ = myConfig_.getUntrackedParameter<bool>("doSignalTopTop",false);
   doPhotonConversionMC_ = myConfig_.getUntrackedParameter<bool>("doPhotonConversionMC",false);
   doElectronsMCTruth_ = myConfig_.getUntrackedParameter<bool>("doElectronMCTruth",false);
   drawMCTree_ = myConfig_.getUntrackedParameter<bool>("drawMCTree",false);
   doBeamSpot_ = myConfig_.getUntrackedParameter<bool>("doBeamSpot",false);
   doPrimaryVertex_ = myConfig_.getUntrackedParameter<bool>("doPrimaryVertex",false);
   doZeePrimaryVertex_ = myConfig_.getUntrackedParameter<bool>("doZeePrimaryVertex",false);
   doTrack_ = myConfig_.getUntrackedParameter<bool>("doTrack",false);
   doJet_ = myConfig_.getUntrackedParameter<bool>("doJet",false);
   doMuon_ = myConfig_.getUntrackedParameter<bool>("doMuon",false);
   doElectron_ = myConfig_.getUntrackedParameter<bool>("doElectron",false);
   doTau_ = myConfig_.getUntrackedParameter<bool>("doTau",false);
   doPhoton_ = myConfig_.getUntrackedParameter<bool>("doPhoton",false);
   doPhotonEnergyRegression_ = myConfig_.getUntrackedParameter<bool>("doPhotonEnergyRegression",false);
   photonEnergyRegressionFileV3_ = myConfig_.getUntrackedParameter<string>("photonEnergyRegressionFileV3","");
   photonEnergyRegressionFileV4_ = myConfig_.getUntrackedParameter<string>("photonEnergyRegressionFileV4","");
   photonEnergyRegressionFileV5_ = myConfig_.getUntrackedParameter<string>("photonEnergyRegressionFileV5","");
   photonEnergyRegressionFileV8_ = myConfig_.getUntrackedParameter<string>("photonEnergyRegressionFileV8","");
   doCluster_ = myConfig_.getUntrackedParameter<bool>("doCluster",false);
   keepAllEcalRecHits_ = myConfig_.getUntrackedParameter<bool>("keepAllEcalRecHits",false);
   keepClusterizedEcalRecHits_ = myConfig_.getUntrackedParameter<bool>("keepClusterizedEcalRecHits",false);
   doPhotonConversion_ = myConfig_.getUntrackedParameter<bool>("doPhotonConversion",false);
   doPhotonIsolation_ = myConfig_.getUntrackedParameter<bool>("doPhotonIsolation",false);
   doMET_ = myConfig_.getUntrackedParameter<bool>("doMET",false);
   doBardak_ = myConfig_.getUntrackedParameter<bool>("doBardak",false);
   doRho_ = myConfig_.getUntrackedParameter<bool>("doRho",false);
   
   nTotEvt_ = 0;
   
   // initialize root output file
   if(verbosity_>0) std::cout << "New RootFile " << rootFileName_.c_str() << " is created" << std::endl;
   rootFile_ = new TFile(rootFileName_.c_str(), "recreate");
   rootFile_->cd();
   
   rootRun_ = NULL;
   runTree_ = new TTree("runTree", "Global Run Infos");
   runTree_->Branch ("runInfos", "TRootRun", &rootRun_);
   
   beamStatus_ = NULL;
   
   rootEvent_ = NULL;
   eventTree_ = new TTree("eventTree", "Event Infos");
   eventTree_->Branch ("Event", "TRootEvent", &rootEvent_);
   
   if(doL1_)
   {
      l1TriggerAnalyzer_ = new L1TriggerAnalyzer(producersNames_, verbosity_);
   }
   
   if(doHLT_)
   {
      hltAnalyzer_ = new HLTAnalyzer(producersNames_, verbosity_);
      if(doHLTObject_)
      {
         if(verbosity_>0) std::cout << "HLT objects will be added to rootuple" << std::endl;
         rootHLTObjects_ = new TClonesArray("TRootHLTObject", 1000);
         eventTree_->Branch ("HLTObjects", "TClonesArray", &rootHLTObjects_);
      }
   }
   
   if(doMC_)
   {
      if(verbosity_>0) std::cout << "MC Particles info will be added to rootuple" << std::endl;
      rootMCParticles_ = new TClonesArray("TRootMCParticle", 1000);
      eventTree_->Branch ("MCParticles", "TClonesArray", &rootMCParticles_);
   }
   
   if(doJetMC_)
   {
      if(verbosity_>0) std::cout << "genJets info will be added to rootuple" << std::endl;
      rootGenJets_ = new TClonesArray("TRootParticle", 1000);
      eventTree_->Branch ("genJets", "TClonesArray", &rootGenJets_);
   }
   
   if(doMETMC_)
   {
      if(verbosity_>0) std::cout << "genMETs info will be added to rootuple" << std::endl;
      rootGenMETs_ = new TClonesArray("TRootParticle", 1000);
      eventTree_->Branch ("genMETs", "TClonesArray", &rootGenMETs_);
   }
   
   if(doSignalMuMuGamma_)
   {
      if(verbosity_>0) std::cout << "MC info for Z -> mu mu gamma  will be added to rootuple" << std::endl;
      eventTree_->Branch ("MuMuGamma", "TRootSignalEvent", &rootMuMuGammaEvent_);
   }
   
   if(doSignalTopTop_)
   {
      if(verbosity_>0) std::cout << "MC info for Top Top will be added to rootuple" << std::endl;
      rootMCTopTop_ = new TClonesArray("TRootTopTop", 1000);
      eventTree_->Branch ("rootMCTopTop", "TClonesArray", &rootMCTopTop_);
   }
   
   if(doPhotonConversionMC_)
   {
      if(verbosity_>0) std::cout << "Converted MC Photons info will be added to rootuple" << std::endl;
      rootMCPhotons_ = new TClonesArray("TRootMCPhoton", 1000);
      eventTree_->Branch ("MCPhotons", "TClonesArray", &rootMCPhotons_);
   }
   
   if (doElectronsMCTruth_)
   {
      if(verbosity_>0) std::cout << "MC truth info for electron for electrons will be added to rootupe" << std::endl;
      rootMCElectrons_ = new TClonesArray("TRootMCElectron", 1000);
      eventTree_->Branch ("MCElectrons","TClonesArray", &rootMCElectrons_);
   }
   
   if(doBeamSpot_)
   {
      if(verbosity_>0) std::cout << "BeamSpot info will be added to rootuple" << std::endl;
      rootBeamSpot_ = new TRootBeamSpot();
      eventTree_->Branch ("BeamSpot", "TRootBeamSpot", &rootBeamSpot_);
   }
   
   if(doPrimaryVertex_)
   {
      if(verbosity_>0) std::cout << "Vertices info will be added to rootuple" << std::endl;
      rootVertices_ = new TClonesArray("TRootVertex", 1000);
      eventTree_->Branch ("Vertices", "TClonesArray", &rootVertices_);
   }
   
   if(doZeePrimaryVertex_)
   {
      if(verbosity_>0) std::cout << "Zee Primary Vertices info will be added to rootuple" << std::endl;
      rootZeeVertices_ = new TClonesArray("TRootVertex", 1000);
      eventTree_->Branch ("ZeeVertices", "TClonesArray", &rootZeeVertices_);
   }
   
   if(doTrack_)
   {
      if(verbosity_>0) std::cout << "Tracks info will be added to rootuple" << std::endl;
      rootTracks_ = new TClonesArray("TRootTrack", 1000);
      eventTree_->Branch ("Tracks", "TClonesArray", &rootTracks_);
   }
   
   if(doJet_)
   {
      if(verbosity_>0) std::cout << "Jets info will be added to rootuple" << std::endl;
      vtag jetProducers = producersNames_.getParameter<vtag>("jetProducer");
      nJetsArrays_ = jetProducers.size();
      rootJetsArrays_ = new TClonesArray*[nJetsArrays_];
      for(unsigned int i=0; i<nJetsArrays_; ++i)
      {
         edm::InputTag jetProducer = jetProducers.at(i);
         rootJetsArrays_[i] = new TClonesArray("TRootJet", 1000);
         eventTree_->Branch (jetProducer.label().data(), "TClonesArray", &(rootJetsArrays_[i]));
      }
   }
   
   if(doMuon_)
   {
      if(verbosity_>0) std::cout << "Muons info will be added to rootuple" << std::endl;
      vtag muonProducers = producersNames_.getParameter<vtag>("muonProducer");
      nMuonsArrays_ = muonProducers.size();
      rootMuonsArrays_ = new TClonesArray*[nMuonsArrays_];
      for(unsigned int i=0; i<nMuonsArrays_; ++i)
      {
         edm::InputTag muonProducer = muonProducers.at(i);
         rootMuonsArrays_[i] = new TClonesArray("TRootMuon", 1000);
         eventTree_->Branch (muonProducer.label().data(), "TClonesArray", &(rootMuonsArrays_[i]));
      }
   }
   
   if(doElectron_)
   {
      if(verbosity_>0) std::cout << "Electrons info will be added to rootuple" << std::endl;
      vtag electronProducers = producersNames_.getParameter<vtag>("electronProducer");
      nElectronsArrays_ = electronProducers.size();
      rootElectronsArrays_ = new TClonesArray*[nElectronsArrays_];
      for(unsigned int i=0; i<nElectronsArrays_; ++i)
      {
         edm::InputTag electronProducer = electronProducers.at(i);
         rootElectronsArrays_[i] = new TClonesArray("TRootElectron", 1000);
         eventTree_->Branch (electronProducer.label().data(), "TClonesArray", &(rootElectronsArrays_[i]));
      }
   }
   
   if(doTau_)
   {
      if(verbosity_>0) std::cout << "Taus info will be added to rootuple" << std::endl;
      vtag tauProducers = producersNames_.getParameter<vtag>("tauProducer");
      nTausArrays_ = tauProducers.size();
      rootTausArrays_ = new TClonesArray*[nTausArrays_];
      for(unsigned int i=0; i<nTausArrays_; ++i)
      {
         edm::InputTag tauProducer = tauProducers.at(i);
         rootTausArrays_[i] = new TClonesArray("TRootTau", 1000);
         eventTree_->Branch (tauProducer.label().data(), "TClonesArray", &(rootTausArrays_[i]));
      }
   }
   
   if(doPhoton_)
   {
      if(verbosity_>0) std::cout << "Photons info will be added to rootuple" << std::endl;
      vtag photonProducers = producersNames_.getParameter<vtag>("photonProducer");
      nPhotonsArrays_ = photonProducers.size();
      rootPhotonsArrays_ = new TClonesArray*[nPhotonsArrays_];
      for(unsigned int i=0; i<nPhotonsArrays_; ++i)
      {
         edm::InputTag photonProducer = photonProducers.at(i);
         rootPhotonsArrays_[i] = new TClonesArray("TRootPhoton", 1000);
         eventTree_->Branch (photonProducer.label().data(), "TClonesArray", &(rootPhotonsArrays_[i]));
      }
      if(doPhotonEnergyRegression_)
      {
         egEnergyRegressionV3_ = new EGEnergyCorrector();
         egEnergyRegressionV4_ = new EGEnergyCorrectorSemiParm();
         egEnergyRegressionV5_ = new EGEnergyCorrectorSemiParm();
         egEnergyRegressionV8_ = new EGEnergyCorrectorSemiParm();
      }
   }
   
   if(doCluster_)
   {
      if(verbosity_>0) std::cout << "ECAL Clusters info will be added to rootuple" << std::endl;
      rootBasicClusters_ = new TClonesArray("TRootCluster", 1000);
      eventTree_->Branch ("BasicClusters", "TClonesArray", &rootBasicClusters_);
      rootSuperClusters_ = new TClonesArray("TRootSuperCluster", 1000);
      eventTree_->Branch ("SuperClusters", "TClonesArray", &rootSuperClusters_);
   }

   if(doCracksCorrection_)
   {
      if(verbosity_>0) std::cout << "Cracks Correction will be added to rootuple" << std::endl;
   }
   
   if(keepAllEcalRecHits_ || keepClusterizedEcalRecHits_)
   {
      if(verbosity_>0) std::cout << "ECAL RecHits will be added to rootuple" << std::endl;
      rootEcalRecHits_ = new TClonesArray("TRootEcalRecHit", 10000);
      eventTree_->Branch ("EcalRecHits", "TClonesArray", &rootEcalRecHits_);
   }
   
   if(doPhotonConversion_)
   {
      if(verbosity_>0) std::cout << "Conversion Tracks info will be added to rootuple" << std::endl;
      rootConversionTracks_ = new TClonesArray("TRootTrack", 1000);
      eventTree_->Branch ("ConversionTracks", "TClonesArray", &rootConversionTracks_);
   }
   
   if(doMET_)
   {
      if(verbosity_>0) std::cout << "MET info will be added to rootuple" << std::endl;
      vtag metProducers = producersNames_.getParameter<vtag>("metProducer");
      nMETsArrays_ = metProducers.size();
      rootMETsArrays_ = new TClonesArray*[nMETsArrays_];
      for(unsigned int i=0; i<nMETsArrays_; ++i)
      {
         edm::InputTag metProducer = metProducers.at(i);
         rootMETsArrays_[i] = new TClonesArray("TRootMET", 1000);
         eventTree_->Branch (metProducer.label().data(), "TClonesArray", &(rootMETsArrays_[i]));
      }
      
   }
   
   if(doBardak_)
   {
      if(verbosity_>0) std::cout << "Bardak will be added to rootuple" << std::endl;
      eventTree_->Branch ("Bardak", "TRootBardak", &rootBardak_);
   }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Method called at the end of TotoAna Job
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TotoAnalyzer::endJob()
{
   
   std::cout << "Total number of events: " << nTotEvt_ << std::endl;
   std::cout << "Closing rootfile " << rootFile_->GetName() << std::endl;
   rootFile_->Write(); 
   rootFile_->Close();
   
   if(doL1_) delete l1TriggerAnalyzer_;
   if(doHLT_) delete hltAnalyzer_;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Method called at the beginning of a new run
//   FIXME - RECO files not read by sequential order - Smart enough to identify a run already read ?
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TotoAnalyzer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
   if(verbosity_>0) std::cout << std::endl << std::endl << "####### TotoAnalyzer - START NEW RUN " << iRun.run() << "#######" << std::endl;
   rootRun_ = new TRootRun();
   rootRun_->setXsection(datasetXsection_);
   rootRun_->setDescription(datasetDesciption_);
   rootRun_->setRunNumber(iRun.run());
   rootRun_->setPoolSourceName(poolFileName_);
   
   if(doLHCInfo_)
   {
      if (! beamStatus_) beamStatus_ = new TRootBeamStatus();
      
      // get ConditionsInRunBlock
      edm::Handle<edm::ConditionsInRunBlock> condInRunBlock;
      try
      {
         iRun.getByLabel("conditionsInEdm", condInRunBlock);
         if ( (!condInRunBlock.isValid()) && verbosity_>1) std::cout << "\n  ##### ERROR IN  TotoAnalyzer::beginRun => ConditionsInRunBlock NOT FOUND #####\n";
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "\n  ##### ERROR IN  TotoAnalyzer::beginRun => ConditionsInRunBlock NOT FOUND #####\n"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No edm::ConditionsInRunBlock, skip LHC Beam info" << endl;
         return;
      }
      
      beamStatus_->setBeamMode( condInRunBlock->beamMode );
      beamStatus_->setBeamMomentum( condInRunBlock->beamMomentum );
      beamStatus_->setLhcFillNumber_( condInRunBlock->lhcFillNumber );
   }
   
   if(doHLT_)
   {
      if(verbosity_>1) std::cout << std::endl << "HLTAnalyzer initialization..." << std::endl;
      hltAnalyzer_->init(iRun, iSetup);
   }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Method called at the end of run
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TotoAnalyzer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
   if(verbosity_>0) std::cout << std::endl << std::endl << "####### TotoAnalyzer - END OF RUN #######" << std::endl;
   
   // Trigger Summary Tables
   if(doL1_)
   {
      l1TriggerAnalyzer_ ->copySummary(rootRun_);
      if(verbosity_>0)
      {
         std::cout << "L1 Trigger Summary Tables" << std::endl;
         l1TriggerAnalyzer_->printSummary();
      }
   }
   
   if(doHLT_)
   {
      hltAnalyzer_ ->copySummary(rootRun_);
      if(verbosity_>0)
      {
         std::cout << "HLT Summary Tables" << std::endl;
         hltAnalyzer_->printSummary();
      }
   }
   
   runTree_->Fill();
   delete rootRun_;
   
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Method called at the beginning of each luminosity block
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TotoAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const& iLumi, edm::EventSetup const& iSetup)
{
   if(verbosity_>0) std::cout << std::endl << std::endl << "####### TotoAnalyzer - START NEW LUMI SECTION #######" << std::endl;
   if(doLHCInfo_)
   {
      if (! beamStatus_) beamStatus_ = new TRootBeamStatus();
      
      // get ConditionsInLumiBlock
      edm::Handle<edm::ConditionsInLumiBlock> condInLumiBlock;
      try
      {
         iLumi.getByLabel("conditionsInEdm", condInLumiBlock);
         if ( (!condInLumiBlock.isValid()) && verbosity_>1) std::cout << "\n  ##### ERROR IN  TotoAnalyzer::beginLuminosityBlock => condInLumiBlock NOT FOUND #####\n";
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "\n  ##### ERROR IN  TotoAnalyzer::beginLuminosityBlock => condInLumiBlock NOT FOUND #####\n"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No edm::condInLumiBlock, skip LHC Beam info" << endl;
         return;
      }
      
      beamStatus_->setTotalIntensityBeam1( condInLumiBlock->totalIntensityBeam1 );
      beamStatus_->setTotalIntensityBeam2( condInLumiBlock->totalIntensityBeam2 );
   }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Method called at the end of each luminosity block
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TotoAnalyzer::endLuminosityBlock(edm::LuminosityBlock const& iLumi, edm::EventSetup const& iSetup)
{
   if(verbosity_>0) std::cout << std::endl << std::endl << "####### TotoAnalyzer - END OF LUMI SECTION #######" << std::endl;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Method called at the opening of a new input of file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TotoAnalyzer::respondToOpenInputFile(edm::FileBlock const& fileBlock)
{
   if(verbosity_>0) std::cout << std::endl << std::endl << "####### TotoAnalyzer is opening new file: " << fileBlock.fileName() << std::endl << std::endl;
   poolFileName_ = fileBlock.fileName();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Method called at the closing of the input of file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TotoAnalyzer::respondToCloseInputFile(edm::FileBlock const& fileBlock)
{
   if(verbosity_>0) std::cout << std::endl << std::endl << "####### TotoAnalyzer is closing file: " << fileBlock.fileName() << std::endl;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Method called at the reading of each edm::Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TotoAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{   
   
   time_t startProcessingTime = time(0);
   rootFile_->cd();
   nTotEvt_++;
   
   //edm::Handle< reco::PhotonCollection > recoPhotons;
   //iEvent.getByLabel("photons", recoPhotons);
   //if(recoPhotons->size()<1) return;
   
   
   // Any additionnal variables temporary needed
   if(doBardak_) rootBardak_ = new TRootBardak();
   
   // Global Event Infos
   if (iEvent.isRealData()) doMC_ = false;
   rootEvent_ = new TRootEvent();
   rootEvent_->setRun(rootRun_);
   rootEvent_->setNb(nTotEvt_);
   rootEvent_->setEventId(iEvent.id().event());
   rootEvent_->setRunId(iEvent.id().run());
   rootEvent_->setStoreNumber(iEvent.eventAuxiliary().storeNumber());
   rootEvent_->setLuminosityBlock(iEvent.id().luminosityBlock());
   rootEvent_->setBunchCrossing(iEvent.eventAuxiliary().bunchCrossing());
   rootEvent_->setOrbitNumber(iEvent.eventAuxiliary().orbitNumber());
   rootEvent_->setCollisionTime(iEvent.eventAuxiliary().time().value());
   
   // Get corrections for pileup effect
   if (doRho_) 
   {
      edm::InputTag srcRho_ = producersNames_.getParameter<edm::InputTag>("srcRho");
      edm::Handle<double> rhoHandle;
      try
      {
         iEvent.getByLabel(srcRho_,rhoHandle);
         if ( (!rhoHandle.isValid()) && verbosity_>1) std::cout << "\n  ##### ERROR IN  TotoAnalyzer::analyze =>" << srcRho_ <<"  NOT FOUND #####\n";
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "\n  ##### ERROR IN  TotoAnalyzer::analyze => " << srcRho_ << " NOT FOUND #####\n"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No " << srcRho_ << ", skip rho info" << endl;
         return;
      }
      if (rhoHandle.isValid()) rootEvent_->setRho(*rhoHandle);
   }
   
   
   // LHC Beam Status
   if(doLHCInfo_)
   {
      if (! beamStatus_) beamStatus_ = new TRootBeamStatus();
      edm::Handle<edm::ConditionsInEventBlock> condInEventBlock;
      try
      {
         iEvent.getByLabel("conditionsInEdm", condInEventBlock);
         if ( (!condInEventBlock.isValid()) && verbosity_>1) std::cout << "\n  ##### ERROR IN  TotoAnalyzer::analyze => condInEventBlock NOT FOUND #####\n";
      }
      catch (cms::Exception& exception)
      {
         if ( !allowMissingCollection_ )
         {
            cout << "\n  ##### ERROR IN  TotoAnalyzer::analyze => condInEventBlock NOT FOUND #####\n"<<endl;
            throw exception;
         }
         if(verbosity_>1) cout <<  "   ===> No edm::condInEventBlock, skip LHC Beam info" << endl;
         return;
      }
      
      beamStatus_->setBstMasterStatus( condInEventBlock->bstMasterStatus );
      beamStatus_->setTurnCountNumber( condInEventBlock->turnCountNumber );
      rootEvent_->setBeamStatus((*beamStatus_));
   }
   
   
   // Print event infos
   if( (verbosity_>1) || (verbosity_>0 && nTotEvt_%10==0 && nTotEvt_<=100)  || (verbosity_>0 && nTotEvt_%100==0 && nTotEvt_>100) )
      std::cout << std::endl << std::endl << "####### TotoAnalyzer - " << *rootEvent_  << " #######" << std::endl;
   
   // L1 Trigger
      if(doL1_)
      {
         if(nTotEvt_==1 && verbosity_>1) std::cout << std::endl << "L1TriggerAnalyzer initialization..." << std::endl;
         if (nTotEvt_==1) l1TriggerAnalyzer_->init(iEvent, iSetup, rootEvent_);
         if(verbosity_>1) std::cout << std::endl << "Get L1 Results..." << std::endl;
         l1TriggerAnalyzer_->process(iEvent, rootEvent_);
      }
      
      // HLT
      if(doHLT_)
      {
         if(verbosity_>1) std::cout << std::endl << "Get HLT Results..." << std::endl;
         hltAnalyzer_->process(iEvent, iSetup, rootEvent_);
         if(doHLTObject_) hltAnalyzer_->keepTriggerObjects(iEvent, producersNames_, rootHLTObjects_);
      }
      
      
      // MC Info
      if(doMC_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing MC info..." << std::endl;
         MCAnalyzer* myMCAnalyzer = new MCAnalyzer(myConfig_, producersNames_);
         myMCAnalyzer->setVerbosity(verbosity_);
         if (drawMCTree_) myMCAnalyzer->drawMCTree(iEvent, iSetup, myConfig_, producersNames_);
         if ( doPDFInfo_ ) myMCAnalyzer->pdfInfo(iEvent, rootEvent_);
         myMCAnalyzer->pileupInfo(iEvent, rootEvent_);
         myMCAnalyzer->processMCParticle(iEvent, rootMCParticles_);
         if(doJetMC_) myMCAnalyzer->processGenJets(iEvent, rootGenJets_);
         if(doMETMC_) myMCAnalyzer->processGenMETs(iEvent, rootGenMETs_);
         if (doSignalMuMuGamma_)
         {
            rootMuMuGammaEvent_ = new TRootSignalEvent();
            myMCAnalyzer->processMuMuGammaEvent(iEvent, rootMuMuGammaEvent_);
         }
         if (doSignalTopTop_) myMCAnalyzer->processTopTopEvent(iEvent, rootMCTopTop_);
         if (doPhotonConversionMC_) myMCAnalyzer->processConvertedPhoton(iEvent, rootMCPhotons_);
         if (doElectronsMCTruth_) myMCAnalyzer->processMCElectron(iEvent, rootMCElectrons_);
         delete myMCAnalyzer;
      }
      
      
      // Tracks (must be called before vertex reconstruction to perform tracks-vertex association)
      if(doTrack_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing tracks collection..." << std::endl;
         TrackAnalyzer* myTrackAnalyzer = new TrackAnalyzer(producersNames_, verbosity_);
         myTrackAnalyzer->process(iEvent, rootTracks_);
         delete myTrackAnalyzer;
      }
      
      
      // Get Primary Vertices and Beam Spot
      if(doPrimaryVertex_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing beam spot and primary vertices collection..." << std::endl;
         VertexAnalyzer* myVertexAnalyzer = new VertexAnalyzer(producersNames_, verbosity_);
         if(doBeamSpot_) myVertexAnalyzer->getBeamSpot(iEvent, rootBeamSpot_);
         myVertexAnalyzer->getVertices(iEvent, rootVertices_, rootTracks_);
         myVertexAnalyzer->selectPrimary(rootEvent_, rootVertices_);
         delete myVertexAnalyzer;
      }
      
      
      // Reconstruct Zee Primary Vertices with and without electron pair
      if(doZeePrimaryVertex_)
      {
         if(verbosity_>1) std::cout << std::endl << "Reconstruct Zee Primary Vertices with and without electron pair..." << std::endl;
         ZeeVertexAnalyzer* myZeeVertexAnalyzer = new ZeeVertexAnalyzer(myConfig_, producersNames_, verbosity_);
         myZeeVertexAnalyzer->getVertices(iEvent, iSetup, rootZeeVertices_, rootTracks_, rootBardak_);
         delete myZeeVertexAnalyzer;
      }
      
      
      // Print tracks (after vertex analyzer to display track-vertex association)
      if(doTrack_ && verbosity_>2)
      {
         std::cout << std::endl << std::endl;
         TRootTrack* tk;
         for (int itk=0; itk<rootTracks_->GetEntriesFast(); itk++)
         {
            tk = (TRootTrack*) rootTracks_->At(itk);
            std::cout << "   ["<< setw(3) << itk << "] ";
            tk->Print();
         }
      }
      
      
      // Calo Jet
      if(doJet_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing jets collection..." << std::endl;
         vtag jetProducers = producersNames_.getParameter<vtag>("jetProducer");
         for(unsigned int i=0; i<jetProducers.size(); ++i)
         {
            const edm::InputTag jetProducer = jetProducers.at(i);
            JetAnalyzer* myJetAnalyzer = new JetAnalyzer(jetProducer, producersNames_, myConfig_, verbosity_);
            myJetAnalyzer->process(iEvent, rootJetsArrays_[i]);
            delete myJetAnalyzer;
         }
      }
      
      
      // Muons
      if(doMuon_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing muons collection..." << std::endl;
         vtag muonProducers = producersNames_.getParameter<vtag>("muonProducer");
         for(unsigned int i=0; i<muonProducers.size(); ++i)
         {
            const edm::InputTag muonProducer = muonProducers.at(i);
            MuonAnalyzer* myMuonAnalyzer = new MuonAnalyzer(muonProducer, producersNames_, myConfig_, verbosity_);
            if(doPrimaryVertex_) myMuonAnalyzer->initIPCalculator(iEvent, iSetup, rootEvent_, rootBeamSpot_);
            myMuonAnalyzer->process(iEvent,rootBeamSpot_, rootMuonsArrays_[i]);
            delete myMuonAnalyzer;
         }
      }
      
      
      // Lazy Tools to calculate Cluster shape variables
      EcalClusterLazyTools* lazyTools = 0;
      if( doElectron_ || doPhoton_ || doCluster_ )
      {
         if(verbosity_>1) std::cout << std::endl << "Loading egamma LazyTools..." << std::endl;
         edm::InputTag reducedBarrelEcalRecHitCollection_ = producersNames_.getParameter<edm::InputTag>("reducedBarrelEcalRecHitCollection");
         edm::InputTag reducedEndcapEcalRecHitCollection_ = producersNames_.getParameter<edm::InputTag>("reducedEndcapEcalRecHitCollection");
         try
         {
            lazyTools = new EcalClusterLazyTools( iEvent, iSetup, reducedBarrelEcalRecHitCollection_, reducedEndcapEcalRecHitCollection_ );
         }
         catch (cms::Exception& exception)
         {
            if ( !allowMissingCollection_ )
            {
               std::cout << "  ##### ERROR IN  TotoAnalyzer::analyze => CaloGeometryRecord, CaloGeometryRecord or EcalRecHitCollection are missing #####"<<std::endl;
               throw exception;
            }
            if(verbosity_>1) std::cout <<  "   ===> CaloGeometryRecord, CaloGeometryRecord or EcalRecHitCollection are missing, skip calculation of cluster shape variables" << std::endl;
            delete lazyTools;
         }
      }

      // Josh's Photon Energy Regression - https://twiki.cern.ch/twiki/bin/view/CMS/RegressionSCCorrections    
      if(doPhotonEnergyRegression_)    
      {    
         int version = 0;  
         //if(verbosity_>1) std::cout << std::endl << "Loading photon energy regression file..." << std::endl;
         if ( ! egEnergyRegressionV3_->IsInitialized() )
         {
            if(verbosity_>1) std::cout << "photonEnergyRegressionFileV3_=" << photonEnergyRegressionFileV3_.data() << std::endl;
            egEnergyRegressionV3_->Initialize(iSetup, photonEnergyRegressionFileV3_.data());
         }         
         if ( ! egEnergyRegressionV4_->IsInitialized() )
         {
            version = 4;
            if(verbosity_>1) std::cout << "photonEnergyRegressionFileV4_=" << photonEnergyRegressionFileV4_.data() << std::endl;
            egEnergyRegressionV4_->Initialize(photonEnergyRegressionFileV4_.data(),version);
         }
         if ( ! egEnergyRegressionV5_->IsInitialized() )
         {
            version = 5;
            if(verbosity_>1) std::cout << "photonEnergyRegressionFileV5_=" << photonEnergyRegressionFileV5_.data() << std::endl;
            egEnergyRegressionV5_->Initialize(photonEnergyRegressionFileV5_.data(),version);
         }
         if ( ! egEnergyRegressionV8_->IsInitialized() )
         {
            version = 6; 
            if(verbosity_>1) std::cout << "photonEnergyRegressionFileV8_=" << photonEnergyRegressionFileV8_.data() << std::endl;
            egEnergyRegressionV8_->Initialize(photonEnergyRegressionFileV8_.data(),version);
         }
      }
      
      
      // Ecal recHits
      if(keepAllEcalRecHits_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing Ecal recHits collection..." << std::endl;
         EcalRecHitsAnalyzer* myEcalRecHitsAnalyzer = new EcalRecHitsAnalyzer(producersNames_, verbosity_);
         myEcalRecHitsAnalyzer->process(iEvent, iSetup, rootEcalRecHits_);
         delete myEcalRecHitsAnalyzer;
      }
      
      // Electrons
      if(doElectron_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing electrons collection..." << std::endl;
         vtag electronProducers = producersNames_.getParameter<vtag>("electronProducer");
         for(unsigned int i=0; i<electronProducers.size(); ++i)
         {
            const edm::InputTag electronProducer = electronProducers.at(i);
            ElectronAnalyzer* myElectronAnalyzer = new ElectronAnalyzer(electronProducer, producersNames_, myConfig_, verbosity_);
            if(doPrimaryVertex_) myElectronAnalyzer->initIPCalculator(iEvent, iSetup, rootEvent_, rootBeamSpot_);
            myElectronAnalyzer->process(iEvent, rootBeamSpot_, rootElectronsArrays_[i], lazyTools);
            delete myElectronAnalyzer;
         }
      }
      
      // Taus
      if(doTau_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing taus collection..." << std::endl;
         vtag tauProducers = producersNames_.getParameter<vtag>("tauProducer");
         for(unsigned int i=0; i<tauProducers.size(); ++i)
         {
            const edm::InputTag tauProducer = tauProducers.at(i);
            TauAnalyzer* myTauAnalyzer = new TauAnalyzer(tauProducer, producersNames_, myConfig_, verbosity_);
            if(doPrimaryVertex_) myTauAnalyzer->initIPCalculator(iEvent, iSetup, rootEvent_, rootBeamSpot_);
            myTauAnalyzer->process(iEvent,rootBeamSpot_, rootTausArrays_[i]);
            delete myTauAnalyzer;
         }
      }
      
      // Photons
      if(doPhoton_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing photons collection..." << std::endl;
         vtag photonProducers = producersNames_.getParameter<vtag>("photonProducer");
         for(unsigned int i=0; i<photonProducers.size(); ++i)
         {
            const edm::InputTag photonProducer = photonProducers.at(i);
            PhotonAnalyzer* myPhotonAnalyzer = new PhotonAnalyzer(photonProducer, producersNames_, myConfig_, verbosity_);
            myPhotonAnalyzer->process(iEvent, iSetup, rootEvent_, rootPhotonsArrays_[i], rootConversionTracks_, lazyTools, egEnergyRegressionV3_, egEnergyRegressionV4_, egEnergyRegressionV5_, egEnergyRegressionV8_);
            delete myPhotonAnalyzer;
         }
      }
      
      
      // Ecal Clusters
      if(doCluster_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing BasicClusters collection..." << std::endl;
         vtag basicClusterProducers = producersNames_.getParameter<vtag>("basicClusterProducer");
         vint32 basicClusterProducerIndices = producersNames_.getParameter<vint32>("basicClusterProducerIndex");
         ClusterAnalyzer* myClusterAnalyzer = new ClusterAnalyzer(myConfig_, producersNames_, verbosity_);
         for(unsigned int i=0; i<basicClusterProducers.size(); ++i)
         {
            const edm::InputTag basicClusterProducer = basicClusterProducers.at(i);
            const int bcType = basicClusterProducerIndices.at(i);
            myClusterAnalyzer->process(iEvent, iSetup, rootEvent_, lazyTools, rootBasicClusters_, basicClusterProducer, bcType);
         }
         delete myClusterAnalyzer;
         
         if(verbosity_>1) std::cout << std::endl << "Analysing SuperClusters collection..." << std::endl;
         vtag superClusterProducers = producersNames_.getParameter<vtag>("superClusterProducer");
         vint32 superClusterProducerIndices = producersNames_.getParameter<vint32>("superClusterProducerIndex");
         SuperClusterAnalyzer* mySClusterAnalyzer = new SuperClusterAnalyzer(myConfig_, producersNames_, verbosity_);
         for(unsigned int i=0; i<superClusterProducers.size(); ++i)
         {
            const edm::InputTag superClusterProducer = superClusterProducers.at(i);
            const int scType = superClusterProducerIndices.at(i);
            mySClusterAnalyzer->process(iEvent, iSetup, rootEvent_, rootSuperClusters_, superClusterProducer, scType, rootBasicClusters_);
         }
         delete mySClusterAnalyzer;
      }
      
      
      if(doCluster_)
      {
         ClusterAssociator* myClusterAssociator = new ClusterAssociator(myConfig_);
         myClusterAssociator->setVerbosity(verbosity_);
         myClusterAssociator->process(rootSuperClusters_, rootBasicClusters_);
         if(verbosity_>4) myClusterAssociator->printSuperClusters(rootSuperClusters_, rootBasicClusters_,0);  // 0 to print all types SC
      delete myClusterAssociator;
      }
      
      
      if(doElectron_ && doCluster_)
      {
         ElectronAssociator* myElectronAssociator = new ElectronAssociator();
         myElectronAssociator->setVerbosity(verbosity_);
         for(unsigned int i=0; i<nElectronsArrays_; ++i)
         {
            myElectronAssociator->associateSuperCluster(rootElectronsArrays_[i], rootSuperClusters_);
            if(verbosity_>2) myElectronAssociator->fullPrintElectrons(rootElectronsArrays_[i],rootSuperClusters_,rootBasicClusters_,0);
         }
         delete myElectronAssociator;
      }
      
      
      if(doPhoton_ && doCluster_)
      {
         PhotonAssociator* myPhotonAssociator = new PhotonAssociator();
         myPhotonAssociator->setVerbosity(verbosity_);
         for(unsigned int i=0; i<nPhotonsArrays_; ++i)
         {
            myPhotonAssociator->associateSuperCluster(rootPhotonsArrays_[i], rootSuperClusters_);
         }
         delete myPhotonAssociator;
      }
      
      
      if(doPhoton_ && doPhotonIsolation_)
      {
         if(verbosity_>1) std::cout << std::endl << "Calculating Photon isolation..." << std::endl;
         
         Float_t ecalIslandIsolation;
         Float_t ecalDoubleConeIsolation;
         Float_t hcalRecHitIsolation;
         Float_t isoTracks;
         Int_t isoNTracks;
         Int_t isoNNiceTracks;
         TRootPhoton* localPhoton;
         
         for(unsigned int i=0; i<nPhotonsArrays_; ++i)
         {
            PhotonIsolator* myPhotonIsolator = new PhotonIsolator(&myConfig_, &producersNames_);
            for (int iphoton=0; iphoton<rootPhotonsArrays_[i]->GetEntriesFast(); iphoton++)
            {
               localPhoton = (TRootPhoton*)rootPhotonsArrays_[i]->At(iphoton);
               
               ecalIslandIsolation=-1.;
               if (doCluster_) ecalIslandIsolation = myPhotonIsolator->basicClustersIsolation(localPhoton, rootSuperClusters_, rootBasicClusters_);
               
               ecalDoubleConeIsolation=-1.;
               if (doCluster_) ecalDoubleConeIsolation = myPhotonIsolator->basicClustersDoubleConeIsolation(localPhoton, rootSuperClusters_, rootBasicClusters_);
               
               hcalRecHitIsolation=-1.;
               if ( myPhotonIsolator->loadHcalRecHits(iEvent, iSetup) ) hcalRecHitIsolation = myPhotonIsolator->hcalRecHitIsolation(localPhoton);
               
               isoTracks=-1.;
               isoNTracks=-1;
               if(doTrack_) isoTracks = myPhotonIsolator->trackerIsolation(localPhoton, rootTracks_, isoNTracks);
               
               localPhoton->setIsolationPerso(ecalIslandIsolation, ecalDoubleConeIsolation, hcalRecHitIsolation, isoTracks, isoNTracks);
               
               isoNNiceTracks=-1;
               bool doNiceTracksIsolation = myConfig_.getUntrackedParameter<bool>("doNiceTracksIsolation",false);
               if(doNiceTracksIsolation) isoNNiceTracks = myPhotonIsolator->nNiceTracks(iEvent, iSetup, producersNames_, localPhoton);
               localPhoton->setDR04IsolationNNiceTracks(isoNNiceTracks);
               
               if(verbosity_>4) { std::cout << "   After isolation - ["<< setw(3) << iphoton << "] "; localPhoton->Print(); std::cout << std::endl; }
            }
            delete myPhotonIsolator;
         }
      }
      
      
      if(doPhoton_ && doElectron_ && doCluster_)
      {
         if(verbosity_>1) std::cout << std::endl << "Runing Ambiguity Solver..." << std::endl;
         AmbiguitySolver* myAmbiguitySolver = new AmbiguitySolver(myConfig_, verbosity_);
         for(unsigned int i=0; i<nElectronsArrays_; ++i)
            for(unsigned int j=0; j<nPhotonsArrays_; ++j)
               myAmbiguitySolver->processElectronsPhotons(rootSuperClusters_, rootElectronsArrays_[i], rootPhotonsArrays_[j]);
            delete myAmbiguitySolver;
      }
      
      
      // Print Photons / SuperClusters / BasicClusters arborescence
      if(doPhoton_)
      {
         PhotonAssociator* myPhotonAssociator = new PhotonAssociator();
         for(unsigned int i=0; i<nPhotonsArrays_; ++i)
         {
            if(verbosity_==3) myPhotonAssociator->fullPrintPhotons(rootPhotonsArrays_[i],rootSuperClusters_,rootBasicClusters_,0);
            if(verbosity_>3) myPhotonAssociator->fullPrintPhotonsAndRecHits(rootPhotonsArrays_[i],rootSuperClusters_,rootBasicClusters_,0);
         }
         delete myPhotonAssociator;
      }
      
      
      // MET
      if(doMET_)
      {
         if(verbosity_>1) std::cout << std::endl << "Analysing Missing Et..." << std::endl;
         vtag metProducers = producersNames_.getParameter<vtag>("metProducer");
         for(unsigned int i=0; i<metProducers.size(); ++i)
         {
            const edm::InputTag metProducer = metProducers.at(i);
            METAnalyzer* myMETAnalyzer = new METAnalyzer(metProducer, producersNames_, myConfig_, verbosity_);
            myMETAnalyzer->process(iEvent, rootMETsArrays_[i]);
            delete myMETAnalyzer;
         }
      }
      
      
      // Associate recoParticles to mcParticles
      if(doMC_)
      {
         // TODO - For the moment, only for PAT format
         if ( dataType_=="PAT")
         {
            MCAssociator* myMCAssociator = new MCAssociator(producersNames_, verbosity_);
            myMCAssociator->init(iEvent, rootMCParticles_);
            if(verbosity_>4) std::cout << std::endl << "Printing recoParticles / mcParticles associations... " << std::endl;
            for(unsigned int i=0; i<nPhotonsArrays_; ++i)
            {
               if(doPhoton_) myMCAssociator->matchGenParticlesTo(rootPhotonsArrays_[i]);
               if(verbosity_>4 && doPhoton_) myMCAssociator->printParticleAssociation(rootPhotonsArrays_[i]);
            }
            for(unsigned int i=0; i<nElectronsArrays_; ++i) {
               if(doElectron_) myMCAssociator->matchGenParticlesTo(rootElectronsArrays_[i]);
               if(verbosity_>4 && doElectron_) myMCAssociator->printParticleAssociation(rootElectronsArrays_[i]);
            }
            for(unsigned int i=0; i<nMuonsArrays_; ++i) {
               if(doMuon_) myMCAssociator->matchGenParticlesTo(rootMuonsArrays_[i]);
               if(verbosity_>4 && doMuon_) myMCAssociator->printParticleAssociation(rootMuonsArrays_[i]);
            }
            for(unsigned int i=0; i<nMETsArrays_; ++i) {
               if(doMET_) myMCAssociator->matchGenParticlesTo(rootMETsArrays_[i]);
               if(verbosity_>4 && doMET_) myMCAssociator->printParticleAssociation(rootMETsArrays_[i]);
            }
            for(unsigned int i=0; i<nJetsArrays_; ++i)
            {
               if(doJet_) myMCAssociator->matchGenParticlesTo(rootJetsArrays_[i]);
               if(doJet_ && doJetMC_) myMCAssociator->processGenJets(rootGenJets_, rootJetsArrays_[i]);
               if(verbosity_>4 && doJet_) myMCAssociator->printJetAssociation(rootJetsArrays_[i]);
            }
            delete myMCAssociator;
         }
      }
      
      time_t endProcessingTime = time(0);
      rootEvent_->setTotoAnaProcessingTime(endProcessingTime-startProcessingTime);
      
      if(verbosity_>1) std::cout << std::endl << "Filling rootuple..." << std::endl;
      
      eventTree_->Fill();
      delete rootEvent_;
      if(verbosity_>1) std::cout << std::endl << "Start deleting objects..." << std::endl;
      if(doHLT_ && doHLTObject_) (*rootHLTObjects_).Delete();
      if(doMC_) (*rootMCParticles_).Delete();
      if(doJetMC_) (*rootGenJets_).Delete();
      if(doMETMC_) (*rootGenMETs_).Delete();
      if(doSignalMuMuGamma_) delete rootMuMuGammaEvent_;
      if(doSignalTopTop_) (*rootMCTopTop_).Delete();
      if(doPhotonConversionMC_) (*rootMCPhotons_).Delete();
      if(doBeamSpot_) rootBeamSpot_->clear();
      if(doPrimaryVertex_) (*rootVertices_).Delete();
      if(doZeePrimaryVertex_) (*rootZeeVertices_).Delete();
      if(doTrack_) (*rootTracks_).Delete();
      for(unsigned int i=0; i<nJetsArrays_; ++i) (*(rootJetsArrays_[i])).Delete();
      for(unsigned int i=0; i<nMuonsArrays_; ++i) (*(rootMuonsArrays_[i])).Delete();
      for(unsigned int i=0; i<nElectronsArrays_; ++i) (*(rootElectronsArrays_[i])).Delete();
      for(unsigned int i=0; i<nTausArrays_; ++i) (*(rootTausArrays_[i])).Delete();
      for(unsigned int i=0; i<nPhotonsArrays_; ++i) (*(rootPhotonsArrays_[i])).Delete();
      if(doCluster_) (*rootBasicClusters_).Delete();
      if(doCluster_) (*rootSuperClusters_).Delete();
      if(keepAllEcalRecHits_ || keepClusterizedEcalRecHits_) (*rootEcalRecHits_).Delete();
      if(doPhotonConversion_) (*rootConversionTracks_).Delete();
      for(unsigned int i=0; i<nMETsArrays_; ++i) (*(rootMETsArrays_[i])).Delete();
      if(doBardak_) delete rootBardak_;
      if(lazyTools != 0) delete lazyTools;
      if(verbosity_>1) std::cout << std::endl << "Objects deleted" << std::endl;
      if(verbosity_>0) std::cout << std::endl;
}
