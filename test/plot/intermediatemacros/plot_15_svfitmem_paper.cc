#include "func.C"


void plot_15_svfitmem_paper(){

  // plot histogram
  cout<<"plotting hist...\n";

  string inputPath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_IV/"};
  string savePath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/"};
  // root file

  vector<string> vinput {
    "hist_smeared_DYJetsToLLM50_inclusive.root",
    "hist_smeared_HToTauTauM125_inclusive.root",
  };

  vector<string>vsample{
    "DYJetsToLLM50_inclusive",
    "HToTauTauM125_inclusive",
  }; 

  func();

  bool log{1};
  int numbin{25};

  vector<string>vdir{"emu_smeared", "muhad_smeared",   "hadhad_smeared"};
  vector<string>vdirleg{"e#mu", "#mu#tau_{h}", "#tau_{h}#tau_{h}"};
  
  TH1D *haxis = new TH1D("", "", 80, 0.01, 1000);
  haxis->SetStats(false);
  //haxis->GetXaxis()->SetRangeUser(0, 10);
  haxis->GetYaxis()->SetRangeUser(0.0001, 10);
  //haxis->SetTitle("m_{#tau#tau}[GeV]");


  int ndir{static_cast<int>(vdir.size())};
  
  TCanvas *canvas;

  canvas = new TCanvas("canvas_smeared","canvas_smeared", 900, 700); 
  canvas->Divide(2,3);

  canvas->cd(1);
  if(log) gPad->SetLogx();
  gPad->SetLogy();
  haxis->Draw();

  canvas->cd(2);
  if(log) gPad->SetLogx();
  gPad->SetLogy();
  haxis->Draw();
  
  canvas->cd(3);
  if(log) gPad->SetLogx();
  gPad->SetLogy();
  haxis->Draw();
  
  canvas->cd(4);
  if(log) gPad->SetLogx();
  gPad->SetLogy();
  haxis->Draw();
  
  canvas->cd(5);
  if(log) gPad->SetLogx();
  gPad->SetLogy();
  haxis->Draw();
  
  canvas->cd(6);
  if(log) gPad->SetLogx();
  gPad->SetLogy();
  haxis->Draw();
  
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
	if(histname.find("ComputingTime")==std::string::npos) continue;
        hmass->Scale(1./hmass->Integral());
	vhmass.push_back((TH1D*)hmass->Clone());

	for(int j=0; j<vhmass.back()->GetNbinsX(); j++){
		vhmass.back()->SetBinContent(j+1, vhmass.back()->GetBinContent(j+1)/vhmass.back()->GetBinWidth(j+1));
		vhmass.back()->SetBinError(j+1, vhmass.back()->GetBinError(j+1)/vhmass.back()->GetBinWidth(j+1));
	}


	if     (histname.find("memSVfitComputingTime_cpu_LOG")!=std::string::npos){ 
		vhmass.back()->SetLineColor(1);
	}
	else if(histname.find("memSVfitComputingTime_cpulo0")!=std::string::npos){
		vhmass.back()->SetLineColor(2);
	}
	else if(histname.find("classicSVfitComputingTime_cpu0")!=std::string::npos){
		vhmass.back()->SetLineColor(3);
        }
	else if(histname.find("memSVfitComputingTime_cpulo3")!=std::string::npos || histname.find("memSVfitComputingTime_cpulo4")!=std::string::npos || 
			histname.find("memSVfitComputingTime_cpulo5")!=std::string::npos){
		vhmass.back()->SetLineColor(4);
        }
	else if(histname.find("classicSVfitComputingTime_cpu3")!=std::string::npos || histname.find("classicSVfitComputingTime_cpu4")!=std::string::npos || 
			histname.find("classicSVfitComputingTime_cpu5")!=std::string::npos){
		vhmass.back()->SetLineColor(5);
        }


	if( vdir[i]=="emu_smeared"){
		if( histname.find("svfitComputingTime_cpu_LOG")!=std::string::npos || histname.find("memSVfitComputingTime_cpulo0")!=std::string::npos || 
		    histname.find("classicSVfitComputingTime_cpu0")!=std::string::npos || histname.find("memSVfitComputingTime_cpulo3")!=std::string::npos || 
		    histname.find("classicSVfitComputingTime_cpu3")!=std::string::npos ){

			if(input.find("DYJetsToLLM50")!=std::string::npos)  {
				canvas->cd(5); vhmass.back()->Draw("same&hist"); 
			}
			if(input.find("HToTauTauM125")!=std::string::npos) {
				canvas->cd(6); vhmass.back()->Draw("same&hist"); 
			}
		}
	}if( vdir[i]=="muhad_smeared"){
		if( histname.find("svfitComputingTime_cpu_LOG")!=std::string::npos || histname.find("memSVfitComputingTime_cpulo0")!=std::string::npos || 
		    histname.find("classicSVfitComputingTime_cpu0")!=std::string::npos || histname.find("memSVfitComputingTime_cpulo4")!=std::string::npos || 
		    histname.find("classicSVfitComputingTime_cpu4")!=std::string::npos ){

			if(input.find("DYJetsToLLM50")!=std::string::npos)  {
				canvas->cd(3); vhmass.back()->Draw("same&hist"); 
			}
			if(input.find("HToTauTauM125")!=std::string::npos) {
				canvas->cd(4); vhmass.back()->Draw("same&hist"); 
			}
		}
	}if( vdir[i]=="hadhad_smeared"){

		if( histname.find("svfitComputingTime_cpu_LOG")!=std::string::npos || histname.find("memSVfitComputingTime_cpulo0")!=std::string::npos || 
		    histname.find("classicSVfitComputingTime_cpu0")!=std::string::npos || histname.find("memSVfitComputingTime_cpulo5")!=std::string::npos || 
		    histname.find("classicSVfitComputingTime_cpu5")!=std::string::npos ){

			if(input.find("DYJetsToLLM50")!=std::string::npos)  {
				canvas->cd(1); vhmass.back()->Draw("same&hist"); 
			}
			if(input.find("HToTauTauM125")!=std::string::npos) {
				canvas->cd(2); vhmass.back()->Draw("same&hist"); 
			}
		}
        }
    } // while hist
  } // input file
} // dir

//save canvas
if(log){ 
	imagepng = savePath+"plot_15_log.png";
	imageroot = savePath+"plot_15_log.root";
}
else {
	imagepng = savePath+"plot_15_lin.png";
	imageroot = savePath+"plot_15_lin.root";
}
canvas->Print(imagepng.c_str()); 
canvas->Print(imageroot.c_str()); 

} // void


