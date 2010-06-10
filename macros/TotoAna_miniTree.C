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


#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootBardak.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootBeamSpot.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootCluster.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootDummyEvent.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootEcalRecHit.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootElectron.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootEvent.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootJet.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootMCParticle.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootMCPhoton.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootMET.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootMuon.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootParticle.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootPhoton.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootRun.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootSignalEvent.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootSuperCluster.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootTopTop.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootTrack.h"
#include "/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootVertex.h"


//int TotoAna_miniTree(){
int main(){
	gSystem->Load("/sps/cms/morgan/common/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/src/libToto.so");
	
	bool doHLT										= true;
	bool doMC										 = false;
	bool doJetMC									= false;
	bool doMETMC									= false;
	bool doPDFInfo								= true;
	bool doSignalMuMuGamma				= false;
	bool doSignalTopTop					 = false;
	bool doPhotonConversionC			= false;
	bool doBeamSpot							 = true;
	bool doPrimaryVertex					= true;
	bool doZeePrimaryVertex			 = false;
	bool doTrack									= true;
	bool doJet										= false;
	bool doMuon									 = false;
	bool doElectron							 = true;
	bool doPhoton								 = true;
	bool doCluster								= true;
	bool doPhotonConversion			 = true;
	bool doMET										= false;
	bool doBardak								 = false;
	bool doPhotonVertexCorrection = false;
	bool doPhotonIsolation				= true;
	bool doPhotonConversionMC		 = false;

	TString dataset = "DATA";
	TChain *inputEventTree = new TChain("eventTree");
//	inputEventTree->Add("");
//	TFile* OutputRootFile = new TFile("miniTree_.root", "RECREATE");

/*
// ************ DATA
	inputEventTree->Add("/sps/cms/xiaoh/7TeVdata/CMSSW_3_5_8/DATA_MinimumBias_Commissioning10-May6thPDSkim_GOODCOLL-v1_RAW-RECO/DATA_MinimumBias_Commissioning10-May6thPDSkim_GOODCOLL-v1_RAW-RECO_TOTOANA_*root");
	inputEventTree->Add("/sps/cms/xiaoh/7TeVdata/CMSSW_3_5_8/DATA_MinimumBias_Commissioning10-May6thPDSkim_GOODCOLL-v1_RAW-RECO2/DATA_MinimumBias_Commissioning10-May6thPDSkim_GOODCOLL-v1_RAW-RECO_TOTOANA_*root");
	inputEventTree->Add("/sps/cms/xiaoh/7TeVdata/CMSSW_3_5_8/DATA_MinimumBias_Commissioning10-GOODCOLL-v9_RAW-RECO/DATA_MinimumBias_Commissioning10-GOODCOLL-v9_RAW-RECO_TOTOANA_*root");
	inputEventTree->Add("/sps/cms/xiaoh/7TeVdata/CMSSW_3_5_8/DATA_MinimumBias_Commissioning10-GOODCOLL-v9_RAW-RECO2/DATA_MinimumBias_Commissioning10-GOODCOLL-v9_RAW-RECO_TOTOANA_*root");
	TFile* OutputRootFile = new TFile("miniTree_DATA.root", "RECREATE");
//	TFile* OutputRootFile = new TFile("miniTree_DATA_MinimumBias_Commissioning10-May6thPDSkim_GOODCOLL-v1_RAW-RECO.root", "RECREATE");
//	TFile* OutputRootFile = new TFile("miniTree_DATA_MinimumBias_Commissioning10-May6thPDSkim_GOODCOLL-v1_RAW-RECO2.root", "RECREATE");
//	TFile* OutputRootFile = new TFile("miniTree_DATA_MinimumBias_Commissioning10-GOODCOLL-v9_RAW-RECO.root", "RECREATE");
//	TFile* OutputRootFile = new TFile("miniTree_DATA_MinimumBias_Commissioning10-GOODCOLL-v9_RAW-RECO2.root", "RECREATE");

*//*
// ************* MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO
	inputEventTree->Add("/sps/cms/xiaoh/7TeVdata/CMSSW_3_5_8/MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO/MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO_TOTOANA_*root");
	TFile* OutputRootFile = new TFile("miniTree_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root", "RECREATE");
*//*
// ************* MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO
	inputEventTree->Add("/sps/cms/xiaoh/7TeVdata/CMSSW_3_5_8/MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO/MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO_TOTOANA_*root");
	TFile* OutputRootFile = new TFile("miniTree_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root", "RECREATE");
*//*
// ************* MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_GEN-SIM-RECO
	inputEventTree->Add("/sps/cms/xiaoh/7TeVdata/CMSSW_3_5_8/MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_GEN-SIM-RECO/MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO_TOTOANA_*root");
	TFile* OutputRootFile = new TFile("miniTree_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root", "RECREATE");
*/
// ************* MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO
	inputEventTree->Add("/sps/cms/xiaoh/7TeVdata/CMSSW_3_5_8/MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO/MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO_TOTOANA_*root");
	TFile* OutputRootFile = new TFile("miniTree_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root", "RECREATE");

	
	TBranch* event_br = 0;
	TRootEvent* event = 0;
	inputEventTree->SetBranchAddress("Event", &event, &event_br);
	inputEventTree->SetBranchStatus("Event", 1);
	
	TBranch* mcParticles_br = 0;
	TClonesArray* mcParticles = new TClonesArray("TRootMCParticle", 0);
	if(doMC)
	{
		inputEventTree->SetBranchAddress("MCParticles", &mcParticles, &mcParticles_br);
		inputEventTree->SetBranchStatus("MCParticles", 1);
	}
	
	TBranch* genJets_br = 0;
	TClonesArray* genJets = new TClonesArray("TRootParticle", 0);
	if(doJetMC)
	{
		inputEventTree->SetBranchAddress("genJets", &genJets, &genJets_br);
		inputEventTree->SetBranchStatus("genJets", 1);
	}
	
	TBranch* genMETs_br = 0;
	TClonesArray* genMETs = new TClonesArray("TRootParticle", 0);
	if(doMETMC)
	{
		inputEventTree->SetBranchAddress("genMETs", &genMETs, &genMETs_br);
		inputEventTree->SetBranchStatus("genMETs", 1);
	}
	
	TBranch* mcSignalMuMuGamma_br = 0;
	TRootSignalEvent* mcMuMuGammaEvent = 0;
	if(doSignalMuMuGamma)
	{
		inputEventTree->SetBranchAddress("MuMuGamma", &mcMuMuGammaEvent, &mcSignalMuMuGamma_br);
		inputEventTree->SetBranchStatus("MuMuGamma", 1);
	}
	
	TBranch* mcTopTopEvent_br = 0;
	TRootSignalEvent* mcTopTopEvent = 0;
	if(doSignalTopTop)
	{
		inputEventTree->SetBranchAddress("rootMCTopTop", &mcTopTopEvent, &mcTopTopEvent_br);
		inputEventTree->SetBranchStatus("rootMCTopTop", 1);
	}
	
	TBranch* mcPhotons_br = 0;
	TClonesArray* mcPhotons = new TClonesArray("TRootMCPhoton", 0);
	if(doPhotonConversionMC)
	{
		inputEventTree->SetBranchAddress("MCPhotons", &mcPhotons, &mcPhotons_br);
		inputEventTree->SetBranchStatus("MCPhotons", 1);
	}
	
	TBranch* beamSpot_br = 0;
	TRootBeamSpot* beamSpot = 0;
	if(doBeamSpot)
	{
		inputEventTree->SetBranchAddress("BeamSpot", &beamSpot, &beamSpot_br);
		inputEventTree->SetBranchStatus("BeamSpot", 1);
	}
	
	TBranch* vertices_br = 0;
	TClonesArray* vertices = new TClonesArray("TRootVertex", 0);
	if(doPrimaryVertex)
	{
		inputEventTree->SetBranchAddress("Vertices", &vertices, &vertices_br);
		inputEventTree->SetBranchStatus("Vertices", 1);
	}
	
	TBranch* zeeVertices_br = 0;
	TClonesArray* zeeVertices = new TClonesArray("TRootVertex", 0);
	if(doZeePrimaryVertex)
	{
		inputEventTree->SetBranchAddress("ZeeVertices", &zeeVertices, &zeeVertices_br);
		inputEventTree->SetBranchStatus("ZeeVertices", 1);
	}
	
	TBranch* tracks_br = 0;
	TClonesArray* tracks = new TClonesArray("TRootTrack", 0);
	if(doTrack)
	{
		inputEventTree->SetBranchAddress("Tracks", &tracks, &tracks_br);
		inputEventTree->SetBranchStatus("Tracks", 1);
	}
	
	TBranch* jets_br = 0;
	TClonesArray* jets = new TClonesArray("TRootJet", 0);
	if(doJet)	{
		inputEventTree->SetBranchAddress("Jets", &jets, &jets_br);
		inputEventTree->SetBranchStatus("Jets", 1);
	}
	
	TBranch* muons_br = 0;
	TClonesArray* muons = new TClonesArray("TRootMuon", 0);
	if(doMuon)
	{
		inputEventTree->SetBranchAddress("Muons", &muons, &muons_br);
		inputEventTree->SetBranchStatus("Muons", 1);
	}
	
	TBranch* electrons_br = 0;
	TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
	if(doElectron)
	{
		inputEventTree->SetBranchAddress("Electrons", &electrons, &electrons_br);
		inputEventTree->SetBranchStatus("Electrons", 1);
	}
	
	TBranch* photons_br = 0;
	TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
	if(doPhoton)
	{
		inputEventTree->SetBranchAddress("Photons", &photons, &photons_br);
		inputEventTree->SetBranchStatus("Photons", 1);
	}
	
	TBranch* clusters_br = 0;
	TClonesArray* clusters = new TClonesArray("TRootCluster", 0);
	if(doCluster)
	{
		inputEventTree->SetBranchAddress("BasicClusters", &clusters, &clusters_br);
		inputEventTree->SetBranchStatus("BasicClusters", 1);
	}
	
	TBranch* superClusters_br = 0;
	TClonesArray* superClusters = new TClonesArray("TRootSuperCluster", 0);
	if(doCluster)
	{
		inputEventTree->SetBranchAddress("SuperClusters", &superClusters, &superClusters_br);
		inputEventTree->SetBranchStatus("SuperClusters", 1);
	}

	TBranch* conversions_br = 0;
	TClonesArray* conversionTracks = new TClonesArray("TRootTrack", 0);
	if(doPhotonConversion)
	{
		inputEventTree->SetBranchAddress("ConversionTracks", &conversionTracks, &conversions_br);
		inputEventTree->SetBranchStatus("ConversionTracks", 1);
	}
	
	TBranch* met_br = 0;
	TClonesArray* met = new TClonesArray("TRootMET", 0);
	if(doMET)
	{
		inputEventTree->SetBranchAddress("MET", &met, &met_br);
		inputEventTree->SetBranchStatus("MET", 1);
	}
	
	TBranch* bardak_br = 0;
	TRootBardak* bardak = 0;
	if(doBardak)
	{
		inputEventTree->SetBranchAddress("bardak", &bardak, &bardak_br);
		inputEventTree->SetBranchStatus("bardak", 1);
	}
	
	
	//cout << "runTree->GetEntries()="<<runTree->GetEntries()<<endl;MinimumBias__BeamCommissioning09-BSCNOBEAMHALO-Dec19thSkim_336p3_v1__TOTOANA_1.root
	//runTree->GetEvent(0);
	
	// Dataset infos
	//cout << "Dataset desciption:"<<runInfos->description()<<endl;
	//cout << "Dataset xsection:"<<runInfos->xsection()<<endl;
	
	// HLT Run Summary
	/*
	if (doHLT)
	{
		cout << dec << endl;
		cout << "HLT-Report " << "---------- Event	Summary ------------\n";
		cout << "HLT-Report"
		<< " Events total = " << runInfos->nHLTEvents()
		<< "	wasrun = " << runInfos->nHLTWasRun()
		<< "	passed = " << runInfos->nHLTAccept()
		<< "	errors = " << runInfos->nHLTErrors()
		<< "\n";
		
		cout << endl;
		cout << "HLT-Report " << "---------- HLTrig Summary ------------\n";
		cout << "HLT-Report	 HLT Bit#		 WasRun		 Passed		 Errors	Name\n";
		
		for (unsigned int i=0; i!=runInfos->nHLTPaths(); ++i)
		{
			printf("HLT-Report %10u %10u %10u %10u	", i, runInfos->hltWasRun(i), runInfos->hltAccept(i), runInfos->hltErrors(i));
			cout << runInfos->hltNames(i) << endl;
}

cout << endl;
}
*/

	Int_t Photon_iEvent;
	Int_t Photon_isEBorEE, Photon_isEB, Photon_isEE, Photon_isEEP, Photon_isEEM;
	Int_t Photon_isAfterCut0, Photon_isAfterCut1, Photon_isAfterCut2, Photon_isAfterCut3, Photon_isAfterCut4, Photon_isAfterCut5, Photon_isAfterCut6, Photon_isAfterCut7;

	Int_t /*Photon_Multiplicity,*/ Photon_hasPixelSeed, Photon_isAlsoElectron, Photon_Nclusters, Photon_nBasicClusters, Photon_nXtals;
	Int_t Photon_isTightPhoton, Photon_isLoosePhoton;
	Int_t Photon_convNTracks, Photon_isoNTracksSolidCone, Photon_isoNTracksHollowCone, Photon_isolationPersoNTracksSolidCone;
	Float_t Photon_Eta, Photon_Phi;
	Float_t Photon_SCEta, Photon_SCPhi, Photon_SCEnergy, Photon_SCEt, Photon_SCRawEnergy, Photon_SCRawEt;
	Float_t Photon_E, Photon_Et, Photon_E2x2, Photon_E3x3, Photon_E5x5, Photon_Emax, Photon_E2nd;
	Float_t Photon_r19, Photon_r9, Photon_cross;
	Float_t Photon_caloConeSize, Photon_PreshEnergy, Photon_HoE, Photon_covIetaIeta, Photon_covIphiIphi, Photon_etaWidth, Photon_phiWidth;
	Float_t Photon_isoEcalRecHit, Photon_isoHcalRecHit, Photon_isoSolidTrkCone, Photon_isoHollowTrkCone, Photon_isoPersoSolidTrkCone, Photon_isolationPersoTracksSolidCone;
	Float_t Photon_s4;
	Float_t Photon_seedTime;
	Int_t Photon_seedFlag, Photon_seedSeverity;
 
//Déclaration des variables pour les SuperClusters
	Float_t SuperClu_E, SuperClu_Et, SuperClu_Eta, SuperClu_Phi, SuperClu_RawE, SuperClu_RawEt;
	Float_t SuperClu_seedTime;
	Float_t SuperClu_s4, SuperClu_etaWidth, SuperClu_phiWidth;
	Int_t SuperClu_seedFlag, SuperClu_seedSeverity;
	Int_t SuperClu_nXtals, SuperClu_nBasicClusters;
	Int_t SuperClu_isEE, SuperClu_isEB, SuperClu_isEEM, SuperClu_isEEP;

//Déclaration des variables par event
	Int_t Photon_Multiplicity, SuperClu_Multiplicity;
	Int_t nPhotonEEP_perEvent, nPhotonEEM_perEvent, nPhotonEE_perEvent, nPhotonEB_perEvent;

	Int_t HLT_Photon10_L1R, HLT_Photon15_L1R, HLT_Photon15_LooseEcalIso_L1R, HLT_Photon20_L1R, HLT_Photon30_L1R_8E29;
	Int_t HLT_DoublePhoton4_Jpsi_L1R, HLT_DoublePhoton4_Upsilon_L1R, HLT_DoublePhoton4_eeRes_L1R, HLT_DoublePhoton5_eeRes_L1R, HLT_DoublePhoton5_Jpsi_L1R;
	Int_t HLT_DoublePhoton5_Upsilon_L1R, HLT_DoublePhoton5_L1R, HLT_DoublePhoton10_L1R, HLT_DoubleEle5_SW_L1R, HLT_Ele20_LW_L1R;
	Int_t HLT_Ele15_SiStrip_L1R, HLT_Ele15_SC10_LW_L1R, HLT_Ele15_LW_L1R, HLT_Ele10_LW_EleId_L1R, HLT_Ele10_LW_L1R; 
	Int_t HLT_Photon15_TrackIso_L1R;
	Int_t NoCuts, SuperClu_isAfterCut1, SuperClu_isAfterCut2, SuperClu_isAfterCut3;

	TTree* miniTree = new TTree("miniTree","Photons info");	
	TTree* miniSuperClu = new TTree("miniSuperClu", "Super Clusters");
	TTree* miniEvent = new TTree("miniEvents", "Events");

	miniTree->Branch("Photon_iEvent", &Photon_iEvent, "Photon_iEvent/I");
	miniTree->Branch("Photon_isEBorEE", &Photon_isEBorEE, "Photon_isEBorEE/I");
	miniTree->Branch("Photon_isEB", &Photon_isEB, "Photon_isEB/I");
	miniTree->Branch("Photon_isEE", &Photon_isEE, "Photon_isEE/I");
	miniTree->Branch("Photon_isEEP", &Photon_isEEP, "Photon_isEEP/I");
	miniTree->Branch("Photon_isEEM", &Photon_isEEM, "Photon_isEEM/I");

	miniTree->Branch("Photon_isAfterCut0,", &Photon_isAfterCut0, "Photon_isAfterCut0/I");
	miniTree->Branch("Photon_isAfterCut1,", &Photon_isAfterCut1, "Photon_isAfterCut1/I");
	miniTree->Branch("Photon_isAfterCut2,", &Photon_isAfterCut2, "Photon_isAfterCut2/I");
	miniTree->Branch("Photon_isAfterCut3,", &Photon_isAfterCut3, "Photon_isAfterCut3/I");
	miniTree->Branch("Photon_isAfterCut4,", &Photon_isAfterCut4, "Photon_isAfterCut4/I");
	miniTree->Branch("Photon_isAfterCut5,", &Photon_isAfterCut5, "Photon_isAfterCut5/I");
	miniTree->Branch("Photon_isAfterCut6,", &Photon_isAfterCut6, "Photon_isAfterCut6/I");
	miniTree->Branch("Photon_isAfterCut7,", &Photon_isAfterCut7, "Photon_isAfterCut7/I");

//	miniTree->Branch("Photon_Multiplicity", &Photon_Multiplicity, "Photon_Multiplicity/I");
	miniTree->Branch("Photon_hasPixelSeed", &Photon_hasPixelSeed, "Photon_hasPixelSeed/I");
	miniTree->Branch("Photon_isAlsoElectron", &Photon_isAlsoElectron, "Photon_isAlsoElectron/I");
	miniTree->Branch("Photon_Nclusters", &Photon_Nclusters, "Photon_Nclusters/I");
	miniTree->Branch("Photon_nBasicClusters", &Photon_nBasicClusters, "Photon_nBasicClusters/I");
	miniTree->Branch("Photon_nXtals", &Photon_nXtals, "Photon_nXtals/I"); // Variable not filled in current version

	miniTree->Branch("Photon_isTightPhoton", &Photon_isTightPhoton, "Photon_isTightPhoton/I");
	miniTree->Branch("Photon_isLoosePhoton", &Photon_isLoosePhoton, "Photon_isLoosePhoton/I");

	miniTree->Branch("Photon_Eta", &Photon_Eta, "Photon_Eta/F");
	miniTree->Branch("Photon_Phi", &Photon_Phi, "Photon_Phi/F");

	miniTree->Branch("Photon_SCEta", &Photon_SCEta, "Photon_SCEta/F");
	miniTree->Branch("Photon_SCPhi", &Photon_SCPhi, "Photon_SCPhi/F");
	miniTree->Branch("Photon_SCEnergy", &Photon_SCEnergy, "Photon_SCEnergy/F");
	miniTree->Branch("Photon_SCEt", &Photon_SCEt, "Photon_SCEt/F");
	miniTree->Branch("Photon_SCRawEnergy", &Photon_SCRawEnergy, "Photon_SCRawEnergy/F");
	miniTree->Branch("Photon_SCRawEt", &Photon_SCRawEt, "Photon_SCRawEt/F");

	miniTree->Branch("Photon_E", &Photon_E, "Photon_E/F");
	miniTree->Branch("Photon_Et", &Photon_Et, "Photon_Et/F");
	miniTree->Branch("Photon_E2x2", &Photon_E2x2, "Photon_E2x2/F");
	miniTree->Branch("Photon_E3x3", &Photon_E3x3, "Photon_E3x3/F");
	miniTree->Branch("Photon_E5x5", &Photon_E5x5, "Photon_E5x5/F");
	miniTree->Branch("Photon_Emax", &Photon_Emax, "Photon_Emax/F");
	miniTree->Branch("Photon_E2nd", &Photon_E2nd, "Photon_E2nd/F");

	miniTree->Branch("Photon_r19", &Photon_r19, "Photon_r19/F");
	miniTree->Branch("Photon_r9", &Photon_r9, "Photon_r9/F");
	miniTree->Branch("Photon_cross", &Photon_cross, "Photon_cross/F");

	miniTree->Branch("Photon_caloConeSize", &Photon_caloConeSize, "Photon_caloConeSize/F");
	miniTree->Branch("Photon_PreshEnergy", &Photon_PreshEnergy, "Photon_PreshEnergy/F");
	miniTree->Branch("Photon_HoE", &Photon_HoE, "Photon_HoE/F");
	miniTree->Branch("Photon_covIetaIeta", &Photon_covIetaIeta, "Photon_covIetaIeta/F");
	miniTree->Branch("Photon_covIphiIphi", &Photon_covIphiIphi, "Photon_covIphiIphi/F");
	miniTree->Branch("Photon_convNTracks", &Photon_convNTracks, "Photon_convNTracks/I");
	miniTree->Branch("Photon_etaWidth", &Photon_etaWidth, "Photon_etaWidth/F");
	miniTree->Branch("Photon_phiWidth", &Photon_phiWidth, "Photon_phiWidth/F");

	miniTree->Branch("Photon_isoEcalRecHit", &Photon_isoEcalRecHit, "Photon_isoEcalRecHit/F");
	miniTree->Branch("Photon_isoHcalRecHit", &Photon_isoHcalRecHit, "Photon_isoHcalRecHit/F");
	miniTree->Branch("Photon_isoSolidTrkCone", &Photon_isoSolidTrkCone, "Photon_isoSolidTrkCone/F");
	miniTree->Branch("Photon_isoHollowTrkCone", &Photon_isoHollowTrkCone, "Photon_isoHollowTrkCone/F");
	miniTree->Branch("Photon_isoNTracksSolidCone", &Photon_isoNTracksSolidCone, "Photon_isoNTracksSolidCone/I");
	miniTree->Branch("Photon_isoNTracksHollowCone", &Photon_isoNTracksHollowCone, "Photon_isoNTracksHollowCone/I");
	miniTree->Branch("Photon_isoPersoSolidTrkCone", &Photon_isoPersoSolidTrkCone, "Photon_isoPersoSolidTrkCone/F");
	miniTree->Branch("Photon_isolationPersoTracksSolidCone", &Photon_isolationPersoTracksSolidCone, "Photon_isolationPersoTracksSolidCone/F");
	miniTree->Branch("Photon_isolationPersoNTracksSolidCone", &Photon_isolationPersoNTracksSolidCone, "Photon_isolationPersoNTracksSolidCone/I");

	miniTree->Branch("Photon_s4", &Photon_s4, "Photon_s4/F");
	miniTree->Branch("Photon_seedTime", &Photon_seedTime, "Photon_seedTime/F");
	miniTree->Branch("Photon_seedFlag", &Photon_seedFlag, "Photon_seedFlag/I");
	miniTree->Branch("Photon_seedSeverity", &Photon_seedSeverity, "Photon_seedSeverity/I");

// Création de toutes les branches nécessaires aux variables pour les super clusters(cf ci dessous)
//	miniSuperClu->Branch("SuperClu_", &SuperClu_, "SuperClu_/F");


	miniSuperClu->Branch("SuperClu_seedTime", &SuperClu_seedTime, "SuperClu_seedTime/F");
	miniSuperClu->Branch("SuperClu_seedFlag", &SuperClu_seedFlag, "SuperClu_seedFlag/I");
	miniSuperClu->Branch("SuperClu_seedSeverity", &SuperClu_seedSeverity, "SuperClu_seedSeverity/I");

	miniSuperClu->Branch("SuperClu_s4", &SuperClu_s4, "SuperClu_s4/F");
	miniSuperClu->Branch("SuperClu_phiWidth", &SuperClu_phiWidth, "SuperClu_phiWidth/F");
	miniSuperClu->Branch("SuperClu_etaWidth", &SuperClu_etaWidth, "SuperClu_etaWidth/F");

	miniSuperClu->Branch("SuperClu_E", &SuperClu_E, "SuperClu_E/F");
	miniSuperClu->Branch("SuperClu_Et", &SuperClu_Et, "SuperClu_Et/F");
	miniSuperClu->Branch("SuperClu_Eta", &SuperClu_Eta, "SuperClu_Eta/F");
	miniSuperClu->Branch("SuperClu_Phi", &SuperClu_Phi, "SuperClu_Phi/F");
	miniSuperClu->Branch("SuperClu_nXtals", &SuperClu_nXtals, "SuperClu_nXtals/I");
	miniSuperClu->Branch("SuperClu_nBasicClusters", &SuperClu_nBasicClusters, "SuperClu_nBasicClusters/I");
	miniSuperClu->Branch("SuperClu_RawE", &SuperClu_RawE, "SuperClu_RawE/F");
	miniSuperClu->Branch("SuperClu_RawEt", &SuperClu_RawEt, "SuperClu_RawEt/F");

	miniSuperClu->Branch("SuperClu_isEE", &SuperClu_isEE, "SuperClu_isEE/I");
	miniSuperClu->Branch("SuperClu_isEB", &SuperClu_isEB, "SuperClu_isEB/I");
	miniSuperClu->Branch("SuperClu_isEEM", &SuperClu_isEEM, "SuperClu_isEEM/I");
	miniSuperClu->Branch("SuperClu_isEEP", &SuperClu_isEEP, "SuperClu_isEEP/I");

	miniSuperClu->Branch("NoCuts", &NoCuts, "NoCuts/I");
	miniSuperClu->Branch("SuperClu_isAfterCut1", &SuperClu_isAfterCut1, "SuperClu_isAfterCut1/I");
	miniSuperClu->Branch("SuperClu_isAfterCut2", &SuperClu_isAfterCut2, "SuperClu_isAfterCut2/I");
	miniSuperClu->Branch("SuperClu_isAfterCut3", &SuperClu_isAfterCut3, "SuperClu_isAfterCut3/I");

//Branches du tree par event
	miniEvent->Branch("NoCuts", &NoCuts, "NoCuts/I");

	miniEvent->Branch("Photon_Multiplicity", &Photon_Multiplicity, "Photon_Multiplicity/I");
	miniEvent->Branch("SuperClu_Multiplicity", &SuperClu_Multiplicity, "SuperClu_Multiplicity/I");

	miniEvent->Branch("nPhotonEEM_perEvent", &nPhotonEEP_perEvent, "nPhotonEEM_perEvent/I");
	miniEvent->Branch("nPhotonEEP_perEvent", &nPhotonEEM_perEvent, "nPhotonEEP_perEvent/I");
	miniEvent->Branch("nPhotonEE_perEvent", &nPhotonEE_perEvent, "nPhotonEE_perEvent/I");
	miniEvent->Branch("nPhotonEB_perEvent", &nPhotonEB_perEvent, "nPhotonEB_perEvent/I");


	miniEvent->Branch("HLT_Photon10_L1R", &HLT_Photon10_L1R,"HLT_Photon10_L1R/I");
	miniEvent->Branch("HLT_Photon15_L1R", &HLT_Photon15_L1R,"HLT_Photon15_L1R/I");
	miniEvent->Branch("HLT_Photon15_LooseEcalIso_L1R", &HLT_Photon15_LooseEcalIso_L1R,"HLT_Photon15_LooseEcalIso_L1R/I");
	miniEvent->Branch("HLT_Photon20_L1R", &HLT_Photon20_L1R,"HLT_Photon20_L1R/I");
	miniEvent->Branch("HLT_Photon30_L1R_8E29", &HLT_Photon30_L1R_8E29,"HLT_Photon30_L1R_8E29/I");

	miniEvent->Branch("HLT_DoublePhoton4_Jpsi_L1R", &HLT_DoublePhoton4_Jpsi_L1R,"HLT_DoublePhoton4_Jpsi_L1R/I");
	miniEvent->Branch("HLT_DoublePhoton4_Upsilon_L1R", &HLT_DoublePhoton4_Upsilon_L1R,"HLT_DoublePhoton4_Upsilon_L1R/I");
	miniEvent->Branch("HLT_DoublePhoton4_eeRes_L1R", &HLT_DoublePhoton4_eeRes_L1R,"HLT_DoublePhoton4_eeRes_L1R/I");
	miniEvent->Branch("HLT_DoublePhoton5_eeRes_L1R", &HLT_DoublePhoton5_eeRes_L1R,"HLT_DoublePhoton5_eeRes_L1R/I");
	miniEvent->Branch("HLT_DoublePhoton5_Jpsi_L1R", &HLT_DoublePhoton5_Jpsi_L1R,"HLT_DoublePhoton5_Jpsi_L1R/I");

	miniEvent->Branch("HLT_DoublePhoton5_Upsilon_L1R", &HLT_DoublePhoton5_Upsilon_L1R,"HLT_DoublePhoton5_Upsilon_L1R/I");
	miniEvent->Branch("HLT_DoublePhoton5_L1R", &HLT_DoublePhoton5_L1R,"HLT_DoublePhoton5_L1R/I");
	miniEvent->Branch("HLT_DoublePhoton10_L1R", &HLT_DoublePhoton10_L1R,"HLT_DoublePhoton10_L1R/I");
	miniEvent->Branch("HLT_DoubleEle5_SW_L1R", &HLT_DoubleEle5_SW_L1R,"HLT_DoubleEle5_SW_L1R/I");
	miniEvent->Branch("HLT_Ele20_LW_L1R", &HLT_Ele20_LW_L1R,"HLT_Ele20_LW_L1R/I");

	miniEvent->Branch("HLT_Ele15_SiStrip_L1R", &HLT_Ele15_SiStrip_L1R,"HLT_Ele15_SiStrip_L1R/I");
	miniEvent->Branch("HLT_Ele15_SC10_LW_L1R", &HLT_Ele15_SC10_LW_L1R,"HLT_Ele15_SC10_LW_L1R/I");
	miniEvent->Branch("HLT_Ele15_LW_L1R", &HLT_Ele15_LW_L1R,"HLT_Ele15_LW_L1R/I");
	miniEvent->Branch("HLT_Ele10_LW_EleId_L1R", &HLT_Ele10_LW_EleId_L1R,"HLT_Ele10_LW_EleId_L1R/I");
	miniEvent->Branch("HLT_Ele10_LW_L1R", &HLT_Ele10_LW_L1R,"HLT_Ele10_LW_L1R/I");

	miniEvent->Branch("HLT_Photon15_TrackIso_L1R", &HLT_Photon15_TrackIso_L1R,"HLT_Photon15_TrackIso_L1R/I");


	unsigned int nTotEvents = (int)inputEventTree->GetEntries();
	//unsigned int nTotEvents = 1000;
	unsigned int nTotEventsSelectedRuns = 0;
	unsigned int nTotEventsSelectedL1 = 0;	
	unsigned int nTotEventsSelectedVertex = 0;
	unsigned int nSelectedEvents = 0;
	unsigned int nEventsWithScHigherThan2GeV = 0;
	unsigned int nTotPhotons = 0;
	unsigned int nSelectedPhotons = 0;
	unsigned int nCut1 = 0;
	unsigned int nCut2 = 0;
	unsigned int nCut3 = 0;
	unsigned int nCut4 = 0;
	unsigned int nCut5 = 0;
	unsigned int nCut6 = 0;
	unsigned int nCut7 = 0;

	unsigned int nTotSC = 0;
	unsigned int nSelectedSC = 0;
	unsigned int nSCAfterCut1 = 0;
	unsigned int nSCAfterCut2 = 0;
	unsigned int nSCAfterCut3 = 0;

	cout<<"Nb of events : "<<nTotEvents<<endl;

	for(unsigned int ievt=0; ievt<nTotEvents; ievt++)
	{
		int nprint = (int)((double)nTotEvents/(double)100.0);
		if( (ievt % nprint)==0 ){ cout<< ievt <<" events done over "<<nTotEvents<<" ( "<<ceil((double)ievt/(double)nTotEvents*100)<<" \% )"<<endl; }
		NoCuts = 1;
		SuperClu_isAfterCut1 = 0;
		SuperClu_isAfterCut2 = 0;
		SuperClu_isAfterCut3 = 0;

		Photon_iEvent = ievt;
		inputEventTree->GetEvent(ievt);

		nPhotonEEP_perEvent = 0 ;
		nPhotonEEM_perEvent = 0 ;
		nPhotonEE_perEvent = 0 ;
		nPhotonEB_perEvent = 0 ;

		SuperClu_E = -99;
		SuperClu_Et = -99;
		SuperClu_Eta = -99;
		SuperClu_Phi = -99;
		SuperClu_RawE = -99;
		SuperClu_RawEt = -99;

		SuperClu_isEEP =-99;
		SuperClu_isEEM = -99;
		SuperClu_isEB = -99;
		SuperClu_isEE = -99;

		SuperClu_nXtals = -99;
		SuperClu_nBasicClusters = -99;
		SuperClu_seedFlag = -99;
		SuperClu_seedSeverity = -99;
		SuperClu_seedTime = -99;
		SuperClu_s4 = -99;
		SuperClu_phiWidth = -99;
		SuperClu_etaWidth = -99;

		// Tri sur le runId
		//if (!(event->runId() ==133928)) continue;

		nTotEventsSelectedRuns++;
		nTotEventsSelectedL1++;
		nTotEventsSelectedVertex++;

		// Count nb of evts with at least one SC with rawEt>2 GeV (for Eiko)
		Bool_t atLeastOneSChigherThan2GeV = false;
		TRootSuperCluster* mysc;
		SuperClu_Multiplicity = superClusters->GetEntriesFast();
		nTotSC += superClusters->GetEntriesFast();
		if (SuperClu_Multiplicity == 0) {miniSuperClu->Fill(); continue;}
		for (int isc=0; isc < SuperClu_Multiplicity; isc++)
		{
			mysc = (TRootSuperCluster*) superClusters->At(isc);
			if ( ! ( mysc->type()==211 || mysc->type()==322 ) ) continue;
			Float_t rawEt = mysc->rawEnergy() * sin(mysc->Theta());
			if (rawEt>2.0) atLeastOneSChigherThan2GeV = true;

			// Remplir les données sur superclu : E ,Et, Eta, Phi, nXtals, is EE/EB/EEM/EEP, seedTime, seedFlag, ... flagSRP?,

			SuperClu_E = mysc->Mag();
			SuperClu_Et = SuperClu_E*sin(mysc->Theta());
			SuperClu_Eta = mysc->Eta();
			SuperClu_Phi = mysc->Phi();
			SuperClu_RawE = mysc->rawEnergy();
			SuperClu_RawEt = SuperClu_RawE * sin (mysc->Theta());

			SuperClu_isEB = mysc->isEB();
			SuperClu_isEE = mysc->isEE();
			if( (SuperClu_isEE==1) && (SuperClu_Eta>0) ) SuperClu_isEEP =1; else SuperClu_isEEP =0;
			if( (SuperClu_isEE==1) && (SuperClu_Eta<0) ) SuperClu_isEEM =1; else SuperClu_isEEM =0;

			SuperClu_nXtals = mysc->nXtals();
			SuperClu_nXtals = mysc->nBasicClusters();
			SuperClu_seedSeverity = mysc->seedSeverity();
			SuperClu_seedFlag = mysc->seedRecoFlag();
			SuperClu_seedTime = mysc->seedTime();
			SuperClu_s4 = mysc->s4();
			SuperClu_etaWidth = mysc->etaWidth();
			SuperClu_phiWidth = mysc->phiWidth();

			// Cuts on superclusters.
			if( fabs(mysc->Eta())>2.5 ){// Eta acceptance region
				miniSuperClu->Fill();
				continue;
			}
			SuperClu_isAfterCut1 = 1;
			nSCAfterCut1++;

			if( (fabs(mysc->Eta())>1.4442) && (fabs(mysc->Eta())<1.566) ){// Veto on EB/EE gap
				miniSuperClu->Fill();
				continue;
			}
			SuperClu_isAfterCut2 = 1;
			nSCAfterCut2++;

			if( ((1-((double)(mysc->s4())/(double)(mysc->eMax())))>0.95 && (mysc->isEB())) || (mysc->seedRecoFlag()==2)){// Post-spike cleaning
				miniSuperClu->Fill();
				continue;
			}
			SuperClu_isAfterCut3 = 1;
			nSCAfterCut3++;

			nSelectedSC++;
			miniSuperClu->Fill();
		}// end of loop over superclusters

		if (atLeastOneSChigherThan2GeV) nEventsWithScHigherThan2GeV++;
		
		if(doPhoton)
		{
			TRootPhoton* myphoton;
			int nPhotons = 0; 
			int nPhotons_EB = 0; Photon_isEB = 0;
			int nPhotons_EE = 0; Photon_isEE = 0;
			int nPhotons_EEM = 0; Photon_isEEM = 0;
			int nPhotons_EEP = 0; Photon_isEEP = 0;
			Photon_Multiplicity = photons->GetEntriesFast();
			if ( Photon_Multiplicity == 0 ) {miniTree->Fill(); continue;}
			for (int iphoton=0; iphoton<Photon_Multiplicity; iphoton++)
			{
				Photon_isAfterCut1 = 0;
				Photon_isAfterCut2 = 0;
				Photon_isAfterCut3 = 0;
				Photon_isAfterCut4 = 0;
				Photon_isAfterCut5 = 0;
				Photon_isAfterCut6 = 0;
				Photon_isAfterCut7 = 0;
				Photon_isEB = 0;
				Photon_isEE = 0;
				Photon_isEEM = 0;
				Photon_isEEP = 0;
				nTotPhotons++;
				Photon_isEBorEE = 1;
				Photon_isAfterCut0 = 1;
				myphoton = (TRootPhoton*) photons->At(iphoton);


				Photon_E = -99;
				Photon_Et = -99;
				Photon_Eta = -99;
				Photon_Phi = -99;
				Photon_E2x2 = -99;
				Photon_E3x3 = -99;
				Photon_E5x5 = -99;
				Photon_Emax = -99;
				Photon_E2nd = -99;
				Photon_r19 = -99;
				Photon_r9 = -99;
				Photon_caloConeSize = -99;
				Photon_PreshEnergy = -99;
				Photon_HoE = -99;
				Photon_Nclusters = -99;
				Photon_covIetaIeta = -99;
				Photon_covIphiIphi = -99;
				Photon_isoEcalRecHit = -99;
				Photon_isoHcalRecHit = -99;
				Photon_isoSolidTrkCone = -99;
				Photon_isoHollowTrkCone = -99;
				Photon_isoNTracksSolidCone = -99;
				Photon_isoNTracksHollowCone = -99;
				Photon_isoPersoSolidTrkCone = -99;
				Photon_convNTracks = -99;
				Photon_hasPixelSeed = -99;
				Photon_isAlsoElectron = -99;
				Photon_isEE = -99;
				Photon_isEB = -99;
				Photon_isEEM = -99;
				Photon_isEEP = -99;

				/*
				cout << "myphoton->clusterAlgo=" << myphoton->clusterAlgo() << " myphoton->isEBPho=" << myphoton->isEBPho() << " myphoton->isEEPho=" << myphoton->isEEPho() << endl;
				cout << "myphoton->superCluster()=" << myphoton->superCluster() << endl;
				cout << "myphoton->superClusterOfType(210)=" << myphoton->superClusterOfType(210) << endl;
				cout << "myphoton->superClusterOfType(211)=" << myphoton->superClusterOfType(211) << endl;
				cout << "myphoton->superClusterOfType(320)=" << myphoton->superClusterOfType(320) << endl;
				cout << "myphoton->superClusterOfType(322)=" << myphoton->superClusterOfType(322) << endl;
				cout << "myphoton->superClusterOfType(323)=" << myphoton->superClusterOfType(323) << endl;
				*/
				//if (myphoton->superClusterOfType(211) == 0 && myphoton->superClusterOfType(323) == 0 ) continue;

				Photon_E = myphoton->Energy();
				Photon_Et = myphoton->Et();
				Photon_Eta = myphoton->Eta();
				Photon_Phi = myphoton->Phi();
				Photon_E2x2 = myphoton->e2x2();
				Photon_E3x3 = myphoton->e3x3();
				Photon_E5x5 = myphoton->e5x5();
				Photon_Emax = myphoton->eMax();
				Photon_E2nd = myphoton->e2nd();
				Photon_r19 = myphoton->r19();
				Photon_r9 = myphoton->r9();
				Photon_caloConeSize = myphoton->caloConeSize();
				Photon_PreshEnergy = myphoton->preshowerEnergy();
				Photon_HoE = myphoton->hoe();
				Photon_Nclusters = myphoton->nbClusters();
				Photon_covIetaIeta = myphoton->covIetaIeta();
				Photon_covIphiIphi = myphoton->covIphiIphi();
				Photon_isoEcalRecHit = myphoton->isolationEcalRecHit();
				Photon_isoHcalRecHit = myphoton->isolationHcalRecHit();
				Photon_isoSolidTrkCone = myphoton->isolationSolidTrkCone();
				Photon_isoHollowTrkCone = myphoton->isolationHollowTrkCone();
				Photon_isoNTracksSolidCone = myphoton->isolationNTracksSolidCone();
				Photon_isoNTracksHollowCone = myphoton->isolationNTracksHollowCone();
				Photon_isoPersoSolidTrkCone = myphoton->isolationPersoTracksSolidCone();
				Photon_convNTracks = myphoton->convNTracks();
				Photon_hasPixelSeed = myphoton->hasPixelSeed();
				Photon_isAlsoElectron = myphoton->isAlsoElectron();
				if (myphoton->isEBPho()){ Photon_isEB = 1; Photon_isEE = 0; nPhotonEB_perEvent++; }
				if (myphoton->isEEPho()){ Photon_isEE = 1; Photon_isEB = 0; nPhotonEE_perEvent++; }
				if (myphoton->isEEPho() && myphoton->Eta()<0){ Photon_isEEM = 1; nPhotonEEM_perEvent++; }
				if (myphoton->isEEPho() && myphoton->Eta()>0){ Photon_isEEP = 1; nPhotonEEP_perEvent++; }
	
				if ( myphoton->superCluster() != 0 )
				{
					Photon_SCEta = myphoton->superCluster()->Eta();
					Photon_SCPhi = myphoton->superCluster()->Phi();
					Photon_SCEnergy = myphoton->superCluster()->Mag();
					Photon_SCEt = myphoton->superCluster()->Pt();
					Photon_SCRawEt = myphoton->superCluster()->rawEnergy() * sin(myphoton->superCluster()->Theta());
					Photon_etaWidth = myphoton->superCluster()->etaWidth();
					Photon_phiWidth = myphoton->superCluster()->phiWidth();
					Photon_nBasicClusters = myphoton->superCluster()->nBasicClusters();
					Photon_nXtals = myphoton->superCluster()->nXtals();
					Photon_s4 = myphoton->superCluster()->s4();
					Photon_seedTime = myphoton->superCluster()->seedTime();
					Photon_seedFlag = myphoton->superCluster()->seedRecoFlag();
					Photon_seedSeverity = myphoton->superCluster()->seedSeverity();
					Photon_cross = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
					Photon_isTightPhoton = myphoton->isTightPhoton();
					Photon_isLoosePhoton = myphoton->isLoosePhoton();
					Photon_isolationPersoTracksSolidCone = myphoton->isolationPersoTracksSolidCone();
					Photon_isolationPersoNTracksSolidCone = myphoton->isolationPersoNTracksSolidCone();
					Photon_SCRawEnergy = myphoton->superCluster()->rawEnergy();
				} else {
					Photon_SCEta = -99;
					Photon_SCPhi = -99;
					Photon_SCEnergy = -99;
					Photon_SCEt = -99;
					Photon_SCRawEt = -99;
					Photon_etaWidth = -99;
					Photon_phiWidth = -99;
					Photon_nBasicClusters = -99;
					Photon_nXtals = -99;
					Photon_s4 = -99;
					Photon_seedTime = -99;
					Photon_seedFlag = -99;
					Photon_seedSeverity = -99;
					Photon_cross = -99;
					Photon_isTightPhoton = -99;
					Photon_isLoosePhoton = -99;
					Photon_isolationPersoTracksSolidCone = -99;
					Photon_isolationPersoNTracksSolidCone = -99;
					Photon_SCRawEnergy = -99;
				} // end of loop over photons having a supercluster

				// CUT 0: check if the photon have a superCluster
				if (myphoton->superCluster() == 0 ) {miniTree->Fill(); continue;}

				Float_t scRawEt = myphoton->superCluster()->rawEnergy() * sin(myphoton->superCluster()->Theta());
				Float_t abs_eta = fabs(myphoton->superCluster()->Eta());

				// CUT 1: obsolete
				nCut1++;
				Photon_isAfterCut1 = 1;

				// CUT 2: obsolete
				nCut2++;
				Photon_isAfterCut2 = 1;

				// CUT 3: obsolete				
				nCut3++;
				Photon_isAfterCut3 = 1;

				// CUT 4: minimum supercluster transverse energy
				if ( scRawEt<2.0 ) {miniTree->Fill(); continue;}
				nCut4++;
				Photon_isAfterCut4 = 1;

				// CUT 5: |eta| < 2.5 and not close to barrel/endcap gap
				if ( (abs_eta>2.5) || ( abs_eta>1.4442 && abs_eta<1.566 ) ) {miniTree->Fill();	continue;}
				nCut5++;
				Photon_isAfterCut5 = 1;

				// CUT 6: spike removal
				if ( myphoton->isEBPho() &&(1 - ((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax())))>0.95 ) {miniTree->Fill(); continue;}
				nCut6++;
				Photon_isAfterCut6 = 1;
			
				// CUT 7: H/E
				if (Photon_HoE > 0.05){miniTree->Fill(); continue;}
				nCut7++;
				Photon_isAfterCut7 = 1;
	
				nPhotons++;
				nSelectedPhotons++;
		
				miniTree->Fill();	
			} // end of loop over photons
			
			
		} // end of do photons

		if (event->trigHLT()[71]==true) HLT_Photon10_L1R = 1; else HLT_Photon10_L1R =0;
		if (event->trigHLT()[72]==true) HLT_Photon10_L1R = 1; else HLT_Photon10_L1R =0;
		if (event->trigHLT()[74]==true) HLT_Photon15_LooseEcalIso_L1R = 1; else HLT_Photon15_LooseEcalIso_L1R =0;
		if (event->trigHLT()[75]==true) HLT_Photon20_L1R = 1; else HLT_Photon20_L1R =0;
		if (event->trigHLT()[76]==true) HLT_Photon30_L1R_8E29 = 1; else HLT_Photon30_L1R_8E29 =0;

		if (event->trigHLT()[78]==true) HLT_DoublePhoton4_Jpsi_L1R = 1; else HLT_DoublePhoton4_Jpsi_L1R =0;
		if (event->trigHLT()[79]==true) HLT_DoublePhoton4_Upsilon_L1R = 1; else HLT_DoublePhoton4_Upsilon_L1R =0;
		if (event->trigHLT()[77]==true) HLT_DoublePhoton4_eeRes_L1R = 1; else HLT_DoublePhoton4_eeRes_L1R =0;
//		if (event->trigHLT()[]==true) HLT_DoublePhoton5_eeRes_L1R = 1; else HLT_DoublePhoton5_eeRes_L1R =0;
		if (event->trigHLT()[80]==true) HLT_DoublePhoton5_Jpsi_L1R = 1; else HLT_DoublePhoton5_Jpsi_L1R =0;

		if (event->trigHLT()[81]==true) HLT_DoublePhoton5_Upsilon_L1R = 1; else HLT_DoublePhoton5_Upsilon_L1R =0;
		if (event->trigHLT()[82]==true) HLT_DoublePhoton5_L1R = 1; else HLT_DoublePhoton5_L1R =0;
		if (event->trigHLT()[83]==true) HLT_DoublePhoton10_L1R = 1; else HLT_DoublePhoton10_L1R =0;
		if (event->trigHLT()[70]==true) HLT_DoubleEle5_SW_L1R = 1; else HLT_DoubleEle5_SW_L1R =0;
		if (event->trigHLT()[69]==true) HLT_Ele20_LW_L1R = 1; else HLT_Ele20_LW_L1R =0;

		if (event->trigHLT()[68]==true) HLT_Ele15_SiStrip_L1R = 1; else HLT_Ele15_SiStrip_L1R =0;
		if (event->trigHLT()[67]==true) HLT_Ele15_SC10_LW_L1R = 1; else HLT_Ele15_SC10_LW_L1R =0;
		if (event->trigHLT()[66]==true) HLT_Ele15_LW_L1R = 1; else HLT_Ele15_LW_L1R =0;
		if (event->trigHLT()[65]==true) HLT_Ele10_LW_EleId_L1R = 1; else HLT_Ele10_LW_EleId_L1R =0;
		if (event->trigHLT()[64]==true) HLT_Ele10_LW_L1R = 1; else HLT_Ele10_LW_L1R =0;

		if (event->trigHLT()[73]==true) HLT_Photon15_TrackIso_L1R = 1; else HLT_Photon15_TrackIso_L1R =0;

		miniEvent->Fill();	
		nSelectedEvents++;	
	} // fin boucle sur evts

	
	if(nTotEvents>0) cout << "nTotEvents=" << nTotEvents << "	nTotEventsSelectedRuns=" << nTotEventsSelectedRuns << "	nTotEventsSelectedL1=" << nTotEventsSelectedL1
		<< "	nTotEventsSelectedVertex=" << nTotEventsSelectedVertex	<< "	nSelectedEvents=" << nSelectedEvents	 << "	nEventsWithScHigherThan2GeV=" << nEventsWithScHigherThan2GeV
	<< "	nSelectedEvents/nTotEventsSelectedRuns=" <<100.*nSelectedEvents/nTotEventsSelectedRuns << "%" << "	nSelectedEvents/nTotEvents=" <<100.*nSelectedEvents/nTotEvents << "%" << endl;

	if(nTotPhotons>0) cout << "nSelectedPhotons=" << nSelectedPhotons << "	nTotPhotons=" << nTotPhotons << "	Eff=" <<100.*nSelectedPhotons/nTotPhotons << "%" << endl;
	cout << "nCut1=" << nCut1 << "	nCut2=" << nCut2 << "	nCut3=" << nCut3 << "	nCut4=" << nCut4 << "	nCut5=" << nCut5 << "	nCut6=" << nCut6 << "	 nCut7=" << nCut7 << endl;

	if(nTotSC>0) cout << "nTotSC=" << nTotSC << "  nSelectedSC=" << nSelectedSC << "  nSCAfterCut1=" << nSCAfterCut1 << "  nSCAfterCut2=" << nSCAfterCut2 << "  nSCAfterCut3=" << nSCAfterCut3 << endl;
	
	OutputRootFile->cd();
	OutputRootFile->Write();
	OutputRootFile->Close();

	return 0;
}
