#include "getLogBinning.C"
#include "func.C"
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
  TCanvas* canvas_legend = new TCanvas("canvas_legend", "canvas_legend", 500, 600);
  canvas_legend->SetFillColor(10);
  canvas_legend->SetBorderSize(0);
  canvas_legend->Draw();
  canvas_legend->cd();

  legend->SetX1NDC(0.00);
  legend->SetY1NDC(0.00);
  legend->SetX2NDC(1.0);
  legend->SetY2NDC(1.0);
  legend->SetTextSize(0.070);
  //legend->SetMargin(0.20);
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

void makePlot(const std::string& inputFilePath, const std::string& canvasName, const std::vector<string> samples, const std::vector<string> categories, const std::string& channel, 
		double k, const std::string& inputFileName, const std::string& outputFilePath, const std::string& outputFileName)
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

	TCanvas* canvas_new = new TCanvas("canvas_new", "canvas_new", 900*2, 800*4);
	canvas_new->SetTopMargin(0.00); canvas_new->SetRightMargin(0.00); canvas_new->SetBottomMargin(0.00);  canvas_new->SetLeftMargin(0.00);

	TPad* t2 = new TPad("t2","t2", 0.0, 0.975, 1.00, 1.00);  t2->Draw();  canvas_new->cd();
	t2->SetTopMargin(0.00); t2->SetRightMargin(0.00); t2->SetBottomMargin(0.00);  t2->SetLeftMargin(0.00);
	t2->SetFillColor(0);
	t2->Divide(2,1,0,0);  

	TPad* t1 = new TPad("t1","t1", 0.0, 0.0, 1.00, 0.972, 4, 1);  t1->Draw();  t1->cd();
	t1->SetTopMargin(0.00); 
        t1->SetRightMargin(0.02); 
        t1->SetBottomMargin(0.14);  
        t1->SetLeftMargin(0.145);
	t1->SetFillColor(0);
	t1->Divide(2,4,0,0);

	//canvas_new->SetFillColor(10);
	//canvas_new->SetBorderSize(2);
	//canvas_new->SetTopMargin(0.165);
	//canvas_new->SetBottomMargin(0.17);
	//canvas_new->SetLeftMargin(0.145);
	//canvas_new->SetRightMargin(0.02);
	//canvas_new->Divide(2,4,0,0);
	canvas_new->Draw();

	int nPlots = (categories.size()/2)*samples.size();

	int idxPad[8]={1,2,3,4,5,6,7,8};
        vector<string> letters;
        letters.push_back("a)"); 
        letters.push_back("b)"); 
        letters.push_back("c)"); 
        letters.push_back("d)"); 
        letters.push_back("e)"); 
        letters.push_back("f)"); 
        letters.push_back("g)"); 
        letters.push_back("h)"); 

	for ( int iCat=0; iCat<nPlots; iCat++ ) {
		if(iCat==0 || iCat ==1){
			t2->cd(idxPad[iCat]);

			TPaveText* label_sample;
                        if(iCat==0) label_sample = new TPaveText(0.20, 0.00, 0.4600, 0.3375, "NDC");
                        else label_sample = new TPaveText(0.09, 0.00, 0.4600, 0.3375, "NDC");
			label_sample->SetFillStyle(0);
			label_sample->SetBorderSize(0);
			if(idxPad[iCat]==1) label_sample->AddText(samples[0].c_str());
			else if( idxPad[iCat]==2) label_sample->AddText(samples[1].c_str());
			else label_sample->AddText("");
			label_sample->SetTextFont(43);
			label_sample->SetTextSize(50);
			label_sample->SetTextColor(1);
			label_sample->SetTextAlign(11);
			label_sample->Draw();
			
                        //double label_channel_y0;
			//if      ( channel == "e#mu"             ) label_channel_y0 = 0.9275;
			//else if ( channel == "#mu#tau_{h}"      ) label_channel_y0 = 0.9400;
			//else if ( channel == "#tau_{h}#tau_{h}" ) label_channel_y0 = 0.9350;
			//else {
			//	std::cerr << "Invalid channel = " << channel << " !!" << std::endl;
			//	assert(0);
			//}

			TPaveText* label_channel = new TPaveText(0.830357, 0.3, 0.96, 0.5375, "NDC");
			label_channel->SetFillStyle(0);
			label_channel->SetBorderSize(0);
			label_channel->AddText(channel.data());
			label_channel->SetTextFont(63);
			label_channel->SetTextSize(50);
			label_channel->SetTextColor(1);
			label_channel->SetTextAlign(31);
                        if(iCat==1) label_channel->Draw();
		}

		t1->cd(idxPad[iCat]);
		gPad->SetTickx(1);
		gPad->SetLogx(true);
		gPad->SetLogy(true);

		//gPad->SetTopMargin(0.04);
		//gPad->SetBottomMargin(0.01);
		//if(idxPad[iCat]==7||idxPad[iCat]==8) gPad->SetBottomMargin(0.15);
		//else gPad->SetBottomMargin(0.00);

		//if(idxPad[iCat]==2||idxPad[iCat]==4||idxPad[iCat]==6||idxPad[iCat]==8) gPad->SetLeftMargin(0.04);
		//else gPad->SetLeftMargin(0.13);
		//if(idxPad[iCat]==2||idxPad[iCat]==4||idxPad[iCat]==6||idxPad[iCat]==8) gPad->SetRightMargin(0.10);
		//else gPad->SetRightMargin(0.01);

		TVirtualPad* pad = canvas->GetPad(idxPad[iCat]);
		std::cout << "pad = " << pad << ": ClassName = " << pad->ClassName() << std::endl;

		TH1* histogramCA            = 0;
		TH1* histogramSVfit         = 0;
		TH1* histogramSVfitMEMkEq0  = 0;
		TH1* histogramSVfitMEMkNeq0 = 0;
		TH1* histogramSVfitCLAkEq0  = 0;
		TH1* histogramSVfitCLAkNeq0 = 0;
		
		TList* pad_primitives = pad->GetListOfPrimitives();
		TIter pad_nextObj(pad_primitives);

		while ( TObject* obj = pad_nextObj() ) {
			std::string objName = "";
			if ( dynamic_cast<TNamed*>(obj) ) objName = (dynamic_cast<TNamed*>(obj))->GetName();    
			//std::cout << "obj = " << obj << ": name = " << objName << ", type = " << obj->ClassName() << std::endl;

			TH1* tmpHistogram = dynamic_cast<TH1*>(obj);
			if ( tmpHistogram ) {
				/*std::cout << "tmpHistogram:" 
				  << " fillColor = " << tmpHistogram->GetFillColor() << ", fillStyle = " << tmpHistogram->GetFillStyle() << ","
				  << " lineColor = " << tmpHistogram->GetLineColor() << ", lineStyle = " << tmpHistogram->GetLineStyle() << ", lineWidth = " << tmpHistogram->GetLineWidth() << ","
				  << " markerColor = " << tmpHistogram->GetMarkerColor() << ", markerStyle = " << tmpHistogram->GetMarkerStyle() << ", markerSize = " << tmpHistogram->GetMarkerSize() << ","
				  << " integral = " << tmpHistogram->Integral() << std::endl;
				  std::cout << "(mean = " << tmpHistogram->GetMean() << ", rms = " << tmpHistogram->GetRMS() << ": rms/mean = " << (tmpHistogram->GetRMS()/tmpHistogram->GetMean()) << ")" << std::endl;*/
				if ( tmpHistogram->GetLineColor() == 416 ) histogramCA            = tmpHistogram;
				if ( tmpHistogram->GetLineColor() == 600 ) histogramSVfit         = tmpHistogram;
				if ( tmpHistogram->GetLineColor() == 616 ) histogramSVfitMEMkEq0  = tmpHistogram;
				if ( tmpHistogram->GetLineColor() == 632 ) histogramSVfitMEMkNeq0 = tmpHistogram;
				if ( tmpHistogram->GetLineColor() == 1   ) histogramSVfitCLAkEq0  = tmpHistogram;
				if ( tmpHistogram->GetLineColor() == 800 ) histogramSVfitCLAkNeq0 = tmpHistogram;
			}
		}

		if ( !(histogramCA && histogramSVfit && histogramSVfitMEMkEq0 && histogramSVfitMEMkNeq0 && histogramSVfitCLAkEq0 && histogramSVfitCLAkNeq0) ) {
			std::cerr << "Failed to load histograms !!" << std::endl;
			assert(0);
		}
		
                int colors[6]       = { 28, kGreen - 6, kBlue - 7, kBlack, kMagenta -7, kBlack };
		int lineStyles[6]   = { 7, 1, 1, 1, 1, 1 };
		int lineWidths[6]   = { 2, 2, 1, 1 ,1, 1};
		int markerStyles[6] = { 20, 25, 21, 24, 22, 32}; 
		int markerSizes[6]  = { 2, 2, 3,3, 3, 3};

		histogramCA->SetFillColor(0);
		histogramCA->SetFillStyle(0);
		histogramCA->SetLineColor(colors[0]);
		histogramCA->SetLineStyle(lineStyles[0]);
		histogramCA->SetLineWidth(lineWidths[0]);
		histogramCA->SetMarkerColor(colors[0]);
		histogramCA->SetMarkerStyle(markerStyles[0]);
		histogramCA->SetMarkerSize(markerSizes[0]);
                //histogramCA->Rebin(1.5);

		histogramSVfit->SetFillColor(0);
		histogramSVfit->SetFillStyle(0);
		histogramSVfit->SetLineColor(colors[1]);
		histogramSVfit->SetLineStyle(lineStyles[1]);
		histogramSVfit->SetLineWidth(lineWidths[1]);
		histogramSVfit->SetMarkerColor(colors[1]);
		histogramSVfit->SetMarkerStyle(markerStyles[1]);
		histogramSVfit->SetMarkerSize(markerSizes[1]);
                //histogramSVfit->Rebin(1.5);

		histogramSVfitMEMkEq0->SetFillColor(0);
		histogramSVfitMEMkEq0->SetFillStyle(0);
		histogramSVfitMEMkEq0->SetLineColor(colors[2]);
		histogramSVfitMEMkEq0->SetLineStyle(lineStyles[2]);
		histogramSVfitMEMkEq0->SetLineWidth(lineWidths[2]);
		histogramSVfitMEMkEq0->SetMarkerColor(colors[2]);
		histogramSVfitMEMkEq0->SetMarkerStyle(markerStyles[2]);
		histogramSVfitMEMkEq0->SetMarkerSize(markerSizes[2]);
                //histogramSVfitMEMkEq0->Rebin(1.5);
		
                // CV: fix pathological bins at high mass for which dN/dm increases
		/*int numBins = histogramSVfitMEMkEq0->GetNbinsX();
		  for ( int idxBin = 1; idxBin <= numBins; ++idxBin ) {
		  double binCenter = histogramSVfitMEMkEq0->GetBinCenter(idxBin);
		  if ( (channel == "#tau_{h}#tau_{h}" && sampleCategory == 500 && binCenter > 1500.) ||
		  (channel == "#tau_{h}#tau_{h}" && sampleCategory == 800 && binCenter > 2000.) ||
		  (channel == "#mu#tau_{h}"      && sampleCategory == 500 && binCenter > 1500.) ||
		  (channel == "#mu#tau_{h}"      && sampleCategory == 800 && binCenter > 2500.) ) {
		  histogramSVfitMEMkEq0->SetBinContent(idxBin, 0.);
		  }
		  }*/

		histogramSVfitMEMkNeq0->SetFillColor(0);
		histogramSVfitMEMkNeq0->SetFillStyle(0);
		histogramSVfitMEMkNeq0->SetLineColor(colors[3]);
		histogramSVfitMEMkNeq0->SetLineStyle(lineStyles[3]);
		histogramSVfitMEMkNeq0->SetLineWidth(lineWidths[3]);
		histogramSVfitMEMkNeq0->SetMarkerColor(colors[3]);
		histogramSVfitMEMkNeq0->SetMarkerStyle(markerStyles[3]);
		histogramSVfitMEMkNeq0->SetMarkerSize(markerSizes[3]);
                //histogramSVfitMEMkNeq0->Rebin(1.5);

		histogramSVfitCLAkEq0->SetFillColor(0);
		histogramSVfitCLAkEq0->SetFillStyle(0);
		histogramSVfitCLAkEq0->SetLineColor(colors[4]);
		histogramSVfitCLAkEq0->SetLineStyle(lineStyles[4]);
		histogramSVfitCLAkEq0->SetLineWidth(lineWidths[4]);
		histogramSVfitCLAkEq0->SetMarkerColor(colors[4]);
		histogramSVfitCLAkEq0->SetMarkerStyle(markerStyles[4]);
		histogramSVfitCLAkEq0->SetMarkerSize(markerSizes[4]);
                //histogramSVfitCLAkEq0->Rebin(1.5);

		histogramSVfitCLAkNeq0->SetFillColor(0);
		histogramSVfitCLAkNeq0->SetFillStyle(0);
		histogramSVfitCLAkNeq0->SetLineColor(colors[5]);
		histogramSVfitCLAkNeq0->SetLineStyle(lineStyles[5]);
		histogramSVfitCLAkNeq0->SetLineWidth(lineWidths[5]);
		histogramSVfitCLAkNeq0->SetMarkerColor(colors[5]);
		histogramSVfitCLAkNeq0->SetMarkerStyle(markerStyles[5]);
		histogramSVfitCLAkNeq0->SetMarkerSize(markerSizes[5]);
                //histogramSVfitCLAkNeq0->Rebin(1.5);

		TAxis* xAxis = histogramCA->GetXaxis();
		xAxis->SetRangeUser(0.5,8);
                //if      ( channel == "e#mu"             ) xAxis->SetRangeUser(0.05,8);
		//if      ( channel == "tau_{h}#tau_{h}"  ) xAxis->SetRangeUser(0.05,8);
		xAxis->SetTickLength(0.040);
		xAxis->SetNdivisions(505);//10);
		if(idxPad[iCat]==7 || idxPad[iCat]==8){ 
			xAxis->SetTitle("m_{#tau#tau}/m^{true}_{#tau#tau}");
			xAxis->SetTitleOffset(4);
			xAxis->SetTitleFont(43);
			xAxis->SetTitleSize(60);
			xAxis->SetMoreLogLabels(kFALSE);
			xAxis->SetLabelFont(43);
			xAxis->SetLabelSize(50);
		}else{
			xAxis->SetTitle("");
			xAxis->SetTitleOffset(999);
			xAxis->SetLabelOffset(999);
		}

		TAxis* yAxis = histogramCA->GetYaxis();
		yAxis->SetRangeUser(0.002,9);
		yAxis->SetTickLength(0.040);  
		yAxis->SetNdivisions(505);
		if(idxPad[iCat]%2!=0){
			yAxis->SetTitle("dN/d(m_{#tau#tau}/m^{true}_{#tau#tau})");
			yAxis->SetTitleOffset(4);
			yAxis->SetTitleFont(43);
			yAxis->SetTitleSize(60);
			yAxis->SetLabelOffset(0.010);
			yAxis->SetLabelSize(50);
			yAxis->SetLabelFont(43);
		}else{
			yAxis->SetTitle("");
			yAxis->SetTitleOffset(999);
			yAxis->SetLabelOffset(999);
		}
		
		//double sampleCategory_double = 0.;
		//if ( sampleCategory == 90 ) sampleCategory_double = 91.2;
		//else sampleCategory_double = sampleCategory;
		//double dLog = (TMath::Log(5.*sampleCategory_double) - TMath::Log(50.))/25.; // xMin = 50, xMax = 5*sampleCategory, numBins = 25
		//double binWidth = TMath::Exp(TMath::Log(sampleCategory_double) + 0.5*dLog) - TMath::Exp(TMath::Log(sampleCategory_double) - 0.5*dLog);
		//double sf_binWidth = 1./binWidth;
		//std::cout << "sampleCategory = " << sampleCategory << ": sf_binWidth = " << sf_binWidth << std::endl;

		histogramCA->SetTitle("");
		histogramCA->SetStats(false);
		histogramCA->Draw("hist");
		histogramSVfit->Draw("histsame");
		histogramSVfitMEMkEq0->Draw("epsame");
		histogramSVfitMEMkNeq0->Draw("epsame");
		histogramSVfitCLAkEq0->Draw("epsame");
		histogramSVfitCLAkNeq0->Draw("epsame");
		histogramCA->Draw("axissame");


		TPaveText* label_category = new TPaveText(0.747024,0.82346,0.980476,0.935111, "NDC");
		label_category->SetFillStyle(0);
		label_category->SetBorderSize(0);
                label_category->AddText(categories[iCat].c_str());
		label_category->SetTextFont(43); //text font with precision = 3
		label_category->SetTextSize(50); //size given in pixel
		label_category->SetTextColor(1);
		label_category->SetTextAlign(31);
		label_category->Draw();
		
		TPaveText* label_letter; //= new TPaveText(0.03308, 0.82346, 0.383929, 0.935111, "NDC");
                if(idxPad[iCat]%2!=0) label_letter = new TPaveText(0.20308, 0.82346, 0.383929, 0.935111, "NDC");
                else label_letter = new TPaveText(0.03308, 0.82346, 0.383929, 0.935111, "NDC");
                label_letter->SetFillStyle(0);
		label_letter->SetBorderSize(0);
                label_letter->AddText(letters[iCat].c_str());
		label_letter->SetTextFont(63); //text font with precision = 3
		label_letter->SetTextSize(50); //size given in pixel
		label_letter->SetTextColor(1);
		label_letter->SetTextAlign(11);
		label_letter->Draw();
	

		TLegend* legend_new = new TLegend(0.20, 0.20, 0.90, 0.90, NULL, "brNDC");
		legend_new->SetFillColor(10);
		legend_new->SetFillStyle(0);
		legend_new->SetBorderSize(0);
		legend_new->SetTextFont(42);
		legend_new->SetTextSize(0.055);
		legend_new->SetTextColor(1);
		legend_new->SetMargin(0.2);
		legend_new->AddEntry(histogramCA, "CA", "l");
		legend_new->AddEntry(histogramSVfit, "SVfitSA", "l");
		legend_new->AddEntry(histogramSVfitCLAkEq0, "cSVfit (#kappa=0)", "p");
		legend_new->AddEntry(histogramSVfitCLAkNeq0, Form("cSVfit (#kappa=%1.0f)", k), "p");
		legend_new->AddEntry(histogramSVfitMEMkEq0, "SVfitMEM (#kappa=0)", "p");
		legend_new->AddEntry(histogramSVfitMEMkNeq0, Form("SVfitMEM (#kappa=%1.0f)", k), "p");
		//legend_new->Draw();


		canvas_new->Update();

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

		canvas_new->Update();
	} //close for on categories
	
        std::string outputFileName_full = Form("%s%s", outputFilePath.data(), outputFileName.data());
	size_t idx = outputFileName_full.find_last_of('.');
	std::string outputFileName_plot = std::string(outputFileName_full, 0, idx);
	canvas_new->Print(std::string(outputFileName_plot).append(".pdf").data());
	canvas_new->Print(std::string(outputFileName_plot).append(".root").data());
	//delete label_sample;
	//delete label_channel;
	delete canvas_new;

	delete inputFile;
}

void makeSVfitMEM_massPlots_from6to8_ratio()
{
	gROOT->SetBatch(true);

	//LOGIC

	std::vector<string> samples;
	samples.push_back("Z/#gamma* #rightarrow #tau#tau");
	samples.push_back("H(125 GeV) #rightarrow #tau#tau");

	std::vector<string> categories; 
	categories.push_back("0-jet");
	categories.push_back("0-jet");
	categories.push_back("1-jet non-boosted");
	categories.push_back("1-jet non-boosted");
	categories.push_back("1-jet boosted");
	categories.push_back("1-jet boosted");
	categories.push_back("2-jet VBF");
	categories.push_back("2-jet VBF");

	std::string inputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/";
	std::string outputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/finalplots/";

	TH1::AddDirectory(false);

	std::string inputFileName_emu     = "plot_6to8_log_ratio_emu_smeared.root";
	std::string outputFileName_emu    = "makeSVfitMEM_PerformancePlots_DYJets_HiggsSM_all_categories_emu_log_ratio.pdf";
	makePlot(inputFilePath, "emu_smeared", samples, categories, "e#mu", 3., inputFileName_emu, outputFilePath, outputFileName_emu);
	std::string inputFileName_muhad   = "plot_6to8_log_ratio_muhad_smeared.root";
	std::string outputFileName_muhad  = "makeSVfitMEM_PerformancePlots_DYJets_HiggsSM_all_categories_muhad_log_ratio.pdf";
	makePlot(inputFilePath, "muhad_smeared", samples, categories, "#mu#tau_{h}", 4., inputFileName_muhad, outputFilePath, outputFileName_muhad);
	std::string inputFileName_hadhad  = "plot_6to8_log_ratio_hadhad_smeared.root";
	std::string outputFileName_hadhad = "makeSVfitMEM_PerformancePlots_DYJets_HiggsSM_all_categories_hadhad_log_ratio.pdf";
	makePlot(inputFilePath, "hadhad_smeared", samples, categories, "#tau_{h}#tau_{h}", 5., inputFileName_hadhad, outputFilePath, outputFileName_hadhad);

}
