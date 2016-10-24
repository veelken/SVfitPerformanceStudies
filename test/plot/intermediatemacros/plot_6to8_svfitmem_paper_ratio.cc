#include "func.C"


void plot_6to8_svfitmem_paper_ratio(){

  // plot histogram
  cout<<"plotting hist...\n";

  string inputPath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_V/"};
  string savePath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/"};
  // root file
  vector<string> vinput {
    "hist_smeared_DYJetsToLLM50_0Jets.root",
    "hist_smeared_GluGluHToTauTauM125_0Jets.root",
    "hist_smeared_DYJetsToLLM50_1JetNotBoosted.root",
    "hist_smeared_GluGluHToTauTauM125_1JetNotBoosted.root",
    "hist_smeared_DYJetsToLLM50_1JetBoosted.root",
    "hist_smeared_GluGluHToTauTauM125_1JetBoosted.root",
    "hist_smeared_DYJetsToLLM50_2Jets.root",
    "hist_smeared_VBFHToTauTauM125_2Jets.root"
  };

  vector<string>vsample{
    "DYJetsToLLM50_0Jets",
    "GluGluHToTauTauM125_0Jets",
    "DYJetsToLLM50_1JetNotBoosted",
    "GluGluHToTauTauM125_1JetNotBoosted",
    "DYJetsToLLM50_1JetBoosted",
    "GluGluHToTauTauM125_1JetBoosted",
    "DYJetsToLLM50_2Jets",
    "VBFHToTauTauM125_2Jets"
  }; 

  func();

  bool log{1};
  int numbin{25};

  vector<string>vdir{"emu_smeared", "muhad_smeared",   "hadhad_smeared"};
  vector<string>vdirleg{"e#mu", "#mu#tau_{h}", "#tau_{h}#tau_{h}"};
  
  TH1D *haxis = new TH1D("", "", 100, 0, 10);
  haxis->SetStats(false);
  haxis->GetXaxis()->SetRangeUser(0, 10);
  haxis->GetYaxis()->SetRangeUser(0.0001, 10);
  haxis->GetXaxis()->SetTitleOffset(1.);
  haxis->GetYaxis()->SetTitleOffset(1.4);
  haxis->GetXaxis()->SetTitle("m_{#tau#tau}[GeV]");
  haxis->GetYaxis()->SetTitle("dN/dm_{#tau#tau}[1/GeV]");


  int ndir{static_cast<int>(vdir.size())};
  
  TCanvas *canvas[ndir];

  for(int i=0; i<ndir; i++){
    canvas[i] = new TCanvas(vdir[i].c_str(), vdir[i].c_str(), 900, 700); 
    canvas[i]->Divide(2, 4);

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

    canvas[i]->cd(6);
    if(log) gPad->SetLogx();
    gPad->SetLogy();
    haxis->Draw();
    
    canvas[i]->cd(7);
    if(log) gPad->SetLogx();
    gPad->SetLogy();
    haxis->Draw();
    
    canvas[i]->cd(8);
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
	if(histname.find("_ratio")==std::string::npos) continue;
	if(histname.find("_LIN")!=std::string::npos)  continue;
	if(histname.find("diTau")!=std::string::npos)  continue;
	if(histname.find("pT1_")!=std::string::npos)  continue;
	if(histname.find("pT2_")!=std::string::npos)  continue;
	if(histname.find("pT2_")!=std::string::npos)  continue;
	if(histname.find("mVis_")!=std::string::npos) continue;
	if(histname.find("MET_")!=std::string::npos)  continue;
	if(histname.find("tfk1")!=std::string::npos) continue;
	if(histname.find("tfk2")!=std::string::npos) continue;
	if(i==0 && histname.find("tfk4")!=std::string::npos) continue;
	if(i==0 && histname.find("tfk5")!=std::string::npos) continue;
	if(i==1 && histname.find("tfk3")!=std::string::npos) continue;
	if(i==1 && histname.find("tfk5")!=std::string::npos) continue;
	if(i==2 && histname.find("tfk3")!=std::string::npos) continue;
	if(i==2 && histname.find("tfk4")!=std::string::npos) continue;
	if(histname.find("tfk6")!=std::string::npos) continue;
	if(histname.find("tfk7")!=std::string::npos) continue;
	if(histname.find("tfk8")!=std::string::npos) continue;
	if(histname.find("Jet")!=std::string::npos) continue;
	
        hmass->Scale(1./hmass->Integral());
	vhmass.push_back((TH1D*)hmass->Clone());
	vhmass.back()->SetLineWidth(2);
        //vhmass.back()->Rebin( vhmass.back()->GetXaxis()->GetNbins()/40 );
	vhmass.back()->GetYaxis()->SetRangeUser(0.0001, 0.50);

        cout<<vhmass.back()->GetName()<<": "<<vhmass.back()->Integral()<<endl;
        //cout<<"integral: "<<vhmass.back()->Integral()<<endl;
	//cout<<"mean: "<<vhmass.back()->GetMean()<<endl;
	///cout<<"mean/RMS: "<<vhmass.back()->GetMean()/vhmass.back()->GetRMS()<<endl;

	for(int j=0; j<vhmass.back()->GetNbinsX(); j++){


               if(i==0 && histname.find("svfitclatfk0")!=std::string::npos && input.find("DYJetsToLLM50_2Jets")!=std::string::npos) cout <<" bin " << j+1 << " content " << vhmass.back()->GetBinContent(j+1) << endl;

		vhmass.back()->SetBinContent(j+1, vhmass.back()->GetBinContent(j+1)/vhmass.back()->GetBinWidth(j+1));
		vhmass.back()->SetBinError(j+1, vhmass.back()->GetBinError(j+1)/vhmass.back()->GetBinWidth(j+1));
               
                if(i==0 && histname.find("svfitclatfk0")!=std::string::npos && input.find("DYJetsToLLM50_2Jets")!=std::string::npos) cout <<" bin " << j+1 << " content " << vhmass.back()->GetBinContent(j+1) << endl;

	}


	if     (histname.find("ca")!=std::string::npos)          {vhmass.back()->SetLineStyle(6); vhmass.back()->SetLineColor(kGreen); }
	else if(histname.find("svFit")!=std::string::npos)       {vhmass.back()->SetLineStyle(2); vhmass.back()->SetLineColor(kBlue); }
	else if(histname.find("svfitmemtfk0")!=std::string::npos){vhmass.back()->SetLineStyle(3); vhmass.back()->SetLineColor(kMagenta); }
	else if(histname.find("svfitclatfk0")!=std::string::npos){vhmass.back()->SetLineStyle(3); vhmass.back()->SetLineColor(kBlack); }
	else if(histname.find("svfitmemtfk3")!=std::string::npos || histname.find("svfitmemtfk4")!=std::string::npos || 
			histname.find("svfitmemtfk5")!=std::string::npos){vhmass.back()->SetLineStyle(1); vhmass.back()->SetLineColor(kRed);}
	else if(histname.find("svfitclatfk3")!=std::string::npos || histname.find("svfitclatfk4")!=std::string::npos || 
			histname.find("svfitclatfk5")!=std::string::npos){vhmass.back()->SetLineStyle(1); vhmass.back()->SetLineColor(kOrange);}


	if( vdir[i]=="emu_smeared"){
		if( histname.find("_svfitclatfk0")!=std::string::npos || histname.find("_svfitclatfk3")!=std::string::npos || histname.find("_ca")!=std::string::npos || histname.find("_svFit")!=std::string::npos || histname.find("_svfitmemtfk0")!=std::string::npos || histname.find("_svfitmemtfk3")!=std::string::npos ){

			if(input.find("DYJetsToLLM50_0Jets")!=std::string::npos)  {
                                cout << " nbins " << vhmass.back()->GetXaxis()->GetNbins() << endl;
                                cout << " DYJetsToLLM50_0Jets " << vhmass.back()->GetName();
				canvas[i]->cd(1); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist"); 
			}
			if(input.find("GluGluHToTauTauM125_0Jets")!=std::string::npos) {
                                cout << " GluGluHToTauTauM125_0Jets " << vhmass.back()->GetName();
				canvas[i]->cd(2); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist"); 
			}
			if(input.find("DYJetsToLLM50_1JetNotBoosted")!=std::string::npos)  {
                                cout << " DYJetsToLLM50_1JetNotBoosted " << vhmass.back()->GetName();
				canvas[i]->cd(3); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist"); 
			}
			if(input.find("GluGluHToTauTauM125_1JetNotBoosted")!=std::string::npos) {
                                cout << " GluGluHToTauTauM125_1JetNotBoosted " << vhmass.back()->GetName();
				canvas[i]->cd(4); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");  
			}
			if(input.find("DYJetsToLLM50_1JetBoosted")!=std::string::npos)  {
                                cout << " DYJetsToLLM50_1JetBoosted " << vhmass.back()->GetName();
				canvas[i]->cd(5); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist"); 
			}
			if(input.find("GluGluHToTauTauM125_1JetBoosted")!=std::string::npos) {
                                cout << " GluGluHToTauTauM125_1JetBoosted " << vhmass.back()->GetName();
				canvas[i]->cd(6); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");  
			}
			if(input.find("DYJetsToLLM50_2Jets")!=std::string::npos)  {
                                cout << " DYJetsToLLM50_2Jets " << vhmass.back()->GetName();
				canvas[i]->cd(7); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist"); 
			}
			if(input.find("VBFHToTauTauM125_2Jets")!=std::string::npos) {
                                cout << " VBFHToTauTauM125_2Jets " << vhmass.back()->GetName();
				canvas[i]->cd(8); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");  
			}
		}
	}if( vdir[i]=="muhad_smeared"){
                if( histname.find("_svfitclatfk0")!=std::string::npos || histname.find("_svfitclatfk4")!=std::string::npos || histname.find("_ca")!=std::string::npos || histname.find("_svFit")!=std::string::npos || histname.find("_svfitmemtfk0")!=std::string::npos || histname.find("_svfitmemtfk4")!=std::string::npos ){

                        if(input.find("DYJetsToLLM50_0Jets")!=std::string::npos)  {
                                canvas[i]->cd(1); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("GluGluHToTauTauM125_0Jets")!=std::string::npos) {
                                canvas[i]->cd(2); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("DYJetsToLLM50_1JetNotBoosted")!=std::string::npos)  {
                                canvas[i]->cd(3); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("GluGluHToTauTauM125_1JetNotBoosted")!=std::string::npos) {
                                canvas[i]->cd(4); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("DYJetsToLLM50_1JetBoosted")!=std::string::npos)  {
                                canvas[i]->cd(5); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("GluGluHToTauTauM125_1JetBoosted")!=std::string::npos) {
                                canvas[i]->cd(6); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("DYJetsToLLM50_2Jets")!=std::string::npos)  {
                                canvas[i]->cd(7); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("VBFHToTauTauM125_2Jets")!=std::string::npos) {
                                canvas[i]->cd(8); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                }
        }if( vdir[i]=="hadhad_smeared"){
                if( histname.find("_svfitclatfk0")!=std::string::npos || histname.find("_svfitclatfk5")!=std::string::npos || histname.find("_ca")!=std::string::npos || histname.find("_svFit")!=std::string::npos || histname.find("_svfitmemtfk0")!=std::string::npos || histname.find("_svfitmemtfk5")!=std::string::npos ){

                        if(input.find("DYJetsToLLM50_0Jets")!=std::string::npos)  {
                                canvas[i]->cd(1); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("GluGluHToTauTauM125_0Jets")!=std::string::npos) {
                                canvas[i]->cd(2); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("DYJetsToLLM50_1JetNotBoosted")!=std::string::npos)  {
                                canvas[i]->cd(3); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("GluGluHToTauTauM125_1JetNotBoosted")!=std::string::npos) {
                                canvas[i]->cd(4); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("DYJetsToLLM50_1JetBoosted")!=std::string::npos)  {
                                canvas[i]->cd(5); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("GluGluHToTauTauM125_1JetBoosted")!=std::string::npos) {
                                canvas[i]->cd(6); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("DYJetsToLLM50_2Jets")!=std::string::npos)  {
                                canvas[i]->cd(7); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                        if(input.find("VBFHToTauTauM125_2Jets")!=std::string::npos) {
                                canvas[i]->cd(8); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist");
                        }
                }
        }

    } // while hist
  } // input file
} // dir

//save canvas
for(int i=0; i<ndir; i++){
  if(log){ 
    imagepng = savePath+"plot_6to8_log_ratio_"+canvas[i]->GetName()+".png";
    imageroot = savePath+"plot_6to8_log_ratio_"+canvas[i]->GetName()+".root";
  }
  else {
    imagepng = savePath+"plot_6to8_lin_ratio_"+canvas[i]->GetName()+".png";
    imageroot = savePath+"plot_6to8_lin_ratio_"+canvas[i]->GetName()+".root";
  }
  canvas[i]->Print(imagepng.c_str()); 
  canvas[i]->Print(imageroot.c_str()); 
} 

} // void


