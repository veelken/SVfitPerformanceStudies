#include "func.C"
#include <fstream>
#include <vector>
#include <math.h>

double Median(const TH1D * h1);
double rounded(double val);

void plot_13_ratio_svfitmem_paper(){

  // plot histogram
  cout<<"plotting hist...\n";

  string inputPath {"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_IV"};
  string savePath {"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot"};

  // root file
    vector<string> vinput {
          "hist_DYJetsToLLM50_inclusive.root",
          "hist_HToTauTauM125_inclusive.root",
          "hist_SUSYGluGluToHToTauTauM200_inclusive.root",
          "hist_SUSYGluGluToHToTauTauM300_inclusive.root",
          "hist_SUSYGluGluToHToTauTauM500_inclusive.root",
          "hist_SUSYGluGluToHToTauTauM800_inclusive.root",
          "hist_SUSYGluGluToHToTauTauM1200_inclusive.root",
          "hist_SUSYGluGluToHToTauTauM1800_inclusive.root",
          "hist_SUSYGluGluToHToTauTauM2600_inclusive.root"
  };

  vector<string>vsample{
          "DYJetsToLLM50",
          "HToTauTauM125",
          "SUSYGluGluToHToTauTauM200",
          "SUSYGluGluToHToTauTauM300",
          "SUSYGluGluToHToTauTauM500",
          "SUSYGluGluToHToTauTauM800",
          "SUSYGluGluToHToTauTauM1200",
          "SUSYGluGluToHToTauTauM1800",
          "SUSYGluGluToHToTauTauM2600"
  };


  func();

  bool log{0};

  TH1D *haxisvis = new TH1D("", "", 100, 0, 3);
  haxisvis->SetStats(false);
  haxisvis->GetXaxis()->SetRangeUser(0, 3);
  haxisvis->GetYaxis()->SetRangeUser(0, 1.5);
  haxisvis->GetXaxis()->SetTitleOffset(1.);
  haxisvis->GetYaxis()->SetTitleOffset(1.4);
  haxisvis->GetXaxis()->SetTitle("m_{vis}/m^{true}_{#tau#tau}");
  haxisvis->GetYaxis()->SetTitle("dN/dm_{vis}/m^{true}_{#tau#tau}");
  //
  TH1D *haxisrec=(TH1D*) haxisvis->Clone();
  haxisrec->GetXaxis()->SetTitle("m_{#tau#tau}/m^{true}_{#tau#tau}");
  haxisrec->GetYaxis()->SetTitle("dN/dm_{#tau#tau}/m^{true}_{#tau#tau}");

  vector<string>vdir{"emu_smeared","muhad_smeared","hadhad_smeared"};
  vector<string>vdirleg{"e#mu","#mu#tau_{h}","#tau_{h}#tau_{h}"};

  int ndir{static_cast<int>(vdir.size())};
  //
  TLegend *legend1[ndir];
  TLegend *legend2[ndir];
  TLegend *legend3[ndir];
  for(int i=0; i<ndir; i++){
    legend1[i] = new TLegend( 0.55, 0.55, 0.9, 0.9, NULL,"brNDC"); 
    legend1[i]->SetTextSize(0.034);
  }
  //
  TCanvas *canvas[ndir];
  for(int i=0; i<ndir; i++){
    canvas[i] = new TCanvas(vdir[i].c_str(), vdir[i].c_str(), 1200, 500); 
    canvas[i]->Divide(2, 1);
    canvas[i]->cd(1);
    if(log) gPad->SetLogy();
    haxisvis->Draw();
    canvas[i]->cd(2);
    if(log) gPad->SetLogy();
    haxisrec->Draw();
  }

  vector<TH1D*> vhmass;
  vector<TH1D*> vhmass_ratio;
  string imagepng;
  string imageroot;

  ofstream table1;
  table1.open("table1.txt");

  table1<< "\\begin{table}"<<endl;
  table1<< "\\begin{center}"<<endl;

  // loop over directories
  for(int i=0; i<ndir; i++){
    cout<<"\ndir: "<<vdir[i]<<endl;

    ///////////////////// latex table //////////////////
    table1<< "\\begin{tabular}{|l|cc|cc|}"<<endl;
    table1<< "\\hline"<<endl;
    if(vdir[i]=="hadhad_smeared") table1<< "\\multicolumn{5}{|c|}{$\\tauh\\tauh$ decay channel} \\\\"<<endl;
    else if(vdir[i]=="muhad_smeared") table1<< "\\multicolumn{5}{|c|}{$\\Pgm\\tauh$ decay channel} \\\\"<<endl;
    else table1<< "\\multicolumn{5}{|c|}{$\\Pe\\Pgm$  decay channel} \\\\"<<endl;
    table1<< "\\hline"<<endl;
    table1<< "\\hline"<<endl;
    if(vdir[i]=="emu_smeared") table1<< "\\multirow{2}{17mm}{Sample} & \\multicolumn{2}{c|}{$m_{\\vis}$} & \\multicolumn{2}{c|}{$m_{\\Pgt\\Pgt}$ (SVfitMEM, $\\kappa = 2$)} \\\\"<<endl;
    else table1<< "\\multirow{2}{17mm}{Sample} & \\multicolumn{2}{c|}{$m_{\\vis}$} & \\multicolumn{2}{c|}{$m_{\\Pgt\\Pgt}$ (SVfitMEM, $\\kappa = 3$)} \\\\"<<endl;

    table1<< "\\cline{2-5}"<<endl;
    //table1<< " & Mean & RMS/Mean & Mean~[\\GeV] & RMS/Mean \\\\"<<endl;
    table1<< " & Median~[\\GeV] & RMS/Median & Median~[\\GeV] & RMS/Median \\\\"<<endl;
    table1<< "\\hline"<<endl;
    ////////////////////////////////////////////////////

    // loop over input files
    for (int in=0; in<vinput.size(); in++){ 
      string input{inputPath+"/"+vinput[in]};
      TFile *file = new TFile(input.c_str(), "READ");
      //cout<<"input: "<<input<<endl;

      // extract sample name
      string sample{input};
      sample.replace(0, sample.find_first_of("_")+1, "");
      sample.replace(sample.find_first_of("_"), sample.find_last_of("t"), "");
      //cout<<"sample: "<<sample<<endl;

      string mass{sample};
      mass.replace(0, mass.find_first_of("M")+1, "");

      // loop over hist
      TIter nextHist(file->GetListOfKeys());
      TKey* histKey(0);
      while ((histKey=(TKey*)nextHist())) {
	if (strcmp(histKey->GetClassName(),"TH1D")!=0) continue;
	TH1D* hmass = (TH1D*)histKey->ReadObj();
	string histname(hmass->GetName());
	// hist name match directory name
	if(histname.find(vdir[i])==std::string::npos) continue; 
	if(histname.find("pT1_")!=std::string::npos) continue; 
	if(histname.find("pT2_")!=std::string::npos) continue; 
	if(histname.find("mVis_")!=std::string::npos) continue; 
	if(histname.find("MET_")!=std::string::npos) continue; 
	if(histname.find("_LOG")!=std::string::npos) continue; 
	if(histname.find("_gen_")!=std::string::npos) continue; 
	if(histname.find("_ratio_")==std::string::npos) continue; 

	hmass->Scale(1./hmass->Integral());
        //hmass->Rebin(5);
        vhmass.push_back((TH1D*)hmass->Clone());
	vhmass.back()->SetLineWidth(2);

	if     (input.find("M50") !=std::string::npos){
		vhmass.back()->SetFillStyle(3001);
	}
	else if(input.find("M125")!=std::string::npos){
		vhmass.back()->SetFillColor(kRed);
		vhmass.back()->SetLineColor(kRed);
		vhmass.back()->SetFillStyle(3001);
	}
	else if(input.find("M200")!=std::string::npos){
		vhmass.back()->SetFillColor(kMagenta);
		vhmass.back()->SetLineColor(kMagenta);
		vhmass.back()->SetFillStyle(3004);
	}
	else if(input.find("M300")!=std::string::npos){
		vhmass.back()->SetFillColor(kBlue);
		vhmass.back()->SetLineColor(kBlue);
		vhmass.back()->SetFillStyle(3005);
	}
	
        // plot vismass
	if( histname.find("_vismass")!=std::string::npos) {
		string header {vdirleg[i]};
		legend1[i]->SetHeader(header.c_str());
		if     (input.find("M50_") !=std::string::npos) legend1[i]->AddEntry( vhmass.back(), "Z#rightarrow#tau#tau", "f");
		else if(input.find("M125_")!=std::string::npos) legend1[i]->AddEntry( vhmass.back(), "H#rightarrow#tau#tau, m_{H} = 125 GeV", "f");
		else if(input.find("M200_")!=std::string::npos) legend1[i]->AddEntry( vhmass.back(), "H#rightarrow#tau#tau, m_{H} = 200 GeV", "f");
		else if(input.find("M300_")!=std::string::npos) legend1[i]->AddEntry( vhmass.back(), "H#rightarrow#tau#tau, m_{H} = 300 GeV", "f");
		if   ( input.find("M50_") !=std::string::npos   || input.find("M125_")  !=std::string::npos ||
		       input.find("M200_")  !=std::string::npos || input.find("M300_")  !=std::string::npos ) {
			canvas[i]->cd(1); vhmass.back()->Draw("same&hist"); 
			legend1[i]->Draw("same");
		}

		if(sample=="DYJetsToLLM50")
			//table1<< "$\\PZ/\\Pggx \\to \\Pgt\\Pgt$ & $"<<vhmass.back()->GetMean()<<"$ & $"<<vhmass.back()->GetRMS()/vhmass.back()->GetMean()<<"$ & $";  
			table1<< "$\\PZ/\\Pggx \\to \\Pgt\\Pgt$ & $"<<Median(vhmass.back())<<"$ & $"<<rounded(vhmass.back()->GetRMS()/Median(vhmass.back()))<<"$ & $";  
		else
			//table1<< "$\\PHiggs \\to \\Pgt\\Pgt$: $\\quad m_{\\PHiggs} ="<< mass<<"$~\\GeV & $"<<vhmass.back()->GetMean()<<"$ & $"<<vhmass.back()->GetRMS()/vhmass.back()->GetMean()<<"$ & $";
			table1<< "$\\PHiggs \\to \\Pgt\\Pgt$: $\\quad m_{\\PHiggs} ="<< mass<<"$~\\GeV & $"<<Median(vhmass.back())<<"$ & $"<<rounded(vhmass.back()->GetRMS()/Median(vhmass.back()))<<"$ & $";

	} 
	// plot svFitMEMmass
	if( vdir[i]=="emu_smeared" && histname.find("_svfitmemtfk3")!=std::string::npos ) {
		string header {vdirleg[i]+"    #kappa = 3"};
		legend2[i]=(TLegend*)legend1[i]->Clone();
		legend2[i]->SetHeader(header.c_str());

		if   ( input.find("M50_") !=std::string::npos   || 
				input.find("M125_")  !=std::string::npos ||
				input.find("M200_")  !=std::string::npos ||
				input.find("M300_")  !=std::string::npos ) {canvas[i]->cd(2); vhmass.back()->Draw("same&hist"); legend2[i]->Draw("same");}

	      //table1<< vhmass.back()->GetMean()<<"$ & $"<<vhmass.back()->GetRMS()/vhmass.back()->GetMean()<<"$ & $ \\\\"<<endl;
	      table1<< Median(vhmass.back())<<"$ & $"<<rounded(vhmass.back()->GetRMS()/Median(vhmass.back()))<<"$ & $ \\\\"<<endl;
	    } 
	    if( vdir[i]=="muhad_smeared" && histname.find("_svfitmemtfk4")!=std::string::npos ) {
	      string header {vdirleg[i]+"    #kappa = 4"};
	      legend3[i]=(TLegend*)legend1[i]->Clone();
	      legend3[i]->SetHeader(header.c_str());

	      if   ( input.find("M50_") !=std::string::npos   || 
	             input.find("M125_")  !=std::string::npos ||
	             input.find("M200_")  !=std::string::npos ||
	             input.find("M300_")  !=std::string::npos ) {canvas[i]->cd(2); vhmass.back()->Draw("same&hist"); legend3[i]->Draw("same");}

	      //table1<< vhmass.back()->GetMean()<<"$ & $"<<vhmass.back()->GetRMS()/vhmass.back()->GetMean()<<"$ & $ \\\\"<<endl;
	      table1<< Median(vhmass.back())<<"$ & $"<<rounded(vhmass.back()->GetRMS()/Median(vhmass.back()))<<"$ & $ \\\\"<<endl;
	    }if( vdir[i]=="hadhad_smeared" && histname.find("_svfitmemtfk5")!=std::string::npos ) {
	      string header {vdirleg[i]+"    #kappa = 5"};
	      legend3[i]=(TLegend*)legend1[i]->Clone();
	      legend3[i]->SetHeader(header.c_str());

	      if   ( input.find("M50_") !=std::string::npos   || 
	             input.find("M125_")  !=std::string::npos ||
	             input.find("M200_")  !=std::string::npos ||
	             input.find("M300_")  !=std::string::npos ) {canvas[i]->cd(2); vhmass.back()->Draw("same&hist"); legend3[i]->Draw("same");}

	      //table1<< vhmass.back()->GetMean()<<"$ & $"<<vhmass.back()->GetRMS()/vhmass.back()->GetMean()<<"$ & $ \\\\"<<endl;
	      table1<< Median(vhmass.back())<<"$ & $"<<rounded(vhmass.back()->GetRMS()/Median(vhmass.back()))<<"$ & $ \\\\"<<endl;
	    } 
      } // while hist
    } // input file

    table1<<"\\hline"<<endl;
    table1<<"\\end{tabular}\n"<<endl;
    table1<<"\\vspace*{0.4 cm}\n"<<endl;

  } // dir

  // close file
  table1.close();

  //save canvas
  for(int i=0; i<ndir; i++){
    if(log) {
      imagepng = savePath+"/plot_13_log_ratio_"+canvas[i]->GetName()+".png";
      imageroot = savePath+"/plot_13_log_ratio_"+canvas[i]->GetName()+".root";
    }
    else {
      imagepng = savePath+"/plot_13_lin_ratio_"+canvas[i]->GetName()+".png";
      imageroot = savePath+"/plot_13_lin_ratio_"+canvas[i]->GetName()+".root";
    }
    canvas[i]->Print(imagepng.c_str()); 
    canvas[i]->Print(imageroot.c_str()); 
  } 

} // void

