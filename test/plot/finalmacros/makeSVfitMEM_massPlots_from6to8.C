
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

void makePlot(const std::string& inputFilePath, const std::string& canvasName, const std::string& sample, int sampleCategory, const std::string& channel, 
              const std::string& category, double k, const std::string& inputFileName, const std::string& outputFilePath, const std::string& outputFileName)
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
  if ( sampleCategory == 10 )  idxPad = 1;
  if ( sampleCategory == 11 )  idxPad = 2;
  if ( sampleCategory == 20 )  idxPad = 3;
  if ( sampleCategory == 21 )  idxPad = 4;  
  if ( sampleCategory == 30 )  idxPad = 5;  
  if ( sampleCategory == 31 )  idxPad = 6;  
  if ( sampleCategory == 40 )  idxPad = 7;  
  if ( sampleCategory == 41 )  idxPad = 8;  
  if ( !(idxPad >= 1 && idxPad <= 8) ) {
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
  canvas_new->SetRightMargin(0.015);
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
    }
  }

  if ( !(histogramCA && histogramSVfit && histogramSVfitMEMkEq0 && histogramSVfitMEMkNeq0) ) {
    std::cerr << "Failed to load histograms !!" << std::endl;
    assert(0);
  }

  //gStyle->SetLineStyleString(2,"40 10 10 10 10 10 10 10");
  //gStyle->SetLineStyleString(3,"25 15");
  //gStyle->SetLineStyleString(4,"60 25");

  //int colors[4] = { kBlack, kGreen - 6, kBlue - 7, kMagenta - 7  };
  int colors[4] = { 28, kGreen - 6, kBlue - 7, kBlack };
  //int lineStyles[4] = { 2, 3, 4, 1 };
  int lineStyles[4] = { 7, 1, 1, 1 };
  //int lineWidths[4] = { 3, 3, 4, 3 };
  int lineWidths[4] = { 3, 3, 1, 1 };
  int markerStyles[4] = { 20, 25, 21, 24 };
  int markerSizes[4] = { 2, 2, 2, 2 };

  histogramCA->SetFillColor(0);
  histogramCA->SetFillStyle(0);
  histogramCA->SetLineColor(colors[0]);
  histogramCA->SetLineStyle(lineStyles[0]);
  histogramCA->SetLineWidth(lineWidths[0]);
  histogramCA->SetMarkerColor(colors[0]);
  histogramCA->SetMarkerStyle(markerStyles[0]);
  histogramCA->SetMarkerSize(markerSizes[0]);

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
    if ( (channel == "#tau_{h}#tau_{h}" && sampleCategory == 500 && binCenter > 1500.) ||
	 (channel == "#tau_{h}#tau_{h}" && sampleCategory == 800 && binCenter > 2000.) ||
	 (channel == "#mu#tau_{h}"      && sampleCategory == 500 && binCenter > 1500.) ||
	 (channel == "#mu#tau_{h}"      && sampleCategory == 800 && binCenter > 2500.) ) {
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

  TAxis* xAxis = histogramCA->GetXaxis();
  xAxis->SetTitle("m_{#tau#tau} [GeV]");
  xAxis->SetTitleOffset(1.15);
  xAxis->SetTitleSize(0.070);
  xAxis->SetTitleFont(42);
  xAxis->SetLabelOffset(0.010);
  xAxis->SetLabelSize(0.055);
  xAxis->SetLabelFont(42);
  xAxis->SetTickLength(0.040);
  xAxis->SetNdivisions(510);

  //double xMin = 20.;
  //double xMax = xAxis->GetXmax();
  //xAxis->SetRangeUser(xMin, xMax);

  TAxis* yAxis = histogramCA->GetYaxis();
  yAxis->SetTitle("dN/dm_{#tau#tau} [1/GeV]");
  yAxis->SetTitleOffset(1.20);
  yAxis->SetTitleSize(0.070);
  yAxis->SetTitleFont(42);
  yAxis->SetLabelOffset(0.010);
  yAxis->SetLabelSize(0.055);
  yAxis->SetLabelFont(42);
  yAxis->SetTickLength(0.040);  
  yAxis->SetNdivisions(505);

  //double sampleCategory_double = 0.;
  //if ( sampleCategory == 90 ) sampleCategory_double = 91.2;
  //else sampleCategory_double = sampleCategory;
  //double dLog = (TMath::Log(5.*sampleCategory_double) - TMath::Log(50.))/25.; // xMin = 50, xMax = 5*sampleCategory, numBins = 25
  //double binWidth = TMath::Exp(TMath::Log(sampleCategory_double) + 0.5*dLog) - TMath::Exp(TMath::Log(sampleCategory_double) - 0.5*dLog);
  //double sf_binWidth = 1./binWidth;
  //std::cout << "sampleCategory = " << sampleCategory << ": sf_binWidth = " << sf_binWidth << std::endl;

  histogramCA->SetTitle("");
  histogramCA->SetStats(false);
  //histogramCA->SetMaximum(sf_binWidth*0.79);
  //histogramCA->SetMinimum(sf_binWidth*1.1e-4);
  histogramCA->Draw("hist");
  histogramSVfit->Draw("histsame");
  //histogramSVfitMEMkEq0->Draw("histsame");
  histogramSVfitMEMkEq0->Draw("epsame");
  //histogramSVfitMEMkNeq0->Draw("histsame");
  histogramSVfitMEMkNeq0->Draw("epsame");
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
 
  TPaveText* label_category = new TPaveText(0.19308, 0.873278, 0.383929, 0.96281, "NDC");
  label_category->SetFillStyle(0);
  label_category->SetBorderSize(0);
  label_category->AddText(category.data());
  label_category->SetTextFont(42);
  label_category->SetTextSize(0.055);
  label_category->SetTextColor(1);
  label_category->SetTextAlign(13);
  label_category->Draw();

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
  legend_new->AddEntry(histogramSVfit, "SVfit", "l");
  //legend_new->AddEntry(histogramSVfitMEMkEq0, "SVfitMEM (k=0)", "l");
  legend_new->AddEntry(histogramSVfitMEMkEq0, "SVfitMEM (k=0)", "p");
  //legend_new->AddEntry(histogramSVfitMEMkNeq0, Form("SVfitMEM(k=%1.0f)", k), "l");
  legend_new->AddEntry(histogramSVfitMEMkNeq0, Form("SVfitMEM (k=%1.0f)", k), "p");
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
  makePlot_legend(legend_new, outputFilePath, outputFileName_legend);

  delete label_sample;
  delete legend_new;
  delete label_channel;
  delete canvas_new;

  delete inputFile;
}

void makeSVfitMEM_massPlots_from6to8()
{
  gROOT->SetBatch(true);
  
  //LOGIC
  

  TH1::AddDirectory(false);
  std::vector<int> sampleCategories;
  sampleCategories.push_back(10); //DYJets 0 Jets 
  sampleCategories.push_back(11); //GluGlu 0 Jets
  sampleCategories.push_back(20); //DY 1Jet Not Boosted§
  sampleCategories.push_back(21); //GluGlu 1Jet Not Boosted
  sampleCategories.push_back(30); //DY 1Jet Boosted
  sampleCategories.push_back(31); //GluGlu 1Jet Boosted
  sampleCategories.push_back(40); //DY 2Jets
  sampleCategories.push_back(41); //VBF 2Jets
  
  std::map<int, std::string> samples; // key = sampleCategory
  samples[10]   = "Z/#gamma* #rightarrow #tau#tau";
  samples[11]   = "gg #rightarrow H, H(125 GeV) #rightarrow #tau#tau";
  samples[20]   = "Z/#gamma* #rightarrow #tau#tau";
  samples[21]   = "gg #rightarrow H, H(125 GeV) #rightarrow #tau#tau";
  samples[30]   = "Z/#gamma* #rightarrow #tau#tau";
  samples[31]   = "gg #rightarrow H, H(125 GeV) #rightarrow #tau#tau";
  samples[40]   = "Z/#gamma* #rightarrow #tau#tau";
  samples[41]   = "q#bar{q} #rightarrow H, H(125 GeV) #rightarrow #tau#tau";
  
  std::map<int, std::string> categories; // key = sampleCategory
  categories[10]   = "0-jet";
  categories[11]   = "0-jet";
  categories[20]   = "1-jet non-boosted";
  categories[21]   = "1-jet non-boosted";
  categories[30]   = "1-jet boosted";
  categories[31]   = "1-jet boosted";
  categories[40]   = "2-jet VBF";
  categories[41]   = "2-jet VBF";
  
  std::string inputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/";
  std::map<int, std::string> inputFileNames_emu; // key = sampleCategory
  inputFileNames_emu[10]     = "plot_6to8_log_emu_smeared.root";
  inputFileNames_emu[11]     = "plot_6to8_log_emu_smeared.root";
  inputFileNames_emu[20]     = "plot_6to8_log_emu_smeared.root";
  inputFileNames_emu[21]     = "plot_6to8_log_emu_smeared.root";
  inputFileNames_emu[30]     = "plot_6to8_log_emu_smeared.root";
  inputFileNames_emu[31]     = "plot_6to8_log_emu_smeared.root";
  inputFileNames_emu[40]     = "plot_6to8_log_emu_smeared.root";
  inputFileNames_emu[41]     = "plot_6to8_log_emu_smeared.root";
  std::map<int, std::string> inputFileNames_muhad; // key = sampleCategory
  inputFileNames_muhad[10]     = "plot_6to8_log_muhad_smeared.root";
  inputFileNames_muhad[11]     = "plot_6to8_log_muhad_smeared.root";
  inputFileNames_muhad[20]     = "plot_6to8_log_muhad_smeared.root";
  inputFileNames_muhad[21]     = "plot_6to8_log_muhad_smeared.root";
  inputFileNames_muhad[30]     = "plot_6to8_log_muhad_smeared.root";
  inputFileNames_muhad[31]     = "plot_6to8_log_muhad_smeared.root";
  inputFileNames_muhad[40]     = "plot_6to8_log_muhad_smeared.root";
  inputFileNames_muhad[41]     = "plot_6to8_log_muhad_smeared.root";
  std::map<int, std::string> inputFileNames_hadhad; // key = sampleCategory
  inputFileNames_hadhad[10]     = "plot_6to8_log_hadhad_smeared.root";
  inputFileNames_hadhad[11]     = "plot_6to8_log_hadhad_smeared.root";
  inputFileNames_hadhad[20]     = "plot_6to8_log_hadhad_smeared.root";
  inputFileNames_hadhad[21]     = "plot_6to8_log_hadhad_smeared.root";
  inputFileNames_hadhad[30]     = "plot_6to8_log_hadhad_smeared.root";
  inputFileNames_hadhad[31]     = "plot_6to8_log_hadhad_smeared.root";
  inputFileNames_hadhad[40]     = "plot_6to8_log_hadhad_smeared.root";
  inputFileNames_hadhad[41]     = "plot_6to8_log_hadhad_smeared.root";

  std::string outputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/finalplots/";
  std::map<int, std::string> outputFileNames_emu; // key = sampleCategory
  outputFileNames_emu[10]     = "makeSVfitMEM_PerformancePlots_DYJets0Jet_emu_log.pdf";
  outputFileNames_emu[11]     = "makeSVfitMEM_PerformancePlots_HiggsSMGluGlu0Jet_emu_log.pdf";
  outputFileNames_emu[20]     = "makeSVfitMEM_PerformancePlots_DYJets1JetNonBoosted_emu_log.pdf";
  outputFileNames_emu[21]     = "makeSVfitMEM_PerformancePlots_HiggsSMGluGlu1JetNonBoosted_emu_log.pdf";
  outputFileNames_emu[30]     = "makeSVfitMEM_PerformancePlots_DYJets1JetBoosted_emu_log.pdf";
  outputFileNames_emu[31]     = "makeSVfitMEM_PerformancePlots_HiggsSMGluGlu1JetBoosted_emu_log.pdf";
  outputFileNames_emu[40]     = "makeSVfitMEM_PerformancePlots_DYJets2Jet_emu_log.pdf";
  outputFileNames_emu[41]     = "makeSVfitMEM_PerformancePlots_HiggsSMQQ2Jet_emu_log.pdf";
  std::map<int, std::string> outputFileNames_muhad; // key = sampleCategory
  outputFileNames_muhad[10]     = "makeSVfitMEM_PerformancePlots_DYJets0Jet_muhad_log.pdf";
  outputFileNames_muhad[11]     = "makeSVfitMEM_PerformancePlots_HiggsSMGluGlu0Jet_muhad_log.pdf";
  outputFileNames_muhad[20]     = "makeSVfitMEM_PerformancePlots_DYJets1JetNonBoosted_muhad_log.pdf";
  outputFileNames_muhad[21]     = "makeSVfitMEM_PerformancePlots_HiggsSMGluGlu1JetNonBoosted_muhad_log.pdf";
  outputFileNames_muhad[30]     = "makeSVfitMEM_PerformancePlots_DYJets1JetBoosted_muhad_log.pdf";
  outputFileNames_muhad[31]     = "makeSVfitMEM_PerformancePlots_HiggsSMGluGlu1JetBoosted_muhad_log.pdf";
  outputFileNames_muhad[40]     = "makeSVfitMEM_PerformancePlots_DYJets2Jet_muhad_log.pdf";
  outputFileNames_muhad[41]     = "makeSVfitMEM_PerformancePlots_HiggsSMQQ2Jet_muhad_log.pdf";
  std::map<int, std::string> outputFileNames_hadhad; // key = sampleCategory
  outputFileNames_hadhad[10]     = "makeSVfitMEM_PerformancePlots_DYJets0Jet_hadhad_log.pdf";
  outputFileNames_hadhad[11]     = "makeSVfitMEM_PerformancePlots_HiggsSMGluGlu0Jet_hadhad_log.pdf";
  outputFileNames_hadhad[20]     = "makeSVfitMEM_PerformancePlots_DYJets1JetNonBoosted_hadhad_log.pdf";
  outputFileNames_hadhad[21]     = "makeSVfitMEM_PerformancePlots_HiggsSMGluGlu1JetNonBoosted_hadhad_log.pdf";
  outputFileNames_hadhad[30]     = "makeSVfitMEM_PerformancePlots_DYJets1JetBoosted_hadhad_log.pdf";
  outputFileNames_hadhad[31]     = "makeSVfitMEM_PerformancePlots_HiggsSMGluGlu1JetBoosted_hadhad_log.pdf";
  outputFileNames_hadhad[40]     = "makeSVfitMEM_PerformancePlots_DYJets2Jet_hadhad_log.pdf";
  outputFileNames_hadhad[41]     = "makeSVfitMEM_PerformancePlots_HiggsSMQQ2Jet_hadhad_log.pdf";
  
  for ( std::vector<int>::const_iterator sampleCategory = sampleCategories.begin();
	sampleCategory != sampleCategories.end(); ++sampleCategory ) {
   
    std::string category = categories[*sampleCategory];
    
    std::string sample_emu            = samples[*sampleCategory];
    std::string inputFileName_emu     = inputFileNames_emu[*sampleCategory];
    std::string outputFileName_emu    = outputFileNames_emu[*sampleCategory];
    makePlot(inputFilePath, "emu_smeared", sample_emu, *sampleCategory, "e#mu", category, 3., inputFileName_emu, outputFilePath, outputFileName_emu);
    std::string sample_muhad          = samples[*sampleCategory];
    std::string inputFileName_muhad   = inputFileNames_muhad[*sampleCategory];
    std::string outputFileName_muhad  = outputFileNames_muhad[*sampleCategory];
    makePlot(inputFilePath, "muhad_smeared", sample_muhad, *sampleCategory, "#mu#tau_{h}", category, 4., inputFileName_muhad, outputFilePath, outputFileName_muhad);
    std::string sample_hadhad         = samples[*sampleCategory];
    std::string inputFileName_hadhad  = inputFileNames_hadhad[*sampleCategory];
    std::string outputFileName_hadhad = outputFileNames_hadhad[*sampleCategory];
    makePlot(inputFilePath, "hadhad_smeared", sample_hadhad, *sampleCategory, "#tau_{h}#tau_{h}", category, 5., inputFileName_hadhad, outputFilePath, outputFileName_hadhad);
  }
}
