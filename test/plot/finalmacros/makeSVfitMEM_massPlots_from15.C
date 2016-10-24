
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
#include "func.C"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

void makePlot(const std::string& inputFilePath, const std::string inputFileName, std::string& outputFilePath, const std::string& outputFileName)
{

	std::string inputFileName_full = Form("%s%s", inputFilePath.data(), inputFileName.data());
	TFile* inputFile = new TFile(inputFileName_full.data());
	if ( !inputFile ) {
		std::cerr << "Failed to open input file = " << inputFileName_full << " !!" << std::endl;
		assert(0);
	}


	inputFile->ls();

	TCanvas* canvas = dynamic_cast<TCanvas*>(inputFile->Get("canvas_smeared"));
	if ( !canvas ) {
		std::cerr << "Failed to load canvas !!" << std::endl;
		assert(0);
	}

	TCanvas* canvas_new = new TCanvas("canvas_new", "canvas_new", 1200*2, 1100*3);
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
	t1->Divide(2,3,0,0);

	canvas_new->Draw();
	int idxPad[6]={1,2,3,4,5,6};

	vector<string> letters;
	letters.push_back("a)");
	letters.push_back("b)");
	letters.push_back("c)");
	letters.push_back("d)");
	letters.push_back("e)");
	letters.push_back("f)");

	int nPlots = letters.size();

	for ( int iCat=0; iCat<nPlots; iCat++ ) {
		if(iCat<2){
			t2->cd(idxPad[iCat]);
			TPaveText* label_sample = new TPaveText(0.20, 0.00, 0.4600, 0.3375, "NDC");
			label_sample->SetFillStyle(0);
			label_sample->SetBorderSize(0);
			if(iCat==0) label_sample->AddText("Z/#gamma* #rightarrow #tau#tau"); 
                        else label_sample->AddText("H(125 GeV) #rightarrow #tau#tau");
			label_sample->SetTextFont(43);
			label_sample->SetTextSize(50);
			label_sample->SetTextColor(1);
			label_sample->SetTextAlign(11);
			label_sample->Draw();
		}

		t1->cd(idxPad[iCat]);
		gPad->SetTickx(1);
		gPad->SetLogx(true);
		gPad->SetLogy(true);

		TVirtualPad* pad = canvas->GetPad(idxPad[iCat]);
		std::cout << "pad = " << pad << ": ClassName = " << pad->ClassName() << std::endl;

		TH1* histogramSVfit          = 0;
		TH1* histogramSVfitMEMkNeq0  = 0;
		TH1* histogramSVfitMEMkEq0   = 0;
		TH1* histogramcSVfitkEq0     = 0;
		TH1* histogramcSVfitkNeq0    = 0;

		TList* pad_primitives = pad->GetListOfPrimitives();
		TIter pad_nextObj(pad_primitives);

		while ( TObject* obj = pad_nextObj() ) {
			std::string objName = "";
			if ( dynamic_cast<TNamed*>(obj) ) objName = (dynamic_cast<TNamed*>(obj))->GetName();    
			std::cout << "obj = " << obj << ": name = " << objName << ", type = " << obj->ClassName() << std::endl;

			TH1* tmpHistogram = dynamic_cast<TH1*>(obj);
			if ( tmpHistogram ) {
				if ( tmpHistogram->GetLineColor() ==   1 ) histogramSVfit          = tmpHistogram;
				if ( tmpHistogram->GetLineColor() ==   2 ) histogramSVfitMEMkEq0   = tmpHistogram;
				if ( tmpHistogram->GetLineColor() ==   3 ) histogramcSVfitkEq0     = tmpHistogram;
				if ( tmpHistogram->GetLineColor() ==   4 ) histogramSVfitMEMkNeq0  = tmpHistogram;
				if ( tmpHistogram->GetLineColor() ==   5 ) histogramcSVfitkNeq0    = tmpHistogram;
			}
		}

		if ( !(histogramSVfit && histogramSVfitMEMkEq0 && histogramcSVfitkEq0 && histogramSVfitMEMkNeq0 && histogramcSVfitkNeq0 ) ) {
			std::cerr << "Failed to load histograms !!" << std::endl;
			assert(0);
		}

		int lineColors[5] = { kGreen-6,28,kBlue-7,kMagenta -7,kBlack};
		int lineStyles[5] = { 1,3,1,8,1};
		int lineWidths[5] = { 4,4,2,4,2};
		int fillColors[5] = { 0,0,0,0,0};
		int fillStyles[5] = { 0,0,0,0,0};
		int markerStyle[5]  = {1,1,21,1,24};
		int markerColors[5] = {kGreen-6,28,kBlue-7,kMagenta -7,kBlack};
		int markerSize[5]  = { 1,1,3,1,3};

		histogramSVfit->SetFillColor(fillColors[0]);
		histogramSVfit->SetFillStyle(fillStyles[0]);
		histogramSVfit->SetLineColor(lineColors[0]);
		histogramSVfit->SetLineStyle(lineStyles[0]);
		histogramSVfit->SetLineWidth(lineWidths[0]);

		histogramcSVfitkEq0->SetFillColor(fillColors[1]);
		histogramcSVfitkEq0->SetFillStyle(fillStyles[1]);
		histogramcSVfitkEq0->SetLineColor(lineColors[1]);
		histogramcSVfitkEq0->SetLineStyle(lineStyles[1]);
		histogramcSVfitkEq0->SetLineWidth(lineWidths[1]);

		histogramcSVfitkNeq0->SetFillColor(fillColors[2]);
		histogramcSVfitkNeq0->SetFillStyle(fillStyles[2]);
		histogramcSVfitkNeq0->SetLineColor(lineColors[2]);
		histogramcSVfitkNeq0->SetLineStyle(lineStyles[2]);
		histogramcSVfitkNeq0->SetLineWidth(lineWidths[2]);
		histogramcSVfitkNeq0->SetMarkerSize(markerSize[2]);
		histogramcSVfitkNeq0->SetMarkerStyle(markerStyle[2]);
		histogramcSVfitkNeq0->SetMarkerColor(markerColors[2]);
		
                histogramSVfitMEMkEq0->SetFillColor(fillColors[3]);
		histogramSVfitMEMkEq0->SetFillStyle(fillStyles[3]);
		histogramSVfitMEMkEq0->SetLineColor(lineColors[3]);
		histogramSVfitMEMkEq0->SetLineStyle(lineStyles[3]);
		histogramSVfitMEMkEq0->SetLineWidth(lineWidths[3]);

		histogramSVfitMEMkNeq0->SetFillColor(fillColors[4]);
		histogramSVfitMEMkNeq0->SetFillStyle(fillStyles[4]);
		histogramSVfitMEMkNeq0->SetLineColor(lineColors[4]);
		histogramSVfitMEMkNeq0->SetLineStyle(lineStyles[4]);
		histogramSVfitMEMkNeq0->SetLineWidth(lineWidths[4]);
		histogramSVfitMEMkNeq0->SetMarkerSize(markerSize[4]);
		histogramSVfitMEMkNeq0->SetMarkerStyle(markerStyle[4]);
		histogramSVfitMEMkNeq0->SetMarkerColor(markerColors[4]);

		TAxis* xAxis = histogramcSVfitkEq0->GetXaxis();
		if(iCat>3) xAxis->SetTitle("t [s]");
		else xAxis->SetTitle("");
		xAxis->SetRangeUser(0.13,200);
		xAxis->SetTitleOffset(3);
		xAxis->SetTitleSize(60);
		xAxis->SetTitleFont(43);
		if(iCat<4) xAxis->SetLabelOffset(999);
		xAxis->SetLabelSize(50);
		xAxis->SetLabelFont(43);
		xAxis->SetTickLength(0.040);
		xAxis->SetNdivisions(505);

		TAxis* yAxis =histogramcSVfitkEq0 ->GetYaxis();
		if(iCat==0||iCat==2||iCat==4) yAxis->SetTitle("dN/dt [1/s]");
		else yAxis->SetTitle("");
		yAxis->SetRangeUser(0.000005,3300);
		yAxis->SetTitleOffset(4);
		yAxis->SetTitleSize(60);
		yAxis->SetTitleFont(43);
		if(iCat!=0 && iCat!=2 && iCat!=4) 
			yAxis->SetLabelOffset(999);
		yAxis->SetLabelSize(50);
		yAxis->SetLabelFont(43);
		yAxis->SetTickLength(0.040);  
		//yAxis->SetNdivisions(505);

		histogramcSVfitkEq0->SetTitle("");
		histogramcSVfitkEq0->SetStats(false);
		histogramcSVfitkEq0->Draw();
		histogramcSVfitkNeq0->Draw("same");
		histogramSVfitMEMkEq0->Draw("histsame");
		histogramSVfitMEMkNeq0->Draw("same");
		histogramSVfitMEMkEq0->Draw("histsame");
		histogramSVfit->Draw("histsame");
		histogramcSVfitkEq0->Draw("histsame");

		TPaveText* label_channel;
		//if(iCat==0||iCat==3||iCat==6) 
                label_channel = new TPaveText(0.20308, 0.78346, 0.383929, 0.845111, "NDC");
		if(idxPad[iCat]%2==0) label_channel = new TPaveText(0.03308, 0.78346, 0.383929, 0.845111, "NDC");
		label_channel->SetFillStyle(0);
		label_channel->SetBorderSize(0);
		if(iCat<2) label_channel->AddText("#tau_{h}#tau_{h}");
		if(iCat==2||iCat==3) label_channel->AddText("#mu#tau_{h}");
		if(iCat==4||iCat==5) label_channel->AddText("e#mu");
		label_channel->SetTextFont(63); //text font with precision = 3
		label_channel->SetTextSize(60); //size given in pixel
		label_channel->SetTextColor(1);
		label_channel->SetTextAlign(11);
		label_channel->Draw(); 
		
		TPaveText* label_letter; //= new TPaveText(0.03308, 0.82346, 0.383929, 0.935111, "NDC");
		if(idxPad[iCat]%2!=0) label_letter = new TPaveText(0.20308, 0.82346, 0.383929, 0.935111, "NDC");
		else label_letter = new TPaveText(0.03308, 0.82346, 0.383929, 0.935111, "NDC");
		label_letter->SetFillStyle(0);
		label_letter->SetBorderSize(0);
		label_letter->AddText(letters[iCat].c_str());
		label_letter->SetTextFont(63); //text font with precision = 3
		label_letter->SetTextSize(80); //size given in pixel
		label_letter->SetTextColor(1);
		label_letter->SetTextAlign(11);
		label_letter->Draw();



                double meanSVfit         = histogramSVfit->GetMean();
                double meancSVfitkEq0    = histogramcSVfitkEq0->GetMean();
                double meancSVfitkNeq0   = histogramcSVfitkNeq0->GetMean();
                double meanSVfitMEMkEq0  = histogramSVfitMEMkEq0->GetMean();
                double meanSVfitMEMkNeq0 = histogramSVfitMEMkNeq0->GetMean();
                double rmsSVfit          = histogramSVfit->GetRMS();
                double rmscSVfitkEq0     = histogramcSVfitkEq0->GetRMS();
                double rmscSVfitkNeq0    = histogramcSVfitkNeq0->GetRMS();
                double rmsSVfitMEMkEq0   = histogramSVfitMEMkEq0->GetRMS();
                double rmsSVfitMEMkNeq0  = histogramSVfitMEMkNeq0->GetRMS();

                TLegend* legend_new  = new TLegend(0.62, 0.65, 0.83, 0.95); //good for iCat==4 
                if(iCat==0||iCat==2) legend_new = new TLegend(0.62, 0.60, 0.83, 0.95);
                if(iCat==5) legend_new = new TLegend(0.53, 0.65, 0.83, 0.95);
                if(iCat==1||iCat==3) legend_new = new TLegend(0.53, 0.60, 0.83, 0.95); // 
                legend_new->SetFillColor(10);
                legend_new->SetFillStyle(0);
                legend_new->SetBorderSize(0);
                legend_new->SetTextFont(43);
                legend_new->SetTextSize(60);
                legend_new->SetTextColor(1);
                //legend_new->SetNColumns(2);
                
                TH1D *hdummy = (TH1D*)histogramSVfit->Clone();
                hdummy->SetLineColor(0); hdummy->SetMarkerColor(0);
                legend_new->AddEntry(histogramSVfit, "SVfitSA", "l");

                /*string m0 = Form("%.2f",meanVis);
                string m1 = Form("%.2f",meankEq0);
                string m2 = Form("%.2f",meankNeq0);

                if(m0=="-0.00" || m0=="0.00") m0="0";
                if(m1=="-0.00" || m1=="0.00") m1="0";
                if(m2=="-0.00" || m2=="0.00") m2="0";*/

                //iTLegendEntry* l1 = legend_new->AddEntry(hdummy, Form("Mean=%.2f, RMS=%.2f",meanSVfit,rmsSVfit), "l");
		//l1->SetTextFont(83); l1->SetTextSize(40); l1->SetTextColor(kGreen-6);

		legend_new->AddEntry(histogramcSVfitkEq0, "cSVfit (#kappa=0)", "l");
                //TLegendEntry* l2 = legend_new->AddEntry(hdummy, Form("Mean=%.2f, RMS=%.2f",meancSVfitkEq0,rmscSVfitkEq0), "l");
		//l2->SetTextFont(83); l2->SetTextSize(40); l2->SetTextColor(28);

		if(iCat<2)                legend_new->AddEntry(histogramcSVfitkNeq0, "cSVfit (#kappa=5)", "p");
		else if(iCat>1 && iCat<3) legend_new->AddEntry(histogramcSVfitkNeq0, "cSVfit (#kappa=4)", "p");
		else                      legend_new->AddEntry(histogramcSVfitkNeq0, "cSVfit (#kappa=3)", "p");
		
                //TLegendEntry* l3 = legend_new->AddEntry(hdummy, Form("Mean=%.2f, RMS=%.2f",meancSVfitkNeq0,rmscSVfitkNeq0), "p");
		//l3->SetTextFont(83); l3->SetTextSize(40); l3->SetTextColor(kBlue-7);
		
                legend_new->AddEntry(histogramSVfitMEMkEq0, "SVfitMEM (#kappa=0)", "l");
                //TLegendEntry* l4 = legend_new->AddEntry(hdummy, Form("Mean=%.2f, RMS=%.2f",meanSVfitMEMkEq0,rmsSVfitMEMkEq0), "l");
		//l4->SetTextFont(83); l4->SetTextSize(40); l4->SetTextColor(kMagenta-7);

		if(iCat<2)                legend_new->AddEntry(histogramSVfitMEMkNeq0, "SVfitMEM (#kappa=5)", "p");
		else if(iCat>1 && iCat<3) legend_new->AddEntry(histogramSVfitMEMkNeq0, "SVfitMEM (#kappa=4)", "p");
		else                      legend_new->AddEntry(histogramSVfitMEMkNeq0, "SVfitMEM (#kappa=3)", "p");
		
                //TLegendEntry* l5 = legend_new->AddEntry(hdummy, Form("Mean=%.2f, RMS=%.2f",meanSVfitMEMkNeq0,rmsSVfitMEMkNeq0), "p");
		//l5->SetTextFont(83); l5->SetTextSize(40); l5->SetTextColor(kBlack);
		
                legend_new->Draw();

		canvas_new->Update();
	}
	std::string outputFileName_full = Form("%s%s", outputFilePath.data(), outputFileName.data());
	size_t idx = outputFileName_full.find_last_of('.');
	std::string outputFileName_plot = std::string(outputFileName_full, 0, idx);
	canvas_new->Print(std::string(outputFileName_plot).append(".pdf").data());
	canvas_new->Print(std::string(outputFileName_plot).append(".root").data());

	//delete legend_new;
	//delete label_channel;
	delete canvas_new;

	delete inputFile;
}

void makeSVfitMEM_massPlots_from15()
{
	gROOT->SetBatch(true);

	TH1::AddDirectory(false);


	std::string inputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/";
	std::string outputFilePath = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/finalplots/";

	std::string inputFileName   = "plot_15_log.root";
	std::string outputFileName  = "Higgs_DYJets_CPU_time.root";
	makePlot(inputFilePath, inputFileName, outputFilePath, outputFileName);

}
