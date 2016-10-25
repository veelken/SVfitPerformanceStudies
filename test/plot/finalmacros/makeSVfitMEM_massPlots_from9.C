
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
  if ( histogram == "HiggsDiTauPt"  ) idxPad = 1;
  if ( histogram == "HiggsDPhi"  )    idxPad = 2;
  if ( histogram == "DYJetsDiTauPt" ) idxPad = 3;
  if ( histogram == "DYJetsDPhi"  )   idxPad = 4;
  if ( !(idxPad >= 1 && idxPad <= 4) ) {
    std::cerr << "Invalid histogram = " << histogram << " !!" << std::endl;
    assert(0);
  }
  TVirtualPad* pad = canvas->GetPad(idxPad);
  std::cout << "pad = " << pad << ": ClassName = " << pad->ClassName() << std::endl;

  TCanvas* canvas_new = new TCanvas("canvas_new", "canvas_new", 1000, 1000);
  canvas_new->SetFillColor(10);
  canvas_new->SetBorderSize(2);
  canvas_new->SetTopMargin(0.065);
  canvas_new->SetLeftMargin(0.1975);
  canvas_new->SetBottomMargin(0.1725);
  canvas_new->SetRightMargin(0.010);
  if(histogram == "HiggsDiTauPt" || histogram == "DYJetsDiTauPt" ) canvas_new->SetLogx(true);
  canvas_new->SetLogy(true);
  canvas_new->Draw();
  canvas_new->cd();

  TList* pad_primitives = pad->GetListOfPrimitives();

  TH1* histogram0Jet           = 0;
  TH1* histogram1JetNotBoosted = 0;
  TH1* histogram1JetBoosted    = 0;
  TH1* histogram2Jets          = 0;

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
      if ( tmpHistogram->GetLineColor() ==   1 ) histogram0Jet            = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   2 ) histogram1JetNotBoosted  = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   3 ) histogram1JetBoosted     = tmpHistogram;
      if ( tmpHistogram->GetLineColor() ==   4 ) histogram2Jets           = tmpHistogram;
    }
  }

  if ( !(histogram0Jet && histogram1JetNotBoosted && histogram1JetBoosted && histogram2Jets) ) {
	  std::cerr << "Failed to load histograms !!" << std::endl;
	  assert(0);
  }

  int colors[4]       = { kGreen - 6, 28, kBlue - 7, kBlack };
  int lineStyles[5]   = { 1, 7, 1, 1};
  int markerStyles[5] = { 1, 1, 21, 24};
  int markerSizes[5]  = { 1, 1, 3, 3};
  int markerColors[4] = { kGreen - 6, 28, kBlue - 7, kBlack };
  int lineWidths[5]   = { 6, 6, 3 , 3};

  histogram0Jet->SetLineColor(colors[0]);
  histogram0Jet->SetLineStyle(lineStyles[0]);
  histogram0Jet->SetLineWidth(lineWidths[0]);
  
  histogram1JetNotBoosted->SetLineColor(colors[1]);
  histogram1JetNotBoosted->SetLineStyle(lineStyles[1]);
  histogram1JetNotBoosted->SetLineWidth(lineWidths[1]);

  histogram1JetBoosted->SetLineColor(colors[2]);
  histogram1JetBoosted->SetLineStyle(lineStyles[2]);
  histogram1JetBoosted->SetLineWidth(lineWidths[2]);
  histogram1JetBoosted->SetMarkerStyle(markerStyles[2]);
  histogram1JetBoosted->SetMarkerColor(markerColors[2]);
  histogram1JetBoosted->SetMarkerSize(markerSizes[2]);
  
  histogram2Jets->SetLineColor(colors[3]);
  histogram2Jets->SetLineStyle(lineStyles[3]);
  histogram2Jets->SetLineWidth(lineWidths[3]);
  histogram2Jets->SetMarkerStyle(markerStyles[3]);
  histogram2Jets->SetMarkerColor(markerColors[3]);
  histogram2Jets->SetMarkerSize(markerSizes[3]);

  TAxis* xAxis = histogram0Jet->GetXaxis();
  string title = xAxisTitle.data();
  xAxis->SetTitle(xAxisTitle.data());
  xAxis->SetTitleOffset(1.1);
  xAxis->SetTitleSize(70);
  xAxis->SetTitleFont(43);
  //xAxis->SetLabelOffset(-0.01);
  xAxis->SetLabelSize(0.050);
  if(histogram == "HiggsDiTauPt" || histogram == "DYJetsDiTauPt" ){
    xAxis->SetRangeUser(0.1,500);
  }
  xAxis->SetLabelFont(42);
  xAxis->SetTickLength(0.040);
  xAxis->SetNdivisions(505);

  TAxis* yAxis = histogram0Jet->GetYaxis();
  yAxis->SetTitle(yAxisTitle.data());
  yAxis->SetTitleOffset(1.30);
  yAxis->SetTitleSize(70);
  yAxis->SetTitleFont(43);
  if(histogram == "HiggsDiTauPt")  yAxis->SetRangeUser(0.65e-4, 6.5e-1);
  if(histogram == "DYJetsDiTauPt") yAxis->SetRangeUser(1.e-3, 1.e+3);
  if(histogram == "HiggsDPhi")     yAxis->SetRangeUser(0.25e-4, 2.5e-1);
  if(histogram == "DYJetsDPhi")    yAxis->SetRangeUser(1.e-4, 1.e+3);
  //yAxis->SetLabelOffset(0.010);
  yAxis->SetLabelSize(0.055);
  yAxis->SetLabelFont(42);
  yAxis->SetTickLength(0.040);  
  yAxis->SetNdivisions(505);

  histogram0Jet->SetTitle("");
  histogram0Jet->SetStats(false);
  histogram0Jet->Draw("hist");
  histogram1JetNotBoosted->Draw("histsame");
  histogram1JetBoosted->Draw("same");
  histogram2Jets->Draw("same");
  histogram0Jet->Draw("axissame");

  histogram1JetBoosted->Draw("same");
  histogram2Jets->Draw("same");
  
  TLegend* legend_new = new TLegend(0.51, 0.62, 0.84, 0.92, NULL, "brNDC");
  legend_new->SetFillColor(10);
  legend_new->SetFillStyle(0);
  legend_new->SetBorderSize(0);
  legend_new->SetTextFont(42);
  legend_new->SetTextSize(0.055);
  legend_new->SetTextColor(1);
  legend_new->SetMargin(0.20);
  legend_new->AddEntry(histogram0Jet, "0-jet ", "l");
  legend_new->AddEntry(histogram1JetNotBoosted, "1-jet non-boosted", "l");
  legend_new->AddEntry(histogram1JetBoosted,    "1-jet boosted", "p");
  legend_new->AddEntry(histogram2Jets, "2-jet VBF", "p");
  legend_new->Draw();

  double label_channel_y0;
  //if      ( channel == "e#mu"             ) label_channel_y0 = 0.9275;
  if ( channel == "#mu#tau_{h}"      ) label_channel_y0 = 0.9400;
  //else if ( channel == "#tau_{h}#tau_{h}" ) label_channel_y0 = 0.9350;
  else {
	  std::cerr << "Invalid channel = " << channel << " !!" << std::endl;
	  assert(0);
  }
  TPaveText* label_channel = new TPaveText(0.875, label_channel_y0, 0.965, label_channel_y0 + 0.055, "NDC");
  label_channel->SetFillStyle(0);
  label_channel->SetBorderSize(0);
  label_channel->AddText(channel.data());
  label_channel->SetTextFont(62);
  label_channel->SetTextSize(0.055);
  label_channel->SetTextColor(1);
  label_channel->SetTextAlign(31);
  label_channel->Draw();

  TPaveText* label_sample = new TPaveText(0.20, 0.938, 0.4600, 0.965, "NDC");
  label_sample->SetFillStyle(0);
  label_sample->SetBorderSize(0);
  if ( histogram == "HiggsDiTauPt"  ) label_sample->AddText("H(125 GeV) #rightarrow #tau#tau");
  if ( histogram == "HiggsDPhi"  )    label_sample->AddText("H(125 GeV) #rightarrow #tau#tau");
  if ( histogram == "DYJetsDiTauPt" ) label_sample->AddText("Z/#gamma* #rightarrow #tau#tau"); 
  if ( histogram == "DYJetsDPhi" )    label_sample->AddText("Z/#gamma* #rightarrow #tau#tau"); 
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

void makeSVfitMEM_massPlots_from9()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  std::vector<std::string> histograms;
  histograms.push_back("HiggsDiTauPt");
  histograms.push_back("HiggsDPhi");
  histograms.push_back("DYJetsDiTauPt");
  histograms.push_back("DYJetsDPhi");

  std::map<std::string, std::string> xAxisTitles; // key = histogram
  xAxisTitles["HiggsDiTauPt"]   = "p_{T}^{H} [GeV]";
  xAxisTitles["HiggsDPhi"]      = "#Delta#phi_{#tau#tau}";
  xAxisTitles["DYJetsDiTauPt"]  = "p_{T}^{Z} [GeV]";
  xAxisTitles["DYJetsDPhi"]      = "#Delta#phi_{#tau#tau}";

  std::map<std::string, std::string> yAxisTitles; // key = histogram
  yAxisTitles["HiggsDiTauPt"]   = "dN/dp_{T}^{H} [1/GeV]";
  yAxisTitles["HiggsDPhi"]      = "dN/d#Delta#phi_{#tau#tau}";
  yAxisTitles["DYJetsDiTauPt"]  = "dN/dp_{T}^{Z} [1/GeV]";
  yAxisTitles["DYJetsDPhi"]     = "dN/d#Delta#phi_{#tau#tau}";
  
  //std::string inputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/";
  std::string inputFilePath = "/home/veelken/SVfitMEM_paper/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/";
  std::map<std::string, std::string> inputFileNames_muhad; // key = histogram
  inputFileNames_muhad["HiggsDiTauPt"]   = "plot_9_lin_muhad_smeared.root";
  inputFileNames_muhad["HiggsDPhi"]      = "plot_9_lin_muhad_smeared.root";
  inputFileNames_muhad["DYJetsDiTauPt"]  = "plot_9_lin_muhad_smeared.root";
  inputFileNames_muhad["DYJetsDPhi"]     = "plot_9_lin_muhad_smeared.root";

  //std::string outputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/finalplots/";
  std::string outputFilePath = "/home/veelken/SVfitMEM_paper/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/finalplots/";
  std::map<std::string, std::string> outputFileNames_muhad; // key = histogram
  outputFileNames_muhad["HiggsDiTauPt"]   = "Higgs_pT_muhad.root";
  outputFileNames_muhad["HiggsDPhi"]      = "Higgs_dPhiTauTau_muhad.root";
  outputFileNames_muhad["DYJetsDiTauPt"]  = "DYJets_pT_muhad.root";
  outputFileNames_muhad["DYJetsDPhi"]     = "DYJets_dPhiTauTau_muhad.root";
  
  for ( std::vector<std::string>::const_iterator histogram = histograms.begin();
	histogram != histograms.end(); ++histogram ) {
    std::string xAxisTitle_muhad      = xAxisTitles[*histogram];
    std::string yAxisTitle_muhad      = yAxisTitles[*histogram];
    std::string inputFileName_muhad   = inputFileNames_muhad[*histogram];
    std::string outputFileName_muhad  = outputFileNames_muhad[*histogram];
    makePlot(inputFilePath, "muhad_smeared", *histogram, "#mu#tau_{h}", xAxisTitle_muhad, yAxisTitle_muhad, inputFileName_muhad, outputFilePath, outputFileName_muhad);
  }
}
