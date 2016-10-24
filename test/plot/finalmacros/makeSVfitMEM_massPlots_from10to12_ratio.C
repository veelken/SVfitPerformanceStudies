
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

void makePlot_legend(TLegend* legend, const std::string& outputFilePath, const std::string& outputFileName)
{
  TCanvas* canvas_legend = new TCanvas("canvas_legend", "canvas_legend", 900, 800);
  canvas_legend->SetFillColor(10);
  canvas_legend->SetBorderSize(2);
  canvas_legend->Draw();
  canvas_legend->cd();

  legend->SetX1NDC(0.30);
  legend->SetY1NDC(0.30);
  legend->SetX2NDC(0.80);
  legend->SetY2NDC(0.80);
  legend->SetTextSize(0.070);
  legend->SetMargin(0.20);
  TList* legend_primitives = legend->GetListOfPrimitives();
  TIter legend_nextObj(legend_primitives);
  while ( TObject* obj = legend_nextObj() ) {
    std::string objName = "";
    if ( dynamic_cast<TNamed*>(obj) ) objName = (dynamic_cast<TNamed*>(obj))->GetName();    
    //std::cout << "obj = " << obj << ": name = " << objName << ", type = " << obj->ClassName() << std::endl;

    TLegendEntry* legendEntry = dynamic_cast<TLegendEntry*>(obj);
    if ( legendEntry ) {
      TH1* histogram = dynamic_cast<TH1*>(legendEntry->GetObject());
      if ( histogram ) {
	histogram->SetLineWidth(2*histogram->GetLineWidth());
	histogram->SetMarkerSize(3);
      }
    }
  }
  legend->Draw();

  canvas_legend->Update();

  std::string outputFileName_full = Form("%s%s", outputFilePath.data(), outputFileName.data());
  size_t idx = outputFileName_full.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName_full, 0, idx);
  canvas_legend->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas_legend->Print(std::string(outputFileName_plot).append(".root").data());

  delete canvas_legend;
}

void makePlot(const std::string& inputFilePath, const std::string& canvasName, const std::string& sample, int massPoint, const std::string& channel, double k, 
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
  if ( massPoint == 200 )  idxPad = 1;
  if ( massPoint == 300 )  idxPad = 2;
  if ( massPoint == 500 )  idxPad = 3;
  if ( massPoint == 800 )  idxPad = 4;  
  if ( massPoint == 1200 ) idxPad = 5;  
  if ( !(idxPad >= 1 && idxPad <= 6) ) {
    std::cerr << "Invalid sample = " << sample << " !!" << std::endl;
    assert(0);
  }
  TVirtualPad* pad = canvas->GetPad(idxPad);
  std::cout << "pad = " << pad << ": ClassName = " << pad->ClassName() << std::endl;

  TCanvas* canvas_new = new TCanvas("canvas_new", "canvas_new", 900, 800);
  canvas_new->SetFillColor(10);
  canvas_new->SetBorderSize(2);
  canvas_new->SetTopMargin(0.065);
  canvas_new->SetLeftMargin(0.17);
  canvas_new->SetBottomMargin(0.165);
  canvas_new->SetRightMargin(0.025); //before was 0.015
  canvas_new->SetLogx(true);
  canvas_new->SetLogy(true);
  canvas_new->Draw();
  canvas_new->cd();

  //TList* pad_primitives = canvas->GetListOfPrimitives();
  TList* pad_primitives = pad->GetListOfPrimitives();

  TH1* histogramCA            = 0;
  TH1* histogramSVfit         = 0;
  TH1* histogramSVfitMEMkEq0  = 0;
  TH1* histogramSVfitMEMkNeq0 = 0;
  TH1* histogramSVfitCLAkEq0  = 0;
  TH1* histogramSVfitCLAkNeq0 = 0;

  TIter pad_nextObj(pad_primitives);
  while ( TObject* obj = pad_nextObj() ) {
    std::string objName = "";
    if ( dynamic_cast<TNamed*>(obj) ) objName = (dynamic_cast<TNamed*>(obj))->GetName();    
    std::cout << "obj = " << obj << ": name = " << objName << ", type = " << obj->ClassName() << std::endl;

    TH1* tmpHistogram = dynamic_cast<TH1*>(obj);
    if ( tmpHistogram ) {
      std::cout << "tmpHistogram:" 
		<< " fillColor = " << tmpHistogram->GetFillColor() << ", fillStyle = " << tmpHistogram->GetFillStyle() << ","
		<< " lineColor = " << tmpHistogram->GetLineColor() << ", lineStyle = " << tmpHistogram->GetLineStyle() << ", lineWidth = " << tmpHistogram->GetLineWidth() << ","
		<< " markerColor = " << tmpHistogram->GetMarkerColor() << ", markerStyle = " << tmpHistogram->GetMarkerStyle() << ", markerSize = " << tmpHistogram->GetMarkerSize() << ","
		<< " integral = " << tmpHistogram->Integral() << std::endl;
      std::cout << "(mean = " << tmpHistogram->GetMean() << ", rms = " << tmpHistogram->GetRMS() << ": rms/mean = " << (tmpHistogram->GetRMS()/tmpHistogram->GetMean()) << ")" << std::endl;
      if ( tmpHistogram->GetLineColor() == 416 ) histogramCA            = tmpHistogram;
      if ( tmpHistogram->GetLineColor() == 600 ) histogramSVfit         = tmpHistogram;
      if ( tmpHistogram->GetLineColor() == 616 ) histogramSVfitMEMkEq0  = tmpHistogram;
      if ( tmpHistogram->GetLineColor() == 632 ) histogramSVfitMEMkNeq0 = tmpHistogram;
      if ( tmpHistogram->GetLineColor() == 1   ) histogramSVfitCLAkEq0  = tmpHistogram;
      if ( tmpHistogram->GetLineColor() == 800 ) histogramSVfitCLAkNeq0 = tmpHistogram;
    }
  }

  if ( !(histogramSVfitCLAkEq0 && histogramSVfitCLAkNeq0 && histogramCA && histogramSVfit && histogramSVfitMEMkEq0 && histogramSVfitMEMkNeq0) ) {
    std::cerr << "Failed to load histograms !!" << std::endl;
    assert(0);
  }

  //gStyle->SetLineStyleString(2,"40 10 10 10 10 10 10 10");
  //gStyle->SetLineStyleString(3,"25 15");
  //gStyle->SetLineStyleString(4,"60 25");

  int colors[6]       = { 28, kGreen - 6, kBlue - 7, kBlack, kMagenta -7, kBlack };
  int lineStyles[6]   = { 7, 1, 1, 1, 1, 1 };
  int lineWidths[6]   = { 8, 8, 1, 1, 1, 1 };
  int markerStyles[6] = { 20, 25, 21, 24, 22, 32};
  int markerSizes[6]  = { 4, 4, 3, 3, 3, 3};

  histogramCA->SetFillColor(0);
  histogramCA->SetFillStyle(0);
  histogramCA->SetLineColor(colors[0]);
  histogramCA->SetLineStyle(lineStyles[0]);
  histogramCA->SetLineWidth(lineWidths[0]);
  histogramCA->SetMarkerColor(colors[0]);
  //histogramCA->SetMarkerStyle(markerStyles[0]);
  //histogramCA->SetMarkerSize(markerSizes[0]);

  histogramSVfit->SetFillColor(0);
  histogramSVfit->SetFillStyle(0);
  histogramSVfit->SetLineColor(colors[1]);
  histogramSVfit->SetLineStyle(lineStyles[1]);
  histogramSVfit->SetLineWidth(lineWidths[1]);
  histogramSVfit->SetMarkerColor(colors[1]);
  histogramSVfit->SetMarkerStyle(markerStyles[1]);
  histogramSVfit->SetMarkerSize(markerSizes[1]);

  histogramSVfitMEMkEq0->SetFillColor(0);
  histogramSVfitMEMkEq0->SetFillStyle(0);
  histogramSVfitMEMkEq0->SetLineColor(colors[2]);
  histogramSVfitMEMkEq0->SetLineStyle(lineStyles[2]);
  histogramSVfitMEMkEq0->SetLineWidth(lineWidths[2]);
  histogramSVfitMEMkEq0->SetMarkerColor(colors[2]);
  histogramSVfitMEMkEq0->SetMarkerStyle(markerStyles[2]);
  histogramSVfitMEMkEq0->SetMarkerSize(markerSizes[2]);
  // CV: fix pathological bins at high mass for which dN/dm increases
  int numBins = histogramSVfitMEMkEq0->GetNbinsX();
  for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
    double binCenter = histogramSVfitMEMkEq0->GetBinCenter(idxBin);
    if ( (channel == "#tau_{h}#tau_{h}" && massPoint == 200  && binCenter > 4.) ||
	 (channel == "#tau_{h}#tau_{h}" && massPoint == 300  && binCenter > 4.) ||
	 (channel == "#tau_{h}#tau_{h}" && massPoint == 500  && binCenter > 3.) ||
	 (channel == "#tau_{h}#tau_{h}" && massPoint == 800  && binCenter > 3.) ||
	 (channel == "#tau_{h}#tau_{h}" && massPoint == 1200 && binCenter > 2.) ||
	 (channel == "#mu#tau_{h}"      && massPoint == 800  && binCenter > 3.) ||
	 (channel == "#mu#tau_{h}"      && massPoint == 1200 && binCenter > 3.) ||
	 (channel == "e#mu"             && massPoint == 300  && binCenter > 3.) ){
      histogramSVfitMEMkEq0->SetBinContent(idxBin, 0.);
    }
  }


  histogramSVfitMEMkNeq0->SetFillColor(0);
  histogramSVfitMEMkNeq0->SetFillStyle(0);
  histogramSVfitMEMkNeq0->SetLineColor(colors[3]);
  histogramSVfitMEMkNeq0->SetLineStyle(lineStyles[3]);
  histogramSVfitMEMkNeq0->SetLineWidth(lineWidths[3]);
  histogramSVfitMEMkNeq0->SetMarkerColor(colors[3]);
  histogramSVfitMEMkNeq0->SetMarkerStyle(markerStyles[3]);
  histogramSVfitMEMkNeq0->SetMarkerSize(markerSizes[3]);
  
  histogramSVfitCLAkEq0->SetFillColor(0);
  histogramSVfitCLAkEq0->SetFillStyle(0);
  histogramSVfitCLAkEq0->SetLineColor(colors[4]);
  histogramSVfitCLAkEq0->SetLineStyle(lineStyles[4]);
  histogramSVfitCLAkEq0->SetLineWidth(lineWidths[4]);
  histogramSVfitCLAkEq0->SetMarkerColor(colors[4]);
  histogramSVfitCLAkEq0->SetMarkerStyle(markerStyles[4]);
  histogramSVfitCLAkEq0->SetMarkerSize(markerSizes[4]);
  
  histogramSVfitCLAkNeq0->SetFillColor(0);
  histogramSVfitCLAkNeq0->SetFillStyle(0);
  histogramSVfitCLAkNeq0->SetLineColor(colors[5]);
  histogramSVfitCLAkNeq0->SetLineStyle(lineStyles[5]);
  histogramSVfitCLAkNeq0->SetLineWidth(lineWidths[5]);
  histogramSVfitCLAkNeq0->SetMarkerColor(colors[5]);
  histogramSVfitCLAkNeq0->SetMarkerStyle(markerStyles[5]);
  histogramSVfitCLAkNeq0->SetMarkerSize(markerSizes[5]);

  TAxis* xAxis = histogramCA->GetXaxis();
  xAxis->SetTitle("m_{#tau#tau}/m^{true}_{#tau#tau}");
  xAxis->SetTitleOffset(0.9);
  xAxis->SetTitleSize(60);
  xAxis->SetTitleFont(43);
  //xAxis->SetLabelOffset(0.010);
  xAxis->SetLabelSize(50);
  xAxis->SetLabelFont(43);
  xAxis->SetTickLength(0.040);
  xAxis->SetNdivisions(505);
  xAxis->SetRangeUser(0.01,8);

  TAxis* yAxis = histogramCA->GetYaxis();
  yAxis->SetTitle("dN/d(m_{#tau#tau}/m^{true}_{#tau#tau})");
  yAxis->SetRangeUser(0.002,9);
  yAxis->SetTitleSize(60);
  yAxis->SetTitleFont(43);
  //yAxis->SetLabelOffset(0.010);
  yAxis->SetLabelSize(50);
  yAxis->SetLabelFont(43);
  yAxis->SetTickLength(0.040);  
  yAxis->SetNdivisions(505);

  double massPoint_double = 0.;
  if ( massPoint == 90 ) massPoint_double = 91.2;
  else massPoint_double = massPoint;
  double dLog = (TMath::Log(5.*massPoint_double) - TMath::Log(50.))/25.; // xMin = 50, xMax = 5*massPoint, numBins = 25
  double binWidth = TMath::Exp(TMath::Log(massPoint_double) + 0.5*dLog) - TMath::Exp(TMath::Log(massPoint_double) - 0.5*dLog);
  double sf_binWidth = 1./binWidth;
  std::cout << "massPoint = " << massPoint << ": sf_binWidth = " << sf_binWidth << std::endl;

  histogramCA->SetTitle("");
  histogramCA->SetStats(false);
  histogramCA->GetXaxis()->SetRangeUser(0.01,8);
  //histogramCA->SetMaximum(sf_binWidth*0.79);
  //histogramCA->SetMinimum(sf_binWidth*1.1e-4);
  histogramCA->Draw("hist");
  histogramSVfit->Draw("histsame");
  //histogramSVfitMEMkEq0->Draw("histsame");
  histogramSVfitMEMkEq0->Draw("epsame");
  //histogramSVfitMEMkNeq0->Draw("histsame");
  histogramSVfitMEMkNeq0->Draw("epsame");
  histogramSVfitCLAkEq0->Draw("epsame");
  histogramSVfitCLAkNeq0->Draw("epsame");
  histogramCA->Draw("axissame");

  //TPaveText* label_sample = new TPaveText(0.21, 0.86, 0.46, 0.94, "NDC");
  TPaveText* label_sample = new TPaveText(0.1700, 0.9475, 0.4600, 1.0375, "NDC");
  label_sample->SetFillStyle(0);
  label_sample->SetBorderSize(0);
  label_sample->AddText(sample.data());
  label_sample->SetTextFont(42);
  label_sample->SetTextSize(0.055);
  label_sample->SetTextColor(1);
  label_sample->SetTextAlign(13);
  label_sample->Draw();

  //TLegend* legend_new = new TLegend(0.225, 0.52, 0.41, 0.82, NULL, "brNDC");
  TLegend* legend_new = new TLegend(0.30, 0.30, 0.80, 0.80, NULL, "brNDC");
  legend_new->SetFillColor(10);
  legend_new->SetFillStyle(0);
  legend_new->SetBorderSize(0);
  legend_new->SetTextFont(42);
  legend_new->SetTextSize(0.055);
  legend_new->SetTextColor(1);
  legend_new->SetMargin(0.20);
  legend_new->AddEntry(histogramCA, "CA", "l");
  legend_new->AddEntry(histogramSVfit, "SVfitSA", "l");
  legend_new->AddEntry(histogramSVfitMEMkEq0, "SVfitMEM (#kappa=0)", "p");
  legend_new->AddEntry(histogramSVfitMEMkNeq0, Form("SVfitMEM (#kappa=%1.0f)", k), "p");
  legend_new->AddEntry(histogramSVfitCLAkEq0, "cSVfit (#kappa=0)", "p");
  legend_new->AddEntry(histogramSVfitCLAkNeq0, Form("cSVfit (#kappa=%1.0f)",k), "p");
  //legend_new->Draw();

  double label_channel_y0;
  if      ( channel == "e#mu"             ) label_channel_y0 = 0.9275;
  else if ( channel == "#mu#tau_{h}"      ) label_channel_y0 = 0.9400;
  else if ( channel == "#tau_{h}#tau_{h}" ) label_channel_y0 = 0.9350;
  else {
    std::cerr << "Invalid channel = " << channel << " !!" << std::endl;
    assert(0);
  }
  TPaveText* label_channel = new TPaveText(0.895, label_channel_y0, 0.975, label_channel_y0 + 0.055, "NDC");
  label_channel->SetFillStyle(0);
  label_channel->SetBorderSize(0);
  label_channel->AddText(channel.data());
  label_channel->SetTextFont(62);
  label_channel->SetTextSize(0.055);
  label_channel->SetTextColor(1);
  label_channel->SetTextAlign(31);
  label_channel->Draw();

  canvas_new->Update();

  std::string outputFileName_full = Form("%s%s", outputFilePath.data(), outputFileName.data());
  size_t idx = outputFileName_full.find_last_of('.');
  std::string outputFileName_plot = std::string(outputFileName_full, 0, idx);
  canvas_new->Print(std::string(outputFileName_plot).append(".pdf").data());
  canvas_new->Print(std::string(outputFileName_plot).append(".root").data());

  std::string channel_string;
  if      ( channel == "e#mu"             ) channel_string = "emu";
  else if ( channel == "#mu#tau_{h}"      ) channel_string = "muhad";
  else if ( channel == "#tau_{h}#tau_{h}" ) channel_string = "hadhad";
  else {
    std::cerr << "Invalid channel = " << channel << " !!" << std::endl;
    assert(0);
  }
  std::string outputFileName_legend = Form("makeSVfitMEM_PerformancePlots_legend_%s.pdf", channel_string.data());
  //makePlot_legend(legend_new, outputFilePath, outputFileName_legend);

  delete label_sample;
  delete legend_new;
  delete label_channel;
  delete canvas_new;

  delete inputFile;
}

void makeSVfitMEM_massPlots_from10to12_ratio()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::vector<int> massPoints;
  massPoints.push_back(200);
  massPoints.push_back(300);
  massPoints.push_back(500);
  massPoints.push_back(800);
  massPoints.push_back(1200);
  
  std::map<int, std::string> samples; // key = massPoint
  samples[200]  = "H(200 GeV) #rightarrow #tau#tau";
  samples[300]  = "H(300 GeV) #rightarrow #tau#tau";
  samples[500]  = "H(500 GeV) #rightarrow #tau#tau";
  samples[800]  = "H(800 GeV) #rightarrow #tau#tau";
  samples[1200] = "H(1200 GeV) #rightarrow #tau#tau";
  
  std::string inputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/";
  std::map<int, std::string> inputFileNames_emu; // key = massPoint
  inputFileNames_emu[200]     = "plot_10to12_log_ratio_emu_smeared.root";
  inputFileNames_emu[300]     = "plot_10to12_log_ratio_emu_smeared.root";
  inputFileNames_emu[500]     = "plot_10to12_log_ratio_emu_smeared.root";
  inputFileNames_emu[800]     = "plot_10to12_log_ratio_emu_smeared.root";
  inputFileNames_emu[1200]    = "plot_10to12_log_ratio_emu_smeared.root";
  std::map<int, std::string> inputFileNames_muhad; // key = massPoint
  inputFileNames_muhad[200]   = "plot_10to12_log_ratio_muhad_smeared.root";
  inputFileNames_muhad[300]   = "plot_10to12_log_ratio_muhad_smeared.root";
  inputFileNames_muhad[500]   = "plot_10to12_log_ratio_muhad_smeared.root";
  inputFileNames_muhad[800]   = "plot_10to12_log_ratio_muhad_smeared.root";
  inputFileNames_muhad[1200]  = "plot_10to12_log_ratio_muhad_smeared.root";
  std::map<int, std::string> inputFileNames_hadhad; // key = massPoint
  inputFileNames_hadhad[200]  = "plot_10to12_log_ratio_hadhad_smeared.root";
  inputFileNames_hadhad[300]  = "plot_10to12_log_ratio_hadhad_smeared.root";
  inputFileNames_hadhad[500]  = "plot_10to12_log_ratio_hadhad_smeared.root";
  inputFileNames_hadhad[800]  = "plot_10to12_log_ratio_hadhad_smeared.root";
  inputFileNames_hadhad[1200] = "plot_10to12_log_ratio_hadhad_smeared.root";

  std::string outputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/finalplots/";
  std::map<int, std::string> outputFileNames_emu; // key = massPoint
  outputFileNames_emu[200]     = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu200_emu_log_ratio.pdf";
  outputFileNames_emu[300]     = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu300_emu_log_ratio.pdf";
  outputFileNames_emu[500]     = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu500_emu_log_ratio.pdf";
  outputFileNames_emu[800]     = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu800_emu_log_ratio.pdf";
  outputFileNames_emu[1200]    = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu1200_emu_log_ratio.pdf";
  std::map<int, std::string> outputFileNames_muhad; // key = massPoint
  outputFileNames_muhad[200]   = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu200_muhad_log_ratio.pdf";
  outputFileNames_muhad[300]   = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu300_muhad_log_ratio.pdf";
  outputFileNames_muhad[500]   = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu500_muhad_log_ratio.pdf";
  outputFileNames_muhad[800]   = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu800_muhad_log_ratio.pdf";
  outputFileNames_muhad[1200]  = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu1200_muhad_log_ratio.pdf";
  std::map<int, std::string> outputFileNames_hadhad; // key = massPoint
  outputFileNames_hadhad[200]  = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu200_hadhad_log_ratio.pdf";
  outputFileNames_hadhad[300]  = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu300_hadhad_log_ratio.pdf";
  outputFileNames_hadhad[500]  = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu500_hadhad_log_ratio.pdf";
  outputFileNames_hadhad[800]  = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu800_hadhad_log_ratio.pdf";
  outputFileNames_hadhad[1200] = "makeSVfitMEM_PerformancePlots_HiggsSUSYGluGlu1200_hadhad_log_ratio.pdf";
  
  for ( std::vector<int>::const_iterator massPoint = massPoints.begin();
	massPoint != massPoints.end(); ++massPoint ) {
    std::string sample_emu            = samples[*massPoint];
    std::string inputFileName_emu     = inputFileNames_emu[*massPoint];
    std::string outputFileName_emu    = outputFileNames_emu[*massPoint];
    makePlot(inputFilePath, "emu_smeared", sample_emu, *massPoint, "e#mu", 3., inputFileName_emu, outputFilePath, outputFileName_emu);
    std::string sample_muhad          = samples[*massPoint];
    std::string inputFileName_muhad   = inputFileNames_muhad[*massPoint];
    std::string outputFileName_muhad  = outputFileNames_muhad[*massPoint];
    makePlot(inputFilePath, "muhad_smeared", sample_muhad, *massPoint, "#mu#tau_{h}", 4., inputFileName_muhad, outputFilePath, outputFileName_muhad);
    std::string sample_hadhad         = samples[*massPoint];
    std::string inputFileName_hadhad  = inputFileNames_hadhad[*massPoint];
    std::string outputFileName_hadhad = outputFileNames_hadhad[*massPoint];
    makePlot(inputFilePath, "hadhad_smeared", sample_hadhad, *massPoint, "#tau_{h}#tau_{h}", 5., inputFileName_hadhad, outputFilePath, outputFileName_hadhad);
  }
}
