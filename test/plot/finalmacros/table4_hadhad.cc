#include "func.C"
#include <fstream>
#include <vector>
#include <math.h>

double AlternativeMedian(const TH1D * h1);
double rounded(double val);
double ComputeStatisticalError(int bin1, int bin2, TH1D* hSig, TH1D* hBkg){//, double xsSig, double xsBkg, double ceSig, double ceBkg){

        //cout << " into the function " << hBkg->GetName() << endl;
        double nBkg = hBkg->Integral(bin1,bin2);
        double nSig = hSig->Integral(bin1,bin2);
        //cout << " nBkg " << nBkg << endl;
        //cout << " nSig " << nSig << endl;
        double poissonBkg = 1;
        double poissonSig = 1;
        if(nBkg!=0) poissonBkg = TMath::Sqrt(nBkg/hBkg->GetEntries());
        if(nSig!=0) poissonSig = TMath::Sqrt(nSig/hSig->GetEntries());
        //cout << " poissonBkg " << poissonBkg << endl;
        //cout << " poissonSig " << poissonSig << endl;
        double term1 = TMath::Power(nBkg*poissonSig,2); // (B*sigma_S)2 
        double term2 = TMath::Power(nSig*poissonBkg,2); // (S*sigma_B)2
        //cout << "(nSig*xsSig*ceSig) " << (nSig*xsSig*ceSig) << " (xsBkg*ceBkg) " << (xsBkg*ceBkg) << endl;
        double term3 = TMath::Power(nSig+nBkg,4);    // (S+B)2
        double finalError = TMath::Sqrt((term1+term2)/term3);
        //cout << "xsBkg "<< xsBkg << " ceBkg " << ceBkg << " xsSig "<< xsSig << " ceSig " << ceSig << endl;
        //cout << " term1 " << term1 << " term2 " << term2 << " term3 " << term3 << endl;
        //cout << " final error " << finalError << endl;
        return finalError;
}


void table4_hadhad(){

  // plot histogram
  cout<<"plotting hist...\n";

  string inputPath {"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_III"};
  string savePath {"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot"};

  // root file
    vector<string> vinput {
          "hist_smeared_SUSYGluGluToHToTauTauM200_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM300_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM500_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM800_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM1200_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM1800_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM2600_inclusive.root"
          //"hist_smeared_ZprimeToTauTauM2500_inclusive.root"
  };

  vector<string>vsample{
          "SUSYGluGluToHToTauTauM200",
          "SUSYGluGluToHToTauTauM300",
          "SUSYGluGluToHToTauTauM500",
          "SUSYGluGluToHToTauTauM800",
          "SUSYGluGluToHToTauTauM1200",
          "SUSYGluGluToHToTauTauM1800",
          "SUSYGluGluToHToTauTauM2600"
          //"ZprimeToTauTauM2500"
  };


  func();

  bool log{0};

  TFile *file_bkg = new TFile((inputPath+"/hist_smeared_ZprimeToTauTauM2500_inclusive.root").c_str(), "READ");
  TH1D * bh_mvis       = (TH1D*)file_bkg->Get("hadhad_smeared_vismass_fine_bin");
  TH1D * bh_SVfitSA    = (TH1D*)file_bkg->Get("hadhad_smeared_svFit_fine_bin");
  TH1D * bh_SVfitMEMk0 = (TH1D*)file_bkg->Get("hadhad_smeared_svfitmemtfk0_fine_bin");
  TH1D * bh_SVfitMEMk  = (TH1D*)file_bkg->Get("hadhad_smeared_svfitmemtfk5_fine_bin");
  TH1D * bh_SVfitCLAk0 = (TH1D*)file_bkg->Get("hadhad_smeared_svfitclatfk0_fine_bin");
  TH1D * bh_SVfitCLAk  = (TH1D*)file_bkg->Get("hadhad_smeared_svfitclatfk5_fine_bin");
  vector<TH1D*> vh_mvis;
  vector<TH1D*> vh_SVfitSA;
  vector<TH1D*> vh_SVfitMEMk0;
  vector<TH1D*> vh_SVfitMEMk;
  vector<TH1D*> vh_SVfitCLAk0;
  vector<TH1D*> vh_SVfitCLAk;
    
  // loop over input files
  for (int in=0; in<vinput.size(); in++){ 
	  string input{inputPath+"/"+vinput[in]};
	  TFile *file = new TFile(input.c_str(), "READ");

	  string sample{input};
	  sample.replace(0, sample.find_first_of("_")+1, "");
	  sample.replace(sample.find_first_of("_"), sample.find_last_of("t"), "");

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
		  if(histname.find("hadhad")==std::string::npos) continue; 
		  if(histname.find("smeared_vismass_fine_bin")!=std::string::npos)         vh_mvis.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svFit_fine_bin")!=std::string::npos)           vh_SVfitSA.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svfitmemtfk0_fine_bin")!=std::string::npos)    vh_SVfitMEMk0.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svfitclatfk0_fine_bin")!=std::string::npos)    vh_SVfitCLAk0.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svfitmemtfk5_fine_bin")!=std::string::npos)    vh_SVfitMEMk.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svfitclatfk5_fine_bin")!=std::string::npos)    vh_SVfitCLAk.push_back((TH1D*)hmass->Clone());
	  }
  }
  
  int binxmin_mvis_M200     = vh_mvis.at(0)->FindBin(Quantile68(vh_mvis.at(0))[0]); int binxmax_mvis_M200 = vh_mvis.at(0)->FindBin(Quantile68(vh_mvis.at(0))[1]);
  int binxmin_mvis_M300     = vh_mvis.at(1)->FindBin(Quantile68(vh_mvis.at(1))[0]); int binxmax_mvis_M300 = vh_mvis.at(1)->FindBin(Quantile68(vh_mvis.at(1))[1]);
  int binxmin_mvis_M500     = vh_mvis.at(2)->FindBin(Quantile68(vh_mvis.at(2))[0]); int binxmax_mvis_M500 = vh_mvis.at(2)->FindBin(Quantile68(vh_mvis.at(2))[1]);
  int binxmin_mvis_M800     = vh_mvis.at(3)->FindBin(Quantile68(vh_mvis.at(3))[0]); int binxmax_mvis_M800 = vh_mvis.at(3)->FindBin(Quantile68(vh_mvis.at(3))[1]);
  int binxmin_mvis_M1200    = vh_mvis.at(4)->FindBin(Quantile68(vh_mvis.at(4))[0]); int binxmax_mvis_M1200 = vh_mvis.at(4)->FindBin(Quantile68(vh_mvis.at(4))[1]);
  int binxmin_mvis_M1800    = vh_mvis.at(5)->FindBin(Quantile68(vh_mvis.at(5))[0]); int binxmax_mvis_M1800 = vh_mvis.at(5)->FindBin(Quantile68(vh_mvis.at(5))[1]);
  int binxmin_mvis_M2600    = vh_mvis.at(6)->FindBin(Quantile68(vh_mvis.at(6))[0]); int binxmax_mvis_M2600 = vh_mvis.at(6)->FindBin(Quantile68(vh_mvis.at(6))[1]);
  int binxmin_SVfitSA_M200  = vh_SVfitSA.at(0)->FindBin(Quantile68(vh_SVfitSA.at(0))[0]); int binxmax_SVfitSA_M200 = vh_SVfitSA.at(0)->FindBin(Quantile68(vh_SVfitSA.at(0))[1]);
  int binxmin_SVfitSA_M300  = vh_SVfitSA.at(1)->FindBin(Quantile68(vh_SVfitSA.at(1))[0]); int binxmax_SVfitSA_M300 = vh_SVfitSA.at(1)->FindBin(Quantile68(vh_SVfitSA.at(1))[1]);
  int binxmin_SVfitSA_M500  = vh_SVfitSA.at(2)->FindBin(Quantile68(vh_SVfitSA.at(2))[0]); int binxmax_SVfitSA_M500 = vh_SVfitSA.at(2)->FindBin(Quantile68(vh_SVfitSA.at(2))[1]);
  int binxmin_SVfitSA_M800  = vh_SVfitSA.at(3)->FindBin(Quantile68(vh_SVfitSA.at(3))[0]); int binxmax_SVfitSA_M800 = vh_SVfitSA.at(3)->FindBin(Quantile68(vh_SVfitSA.at(3))[1]);
  int binxmin_SVfitSA_M1200 = vh_SVfitSA.at(4)->FindBin(Quantile68(vh_SVfitSA.at(4))[0]); int binxmax_SVfitSA_M1200 = vh_SVfitSA.at(4)->FindBin(Quantile68(vh_SVfitSA.at(4))[1]);
  int binxmin_SVfitSA_M1800 = vh_SVfitSA.at(5)->FindBin(Quantile68(vh_SVfitSA.at(5))[0]); int binxmax_SVfitSA_M1800 = vh_SVfitSA.at(5)->FindBin(Quantile68(vh_SVfitSA.at(5))[1]);
  int binxmin_SVfitSA_M2600 = vh_SVfitSA.at(6)->FindBin(Quantile68(vh_SVfitSA.at(6))[0]); int binxmax_SVfitSA_M2600 = vh_SVfitSA.at(6)->FindBin(Quantile68(vh_SVfitSA.at(6))[1]);

  double bkg_mvis_M200        = bh_mvis->Integral(binxmin_mvis_M200,binxmax_mvis_M200);   
  double bkg_mvis_M300        = bh_mvis->Integral(binxmin_mvis_M300,binxmax_mvis_M300);   
  double bkg_mvis_M500        = bh_mvis->Integral(binxmin_mvis_M500,binxmax_mvis_M500);   
  double bkg_mvis_M800        = bh_mvis->Integral(binxmin_mvis_M800,binxmax_mvis_M800);   
  double bkg_mvis_M1200       = bh_mvis->Integral(binxmin_mvis_M1200,binxmax_mvis_M1200);   
  double bkg_mvis_M1800       = bh_mvis->Integral(binxmin_mvis_M1800,binxmax_mvis_M1800);   
  double bkg_mvis_M2600       = bh_mvis->Integral(binxmin_mvis_M2600,binxmax_mvis_M2600);   
  double bkg_SVfitSA_M200     = bh_SVfitSA->Integral(binxmin_SVfitSA_M200,binxmax_SVfitSA_M200);   
  double bkg_SVfitSA_M300     = bh_SVfitSA->Integral(binxmin_SVfitSA_M300,binxmax_SVfitSA_M300);   
  double bkg_SVfitSA_M500     = bh_SVfitSA->Integral(binxmin_SVfitSA_M500,binxmax_SVfitSA_M500);   
  double bkg_SVfitSA_M800     = bh_SVfitSA->Integral(binxmin_SVfitSA_M800,binxmax_SVfitSA_M800);   
  double bkg_SVfitSA_M1200    = bh_SVfitSA->Integral(binxmin_SVfitSA_M1200,binxmax_SVfitSA_M1200);   
  double bkg_SVfitSA_M1800    = bh_SVfitSA->Integral(binxmin_SVfitSA_M1800,binxmax_SVfitSA_M1800);   
  double bkg_SVfitSA_M2600    = bh_SVfitSA->Integral(binxmin_SVfitSA_M2600,binxmax_SVfitSA_M2600);   
  double signal_mvis_M200     = vh_mvis[0]->Integral(binxmin_mvis_M200,binxmax_mvis_M200);   
  double signal_mvis_M300     = vh_mvis[1]->Integral(binxmin_mvis_M300,binxmax_mvis_M300);   
  double signal_mvis_M500     = vh_mvis[2]->Integral(binxmin_mvis_M500,binxmax_mvis_M500);   
  double signal_mvis_M800     = vh_mvis[3]->Integral(binxmin_mvis_M800,binxmax_mvis_M800);   
  double signal_mvis_M1200    = vh_mvis[4]->Integral(binxmin_mvis_M1200,binxmax_mvis_M1200);   
  double signal_mvis_M1800    = vh_mvis[5]->Integral(binxmin_mvis_M1800,binxmax_mvis_M1800);   
  double signal_mvis_M2600    = vh_mvis[6]->Integral(binxmin_mvis_M2600,binxmax_mvis_M2600);   
  double signal_SVfitSA_M200  = vh_SVfitSA[0]->Integral(binxmin_SVfitSA_M200,binxmax_SVfitSA_M200);   
  double signal_SVfitSA_M300  = vh_SVfitSA[1]->Integral(binxmin_SVfitSA_M300,binxmax_SVfitSA_M300);   
  double signal_SVfitSA_M500  = vh_SVfitSA[2]->Integral(binxmin_SVfitSA_M500,binxmax_SVfitSA_M500);   
  double signal_SVfitSA_M800  = vh_SVfitSA[3]->Integral(binxmin_SVfitSA_M800,binxmax_SVfitSA_M800);   
  double signal_SVfitSA_M1200 = vh_SVfitSA[4]->Integral(binxmin_SVfitSA_M1200,binxmax_SVfitSA_M1200);   
  double signal_SVfitSA_M1800 = vh_SVfitSA[5]->Integral(binxmin_SVfitSA_M1800,binxmax_SVfitSA_M1800);   
  double signal_SVfitSA_M2600 = vh_SVfitSA[6]->Integral(binxmin_SVfitSA_M2600,binxmax_SVfitSA_M2600);   

  double ratio_mvis_M200       = signal_mvis_M200 / (signal_mvis_M200 + bkg_mvis_M200);
  double ratio_mvis_M300       = signal_mvis_M300 / (signal_mvis_M300 + bkg_mvis_M300);
  double ratio_mvis_M500       = signal_mvis_M500 / (signal_mvis_M500 + bkg_mvis_M500);
  double ratio_mvis_M800       = signal_mvis_M800 / (signal_mvis_M800 + bkg_mvis_M800);
  double ratio_mvis_M1200      = signal_mvis_M1200 / (signal_mvis_M1200 + bkg_mvis_M1200);
  double ratio_mvis_M1800      = signal_mvis_M1800 / (signal_mvis_M1800 + bkg_mvis_M1800);
  double ratio_mvis_M2600      = signal_mvis_M2600 / (signal_mvis_M2600 + bkg_mvis_M2600);
  double ratio_SVfitSA_M200    = signal_SVfitSA_M200 / (signal_SVfitSA_M200 + bkg_SVfitSA_M200);
  double ratio_SVfitSA_M300    = signal_SVfitSA_M300 / (signal_SVfitSA_M300 + bkg_SVfitSA_M300);
  double ratio_SVfitSA_M500    = signal_SVfitSA_M500 / (signal_SVfitSA_M500 + bkg_SVfitSA_M500);
  double ratio_SVfitSA_M800    = signal_SVfitSA_M800 / (signal_SVfitSA_M800 + bkg_SVfitSA_M800);
  double ratio_SVfitSA_M1200   = signal_SVfitSA_M1200 / (signal_SVfitSA_M1200 + bkg_SVfitSA_M1200);
  double ratio_SVfitSA_M1800   = signal_SVfitSA_M1800 / (signal_SVfitSA_M1800 + bkg_SVfitSA_M1800);
  double ratio_SVfitSA_M2600   = signal_SVfitSA_M2600 / (signal_SVfitSA_M2600 + bkg_SVfitSA_M2600);
  double err_ratio_mvis_M200   = ComputeStatisticalError(binxmin_mvis_M200,binxmax_mvis_M200,vh_mvis[0],bh_mvis);
  double err_ratio_mvis_M300   = ComputeStatisticalError(binxmin_mvis_M300,binxmax_mvis_M300,vh_mvis[1],bh_mvis);
  double err_ratio_mvis_M500   = ComputeStatisticalError(binxmin_mvis_M500,binxmax_mvis_M500,vh_mvis[2],bh_mvis);
  double err_ratio_mvis_M800   = ComputeStatisticalError(binxmin_mvis_M800,binxmax_mvis_M800,vh_mvis[3],bh_mvis);
  double err_ratio_mvis_M1200  = ComputeStatisticalError(binxmin_mvis_M1200,binxmax_mvis_M1200,vh_mvis[4],bh_mvis);
  double err_ratio_mvis_M1800  = ComputeStatisticalError(binxmin_mvis_M1800,binxmax_mvis_M1800,vh_mvis[5],bh_mvis);
  double err_ratio_mvis_M2600     = ComputeStatisticalError(binxmin_mvis_M2600,binxmax_mvis_M2600,vh_mvis[6],bh_mvis);
  double err_ratio_SVfitSA_M200   = ComputeStatisticalError(binxmin_SVfitSA_M200,binxmax_SVfitSA_M200,vh_SVfitSA[0],bh_SVfitSA);
  double err_ratio_SVfitSA_M300   = ComputeStatisticalError(binxmin_SVfitSA_M300,binxmax_SVfitSA_M300,vh_SVfitSA[1],bh_SVfitSA);
  double err_ratio_SVfitSA_M500   = ComputeStatisticalError(binxmin_SVfitSA_M500,binxmax_SVfitSA_M500,vh_SVfitSA[2],bh_SVfitSA);
  double err_ratio_SVfitSA_M800   = ComputeStatisticalError(binxmin_SVfitSA_M800,binxmax_SVfitSA_M800,vh_SVfitSA[3],bh_SVfitSA);
  double err_ratio_SVfitSA_M1200  = ComputeStatisticalError(binxmin_SVfitSA_M1200,binxmax_SVfitSA_M1200,vh_SVfitSA[4],bh_SVfitSA);
  double err_ratio_SVfitSA_M1800  = ComputeStatisticalError(binxmin_SVfitSA_M1800,binxmax_SVfitSA_M1800,vh_SVfitSA[5],bh_SVfitSA);
  double err_ratio_SVfitSA_M2600  = ComputeStatisticalError(binxmin_SVfitSA_M2600,binxmax_SVfitSA_M2600,vh_SVfitSA[6],bh_SVfitSA);
  
  int binxmin_SVfitCLAk0_M200     = vh_SVfitCLAk0.at(0)->FindBin(Quantile68(vh_SVfitCLAk0.at(0))[0]); int binxmax_SVfitCLAk0_M200 = vh_SVfitCLAk0.at(0)->FindBin(Quantile68(vh_SVfitCLAk0.at(0))[1]);
  int binxmin_SVfitCLAk0_M300     = vh_SVfitCLAk0.at(1)->FindBin(Quantile68(vh_SVfitCLAk0.at(1))[0]); int binxmax_SVfitCLAk0_M300 = vh_SVfitCLAk0.at(1)->FindBin(Quantile68(vh_SVfitCLAk0.at(1))[1]);
  int binxmin_SVfitCLAk0_M500     = vh_SVfitCLAk0.at(2)->FindBin(Quantile68(vh_SVfitCLAk0.at(2))[0]); int binxmax_SVfitCLAk0_M500 = vh_SVfitCLAk0.at(2)->FindBin(Quantile68(vh_SVfitCLAk0.at(2))[1]);
  int binxmin_SVfitCLAk0_M800     = vh_SVfitCLAk0.at(3)->FindBin(Quantile68(vh_SVfitCLAk0.at(3))[0]); int binxmax_SVfitCLAk0_M800 = vh_SVfitCLAk0.at(3)->FindBin(Quantile68(vh_SVfitCLAk0.at(3))[1]);
  int binxmin_SVfitCLAk0_M1200    = vh_SVfitCLAk0.at(4)->FindBin(Quantile68(vh_SVfitCLAk0.at(4))[0]); int binxmax_SVfitCLAk0_M1200 = vh_SVfitCLAk0.at(4)->FindBin(Quantile68(vh_SVfitCLAk0.at(4))[1]);
  int binxmin_SVfitCLAk0_M1800    = vh_SVfitCLAk0.at(5)->FindBin(Quantile68(vh_SVfitCLAk0.at(5))[0]); int binxmax_SVfitCLAk0_M1800 = vh_SVfitCLAk0.at(5)->FindBin(Quantile68(vh_SVfitCLAk0.at(5))[1]);
  int binxmin_SVfitCLAk0_M2600    = vh_SVfitCLAk0.at(6)->FindBin(Quantile68(vh_SVfitCLAk0.at(6))[0]); int binxmax_SVfitCLAk0_M2600 = vh_SVfitCLAk0.at(6)->FindBin(Quantile68(vh_SVfitCLAk0.at(6))[1]);
  int binxmin_SVfitCLAk_M200  = vh_SVfitCLAk.at(0)->FindBin(Quantile68(vh_SVfitCLAk.at(0))[0]); int binxmax_SVfitCLAk_M200 = vh_SVfitCLAk.at(0)->FindBin(Quantile68(vh_SVfitCLAk.at(0))[1]);
  int binxmin_SVfitCLAk_M300  = vh_SVfitCLAk.at(1)->FindBin(Quantile68(vh_SVfitCLAk.at(1))[0]); int binxmax_SVfitCLAk_M300 = vh_SVfitCLAk.at(1)->FindBin(Quantile68(vh_SVfitCLAk.at(1))[1]);
  int binxmin_SVfitCLAk_M500  = vh_SVfitCLAk.at(2)->FindBin(Quantile68(vh_SVfitCLAk.at(2))[0]); int binxmax_SVfitCLAk_M500 = vh_SVfitCLAk.at(2)->FindBin(Quantile68(vh_SVfitCLAk.at(2))[1]);
  int binxmin_SVfitCLAk_M800  = vh_SVfitCLAk.at(3)->FindBin(Quantile68(vh_SVfitCLAk.at(3))[0]); int binxmax_SVfitCLAk_M800 = vh_SVfitCLAk.at(3)->FindBin(Quantile68(vh_SVfitCLAk.at(3))[1]);
  int binxmin_SVfitCLAk_M1200 = vh_SVfitCLAk.at(4)->FindBin(Quantile68(vh_SVfitCLAk.at(4))[0]); int binxmax_SVfitCLAk_M1200 = vh_SVfitCLAk.at(4)->FindBin(Quantile68(vh_SVfitCLAk.at(4))[1]);
  int binxmin_SVfitCLAk_M1800 = vh_SVfitCLAk.at(5)->FindBin(Quantile68(vh_SVfitCLAk.at(5))[0]); int binxmax_SVfitCLAk_M1800 = vh_SVfitCLAk.at(5)->FindBin(Quantile68(vh_SVfitCLAk.at(5))[1]);
  int binxmin_SVfitCLAk_M2600 = vh_SVfitCLAk.at(6)->FindBin(Quantile68(vh_SVfitCLAk.at(6))[0]); int binxmax_SVfitCLAk_M2600 = vh_SVfitCLAk.at(6)->FindBin(Quantile68(vh_SVfitCLAk.at(6))[1]);

  double bkg_SVfitCLAk0_M200        = bh_SVfitCLAk0->Integral(binxmin_SVfitCLAk0_M200,binxmax_SVfitCLAk0_M200);   
  double bkg_SVfitCLAk0_M300        = bh_SVfitCLAk0->Integral(binxmin_SVfitCLAk0_M300,binxmax_SVfitCLAk0_M300);   
  double bkg_SVfitCLAk0_M500        = bh_SVfitCLAk0->Integral(binxmin_SVfitCLAk0_M500,binxmax_SVfitCLAk0_M500);   
  double bkg_SVfitCLAk0_M800        = bh_SVfitCLAk0->Integral(binxmin_SVfitCLAk0_M800,binxmax_SVfitCLAk0_M800);   
  double bkg_SVfitCLAk0_M1200       = bh_SVfitCLAk0->Integral(binxmin_SVfitCLAk0_M1200,binxmax_SVfitCLAk0_M1200);   
  double bkg_SVfitCLAk0_M1800       = bh_SVfitCLAk0->Integral(binxmin_SVfitCLAk0_M1800,binxmax_SVfitCLAk0_M1800);   
  double bkg_SVfitCLAk0_M2600       = bh_SVfitCLAk0->Integral(binxmin_SVfitCLAk0_M2600,binxmax_SVfitCLAk0_M2600);   
  double bkg_SVfitCLAk_M200         = bh_SVfitCLAk->Integral(binxmin_SVfitCLAk_M200,binxmax_SVfitCLAk_M200);   
  double bkg_SVfitCLAk_M300         = bh_SVfitCLAk->Integral(binxmin_SVfitCLAk_M300,binxmax_SVfitCLAk_M300);   
  double bkg_SVfitCLAk_M500         = bh_SVfitCLAk->Integral(binxmin_SVfitCLAk_M500,binxmax_SVfitCLAk_M500);   
  double bkg_SVfitCLAk_M800         = bh_SVfitCLAk->Integral(binxmin_SVfitCLAk_M800,binxmax_SVfitCLAk_M800);   
  double bkg_SVfitCLAk_M1200        = bh_SVfitCLAk->Integral(binxmin_SVfitCLAk_M1200,binxmax_SVfitCLAk_M1200);   
  double bkg_SVfitCLAk_M1800        = bh_SVfitCLAk->Integral(binxmin_SVfitCLAk_M1800,binxmax_SVfitCLAk_M1800);   
  double bkg_SVfitCLAk_M2600        = bh_SVfitCLAk->Integral(binxmin_SVfitCLAk_M2600,binxmax_SVfitCLAk_M2600);   
  double signal_SVfitCLAk0_M200     = vh_SVfitCLAk0[0]->Integral(binxmin_SVfitCLAk0_M200,binxmax_SVfitCLAk0_M200);   
  double signal_SVfitCLAk0_M300     = vh_SVfitCLAk0[1]->Integral(binxmin_SVfitCLAk0_M300,binxmax_SVfitCLAk0_M300);   
  double signal_SVfitCLAk0_M500     = vh_SVfitCLAk0[2]->Integral(binxmin_SVfitCLAk0_M500,binxmax_SVfitCLAk0_M500);   
  double signal_SVfitCLAk0_M800     = vh_SVfitCLAk0[3]->Integral(binxmin_SVfitCLAk0_M800,binxmax_SVfitCLAk0_M800);   
  double signal_SVfitCLAk0_M1200    = vh_SVfitCLAk0[4]->Integral(binxmin_SVfitCLAk0_M1200,binxmax_SVfitCLAk0_M1200);   
  double signal_SVfitCLAk0_M1800    = vh_SVfitCLAk0[5]->Integral(binxmin_SVfitCLAk0_M1800,binxmax_SVfitCLAk0_M1800);   
  double signal_SVfitCLAk0_M2600    = vh_SVfitCLAk0[6]->Integral(binxmin_SVfitCLAk0_M2600,binxmax_SVfitCLAk0_M2600);   
  double signal_SVfitCLAk_M200      = vh_SVfitCLAk[0]->Integral(binxmin_SVfitCLAk_M200,binxmax_SVfitCLAk_M200);   
  double signal_SVfitCLAk_M300      = vh_SVfitCLAk[1]->Integral(binxmin_SVfitCLAk_M300,binxmax_SVfitCLAk_M300);   
  double signal_SVfitCLAk_M500      = vh_SVfitCLAk[2]->Integral(binxmin_SVfitCLAk_M500,binxmax_SVfitCLAk_M500);   
  double signal_SVfitCLAk_M800      = vh_SVfitCLAk[3]->Integral(binxmin_SVfitCLAk_M800,binxmax_SVfitCLAk_M800);   
  double signal_SVfitCLAk_M1200     = vh_SVfitCLAk[4]->Integral(binxmin_SVfitCLAk_M1200,binxmax_SVfitCLAk_M1200);   
  double signal_SVfitCLAk_M1800     = vh_SVfitCLAk[5]->Integral(binxmin_SVfitCLAk_M1800,binxmax_SVfitCLAk_M1800);   
  double signal_SVfitCLAk_M2600     = vh_SVfitCLAk[6]->Integral(binxmin_SVfitCLAk_M2600,binxmax_SVfitCLAk_M2600);   

  double ratio_SVfitCLAk0_M200      = signal_SVfitCLAk0_M200 / (signal_SVfitCLAk0_M200 + bkg_SVfitCLAk0_M200);
  double ratio_SVfitCLAk0_M300      = signal_SVfitCLAk0_M300 / (signal_SVfitCLAk0_M300 + bkg_SVfitCLAk0_M300);
  double ratio_SVfitCLAk0_M500      = signal_SVfitCLAk0_M500 / (signal_SVfitCLAk0_M500 + bkg_SVfitCLAk0_M500);
  double ratio_SVfitCLAk0_M800      = signal_SVfitCLAk0_M800 / (signal_SVfitCLAk0_M800 + bkg_SVfitCLAk0_M800);
  double ratio_SVfitCLAk0_M1200     = signal_SVfitCLAk0_M1200 / (signal_SVfitCLAk0_M1200 + bkg_SVfitCLAk0_M1200);
  double ratio_SVfitCLAk0_M1800     = signal_SVfitCLAk0_M1800 / (signal_SVfitCLAk0_M1800 + bkg_SVfitCLAk0_M1800);
  double ratio_SVfitCLAk0_M2600     = signal_SVfitCLAk0_M2600 / (signal_SVfitCLAk0_M2600 + bkg_SVfitCLAk0_M2600);
  double ratio_SVfitCLAk_M200       = signal_SVfitCLAk_M200 / (signal_SVfitCLAk_M200 + bkg_SVfitCLAk_M200);
  double ratio_SVfitCLAk_M300       = signal_SVfitCLAk_M300 / (signal_SVfitCLAk_M300 + bkg_SVfitCLAk_M300);
  double ratio_SVfitCLAk_M500       = signal_SVfitCLAk_M500 / (signal_SVfitCLAk_M500 + bkg_SVfitCLAk_M500);
  double ratio_SVfitCLAk_M800       = signal_SVfitCLAk_M800 / (signal_SVfitCLAk_M800 + bkg_SVfitCLAk_M800);
  double ratio_SVfitCLAk_M1200      = signal_SVfitCLAk_M1200 / (signal_SVfitCLAk_M1200 + bkg_SVfitCLAk_M1200);
  double ratio_SVfitCLAk_M1800      = signal_SVfitCLAk_M1800 / (signal_SVfitCLAk_M1800 + bkg_SVfitCLAk_M1800);
  double ratio_SVfitCLAk_M2600      = signal_SVfitCLAk_M2600 / (signal_SVfitCLAk_M2600 + bkg_SVfitCLAk_M2600);
  double err_ratio_SVfitCLAk0_M200   = ComputeStatisticalError(binxmin_SVfitCLAk0_M200,binxmax_SVfitCLAk0_M200,vh_SVfitCLAk0[0],bh_SVfitCLAk0);
  double err_ratio_SVfitCLAk0_M300   = ComputeStatisticalError(binxmin_SVfitCLAk0_M300,binxmax_SVfitCLAk0_M300,vh_SVfitCLAk0[1],bh_SVfitCLAk0);
  double err_ratio_SVfitCLAk0_M500   = ComputeStatisticalError(binxmin_SVfitCLAk0_M500,binxmax_SVfitCLAk0_M500,vh_SVfitCLAk0[2],bh_SVfitCLAk0);
  double err_ratio_SVfitCLAk0_M800   = ComputeStatisticalError(binxmin_SVfitCLAk0_M800,binxmax_SVfitCLAk0_M800,vh_SVfitCLAk0[3],bh_SVfitCLAk0);
  double err_ratio_SVfitCLAk0_M1200  = ComputeStatisticalError(binxmin_SVfitCLAk0_M1200,binxmax_SVfitCLAk0_M1200,vh_SVfitCLAk0[4],bh_SVfitCLAk0);
  double err_ratio_SVfitCLAk0_M1800  = ComputeStatisticalError(binxmin_SVfitCLAk0_M1800,binxmax_SVfitCLAk0_M1800,vh_SVfitCLAk0[5],bh_SVfitCLAk0);
  double err_ratio_SVfitCLAk0_M2600     = ComputeStatisticalError(binxmin_SVfitCLAk0_M2600,binxmax_SVfitCLAk0_M2600,vh_SVfitCLAk0[6],bh_SVfitCLAk0);
  double err_ratio_SVfitCLAk_M200   = ComputeStatisticalError(binxmin_SVfitCLAk_M200,binxmax_SVfitCLAk_M200,vh_SVfitCLAk[0],bh_SVfitCLAk);
  double err_ratio_SVfitCLAk_M300   = ComputeStatisticalError(binxmin_SVfitCLAk_M300,binxmax_SVfitCLAk_M300,vh_SVfitCLAk[1],bh_SVfitCLAk);
  double err_ratio_SVfitCLAk_M500   = ComputeStatisticalError(binxmin_SVfitCLAk_M500,binxmax_SVfitCLAk_M500,vh_SVfitCLAk[2],bh_SVfitCLAk);
  double err_ratio_SVfitCLAk_M800   = ComputeStatisticalError(binxmin_SVfitCLAk_M800,binxmax_SVfitCLAk_M800,vh_SVfitCLAk[3],bh_SVfitCLAk);
  double err_ratio_SVfitCLAk_M1200  = ComputeStatisticalError(binxmin_SVfitCLAk_M1200,binxmax_SVfitCLAk_M1200,vh_SVfitCLAk[4],bh_SVfitCLAk);
  double err_ratio_SVfitCLAk_M1800  = ComputeStatisticalError(binxmin_SVfitCLAk_M1800,binxmax_SVfitCLAk_M1800,vh_SVfitCLAk[5],bh_SVfitCLAk);
  double err_ratio_SVfitCLAk_M2600  = ComputeStatisticalError(binxmin_SVfitCLAk_M2600,binxmax_SVfitCLAk_M2600,vh_SVfitCLAk[6],bh_SVfitCLAk);
  
  int binxmin_SVfitMEMk0_M200     = vh_SVfitMEMk0.at(0)->FindBin(Quantile68(vh_SVfitMEMk0.at(0))[0]); int binxmax_SVfitMEMk0_M200 = vh_SVfitMEMk0.at(0)->FindBin(Quantile68(vh_SVfitMEMk0.at(0))[1]);
  int binxmin_SVfitMEMk0_M300     = vh_SVfitMEMk0.at(1)->FindBin(Quantile68(vh_SVfitMEMk0.at(1))[0]); int binxmax_SVfitMEMk0_M300 = vh_SVfitMEMk0.at(1)->FindBin(Quantile68(vh_SVfitMEMk0.at(1))[1]);
  int binxmin_SVfitMEMk0_M500     = vh_SVfitMEMk0.at(2)->FindBin(Quantile68(vh_SVfitMEMk0.at(2))[0]); int binxmax_SVfitMEMk0_M500 = vh_SVfitMEMk0.at(2)->FindBin(Quantile68(vh_SVfitMEMk0.at(2))[1]);
  int binxmin_SVfitMEMk0_M800     = vh_SVfitMEMk0.at(3)->FindBin(Quantile68(vh_SVfitMEMk0.at(3))[0]); int binxmax_SVfitMEMk0_M800 = vh_SVfitMEMk0.at(3)->FindBin(Quantile68(vh_SVfitMEMk0.at(3))[1]);
  int binxmin_SVfitMEMk0_M1200    = vh_SVfitMEMk0.at(4)->FindBin(Quantile68(vh_SVfitMEMk0.at(4))[0]); int binxmax_SVfitMEMk0_M1200 = vh_SVfitMEMk0.at(4)->FindBin(Quantile68(vh_SVfitMEMk0.at(4))[1]);
  int binxmin_SVfitMEMk0_M1800    = vh_SVfitMEMk0.at(5)->FindBin(Quantile68(vh_SVfitMEMk0.at(5))[0]); int binxmax_SVfitMEMk0_M1800 = vh_SVfitMEMk0.at(5)->FindBin(Quantile68(vh_SVfitMEMk0.at(5))[1]);
  int binxmin_SVfitMEMk0_M2600    = vh_SVfitMEMk0.at(6)->FindBin(Quantile68(vh_SVfitMEMk0.at(6))[0]); int binxmax_SVfitMEMk0_M2600 = vh_SVfitMEMk0.at(6)->FindBin(Quantile68(vh_SVfitMEMk0.at(6))[1]);
  int binxmin_SVfitMEMk_M200  = vh_SVfitMEMk.at(0)->FindBin(Quantile68(vh_SVfitMEMk.at(0))[0]); int binxmax_SVfitMEMk_M200 = vh_SVfitMEMk.at(0)->FindBin(Quantile68(vh_SVfitMEMk.at(0))[1]);
  int binxmin_SVfitMEMk_M300  = vh_SVfitMEMk.at(1)->FindBin(Quantile68(vh_SVfitMEMk.at(1))[0]); int binxmax_SVfitMEMk_M300 = vh_SVfitMEMk.at(1)->FindBin(Quantile68(vh_SVfitMEMk.at(1))[1]);
  int binxmin_SVfitMEMk_M500  = vh_SVfitMEMk.at(2)->FindBin(Quantile68(vh_SVfitMEMk.at(2))[0]); int binxmax_SVfitMEMk_M500 = vh_SVfitMEMk.at(2)->FindBin(Quantile68(vh_SVfitMEMk.at(2))[1]);
  int binxmin_SVfitMEMk_M800  = vh_SVfitMEMk.at(3)->FindBin(Quantile68(vh_SVfitMEMk.at(3))[0]); int binxmax_SVfitMEMk_M800 = vh_SVfitMEMk.at(3)->FindBin(Quantile68(vh_SVfitMEMk.at(3))[1]);
  int binxmin_SVfitMEMk_M1200 = vh_SVfitMEMk.at(4)->FindBin(Quantile68(vh_SVfitMEMk.at(4))[0]); int binxmax_SVfitMEMk_M1200 = vh_SVfitMEMk.at(4)->FindBin(Quantile68(vh_SVfitMEMk.at(4))[1]);
  int binxmin_SVfitMEMk_M1800 = vh_SVfitMEMk.at(5)->FindBin(Quantile68(vh_SVfitMEMk.at(5))[0]); int binxmax_SVfitMEMk_M1800 = vh_SVfitMEMk.at(5)->FindBin(Quantile68(vh_SVfitMEMk.at(5))[1]);
  int binxmin_SVfitMEMk_M2600 = vh_SVfitMEMk.at(6)->FindBin(Quantile68(vh_SVfitMEMk.at(6))[0]); int binxmax_SVfitMEMk_M2600 = vh_SVfitMEMk.at(6)->FindBin(Quantile68(vh_SVfitMEMk.at(6))[1]);

  double bkg_SVfitMEMk0_M200        = bh_SVfitMEMk0->Integral(binxmin_SVfitMEMk0_M200,binxmax_SVfitMEMk0_M200);   
  double bkg_SVfitMEMk0_M300        = bh_SVfitMEMk0->Integral(binxmin_SVfitMEMk0_M300,binxmax_SVfitMEMk0_M300);   
  double bkg_SVfitMEMk0_M500        = bh_SVfitMEMk0->Integral(binxmin_SVfitMEMk0_M500,binxmax_SVfitMEMk0_M500);   
  double bkg_SVfitMEMk0_M800        = bh_SVfitMEMk0->Integral(binxmin_SVfitMEMk0_M800,binxmax_SVfitMEMk0_M800);   
  double bkg_SVfitMEMk0_M1200       = bh_SVfitMEMk0->Integral(binxmin_SVfitMEMk0_M1200,binxmax_SVfitMEMk0_M1200);   
  double bkg_SVfitMEMk0_M1800       = bh_SVfitMEMk0->Integral(binxmin_SVfitMEMk0_M1800,binxmax_SVfitMEMk0_M1800);   
  double bkg_SVfitMEMk0_M2600       = bh_SVfitMEMk0->Integral(binxmin_SVfitMEMk0_M2600,binxmax_SVfitMEMk0_M2600);   
  double bkg_SVfitMEMk_M200         = bh_SVfitMEMk->Integral(binxmin_SVfitMEMk_M200,binxmax_SVfitMEMk_M200);   
  double bkg_SVfitMEMk_M300         = bh_SVfitMEMk->Integral(binxmin_SVfitMEMk_M300,binxmax_SVfitMEMk_M300);   
  double bkg_SVfitMEMk_M500         = bh_SVfitMEMk->Integral(binxmin_SVfitMEMk_M500,binxmax_SVfitMEMk_M500);   
  double bkg_SVfitMEMk_M800         = bh_SVfitMEMk->Integral(binxmin_SVfitMEMk_M800,binxmax_SVfitMEMk_M800);   
  double bkg_SVfitMEMk_M1200        = bh_SVfitMEMk->Integral(binxmin_SVfitMEMk_M1200,binxmax_SVfitMEMk_M1200);   
  double bkg_SVfitMEMk_M1800        = bh_SVfitMEMk->Integral(binxmin_SVfitMEMk_M1800,binxmax_SVfitMEMk_M1800);   
  double bkg_SVfitMEMk_M2600        = bh_SVfitMEMk->Integral(binxmin_SVfitMEMk_M2600,binxmax_SVfitMEMk_M2600);   
  double signal_SVfitMEMk0_M200     = vh_SVfitMEMk0[0]->Integral(binxmin_SVfitMEMk0_M200,binxmax_SVfitMEMk0_M200);   
  double signal_SVfitMEMk0_M300     = vh_SVfitMEMk0[1]->Integral(binxmin_SVfitMEMk0_M300,binxmax_SVfitMEMk0_M300);   
  double signal_SVfitMEMk0_M500     = vh_SVfitMEMk0[2]->Integral(binxmin_SVfitMEMk0_M500,binxmax_SVfitMEMk0_M500);   
  double signal_SVfitMEMk0_M800     = vh_SVfitMEMk0[3]->Integral(binxmin_SVfitMEMk0_M800,binxmax_SVfitMEMk0_M800);   
  double signal_SVfitMEMk0_M1200    = vh_SVfitMEMk0[4]->Integral(binxmin_SVfitMEMk0_M1200,binxmax_SVfitMEMk0_M1200);   
  double signal_SVfitMEMk0_M1800    = vh_SVfitMEMk0[5]->Integral(binxmin_SVfitMEMk0_M1800,binxmax_SVfitMEMk0_M1800);   
  double signal_SVfitMEMk0_M2600    = vh_SVfitMEMk0[6]->Integral(binxmin_SVfitMEMk0_M2600,binxmax_SVfitMEMk0_M2600);   
  double signal_SVfitMEMk_M200      = vh_SVfitMEMk[0]->Integral(binxmin_SVfitMEMk_M200,binxmax_SVfitMEMk_M200);   
  double signal_SVfitMEMk_M300      = vh_SVfitMEMk[1]->Integral(binxmin_SVfitMEMk_M300,binxmax_SVfitMEMk_M300);   
  double signal_SVfitMEMk_M500      = vh_SVfitMEMk[2]->Integral(binxmin_SVfitMEMk_M500,binxmax_SVfitMEMk_M500);   
  double signal_SVfitMEMk_M800      = vh_SVfitMEMk[3]->Integral(binxmin_SVfitMEMk_M800,binxmax_SVfitMEMk_M800);   
  double signal_SVfitMEMk_M1200     = vh_SVfitMEMk[4]->Integral(binxmin_SVfitMEMk_M1200,binxmax_SVfitMEMk_M1200);   
  double signal_SVfitMEMk_M1800     = vh_SVfitMEMk[5]->Integral(binxmin_SVfitMEMk_M1800,binxmax_SVfitMEMk_M1800);   
  double signal_SVfitMEMk_M2600     = vh_SVfitMEMk[6]->Integral(binxmin_SVfitMEMk_M2600,binxmax_SVfitMEMk_M2600);   

  double ratio_SVfitMEMk0_M200      = signal_SVfitMEMk0_M200 / (signal_SVfitMEMk0_M200 + bkg_SVfitMEMk0_M200);
  double ratio_SVfitMEMk0_M300      = signal_SVfitMEMk0_M300 / (signal_SVfitMEMk0_M300 + bkg_SVfitMEMk0_M300);
  double ratio_SVfitMEMk0_M500      = signal_SVfitMEMk0_M500 / (signal_SVfitMEMk0_M500 + bkg_SVfitMEMk0_M500);
  double ratio_SVfitMEMk0_M800      = signal_SVfitMEMk0_M800 / (signal_SVfitMEMk0_M800 + bkg_SVfitMEMk0_M800);
  double ratio_SVfitMEMk0_M1200     = signal_SVfitMEMk0_M1200 / (signal_SVfitMEMk0_M1200 + bkg_SVfitMEMk0_M1200);
  double ratio_SVfitMEMk0_M1800     = signal_SVfitMEMk0_M1800 / (signal_SVfitMEMk0_M1800 + bkg_SVfitMEMk0_M1800);
  double ratio_SVfitMEMk0_M2600     = signal_SVfitMEMk0_M2600 / (signal_SVfitMEMk0_M2600 + bkg_SVfitMEMk0_M2600);
  double ratio_SVfitMEMk_M200       = signal_SVfitMEMk_M200 / (signal_SVfitMEMk_M200 + bkg_SVfitMEMk_M200);
  double ratio_SVfitMEMk_M300       = signal_SVfitMEMk_M300 / (signal_SVfitMEMk_M300 + bkg_SVfitMEMk_M300);
  double ratio_SVfitMEMk_M500       = signal_SVfitMEMk_M500 / (signal_SVfitMEMk_M500 + bkg_SVfitMEMk_M500);
  double ratio_SVfitMEMk_M800       = signal_SVfitMEMk_M800 / (signal_SVfitMEMk_M800 + bkg_SVfitMEMk_M800);
  double ratio_SVfitMEMk_M1200      = signal_SVfitMEMk_M1200 / (signal_SVfitMEMk_M1200 + bkg_SVfitMEMk_M1200);
  double ratio_SVfitMEMk_M1800      = signal_SVfitMEMk_M1800 / (signal_SVfitMEMk_M1800 + bkg_SVfitMEMk_M1800);
  double ratio_SVfitMEMk_M2600      = signal_SVfitMEMk_M2600 / (signal_SVfitMEMk_M2600 + bkg_SVfitMEMk_M2600);
  double err_ratio_SVfitMEMk0_M200   = ComputeStatisticalError(binxmin_SVfitMEMk0_M200,binxmax_SVfitMEMk0_M200,vh_SVfitMEMk0[0],bh_SVfitMEMk0);
  double err_ratio_SVfitMEMk0_M300   = ComputeStatisticalError(binxmin_SVfitMEMk0_M300,binxmax_SVfitMEMk0_M300,vh_SVfitMEMk0[1],bh_SVfitMEMk0);
  double err_ratio_SVfitMEMk0_M500   = ComputeStatisticalError(binxmin_SVfitMEMk0_M500,binxmax_SVfitMEMk0_M500,vh_SVfitMEMk0[2],bh_SVfitMEMk0);
  double err_ratio_SVfitMEMk0_M800   = ComputeStatisticalError(binxmin_SVfitMEMk0_M800,binxmax_SVfitMEMk0_M800,vh_SVfitMEMk0[3],bh_SVfitMEMk0);
  double err_ratio_SVfitMEMk0_M1200  = ComputeStatisticalError(binxmin_SVfitMEMk0_M1200,binxmax_SVfitMEMk0_M1200,vh_SVfitMEMk0[4],bh_SVfitMEMk0);
  double err_ratio_SVfitMEMk0_M1800  = ComputeStatisticalError(binxmin_SVfitMEMk0_M1800,binxmax_SVfitMEMk0_M1800,vh_SVfitMEMk0[5],bh_SVfitMEMk0);
  double err_ratio_SVfitMEMk0_M2600     = ComputeStatisticalError(binxmin_SVfitMEMk0_M2600,binxmax_SVfitMEMk0_M2600,vh_SVfitMEMk0[6],bh_SVfitMEMk0);
  double err_ratio_SVfitMEMk_M200   = ComputeStatisticalError(binxmin_SVfitMEMk_M200,binxmax_SVfitMEMk_M200,vh_SVfitMEMk[0],bh_SVfitMEMk);
  double err_ratio_SVfitMEMk_M300   = ComputeStatisticalError(binxmin_SVfitMEMk_M300,binxmax_SVfitMEMk_M300,vh_SVfitMEMk[1],bh_SVfitMEMk);
  double err_ratio_SVfitMEMk_M500   = ComputeStatisticalError(binxmin_SVfitMEMk_M500,binxmax_SVfitMEMk_M500,vh_SVfitMEMk[2],bh_SVfitMEMk);
  double err_ratio_SVfitMEMk_M800   = ComputeStatisticalError(binxmin_SVfitMEMk_M800,binxmax_SVfitMEMk_M800,vh_SVfitMEMk[3],bh_SVfitMEMk);
  double err_ratio_SVfitMEMk_M1200  = ComputeStatisticalError(binxmin_SVfitMEMk_M1200,binxmax_SVfitMEMk_M1200,vh_SVfitMEMk[4],bh_SVfitMEMk);
  double err_ratio_SVfitMEMk_M1800  = ComputeStatisticalError(binxmin_SVfitMEMk_M1800,binxmax_SVfitMEMk_M1800,vh_SVfitMEMk[5],bh_SVfitMEMk);
  double err_ratio_SVfitMEMk_M2600  = ComputeStatisticalError(binxmin_SVfitMEMk_M2600,binxmax_SVfitMEMk_M2600,vh_SVfitMEMk[6],bh_SVfitMEMk);
  
  ofstream table4;
  table4.open("table4_hadhad.txt");

  table4<< "\\begin{table}"<<endl;
  table4<< "\\begin{center}"<<endl;

    ///////////////////// latex table //////////////////
    table4<< "\\begin{tabular}{|l|ccc|ccc|}"<<endl;
    table4<< "\\hline"<<endl;
    table4<< "\\multicolumn{7}{|c|}{$\\tauh\\tauh$ decay channel} \\\\"<<endl;
    table4<< "\\hline"<<endl;
    table4<< "\\hline"<<endl;
    table4<< "\\multirow{2}{17mm}{Sample} & \\multicolumn{3}{c|}{$m_{\\vis}$} & \\multicolumn{3}{c|}{SVfitSA} \\\\"<<endl;
    table4<< "\\cline{2-7}"<<endl;
    table4<< "& $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ \\\\"<<endl;
    table4<< "\\hline"<<endl;
    
    table4<< "$\\PHiggsps \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
    table4<<"$\\quad m_{\\PHiggsps} = 200$~\\GeV   &  $"<<AlternativeMedian(vh_mvis.at(0))<<"$ & $ "<< rounded(vh_mvis.at(0)->GetRMS()/AlternativeMedian(vh_mvis.at(0))) << "$ & $ " << rounded(100*ratio_mvis_M200) <<"\\pm"<<rounded(100*err_ratio_mvis_M200) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitSA.at(0))<<"$ & $ "<< rounded(vh_SVfitSA.at(0)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(0))) << "$ & $ " << rounded(100*ratio_SVfitSA_M200) <<"\\pm"<<rounded(100*err_ratio_SVfitSA_M200) <<"$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 300$~\\GeV   &  $"<<AlternativeMedian(vh_mvis.at(1))<<"$ & $ "<< rounded(vh_mvis.at(1)->GetRMS()/AlternativeMedian(vh_mvis.at(1))) << "$ & $ " << rounded(100*ratio_mvis_M300) <<"\\pm"<<rounded(100*err_ratio_mvis_M300) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitSA.at(1))<<"$ & $ "<< rounded(vh_SVfitSA.at(1)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(1))) << "$ & $ " << rounded(100*ratio_SVfitSA_M300) <<"\\pm"<<rounded(100*err_ratio_SVfitSA_M300) << "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 500$~\\GeV   &  $"<<AlternativeMedian(vh_mvis.at(2))<<"$ & $ "<< rounded(vh_mvis.at(2)->GetRMS()/AlternativeMedian(vh_mvis.at(2))) << "$ & $ " << rounded(100*ratio_mvis_M500) <<"\\pm"<<rounded(100*err_ratio_mvis_M500)<< 
	    " $ &  $" << AlternativeMedian(vh_SVfitSA.at(2))<<"$ & $ "<< rounded(vh_SVfitSA.at(2)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(2))) << "$ & $ " << rounded(100*ratio_SVfitSA_M500) <<"\\pm"<<rounded(100*err_ratio_SVfitSA_M500) << "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 800$~\\GeV   &  $"<<AlternativeMedian(vh_mvis.at(3))<<"$ & $ "<< rounded(vh_mvis.at(3)->GetRMS()/AlternativeMedian(vh_mvis.at(3))) << "$ & $ " << rounded(100*ratio_mvis_M800) <<"\\pm"<<rounded(100*err_ratio_mvis_M800) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitSA.at(3))<<"$ & $ "<< rounded(vh_SVfitSA.at(3)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(3))) << "$ & $ " << rounded(100*ratio_SVfitSA_M800) <<"\\pm"<<rounded(100*err_ratio_SVfitSA_M800) <<  "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 1200$~\\GeV  &  $"<<AlternativeMedian(vh_mvis.at(4))<<"$ & $ "<< rounded(vh_mvis.at(4)->GetRMS()/AlternativeMedian(vh_mvis.at(4))) << "$ & $ " << rounded(100*ratio_mvis_M1200) <<"\\pm"<<rounded(100*err_ratio_mvis_M1200) <<
	    " $ &  $" << AlternativeMedian(vh_SVfitSA.at(4))<<"$ & $ "<< rounded(vh_SVfitSA.at(4)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(4))) << "$ & $ " << rounded(100*ratio_SVfitSA_M1200) <<"\\pm"<<rounded(100*err_ratio_SVfitSA_M1200) <<  "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 1800$~\\GeV  &  $"<<AlternativeMedian(vh_mvis.at(5))<<"$ & $ "<< rounded(vh_mvis.at(5)->GetRMS()/AlternativeMedian(vh_mvis.at(5))) << "$ & $ " << rounded(100*ratio_mvis_M1800) <<"\\pm"<<rounded(100*err_ratio_mvis_M1800) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitSA.at(5))<<"$ & $ "<< rounded(vh_SVfitSA.at(5)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(5))) << "$ & $ " << rounded(100*ratio_SVfitSA_M1800) <<"\\pm"<<rounded(100*err_ratio_SVfitSA_M1800) << "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 2600$~\\GeV  &  $"<<AlternativeMedian(vh_mvis.at(6))<<"$ & $ "<< rounded(vh_mvis.at(6)->GetRMS()/AlternativeMedian(vh_mvis.at(6))) << "$ & $ " << rounded(100*ratio_mvis_M2600) <<"\\pm"<<rounded(100*err_ratio_mvis_M2600)<<
	    " $ &  $" << AlternativeMedian(vh_SVfitSA.at(6))<<"$ & $ "<< rounded(vh_SVfitSA.at(6)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(6))) << "$ & $ " << rounded(100*ratio_SVfitSA_M2600) <<"\\pm"<<rounded(100*err_ratio_SVfitSA_M2600) <<  "$  \\\\" << endl;
    table4<<"$\\PZ' \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl;
    table4<<"$\\quad m_{\\PZ'} = 2500$~\\GeV       &  $"<<AlternativeMedian(bh_mvis)<<"$ & $ "<< rounded(bh_mvis->GetRMS()/AlternativeMedian(bh_mvis))<< "$ & $ " << " - " <<
	    " $ &  $" << AlternativeMedian(bh_SVfitSA)<<"$ & $ "<< rounded(bh_SVfitSA->GetRMS()/AlternativeMedian(bh_SVfitSA)) << "$ & $ " << " - " << "$  \\\\" << endl;

    table4<<"\\hline"<<endl;
    table4<<"\\end{tabular}\n"<<endl;
    
    table4<< "\\begin{tabular}{|l|ccc|ccc|}"<<endl;
    table4<< "\\hline"<<endl;
    table4<< "\\multicolumn{7}{|c|}{$\\tauh\\tauh$ decay channel} \\\\"<<endl;
    table4<< "\\hline"<<endl;
    table4<< "\\hline"<<endl;
    table4<< "\\multirow{2}{17mm}{Sample} & \\multicolumn{3}{c|}{$cSVfit, $\\kappa=0$$} & \\multicolumn{3}{c|}{cSVfit, $\\kappa=5$} \\\\"<<endl;
    table4<< "\\cline{2-7}"<<endl;
    table4<< "& $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ \\\\"<<endl;
    table4<< "\\hline"<<endl;

    table4<< "$\\PHiggsps \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
    table4<<"$\\quad m_{\\PHiggsps} = 200$~\\GeV   &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(0))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(0)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(0))) << "$ & $ " << rounded(100*ratio_SVfitCLAk0_M200) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk0_M200) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitCLAk.at(0))<<"$ & $ "<< rounded(vh_SVfitCLAk.at(0)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(0))) << "$ & $ " << rounded(100*ratio_SVfitCLAk_M200) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk_M200) <<"$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 300$~\\GeV   &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(1))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(1)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(1))) << "$ & $ " << rounded(100*ratio_SVfitCLAk0_M300) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk0_M300) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitCLAk.at(1))<<"$ & $ "<< rounded(vh_SVfitCLAk.at(1)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(1))) << "$ & $ " << rounded(100*ratio_SVfitCLAk_M300) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk_M300) << "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 500$~\\GeV   &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(2))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(2)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(2))) << "$ & $ " << rounded(100*ratio_SVfitCLAk0_M500) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk0_M500)<< 
	    " $ &  $" << AlternativeMedian(vh_SVfitCLAk.at(2))<<"$ & $ "<< rounded(vh_SVfitCLAk.at(2)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(2))) << "$ & $ " << rounded(100*ratio_SVfitCLAk_M500) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk_M500) << "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 800$~\\GeV   &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(3))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(3)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(3))) << "$ & $ " << rounded(100*ratio_SVfitCLAk0_M800) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk0_M800) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitCLAk.at(3))<<"$ & $ "<< rounded(vh_SVfitCLAk.at(3)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(3))) << "$ & $ " << rounded(100*ratio_SVfitCLAk_M800) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk_M800) <<  "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 1200$~\\GeV  &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(4))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(4)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(4))) << "$ & $ " << rounded(100*ratio_SVfitCLAk0_M1200) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk0_M1200) <<
	    " $ &  $" << AlternativeMedian(vh_SVfitCLAk.at(4))<<"$ & $ "<< rounded(vh_SVfitCLAk.at(4)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(4))) << "$ & $ " << rounded(100*ratio_SVfitCLAk_M1200) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk_M1200) <<  "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 1800$~\\GeV  &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(5))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(5)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(5))) << "$ & $ " << rounded(100*ratio_SVfitCLAk0_M1800) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk0_M1800) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitCLAk.at(5))<<"$ & $ "<< rounded(vh_SVfitCLAk.at(5)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(5))) << "$ & $ " << rounded(100*ratio_SVfitCLAk_M1800) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk_M1800) << "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 2600$~\\GeV  &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(6))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(6)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(6))) << "$ & $ " << rounded(100*ratio_SVfitCLAk0_M2600) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk0_M2600)<<
	    " $ &  $" << AlternativeMedian(vh_SVfitCLAk.at(6))<<"$ & $ "<< rounded(vh_SVfitCLAk.at(6)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(6))) << "$ & $ " << rounded(100*ratio_SVfitCLAk_M2600) <<"\\pm"<<rounded(100*err_ratio_SVfitCLAk_M2600) <<  "$  \\\\" << endl;
    table4<<"$\\PZ' \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl;
    table4<<"$\\quad m_{\\PZ'} = 2500$~\\GeV       &  $"<<AlternativeMedian(bh_SVfitCLAk0)<<"$ & $ "<< rounded(bh_SVfitCLAk0->GetRMS()/AlternativeMedian(bh_SVfitCLAk0))<< "$ & $ " << " - " <<
	    " $ &  $" << AlternativeMedian(bh_SVfitCLAk)<<"$ & $ "<< rounded(bh_SVfitCLAk->GetRMS()/AlternativeMedian(bh_SVfitCLAk)) << "$ & $ " << " - " << "$  \\\\" << endl;

    table4<<"\\hline"<<endl;
    table4<<"\\end{tabular}\n"<<endl;
    
    table4<< "\\begin{tabular}{|l|ccc|ccc|}"<<endl;
    table4<< "\\hline"<<endl;
    table4<< "\\multicolumn{7}{|c|}{$\\tauh\\tauh$ decay channel} \\\\"<<endl;
    table4<< "\\hline"<<endl;
    table4<< "\\hline"<<endl;
    table4<< "\\multirow{2}{17mm}{Sample} & \\multicolumn{3}{c|}{$SVfitMEM, $\\kappa=0$$} & \\multicolumn{3}{c|}{SVfitMEM, $\\kappa=5$} \\\\"<<endl;
    table4<< "\\cline{2-7}"<<endl;
    table4<< "& $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ \\\\"<<endl;
    table4<< "\\hline"<<endl;
    
    table4<< "$\\PHiggsps \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
    table4<<"$\\quad m_{\\PHiggsps} = 200$~\\GeV   &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(0))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(0)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(0))) << "$ & $ " << rounded(100*ratio_SVfitMEMk0_M200) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk0_M200) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitMEMk.at(0))<<"$ & $ "<< rounded(vh_SVfitMEMk.at(0)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(0))) << "$ & $ " << rounded(100*ratio_SVfitMEMk_M200) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk_M200) <<"$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 300$~\\GeV   &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(1))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(1)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(1))) << "$ & $ " << rounded(100*ratio_SVfitMEMk0_M300) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk0_M300) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitMEMk.at(1))<<"$ & $ "<< rounded(vh_SVfitMEMk.at(1)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(1))) << "$ & $ " << rounded(100*ratio_SVfitMEMk_M300) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk_M300) << "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 500$~\\GeV   &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(2))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(2)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(2))) << "$ & $ " << rounded(100*ratio_SVfitMEMk0_M500) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk0_M500)<< 
	    " $ &  $" << AlternativeMedian(vh_SVfitMEMk.at(2))<<"$ & $ "<< rounded(vh_SVfitMEMk.at(2)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(2))) << "$ & $ " << rounded(100*ratio_SVfitMEMk_M500) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk_M500) << "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 800$~\\GeV   &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(3))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(3)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(3))) << "$ & $ " << rounded(100*ratio_SVfitMEMk0_M800) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk0_M800) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitMEMk.at(3))<<"$ & $ "<< rounded(vh_SVfitMEMk.at(3)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(3))) << "$ & $ " << rounded(100*ratio_SVfitMEMk_M800) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk_M800) <<  "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 1200$~\\GeV  &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(4))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(4)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(4))) << "$ & $ " << rounded(100*ratio_SVfitMEMk0_M1200) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk0_M1200) <<
	    " $ &  $" << AlternativeMedian(vh_SVfitMEMk.at(4))<<"$ & $ "<< rounded(vh_SVfitMEMk.at(4)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(4))) << "$ & $ " << rounded(100*ratio_SVfitMEMk_M1200) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk_M1200) <<  "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 1800$~\\GeV  &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(5))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(5)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(5))) << "$ & $ " << rounded(100*ratio_SVfitMEMk0_M1800) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk0_M1800) << 
	    " $ &  $" << AlternativeMedian(vh_SVfitMEMk.at(5))<<"$ & $ "<< rounded(vh_SVfitMEMk.at(5)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(5))) << "$ & $ " << rounded(100*ratio_SVfitMEMk_M1800) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk_M1800) << "$  \\\\" << endl;
    table4<<"$\\quad m_{\\PHiggsps} = 2600$~\\GeV  &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(6))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(6)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(6))) << "$ & $ " << rounded(100*ratio_SVfitMEMk0_M2600) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk0_M2600)<<
	    " $ &  $" << AlternativeMedian(vh_SVfitMEMk.at(6))<<"$ & $ "<< rounded(vh_SVfitMEMk.at(6)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(6))) << "$ & $ " << rounded(100*ratio_SVfitMEMk_M2600) <<"\\pm"<<rounded(100*err_ratio_SVfitMEMk_M2600) <<  "$  \\\\" << endl;
    table4<<"$\\PZ' \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl;
    table4<<"$\\quad m_{\\PZ'} = 2500$~\\GeV       &  $"<<AlternativeMedian(bh_SVfitMEMk0)<<"$ & $ "<< rounded(bh_SVfitMEMk0->GetRMS()/AlternativeMedian(bh_SVfitMEMk0))<< "$ & $ " << " - " <<
	    " $ &  $" << AlternativeMedian(bh_SVfitMEMk)<<"$ & $ "<< rounded(bh_SVfitMEMk->GetRMS()/AlternativeMedian(bh_SVfitMEMk)) << "$ & $ " << " - " << "$  \\\\" << endl;

    table4<<"\\hline"<<endl;
    table4<<"\\end{tabular}\n"<<endl;
    table4<<"\\end{table}\n"<<endl;

  table4.close();

} // void
