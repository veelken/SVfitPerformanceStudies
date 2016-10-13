
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
  if ( histogram == "Higgs"  ) idxPad = 1;
  if ( histogram == "DYJets" ) idxPad = 2;
  if ( !(idxPad >= 1 && idxPad <= 2) ) {
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
  canvas_new->SetLogx(true);
  canvas_new->SetLogy(true);
  canvas_new->Draw();
  canvas_new->cd();

  TList* pad_primitives = pad->GetListOfPrimitives();

  TH1* histogramSVfit           = 0;
  TH1* histogramSVfitMEMkNeq0    = 0;
  TH1* histogramSVfitMEMkEq0   = 0;
  TH1* histogramcSVfitkEq0      = 0;
  TH1* histogramcSVfitkNeq0     = 0;

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
      if ( tmpHistogram->GetLineColor() ==   1 ) histogramSVfit          = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   2 ) histogramSVfitMEMkEq0   = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   3 ) histogramcSVfitkEq0     = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   4 ) histogramSVfitMEMkNeq0  = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   5 ) histogramcSVfitkNeq0    = tmpHistogram;
    }
  }

  if ( !(histogramSVfit && histogramSVfitMEMkEq0 && histogramcSVfitkEq0 && histogramSVfitMEMkNeq0 && histogramcSVfitkNeq0) ) {
	  std::cerr << "Failed to load histograms !!" << std::endl;
	  assert(0);
  }

  int colors[5]       = { kGreen - 6, kBlue - 7, kRed, kMagenta -7, kBlack };
  int lineStyles[5]   = { 1, 1, 1, 1, 1 };
  int lineWidths[5]   = { 2, 2, 2 ,2, 2};

  histogramSVfit->SetLineColor(colors[0]);
  histogramSVfit->SetLineStyle(lineStyles[0]);
  histogramSVfit->SetLineWidth(lineWidths[0]);
  
  histogramcSVfitkEq0->SetLineColor(colors[1]);
  histogramcSVfitkEq0->SetLineStyle(lineStyles[1]);
  histogramcSVfitkEq0->SetLineWidth(lineWidths[1]);

  histogramcSVfitkNeq0->SetLineColor(colors[2]);
  histogramcSVfitkNeq0->SetLineStyle(lineStyles[2]);
  histogramcSVfitkNeq0->SetLineWidth(lineWidths[2]);
  
  histogramSVfitMEMkEq0->SetLineColor(colors[3]);
  histogramSVfitMEMkEq0->SetLineStyle(lineStyles[3]);
  histogramSVfitMEMkEq0->SetLineWidth(lineWidths[3]);
  
  histogramSVfitMEMkNeq0->SetLineColor(colors[4]);
  histogramSVfitMEMkNeq0->SetLineStyle(lineStyles[4]);
  histogramSVfitMEMkNeq0->SetLineWidth(lineWidths[4]);

  TAxis* xAxis = histogramSVfitMEMkNeq0->GetXaxis();
  string title = xAxisTitle.data();
  xAxis->SetTitle(xAxisTitle.data());
  xAxis->SetTitleOffset(1.00);
  xAxis->SetTitleSize(0.070);
  xAxis->SetTitleFont(42);
  xAxis->SetLabelOffset(0.010);
  xAxis->SetLabelSize(0.050);
  xAxis->SetLabelFont(42);
  xAxis->SetTickLength(0.040);
  xAxis->SetNdivisions(505);

  TAxis* yAxis = histogramSVfitMEMkNeq0->GetYaxis();
  yAxis->SetTitle(yAxisTitle.data());
  yAxis->SetTitleOffset(1.20);
  yAxis->SetTitleSize(0.070);
  yAxis->SetTitleFont(42);
  yAxis->SetRangeUser(0.001,10);
  yAxis->SetLabelOffset(0.010);
  yAxis->SetLabelSize(0.055);
  yAxis->SetLabelFont(42);
  yAxis->SetTickLength(0.040);  
  yAxis->SetNdivisions(505);

  histogramSVfitMEMkNeq0->SetTitle("");
  histogramSVfitMEMkNeq0->SetStats(false);
  histogramSVfitMEMkNeq0->Draw("hist");
  histogramSVfitMEMkEq0->Draw("histsame");
  histogramcSVfitkEq0->Draw("histsame");
  histogramcSVfitkNeq0->Draw("histsame");
  histogramSVfit->Draw("histsame");
  histogramSVfitMEMkNeq0->Draw("axissame");

  TLegend* legend_new = new TLegend(0.50, 0.65, 0.86, 0.92, NULL, "brNDC");
  legend_new->SetFillColor(10);
  legend_new->SetFillStyle(0);
  legend_new->SetBorderSize(0);
  legend_new->SetTextFont(42);
  legend_new->SetTextSize(0.055);
  legend_new->SetTextColor(1);
  legend_new->SetMargin(0.20);
  legend_new->AddEntry(histogramSVfit, "SVfitSA ", "f");
  legend_new->AddEntry(histogramcSVfitkEq0, "cSVfit (#kappa=0)", "f");
  if(channel == "e#mu")             legend_new->AddEntry(histogramcSVfitkNeq0, "cSVfit (#kappa=3)", "f");
  if(channel == "#mu#tau_{h}")      legend_new->AddEntry(histogramcSVfitkNeq0, "cSVfit (#kappa=4)", "f");
  if(channel == "#tau_{h}#tau_{h}") legend_new->AddEntry(histogramcSVfitkNeq0, "cSVfit (#kappa=5)", "f");
  legend_new->AddEntry(histogramSVfitMEMkEq0, "SVfitMEM #kappa=0", "f");
  if(channel == "e#mu")             legend_new->AddEntry(histogramSVfitMEMkNeq0, "SVfitMEM (#kappa=3)", "f");
  if(channel == "#mu#tau_{h}")      legend_new->AddEntry(histogramSVfitMEMkNeq0, "SVfitMEM (#kappa=4)", "f");
  if(channel == "#tau_{h}#tau_{h}") legend_new->AddEntry(histogramSVfitMEMkNeq0, "SVfitMEM (#kappa=5)", "f");
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
  if ( histogram == "Higgs"  ) label_sample->AddText("H(125 GeV) #rightarrow #tau#tau");
  if ( histogram == "DYJets" ) label_sample->AddText("Z/#gamma* #rightarrow #tau#tau"); 
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

void makeSVfitMEM_massPlots_from15()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::vector<std::string> histograms;
  histograms.push_back("Higgs");
  histograms.push_back("DYJets");

  std::map<std::string, std::string> xAxisTitles; // key = histogram
  xAxisTitles["Higgs"]    = "t [s]";
  xAxisTitles["DYJets"]   = "t [s]";

  std::map<std::string, std::string> yAxisTitles; // key = histogram
  yAxisTitles["Higgs"]  = "dN/dt [1/s]";
  yAxisTitles["DYJets"] = "dN/dt [1/s]";
  
  std::string inputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/";
  std::map<std::string, std::string> inputFileNames_emu; // key = histogram
  inputFileNames_emu["Higgs"]     = "plot_15_log_ratio_emu_smeared.root";
  inputFileNames_emu["DYJets"]    = "plot_15_log_ratio_emu_smeared.root";
  std::map<std::string, std::string> inputFileNames_muhad; // key = histogram
  inputFileNames_muhad["Higgs"]     = "plot_15_log_ratio_muhad_smeared.root";
  inputFileNames_muhad["DYJets"]    = "plot_15_log_ratio_muhad_smeared.root";
  std::map<std::string, std::string> inputFileNames_hadhad; // key = mhistogram
  inputFileNames_hadhad["Higgs"]     = "plot_15_log_ratio_hadhad_smeared.root";
  inputFileNames_hadhad["DYJets"]    = "plot_15_log_ratio_hadhad_smeared.root";

  std::string outputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/finalplots/";
  std::map<std::string, std::string> outputFileNames_emu; // key = histogram
  outputFileNames_emu["Higgs"]     = "Higgs_cpuTime_emu.root";
  outputFileNames_emu["DYJets"]    = "DYJets_cpuTime_emu.root";
  std::map<std::string, std::string> outputFileNames_muhad; // key = histogram
  outputFileNames_muhad["Higgs"]   = "Higgs_cpuTime_muhad.root";
  outputFileNames_muhad["DYJets"]  = "DYJets_cpuTime_muhad.root";
  std::map<std::string, std::string> outputFileNames_hadhad; // key = mhistogram
  outputFileNames_hadhad["Higgs"]  = "Higgs_cpuTime_hadhad.root";
  outputFileNames_hadhad["DYJets"] = "DYJets_cpuTime_hadhad.root";
  
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
