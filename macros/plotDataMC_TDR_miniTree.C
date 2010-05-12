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
// essai
#pragma optimize 0

using namespace std;

void DrawDataMCplot_NormEntries_Fast(TTree *Data_eventTree, TTree *MC_eventTree, string var, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFlow, TCanvas *c1){

	// Get Histo_Data from eventTree
	TH1F *Histo_Data_temp = new TH1F();
  string variable_Data = var + ">>Histo_Data_temp" + limits;
  Data_eventTree->Draw(variable_Data.c_str(), cut.c_str());
	TH1F *Histo_Data = (TH1F*)gDirectory->Get("Histo_Data_temp"); 
	c1->Clear();

	// Get Histo_MC from eventTree
	TH1F *Histo_MC_temp = new TH1F();
	string variable_MC = var + ">>Histo_MC_temp" + limits;
	MC_eventTree->Draw(variable_MC.c_str(), cut.c_str());
	TH1F *Histo_MC = (TH1F*)gDirectory->Get("Histo_MC_temp");
	c1->Clear();

	// TODO: implement drawUnderOverFlow

	// Get the number of entries for further normalization
	double a = Histo_Data->GetEntries();
	double b = Histo_MC->GetEntries();

	// Normalize
  Histo_Data->Sumw2(); // In order to have the correct error bars on data after renormalization
	// // Normalize MC and Data to 1
	//Histo_Data->Scale((double)((double)1.0/(double)a));
	//Histo_MC->Scale((double)((double)1.0/(double)b));
	// // Normalize MC to Data number of entries
	Histo_MC->Scale((double)((double)a/(double)b));

	// Get the maxs and the mins to further correct the Y-axis
	double dataMax = Histo_Data->GetMaximumStored();
  double dataMin = Histo_Data->GetMinimumStored();
  double mcMax = Histo_MC->GetMaximumStored();
  double mcMin = Histo_MC->GetMinimumStored();
  double YMax = max(dataMax, mcMax);
  double YMin = max(dataMin, mcMin);	

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
  Histo_Data->SetMaximum(YMax);
  Histo_Data->SetMinimum(YMin);
  Histo_Data->Draw("E1");

  // // Second: draw MC on the same canvas
	Histo_MC->SetLineColor(kBlack);
  Histo_MC->SetFillColor(kYellow);
  Histo_MC->Draw("same");

	// // Third: re-draw Data so that data appears in front of MC
  Histo_Data->Draw("E1same");

	// // Fourth: redraw axis so that axis appears in front of everything
  gPad->RedrawAxis();

	// // Fifth: draw legend
  TLegend *legend = new TLegend(0.7, 0.83, 0.99, 0.994, "");
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kWhite);
  legend->SetShadowColor(kWhite);
  legend->AddEntry(Histo_Data->GetName(), "Data", "lp");
  legend->AddEntry(Histo_MC->GetName(), "MC", "f");
  legend->Draw();

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
  string MC = "miniTree_TEST_MC.root"; 
	
  TFile *Data_File = new TFile(Data.c_str());
  TFile *MC_File = new TFile(MC.c_str());
  TTree* Data_eventTree = (TTree*) Data_File->Get("miniTree");
	TTree* MC_eventTree = (TTree*) MC_File->Get("miniTree");

	TCanvas *c1 = new TCanvas("Default", "Default");

	vector<string> set_of_cuts;
	vector<string> name;
	set_of_cuts.push_back("Photon_isAfterCut6");
	name.push_back("Photon_isAfterCut6");
	set_of_cuts.push_back("Photon_isAfterCut6 && Photon_isEB");
	name.push_back("Photon_isAfterCut6_AND_Photon_isEB");
	set_of_cuts.push_back("Photon_isAfterCut6 && Photon_isEE");
	name.push_back("Photon_isAfterCut6_AND_Photon_isEE");
	set_of_cuts.push_back("Photon_isAfterCut6 && Photon_isEEP");
	name.push_back("Photon_isAfterCut6_AND_Photon_isEEP");
	set_of_cuts.push_back("Photon_isAfterCut6 && Photon_isEEM");
	name.push_back("Photon_isAfterCut6_AND_Photon_isEEM");
	set_of_cuts.push_back("Photon_SCRawEnergy>4 && Photon_isAfterCut6 && Photon_isEB");
	name.push_back("Photon_isAfterCut6_AND_Photon_isEEM_AND_Photon_SCRawEnergyGT4");

	for(int i=0; i<set_of_cuts.size() ; i++){ // loop over different set of cuts
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Multiplicity", "(15,0,15)", set_of_cuts[i], name[i], "Photon Multiplicity", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_hasPixelSeed", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon hasPixelSeed", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isAlsoElectron", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isAlsoElectron", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E", "(100, 0, 800)", set_of_cuts[i], name[i], "Photon Energy", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Et", "(100, 0, 800)", set_of_cuts[i], name[i], "Photon Et", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Eta", "(60, -3.0, 3.0)", set_of_cuts[i], name[i], "Photon Eta", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Phi", "(30, -MYPI, MYPI)", set_of_cuts[i], name[i], "Photon Phi", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_SCEta", "(60, -3.0, 3.0)", set_of_cuts[i], name[i], "Photon SC  Eta", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_SCPhi", "(30, -MYPI, MYPI)", set_of_cuts[i], name[i], "Photon SC Phi", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E2x2", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E2x2", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E3x3", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E3x3", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E5x5", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E5x5", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Emax", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon Emax", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E2nd", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon E2nd", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_r19", "(100, 0, 2)", set_of_cuts[i], name[i], "Photon r19", true, false, c1);
  	DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_r9", "(100, 0, 2)", set_of_cuts[i], name[i], "r9", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_cross", "(50, 0, 1.1)", set_of_cuts[i], name[i], "Photon cross", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_caloConeSize", "(30, 0, 0.5)", set_of_cuts[i], name[i], "Photon caloConeSize", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_SCEnergy", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon SC Energy", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_SCEt", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon SC Et", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_SCRawEnergy", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon SC Raw Energy", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_SCRawEt", "(100, 0, 1000)", set_of_cuts[i], name[i], "Photon SC Raw Et", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_PreshEnergy", "(40, 0, 10)", set_of_cuts[i], name[i], "Photon Preshower Energy", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_HoE", "(30, 0, 0.55)", set_of_cuts[i], name[i], "Photon HoE", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Nclusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon Nclusters", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_covIetaIeta", "(30, 0, 0.02)", set_of_cuts[i], name[i], "Photon covIetaIeta", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_covIphiIphi", "(30, 0, 0.025)", set_of_cuts[i], name[i], "Photon covIphiIphi", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoEcalRecHit", "(70, -2, 20)", set_of_cuts[i], name[i], "Photon isoEcalRecHit", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoHcalRecHit", "(100, -1, 10)", set_of_cuts[i], name[i], "Photon isoHcalRecHit", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoSolidTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoSolidTrkCone", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoHollowTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoHollowTrkCone", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoNTracksSolidCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksSolidCone", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoNTracksHollowCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksHollowCone", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoPersoSolidTrkCone", "(100, 0, 30)", set_of_cuts[i], name[i], "Photon isoPersoSolidTrkCone", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_convNTracks", "(4, 0, 4)", set_of_cuts[i], name[i], "Photon convNTracks", true, false, c1);
	//  TH2F* h_Photon_EtaPhi_Occupancy", "(60, -3, 3, 60, -MYPI, MYPI)", set_of_cuts[i], name[i], "Photon Multiplicity", true, false, c1);
	//  TH2F* h_Photon_Energy_vs_Phi", "(60, 0, 60, 60, -MYPI, MYPI)", set_of_cuts[i], name[i], "Photon Multiplicity", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_etaWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Eta Width", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_phiWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Phi Width", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_nBasicClusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon nBasicClusters", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_nXtals", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon nXtals", true, false, c1);
	//    DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_nRecHits", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon nRecHits", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_seedTime", "(50,-50,50)", set_of_cuts[i], name[i], "Photon seed Time", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_seedFlag", "(50,0,50)", set_of_cuts[i], name[i], "Photon seed Flag", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isTightPhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isTightPhoton", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isLoosePhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isLoosePhoton", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isolationPersoTracksSolidCone", "(30, 0, 100)", set_of_cuts[i], name[i], "Photon isolationPersoTracksSolidCone", true, false, c1);
	  DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isolationPersoNTracksSolidCone", "(30, 0, 100)", set_of_cuts[i], name[i], "Photon isolationPersoNTracksSolidCone", true, false, c1);
	
	} // end of loop over set of cuts



	return 0;	
}

