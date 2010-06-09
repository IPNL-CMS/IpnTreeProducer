#include <TLorentzVector.h>
#include <TVector3.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TFormula.h>
#include <TF1.h>
#include <TSystem.h>
#include <TClonesArray.h>
#include <TLeaf.h>
#include <TChain.h>
#include <TObject.h>
#include <string.h>
#include <algorithm>
#include <TBranch.h>
#include <TString.h>
#include <TBits.h>
#include <TMath.h>
#include "TROOT.h"
#include <TLatex.h>

#pragma optimize 0

using namespace std;

void DrawDataMCplot_NormEntries_Fast(TTree *Data_PhotonTree, TTree *MC_PhotonTree, string var, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFlow, TCanvas *c1){

	// Get Histo_Data from PhotonTree
	TH1F *Histo_Data_temp = new TH1F();
	string variable_Data = var + ">>Histo_Data_temp" + limits;
	Data_PhotonTree->Draw(variable_Data.c_str(), cut.c_str());
	TH1F *Histo_Data = (TH1F*)gDirectory->Get("Histo_Data_temp"); 
	c1->Clear();

	// Get Histo_MC from PhotonTree
	TH1F *Histo_MC_temp = new TH1F();
	string variable_MC = var + ">>Histo_MC_temp" + limits;
	MC_PhotonTree->Draw(variable_MC.c_str(), cut.c_str());
	TH1F *Histo_MC = (TH1F*)gDirectory->Get("Histo_MC_temp");
	c1->Clear();

	// TODO: implement drawUnderOverFlow

	// Get the number of entries for further normalization
	double a = Histo_Data->GetEntries();
	double b = Histo_MC->GetEntries();
	if( (a==0.0) || (b==0.0) ){
		cout << "no entries in MC or DATA sample, skipping plot" <<endl;
		return;
	}

	// Normalize
	Histo_Data->Sumw2(); // In order to have the correct error bars on data after renormalization
	// // Normalize MC and Data to 1
	//Histo_Data->Scale((double)((double)1.0/(double)a));
	//Histo_MC->Scale((double)((double)1.0/(double)b));
	// // Normalize MC to Data number of entries
	Histo_MC->Scale((double)((double)a/(double)b));

	// Get the maxs and the mins to further correct the Y-axis
	double dataMax = Histo_Data->GetMaximum();
	double mcMax = Histo_MC->GetMaximum();
	double YMax = max(dataMax, mcMax);
	double dataMin = YMax;
	double mcMin = YMax;
	// Gets the actual minimum for each histogram, and not the unfilled bin if any
	for( int ibin=1 ; ibin<Histo_Data->GetNbinsX() ; ibin++ ){
		if( ((Histo_Data->GetBinContent(ibin))!=0) && ((Histo_Data->GetBinContent(ibin))<dataMin) ){
			dataMin = Histo_Data->GetBinContent(ibin);
		}
	}
	for( int ibin=1 ; ibin<Histo_MC->GetNbinsX() ; ibin++ ){
		if( ((Histo_MC->GetBinContent(ibin))!=0) && ((Histo_MC->GetBinContent(ibin))<mcMin) ){
			mcMin = Histo_MC->GetBinContent(ibin);
		}
	}
	double YMin = min(dataMin, mcMin);
	double YMax_lin = YMax + (YMax)*.3;
	double YMin_lin = YMin - (YMin)*.2;
	double YMax_log = YMax * 3;
	double YMin_log = (double) YMin / (double) 1.5;

	// Setup the histo and canvas names and title
	string data_name = "Data_" + var + "_" + name;
	string mc_name = "MC_" + var + "_" + name;
	string canvas_name = "DataMC_" + var + "_" + name;
	Histo_Data->SetName(data_name.c_str());
	Histo_MC->SetName(mc_name.c_str());
	c1->SetName(canvas_name.c_str());
	c1->SetTitle(canvas_name.c_str());

	// Draw the comparison plots
	// // First: draw the data to get correct Y-axis scale
	Histo_Data->GetXaxis()->SetTitle(Title.c_str());
	Histo_Data->SetLineColor(kBlack);
	Histo_Data->SetMarkerColor(kBlack);
	Histo_Data->SetMarkerSize(0.7);
	Histo_Data->SetMarkerStyle(20);
	Histo_Data->SetMaximum(YMax_lin);
	Histo_Data->SetMinimum(YMin_lin);
	Histo_Data->Draw("E1");

	// // Second: draw MC on the same canvas
	Histo_MC->SetLineColor(kBlack);
	Histo_MC->SetFillColor(kYellow);
	Histo_MC->SetMaximum(YMax_lin);
	Histo_MC->SetMinimum(YMin_lin);
	Histo_MC->Draw("same");

	// // Third: re-draw Data so that data appears in front of MC
	Histo_Data->Draw("E1same");

	// // Fourth: redraw axis so that axis appears in front of everything
	gPad->RedrawAxis();

	// // Fifth: draw legend
	TLegend *legend = new TLegend(0.8, 0.83, 0.99, 0.994, "");
	legend->SetFillColor(kWhite);
	legend->SetLineColor(kWhite);
	legend->SetShadowColor(kWhite);
	legend->AddEntry(Histo_Data->GetName(), "Data", "lp");
	legend->AddEntry(Histo_MC->GetName(), "MC", "f");
	legend->Draw();
	TLatex latexLabel;
	latexLabel.SetTextSize(0.04);
	latexLabel.SetNDC();
	latexLabel.DrawLatex(0.18, 0.87, "CMS Preliminary 2010");
	latexLabel.DrawLatex(0.18, 0.82, "#sqrt{s} = 7 TeV");

	// // Sixth: update canvas
	c1->Update();
	c1->Draw();

	// Print the canvas
	string PicName="PlotDataMC7TeV_TEST/DataMC_" + var + "_" + name + ".gif";
	c1->Print(PicName.c_str());
	if (inlog==true) {
		string PicName_log="PlotDataMC7TeV_TEST/DataMC_" + var + "_" + name + "_log.gif";
		c1->cd(1);
		c1->SetLogy(1);
		Histo_Data->SetMaximum(YMax_log);
		Histo_Data->SetMinimum(YMin_log);
		c1->Update();
		c1->Draw();
		c1->Print(PicName_log.c_str());
		c1->SetLogy(0);
		c1->Update();
	} 

	// Clean the memory
	c1->Clear();
	legend->Clear();
	Histo_Data_temp->Delete();
	Histo_MC_temp->Delete();
	Histo_Data->Delete();
	Histo_MC->Delete();

}
	
//int plotDataMC_TDR_miniTree()
int main()
{
//	cout<<"\tDEBUG:\tEntering main()"<<endl;
	//gStyle->SetOptStat(0);
	gROOT->ProcessLine(".x setTDRStyle.C");
	string Data = "miniTree_TEST.root"; 
	string MC = "miniTree_TEST.root"; 
	
	TFile *Data_File = new TFile(Data.c_str());
	TFile *MC_File = new TFile(MC.c_str());
	TTree* Data_PhotonTree = (TTree*) Data_File->Get("miniTree");
	TTree* MC_PhotonTree = (TTree*) MC_File->Get("miniTree");
	TTree* Data_eventTree = (TTree*) Data_File->Get("miniEvents");
	TTree* MC_eventTree = (TTree*) MC_File->Get("miniEvents");
	TTree* Data_SuperCluTree = (TTree*) Data_File->Get("miniSuperClu");
	TTree* MC_SuperCluTree = (TTree*) MC_File->Get("miniSuperClu");


	TCanvas *c1 = new TCanvas("Default", "Default");

	vector<string> set_of_cuts;
	vector<string> name;
	set_of_cuts.push_back("Photon_isAfterCut7==1");
	name.push_back("Photon_isAfterCut7");
	set_of_cuts.push_back("Photon_isAfterCut7==1 && Photon_isEB==1");
	name.push_back("Photon_isAfterCut7_AND_Photon_isEB");
	set_of_cuts.push_back("Photon_isAfterCut7==1 && Photon_isEE==1");
	name.push_back("Photon_isAfterCut7_AND_Photon_isEE");
	set_of_cuts.push_back("Photon_isAfterCut7==1 && Photon_isEEP==1");
	name.push_back("Photon_isAfterCut7_AND_Photon_isEEP");
	set_of_cuts.push_back("Photon_isAfterCut7==1 && Photon_isEEM==1");
	name.push_back("Photon_isAfterCut7_AND_Photon_isEEM");
	set_of_cuts.push_back("Photon_SCRawEnergy>4 && Photon_isAfterCut7==1 && Photon_isEEM==1");
	name.push_back("Photon_isAfterCut7_AND_Photon_isEEM_AND_Photon_SCRawEnergyGT4");

	for(int i=0; i<set_of_cuts.size() ; i++){ // loop over different set of cuts
//		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Multiplicity", "(15,0,15)", set_of_cuts[i], name[i], "Photon Multiplicity", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_hasPixelSeed", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon hasPixelSeed", true, false, c1);
/*		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isAlsoElectron", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isAlsoElectron", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E", "(100, 0, 800)", set_of_cuts[i], name[i], "Photon Energy", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Et", "(100, 0, 800)", set_of_cuts[i], name[i], "Photon Et", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Eta", "(60, -3.0, 3.0)", set_of_cuts[i], name[i], "Photon Eta", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Phi", "(30, -3.15, 3.15)", set_of_cuts[i], name[i], "Photon Phi", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCEta", "(60, -3.0, 3.0)", set_of_cuts[i], name[i], "Photon SC	Eta", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCPhi", "(30, -3.15, 3.15)", set_of_cuts[i], name[i], "Photon SC Phi", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E2x2", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E2x2", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E3x3", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E3x3", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E5x5", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E5x5", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Emax", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon Emax", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E2nd", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon E2nd", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_r19", "(100, 0, 2)", set_of_cuts[i], name[i], "Photon r19", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_r9", "(100, 0, 2)", set_of_cuts[i], name[i], "r9", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_cross", "(50, -4, 2)", set_of_cuts[i], name[i], "Photon 1-(E4/E1)", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_caloConeSize", "(30, 0, 0.5)", set_of_cuts[i], name[i], "Photon caloConeSize", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCEnergy", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon SC Energy", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCEt", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon SC Et", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCRawEnergy", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon SC Raw Energy", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCRawEt", "(100, 0, 1000)", set_of_cuts[i], name[i], "Photon SC Raw Et", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_PreshEnergy", "(40, 0, 10)", set_of_cuts[i], name[i], "Photon Preshower Energy", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_HoE", "(30, 0, 0.55)", set_of_cuts[i], name[i], "Photon HoE", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Nclusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon Nclusters", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_covIetaIeta", "(30, 0, 0.02)", set_of_cuts[i], name[i], "Photon covIetaIeta", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_covIphiIphi", "(30, 0, 0.025)", set_of_cuts[i], name[i], "Photon covIphiIphi", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoEcalRecHit", "(70, -2, 20)", set_of_cuts[i], name[i], "Photon isoEcalRecHit", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoHcalRecHit", "(100, -1, 10)", set_of_cuts[i], name[i], "Photon isoHcalRecHit", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoSolidTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoSolidTrkCone", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoHollowTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoHollowTrkCone", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoNTracksSolidCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksSolidCone", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoNTracksHollowCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksHollowCone", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoPersoSolidTrkCone", "(100, 0, 30)", set_of_cuts[i], name[i], "Photon isoPersoSolidTrkCone", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_convNTracks", "(5, -1, 4)", set_of_cuts[i], name[i], "Photon convNTracks", true, false, c1);
	//	TH2F* h_Photon_EtaPhi_Occupancy", "(60, -3, 3, 60, -3.15, 3.15)", set_of_cuts[i], name[i], "Photon Multiplicity", true, false, c1);
	//	TH2F* h_Photon_Energy_vs_Phi", "(60, 0, 60, 60, -3.15, 3.15)", set_of_cuts[i], name[i], "Photon Multiplicity", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_etaWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Eta Width", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_phiWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Phi Width", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_nBasicClusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon nBasicClusters", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_nXtals", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon nXtals", true, false, c1);
	//		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_nRecHits", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon nRecHits", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_seedTime", "(300,-150,150)", set_of_cuts[i], name[i], "Photon seed Time", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_seedFlag", "(50,0,50)", set_of_cuts[i], name[i], "Photon seed Flag", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isTightPhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isTightPhoton", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isLoosePhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isLoosePhoton", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isolationPersoTracksSolidCone", "(30, 0, 100)", set_of_cuts[i], name[i], "Photon isolationPersoTracksSolidCone", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isolationPersoNTracksSolidCone", "(30, 0, 100)", set_of_cuts[i], name[i], "Photon isolationPersoNTracksSolidCone", true, false, c1);
*/
	
	} // end of loop over set of cuts

//			Plots for super-clusters
	vector<string> set_of_cuts_superclu;
	vector<string> name_superclu;
	set_of_cuts_superclu.push_back("NoCuts");
	name_superclu.push_back("NoCuts");
	set_of_cuts_superclu.push_back("SuperClu_isEE==1 && NoCuts==1");
	name_superclu.push_back("SuperClu_isEE");
	set_of_cuts_superclu.push_back("SuperClu_isEB==1 && NoCuts==1");
	name_superclu.push_back("SuperClu_isEB");
	set_of_cuts_superclu.push_back("SuperClu_isEEP==1 && NoCuts==1");
	name_superclu.push_back("SuperClu_isEEP");
	set_of_cuts_superclu.push_back("SuperClu_isEEM==1 && NoCuts==1");
	name_superclu.push_back("SuperClu_isEEM");
/*
	for (int i=0;i<name_superclu.size();i++){
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_E", "(100, 0, 800)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Energy", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_Et", "(100, 0, 800)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Et", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_RawE", "(100, 0, 800)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Raw Energy", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_RawEt", "(100, 0, 800)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Raw Et", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_Eta", "(60, -3.0, 3.0)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Eta", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_Phi", "(30, -3.15, 3.15)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Phi", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_nXtals", "(100, 0, 100)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster number of crystals", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_seedTime", "(300, -40, 40)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster seed time", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_seedFlag", "(15, 0, 15)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster seed flag", true, false, c1);

	}
*/
	vector<string> set_of_cuts_events;
	vector<string> name_events;
	set_of_cuts_events.push_back("NoCuts");
	name_events.push_back("NoCuts");
	for(int i=0;i<name_events.size();i++){
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Multiplicity", "(15, 0, 15)", set_of_cuts_events[i], name_events[i], "Photon multiplicity", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "SuperClu_Multiplicity", "(30, 0, 30)", set_of_cuts_events[i], name_events[i], "Super cluster multiplicity", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "nPhotonEB_perEvent", "(15, 0, 15)", set_of_cuts_events[i], name_events[i],"nPhotonEB_perEvent", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "nPhotonEE_perEvent", "(15, 0, 15)", set_of_cuts_events[i], name_events[i],"nPhotonEE_perEvent", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "nPhotonEEP_perEvent", "(15, 0, 15)", set_of_cuts_events[i], name_events[i],"nPhotonEEP_perEvent", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "nPhotonEEM_perEvent", "(15, 0, 15)", set_of_cuts_events[i], name_events[i], "nPhotonEEM_perEvent", true, false, c1);
/*
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon10_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Photon10_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon15_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Photon15_L1R", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon15_LooseEcalIso_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Photon15_LooseEcalIso_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon20_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Photon20_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon30_L1R_8E29", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Photon30_L1R_8E29 triggered", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton4_Jpsi_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton4_Jpsi_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton4_Upsilon_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton4_Upsilon_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton4_eeRes_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton4_eeRes_L1R triggered", true, false, c1);
//	DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton5_eeRes_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton5_eeRes_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton5_Jpsi_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton5_Jpsi_L1R triggered", true, false, c1);
	
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton5_Upsilon_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton5_Upsilon_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton5_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton5_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton10_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton10_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoubleEle5_SW_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_DoubleEle5_SW_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele20_LW_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Ele20_LW_L1R triggered", true, false, c1);
	
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele15_SiStrip_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Ele15_SiStrip_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele15_SC10_LW_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Ele15_SC10_LW_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele15_LW_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Ele15_LW_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele10_LW_EleId_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Ele10_LW_EleId_L1R triggered", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele10_LW_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Ele10_LW_L1R triggered", true, false, c1);
	
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon15_TrackIso_L1R", "(3, 0, 3)", set_of_cuts_events[i], name_events[i], "HLT_Photon15_TrackIso_L1R triggered", true, false, c1);
	*/
	}

	return 0;	
}

