#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TBranch.h"
#include "TChain.h"
#include "TFile.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"
#include "TBits.h"
#include "TMath.h"
#include "TSystem.h"

#include "../interface/TRootBardak.h"
#include "../interface/TRootBeamSpot.h"
#include "../interface/TRootCluster.h"
#include "../interface/TRootDummyEvent.h"
#include "../interface/TRootEcalRecHit.h"
#include "../interface/TRootElectron.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootJet.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootMCPhoton.h"
#include "../interface/TRootMET.h"
#include "../interface/TRootMuon.h"
#include "../interface/TRootParticle.h"
#include "../interface/TRootPhoton.h"
#include "../interface/TRootRun.h"
#include "../interface/TRootSignalEvent.h"
#include "../interface/TRootSuperCluster.h"
#include "../interface/TRootTopTop.h"
#include "../interface/TRootTrack.h"
#include "../interface/TRootVertex.h"

#include <iomanip>
#include <stdio>

int main(int argc, char*argv[])
//int main()
{

	//gSystem->Load("../src/libToto.so");
	
	
	TChain *runChain = new TChain("eventTree");
	runChain->Add("Test.root");
	
	TChain *eventChain = new TChain("eventTree");
	eventChain->Add("Test.root");
	
	TFile* outputFile = new TFile("histos.root", "RECREATE");

	// Get all branches
	TBranch* eventBranch = 0;
	TRootEvent* event = 0;
	eventChain->SetBranchAddress("Event", &event, &eventBranch);
	eventChain->SetBranchStatus("Event", 1);
	
	TBranch* genParticlesBranch = 0;
	TClonesArray* genParticles = new TClonesArray("TRootMCParticle", 0);
	eventChain->SetBranchAddress("MCParticles", &genParticles, &genParticlesBranch);
	eventChain->SetBranchStatus("MCParticles", 1);
	
	TBranch* genJetsBranch = 0;
	TClonesArray* genJets = new TClonesArray("TRootParticle", 0);
	eventChain->SetBranchAddress("genJets", &genJets, &genJetsBranch);
	eventChain->SetBranchStatus("genJets", 1);
	
	TBranch* genMetBranch = 0;
	TClonesArray* genMet = new TClonesArray("TRootParticle", 0);
	eventChain->SetBranchAddress("genMETs", &genMet, &genMetBranch);
	eventChain->SetBranchStatus("genMETs", 1);
	
	TBranch* genMuMuGammaEventBranch = 0;
	TRootSignalEvent* genMuMuGammaEvent = 0;
	eventChain->SetBranchAddress("MuMuGamma", &genMuMuGammaEvent, &genMuMuGammaEventBranch);
	eventChain->SetBranchStatus("MuMuGamma", 1);
	
	TBranch* genTopTopEventBranch = 0;
	TRootSignalEvent* genTopTopEvent = 0;
	eventChain->SetBranchAddress("rootMCTopTop", &genTopTopEvent, &genTopTopEventBranch);
	eventChain->SetBranchStatus("rootMCTopTop", 1);
	
	TBranch* genConvertedPhotonsBranch = 0;
	TClonesArray* genConvertedPhotons = new TClonesArray("TRootMCPhoton", 0);
	eventChain->SetBranchAddress("MCPhotons", &genConvertedPhotons, &genConvertedPhotonsBranch);
	eventChain->SetBranchStatus("MCPhotons", 1);
	
	TBranch* beamSpotBranch = 0;
	TRootBeamSpot* beamSpot = 0;
	eventChain->SetBranchAddress("BeamSpot", &beamSpot, &beamSpotBranch);
	eventChain->SetBranchStatus("BeamSpot", 1);
	
	TBranch* verticesBranch = 0;
	TClonesArray* vertices = new TClonesArray("TRootVertex", 0);
	eventChain->SetBranchAddress("Vertices", &vertices, &verticesBranch);
	eventChain->SetBranchStatus("Vertices", 1);
	
	TBranch* zeeVerticesBranch = 0;
	TClonesArray* zeeVertices = new TClonesArray("TRootVertex", 0);
	eventChain->SetBranchAddress("ZeeVertices", &zeeVertices, &zeeVerticesBranch);
	eventChain->SetBranchStatus("ZeeVertices", 1);
	
	TBranch* tracksBranch = 0;
	TClonesArray* tracks = new TClonesArray("TRootTrack", 0);
	eventChain->SetBranchAddress("Tracks", &tracks, &tracksBranch);
	eventChain->SetBranchStatus("Tracks", 1);
	
	TBranch* jetsBranch = 0;
	TClonesArray* jets = new TClonesArray("TRootJet", 0);
	eventChain->SetBranchAddress("ak5CaloJets", &jets, &jetsBranch);
	eventChain->SetBranchStatus("ak5CaloJets", 1);
	
	TBranch* muonsBranch = 0;
	TClonesArray* muons = new TClonesArray("TRootMuon", 0);
	eventChain->SetBranchAddress("Muons", &muons, &muonsBranch);
	eventChain->SetBranchStatus("Muons", 1);
	
	TBranch* electronsBranch = 0;
	TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
	eventChain->SetBranchAddress("Electrons", &electrons, &electronsBranch);
	eventChain->SetBranchStatus("Electrons", 1);
	
	TBranch* photonsBranch = 0;
	TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
	eventChain->SetBranchAddress("Photons", &photons, &photonsBranch);
	eventChain->SetBranchStatus("Photons", 1);
	
	TBranch* clustersBranch = 0;
	TClonesArray* clusters = new TClonesArray("TRootCluster", 0);
	eventChain->SetBranchAddress("BasicClusters", &clusters, &clustersBranch);
	eventChain->SetBranchStatus("BasicClusters", 1);
	
	TBranch* superClustersBranch = 0;
	TClonesArray* superClusters = new TClonesArray("TRootSuperCluster", 0);
	eventChain->SetBranchAddress("SuperClusters", &superClusters, &superClustersBranch);
	eventChain->SetBranchStatus("SuperClusters", 1);
	
	TBranch* conversionTracksBranch = 0;
	TClonesArray* conversionTracks = new TClonesArray("TRootTrack", 0);
	eventChain->SetBranchAddress("ConversionTracks", &conversionTracks, &conversionTracksBranch);
	eventChain->SetBranchStatus("ConversionTracks", 1);
	
	TBranch* metBranch = 0;
	TClonesArray* met = new TClonesArray("TRootMET", 0);
	eventChain->SetBranchAddress("MET", &met, &metBranch);
	eventChain->SetBranchStatus("MET", 1);
	
	TBranch* bardakBranch = 0;
	TRootBardak* bardak = 0;
	eventChain->SetBranchAddress("Bardak", &bardak, &bardakBranch);
	eventChain->SetBranchStatus("Bardak", 1);
	
	if (genParticlesBranch !=0) std::cout << "genParticlesBranch is present" << std::endl;
	if (genParticlesBranch ==0) std::cout << "genParticlesBranch is absent" << std::endl;
	
	
	unsigned int nTotEvents = (int)eventChain->GetEntries();
	//unsigned int nTotEvents = 10;

	for(unsigned int ievt=0; ievt<nTotEvents; ievt++)
	{
		eventChain->GetEvent(ievt);
		if( (ievt<=10)  || (ievt%10==0 && ievt<=100)  || (ievt%100==0 && ievt<=1000)   || (ievt%1000==0 && ievt>1000)  )
		{
			//std::cout <<"Analyzing "<< ievt << "th event: " << std::endl;
			std::cout << std::endl << std::endl << "####### TotoAnalyzer - ";  event->Print(); std::cout  << " #######" << std::endl;
         event->printHltAcceptNames();
         cout << endl << "   => passGlobalHLT=" << event->passGlobalHLT() << endl;
         cout << "   => HLT_Ele15_SW_L1R decision="<< event->hltAccept("HLT_Ele15_SW_L1R") << endl;
         
		}
	}
}

