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

	// TODO: implement underflow
	if( drawUnderOverFlow ){
    // overflow bin for data
		string name_Data  = "temp Data";
		char* title_Data = (char*)Histo_Data->GetTitle();
		Int_t nx_Data = Histo_Data->GetNbinsX()+1;
		Double_t bw_Data = Histo_Data->GetBinWidth(nx_Data);
		Double_t x1_Data = Histo_Data->GetBinLowEdge(1);
		Double_t x2_Data = Histo_Data->GetBinLowEdge(nx_Data)+bw_Data;
		TH1F *htmp_Data = new TH1F(name_Data.c_str(), title_Data, nx_Data, x1_Data, x2_Data); // Book a temporary histogram having an extra bin for overflows
    for (Int_t i=1; i<=nx_Data; i++) {// Fill the new hitogram including the extra bin for overflows
       htmp_Data->Fill(htmp_Data->GetBinCenter(i), Histo_Data->GetBinContent(i));
    }
		htmp_Data->Fill(x1_Data-1, Histo_Data->GetBinContent(0));    // Restore the number of entries
		htmp_Data->SetEntries(Histo_Data->GetEntries());    // Draw the temporary histogram
		Histo_Data->Clear();
		Histo_Data = new TH1F(*htmp_Data);
		Histo_Data->SetName("Histo Data");

    // overflow bin for mc
		string name_MC  = "temp MC";
		char* title_MC = (char*)Histo_MC->GetTitle();
		Int_t nx_MC = Histo_MC->GetNbinsX()+1;
		Double_t bw_MC = Histo_MC->GetBinWidth(nx_MC);
		Double_t x1_MC = Histo_MC->GetBinLowEdge(1);
		Double_t x2_MC = Histo_MC->GetBinLowEdge(nx_MC)+bw_MC;
		TH1F *htmp_MC = new TH1F(name_MC.c_str(), title_MC, nx_MC, x1_MC, x2_MC); // Book a temporary histogram having an extra bin for overflows
    for (Int_t i=1; i<=nx_MC; i++) {// Fill the new hitogram including the extra bin for overflows
       htmp_MC->Fill(htmp_MC->GetBinCenter(i), Histo_MC->GetBinContent(i));
    }
		htmp_MC->Fill(x1_MC-1, Histo_MC->GetBinContent(0));    // Restore the number of entries
		htmp_MC->SetEntries(Histo_MC->GetEntries());    // Draw the temporary histogram
		Histo_MC->Clear();
		Histo_MC = new TH1F(*htmp_MC);
		Histo_MC->SetName("Histo MC");

		htmp_Data->Clear();
		htmp_MC->Clear();

	}

	// Get the number of entries for further normalization
	double a = Histo_Data->GetEntries();
	double b = Histo_MC->GetEntries();
	if( (a==0.0) || (b==0.0) ){
		cout << "no entries in MC or DATA sample, skipping plot " << var << " " << name <<endl;
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

//	string dirName="Plots_DATA_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1";
//	string dirName="Plots_DATA_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1";
//	string dirName="Plots_DATA_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1";
//	string dirName="Plots_DATA_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1";

	// Print the canvas
	string PicName= dirName + "/gif/DataMC_" + var + "_" + name + ".gif";
	c1->Print(PicName.c_str());
	PicName= dirName + "/eps/DataMC_" + var + "_" + name + ".eps";
	c1->Print(PicName.c_str());
	if (inlog==true) {
		c1->cd(1);
		c1->SetLogy(1);
		Histo_Data->SetMaximum(YMax_log);
		Histo_Data->SetMinimum(YMin_log);
		c1->Update();
		c1->Draw();
		string PicName_log= dirName + "/gif/DataMC_" + var + "_" + name + "_log.gif";
		c1->Print(PicName_log.c_str());
		PicName_log= dirName + "/eps/DataMC_" + var + "_" + name + "_log.eps";
		c1->Print(PicName_log.c_str());
		c1->SetLogy(0);
		c1->Update();
	} 

	// Clean the memory
	c1->Clear();
	legend->Clear();
	Histo_Data_temp->Clear();
	Histo_MC_temp->Clear();
	Histo_Data->Clear();
	Histo_MC->Clear();

}
	
//int plotDataMC_TDR_miniTree()
int main()
{
//	cout<<"\tDEBUG:\tEntering main()"<<endl;
	//gStyle->SetOptStat(0);
	gROOT->ProcessLine(".x setTDRStyle.C");
	string Data = "miniTree_DATA__ALL.root"; 
//	string MC = "miniTree_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1___ALL.root"; 
//	string MC = "miniTree_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1___ALL.root"; 
//	string MC = "miniTree_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1___ALL.root"; 
//	string MC = "miniTree_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1___ALL.root"; 
	
	TFile *Data_File = new TFile(Data.c_str());
	TFile *MC_File = new TFile(MC.c_str());

	TCanvas *c1 = new TCanvas("Default", "Default");


if(false){	// Plots for the photons
	TTree* Data_PhotonTree = (TTree*) Data_File->Get("photon_miniTree");
	TTree* MC_PhotonTree = (TTree*) MC_File->Get("photon_miniTree");
	vector<string> set_of_cuts;
	vector<string> name;
//	name.push_back("isAfterCut7");
//	set_of_cuts.push_back("Photon_isAfterCut7==1");
//	name.push_back("isAfterCut7_EB");
//	set_of_cuts.push_back("Photon_isAfterCut7==1 && Photon_isEB==1");
//	name.push_back("isAfterCut7_EE");
//	set_of_cuts.push_back("Photon_isAfterCut7==1 && Photon_isEE==1");
//	name.push_back("isAfterCut7_EEP");
//	set_of_cuts.push_back("Photon_isAfterCut7==1 && Photon_isEEP==1");
//	name.push_back("isAfterCut7_EEM");
//	set_of_cuts.push_back("Photon_isAfterCut7==1 && Photon_isEEM==1");

	for(int i=0; i<set_of_cuts.size() ; i++){ // loop over different set of cuts
		cout << "\tStarting loop on photons for plots with cuts: " << set_of_cuts[i] << endl;
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_hasPixelSeed", "(2, 0, 2)", set_of_cuts[i], name[i], "Photon hasPixelSeed", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isAlsoElectron", "(2, 0, 2)", set_of_cuts[i], name[i], "Photon isAlsoElectron", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E", "(60, 0, 90)", set_of_cuts[i], name[i], "Photon Energy", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Et", "(75, 0, 30)", set_of_cuts[i], name[i], "Photon Et", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Eta", "(30, -3.0, 3.0)", set_of_cuts[i], name[i], "Photon Eta", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Phi", "(30, -3.15, 3.15)", set_of_cuts[i], name[i], "Photon Phi", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCEta", "(30, -3.0, 3.0)", set_of_cuts[i], name[i], "Photon SC	Eta", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCPhi", "(30, -3.15, 3.15)", set_of_cuts[i], name[i], "Photon SC Phi", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E2x2", "(70, 0, 70)", set_of_cuts[i], name[i], "Photon E2x2", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E3x3", "(70, 0, 70)", set_of_cuts[i], name[i], "Photon E3x3", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E5x5", "(70, 0, 70)", set_of_cuts[i], name[i], "Photon E5x5", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Emax", "(63, 0, 50)", set_of_cuts[i], name[i], "Photon Emax", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_E2nd", "(34, 0, 20)", set_of_cuts[i], name[i], "Photon E2nd", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_r19", "(50, 0.1, 1.3)", set_of_cuts[i], name[i], "Photon r19", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_r9", "(50, 0.1, 1.3)", set_of_cuts[i], name[i], "r9", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_cross", "(1000, 0, 1.1)", set_of_cuts[i], name[i], "Photon 1-(E4/E1)", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_caloConeSize", "(50, 0, 0.4)", set_of_cuts[i], name[i], "Photon caloConeSize", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCEnergy", "(166, 0, 90)", set_of_cuts[i], name[i], "Photon SC Energy", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCEt", "(75, 0, 30)", set_of_cuts[i], name[i], "Photon SC Et", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCRawEnergy", "(60, 0, 80)", set_of_cuts[i], name[i], "Photon SC Raw Energy", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_SCRawEt", "(75, 0, 30)", set_of_cuts[i], name[i], "Photon SC Raw Et", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_PreshEnergy", "(125, 0, 8)", set_of_cuts[i], name[i], "Photon Preshower Energy", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_HoE", "(21, 0, 0.55)", set_of_cuts[i], name[i], "Photon HoE", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_Nclusters", "(8, 0, 8)", set_of_cuts[i], name[i], "Photon Nb of cluster constituents", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_covIetaIeta", "(44, 0, 0.007)", set_of_cuts[i], name[i], "Photon covIetaIeta", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_covIphiIphi", "(32, 0, 0.008)", set_of_cuts[i], name[i], "Photon covIphiIphi", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoEcalRecHit", "(50, -1, 10)", set_of_cuts[i], name[i], "Photon isoEcalRecHit", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoHcalRecHit", "(42, 0, 5)", set_of_cuts[i], name[i], "Photon isoHcalRecHit", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoSolidTrkCone", "(105, 0, 25)", set_of_cuts[i], name[i], "Photon isoSolidTrkCone", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoHollowTrkCone", "(105, 0, 25)", set_of_cuts[i], name[i], "Photon isoHollowTrkCone", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoNTracksSolidCone", "(12, 0, 12)", set_of_cuts[i], name[i], "Photon isoNTracksSolidCone", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoNTracksHollowCone", "(12, 0, 12)", set_of_cuts[i], name[i], "Photon isoNTracksHollowCone", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isoPersoSolidTrkCone", "(100, 0, 30)", set_of_cuts[i], name[i], "Photon isoPersoSolidTrkCone", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_convNTracks", "(4, 0, 4)", set_of_cuts[i], name[i], "Photon convNTracks", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_etaWidth", "(25, 0, 0.05)", set_of_cuts[i], name[i], "Photon Eta Width", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_phiWidth", "(50, 0, 0.2)", set_of_cuts[i], name[i], "Photon Phi Width", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_nBasicClusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon nBasicClusters", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_nXtals", "(90, 0, 90)", set_of_cuts[i], name[i], "Photon nXtals", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_nRecHits", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon nRecHits", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_seedTime", "(20,-30,30)", set_of_cuts[i], name[i], "Photon seed Time", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_s4", "(50,-2,100)", set_of_cuts[i], name[i], "Photon s4", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_seedSeverity", "(4,0,4)", set_of_cuts[i], name[i], "Photon seed Severity", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_seedFlag", "(11,0,11)", set_of_cuts[i], name[i], "Photon seed Flag", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isTightPhoton", "(2, 0, 2)", set_of_cuts[i], name[i], "Photon isTightPhoton", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isLoosePhoton", "(2, 0, 2)", set_of_cuts[i], name[i], "Photon isLoosePhoton", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isolationPersoTracksSolidCone", "(30, 0, 100)", set_of_cuts[i], name[i], "Photon isolationPersoTracksSolidCone", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_PhotonTree, MC_PhotonTree, "Photon_isolationPersoNTracksSolidCone", "(30, 0, 100)", set_of_cuts[i], name[i], "Photon isolationPersoNTracksSolidCone", true, true, c1);
//
	} // end of loop over set of cuts
}

if(false){ //			Plots for super-clusters
	TTree* Data_SuperCluTree = (TTree*) Data_File->Get("supercluster_miniTree");
	TTree* MC_SuperCluTree = (TTree*) MC_File->Get("supercluster_miniTree");

	vector<string> set_of_cuts_superclu;
	vector<string> name_superclu;
//	name_superclu.push_back("isAfterCut3");
//	set_of_cuts_superclu.push_back("SuperClu_isAfterCut3");
//	name_superclu.push_back("isAfterCut3_EE");
//	set_of_cuts_superclu.push_back("SuperClu_isEE==1 && SuperClu_isAfterCut3==1");
//	name_superclu.push_back("isAfterCut3_EB");
//	set_of_cuts_superclu.push_back("SuperClu_isEB==1 && SuperClu_isAfterCut3==1");
//	name_superclu.push_back("isAfterCut3_EEP");
//	set_of_cuts_superclu.push_back("SuperClu_isEEP==1 && SuperClu_isAfterCut3==1");
//	name_superclu.push_back("isAfterCut3_EEM");
//	set_of_cuts_superclu.push_back("SuperClu_isEEM==1 && SuperClu_isAfterCut3==1");
//	name_superclu.push_back("isAfterCut3_RawEtGT2");
//	set_of_cuts_superclu.push_back("SuperClu_isAfterCut3 && SuperClu_RawEt>2.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT2_EE");
//	set_of_cuts_superclu.push_back("SuperClu_isEE==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>2.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT2_EB");
//	set_of_cuts_superclu.push_back("SuperClu_isEB==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>2.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT2_EEP");
//	set_of_cuts_superclu.push_back("SuperClu_isEEP==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>2.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT2_EEM");
//	set_of_cuts_superclu.push_back("SuperClu_isEEM==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>2.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT4");
//	set_of_cuts_superclu.push_back("SuperClu_isAfterCut3 && SuperClu_RawEt>2.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT4_EE");
//	set_of_cuts_superclu.push_back("SuperClu_isEE==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>4.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT4_EB");
//	set_of_cuts_superclu.push_back("SuperClu_isEB==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>4.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT4_EEP");
//	set_of_cuts_superclu.push_back("SuperClu_isEEP==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>4.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT4_EEM");
//	set_of_cuts_superclu.push_back("SuperClu_isEEM==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>4.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT10");
//	set_of_cuts_superclu.push_back("SuperClu_isAfterCut3 && SuperClu_RawEt>4.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT10_EE");
//	set_of_cuts_superclu.push_back("SuperClu_isEE==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>10.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT10_EB");
//	set_of_cuts_superclu.push_back("SuperClu_isEB==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>10.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT10_EEP");
//	set_of_cuts_superclu.push_back("SuperClu_isEEP==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>10.0");
//	name_superclu.push_back("isAfterCut3_RawEtGT10_EEM");
//	set_of_cuts_superclu.push_back("SuperClu_isEEM==1 && SuperClu_isAfterCut3==1 && SuperClu_RawEt>10.0");

	for (int i=0;i<name_superclu.size();i++){
		cout << "\tStarting loop on superclusters for plots with cuts: " << set_of_cuts_superclu[i] << endl;
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_E", "(100, 0, 500)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Energy", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_Et", "(100, 0, 500)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Et", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_RawE", "(100, 0, 500)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Raw Energy", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_RawEt", "(100, 0, 500)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Raw Et", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_Eta", "(30, -3.0, 3.0)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Eta", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_Phi", "(30, -3.15, 3.15)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster Phi", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_nXtals", "(100, 0, 100)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster number of crystals", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_nBasicClusters", "(100, 0, 100)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster number of basic clusters", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_seedSeverity", "(5,0,5)", set_of_cuts_superclu[i], name_superclu[i], "SuperClu seed Severity", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_seedTime", "(300, -40, 40)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster seed time", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_s4", "(50, -2, 100)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster s4", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_etaWidth", "(50, 0, 0.2)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster etaWidth", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_phiWidth", "(50, 0, 0.3)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster phiWidth", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_SuperCluTree, MC_SuperCluTree, "SuperClu_seedFlag", "(15, 0, 15)", set_of_cuts_superclu[i], name_superclu[i], "SuperCluster seed flag", true, true, c1);
//
	}
}

if(false){	// Plots for the events
	TTree* Data_eventTree = (TTree*) Data_File->Get("event_miniTree");
	TTree* MC_eventTree = (TTree*) MC_File->Get("event_miniTree");
	vector<string> set_of_cuts_events;
	vector<string> name_events;
//	name_events.push_back("NoCuts");
//	set_of_cuts_events.push_back("");
	for(int i=0;i<name_events.size();i++){
		cout << "\tStarting loop on events for plots with cuts: " << set_of_cuts_events[i] << endl;
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Multiplicity", "(7, 0, 7)", set_of_cuts_events[i], name_events[i], "Photon multiplicity", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "SuperClu_Multiplicity", "(30, 0, 30)", set_of_cuts_events[i], name_events[i], "Super cluster multiplicity", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Multiplicity_isAfterCut7", "(7, 0, 7)", set_of_cuts_events[i], name_events[i], "Photon multiplicity", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "SuperClu_Multiplicity_isAfterCut3", "(30, 0, 30)", set_of_cuts_events[i], name_events[i], "Super cluster multiplicity", true, true, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "nPhotonEB_perEvent", "(15, 0, 15)", set_of_cuts_events[i], name_events[i],"nPhotonEB_perEvent", true, true, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "nPhotonEE_perEvent", "(15, 0, 15)", set_of_cuts_events[i], name_events[i],"nPhotonEE_perEvent", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "nPhotonEEP_perEvent", "(15, 0, 15)", set_of_cuts_events[i], name_events[i],"nPhotonEEP_perEvent", true, true, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "nPhotonEEM_perEvent", "(15, 0, 15)", set_of_cuts_events[i], name_events[i], "nPhotonEEM_perEvent", true, true, c1);

//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon10_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Photon10_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon15_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Photon15_L1R", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon15_LooseEcalIso_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Photon15_LooseEcalIso_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon20_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Photon20_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon30_L1R_8E29", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Photon30_L1R_8E29 triggered", true, false, c1);
//
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton4_Jpsi_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton4_Jpsi_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton4_Upsilon_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton4_Upsilon_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton4_eeRes_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton4_eeRes_L1R triggered", true, false, c1);
////	DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton5_eeRes_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton5_eeRes_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton5_Jpsi_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton5_Jpsi_L1R triggered", true, false, c1);
//	
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton5_Upsilon_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton5_Upsilon_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton5_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton5_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoublePhoton10_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_DoublePhoton10_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_DoubleEle5_SW_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_DoubleEle5_SW_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele20_LW_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Ele20_LW_L1R triggered", true, false, c1);
//	
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele15_SiStrip_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Ele15_SiStrip_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele15_SC10_LW_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Ele15_SC10_LW_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele15_LW_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Ele15_LW_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele10_LW_EleId_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Ele10_LW_EleId_L1R triggered", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Ele10_LW_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Ele10_LW_L1R triggered", true, false, c1);
//	
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "HLT_Photon15_TrackIso_L1R", "(2, 0, 2)", set_of_cuts_events[i], name_events[i], "HLT_Photon15_TrackIso_L1R triggered", true, false, c1);
	}
}

	return 0;	
}

