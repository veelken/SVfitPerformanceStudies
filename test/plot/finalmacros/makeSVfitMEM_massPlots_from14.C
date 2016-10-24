
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

void makePlot(const std::string& inputFilePath, const std::string inputFileName, int histogram, const std::string& xAxisTitle, const std::string& yAxisTitle,
                                        const std::string& outputFilePath, const std::string& outputFileName)
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

	TCanvas* canvas_new = new TCanvas("canvas_new", "canvas_new", 800, 1100*3);
	canvas_new->SetTopMargin(0.00); canvas_new->SetRightMargin(0.00); canvas_new->SetBottomMargin(0.00);  canvas_new->SetLeftMargin(0.00);

	TPad* t2 = new TPad("t2","t2", 0.0, 0.975, 1.00, 1.00);  t2->Draw();  canvas_new->cd();
	t2->SetTopMargin(0.00); t2->SetRightMargin(0.00); t2->SetBottomMargin(0.00);  t2->SetLeftMargin(0.00);
	t2->SetFillColor(0);

	TPad* t1 = new TPad("t1","t1", 0.0, 0.0, 1.00, 0.972, 4, 1);  t1->Draw();  t1->cd();
	t1->SetTopMargin(0.00);
	t1->SetRightMargin(0.02);
	t1->SetBottomMargin(0.14);
	t1->SetLeftMargin(0.145);
	t1->SetFillColor(0);
	t1->Divide(1,3,0,0);

	canvas_new->Draw();
	int idxPad[3]={};
        if(histogram==1) { idxPad[0]=1; idxPad[1]=4; idxPad[2]=7; }
        if(histogram==2) { idxPad[0]=2; idxPad[1]=5; idxPad[2]=8; }
        if(histogram==3) { idxPad[0]=3; idxPad[1]=6; idxPad[2]=9; }

	vector<string> letters;
	if(histogram==1) { letters.push_back("a)"); letters.push_back("d)"); letters.push_back("g)");}
	if(histogram==2) { letters.push_back("b)"); letters.push_back("e)"); letters.push_back("h)");}
	if(histogram==3) { letters.push_back("c)"); letters.push_back("f)"); letters.push_back("i)");}

	int nPlots = letters.size();

	for ( int iCat=0; iCat<nPlots; iCat++ ) {

		if(histogram==1){
			t2->cd();

			TPaveText* label_sample = new TPaveText(0.20, 0.00, 0.4600, 0.3375, "NDC");
			label_sample->SetFillStyle(0);
			label_sample->SetBorderSize(0);
			label_sample->AddText("H(125 GeV) #rightarrow #tau#tau");
			label_sample->SetTextFont(43);
			label_sample->SetTextSize(50);
			label_sample->SetTextColor(1);
			label_sample->SetTextAlign(11);
			label_sample->Draw();
		}
		t1->cd(iCat+1);
		gPad->SetTickx(1);
		gPad->SetLogx(false);
		gPad->SetLogy(true);

		TVirtualPad* pad = canvas->GetPad(idxPad[iCat]);
		std::cout << "pad = " << pad << ": ClassName = " << pad->ClassName() << std::endl;

		TH1* histogramH125Vis        = 0;
		TH1* histogramH125LOkEq0     = 0;
		TH1* histogramH125LOkNeq0    = 0;

		TList* pad_primitives = pad->GetListOfPrimitives();
		TIter pad_nextObj(pad_primitives);

		/*TCanvas* canvas_new = new TCanvas("canvas_new", "canvas_new", 900, 850);
		  canvas_new->SetFillColor(10);
		  canvas_new->SetBorderSize(2);
		  canvas_new->SetTopMargin(0.065);
		  canvas_new->SetLeftMargin(0.17);
		  canvas_new->SetBottomMargin(0.155);
		  canvas_new->SetRightMargin(0.045);
		  canvas_new->SetLogx(false);
		  canvas_new->SetLogy(true);
		  canvas_new->Draw();
		  canvas_new->cd();*/

		while ( TObject* obj = pad_nextObj() ) {
			std::string objName = "";
			if ( dynamic_cast<TNamed*>(obj) ) objName = (dynamic_cast<TNamed*>(obj))->GetName();    
			std::cout << "obj = " << obj << ": name = " << objName << ", type = " << obj->ClassName() << std::endl;

			TH1* tmpHistogram = dynamic_cast<TH1*>(obj);
			if ( tmpHistogram ) {
				if ( tmpHistogram->GetLineColor() ==   2 ) histogramH125Vis      = tmpHistogram;
				if ( tmpHistogram->GetLineColor() ==   4 ) histogramH125LOkEq0   = tmpHistogram;
				if ( tmpHistogram->GetLineColor() ==   6 ) histogramH125LOkNeq0  = tmpHistogram;
			}
		}

		if ( !(histogramH125Vis && histogramH125LOkEq0 && histogramH125LOkNeq0) ) {
			std::cerr << "Failed to load histograms !!" << std::endl;
			assert(0);
		}

		int lineColors[3]   = { kGreen-6,kBlue-7,kBlack };
		int lineStyles[3]   = { 1,1,1};
		int lineWidths[3]   = { 4,2,2 };
		int fillColors[3]   = { 0,0,0 };
		int fillStyles[3]   = { 0,0,0 };
		int markerStyle[3]  = { 1,21,24 };
		int markerColors[3] = { kGreen-6,kBlue-7,kBlack };
		int markerSize[3]   = { 1,3,3 };

		histogramH125Vis->SetFillColor(fillColors[0]);
		histogramH125Vis->SetFillStyle(fillStyles[0]);
		histogramH125Vis->SetLineColor(lineColors[0]);
		histogramH125Vis->SetLineStyle(lineStyles[0]);
		histogramH125Vis->SetLineWidth(lineWidths[0]);

		histogramH125LOkEq0->SetFillColor(fillColors[1]);
		histogramH125LOkEq0->SetFillStyle(fillStyles[1]);
		histogramH125LOkEq0->SetLineColor(lineColors[1]);
		histogramH125LOkEq0->SetLineStyle(lineStyles[1]);
		histogramH125LOkEq0->SetLineWidth(lineWidths[1]);
		histogramH125LOkEq0->SetMarkerSize(markerSize[1]);
		histogramH125LOkEq0->SetMarkerStyle(markerStyle[1]);
		histogramH125LOkEq0->SetMarkerColor(markerColors[1]);

		histogramH125LOkNeq0->SetFillColor(fillColors[2]);
		histogramH125LOkNeq0->SetFillStyle(fillStyles[2]);
		histogramH125LOkNeq0->SetLineColor(lineColors[2]);
		histogramH125LOkNeq0->SetLineStyle(lineStyles[2]);
		histogramH125LOkNeq0->SetLineWidth(lineWidths[2]);
		histogramH125LOkNeq0->SetMarkerSize(markerSize[2]);
		histogramH125LOkNeq0->SetMarkerStyle(markerStyle[2]);
		histogramH125LOkNeq0->SetMarkerColor(markerColors[2]);

		TAxis* xAxis = histogramH125LOkEq0->GetXaxis();
		if(histogram!=1) xAxis->SetRangeUser(-4,4);
		else xAxis->SetRangeUser(-100,130);
		if(iCat>1) xAxis->SetTitle(xAxisTitle.data());
		else xAxis->SetTitle("");
		xAxis->SetTitleOffset(3);
		xAxis->SetTitleSize(60);
		xAxis->SetTitleFont(43);
		if(iCat<2) xAxis->SetLabelOffset(999);
		xAxis->SetLabelSize(50);
		xAxis->SetLabelFont(43);
		xAxis->SetTickLength(0.040);
		xAxis->SetNdivisions(505);

		TAxis* yAxis =histogramH125LOkEq0 ->GetYaxis();
		yAxis->SetTitle(yAxisTitle.data());
		if(histogram!=1) yAxis->SetRangeUser(0.006,33000);
		else yAxis->SetRangeUser(0.0005,33000);
		yAxis->SetTitleOffset(4);
		yAxis->SetTitleSize(60);
		yAxis->SetTitleFont(43);
		yAxis->SetLabelSize(50);
		yAxis->SetLabelFont(43);
		yAxis->SetTickLength(0.040);  
		yAxis->SetNdivisions(505);

		histogramH125LOkEq0->SetTitle("");
		histogramH125LOkEq0->SetStats(false);
		histogramH125LOkEq0->Draw();
		histogramH125LOkNeq0->Draw("same");
		histogramH125Vis->Draw("histsame");
		histogramH125LOkEq0->Draw("axissame");

		TPaveText* label_channel  = new TPaveText(0.86308, 0.44346, 0.913929, 0.555111, "NDC");
		if(iCat==0) label_channel = new TPaveText(0.86308, 0.45346, 0.913929, 0.565111, "NDC");
		if(iCat==2) label_channel = new TPaveText(0.88308, 0.52346, 0.933929, 0.635111, "NDC");
		//if(iCat==0||iCat==3||iCat==6) label_channel = new TPaveText(0.20308, 0.78346, 0.383929, 0.845111, "NDC");
		//else label_channel = new TPaveText(0.03308, 0.78346, 0.383929, 0.845111, "NDC");
		label_channel->SetFillStyle(0);
		label_channel->SetBorderSize(0);
		if(iCat==0) label_channel->AddText("#tau_{h}#tau_{h}");
		if(iCat==1) label_channel->AddText("#mu#tau_{h}");
		if(iCat==2) label_channel->AddText("e#mu");
		label_channel->SetTextFont(63); //text font with precision = 3
		label_channel->SetTextSize(60); //size given in pixel
		label_channel->SetTextColor(1);
		label_channel->SetTextAlign(11);
		label_channel->Draw(); 
		
                TPaveText* label_letter = new TPaveText(0.20308, 0.44346, 0.383929, 0.555111, "NDC"); //= new TPaveText(0.03308, 0.82346, 0.383929, 0.935111, "NDC");
		if(iCat>1) label_letter = new TPaveText(0.20308, 0.51346, 0.383929, 0.625111, "NDC");
		//else label_letter = new TPaveText(0.03308, 0.84346, 0.383929, 0.955111, "NDC");
		label_letter->SetFillStyle(0);
		label_letter->SetBorderSize(0);
		label_letter->AddText(letters[iCat].c_str());
		label_letter->SetTextFont(63); //text font with precision = 3
		label_letter->SetTextSize(80); //size given in pixel
		label_letter->SetTextColor(1);
		label_letter->SetTextAlign(11);
		label_letter->Draw(); 


                double medVis   = AlternativeMedian((TH1D*)histogramH125Vis);
                double medkEq0  = AlternativeMedian((TH1D*)histogramH125LOkEq0);
                double medkNeq0 = AlternativeMedian((TH1D*)histogramH125LOkNeq0);
                double rmsVis    = histogramH125Vis->GetRMS();
                double rmskEq0   = histogramH125LOkEq0->GetRMS();
                double rmskNeq0  = histogramH125LOkNeq0->GetRMS();
		TLegend* legend_new   = new TLegend(0.20, 0.63, 0.68, 0.94);  
                if(iCat<2) legend_new = new TLegend(0.20, 0.58, 0.68, 0.94);  
                legend_new->SetFillColor(10);
                legend_new->SetFillStyle(0);
                legend_new->SetBorderSize(0);
                legend_new->SetTextFont(43);
                legend_new->SetTextSize(60);
                legend_new->SetTextColor(1);
                
                TH1D *hdummy = (TH1D*)histogramH125LOkNeq0->Clone();
                hdummy->SetLineColor(0); hdummy->SetMarkerColor(0);
                legend_new->AddEntry(histogramH125Vis, "p^{vis(1)}+p^{vis(2)}+E^{miss}_{T} ", "l");

                string m0 = Form("%.1f",medVis);
                string m1 = Form("%.1f",medkEq0);
                string m2 = Form("%.1f",medkNeq0);

                if(m0=="-0.00" || m0=="0.00") m0="0";
                if(m1=="-0.00" || m1=="0.00") m1="0";
                if(m2=="-0.00" || m2=="0.00") m2="0";

                TLegendEntry* l1;
                if(histogram>1) l1 = legend_new->AddEntry(hdummy, Form("RMS=%.2f",rmsVis), "p");
                else l1 = legend_new->AddEntry(hdummy, ("M="+m0+","+Form("RMS=%.1f",rmsVis)).c_str(), "p");
                //if(histogram>1) l1 = legend_new->AddEntry(hdummy, ("M="+m0+","+Form("RMS=%.2f",rmsVis)).c_str(), "p");

		legend_new->AddEntry(histogramH125LOkEq0, "cSVfit (#kappa=0)", "p");
		TLegendEntry* l2;
                if(histogram>1)  l2 = legend_new->AddEntry(hdummy, Form("RMS=%.2f",rmskEq0), "p");
                else  l2 = legend_new->AddEntry(hdummy, ("M="+m1+","+Form("RMS=%.1f",rmskEq0)).c_str(), "p");

		if(iCat==0)         legend_new->AddEntry(histogramH125LOkNeq0, "cSVfit (#kappa=5)", "p");
		else if(iCat==1)    legend_new->AddEntry(histogramH125LOkNeq0, "cSVfit (#kappa=4)", "p");
		else                legend_new->AddEntry(histogramH125LOkNeq0, "cSVfit (#kappa=3)", "p");
		
		TLegendEntry* l3;
                if(histogram>1) l3 = legend_new->AddEntry(hdummy, Form("RMS=%.2f",rmskNeq0), "p");
                else  l3 = legend_new->AddEntry(hdummy, ("M="+m2+","+Form("RMS=%.1f",rmskNeq0)).c_str(), "p");
 
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

void makeSVfitMEM_massPlots_from14()
{
	gROOT->SetBatch(true);

	TH1::AddDirectory(false);
        
        std::vector<int> histograms;
        histograms.push_back(1);
        histograms.push_back(2);
        histograms.push_back(3);

	std::map<int, std::string> xAxisTitles; // key=histograms
	xAxisTitles[1]  = "#Delta p_{T} [GeV]";
	xAxisTitles[2]  = "#Delta #eta";
	xAxisTitles[3]  = "#Delta #phi";
	
        std::map<int, std::string> yAxisTitles; // key=histograms
	yAxisTitles[1]   = "dN/d#Delta p_{T} [1/GeV]";
	yAxisTitles[2]  = "dN/d#Delta #eta";
	yAxisTitles[3]  = "dN/d#Delta #phi";

	std::string inputFilePath   = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/";
	std::string outputFilePath  = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/finalplots/";

	std::string inputFileName   = "plot_14_lin.root";
	std::map<int, std::string> outputFileNames;  // key = histograms
	outputFileNames[1]  = "Higgs_resolutions_pT.pdf";
	outputFileNames[2]  = "Higgs_resolutions_eta.pdf";
	outputFileNames[3]  = "Higgs_resolutions_phi.pdf";

        for ( std::vector<int>::const_iterator histo = histograms.begin();
        histo != histograms.end(); ++histo ) {
		
                std::string outputFileName_pt = outputFileNames[*histo];
		std::string xAxisTitle_pt     = xAxisTitles[*histo];
		std::string yAxisTitle_pt     = yAxisTitles[*histo];
	        makePlot(inputFilePath, inputFileName, *histo, xAxisTitle_pt, yAxisTitle_pt, outputFilePath, outputFileName_pt);
                
                std::string outputFileName_eta = outputFileNames[*histo];
		std::string xAxisTitle_eta     = xAxisTitles[*histo];
		std::string yAxisTitle_eta     = yAxisTitles[*histo];
	        makePlot(inputFilePath, inputFileName, *histo, xAxisTitle_eta, yAxisTitle_eta, outputFilePath, outputFileName_eta);
                
                std::string outputFileName_phi = outputFileNames[*histo];
		std::string xAxisTitle_phi     = xAxisTitles[*histo];
		std::string yAxisTitle_phi     = yAxisTitles[*histo];
	        makePlot(inputFilePath, inputFileName, *histo, xAxisTitle_phi, yAxisTitle_phi, outputFilePath, outputFileName_phi);
        }


}
