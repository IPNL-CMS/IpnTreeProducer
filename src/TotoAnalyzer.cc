#include "../interface/TotoAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

typedef std::vector<edm::InputTag> vtag;

TotoAnalyzer::TotoAnalyzer(const edm::ParameterSet& iConfig)
{
	startTime_ = time(0);
	time_t t = time(0);
	char ts[] = "dd-Mon-yyyy hh:mm:ss TZN     ";
	strftime(ts, strlen(ts) + 1, "%d-%b-%Y %H:%M:%S %Z", localtime(&t));
	cout << endl << "START TOTOANALYZER AT " << ts << endl << endl;

	myConfig_ = iConfig.getParameter<ParameterSet>("myConfig");
	cout << "myConfig parameters:" << endl << "===================" << endl << endl << myConfig_ << endl;
	dataType_ = myConfig_.getUntrackedParameter<string>("dataType","unknown");
	if( dataType_=="RECO" )          producersNames_ = iConfig.getParameter<ParameterSet>("producersNamesRECO");
	else if( dataType_=="PAT" )         producersNames_ = iConfig.getParameter<ParameterSet>("producersNamesPAT");
	else { cout << "TotoAnalyzer::TotoAnalyzer...   dataType is unknown...  exiting..." << endl; exit(1); }
	cout << endl << "Producers used:" << endl << "==============" << endl << endl << producersNames_ << endl;
	
	runInfos_ = 0;
	rootEvent_ = 0;
	l1TriggerAnalyzer_ = 0;
	hltAnalyzer_ = 0;
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
	rootMuons_ = 0;
	rootElectrons_ = 0;
	rootPhotons_ = 0;
	rootBasicClusters_ = 0;
	rootSuperClusters_ = 0;
	rootEcalRecHits_ = 0;
	rootConversionTracks_ = 0;
	rootMETs_ = 0;
	rootBardak_ = 0;
}


TotoAnalyzer::~TotoAnalyzer()
{
	time_t endTime = time(0);
	char ts[] = "dd-Mon-yyyy hh:mm:ss TZN     ";
	strftime(ts, strlen(ts) + 1, "%d-%b-%Y %H:%M:%S %Z", localtime(&endTime));
	cout << endl << endl << "END TOTOANALYZER AT " << ts << endl;
	if (nTotEvt_>0) cout << "===> " << float(endTime-startTime_)/float(nTotEvt_) << " s/evt" << endl;
}


// ------------ method called once each job just before starting event loop  ------------
void TotoAnalyzer::beginJob()
{
		
	// Load Config parameters
	verbosity_ = myConfig_.getUntrackedParameter<int>("verbosity", 0);
	allowMissingCollection_ = producersNames_.getUntrackedParameter<bool>("allowMissingCollection", false);
	rootFileName_ = myConfig_.getUntrackedParameter<string>("RootFileName","noname.root");
	datasetXsection_ = myConfig_.getUntrackedParameter<double>("xsection");
	datasetDesciption_ = myConfig_.getUntrackedParameter<string>("description","Pas de description");
	doL1_ = myConfig_.getUntrackedParameter<bool>("doL1",false);
	doHLT_ = myConfig_.getUntrackedParameter<bool>("doHLT",false);
	doMC_ = myConfig_.getUntrackedParameter<bool>("doMC",false);
	doJetMC_ = myConfig_.getUntrackedParameter<bool>("doJetMC",false);
	doMETMC_ = myConfig_.getUntrackedParameter<bool>("doMETMC",false);
	doPDFInfo_ = myConfig_.getUntrackedParameter<bool>("doPDFInfo",false);
	doSignalMuMuGamma_ = myConfig_.getUntrackedParameter<bool>("doSignalMuMuGamma",false);
	doSignalTopTop_ = myConfig_.getUntrackedParameter<bool>("doSignalTopTop",false);
	doPhotonConversionMC_ = myConfig_.getUntrackedParameter<bool>("doPhotonConversionMC",false);
	drawMCTree_ = myConfig_.getUntrackedParameter<bool>("drawMCTree",false);
	doBeamSpot_ = myConfig_.getUntrackedParameter<bool>("doBeamSpot",false);
	doPrimaryVertex_ = myConfig_.getUntrackedParameter<bool>("doPrimaryVertex",false);
	doZeePrimaryVertex_ = myConfig_.getUntrackedParameter<bool>("doZeePrimaryVertex",false);
	doTrack_ = myConfig_.getUntrackedParameter<bool>("doTrack",false);
	doJet_ = myConfig_.getUntrackedParameter<bool>("doJet",false);
	doMuon_ = myConfig_.getUntrackedParameter<bool>("doMuon",false);
	doElectron_ = myConfig_.getUntrackedParameter<bool>("doElectron",false);
	doPhoton_ = myConfig_.getUntrackedParameter<bool>("doPhoton",false);
	doCluster_ = myConfig_.getUntrackedParameter<bool>("doCluster",false);
	keepAllEcalRecHits_ = myConfig_.getUntrackedParameter<bool>("keepAllEcalRecHits",false);
	keepClusterizedEcalRecHits_ = myConfig_.getUntrackedParameter<bool>("keepClusterizedEcalRecHits",false);
	doPhotonConversion_ = myConfig_.getUntrackedParameter<bool>("doPhotonConversion",false);
	doPhotonIsolation_ = myConfig_.getUntrackedParameter<bool>("doPhotonIsolation",false);
	doMET_ = myConfig_.getUntrackedParameter<bool>("doMET",false);
	doBardak_ = myConfig_.getUntrackedParameter<bool>("doBardak",false);
	
	nTotEvt_ = 0;
	
	// initialize root output file
	if(verbosity_>0) cout << "New RootFile " << rootFileName_.c_str() << " is created" << endl;
	rootFile_ = new TFile(rootFileName_.c_str(), "recreate");
	rootFile_->cd();
	
	runInfos_ = new TRootRun();
	runTree_ = new TTree("runTree", "Global Run Infos");
	runTree_->Branch ("runInfos", "TRootRun", &runInfos_);
	runInfos_->setXsection(datasetXsection_);
	runInfos_->setDescription(datasetDesciption_);
	
	rootEvent_ = 0;
	eventTree_ = new TTree("eventTree", "Event Infos");
	eventTree_->Branch ("Event", "TRootEvent", &rootEvent_);
	
	if(doL1_)
	{
		l1TriggerAnalyzer_ = new L1TriggerAnalyzer(producersNames_, verbosity_);
	}
	
	if(doHLT_)
	{
		hltAnalyzer_ = new HLTAnalyzer(producersNames_, verbosity_);
	}
	
	if(doMC_)
	{
		if(verbosity_>0) cout << "MC Particles info will be added to rootuple" << endl;
		rootMCParticles_ = new TClonesArray("TRootMCParticle", 1000);
		eventTree_->Branch ("MCParticles", "TClonesArray", &rootMCParticles_);
	}
	
	if(doJetMC_)
	{
		if(verbosity_>0) cout << "genJets info will be added to rootuple" << endl;
		rootGenJets_ = new TClonesArray("TRootParticle", 1000);
		eventTree_->Branch ("genJets", "TClonesArray", &rootGenJets_);
	}
	
	if(doMETMC_)
	{
		if(verbosity_>0) cout << "genMETs info will be added to rootuple" << endl;
		rootGenMETs_ = new TClonesArray("TRootParticle", 1000);
		eventTree_->Branch ("genMETs", "TClonesArray", &rootGenMETs_);
	}
	
	if(doSignalMuMuGamma_)
	{
		if(verbosity_>0) cout << "MC info for Z -> mu mu gamma  will be added to rootuple" << endl;
		eventTree_->Branch ("MuMuGamma", "TRootSignalEvent", &rootMuMuGammaEvent_);
	}
	
	if(doSignalTopTop_)
	{
		if(verbosity_>0) cout << "MC info for Top Top will be added to rootuple" << endl;
		rootMCTopTop_ = new TClonesArray("TRootTopTop", 1000);
		eventTree_->Branch ("rootMCTopTop", "TClonesArray", &rootMCTopTop_);
	}
	
	if(doPhotonConversionMC_)
	{
		if(verbosity_>0) cout << "Converted MC Photons info will be added to rootuple" << endl;
		rootMCPhotons_ = new TClonesArray("TRootMCPhoton", 1000);
		eventTree_->Branch ("MCPhotons", "TClonesArray", &rootMCPhotons_);
	}
	
	if(doBeamSpot_)
	{
		if(verbosity_>0) cout << "BeamSpot info will be added to rootuple" << endl;
		rootBeamSpot_ = new TRootBeamSpot();
		eventTree_->Branch ("BeamSpot", "TRootBeamSpot", &rootBeamSpot_);
	}
	
	if(doPrimaryVertex_)
	{
		if(verbosity_>0) cout << "Vertices info will be added to rootuple" << endl;
		rootVertices_ = new TClonesArray("TRootVertex", 1000);
		eventTree_->Branch ("Vertices", "TClonesArray", &rootVertices_);
	}
	
	if(doZeePrimaryVertex_)
	{
		if(verbosity_>0) cout << "Zee Primary Vertices info will be added to rootuple" << endl;
		rootZeeVertices_ = new TClonesArray("TRootVertex", 1000);
		eventTree_->Branch ("ZeeVertices", "TClonesArray", &rootZeeVertices_);
	}
	
	if(doTrack_)
	{
		if(verbosity_>0) cout << "Tracks info will be added to rootuple" << endl;
		rootTracks_ = new TClonesArray("TRootTrack", 1000);
		eventTree_->Branch ("Tracks", "TClonesArray", &rootTracks_);
	}
	
	if(doJet_)
	{
		if(verbosity_>0) cout << "Jets info will be added to rootuple" << endl;
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
		if(verbosity_>0) cout << "Muons info will be added to rootuple" << endl;
		rootMuons_ = new TClonesArray("TRootMuon", 1000);
		eventTree_->Branch ("Muons", "TClonesArray", &rootMuons_);
	}
	
	if(doElectron_)
	{
		if(verbosity_>0) cout << "Electrons info will be added to rootuple" << endl;
		rootElectrons_ = new TClonesArray("TRootElectron", 1000);
		eventTree_->Branch ("Electrons", "TClonesArray", &rootElectrons_);
	}
	
	if(doPhoton_)
	{
		if(verbosity_>0) cout << "Photons info will be added to rootuple" << endl;
		rootPhotons_ = new TClonesArray("TRootPhoton", 1000);
		eventTree_->Branch ("Photons", "TClonesArray", &rootPhotons_);
	}
	
	if(doCluster_)
	{
		if(verbosity_>0) cout << "ECAL Clusters info will be added to rootuple" << endl;
		rootBasicClusters_ = new TClonesArray("TRootCluster", 1000);
		eventTree_->Branch ("BasicClusters", "TClonesArray", &rootBasicClusters_);
		rootSuperClusters_ = new TClonesArray("TRootSuperCluster", 1000);
		eventTree_->Branch ("SuperClusters", "TClonesArray", &rootSuperClusters_);
	}
	
	if(keepAllEcalRecHits_ || keepClusterizedEcalRecHits_)
	{
		if(verbosity_>0) cout << "ECAL RecHits will be added to rootuple" << endl;
		rootEcalRecHits_ = new TClonesArray("TRootEcalRecHit", 10000);
		eventTree_->Branch ("EcalRecHits", "TClonesArray", &rootEcalRecHits_);
	}
	
	if(doPhotonConversion_)
	{
		if(verbosity_>0) cout << "Conversion Tracks info will be added to rootuple" << endl;
		rootConversionTracks_ = new TClonesArray("TRootTrack", 1000);
		eventTree_->Branch ("ConversionTracks", "TClonesArray", &rootConversionTracks_);
		
		conversionLikelihoodCalculator_ = new ConversionLikelihoodCalculator();
		//std::string weightsString =  myConfig_.getUntrackedParameter<string>("conversionLikelihoodWeightsFile","RecoEgamma/EgammaTools/data/TMVAnalysis_Likelihood.weights.txt");
		//edm::FileInPath weightsFile(weightsString.c_str() );
		//conversionLikelihoodCalculator_->setWeightsFile(weightsFile.fullPath().c_str());
	}
	
	if(doMET_)
	{
		if(verbosity_>0) cout << "MET info will be added to rootuple" << endl;
		rootMETs_ = new TClonesArray("TRootMET", 1000);
		eventTree_->Branch ("MET", "TClonesArray", &rootMETs_);
	}
	
	if(doBardak_)
	{
		if(verbosity_>0) cout << "Bardak will be added to rootuple" << endl;
		eventTree_->Branch ("Bardak", "TRootBardak", &rootBardak_);
	}
	
}


// ------------ method called once each job just after ending the event loop  ------------
void TotoAnalyzer::endJob()
{
	// Trigger Summary Tables
	if(doL1_)
	{
		l1TriggerAnalyzer_ ->copySummary(runInfos_);
	  if(verbosity_>0)
	    {
	      cout << "L1 Trigger Summary Tables" << endl;
	      l1TriggerAnalyzer_->printStats();
	    }
	}
	
	if(doHLT_)
	{
		hltAnalyzer_ ->copySummary(runInfos_);
	  if(verbosity_>0)
	    {
	      cout << "HLT Summary Tables" << endl;
	      hltAnalyzer_->printStats();
	    }
	}
	
	runTree_->Fill();
	
	std::cout << "Total number of events: " << nTotEvt_ << std::endl;
	std::cout << "Closing rootfile " << rootFile_->GetName() << std::endl;
	rootFile_->Write();
	
	rootFile_->Close();
	
	if(doPhotonConversion_) delete conversionLikelihoodCalculator_;
	if(doHLT_) delete hltAnalyzer_;
}



// ------------ method called to for each event  ------------
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
	rootEvent_->setNb(nTotEvt_);
	rootEvent_->setEventId(iEvent.id().event());
	rootEvent_->setRunId(iEvent.id().run());
	rootEvent_->setLuminosityBlock(iEvent.luminosityBlock());
	rootEvent_->setBunchCrossing(iEvent.bunchCrossing());
	rootEvent_->setOrbitNumber(iEvent.orbitNumber());
	rootEvent_->setCollisionTime(iEvent.time().value());
	if( (verbosity_>1) || (verbosity_>0 && nTotEvt_%10==0 && nTotEvt_<=100)  || (verbosity_>0 && nTotEvt_%100==0 && nTotEvt_>100) )
		cout << endl << endl << "####### TotoAnalyzer - " << *rootEvent_  << " #######" << endl;

	
	// L1 Trigger
	if(doL1_)
	{
		if(nTotEvt_==1 && verbosity_>1) cout << endl << "L1TriggerAnalyzer initialization..." << endl;
		if (nTotEvt_==1) l1TriggerAnalyzer_->init(iEvent, iSetup, rootEvent_);
		if(verbosity_>1) cout << endl << "Get L1 Results..." << endl;
		l1TriggerAnalyzer_->process(iEvent, rootEvent_);
	}
	
	// HLT
	rootEvent_->setGlobalHLT(true);
	if(doHLT_)
	{
		if(nTotEvt_==1 && verbosity_>1) cout << endl << "HLTAnalyzer initialization..." << endl;
		if (nTotEvt_==1) hltAnalyzer_->init(iEvent, rootEvent_);
		if(verbosity_>1) cout << endl << "Get HLT Results..." << endl;
		hltAnalyzer_->process(iEvent, rootEvent_);
	}
	//if ( ! rootEvent_->passGlobalHLT() ) return;
	
	
	// MC Info
	if(doMC_)
	{
		if(verbosity_>1) cout << endl << "Analysing MC info..." << endl;
		MCAnalyzer* myMCAnalyzer = new MCAnalyzer(myConfig_, producersNames_);
		myMCAnalyzer->setVerbosity(verbosity_);
		if (drawMCTree_) myMCAnalyzer->drawMCTree(iEvent, iSetup, myConfig_, producersNames_);
		if ( doPDFInfo_ ) myMCAnalyzer->pdfInfo(iEvent, rootEvent_);
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
		delete myMCAnalyzer;
	}
	
	
	// Get Primary Vertices and Beam Spot
	if(doPrimaryVertex_)
	{
		if(verbosity_>1) cout << endl << "Analysing beam spot and primary vertices collection..." << endl;
		VertexAnalyzer* myVertexAnalyzer = new VertexAnalyzer(producersNames_, verbosity_);
		if(doBeamSpot_) myVertexAnalyzer->getBeamSpot(iEvent, rootBeamSpot_);
		myVertexAnalyzer->getVertices(iEvent, rootVertices_);
		myVertexAnalyzer->selectPrimary(rootEvent_, rootVertices_);
		delete myVertexAnalyzer;
	}
	
	
	// Reconstruct Zee Primary Vertices with and without electron pair
	if(doZeePrimaryVertex_)
	{
		if(verbosity_>1) cout << endl << "Reconstruct Zee Primary Vertices with and without electron pair..." << endl;
		ZeeVertexAnalyzer* myZeeVertexAnalyzer = new ZeeVertexAnalyzer(myConfig_, producersNames_, verbosity_);
		myZeeVertexAnalyzer->getVertices(iEvent, iSetup, rootZeeVertices_, rootBardak_);
		delete myZeeVertexAnalyzer;
	}
	
	
	// Tracks
	if(doTrack_)
	{
		if(verbosity_>1) cout << endl << "Analysing tracks collection..." << endl;
		TrackAnalyzer* myTrackAnalyzer = new TrackAnalyzer(producersNames_, verbosity_);
		myTrackAnalyzer->process(iEvent, rootTracks_);
		delete myTrackAnalyzer;
	}
	
	
	// Calo Jet
	if(doJet_)
	{
		if(verbosity_>1) cout << endl << "Analysing jets collection..." << endl;
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
		if(verbosity_>1) cout << endl << "Analysing muons collection..." << endl;
		MuonAnalyzer* myMuonAnalyzer = new MuonAnalyzer(producersNames_, myConfig_, verbosity_);
		if(doPrimaryVertex_) myMuonAnalyzer->initIPCalculator(iEvent, iSetup, rootEvent_, rootBeamSpot_);
		myMuonAnalyzer->process(iEvent, rootBeamSpot_, rootMuons_);
		delete myMuonAnalyzer;
	}
	
	
	// Lazy Tools to calculate Cluster shape variables
	EcalClusterLazyTools* lazyTools = 0;
	if( doElectron_ || doPhoton_ || doCluster_ )
	{
		if(verbosity_>1) cout << endl << "Loading egamma LazyTools..." << endl;
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
				cout << "  ##### ERROR IN  TotoAnalyzer::analyze => CaloGeometryRecord, CaloGeometryRecord or EcalRecHitCollection are missing #####"<<endl;
				throw exception;
			}
			if(verbosity_>1) cout <<  "   ===> CaloGeometryRecord, CaloGeometryRecord or EcalRecHitCollection are missing, skip calculation of cluster shape variables" << endl;
			lazyTools = 0; // FIXME - delete authorized after an exception ?
		}
	}
	
	// Ecal recHits
	if(keepAllEcalRecHits_)
	{
		if(verbosity_>1) cout << endl << "Analysing Ecal recHits collection..." << endl;
		EcalRecHitsAnalyzer* myEcalRecHitsAnalyzer = new EcalRecHitsAnalyzer(producersNames_, verbosity_);
		myEcalRecHitsAnalyzer->process(iEvent, rootEcalRecHits_);
		delete myEcalRecHitsAnalyzer;
	}
	
	// Electrons
	if(doElectron_)
	{
		if(verbosity_>1) cout << endl << "Analysing electrons collection..." << endl;
		ElectronAnalyzer* myElectronAnalyzer = new ElectronAnalyzer(producersNames_, myConfig_, verbosity_);
		if(doPrimaryVertex_) myElectronAnalyzer->initIPCalculator(iEvent, iSetup, rootEvent_, rootBeamSpot_);
		myElectronAnalyzer->process(iEvent, rootBeamSpot_, rootElectrons_, lazyTools);
		delete myElectronAnalyzer;
	}
	
	
	// Photons
	if(doPhoton_)
	{
		if(verbosity_>1) cout << endl << "Analysing photons collection..." << endl;
		PhotonAnalyzer* myPhotonAnalyzer = new PhotonAnalyzer(producersNames_, myConfig_, verbosity_);
		myPhotonAnalyzer->process(iEvent, iSetup, rootEvent_, rootPhotons_, rootConversionTracks_, conversionLikelihoodCalculator_, lazyTools);
		delete myPhotonAnalyzer;
	}
	
	
	// Ecal Clusters
	if(doCluster_)
	{
		if(verbosity_>1) cout << endl << "Analysing BasicClusters collection..." << endl;
		ClusterAnalyzer* myClusterAnalyzer = new ClusterAnalyzer(myConfig_, producersNames_, verbosity_);
		myClusterAnalyzer->process(iEvent, rootEvent_, lazyTools, rootBasicClusters_, "hybridSuperClusters","hybridBarrelBasicClusters", 210);
		myClusterAnalyzer->process(iEvent, rootEvent_, lazyTools, rootBasicClusters_, "multi5x5BasicClusters", "multi5x5EndcapBasicClusters", 320);
		myClusterAnalyzer->process(iEvent, rootEvent_, lazyTools, rootBasicClusters_, "multi5x5BasicClusters", "multi5x5BarrelBasicClusters", 310);
		// For Paolo M. skims:
		//myClusterAnalyzer->process(iEvent, rootEvent_, lazyTools, rootBasicClusters_, "islandBasicClusters", "islandBarrelBasicClusters", 110);
		//myClusterAnalyzer->process(iEvent, rootEvent_, lazyTools, rootBasicClusters_, "islandBasicClustersWeight", "islandBarrelBasicClusters", 410);
		//myClusterAnalyzer->process(iEvent, rootEvent_, lazyTools, rootBasicClusters_, "islandBasicClustersWeight", "islandEndcapBasicClusters", 420);
		
		delete myClusterAnalyzer;
		
		if(verbosity_>1) cout << endl << "Analysing SuperClusters collection..." << endl;
		SuperClusterAnalyzer* mySClusterAnalyzer = new SuperClusterAnalyzer(producersNames_, verbosity_);
		mySClusterAnalyzer->process(iEvent, rootEvent_, rootSuperClusters_, "hybridSuperClusters","",210);
		mySClusterAnalyzer->process(iEvent, rootEvent_, rootSuperClusters_, "correctedHybridSuperClusters","",211);
		mySClusterAnalyzer->process(iEvent, rootEvent_, rootSuperClusters_, "multi5x5SuperClusters","multi5x5EndcapSuperClusters",320);
		mySClusterAnalyzer->process(iEvent, rootEvent_, rootSuperClusters_, "multi5x5SuperClustersWithPreshower","",323);
		mySClusterAnalyzer->process(iEvent, rootEvent_, rootSuperClusters_, "correctedMulti5x5SuperClustersWithPreshower","",322);
		delete mySClusterAnalyzer;
	}
	
	
	if(doCluster_)
	{
		ClusterAssociator* myClusterAssociator = new ClusterAssociator();
		myClusterAssociator->setVerbosity(verbosity_);
		myClusterAssociator->process(rootSuperClusters_, rootBasicClusters_);
		//myClusterAssociator->printSuperClusters(rootSuperClusters_, rootBasicClusters_,0);  // 0 to print all types SC
		delete myClusterAssociator;
	}
	
	
	if(doElectron_ && doCluster_)
	{
		ElectronAssociator* myElectronAssociator = new ElectronAssociator();
		myElectronAssociator->setVerbosity(verbosity_);
		myElectronAssociator->associateSuperCluster(rootElectrons_, rootSuperClusters_);
		if(verbosity_>2) myElectronAssociator->fullPrintElectrons(rootElectrons_,rootSuperClusters_,rootBasicClusters_,0);
		delete myElectronAssociator;
	}
	
	
	if(doPhoton_ && doCluster_)
	{
		PhotonAssociator* myPhotonAssociator = new PhotonAssociator();
		myPhotonAssociator->setVerbosity(verbosity_);
		myPhotonAssociator->associateSuperCluster(rootPhotons_, rootSuperClusters_);
		delete myPhotonAssociator;
	}
	
	
	if(doPhoton_ && doPhotonIsolation_)
	{
		if(verbosity_>1) cout << endl << "Calculating Photon isolation..." << endl;
		
		Float_t ecalIslandIsolation;
		Float_t ecalDoubleConeIsolation;
		Float_t hcalRecHitIsolation;
		Float_t isoTracks;
		Int_t isoNTracks;
		TRootPhoton* localPhoton;
		
		PhotonIsolator* myPhotonIsolator = new PhotonIsolator(&myConfig_, &producersNames_);
		for (int iphoton=0; iphoton<rootPhotons_->GetEntriesFast(); iphoton++)
		{
			localPhoton = (TRootPhoton*)rootPhotons_->At(iphoton);
			
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
			if(verbosity_>4) { cout << "   After isolation - ["<< setw(3) << iphoton << "] "; localPhoton->Print(); cout << endl; }
		}
		delete myPhotonIsolator;
	}
	
	
	if(doPhoton_ && doElectron_ && doCluster_)
	{
		if(verbosity_>1) cout << endl << "Runing Ambiguity Solver..." << endl;
		AmbiguitySolver* myAmbiguitySolver = new AmbiguitySolver(myConfig_, verbosity_);
		myAmbiguitySolver->processElectronsPhotons(rootSuperClusters_, rootElectrons_, rootPhotons_);
		delete myAmbiguitySolver;
	}
	
	
	// Print Photons / SuperClusters / BasicClusters arborescence
	if(doPhoton_)
	{
		PhotonAssociator* myPhotonAssociator = new PhotonAssociator();
		if(verbosity_>2) myPhotonAssociator->fullPrintPhotons(rootPhotons_,rootSuperClusters_,rootBasicClusters_,0);
		delete myPhotonAssociator;
	}
	
	
	// MET
	if(doMET_)
	{
		if(verbosity_>1) cout << endl << "Analysing Missing Et..." << endl;
		METAnalyzer* myMETAnalyzer = new METAnalyzer(producersNames_, myConfig_, verbosity_);
		myMETAnalyzer->process(iEvent, rootMETs_);
		delete myMETAnalyzer;
	}
	
	
	// Associate recoParticles to mcParticles
	if(doMC_)
	{
		// TODO - For the moment, only for PAT format
		if ( dataType_=="PAT")
		{
			MCAssociator* myMCAssociator = new MCAssociator(producersNames_, verbosity_);
			myMCAssociator->init(iEvent, rootMCParticles_);
			if(doPhoton_) myMCAssociator->matchGenParticlesTo(rootPhotons_);
			if(doElectron_) myMCAssociator->matchGenParticlesTo(rootElectrons_);
			if(doMuon_) myMCAssociator->matchGenParticlesTo(rootMuons_);
			if(doMET_) myMCAssociator->matchGenParticlesTo(rootMETs_);
			for(unsigned int i=0; i<nJetsArrays_; ++i)
			{
				if(doJet_) myMCAssociator->matchGenParticlesTo(rootJetsArrays_[i]);
				if(doJet_ && doJetMC_) myMCAssociator->processGenJets(rootGenJets_, rootJetsArrays_[i]);
			}
			if(verbosity_>4) cout << endl << "Printing recoParticles / mcParticles associations... " << endl;
			if(verbosity_>4 && doPhoton_) myMCAssociator->printParticleAssociation(rootPhotons_);
			if(verbosity_>4 && doElectron_) myMCAssociator->printParticleAssociation(rootElectrons_);
			if(verbosity_>4 && doMuon_) myMCAssociator->printParticleAssociation(rootMuons_);
			if(verbosity_>4 && doMET_) myMCAssociator->printParticleAssociation(rootMETs_);
			for(unsigned int i=0; i<nJetsArrays_; ++i)
			{
				if(verbosity_>4 && doJet_) myMCAssociator->printJetAssociation(rootJetsArrays_[i]);
			}
			delete myMCAssociator;
		}
	}
	
	time_t endProcessingTime = time(0);
	rootEvent_->setTotoAnaProcessingTime(endProcessingTime-startProcessingTime);

	if(verbosity_>1) cout << endl << "Filling rootuple..." << endl;
	eventTree_->Fill();
	delete rootEvent_;
	if(verbosity_>1) cout << endl << "Start deleting objects..." << endl;
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
	if(doMuon_) (*rootMuons_).Delete();
	if(doElectron_) (*rootElectrons_).Delete();
	if(doPhoton_) (*rootPhotons_).Delete();
	if(doCluster_) (*rootBasicClusters_).Delete();
	if(doCluster_) (*rootSuperClusters_).Delete();
	if(keepAllEcalRecHits_ || keepClusterizedEcalRecHits_) (*rootEcalRecHits_).Delete();
	if(doPhotonConversion_) (*rootConversionTracks_).Delete();
	if(doMET_) (*rootMETs_).Delete();
	if(doBardak_) delete rootBardak_;
	if(verbosity_>1) cout << endl << "Objects deleted" << endl;
	if(verbosity_>0) cout << endl;
}

