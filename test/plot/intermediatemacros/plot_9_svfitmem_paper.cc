#include "func.C"


void plot_9_svfitmem_paper(){

  // plot histogram
  cout<<"plotting hist...\n";

  string inputPath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_IV/"};
  string savePath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/"};
  // root file
  vector<string> vinput {
    "hist_GluGluHToTauTauM125_0Jets.root",
    "hist_GluGluHToTauTauM125_1JetNotBoosted.root",
    "hist_GluGluHToTauTauM125_1JetBoosted.root",
    "hist_VBFHToTauTauM125_2Jets.root",
    "hist_DYJetsToLLM50_0Jets.root",
    "hist_DYJetsToLLM50_1JetNotBoosted.root",
    "hist_DYJetsToLLM50_1JetBoosted.root",
    "hist_DYJetsToLLM50_2Jets.root",
  };

  vector<string>vsample{
    "GluGluHToTauTauM125_0Jets",
    "GluGluHToTauTauM125_1JetNotBoosted",
    "GluGluHToTauTauM125_1JetBoosted",
    "VBFHToTauTauM125_2Jets",
    "DYJetsToLLM50_0Jets",
    "DYJetsToLLM50_1JetNotBoosted",
    "DYJetsToLLM50_1JetBoosted",
    "DYJetsToLLM50_2Jets",
  }; 

  func();

  bool log{0};
  int numbin{25};

  vector<string>vdir{"muhad_smeared"};
  
  int ndir{static_cast<int>(vdir.size())};
  
  TH1D *haxispt  = new TH1D("", "", 100, 0, 1000);
  TH1D *haxisphi = new TH1D("", "", 100, -5, 5);
  haxispt->SetStats(false);
  haxispt->GetYaxis()->SetRangeUser(0.01,0.1);
  haxispt->GetXaxis()->SetRangeUser(0,100);
  haxisphi->GetYaxis()->SetRangeUser(0.01,10);
  //haxisphi->GetXaxis()->SetRangeUser(-4,4);
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
	      //if(histname.find("diTau")==std::string::npos)  continue;
	      //if(histname.find("tauD")==std::string::npos)  continue;
	      
	      //
              vh.push_back((TH1D*)h->Clone());
 
	      if ( input.find("_0Jets")!=std::string::npos)           vh.back()->SetLineColor(1); 
	      if ( input.find("_1JetNotBoosted")!=std::string::npos)  vh.back()->SetLineColor(2);  
	      if ( input.find("_1JetBoosted")!=std::string::npos)     vh.back()->SetLineColor(3); 
	      if ( input.find("_2Jets")!=std::string::npos)           vh.back()->SetLineColor(4); 

	      for(int j=0; j<vh.back()->GetNbinsX(); j++){
		      vh.back()->SetBinContent(j+1, vh.back()->GetBinContent(j+1)/vh.back()->GetBinWidth(j+1));
		      vh.back()->SetBinError(j+1, vh.back()->GetBinError(j+1)/vh.back()->GetBinWidth(j+1));
	      }

	      if(input.find("HToTauTauM125")!=std::string::npos){ 
		      if(histname.find("diTauPt_")!=std::string::npos){ canvas[i]->cd(1); vh.back()->Draw("same&hist"); }
		      if(histname.find("tauDPhi_")!=std::string::npos){ vh.back()->Rebin(2); canvas[i]->cd(2); vh.back()->Draw("same&hist"); }
	      }
	      if(input.find("DYJetsToLLM50")!=std::string::npos)  {
		      if(histname.find("diTauPt_")!=std::string::npos){ canvas[i]->cd(3); vh.back()->Draw("same&hist"); }
		      if(histname.find("tauDPhi_")!=std::string::npos){ vh.back()->Rebin(2); canvas[i]->cd(4); vh.back()->Draw("same&hist"); }
	      }
      }
    } // input file
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


