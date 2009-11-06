#include <iomanip>

void filter() {

	//gSystem->Load("libPhysics.so");
	//gSystem->Load("libEG.so");
	//gSystem->Load("../src/libToto.so");

	bool doHLT                    = true;
	bool doMC                     = true;
	bool doSignalMuMuGamma        = false;
	bool doSignalTopTop           = false;
	bool doPhotonConversionMC     = false;
	bool doTrack                  = false;
	bool doJet                    = true;
	bool doMuon                   = true;
	bool doElectron               = true;
	bool doPhoton                 = true;
	bool doCluster                = true;
	bool doPhotonIsolation        = true;
	bool doPhotonConversion       = false;
	bool doMET                    = true;

	// Get input file, trees and branches
	TFile* inputFile=new TFile("reco01.root");
	TTree* inputRunTree = (TTree*) inputFile->Get("runTree");
	TTree* inputEventTree = (TTree*) inputFile->Get("eventTree");

	TBranch* run_br = (TBranch *) inputRunTree->GetBranch("runInfos");
	TRootRun* runInfos = 0;
	run_br->SetAddress(&runInfos);
	
	TBranch* event_br = (TBranch *) inputEventTree->GetBranch("Event");
	TRootEvent* event = 0;
	event_br->SetAddress(&event);
		
	if(doMC)
	{
		TBranch* mcParticles_br = (TBranch *) inputEventTree->GetBranch("MCParticles");
		TClonesArray* mcParticles = new TClonesArray("TRootMCParticle", 0);
		mcParticles_br->SetAddress(&mcParticles);
	}

	if(doSignalMuMuGamma)
	{
		TBranch* mcSignalMuMuGamma_br = (TBranch *) inputEventTree->GetBranch("MuMuGamma");
		TRootSignalEvent* mcMuMuGammaEvent = 0;
		mcSignalMuMuGamma_br->SetAddress(&mcMuMuGammaEvent);
	}

	if(doSignalTopTop)
	{
		TBranch* mcTopTopEvent_br = (TBranch *) inputEventTree->GetBranch("rootMCTopTop");
		TRootSignalEvent* mcTopTopEvent = 0;
		mcTopTopEvent_br->SetAddress(&mcTopTopEvent);
	}
	
	if(doPhotonConversionMC)
	{
		TBranch* mcPhotons_br = (TBranch *) inputEventTree->GetBranch("MCPhotons");
		TClonesArray* mcPhotons = new TClonesArray("TRootMCPhoton", 0);
		mcPhotons_br->SetAddress(&mcPhotons);
	}
	
	if(doTrack)
	{
		TBranch* tracks_br = (TBranch *) inputEventTree->GetBranch("Tracks");
		TClonesArray* tracks = new TClonesArray("TRootTrack", 0);
		tracks_br->SetAddress(&tracks);
		
	}

	if(doJet)
	{
		TBranch* jets_br = (TBranch *) inputEventTree->GetBranch("Jets");
		TClonesArray* jets = new TClonesArray("TRootJet", 0);
		jets_br->SetAddress(&jets);
	}

	
	if(doMuon)
	{
		TBranch* muons_br = (TBranch *) inputEventTree->GetBranch("Muons");
		TClonesArray* muons = new TClonesArray("TRootMuon", 0);
		muons_br->SetAddress(&muons);
	}
		
	if(doElectron)
	{

		TBranch* electrons_br = (TBranch *) inputEventTree->GetBranch("Electrons");
		TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
		electrons_br->SetAddress(&electrons);
	}
				
	if(doPhoton)
	{
		TBranch* photons_br = (TBranch *) inputEventTree->GetBranch("Photons");
		TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
		photons_br->SetAddress(&photons);
	}
		
	if(doCluster)
	{
		TBranch* clusters_br = (TBranch *) inputEventTree->GetBranch("BasicClusters");
		TClonesArray* clusters = new TClonesArray("TRootCluster", 0);
		clusters_br->SetAddress(&clusters);
	
		TBranch* superClusters_br = (TBranch *) inputEventTree->GetBranch("SuperClusters");
		TClonesArray* superClusters = new TClonesArray("TRootSuperCluster", 0);
		superClusters_br->SetAddress(&superClusters);
	}
	
	if(doPhotonConversion)
	{
		TBranch* conversions_br = (TBranch *) inputEventTree->GetBranch("ConversionTracks");
		TClonesArray* conversionTracks = new TClonesArray("TRootTrack", 0);
		conversions_br->SetAddress(&conversionTracks);
	}
	
	if(doMET)
	{
		TBranch* met_br = (TBranch *) inputEventTree->GetBranch("MET");
		TClonesArray* met = new TClonesArray("TRootMET", 0);
		met_br->SetAddress(&met);
	}


	// Create output file and copy trees headers
	TFile *outputFile = new TFile("reco01-filtered.root","recreate");
	TTree *outputRunTree = inputRunTree->CloneTree(-1);
	TTree *outputEventTree = inputEventTree->CloneTree(0);


	unsigned int nEvents = (int)inputEventTree->GetEntries();
	//unsigned int nEvents = 2;
	unsigned int nSelected=0;
	
	for(unsigned int ievt=0; ievt<nEvents; ievt++)
	{
		inputEventTree->GetEvent(ievt);
		cout <<"event "<< ievt <<endl;
		cout<<"event->nb()="<<event->nb()<<endl;

		// Put your event selection here...
		int nphotons=0;
		if(doPhoton)
		{
			nphotons=photons->GetEntriesFast();
		}
		if (nphotons<4) continue;
		
		// fill selected event in new rootuple
		outputEventTree->Fill();
		nSelected++;
		
	} // fin boucle sur evts

	cout << nSelected << " selected events out of " << nEvents << endl;
	outputRunTree->AutoSave();
	outputEventTree->AutoSave();
	delete inputFile;
	delete outputFile;
}
