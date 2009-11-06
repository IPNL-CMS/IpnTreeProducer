{
	TStyle* style = new TStyle("style","My Default Style with white Backgrounds");
	
	style->SetPadBottomMargin(0.15);
	style->SetPadLeftMargin(0.12);
	//style->SetPadBottomMargin(0.1);
	//style->SetPadLeftMargin(0.08);
	style->SetPadRightMargin(0.035);
	style->SetPadTopMargin(0.045);
	
	//style->SetPadGridX(1);
	//style->SetPadGridY(1);
	style->SetCanvasBorderMode(0);
	style->SetCanvasBorderSize(2);
	style->SetCanvasColor(10);
	
	style->SetFrameBorderMode(1);
	style->SetFrameBorderSize(1);
	style->SetFrameFillColor(38);
	style->SetFrameFillStyle(1);
	style->SetFrameLineColor(1);
	style->SetFrameLineStyle(0);
	style->SetFrameLineWidth(1);
	
	//style->SetHistFillColor(8);
	//style->SetHistFillStyle(1001);
	style->SetHistFillColor(3);
	//style->SetHistFillStyle(3001);
	style->SetHistLineColor(39);
	style->SetHistLineStyle(0);
	style->SetHistLineWidth(1);
	
	style->SetFuncColor(46);
	style->SetFuncStyle(1);
	style->SetFuncWidth(3);
	
	style->SetGridColor(13);
	style->SetGridStyle(3);
	style->SetGridWidth(1);
	
	style->SetFrameFillColor(10);
	style->SetCanvasColor(10);
	style->SetHistFillColor(10);
	style->SetOptStat(0);
	//style->SetOptStat(1111111);
	// style->SetOptFit(0100);
	//style->SetOptFit(0);
	style->SetOptTitle(kFALSE);
	
	gROOT->SetStyle( "style" );
	
	printf("loading libraries and macros...\n");
	gSystem->Load("libPhysics.so");
	gSystem->Load("libEG.so");
	gSystem->Load("../src/libToto.so");
	//gSystem.Load("libExRootAnalysisReader-tdrv3");
	//gROOT->ProcessLine(".L ./egROOTscripts/AccuratePeak.C");
	//gROOT->ProcessLine(".L ./egROOTscripts/effSigma.C");
	//gROOT->ProcessLine(".L ./defineDataset.C");
	
}
