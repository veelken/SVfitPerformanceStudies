#include "func.C"


void plot_9_svfitmem_paper(){

	// plot histogram
	cout<<"plotting hist...\n";

	string inputPath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_V/"};
	//string inputPath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_IV/"};
	string savePath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/"};
	// root file
	vector<string> vinput {
		"hist_smeared_GluGluHToTauTauM125_0Jets.root",
		"hist_smeared_GluGluHToTauTauM125_1JetNotBoosted.root",
		"hist_smeared_GluGluHToTauTauM125_1JetBoosted.root",
		"hist_smeared_VBFHToTauTauM125_2Jets.root",
		"hist_smeared_DYJetsToLLM50_0Jets.root",
		"hist_smeared_DYJetsToLLM50_1JetNotBoosted.root",
		"hist_smeared_DYJetsToLLM50_1JetBoosted.root",
		"hist_smeared_DYJetsToLLM50_2Jets.root",
	};

	vector<string>vsample{
		"GluGluHToTauTauM125",
		"GluGluHToTauTauM125",
		"GluGluHToTauTauM125",
		"VBFHToTauTauM125",
		"DYJetsToLLM50",
		"DYJetsToLLM50",
		"DYJetsToLLM50",
		"DYJetsToLLM50"
	}; 

	func();

	bool log{0};
	int numbin{25};

	vector<string>vdir{"muhad_smeared"};

	int ndir{static_cast<int>(vdir.size())};

	TH1D *haxispt  = new TH1D("", "", 100, 0, 1000);
	TH1D *haxisphi = new TH1D("", "", 36,0,TMath::Pi());
	haxispt->SetStats(false);
	haxispt->GetYaxis()->SetRangeUser(0.01,1);
	haxisphi->GetYaxis()->SetRangeUser(0.01,1);
	haxispt->GetXaxis()->SetRangeUser(0,400);
	haxisphi->SetStats(false);
	haxispt->SetTitle("");
	haxisphi->SetTitle("");

	TCanvas *canvas[ndir];

	for(int i=0; i<ndir; i++){
		canvas[i] = new TCanvas(vdir[i].c_str(), vdir[i].c_str(), 900, 700); 
		canvas[i]->Divide(2, 2);

		canvas[i]->cd(1);
		if(log) gPad->SetLogx();
		gPad->SetLogy();
		haxispt->Draw();

		canvas[i]->cd(2);
		if(log) gPad->SetLogx();
		gPad->SetLogy();
		haxisphi->Draw();

		canvas[i]->cd(3);
		if(log) gPad->SetLogx();
		gPad->SetLogy();
		haxispt->Draw();

		canvas[i]->cd(4);
		if(log) gPad->SetLogx();
		gPad->SetLogy();
		haxisphi->Draw();

	}


	vector<TH1D*> vh;
	string header;
	string imagepng;
	string imageroot;

	// loop over directories
	for(int i=0; i<ndir; i++){
		cout<<"\ndir: "<<vdir[i]<<endl;

		// loop over input files
		for (int in=0; in<vinput.size(); in++){ 
			string input{inputPath+vinput[in]};
			TFile *file = new TFile(input.c_str(), "READ");

			TIter nextHist(file->GetListOfKeys());
			TKey* histKey(0);
			while ((histKey=(TKey*)nextHist())) {
				if (strcmp(histKey->GetClassName(),"TH1D")!=0) continue;
				TH1D* h = (TH1D*)histKey->ReadObj();
				string histname(h->GetName());

				if(histname.find(vdir[i])==std::string::npos) continue;

				//
				vh.push_back((TH1D*)h->Clone());

				for(int j=0; j<vh.back()->GetNbinsX(); j++){
					vh.back()->SetBinContent(j+1, vh.back()->GetBinContent(j+1)/vh.back()->GetBinWidth(j+1));
					vh.back()->SetBinError(j+1, vh.back()->GetBinError(j+1)/vh.back()->GetBinWidth(j+1));
				}

				if(histname.find("diTauPt_0Jets")!=std::string::npos){
					if(input.find("GluGluHToTauTauM125_0Jets")!=std::string::npos){ 
						vh.back()->Scale(0.00327551182816/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(1); 
						canvas[i]->cd(1); vh.back()->Draw("same&hist"); 
					}
					if(input.find("DYJetsToLLM50_0Jets")!=std::string::npos)  {
						vh.back()->Scale(10.506057804/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(1); 
						canvas[i]->cd(3); vh.back()->Draw("same&hist"); 
					}
				}
				if(histname.find("diTauPt_1JetNotBoosted")!=std::string::npos){
					if(input.find("GluGluHToTauTauM125_1JetNotBoosted")!=std::string::npos){ 
						vh.back()->Scale(0.02490455807424/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(2); 
						canvas[i]->cd(1); vh.back()->Draw("same&hist");
					}
					if(input.find("DYJetsToLLM50_1JetNotBoosted")!=std::string::npos)  {
						vh.back()->Scale(2.0475356868/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(2); 
						canvas[i]->cd(3); vh.back()->Draw("same&hist"); }
				}
				if(histname.find("diTauPt_1JetBoosted")!=std::string::npos){
					if(input.find("GluGluHToTauTauM125_1JetBoosted")!=std::string::npos){ 
						vh.back()->Scale(0.0110693894976/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(3); 
						canvas[i]->cd(1); vh.back()->Draw("same&hist"); 
					}
					if(input.find("DYJetsToLLM50_1JetBoosted")!=std::string::npos)  {
						vh.back()->Scale(0.723067641/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(3); 
						canvas[i]->cd(3); vh.back()->Draw("same&hist"); }
				}
				if(histname.find("diTauPt_2Jets")!=std::string::npos){
					if(input.find("VBFHToTauTauM125_2Jets")!=std::string::npos){ 
						vh.back()->Scale(0.00327551182816/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(4); 
						canvas[i]->cd(1); vh.back()->Draw("same&hist"); 
					}
					if(input.find("DYJetsToLLM50_2Jets")!=std::string::npos)  {
						vh.back()->Scale(0.03106253385/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(4); 
						canvas[i]->cd(3); vh.back()->Draw("same&hist"); }
				}
				if(histname.find("tauDPhi_0Jets")!=std::string::npos){ 
					if(input.find("GluGluHToTauTauM125_0Jets")!=std::string::npos){ 
						vh.back()->Scale(0.00327551182816/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(1); 
						canvas[i]->cd(2); vh.back()->Draw("same&hist"); 
					}
					if(input.find("DYJetsToLLM50_0Jets")!=std::string::npos)  {
						cout << " histname " << histname << endl;  
						vh.back()->Scale(10.506057804/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(1); 
						canvas[i]->cd(4); vh.back()->Draw("same&hist"); }
				}
				if(histname.find("tauDPhi_1JetNotBoosted")!=std::string::npos){ 
					if(input.find("GluGluHToTauTauM125_1JetNotBoosted")!=std::string::npos){ 
						vh.back()->Scale(0.02490455807424/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(2); 
						canvas[i]->cd(2); vh.back()->Draw("same&hist");
					}
					if(input.find("DYJetsToLLM50_1JetNotBoosted")!=std::string::npos)  {
						cout << " histname " << histname << endl;  
						vh.back()->Scale(2.0475356868/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(2); 
						canvas[i]->cd(4); vh.back()->Draw("same&hist"); }
				}
				if(histname.find("tauDPhi_1JetBoosted")!=std::string::npos){ 
					if(input.find("GluGluHToTauTauM125_1JetBoosted")!=std::string::npos){ 
						vh.back()->Scale(0.0110693894976/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(3); 
						canvas[i]->cd(2); vh.back()->Draw("same&hist"); 
					}
					if(input.find("DYJetsToLLM50_1JetBoosted")!=std::string::npos)  {
						vh.back()->Scale(0.723067641/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(3); 
						canvas[i]->cd(4); vh.back()->Draw("same&hist"); }
				}
				if(histname.find("tauDPhi_2Jets")!=std::string::npos){ 
					if(input.find("VBFHToTauTauM125_2Jets")!=std::string::npos){ 
						vh.back()->Scale(0.00327551182816/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(4); 
						canvas[i]->cd(2); vh.back()->Draw("same&hist"); 
					}
					if(input.find("DYJetsToLLM50_2Jets")!=std::string::npos)  {
						vh.back()->Scale(0.03106253385/vh.back()->Integral());
						vh.back()->Rebin(2); vh.back()->SetLineColor(4); 
						canvas[i]->cd(4); vh.back()->Draw("same&hist"); }
				}
			} // input file
		} // dir
	} // dir

	//save canvas
	for(int i=0; i<ndir; i++){
		if(log){ 
			imagepng = savePath+"plot_9_log_"+canvas[i]->GetName()+".png";
			imageroot = savePath+"plot_9_log_"+canvas[i]->GetName()+".root";
		}
		else {
			imagepng = savePath+"plot_9_lin_"+canvas[i]->GetName()+".png";
			imageroot = savePath+"plot_9_lin_"+canvas[i]->GetName()+".root";
		}
		canvas[i]->Print(imagepng.c_str()); 
		canvas[i]->Print(imageroot.c_str()); 
	} 

} // void


