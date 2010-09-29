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
	
   TFile* outputFile = new TFile("histos.root", "RECREATE");

   // Get branches from runTree
   
   TChain *runChain = new TChain("runTree");
	runChain->Add("Test.root");
	
   TBranch* runBranch = 0;
   TRootRun* run = 0;
   runChain->SetBranchAddress("runInfos", &run, &runBranch);
   runChain->SetBranchStatus("runInfos", 1);

   
   // Get branches from eventTree
   
   TChain *eventChain = new TChain("eventTree");
	eventChain->Add("Test.root");
	
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
	eventChain->SetBranchAddress("muons", &muons, &muonsBranch);
	eventChain->SetBranchStatus("muons", 1);
	
	TBranch* electronsBranch = 0;
	TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
	eventChain->SetBranchAddress("gsfElectrons", &electrons, &electronsBranch);
	eventChain->SetBranchStatus("gsfElectrons", 1);
	
	TBranch* photonsBranch = 0;
	TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
	eventChain->SetBranchAddress("photons", &photons, &photonsBranch);
	eventChain->SetBranchStatus("photons", 1);
	
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
	eventChain->SetBranchAddress("met", &met, &metBranch);
	eventChain->SetBranchStatus("met", 1);
	
	TBranch* bardakBranch = 0;
	TRootBardak* bardak = 0;
	eventChain->SetBranchAddress("Bardak", &bardak, &bardakBranch);
	eventChain->SetBranchStatus("Bardak", 1);
	
	if (genParticlesBranch !=0) std::cout << "genParticlesBranch is present" << std::endl;
	if (genParticlesBranch ==0) std::cout << "genParticlesBranch is absent" << std::endl;
	
	
	//unsigned int nTotEvents = (int)eventChain->GetEntries();
	unsigned int nTotEvents = 0;

   cout << "nEvents=" << eventChain->GetEntries() << endl;
   cout << "nRuns=" << runChain->GetEntries() << endl;
   for(unsigned int irun=0; irun<runChain->GetEntries(); irun++)
   {
      runChain->GetEvent(irun);
      std::cout << std::endl << std::endl << "####### TotoAnalyzer - New Run " << run->runNumber() << " #######" << std::endl;
      std::cout << std::endl <<  "PoolSource: " << run->poolSourceName() << std::endl;
      run->printHLTSummary();
   }

   
	for(unsigned int ievt=0; ievt<nTotEvents; ievt++)
	{
		eventChain->GetEvent(ievt);
      //if( (ievt<=10)  || (ievt%10==0 && ievt<=100)  || (ievt%100==0 && ievt<=1000)   || (ievt%1000==0 && ievt>1000)  )
      if( ievt<=100 )
         {
			//std::cout <<"Analyzing "<< ievt << "th event: " << std::endl;
			std::cout << std::endl << std::endl << "####### TotoAnalyzer - ";  event->Print(); std::cout  << " #######" << std::endl;
         event->printHltAcceptNames();
         cout << endl << "   => passGlobalHLT=" << event->passGlobalHLT() << endl;
         cout << "   => HLT_Photon30_Cleaned_L1R decision="<< event->hltAccept("HLT_Photon30_Cleaned_L1R") << endl;
		}
      
      /*
      TRootPhoton* myphoton;
      for (int iphoton=0; iphoton< photons->GetEntriesFast(); iphoton++)
      {
         myphoton = (TRootPhoton*) photons->At(iphoton);
         cout << endl << "[" << iphoton << "] ";  myphoton->Print(); cout << endl;
         TRootSuperCluster* mysc = myphoton->superCluster();
         cout << endl << "   "; mysc->Print(); cout << endl << endl;
         //TRootCluster* mybc = mysc->seedBasicCluster();
         for (int ihit=0; ihit< mysc->nRecHits(); ihit++)
         {
            TRootEcalRecHit* hit = mysc->hitAt(ihit);
            cout << "      [" << ihit << "] "; hit->Print(); cout << "  chi2=" << hit->chi2() << "  severity=" << hit->severity() << "  outOfTimeEnergy=" << hit->outOfTimeEnergy() << "  outOfTimeChi2=" << hit->outOfTimeChi2() <<endl;
         }
      }
         */
	}
}

