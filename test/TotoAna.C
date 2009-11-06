{
#include <iomanip>

	bool isCSA07Soup              = false;
	bool doHLT                    = true;
	bool doMC                     = true;
	bool doJetMC                  = true;
	bool doMETMC                  = true;
	bool doPDFInfo                = true;
	bool doSignalMuMuGamma        = false;
	bool doSignalTopTop           = false;
	bool doPhotonConversionMC     = false;
	bool doBeamSpot               = true;
	bool doPrimaryVertex          = true;
	bool doTrack                  = true;
	bool doJet                    = true;
	bool doMuon                   = true;
	bool doElectron               = true;
	bool doPhoton                 = true;
	bool doCluster                = false;
	bool doMET                    = true;
	bool doPhotonVertexCorrection = false;
	bool doPhotonIsolation        = false;
	bool doPhotonConversion       = false;
	
	//TFile* f=new TFile("InclusiveMuPt15_Sum08_1_2000events.root");
	//TFile* f=new TFile("InclusiveMuPt15_Sum08_1_31191events.root");
	//TFile* f=new TFile("InclusiveMuPt15_Sum08_1_2000events_BEAMSPOT.root");
	//TFile* f=new TFile("InclusiveMuPt15_Sum08_1_31191events_BEAMSPOT.root");
	TFile* f=new TFile("TotoAna.root");
	TTree* runTree = (TTree*) f->Get("runTree");
	TTree* eventTree = (TTree*) f->Get("eventTree");

	TBranch* run_br = (TBranch *) runTree->GetBranch("runInfos");
	TRootRun* runInfos = 0;
	run_br->SetAddress(&runInfos);

	TBranch* event_br = (TBranch *) eventTree->GetBranch("Event");
	TRootEvent* event = 0;
	event_br->SetAddress(&event);
		
	if(doMC)
	{
		TBranch* mcParticles_br = (TBranch *) eventTree->GetBranch("MCParticles");
		TClonesArray* mcParticles = new TClonesArray("TRootMCParticle", 0);
		mcParticles_br->SetAddress(&mcParticles);
	}

	if(doJetMC)
	{
		TBranch* genJets_br = (TBranch *) eventTree->GetBranch("genJets");
		TClonesArray* genJets = new TClonesArray("TRootParticle", 0);
		genJets_br->SetAddress(&genJets);
	}

	if(doMETMC)
	{
		TBranch* genMETs_br = (TBranch *) eventTree->GetBranch("genMETs");
		TClonesArray* genMETs = new TClonesArray("TRootParticle", 0);
		genMETs_br->SetAddress(&genMETs);
	}

	if(doSignalMuMuGamma)
	{
		TBranch* MuMuGamma_br = (TBranch *) eventTree->GetBranch("MuMuGamma");
		TRootSignalEvent* mcMuMuGammaEvent = 0;
		MuMuGamma_br->SetAddress(&mcMuMuGammaEvent);
	}

	if(doSignalTopTop)
	{
		TBranch* mcTopTop_br = (TBranch *) eventTree->GetBranch("rootMCTopTop");
		TClonesArray* mcTopTop = new TClonesArray("TRootTopTop", 0);
		mcTopTop_br->SetAddress(&mcTopTop);
	}

	if(doPhotonConversionMC)
	{
		TBranch* mcPhotons_br = (TBranch *) eventTree->GetBranch("MCPhotons");
		TClonesArray* mcPhotons = new TClonesArray("TRootMCPhoton", 0);
		mcPhotons_br->SetAddress(&mcPhotons);
	}

	if(doBeamSpot)
	{
		TBranch* BeamSpot_br = (TBranch *) eventTree->GetBranch("BeamSpot");
		TRootBeamSpot* beamSpot = 0;
		BeamSpot_br->SetAddress(&beamSpot);
	}

	if(doPrimaryVertex)
	{
		TBranch* vertices_br = (TBranch *) eventTree->GetBranch("Vertices");
		TClonesArray* vertices = new TClonesArray("TRootVertex", 0);
		vertices_br->SetAddress(&vertices);

	}

	if(doTrack)
	{
		TBranch* tracks_br = (TBranch *) eventTree->GetBranch("Tracks");
		TClonesArray* tracks = new TClonesArray("TRootTrack", 0);
		tracks_br->SetAddress(&tracks);

	}

	if(doJet)
	{
		TBranch* jets_br = (TBranch *) eventTree->GetBranch("Jets");
		TClonesArray* jets = new TClonesArray("TRootJet", 0);
		jets_br->SetAddress(&jets);
	}


	if(doMuon)
	{
		TBranch* muons_br = (TBranch *) eventTree->GetBranch("Muons");
		TClonesArray* muons = new TClonesArray("TRootMuon", 0);
		muons_br->SetAddress(&muons);
	}

	if(doElectron)
	{
		TBranch* electrons_br = (TBranch *) eventTree->GetBranch("Electrons");
		TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
		electrons_br->SetAddress(&electrons);
	}

	if(doPhoton)
	{
		TBranch* photons_br = (TBranch *) eventTree->GetBranch("Photons");
		TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
		photons_br->SetAddress(&photons);
	}

	if(doCluster)
	{
		TBranch* clusters_br = (TBranch *) eventTree->GetBranch("BasicClusters");
		TClonesArray* clusters = new TClonesArray("TRootCluster", 0);
		clusters_br->SetAddress(&clusters);

		TBranch* superClusters_br = (TBranch *) eventTree->GetBranch("SuperClusters");
		TClonesArray* superClusters = new TClonesArray("TRootSuperCluster", 0);
		superClusters_br->SetAddress(&superClusters);
	}

	if(doPhotonConversion)
	{
		TBranch* conversions_br = (TBranch *) eventTree->GetBranch("ConversionTracks");
		TClonesArray* conversionTracks = new TClonesArray("TRootTrack", 0);
		conversions_br->SetAddress(&conversionTracks);
	}

	if(doMET)
	{
		TBranch* met_br = (TBranch *) eventTree->GetBranch("MET");
		TClonesArray* met = new TClonesArray("TRootMET", 0);
		met_br->SetAddress(&met);
	}


	cout << "runTree->GetEntries()="<<runTree->GetEntries()<<endl;
	runTree->GetEvent(0);
	
	// Dataset infos
	cout << "Dataset desciption:"<<runInfos->description()<<endl;
	cout << "Dataset xsection:"<<runInfos->xsection()<<endl;

	// HLT Run Summary
	if (doHLT)
	{
		cout << dec << endl;
		cout << "HLT-Report " << "---------- Event  Summary ------------\n";
		cout << "HLT-Report"
				<< " Events total = " << runInfos->nHLTEvents()
				<< "  wasrun = " << runInfos->nHLTWasRun()
				<< "  passed = " << runInfos->nHLTAccept()
				<< "  errors = " << runInfos->nHLTErrors()
				<< "\n";

		cout << endl;
		cout << "HLT-Report " << "---------- HLTrig Summary ------------\n";
		cout << "HLT-Report   HLT Bit#     WasRun     Passed     Errors  Name\n";

		for (unsigned int i=0; i!=runInfos->nHLTPaths(); ++i)
		{
			printf("HLT-Report %10u %10u %10u %10u  ", i, runInfos->hltWasRun(i), runInfos->hltAccept(i), runInfos->hltErrors(i));
			cout << runInfos->hltNames(i) << endl;
		}

		cout << endl;
	}

	TH1F* h1 = new TH1F("vertex_z","vertex_z", 200, -10, 10);
	TH1F* h2 = new TH1F("dsz","dsz", 200, -10, 10);
	TH1F* h3 = new TH1F("d0","d0", 200, -0.4, 0.4);
	TH1F* h4 = new TH1F("3DIP","3DIP", 200, -10, 10);

	TH2F* h11 = new TH2F("dsz_vs_vertexz","dsz_vs_vertexz", 100, -10, 10, 100, -10, 10);
	TH2F* h12 = new TH2F("3DIP_vs_vertexz","3DIP_vs_vertexz", 100, -10, 10, 100, -10, 10);
	TH2F* h13 = new TH2F("d0_vs_phi","d0_vs_phi", 100, -4, 4, 100, -0.4, 0.4);
	TH2F* h14 = new TH2F("d0_vs_vertexz","d0_vs_vertexz", 100, -10, 10, 100, -0.4, 0.4);

	unsigned int nEvents = (int)eventTree->GetEntries();
	//unsigned int nEvents = 2;

	for(unsigned int ievt=0; ievt<nEvents; ievt++)
	{
		eventTree->GetEvent(ievt);
		cout<<"Event #"<<event->nb()<<"  - Number of processed events: "<<ievt+1<<endl;
		if (isCSA07Soup) cout << "CSA07 Soup:  pid=" << event->csa07id() << " - " << event->csa07process() << " - weight=" << event->csa07weight() << endl;

		if (doHLT)
		{
			//for(unsigned int ipath=0; ipath<event->nHLTPaths(); ipath++) cout << "   " << runInfos->hltNames(ipath) << " decision=" << event->trigHLT(ipath) <<endl;
			//for(unsigned int ipath=0; ipath<5; ipath++) cout << "   " << runInfos->hltNames(ipath) << " decision=" << event->trigHLT(ipath) <<endl;
		}

		if(doPrimaryVertex && doMuon)
		{
			TRootVertex* primaryVertex = event->primaryVertex();
			h1->Fill(primaryVertex->z(),1);
			TRootMuon* muon;
			for (int imu=0; imu< muons->GetEntriesFast(); imu++)
			{
				muon = (TRootMuon*) muons->At(imu);
				h2->Fill(muon->dsz(),1);
				h3->Fill(muon->d0(),1);
				h4->Fill(muon->ip3DSignificance(),1);
				h11->Fill(primaryVertex->z(),muon->dsz(),1);
				h12->Fill(primaryVertex->z(),muon->ip3DSignificance(),1);
				h13->Fill(muon->Phi(),muon->d0(),1);
				h14->Fill(primaryVertex->z(),muon->d0(),1);
			}
		}

		/*
		if(doPhoton)
		{
			cout << endl << "Photon list..." << endl;
			TRootPhoton* myphoton;
			for (int iphoton=0; iphoton< photons->GetEntriesFast(); iphoton++)
			{
				myphoton = (TRootPhoton*) photons->At(iphoton);
				cout << "   [" << iphoton << "]"; myphoton->Print(); cout << " nConvTracks=" << myphoton->convNTracks() << endl;
				if (myphoton->convNTracks()>0)
				{
					TRootTrack* convtrack1 = (TRootTrack*) myphoton->convTrack1();
					cout <<"  convtrack1 pt=" << convtrack1->Pt() << endl;
				}
				if (myphoton->superCluster() != 0 )
				{
					TRootSuperCluster* sc = (TRootSuperCluster*) myphoton->superCluster();
					cout << "      first associated SC has  Et=" << sc->Pt() << endl;
				}
				h1->Fill(myphoton->Et(),1);
			}

			if(doCluster)
			{
				cout << endl << "SuperClusters list..." << endl;
				TRootSuperCluster* mySC;
				for (int isc=0; isc< superClusters->GetEntriesFast(); isc++)
				{
					mySC = (TRootSuperCluster*) superClusters->At(isc);
					cout << "  SC[" << isc << "] of type" << mySC->type() << " with Et="<< mySC->Pt();
					if (mySC->isPhoton() )
					{
						TRootPhoton* phot = (TRootPhoton*) mySC->photon();
						cout << " is associated to photon Et=" << phot->Et() << endl;
					}
					else
					{
						cout << " is not a photon" << endl;
					}
				}
			}
		}
		*/


	} // fin boucle sur evts

	gStyle->SetOptStat(1110);

	TH1F* dummy = new TH1F();
	dummy->SetStats(true);
	dummy->SetLineWidth(1);
	dummy->SetLineColor(1);
	dummy->GetXaxis()->SetLabelSize(0.05);
	dummy->GetYaxis()->SetLabelSize(0.05);

	TCanvas *c00  = new TCanvas("c00"," ",1000,800);
	TCanvas *c01  = new TCanvas("c01"," ",1000,800);
	c00->SetFillColor(0);
	c00->SetBorderMode(2);
	c00->Divide(2,2);

	c01->SetFillColor(0);
	c01->SetBorderMode(2);
	c01->Divide(2,2);

	dummy = h1;
	c00->cd(1);
	h1->Draw();
	c00->cd(2);
	h2->Draw();
	c00->cd(3);
	h3->Draw();
	c00->cd(4);
	h4->Draw();

	c01->cd(1);
	h11->Draw();
	c01->cd(2);
	h12->Draw();
	c01->cd(3);
	h13->Draw();
	c01->cd(4);
	h14->Draw();
}
