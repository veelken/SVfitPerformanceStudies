#include "func.C"


void plot_10to12_ratio_svfitmem_paper(){

	// plot histogram
	cout<<"plotting hist...\n";

	string inputPath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_IV/"};
	string savePath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/"};
	// root file
	vector<string> vinput {"hist_SUSYGluGluToHToTauTauM200_inclusive.root",
		"hist_SUSYGluGluToHToTauTauM300_inclusive.root",
		"hist_SUSYGluGluToHToTauTauM500_inclusive.root",
		"hist_SUSYGluGluToHToTauTauM800_inclusive.root",
		"hist_SUSYGluGluToHToTauTauM1200_inclusive.root"
	};

	vector<string>vsample{"SUSYGluGluToHToTauTauM200",
		"SUSYGluGluToHToTauTauM300",
		"SUSYGluGluToHToTauTauM500",
		"SUSYGluGluToHToTauTauM800",
		"SUSYGluGluToHToTauTauM1200"
	}; 

	func();

	bool log{1};
	int numbin{25};

	vector<string>vdir{"emu_smeared", "muhad_smeared",   "hadhad_smeared"};
	vector<string>vdirleg{"e#mu", "#mu#tau_{h}", "#tau_{h}#tau_{h}"};

	TH1D *haxis = new TH1D("", "", 100, 0, 20);
	haxis->SetStats(false);
	haxis->GetXaxis()->SetRangeUser(0.1, 10);
	haxis->GetYaxis()->SetRangeUser(0.001, 10);
	haxis->GetXaxis()->SetTitleOffset(1.);
	haxis->GetYaxis()->SetTitleOffset(1.4);
	haxis->GetXaxis()->SetTitle("m_{#tau#tau}/m^{true}_{#tau#tau}");
	haxis->GetYaxis()->SetTitle("dN/d(m_{#tau#tau}/m^{true}_{#tau#tau})");

	int ndir{static_cast<int>(vdir.size())};


	TCanvas *canvas[ndir];

	for(int i=0; i<ndir; i++){
		canvas[i] = new TCanvas(vdir[i].c_str(), vdir[i].c_str(), 900, 700); 
		canvas[i]->Divide(2, 3);

		canvas[i]->cd(1);
		if(log) gPad->SetLogx();
		gPad->SetLogy();
		haxis->Draw();

		canvas[i]->cd(2);
		if(log) gPad->SetLogx();
		gPad->SetLogy();
		haxis->Draw();

		canvas[i]->cd(3);
		if(log) gPad->SetLogx();
		gPad->SetLogy();
		haxis->Draw();

		canvas[i]->cd(4);
		if(log) gPad->SetLogx();
		gPad->SetLogy();
		haxis->Draw();

		canvas[i]->cd(5);
		if(log) gPad->SetLogx();
		gPad->SetLogy();
		haxis->Draw();

	}


	vector<TH1D*> vhmass;
	string header;
	string imagepng;
	string imageroot;

	// loop over directories
	for(int i=0; i<ndir; i++){
		cout<<"\ndir: "<<vdir[i]<<endl;
		TLegend *legend;
		legend = new TLegend( 0.12, 0.15, 0.95, 0.95, NULL,"brNDC"); 
		legend->SetTextSize(0.09);

		// loop over input files
		for (int in=0; in<vinput.size(); in++){ 
			string input{inputPath+vinput[in]};
			TFile *file = new TFile(input.c_str(), "READ");
			string sample{vsample.at(in)};

			// loop over hist
			TIter nextHist(file->GetListOfKeys());
			TKey* histKey(0);
			while ((histKey=(TKey*)nextHist())) {
				if (strcmp(histKey->GetClassName(),"TH1D")!=0) continue;
				TH1D* hmass = (TH1D*)histKey->ReadObj();
				string histname(hmass->GetName());
				if(histname.find(vdir[i])==std::string::npos) continue;
				if(histname.find("pT1_")!=std::string::npos) continue;
				if(histname.find("pT2_")!=std::string::npos) continue;
				if(histname.find("mVis_")!=std::string::npos) continue;
				if(histname.find("MET_")!=std::string::npos) continue;
				if(histname.find("_LIN")!=std::string::npos) continue;
				if(histname.find("_gen_")!=std::string::npos) continue;
				if(histname.find("_svfitmemtfk1")!=std::string::npos) continue;
				if(histname.find("_svfitmemtfk2")!=std::string::npos) continue;
				if(histname.find("_svfitmemtfk6")!=std::string::npos) continue;
				if(histname.find("_svfitmemtfk7")!=std::string::npos) continue;
				if(histname.find("_svfitmemtfk8")!=std::string::npos) continue;
				if(histname.find("_svfitclatfk1")!=std::string::npos) continue;
				if(histname.find("_svfitclatfk2")!=std::string::npos) continue;
				if(histname.find("_svfitclatfk6")!=std::string::npos) continue;
				if(histname.find("_svfitclatfk7")!=std::string::npos) continue;
				if(histname.find("_svfitclatfk8")!=std::string::npos) continue;
				if(histname.find("_ratio")==std::string::npos) continue;

                                hmass->Scale(1./hmass->Integral());
				vhmass.push_back((TH1D*)hmass->Clone());
				vhmass.back()->SetLineWidth(2);

				cout<<"integral: "<<vhmass.back()->Integral()<<endl;
				cout<<"mean: "<<vhmass.back()->GetMean()<<endl;
				cout<<"mean/RMS: "<<vhmass.back()->GetMean()/vhmass.back()->GetRMS()<<endl;

				for(int j=0; j<vhmass.back()->GetNbinsX(); j++){
					vhmass.back()->SetBinContent(j+1, vhmass.back()->GetBinContent(j+1)/vhmass.back()->GetBinWidth(j+1));
					vhmass.back()->SetBinError(j+1, vhmass.back()->GetBinError(j+1)/vhmass.back()->GetBinWidth(j+1));
				}


				if     (histname.find("ca")!=std::string::npos)          {vhmass.back()->SetLineStyle(6); vhmass.back()->SetLineColor(kGreen); }
				else if(histname.find("svFit")!=std::string::npos)       {vhmass.back()->SetLineStyle(2); vhmass.back()->SetLineColor(kBlue); }
				else if(histname.find("svfitmemtfk0")!=std::string::npos){vhmass.back()->SetLineStyle(3); vhmass.back()->SetLineColor(kMagenta); }
				else if(histname.find("svfitclatfk0")!=std::string::npos){vhmass.back()->SetLineStyle(3); vhmass.back()->SetLineColor(kBlack); }
				else if(histname.find("svfitmemtfk3")!=std::string::npos || histname.find("svfitmemtfk4")!=std::string::npos ||
                                        histname.find("svfitmemtfk5")!=std::string::npos){vhmass.back()->SetLineStyle(1); vhmass.back()->SetLineColor(kRed);}
				else if(histname.find("svfitclatfk3")!=std::string::npos || histname.find("svfitclatfk4")!=std::string::npos ||
                                        histname.find("svfitclatfk5")!=std::string::npos){vhmass.back()->SetLineStyle(1); vhmass.back()->SetLineColor(kOrange);}


				if(vdir[i]=="emu_smeared"){
					if( histname.find("_ca")!=std::string::npos || histname.find("_svFit")!=std::string::npos || 
							histname.find("_svfitmemtfk0")!=std::string::npos || histname.find("_svfitmemtfk3")!=std::string::npos ||
							histname.find("_svfitclatfk0")!=std::string::npos || histname.find("_svfitclatfk3")!=std::string::npos ){
						if ( input.find("M200_")!=std::string::npos){ 
							if(histname.find("_ca")!=std::string::npos) legend->AddEntry( vhmass.back(), "m_{ca}", "l");
							if(histname.find("_svFit")!=std::string::npos)        legend->AddEntry( vhmass.back(), "SVfit", "l");
							if(histname.find("_svfitmemtfk0")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 0", "l");
							if(histname.find("_svfitmemtfk3")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 3", "l");
							if(histname.find("_svfitclatfk0")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfit standalone, #kappa = 0", "l");
							if(histname.find("_svfitclatfk3")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfit standalone, #kappa = 3", "l");
						}
						if(input.find("M200_")!=std::string::npos)  {canvas[i]->cd(1); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M200_")!=std::string::npos)  {canvas[i]->cd(6); legend->Draw("same"); }
						if(input.find("M300_")!=std::string::npos)  {canvas[i]->cd(2); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M500_")!=std::string::npos)  {canvas[i]->cd(3); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M800_")!=std::string::npos)  {canvas[i]->cd(4); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M1200_")!=std::string::npos) {canvas[i]->cd(5); vhmass.back()->Draw("same&hist"); } 
					} 
				}if(vdir[i]=="muhad_smeared"){
					if( histname.find("_ca")!=std::string::npos || histname.find("_svFit")!=std::string::npos || 
							histname.find("_svfitmemtfk0")!=std::string::npos || histname.find("_svfitmemtfk4")!=std::string::npos ||
							histname.find("_svfitclatfk0")!=std::string::npos || histname.find("_svfitclatfk4")!=std::string::npos ){
						if ( input.find("M200_")!=std::string::npos){ 
							if(histname.find("_ca")!=std::string::npos) legend->AddEntry( vhmass.back(), "m_{ca}", "l");
							if(histname.find("_svFit")!=std::string::npos)        legend->AddEntry( vhmass.back(), "SVfit", "l");
							if(histname.find("_svfitmemtfk0")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 0", "l");
							if(histname.find("_svfitmemtfk4")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 4", "l");
							if(histname.find("_svfitclatfk0")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfit standalone, #kappa = 0", "l");
							if(histname.find("_svfitclatfk4")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfit standalone, #kappa = 4", "l");
						}
						if(input.find("M200_")!=std::string::npos)  {canvas[i]->cd(1); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M200_")!=std::string::npos)  {canvas[i]->cd(6); legend->Draw("same"); }
						if(input.find("M300_")!=std::string::npos)  {canvas[i]->cd(2); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M500_")!=std::string::npos)  {canvas[i]->cd(3); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M800_")!=std::string::npos)  {canvas[i]->cd(4); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M1200_")!=std::string::npos) {canvas[i]->cd(5); vhmass.back()->Draw("same&hist"); } 
					} 
				}if(vdir[i]=="hadhad_smeared"){
					if( histname.find("_ca")!=std::string::npos || histname.find("_svFit")!=std::string::npos || 
							histname.find("_svfitmemtfk0")!=std::string::npos || histname.find("_svfitmemtfk5")!=std::string::npos ||
							histname.find("_svfitclatfk0")!=std::string::npos || histname.find("_svfitclatfk5")!=std::string::npos ){
						if ( input.find("M200_")!=std::string::npos){ 
							if(histname.find("_ca")!=std::string::npos) legend->AddEntry( vhmass.back(), "m_{ca}", "l");
							if(histname.find("_svFit")!=std::string::npos)        legend->AddEntry( vhmass.back(), "SVfit", "l");
							if(histname.find("_svfitmemtfk0")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 0", "l");
							if(histname.find("_svfitmemtfk5")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 5", "l");
							if(histname.find("_svfitclatfk0")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfit standalone, #kappa = 0", "l");
							if(histname.find("_svfitclatfk5")!=std::string::npos) legend->AddEntry( vhmass.back(), "SVfit standalone, #kappa = 5", "l");
						}
						if(input.find("M200_")!=std::string::npos)  {canvas[i]->cd(1); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M200_")!=std::string::npos)  {canvas[i]->cd(6); legend->Draw("same"); }
						if(input.find("M300_")!=std::string::npos)  {canvas[i]->cd(2); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M500_")!=std::string::npos)  {canvas[i]->cd(3); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M800_")!=std::string::npos)  {canvas[i]->cd(4); vhmass.back()->Draw("same&hist"); } 
						if(input.find("M1200_")!=std::string::npos) {canvas[i]->cd(5); vhmass.back()->Draw("same&hist"); } 
					} 
				}
			} // while hist
		} // input file
	} // dir

	//save canvas
	for(int i=0; i<ndir; i++){
		if(log){ 
			imagepng = savePath+"plot_10to12_log_ratio_"+canvas[i]->GetName()+".png";
			imageroot = savePath+"plot_10to12_log_ratio_"+canvas[i]->GetName()+".root";
		}
		else {
			imagepng = savePath+"plot_10to12_lin_ratio_"+canvas[i]->GetName()+".png";
			imageroot = savePath+"plot_10to12_lin_ratio_"+canvas[i]->GetName()+".root";
		}
		canvas[i]->Print(imagepng.c_str()); 
		canvas[i]->Print(imageroot.c_str()); 
	} 

} // void


