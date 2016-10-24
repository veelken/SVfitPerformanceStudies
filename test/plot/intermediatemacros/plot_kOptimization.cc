#include "func.C"
#include <vector>
#include <math.h>
#include "TPaveStats.h"
#include <fstream>
#include <sstream>

double Median(const TH1D * h1);
void plot_kOptimization(){

  // plot histogram
  cout<<"plotting hist...\n";

  string inputPath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_V/"};
  string savePath{"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/"};
  // root file, for optimisation use 1 file!!
  vector<string> vsample {
	  "DYJetsToLLM50"
  };

  vector<string> vinput {
    //"hist_DYJetsToLLM50_inclusive.root"
    "hist_smeared_DYJetsToLLM50_inclusive.root"
  }; 

  func();

  vector<string>vdir{"hadhad" ,"muhad", "emu"};
  vector<string>vdirleg{"#tau_{h}#tau_{h}" ,"#mu#tau_{h}", "e#mu"};

  int ndir{static_cast<int>(vdir.size())};
  int nhist{27}; // 9(logk)*3(dir)

  vector<TH1D*> vh;

  // loop over input files
  for (int in=0; in<vinput.size(); in++){ 
    string input{inputPath+vinput[in]};
    TFile *file = new TFile(input.c_str(), "READ");
    cout<<"input: "<<input<<endl;

    string sample{vsample.at(in)};
    string mass{sample};
    mass.replace(0, mass.find_first_of("M")+1, "");
    cout << mass << endl;


    ////////////////////////////////
    TLegend *legend[ndir];
    for(int i=0; i<ndir; i++){
      legend[i] = new TLegend( 0.67, 0.50, 0.91, 0.85, NULL,"brNDC"); 
      legend[i]->SetTextSize(0.034);
    }
    //
    int ncanvas{0};
    TCanvas *canvas[vinput.size()*ndir];
    for(int i=0; i<vinput.size()*ndir; i++){
      canvas[i] = new TCanvas(to_string(i).c_str(), "", 900, 500); 
      canvas[i]->cd();
      gPad->SetLogy();
      //gPad->SetLogx();
      //gPad->SetLogy();
    }

    TPaveStats *paveStat[nhist];
    int npaveStat{0};
    gStyle->SetOptStat("r");
    TPaveStats *ps[nhist];
    TList *llist[nhist];
    TLatex *mytRmsOverMedian [nhist];
    TLatex *mytMedian [nhist];


    // loop over dir
    for(int i=0; i<ndir; i++){
      cout<<"\ndir: "<<vdir[i]<<endl;

      // loop over the histograms
      TIter nextHist(file->GetListOfKeys());
      TKey* histKey(0);
      int color(1);
      while ((histKey=(TKey*)nextHist())) {
	if (strcmp(histKey->GetClassName(),"TH1D")!=0) continue;
	TH1D* hmass = (TH1D*)histKey->ReadObj();
	string histname(hmass->GetName());
	if(histname.find(vdir[i])==std::string::npos) continue; // hadhad, muhad, emu 
	if(histname.find("_gen")!=std::string::npos) continue;
	if(histname.find("_ratio")!=std::string::npos) continue;
	if(histname.find("_LOG")!=std::string::npos) continue;
	if(histname.find("_svfitmemtfk")==std::string::npos) continue;
        

	vh.push_back((TH1D*)hmass->Clone());
	vh.back()->SetStats(kTRUE);
	vh.back()->SetLineWidth(2);
	//vh.back()->GetXaxis()->SetLimits(50, 9*stoi(mass));
	//vh.back()->GetXaxis()->SetLimits(0, 5*stoi(mass));
	vh.back()->GetYaxis()->SetRangeUser(0.0001, 1);//vh.back()->GetMaximum()*10);
	vh.back()->GetXaxis()->SetTitleOffset(1.);
	vh.back()->GetYaxis()->SetTitleOffset(1.4);
	vh.back()->GetXaxis()->SetTitle("m[GeV]");
	vh.back()->GetYaxis()->SetTitle("1/dm[1/GeV]");

	legend[i]->SetHeader(vdirleg[i].c_str());
	if(histname.find("_smeared_svfitmemtfk0_LIN")!=std::string::npos){vh.back()->SetLineColor(kBlack); legend[i]->AddEntry(vh.back(), "sme_tf_k0", "l");}
	if(histname.find("_smeared_svfitmemtfk1_LIN")!=std::string::npos){vh.back()->SetLineColor(kBlue);  legend[i]->AddEntry(vh.back(), "sme_tf_k1", "l");}
	if(histname.find("_smeared_svfitmemtfk2_LIN")!=std::string::npos){vh.back()->SetLineColor(kGreen); legend[i]->AddEntry(vh.back(), "sme_tf_k2", "l");}
	if(histname.find("_smeared_svfitmemtfk3_LIN")!=std::string::npos){vh.back()->SetLineColor(kOrange);legend[i]->AddEntry(vh.back(), "sme_tf_k3", "l");}
	if(histname.find("_smeared_svfitmemtfk4_LIN")!=std::string::npos){vh.back()->SetLineColor(kRed+2); legend[i]->AddEntry(vh.back(), "sme_tf_k4", "l");}
	if(histname.find("_smeared_svfitmemtfk5_LIN")!=std::string::npos){vh.back()->SetLineColor(kCyan);  legend[i]->AddEntry(vh.back(), "sme_tf_k5", "l");}
	if(histname.find("_smeared_svfitmemtfk6_LIN")!=std::string::npos){vh.back()->SetLineColor(kGray);  legend[i]->AddEntry(vh.back(), "sme_tf_k6", "l");}
	if(histname.find("_smeared_svfitmemtfk7_LIN")!=std::string::npos){vh.back()->SetLineColor(kViolet);legend[i]->AddEntry(vh.back(), "sme_tf_k7", "l");}
	if(histname.find("_smeared_svfitmemtfk8_LIN")!=std::string::npos){vh.back()->SetLineColor(kRed);   legend[i]->AddEntry(vh.back(), "sme_tf_k8", "l");}

	// canvas array [for each sample]
	string canvasName {sample+"_"+vdir[i]};
	canvas[ncanvas]->SetName(canvasName.c_str());
	canvas[ncanvas]->SetTitle(canvasName.c_str());
	//if (histname.find("_LIN_")!=std::string::npos){
	canvas[ncanvas]->cd();
	string kvalue{vh.back()->GetName()};
	kvalue.replace(0, kvalue.find_first_of("r")+3,"");
	kvalue.replace(0, kvalue.find_first_of("N")-5,"");
	kvalue.replace(2, kvalue.find_first_of("_")+3,"");
        
        cout << kvalue << ": " << AlternativeMedian(vh.back()) << " - " << vh.back()->GetRMS()/AlternativeMedian(vh.back()) << endl;

        if(stoi(mass)==500) vh.back()->Rebin(19);
        else vh.back()->Rebin(10);
	vh.back()->Draw("hist&sames");
	//gPad->Modified(); gPad->Update(); // make sure it's really (re)drawn

        //canvas[ncanvas]->cd(2);
	//paveStat[npaveStat]=(TPaveStats*)vh.back()->FindObject("stats");
	//paveStat[npaveStat]->SetName("mystats"); // you MUST rename "stats"
	//paveStat[npaveStat]->SetName(TString::Format("mystats_%d", npaveStat)); // you MUST rename "stats"
	//paveStat[npaveStat]->Draw("same"); // why does one need to draw it manually?
	vh.back()->SetStats(0);

	//paveStat[npaveStat]->SetLineColor(vh.back()->GetLineColor());
	//paveStat[npaveStat]->SetLineStyle(vh.back()->GetLineStyle());
	//paveStat[npaveStat]->SetLineWidth(vh.back()->GetLineWidth());
	//paveStat[npaveStat]->SetTextSize(0.025);
	//paveStat[npaveStat]->SetY1NDC(0.89); // Y1=lower bound
	//paveStat[npaveStat]->SetX1NDC(0.75); // X1=lower bound

	/*if(npaveStat!=0 && npaveStat!=9 && npaveStat!=18 ){ 
		double delta{paveStat[npaveStat-1]->GetY2NDC()-paveStat[npaveStat-1]->GetY1NDC()};
		paveStat[npaveStat]->SetY2NDC(paveStat[npaveStat-1]->GetY1NDC());
		paveStat[npaveStat]->SetY1NDC(paveStat[npaveStat-1]->GetY1NDC()-delta);
	}*/

	// Add a new line in the stat box.
	//llist[npaveStat] = paveStat[npaveStat]->GetListOfLines();

	/* ssMedian << std::fixed << std::setprecision(3) << Median(vh.back());
	string median{"median: =" + ssMedian.str()};
	mytMedian[npaveStat] = new TLatex(0, 0, median.c_str()); 
	mytMedian[npaveStat] ->SetTextFont(paveStat[npaveStat]->GetTextFont());
	mytMedian[npaveStat] ->SetTextSize(0.025);
	llist[npaveStat]->Add(mytMedian[npaveStat]);
	//
	cout << "computing rms/med"<< endl;
	ssRmsOverMedian << std::fixed << std::setprecision(3) << vh.back()->GetRMS()/Median(vh.back());
	string rmsOverMedian{"rms/med: =" + ssRmsOverMedian.str()};
	mytRmsOverMedian[npaveStat] = new TLatex(0, 0, rmsOverMedian.c_str()); 
	mytRmsOverMedian[npaveStat] ->SetTextFont(paveStat[npaveStat]->GetTextFont());
	mytRmsOverMedian[npaveStat] ->SetTextSize(0.025);
	llist[npaveStat]->Add(mytRmsOverMedian[npaveStat]);
	*/ // 
	npaveStat++;
	gPad->Modified(); 
        gPad->Update();
	//}
	//else { 
	//  canvas[ncanvas]->cd(2); vh.back()->Draw("hist&sames"); vh.back()->SetStats(0); legend[i]->Draw("sames");
	//}
	legend[i]->Draw("same");
      } // hist

      string image {savePath+"plot_svfitmem_"+sample+"_"+vdir[i]+".png"};
      string imageroot {savePath+"plot_svfitmem_"+sample+"_"+vdir[i]+".root"};
      canvas[ncanvas]->Print(image.c_str()); 
      canvas[ncanvas]->Print(imageroot.c_str()); 

      //if(stoi(mass)!=500) vh.back()->Rebin(10);
      //else vh.back()->Rebin(50);
      ncanvas++;

    } // dir
  } // sample
} // void
