
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TVirtualPad.h>
#include <TH1.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TPaveText.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TList.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

void makePlot(const std::string& inputFilePath, const std::string& canvasName, const std::string& histogram, const std::string& channel, const std::string& xAxisTitle, const std::string& yAxisTitle,
	      const std::string& inputFileName, const std::string& outputFilePath, const std::string& outputFileName)
{
  std::string inputFileName_full = Form("%s%s", inputFilePath.data(), inputFileName.data());
  TFile* inputFile = new TFile(inputFileName_full.data());
  if ( !inputFile ) {
    std::cerr << "Failed to open input file = " << inputFileName_full << " !!" << std::endl;
    assert(0);
  }

  inputFile->ls();

  TCanvas* canvas = dynamic_cast<TCanvas*>(inputFile->Get(canvasName.data()));
  if ( !canvas ) {
    std::cerr << "Failed to load canvas = " << canvasName << " !!" << std::endl;
    assert(0);
  }

  int idxPad = -1;
  if ( histogram == "pt"  ) idxPad = 1;
  if ( histogram == "eta" ) idxPad = 2;
  if ( histogram == "phi" ) idxPad = 3;
  if ( !(idxPad >= 1 && idxPad <= 3) ) {
    std::cerr << "Invalid histogram = " << histogram << " !!" << std::endl;
    assert(0);
  }
  TVirtualPad* pad = canvas->GetPad(idxPad);
  std::cout << "pad = " << pad << ": ClassName = " << pad->ClassName() << std::endl;

  TCanvas* canvas_new = new TCanvas("canvas_new", "canvas_new", 900, 850);
  canvas_new->SetFillColor(10);
  canvas_new->SetBorderSize(2);
  canvas_new->SetTopMargin(0.065);
  canvas_new->SetLeftMargin(0.17);
  canvas_new->SetBottomMargin(0.155);
  canvas_new->SetRightMargin(0.045);
  canvas_new->SetLogx(false);
  canvas_new->SetLogy(false);
  canvas_new->Draw();
  canvas_new->cd();

  TList* pad_primitives = pad->GetListOfPrimitives();

  TH1* histogramDYJetsVis      = 0;
  TH1* histogramDYJetsLOkEq0   = 0;
  TH1* histogramDYJetsLOkNeq0  = 0;
  TH1* histogramH125Vis        = 0;
  TH1* histogramH125LOkEq0     = 0;
  TH1* histogramH125LOkNeq0    = 0;

  TIter pad_nextObj(pad_primitives);
  while ( TObject* obj = pad_nextObj() ) {
    std::string objName = "";
    if ( dynamic_cast<TNamed*>(obj) ) objName = (dynamic_cast<TNamed*>(obj))->GetName();    
    std::cout << "obj = " << obj << ": name = " << objName << ", type = " << obj->ClassName() << std::endl;

    TH1* tmpHistogram = dynamic_cast<TH1*>(obj);
    if ( tmpHistogram ) {
      std::cout << "tmpHistogram:" 
		//<< " fillColor = " << tmpHistogram->GetFillColor() << ", fillStyle = " << tmpHistogram->GetFillStyle() << ","
		<< " lineColor = " << tmpHistogram->GetLineColor() << ", lineStyle = " << tmpHistogram->GetLineStyle() << ", lineWidth = " << tmpHistogram->GetLineWidth() << ","
		//<< " markerColor = " << tmpHistogram->GetMarkerColor() << ", markerStyle = " << tmpHistogram->GetMarkerStyle() << ", markerSize = " << tmpHistogram->GetMarkerSize() << ","
		<< " integral = " << tmpHistogram->Integral() << std::endl;
      if ( tmpHistogram->GetLineColor() ==   1 ) histogramDYJetsVis      = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   3 ) histogramDYJetsLOkEq0   = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   5 ) histogramDYJetsLOkNeq0  = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   2 ) histogramH125Vis      = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   4 ) histogramH125LOkEq0   = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   6 ) histogramH125LOkNeq0  = tmpHistogram;
    }
  }

if ( !(histogramDYJetsVis && histogramDYJetsLOkEq0 && histogramDYJetsLOkNeq0 && histogramH125Vis && histogramH125LOkEq0 && histogramH125LOkNeq0) ) {
    std::cerr << "Failed to load histograms !!" << std::endl;
    assert(0);
 }
  int lineColors[6] = { 1,2,6,1,2,6 };
  int lineStyles[6] = { 7,7,7,1,1,1};
  int lineWidths[6] = { 2,2,2,2,2,2 };
  int fillColors[6] = { 0,0,0,0,0,0 };
  int fillStyles[6] = { 0,0,0,0,0,0 };

  histogramDYJetsVis->SetFillColor(fillColors[0]);
  histogramDYJetsVis->SetFillStyle(fillStyles[0]);
  histogramDYJetsVis->SetLineColor(lineColors[0]);
  histogramDYJetsVis->SetLineStyle(lineStyles[0]);
  histogramDYJetsVis->SetLineWidth(lineWidths[0]);
  
  histogramDYJetsLOkEq0->SetFillColor(fillColors[1]);
  histogramDYJetsLOkEq0->SetFillStyle(fillStyles[1]);
  histogramDYJetsLOkEq0->SetLineColor(lineColors[1]);
  histogramDYJetsLOkEq0->SetLineStyle(lineStyles[1]);
  histogramDYJetsLOkEq0->SetLineWidth(lineWidths[1]);
  
  histogramDYJetsLOkNeq0->SetFillColor(fillColors[2]);
  histogramDYJetsLOkNeq0->SetFillStyle(fillStyles[2]);
  histogramDYJetsLOkNeq0->SetLineColor(lineColors[2]);
  histogramDYJetsLOkNeq0->SetLineStyle(lineStyles[2]);
  histogramDYJetsLOkNeq0->SetLineWidth(lineWidths[2]);

  histogramH125Vis->SetFillColor(fillColors[3]);
  histogramH125Vis->SetFillStyle(fillStyles[3]);
  histogramH125Vis->SetLineColor(lineColors[3]);
  histogramH125Vis->SetLineStyle(lineStyles[3]);
  histogramH125Vis->SetLineWidth(lineWidths[3]);
  
  histogramH125LOkEq0->SetFillColor(fillColors[4]);
  histogramH125LOkEq0->SetFillStyle(fillStyles[4]);
  histogramH125LOkEq0->SetLineColor(lineColors[4]);
  histogramH125LOkEq0->SetLineStyle(lineStyles[4]);
  histogramH125LOkEq0->SetLineWidth(lineWidths[4]);
  
  histogramH125LOkNeq0->SetFillColor(fillColors[5]);
  histogramH125LOkNeq0->SetFillStyle(fillStyles[5]);
  histogramH125LOkNeq0->SetLineColor(lineColors[5]);
  histogramH125LOkNeq0->SetLineStyle(lineStyles[5]);
  histogramH125LOkNeq0->SetLineWidth(lineWidths[5]);

  TAxis* xAxis = histogramH125LOkNeq0->GetXaxis();
  string title = xAxisTitle.data();
  if(title.find("GeV")==std::string::npos) xAxis->SetRangeUser(-3,4);
  xAxis->SetTitle(xAxisTitle.data());
  xAxis->SetTitleOffset(1.00);
  xAxis->SetTitleSize(0.070);
  xAxis->SetTitleFont(42);
  xAxis->SetLabelOffset(0.010);
  xAxis->SetLabelSize(0.050);
  xAxis->SetLabelFont(42);
  xAxis->SetTickLength(0.040);
  xAxis->SetNdivisions(505);

  TAxis* yAxis =histogramH125LOkNeq0 ->GetYaxis();
  yAxis->SetTitle(yAxisTitle.data());
  yAxis->SetTitleOffset(1.20);
  yAxis->SetTitleSize(0.070);
  yAxis->SetTitleFont(42);
  yAxis->SetLabelOffset(0.010);
  yAxis->SetLabelSize(0.055);
  yAxis->SetLabelFont(42);
  yAxis->SetTickLength(0.040);  
  yAxis->SetNdivisions(505);

  histogramH125LOkNeq0->SetTitle("");
  histogramH125LOkNeq0->SetStats(false);
  //histogramHiggs300->SetMaximum(0.41);
  //histogramHiggs300->SetMinimum(0.);
  histogramH125LOkNeq0->Draw("hist");
  histogramH125LOkEq0->Draw("histsame");
  histogramH125Vis->Draw("histsame");
  //histogramDYJetsLOkNeq0->Draw("histsame");
  //histogramDYJetsLOkEq0->Draw("histsame");
  //histogramDYJetsVis->Draw("histsame");
  histogramH125LOkNeq0->Draw("axissame");

  TLegend* legend_new = new TLegend(0.57, 0.72, 0.86, 0.91, NULL, "brNDC");
  legend_new->SetFillColor(10);
  legend_new->SetFillStyle(0);
  legend_new->SetBorderSize(0);
  legend_new->SetTextFont(42);
  legend_new->SetTextSize(0.055);
  legend_new->SetTextColor(1);
  legend_new->SetMargin(0.20);
  legend_new->AddEntry(histogramH125Vis, "#tau_{1,vis}+#tau_{2,vis}+E^{miss}_{T} ", "f");
  legend_new->AddEntry(histogramH125LOkEq0, "cSVfit #kappa=0", "f");
  if(channel == "e#mu")             legend_new->AddEntry(histogramH125LOkNeq0, "cSVfit #kappa=3", "f");
  if(channel == "#mu#tau_{h}")      legend_new->AddEntry(histogramH125LOkNeq0, "cSVfit #kappa=4", "f");
  if(channel == "#tau_{h}#tau_{h}") legend_new->AddEntry(histogramH125LOkNeq0, "cSVfit #kappa=5", "f");
  legend_new->Draw();

  double label_channel_y0;
  if      ( channel == "e#mu"             ) label_channel_y0 = 0.9275;
  else if ( channel == "#mu#tau_{h}"      ) label_channel_y0 = 0.9400;
  else if ( channel == "#tau_{h}#tau_{h}" ) label_channel_y0 = 0.9350;
  else {
	  std::cerr << "Invalid channel = " << channel << " !!" << std::endl;
	  assert(0);
  }
  TPaveText* label_channel = new TPaveText(0.855, label_channel_y0, 0.945, label_channel_y0 + 0.055, "NDC");
  label_channel->SetFillStyle(0);
  label_channel->SetBorderSize(0);
  label_channel->AddText(channel.data());
  label_channel->SetTextFont(62);
  label_channel->SetTextSize(0.055);
  label_channel->SetTextColor(1);
  label_channel->SetTextAlign(31);
  label_channel->Draw();

  TPaveText* label_sample = new TPaveText(0.17, 0.938, 0.4600, 0.965, "NDC");
  label_sample->SetFillStyle(0);
  label_sample->SetBorderSize(0);
  label_sample->AddText("gg #rightarrow H(125 GeV) #rightarrow #tau#tau");
  label_sample->SetTextFont(42);
  label_sample->SetTextSize(0.055);
  label_sample->SetTextColor(1);
  label_sample->SetTextAlign(11);
  label_sample->Draw();

  canvas_new->Update();

  std::string outputFileName_full = Form("%s%s", outputFilePath.data(), outputFileName.data());
  size_t idx = outputFileName_full.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName_full, 0, idx);
  canvas_new->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas_new->Print(std::string(outputFileName_plot).append(".root").data());

  delete legend_new;
  delete label_channel;
  delete canvas_new;

  delete inputFile;
}

void makeSVfitMEM_massPlots_from14()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::vector<int> massPoints;
  massPoints.push_back(90);
  massPoints.push_back(125);
  massPoints.push_back(200);
  massPoints.push_back(300);
  massPoints.push_back(500);
  massPoints.push_back(800);
  
  std::vector<std::string> histograms;
  histograms.push_back("pt");
  histograms.push_back("eta");
  histograms.push_back("phi");

  std::map<std::string, std::string> xAxisTitles; // key = histogram
  xAxisTitles["pt"]    = "#Delta p_{T} [GeV]";
  xAxisTitles["eta"]   = "#Delta #eta";
  xAxisTitles["phi"]   = "#Delta #phi";

  std::map<std::string, std::string> yAxisTitles; // key = histogram
  yAxisTitles["pt"]  = "dN/d#Delta p_{T} [1/GeV]";
  yAxisTitles["eta"] = "dN/d#Delta #eta";
  yAxisTitles["phi"] = "dN/d#Delta #phi";
  
  std::string inputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/";
  std::map<std::string, std::string> inputFileNames_emu; // key = histogram
  inputFileNames_emu["pt"]     = "plot_14_lin_ratio_emu_smeared.root";
  inputFileNames_emu["eta"]    = "plot_14_lin_ratio_emu_smeared.root";
  inputFileNames_emu["phi"]    = "plot_14_lin_ratio_emu_smeared.root";
  std::map<std::string, std::string> inputFileNames_muhad; // key = histogram
  inputFileNames_muhad["pt"]   = "plot_14_lin_ratio_muhad_smeared.root";
  inputFileNames_muhad["eta"]  = "plot_14_lin_ratio_muhad_smeared.root";
  inputFileNames_muhad["phi"]  = "plot_14_lin_ratio_muhad_smeared.root";
  std::map<std::string, std::string> inputFileNames_hadhad; // key = mhistogram
  inputFileNames_hadhad["pt"]   = "plot_14_lin_ratio_hadhad_smeared.root";
  inputFileNames_hadhad["eta"]  = "plot_14_lin_ratio_hadhad_smeared.root";
  inputFileNames_hadhad["phi"]  = "plot_14_lin_ratio_hadhad_smeared.root";

  std::string outputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/finalplots/";
  std::map<std::string, std::string> outputFileNames_emu; // key = histogram
  outputFileNames_emu["pt"]      = "Higgs_resolution_pT_emu.root";
  outputFileNames_emu["eta"]     = "Higgs_resolution_eta_emu.root";
  outputFileNames_emu["phi"]     = "Higgs_resolution_phi_emu.root";
  std::map<std::string, std::string> outputFileNames_muhad; // key = histogram
  outputFileNames_muhad["pt"]      = "Higgs_resolution_pT_muhad.root";
  outputFileNames_muhad["eta"]     = "Higgs_resolution_eta_muhad.root";
  outputFileNames_muhad["phi"]     = "Higgs_resolution_phi_muhad.root";
  std::map<std::string, std::string> outputFileNames_hadhad; // key = histogram
  outputFileNames_hadhad["pt"]      = "Higgs_resolution_pT_hadhad.root";
  outputFileNames_hadhad["eta"]     = "Higgs_resolution_eta_hadhad.root";
  outputFileNames_hadhad["phi"]     = "Higgs_resolution_phi_hadhad.root";
  
  for ( std::vector<std::string>::const_iterator histogram = histograms.begin();
	histogram != histograms.end(); ++histogram ) {
    std::string xAxisTitle_emu        = xAxisTitles[*histogram];
    std::string yAxisTitle_emu        = yAxisTitles[*histogram];
    std::string inputFileName_emu     = inputFileNames_emu[*histogram];
    std::string outputFileName_emu    = outputFileNames_emu[*histogram];
    makePlot(inputFilePath, "emu_smeared", *histogram, "e#mu", xAxisTitle_emu, yAxisTitle_emu, inputFileName_emu, outputFilePath, outputFileName_emu);
    std::string xAxisTitle_muhad      = xAxisTitles[*histogram];
    std::string yAxisTitle_muhad      = yAxisTitles[*histogram];
    std::string inputFileName_muhad   = inputFileNames_muhad[*histogram];
    std::string outputFileName_muhad  = outputFileNames_muhad[*histogram];
    makePlot(inputFilePath, "muhad_smeared", *histogram, "#mu#tau_{h}", xAxisTitle_muhad, yAxisTitle_muhad, inputFileName_muhad, outputFilePath, outputFileName_muhad);
    std::string xAxisTitle_hadhad     = xAxisTitles[*histogram];
    std::string yAxisTitle_hadhad     = yAxisTitles[*histogram];
    std::string inputFileName_hadhad  = inputFileNames_hadhad[*histogram];
    std::string outputFileName_hadhad = outputFileNames_hadhad[*histogram];
    makePlot(inputFilePath, "hadhad_smeared", *histogram, "#tau_{h}#tau_{h}", xAxisTitle_hadhad, yAxisTitle_hadhad, inputFileName_hadhad, outputFilePath, outputFileName_hadhad);
  }
}
