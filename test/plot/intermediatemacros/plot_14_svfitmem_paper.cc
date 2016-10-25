#include "func.C"


void plot_14_svfitmem_paper(){

  // plot histogram
  cout<<"plotting hist...\n";

  string inputPath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_V/"};
  //string savePath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/"};
  string savePath{"/home/veelken/SVfitMEM_paper/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/"};
  // root file

  vector<string> vinput {
    "hist_smeared_DYJetsToLLM50_inclusive.root",
    "hist_smeared_GluGluHToTauTauM125_inclusive.root",
  };

  vector<string>vsample{
    "DYJetsToLLM50_inclusive",
    "GluGluHToTauTauM125_inclusive",
  }; 

  func();

  bool log{0};
  int numbin{25};

  vector<string>vdir{"emu_smeared", "muhad_smeared",   "hadhad_smeared"};
  vector<string>vdirleg{"e#mu", "#mu#tau_{h}", "#tau_{h}#tau_{h}"};
  
  TH1D *haxispt  = new TH1D("", "", 700, -100, 250);
  TH1D *haxisphi = new TH1D("", "", 100, -5, 5);
  haxispt->GetYaxis()->SetRangeUser(0.01,1);
  haxispt->GetXaxis()->SetRangeUser(-20,30);
  haxisphi->GetYaxis()->SetRangeUser(0.01,10);
  //haxisphi->GetXaxis()->SetRangeUser(-4,4);
  haxispt->SetStats(false);
  haxisphi->SetStats(false);
  haxispt->SetTitle("");
  haxisphi->SetTitle("");

  int ndir{static_cast<int>(vdir.size())};
  TCanvas *canvas = new TCanvas("canvas_smeared","canvas_smeared", 900, 700);
  canvas->Divide(3, 3);

  canvas->cd(1);
  gPad->SetLogy();
  haxispt->Draw();

  canvas->cd(2);
  gPad->SetLogy();
  haxisphi->Draw();

  canvas->cd(3);
  if(log) gPad->SetLogx();
  gPad->SetLogy();
  haxisphi->Draw();

  canvas->cd(4);
  gPad->SetLogy();
  haxispt->Draw();

  canvas->cd(5);
  gPad->SetLogy();
  haxisphi->Draw();

  canvas->cd(6);
  if(log) gPad->SetLogx();
  gPad->SetLogy();
  haxisphi->Draw();

  canvas->cd(7);
  gPad->SetLogy();
  haxispt->Draw();

  canvas->cd(8);
  gPad->SetLogy();
  haxisphi->Draw();

  canvas->cd(9);
  if(log) gPad->SetLogx();
  gPad->SetLogy();
	  haxisphi->Draw();


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
	if(histname.find("genMinus")==std::string::npos) continue;
        
        hmass->Scale(1./hmass->Integral());
	vhmass.push_back((TH1D*)hmass->Clone());

	for(int j=0; j<vhmass.back()->GetNbinsX(); j++){
		vhmass.back()->SetBinContent(j+1, vhmass.back()->GetBinContent(j+1)/vhmass.back()->GetBinWidth(j+1));
		vhmass.back()->SetBinError(j+1, vhmass.back()->GetBinError(j+1)/vhmass.back()->GetBinWidth(j+1));
	}

	if     (histname.find("_genMinusVisible_")!=std::string::npos)  {
                                     if(sample.find("DYJets")!=std::string::npos) vhmass.back()->SetLineColor(1); 
                                     else vhmass.back()->SetLineColor(2); 
	}else if(histname.find("genMinusClassicSVfitComputingTime_cpu0")!=std::string::npos){
		if(sample.find("DYJets")!=std::string::npos) vhmass.back()->SetLineColor(3); 
		else vhmass.back()->SetLineColor(4); 
        }else if(histname.find("genMinusClassicSVfitComputingTime_cpu3")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu4")!=std::string::npos || 
			histname.find("genMinusClassicSVfitComputingTime_cpu5")!=std::string::npos){
		if(sample.find("DYJets")!=std::string::npos) vhmass.back()->SetLineColor(5);
		else vhmass.back()->SetLineColor(6);
        }

	if( vdir[i]=="emu_smeared"){
		if( histname.find("_genMinusVisible_pt")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu0_pt")!=std::string::npos 
                   || histname.find("genMinusClassicSVfitComputingTime_cpu3_pt")!=std::string::npos) 
				{canvas->cd(1); vhmass.back()->Rebin(20); vhmass.back()->Draw("same&hist"); }
		if( histname.find("_genMinusVisible_eta")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu0_eta")!=std::string::npos 
                   || histname.find("genMinusClassicSVfitComputingTime_cpu3_eta")!=std::string::npos) 
				{canvas->cd(2); vhmass.back()->Rebin(4); vhmass.back()->Draw("same&hist"); }
		if( histname.find("_genMinusVisible_phi")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu0_phi")!=std::string::npos 
                   || histname.find("genMinusClassicSVfitComputingTime_cpu3_phi")!=std::string::npos) 
				{canvas->cd(3); vhmass.back()->Rebin(4); vhmass.back()->Draw("same&hist"); }
	}if( vdir[i]=="muhad_smeared"){
		if( histname.find("_genMinusVisible_pt")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu0_pt")!=std::string::npos 
                   || histname.find("genMinusClassicSVfitComputingTime_cpu4_pt")!=std::string::npos) 
				{canvas->cd(4); vhmass.back()->Rebin(20); vhmass.back()->Draw("same&hist"); }
		if( histname.find("_genMinusVisible_eta")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu0_eta")!=std::string::npos 
                   || histname.find("genMinusClassicSVfitComputingTime_cpu4_eta")!=std::string::npos) 
				{canvas->cd(5); vhmass.back()->Rebin(4); vhmass.back()->Draw("same&hist"); }
		if( histname.find("_genMinusVisible_phi")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu0_phi")!=std::string::npos 
                   || histname.find("genMinusClassicSVfitComputingTime_cpu4_phi")!=std::string::npos) 
				{canvas->cd(6); vhmass.back()->Rebin(4); vhmass.back()->Draw("same&hist"); } 
	}if( vdir[i]=="hadhad_smeared"){
		if( histname.find("_genMinusVisible_pt")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu0_pt")!=std::string::npos 
                   || histname.find("genMinusClassicSVfitComputingTime_cpu5_pt")!=std::string::npos) 
				{canvas->cd(7); vhmass.back()->Rebin(20); vhmass.back()->Draw("same&hist"); }
		if( histname.find("_genMinusVisible_eta")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu0_eta")!=std::string::npos 
                   || histname.find("genMinusClassicSVfitComputingTime_cpu5_eta")!=std::string::npos) 
				{canvas->cd(8); vhmass.back()->Rebin(4); vhmass.back()->Draw("same&hist"); }
		if( histname.find("_genMinusVisible_phi")!=std::string::npos || histname.find("genMinusClassicSVfitComputingTime_cpu0_phi")!=std::string::npos 
                   || histname.find("genMinusClassicSVfitComputingTime_cpu5_phi")!=std::string::npos) 
				{canvas->cd(9); vhmass.back()->Rebin(4); vhmass.back()->Draw("same&hist"); } 
	}
    } // while hist
  } // input file
} // dir

//save canvas
if(log){ 
	imagepng = savePath+"plot_14_log.png";
	imageroot = savePath+"plot_14_log.root";
}
else {
	imagepng = savePath+"plot_14_lin.png";
	imageroot = savePath+"plot_14_lin.root";
}
canvas->Print(imagepng.c_str()); 
canvas->Print(imageroot.c_str()); 

} // void


