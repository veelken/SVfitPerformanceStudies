#include "func.C"
#include <fstream>
#include <vector>
#include <math.h>

double AlternativeMedian(const TH1D * h1);
double rounded(double val);
double ComputeStatisticalError(int bin1, int bin2, TH1D* hSig, TH1D* hBkg, double xsSig, double xsBkg, double ceSig, double ceBkg){

        cout << " into the function " << hBkg->GetName() << endl;
	double nBkg = hBkg->Integral(bin1,bin2);
	double nSig = hSig->Integral(bin1,bin2);
        cout << " nBkg " << nBkg << endl;
        cout << " nSig " << nSig << endl;
	double poissonBkg = 1;
	double poissonSig = 1;
        if(nBkg!=0) poissonBkg = TMath::Sqrt(nBkg/hBkg->GetEntries());
        if(nSig!=0) poissonSig = TMath::Sqrt(nSig/hSig->GetEntries());
        cout << " poissonBkg " << poissonBkg << endl;
        cout << " poissonSig " << poissonSig << endl;
	double term1 = TMath::Power(nBkg*xsBkg*ceBkg*poissonSig*xsSig*ceSig,2); // (B*sigma_S)2 
	double term2 = TMath::Power(nSig*xsSig*ceSig*poissonBkg*xsBkg*ceBkg,2); // (S*sigma_B)2
        cout << "(nSig*xsSig*ceSig) " << (nSig*xsSig*ceSig) << " (xsBkg*ceBkg) " << (xsBkg*ceBkg) << endl;  
	double term3 = TMath::Power((nSig*xsSig*ceSig)+(nBkg*xsBkg*ceBkg),4);    // (S+B)2
	double finalError = TMath::Sqrt((term1+term2)/term3);
        cout << "xsBkg "<< xsBkg << " ceBkg " << ceBkg << " xsSig "<< xsSig << " ceSig " << ceSig << endl; 
	cout << " term1 " << term1 << " term2 " << term2 << " term3 " << term3 << endl;
        cout << " final error " << finalError << endl;
        return finalError; 
}

void table3_emu(){

  // plot histogram
  cout<<"plotting hist...\n";

  string inputPath {"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_III"};
  string savePath {"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot"};

  // root file
  vector<double> CEfactor_visMass_svFit {0.163568773234201,0.181412639405204,0.205204460966543,0.0267657992565056,
                                         0.554179475053204,0.177642468668716,0.0500709387562071,0.406844327381183};
  vector<double> CEfactor_CsvFit        {0.129752066115702,0.188429752066116,0.188429752066116,0.0289256198347107,
                                         0.512967032967033,0.19083685545224,0.05541842772612,0.409154430379747};
  
  vector<string> vinput {
          "hist_smeared_DYJetsToLLM50_0Jets.root",
          "hist_smeared_DYJetsToLLM50_1JetNotBoosted.root",
          "hist_smeared_DYJetsToLLM50_1JetBoosted.root",
          "hist_smeared_DYJetsToLLM50_2Jets.root",
          "hist_smeared_GluGluHToTauTauM125_0Jets.root",
          "hist_smeared_GluGluHToTauTauM125_1JetNotBoosted.root",
          "hist_smeared_GluGluHToTauTauM125_1JetBoosted.root",
          "hist_smeared_VBFHToTauTauM125_2Jets.root"
  };

  vector<string>vsample{
          "DYJetsToLLM50",
          "DYJetsToLLM50",
          "DYJetsToLLM50",
          "DYJetsToLLM50",
          "GluGluHToTauTauM125",
          "GluGluHToTauTauM125",
          "GluGluHToTauTauM125",
          "VBFHToTauTauM125"
  };


  func();

  bool log{0};
  double glugluxs = 43.92*0.0627;  //pb
  double vbfxs    = 3.748*0.0627; //pb
  double dyxs     = 5765.4; //NNLO pb

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
		  if(histname.find("emu")==std::string::npos) continue; 
		  if(histname.find("fine_bin")==std::string::npos) continue; 
		  if(histname.find("smeared_vismass_fine_bin")!=std::string::npos)         vh_mvis.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svFit_fine_bin")!=std::string::npos)           vh_SVfitSA.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svfitmemtfk0_fine_bin")!=std::string::npos)    vh_SVfitMEMk0.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svfitclatfk0_fine_bin")!=std::string::npos)    vh_SVfitCLAk0.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svfitmemtfk3_fine_bin")!=std::string::npos)    vh_SVfitMEMk.push_back((TH1D*)hmass->Clone());
		  if(histname.find("smeared_svfitclatfk3_fine_bin")!=std::string::npos)    vh_SVfitCLAk.push_back((TH1D*)hmass->Clone());
	  }
  }	

  ofstream table3;
  table3.open("table3_emu.txt");

  table3<< "\\begin{table}"<<endl;
  table3<< "\\begin{center}"<<endl;

    ///////////////////// latex table //////////////////
    table3<< "\\begin{tabular}{|l|ccc|ccc|}"<<endl;
    table3<< "\\hline"<<endl;
    table3<< "\\multicolumn{7}{|c|}{$\\tauh\\tauh$ decay channel} \\\\"<<endl;
    table3<< "\\hline"<<endl;
    table3<< "\\hline"<<endl;
    table3<< "\\multirow{2}{17mm}{Sample} & \\multicolumn{3}{c|}{$m_{\\vis}$} & \\multicolumn{3}{c|}{SVfitSA} \\\\"<<endl;
    table3<< "\\cline{2-7}"<<endl;
    table3<< "& $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ \\\\"<<endl;
    table3<< "\\hline"<<endl;
    
    //Ztautau			    
    table3<< "$\\PZ \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
    table3<<"$\\quad$ $0$-jet              &  $"<<AlternativeMedian(vh_mvis.at(0))<<"$ & $ "<<
	    rounded(vh_mvis.at(0)->GetRMS()/AlternativeMedian(vh_mvis.at(0))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitSA.at(0))<<"$ & $ "<<
		    rounded(vh_SVfitSA.at(0)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(0))) << "$ & $-$  \\\\" << endl;
    table3<<"$\\quad$ $1$-jet non--boosted &  $"<<AlternativeMedian(vh_mvis.at(1))<<"$ & $ "<<
	    rounded(vh_mvis.at(1)->GetRMS()/AlternativeMedian(vh_mvis.at(1))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitSA.at(1))<<"$ & $ "<<
		    rounded(vh_SVfitSA.at(1)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(1))) << "$ & $-$  \\\\" << endl;
    table3<<"$\\quad$ $1$-jet boosted      &  $"<<AlternativeMedian(vh_mvis.at(2))<<"$ & $ "<<
	    rounded(vh_mvis.at(2)->GetRMS()/AlternativeMedian(vh_mvis.at(2))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitSA.at(2))<<"$ & $ "<<
		    rounded(vh_SVfitSA.at(2)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(2))) << "$ & $-$  \\\\" << endl;
    table3<<"$\\quad$ $2$-jet VBF          &  $"<<AlternativeMedian(vh_mvis.at(3))<<"$ & $ "<<
	    rounded(vh_mvis.at(3)->GetRMS()/AlternativeMedian(vh_mvis.at(3))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitSA.at(3))<<"$ & $ "<<
		    rounded(vh_SVfitSA.at(3)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(3))) << "$ & $-$  \\\\" << endl;
 
    //SM GluGlu	
    int binxmin_mvis_0     = vh_mvis.at(4)->FindBin(Quantile68(vh_mvis.at(4))[0]); int binxmax_mvis_0  = vh_mvis.at(4)->FindBin(Quantile68(vh_mvis.at(4))[1]);
    int binxmin_mvis_10    = vh_mvis.at(5)->FindBin(Quantile68(vh_mvis.at(5))[0]); int binxmax_mvis_10 = vh_mvis.at(5)->FindBin(Quantile68(vh_mvis.at(5))[1]);
    int binxmin_mvis_11    = vh_mvis.at(6)->FindBin(Quantile68(vh_mvis.at(6))[0]); int binxmax_mvis_11 = vh_mvis.at(6)->FindBin(Quantile68(vh_mvis.at(6))[1]);
    int binxmin_mvis_2     = vh_mvis.at(7)->FindBin(Quantile68(vh_mvis.at(7))[0]); int binxmax_mvis_2  = vh_mvis.at(7)->FindBin(Quantile68(vh_mvis.at(7))[1]);
    int binxmin_SVfitSA_0  = vh_SVfitSA.at(4)->FindBin(Quantile68(vh_SVfitSA.at(4))[0]); int binxmax_SVfitSA_0  = vh_SVfitSA.at(4)->FindBin(Quantile68(vh_SVfitSA.at(4))[1]);
    int binxmin_SVfitSA_10 = vh_SVfitSA.at(5)->FindBin(Quantile68(vh_SVfitSA.at(5))[0]); int binxmax_SVfitSA_10 = vh_SVfitSA.at(5)->FindBin(Quantile68(vh_SVfitSA.at(5))[1]);
    int binxmin_SVfitSA_11 = vh_SVfitSA.at(6)->FindBin(Quantile68(vh_SVfitSA.at(6))[0]); int binxmax_SVfitSA_11 = vh_SVfitSA.at(6)->FindBin(Quantile68(vh_SVfitSA.at(6))[1]);
    int binxmin_SVfitSA_2  = vh_SVfitSA.at(7)->FindBin(Quantile68(vh_SVfitSA.at(7))[0]); int binxmax_SVfitSA_2  = vh_SVfitSA.at(7)->FindBin(Quantile68(vh_SVfitSA.at(7))[1]);
    
    cout << " outside the function " << endl;
    cout << " vh_SVfitSA[3]->Integral(binxmin_SVfitSA_2,binxmax_SVfitSA_2) " << vh_SVfitSA[3]->Integral(binxmin_SVfitSA_2,binxmax_SVfitSA_2) << " bkg_SVfitSA_2Jets " << endl;
    cout << " vh_SVfitSA[7]->Integral(binxmin_SVfitSA_2,binxmax_SVfitSA_2) " << vh_SVfitSA[7]->Integral(binxmin_SVfitSA_2,binxmax_SVfitSA_2) << " signal_SVfitSA_2Jets " << endl;
     
    double bkg_mvis_0Jets             = vh_mvis[0]->Integral(binxmin_mvis_0,binxmax_mvis_0)   * dyxs     * CEfactor_visMass_svFit[0];
    double bkg_mvis_1JetNonBoosted    = vh_mvis[1]->Integral(binxmin_mvis_10,binxmax_mvis_10) * dyxs     * CEfactor_visMass_svFit[1];
    double bkg_mvis_1JetBoosted       = vh_mvis[2]->Integral(binxmin_mvis_11,binxmax_mvis_11) * dyxs     * CEfactor_visMass_svFit[2];
    double bkg_mvis_2Jets             = vh_mvis[3]->Integral(binxmin_mvis_2,binxmax_mvis_2)   * dyxs     * CEfactor_visMass_svFit[3];
    double signal_mvis_0Jets          = vh_mvis[4]->Integral(binxmin_mvis_0,binxmax_mvis_0)   * glugluxs * CEfactor_visMass_svFit[4];
    double signal_mvis_1JetNonBoosted = vh_mvis[5]->Integral(binxmin_mvis_10,binxmax_mvis_10) * glugluxs * CEfactor_visMass_svFit[5];
    double signal_mvis_1JetBoosted    = vh_mvis[6]->Integral(binxmin_mvis_11,binxmax_mvis_11) * glugluxs * CEfactor_visMass_svFit[6];
    double signal_mvis_2Jets          = vh_mvis[7]->Integral(binxmin_mvis_2,binxmax_mvis_2)   * vbfxs    * CEfactor_visMass_svFit[7];
    
    double bkg_SVfitSA_0Jets             = vh_SVfitSA[0]->Integral(binxmin_SVfitSA_0,binxmax_SVfitSA_0)   * dyxs     * CEfactor_visMass_svFit[0];
    double bkg_SVfitSA_1JetNonBoosted    = vh_SVfitSA[1]->Integral(binxmin_SVfitSA_10,binxmax_SVfitSA_10) * dyxs     * CEfactor_visMass_svFit[1];
    double bkg_SVfitSA_1JetBoosted       = vh_SVfitSA[2]->Integral(binxmin_SVfitSA_11,binxmax_SVfitSA_11) * dyxs     * CEfactor_visMass_svFit[2];
    double bkg_SVfitSA_2Jets             = vh_SVfitSA[3]->Integral(binxmin_SVfitSA_2,binxmax_SVfitSA_2)   * dyxs     * CEfactor_visMass_svFit[3];
    double signal_SVfitSA_0Jets          = vh_SVfitSA[4]->Integral(binxmin_SVfitSA_0,binxmax_SVfitSA_0)   * glugluxs * CEfactor_visMass_svFit[4];
    double signal_SVfitSA_1JetNonBoosted = vh_SVfitSA[5]->Integral(binxmin_SVfitSA_10,binxmax_SVfitSA_10) * glugluxs * CEfactor_visMass_svFit[5];
    double signal_SVfitSA_1JetBoosted    = vh_SVfitSA[6]->Integral(binxmin_SVfitSA_11,binxmax_SVfitSA_11) * glugluxs * CEfactor_visMass_svFit[6];
    double signal_SVfitSA_2Jets          = vh_SVfitSA[7]->Integral(binxmin_SVfitSA_2,binxmax_SVfitSA_2)   * vbfxs    * CEfactor_visMass_svFit[7];

    double ratio_mvis_0Jets             = signal_mvis_0Jets / ( signal_mvis_0Jets + bkg_mvis_0Jets );
    double ratio_mvis_1JetNonBoosted    = signal_mvis_1JetNonBoosted / ( signal_mvis_1JetNonBoosted + bkg_mvis_1JetNonBoosted );
    double ratio_mvis_1JetBoosted       = signal_mvis_1JetBoosted / ( signal_mvis_1JetBoosted + bkg_mvis_1JetBoosted );
    double ratio_mvis_2Jets             = signal_mvis_2Jets / ( signal_mvis_2Jets + bkg_mvis_2Jets );
    double ratio_SVfitSA_0Jets             = signal_SVfitSA_0Jets / ( signal_SVfitSA_0Jets + bkg_SVfitSA_0Jets );
    double ratio_SVfitSA_1JetNonBoosted    = signal_SVfitSA_1JetNonBoosted / ( signal_SVfitSA_1JetNonBoosted + bkg_SVfitSA_1JetNonBoosted );
    double ratio_SVfitSA_1JetBoosted       = signal_SVfitSA_1JetBoosted / ( signal_SVfitSA_1JetBoosted + bkg_SVfitSA_1JetBoosted );
    double ratio_SVfitSA_2Jets             = signal_SVfitSA_2Jets / ( signal_SVfitSA_2Jets + bkg_SVfitSA_2Jets );

    double err_ratio_mvis_0Jets 		= ComputeStatisticalError(binxmin_mvis_0,    binxmax_mvis_0,    vh_mvis[4],   vh_mvis[0],   glugluxs,dyxs,CEfactor_visMass_svFit[4],CEfactor_visMass_svFit[0]);
    double err_ratio_mvis_1JetNonBoosted 	= ComputeStatisticalError(binxmin_mvis_10,   binxmax_mvis_10,   vh_mvis[5],   vh_mvis[1],   glugluxs,dyxs,CEfactor_visMass_svFit[5],CEfactor_visMass_svFit[1]);
    double err_ratio_mvis_1JetBoosted 		= ComputeStatisticalError(binxmin_mvis_11,   binxmax_mvis_11,   vh_mvis[6],   vh_mvis[2],   glugluxs,dyxs,CEfactor_visMass_svFit[6],CEfactor_visMass_svFit[2]);
    double err_ratio_mvis_2Jets 		= ComputeStatisticalError(binxmin_mvis_2,    binxmax_mvis_2,    vh_mvis[7],   vh_mvis[3],   vbfxs,   dyxs,CEfactor_visMass_svFit[7],CEfactor_visMass_svFit[3]);
    double err_ratio_SVfitSA_0Jets		= ComputeStatisticalError(binxmin_SVfitSA_0, binxmax_SVfitSA_0, vh_SVfitSA[4],vh_SVfitSA[0],glugluxs,dyxs,CEfactor_visMass_svFit[4],CEfactor_visMass_svFit[0]);
    double err_ratio_SVfitSA_1JetNonBoosted 	= ComputeStatisticalError(binxmin_SVfitSA_10,binxmax_SVfitSA_10,vh_SVfitSA[5],vh_SVfitSA[1],glugluxs,dyxs,CEfactor_visMass_svFit[5],CEfactor_visMass_svFit[1]);
    double err_ratio_SVfitSA_1JetBoosted 	= ComputeStatisticalError(binxmin_SVfitSA_11,binxmax_SVfitSA_11,vh_SVfitSA[6],vh_SVfitSA[2],glugluxs,dyxs,CEfactor_visMass_svFit[6],CEfactor_visMass_svFit[2]);
    double err_ratio_SVfitSA_2Jets 		= ComputeStatisticalError(binxmin_SVfitSA_2, binxmax_SVfitSA_2, vh_SVfitSA[7],vh_SVfitSA[3],vbfxs,   dyxs,CEfactor_visMass_svFit[7],CEfactor_visMass_svFit[3]);


    table3<< "SM $\\Pg\\Pg \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 

    table3<<"$\\quad$ $0$-jet              &  $"<<AlternativeMedian(vh_mvis.at(4))<<"$ & $ "<< rounded(vh_mvis.at(4)->GetRMS()/AlternativeMedian(vh_mvis.at(4))) << 
	    "$ & $" << rounded(ratio_mvis_0Jets*100) << "\\pm"<<rounded(err_ratio_mvis_0Jets*100) <<" $ &  $" << AlternativeMedian(vh_SVfitSA.at(4))<<"$ & $ "<<
		    rounded(vh_SVfitSA.at(4)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(4))) << "$ & $" << rounded(ratio_SVfitSA_0Jets*100) << "\\pm"<<rounded(err_ratio_SVfitSA_0Jets*100) <<" $ \\\\" << endl;

    table3<<"$\\quad$ $1$-jet non--boosted &  $"<<AlternativeMedian(vh_mvis.at(5))<<"$ & $ "<< rounded(vh_mvis.at(5)->GetRMS()/AlternativeMedian(vh_mvis.at(5))) << 
	    "$ & $ " << rounded(ratio_mvis_1JetNonBoosted*100) << "\\pm"<<rounded(err_ratio_mvis_1JetNonBoosted*100) << "$ &  $" << AlternativeMedian(vh_SVfitSA.at(5))<<"$ & $ "<<
		    rounded(vh_SVfitSA.at(5)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(5))) << "$ & $ " << rounded(ratio_SVfitSA_1JetNonBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitSA_1JetNonBoosted*100) << " $  \\\\" << endl;

    table3<<"$\\quad$ $1$-jet boosted      &  $"<<AlternativeMedian(vh_mvis.at(6))<<"$ & $ "<< rounded(vh_mvis.at(6)->GetRMS()/AlternativeMedian(vh_mvis.at(6))) << 
	    "$ & $ " << rounded(ratio_mvis_1JetBoosted*100) << "\\pm"<<rounded(err_ratio_mvis_1JetBoosted*100) << "$ &  $" << AlternativeMedian(vh_SVfitSA.at(6))<<"$ & $ "<<
		    rounded(vh_SVfitSA.at(6)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(6))) << "$ & $" << rounded(ratio_SVfitSA_1JetBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitSA_1JetBoosted*100) <<  "$  \\\\" << endl;

    //SM VBF		    
    table3<< "SM $\\Pquark\\APquark \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & "<<endl; 
    table3<<"$\\quad$ $2$-jet VBF          &  $"<<AlternativeMedian(vh_mvis.at(7))<<"$ & $ "<< rounded(vh_mvis.at(7)->GetRMS()/AlternativeMedian(vh_mvis.at(7))) << 
	    "$ & $ "<< rounded(ratio_mvis_2Jets*100) << "\\pm"<<rounded(err_ratio_mvis_2Jets*100) << "$ &  $" << AlternativeMedian(vh_SVfitSA.at(7))<<"$ & $ "<<
		    rounded(vh_SVfitSA.at(7)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(7))) << "$ & $"<< rounded(ratio_SVfitSA_2Jets*100) << "\\pm"<<rounded(err_ratio_SVfitSA_2Jets*100) <<  "$  \\\\" << endl;

    table3<<"\\hline"<<endl;
    table3<<"\\end{tabular}\n"<<endl;
    
    int binxmin_SVfitCLAk0_0  = vh_SVfitCLAk0.at(4)->FindBin(Quantile68(vh_SVfitCLAk0.at(4))[0]); int binxmax_SVfitCLAk0_0  = vh_SVfitCLAk0.at(4)->FindBin(Quantile68(vh_SVfitCLAk0.at(4))[1]);
    int binxmin_SVfitCLAk0_10 = vh_SVfitCLAk0.at(5)->FindBin(Quantile68(vh_SVfitCLAk0.at(5))[0]); int binxmax_SVfitCLAk0_10 = vh_SVfitCLAk0.at(5)->FindBin(Quantile68(vh_SVfitCLAk0.at(5))[1]);
    int binxmin_SVfitCLAk0_11 = vh_SVfitCLAk0.at(6)->FindBin(Quantile68(vh_SVfitCLAk0.at(6))[0]); int binxmax_SVfitCLAk0_11 = vh_SVfitCLAk0.at(6)->FindBin(Quantile68(vh_SVfitCLAk0.at(6))[1]);
    int binxmin_SVfitCLAk0_2  = vh_SVfitCLAk0.at(7)->FindBin(Quantile68(vh_SVfitCLAk0.at(7))[0]); int binxmax_SVfitCLAk0_2  = vh_SVfitCLAk0.at(7)->FindBin(Quantile68(vh_SVfitCLAk0.at(7))[1]);
    int binxmin_SVfitCLAk_0   = vh_SVfitCLAk.at(4)->FindBin(Quantile68(vh_SVfitCLAk.at(4))[0]);   int binxmax_SVfitCLAk_0  = vh_SVfitCLAk.at(4)->FindBin(Quantile68(vh_SVfitCLAk.at(4))[1]);
    int binxmin_SVfitCLAk_10  = vh_SVfitCLAk.at(5)->FindBin(Quantile68(vh_SVfitCLAk.at(5))[0]);   int binxmax_SVfitCLAk_10 = vh_SVfitCLAk.at(5)->FindBin(Quantile68(vh_SVfitCLAk.at(5))[1]);
    int binxmin_SVfitCLAk_11  = vh_SVfitCLAk.at(6)->FindBin(Quantile68(vh_SVfitCLAk.at(6))[0]);   int binxmax_SVfitCLAk_11 = vh_SVfitCLAk.at(6)->FindBin(Quantile68(vh_SVfitCLAk.at(6))[1]);
    int binxmin_SVfitCLAk_2   = vh_SVfitCLAk.at(7)->FindBin(Quantile68(vh_SVfitCLAk.at(7))[0]);   int binxmax_SVfitCLAk_2  = vh_SVfitCLAk.at(7)->FindBin(Quantile68(vh_SVfitCLAk.at(7))[1]);

    double bkg_SVfitCLAk0_0Jets             = vh_SVfitCLAk0[0]->Integral(binxmin_SVfitCLAk0_0,binxmax_SVfitCLAk0_0)   * dyxs     * CEfactor_CsvFit[0];
    double bkg_SVfitCLAk0_1JetNonBoosted    = vh_SVfitCLAk0[1]->Integral(binxmin_SVfitCLAk0_10,binxmax_SVfitCLAk0_10) * dyxs     * CEfactor_CsvFit[1];
    double bkg_SVfitCLAk0_1JetBoosted       = vh_SVfitCLAk0[2]->Integral(binxmin_SVfitCLAk0_11,binxmax_SVfitCLAk0_11) * dyxs     * CEfactor_CsvFit[2];
    double bkg_SVfitCLAk0_2Jets             = vh_SVfitCLAk0[3]->Integral(binxmin_SVfitCLAk0_2,binxmax_SVfitCLAk0_2)   * dyxs     * CEfactor_CsvFit[3];
    double signal_SVfitCLAk0_0Jets          = vh_SVfitCLAk0[4]->Integral(binxmin_SVfitCLAk0_0,binxmax_SVfitCLAk0_0)   * glugluxs * CEfactor_CsvFit[4];
    double signal_SVfitCLAk0_1JetNonBoosted = vh_SVfitCLAk0[5]->Integral(binxmin_SVfitCLAk0_10,binxmax_SVfitCLAk0_10) * glugluxs * CEfactor_CsvFit[5];
    double signal_SVfitCLAk0_1JetBoosted    = vh_SVfitCLAk0[6]->Integral(binxmin_SVfitCLAk0_11,binxmax_SVfitCLAk0_11) * glugluxs * CEfactor_CsvFit[6];
    double signal_SVfitCLAk0_2Jets          = vh_SVfitCLAk0[7]->Integral(binxmin_SVfitCLAk0_2,binxmax_SVfitCLAk0_2)   * vbfxs    * CEfactor_CsvFit[7];
    
    double bkg_SVfitCLAk_0Jets             = vh_SVfitCLAk[0]->Integral(binxmin_SVfitCLAk_0,binxmax_SVfitCLAk_0)   * dyxs     * CEfactor_CsvFit[0];
    double bkg_SVfitCLAk_1JetNonBoosted    = vh_SVfitCLAk[1]->Integral(binxmin_SVfitCLAk_10,binxmax_SVfitCLAk_10) * dyxs     * CEfactor_CsvFit[1];
    double bkg_SVfitCLAk_1JetBoosted       = vh_SVfitCLAk[2]->Integral(binxmin_SVfitCLAk_11,binxmax_SVfitCLAk_11) * dyxs     * CEfactor_CsvFit[2];
    double bkg_SVfitCLAk_2Jets             = vh_SVfitCLAk[3]->Integral(binxmin_SVfitCLAk_2,binxmax_SVfitCLAk_2)   * dyxs     * CEfactor_CsvFit[3];
    double signal_SVfitCLAk_0Jets          = vh_SVfitCLAk[4]->Integral(binxmin_SVfitCLAk_0,binxmax_SVfitCLAk_0)   * glugluxs * CEfactor_CsvFit[4];
    double signal_SVfitCLAk_1JetNonBoosted = vh_SVfitCLAk[5]->Integral(binxmin_SVfitCLAk_10,binxmax_SVfitCLAk_10) * glugluxs * CEfactor_CsvFit[5];
    double signal_SVfitCLAk_1JetBoosted    = vh_SVfitCLAk[6]->Integral(binxmin_SVfitCLAk_11,binxmax_SVfitCLAk_11) * glugluxs * CEfactor_CsvFit[6];
    double signal_SVfitCLAk_2Jets          = vh_SVfitCLAk[7]->Integral(binxmin_SVfitCLAk_2,binxmax_SVfitCLAk_2)   * vbfxs    * CEfactor_CsvFit[7];

    double ratio_SVfitCLAk0_0Jets             = signal_SVfitCLAk0_0Jets / ( signal_SVfitCLAk0_0Jets + bkg_SVfitCLAk0_0Jets );
    double ratio_SVfitCLAk0_1JetNonBoosted    = signal_SVfitCLAk0_1JetNonBoosted / ( signal_SVfitCLAk0_1JetNonBoosted + bkg_SVfitCLAk0_1JetNonBoosted );
    double ratio_SVfitCLAk0_1JetBoosted       = signal_SVfitCLAk0_1JetBoosted / ( signal_SVfitCLAk0_1JetBoosted + bkg_SVfitCLAk0_1JetBoosted );
    double ratio_SVfitCLAk0_2Jets             = signal_SVfitCLAk0_2Jets / ( signal_SVfitCLAk0_2Jets + bkg_SVfitCLAk0_2Jets );
    double ratio_SVfitCLAk_0Jets             = signal_SVfitCLAk_0Jets / ( signal_SVfitCLAk_0Jets + bkg_SVfitCLAk_0Jets );
    double ratio_SVfitCLAk_1JetNonBoosted    = signal_SVfitCLAk_1JetNonBoosted / ( signal_SVfitCLAk_1JetNonBoosted + bkg_SVfitCLAk_1JetNonBoosted );
    double ratio_SVfitCLAk_1JetBoosted       = signal_SVfitCLAk_1JetBoosted / ( signal_SVfitCLAk_1JetBoosted + bkg_SVfitCLAk_1JetBoosted );
    double ratio_SVfitCLAk_2Jets             = signal_SVfitCLAk_2Jets / ( signal_SVfitCLAk_2Jets + bkg_SVfitCLAk_2Jets );
    
    double err_ratio_SVfitCLAk_0Jets = ComputeStatisticalError(binxmin_SVfitCLAk_0,binxmax_SVfitCLAk_0,vh_SVfitCLAk[4],vh_SVfitCLAk[0],glugluxs,dyxs,CEfactor_CsvFit[4],CEfactor_CsvFit[0]);
    double err_ratio_SVfitCLAk_1JetNonBoosted = ComputeStatisticalError(binxmin_SVfitCLAk_10,binxmax_SVfitCLAk_10,vh_SVfitCLAk[5],vh_SVfitCLAk[1],glugluxs,dyxs,CEfactor_CsvFit[5],CEfactor_CsvFit[1]);
    double err_ratio_SVfitCLAk_1JetBoosted = ComputeStatisticalError(binxmin_SVfitCLAk_11,binxmax_SVfitCLAk_11,vh_SVfitCLAk[6],vh_SVfitCLAk[2],glugluxs,dyxs,CEfactor_CsvFit[6],CEfactor_CsvFit[2]);
    double err_ratio_SVfitCLAk_2Jets = ComputeStatisticalError(binxmin_SVfitCLAk_2,binxmax_SVfitCLAk_2,vh_SVfitCLAk[7],vh_SVfitCLAk[3],vbfxs,dyxs,CEfactor_CsvFit[7],CEfactor_CsvFit[3]);
    double err_ratio_SVfitCLAk0_0Jets = ComputeStatisticalError(binxmin_SVfitCLAk0_0,binxmax_SVfitCLAk0_0,vh_SVfitCLAk0[4],vh_SVfitCLAk0[0],glugluxs,dyxs,CEfactor_CsvFit[4],CEfactor_CsvFit[0]);
    double err_ratio_SVfitCLAk0_1JetNonBoosted = ComputeStatisticalError(binxmin_SVfitCLAk0_10,binxmax_SVfitCLAk0_10,vh_SVfitCLAk0[5],vh_SVfitCLAk0[1],glugluxs,dyxs,CEfactor_CsvFit[5],CEfactor_CsvFit[1]);
    double err_ratio_SVfitCLAk0_1JetBoosted = ComputeStatisticalError(binxmin_SVfitCLAk0_11,binxmax_SVfitCLAk0_11,vh_SVfitCLAk0[6],vh_SVfitCLAk0[2],glugluxs,dyxs,CEfactor_CsvFit[6],CEfactor_CsvFit[2]);
    double err_ratio_SVfitCLAk0_2Jets = ComputeStatisticalError(binxmin_SVfitCLAk0_2,binxmax_SVfitCLAk0_2,vh_SVfitCLAk0[7],vh_SVfitCLAk0[3],vbfxs,dyxs,CEfactor_CsvFit[7],CEfactor_CsvFit[3]);
    
    table3<< "\\begin{tabular}{|l|ccc|ccc|}"<<endl;
    table3<< "\\hline"<<endl;
    table3<< "\\multicolumn{7}{|c|}{$\\tauh\\tauh$ decay channel} \\\\"<<endl;
    table3<< "\\hline"<<endl;
    table3<< "\\hline"<<endl;
    table3<< "\\multirow{2}{17mm}{Sample} & \\multicolumn{3}{c|}{$cSVfit, $\\kappa=0$$} & \\multicolumn{3}{c|}{cSVfit, $\\kappa=3$} \\\\"<<endl;
    table3<< "\\cline{2-7}"<<endl;
    table3<< "& $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ \\\\"<<endl;
    table3<< "\\hline"<<endl;

    //Ztautau			    
    table3<< "$\\PZ \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
    table3<<"$\\quad$ $0$-jet              &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(0))<<"$ & $ "<<
	    rounded(vh_SVfitCLAk0.at(0)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(0))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitCLAk.at(0))<<"$ & $ "<<
		    rounded(vh_SVfitCLAk.at(0)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(0))) << "$ & $-$  \\\\" << endl;
    table3<<"$\\quad$ $1$-jet non--boosted &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(1))<<"$ & $ "<<
	    rounded(vh_SVfitCLAk0.at(1)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(1))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitCLAk.at(1))<<"$ & $ "<<
		    rounded(vh_SVfitCLAk.at(1)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(1))) << "$ & $-$  \\\\" << endl;
    table3<<"$\\quad$ $1$-jet boosted      &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(2))<<"$ & $ "<<
	    rounded(vh_SVfitCLAk0.at(2)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(2))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitCLAk.at(2))<<"$ & $ "<<
		    rounded(vh_SVfitCLAk.at(2)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(2))) << "$ & $-$  \\\\" << endl;
    table3<<"$\\quad$ $2$-jet VBF          &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(3))<<"$ & $ "<<
	    rounded(vh_SVfitCLAk0.at(3)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(3))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitCLAk.at(3))<<"$ & $ "<<
		    rounded(vh_SVfitCLAk.at(3)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(3))) << "$ & $-$  \\\\" << endl;
 
    //SM GluGlu		    
    table3<< "SM $\\Pg\\Pg \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl;

    table3<<"$\\quad$ $0$-jet              &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(4))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(4)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(4))) << 
	    "$ & $" << rounded(ratio_SVfitCLAk0_0Jets*100) << "\\pm"<<rounded(err_ratio_SVfitCLAk0_0Jets*100) <<" $ &  $" << AlternativeMedian(vh_SVfitCLAk.at(4))<<"$ & $ "<<
		    rounded(vh_SVfitCLAk.at(4)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(4))) << "$ & $" << rounded(ratio_SVfitCLAk_0Jets*100) << "\\pm"<<rounded(err_ratio_SVfitCLAk_0Jets*100) <<" $ \\\\" << endl;

    table3<<"$\\quad$ $1$-jet non--boosted &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(5))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(5)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(5))) << 
	    "$ & $ " << rounded(ratio_SVfitCLAk0_1JetNonBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitCLAk0_1JetNonBoosted*100) << "$ &  $" << AlternativeMedian(vh_SVfitCLAk.at(5))<<"$ & $ "<<
		    rounded(vh_SVfitCLAk.at(5)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(5))) << "$ & $ " << rounded(ratio_SVfitCLAk_1JetNonBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitCLAk_1JetNonBoosted*100) << " $  \\\\" << endl;

    table3<<"$\\quad$ $1$-jet boosted      &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(6))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(6)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(6))) << 
	    "$ & $ " << rounded(ratio_SVfitCLAk0_1JetBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitCLAk0_1JetBoosted*100) << "$ &  $" << AlternativeMedian(vh_SVfitCLAk.at(6))<<"$ & $ "<<
		    rounded(vh_SVfitCLAk.at(6)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(6))) << "$ & $" << rounded(ratio_SVfitCLAk_1JetBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitCLAk_1JetBoosted*100) <<  "$  \\\\" << endl;

    //SM VBF		    
    table3<< "SM $\\Pquark\\APquark \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & "<<endl; 
    table3<<"$\\quad$ $2$-jet VBF          &  $"<<AlternativeMedian(vh_SVfitCLAk0.at(7))<<"$ & $ "<< rounded(vh_SVfitCLAk0.at(7)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(7))) << 
	    "$ & $ "<< rounded(ratio_SVfitCLAk0_2Jets*100) << "\\pm"<<rounded(err_ratio_SVfitCLAk0_2Jets*100) << "$ &  $" << AlternativeMedian(vh_SVfitCLAk.at(7))<<"$ & $ "<<
		    rounded(vh_SVfitCLAk.at(7)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(7))) << "$ & $" << rounded(ratio_SVfitCLAk_2Jets*100) << "\\pm"<<rounded(err_ratio_SVfitCLAk_2Jets*100) <<  "$  \\\\" << endl;

    table3<<"\\hline"<<endl;
    table3<<"\\end{tabular}\n"<<endl;
    
    int binxmin_SVfitMEMk0_0  = vh_SVfitMEMk0.at(4)->FindBin(Quantile68(vh_SVfitMEMk0.at(4))[0]); int binxmax_SVfitMEMk0_0  = vh_SVfitMEMk0.at(4)->FindBin(Quantile68(vh_SVfitMEMk0.at(4))[1]);
    int binxmin_SVfitMEMk0_10 = vh_SVfitMEMk0.at(5)->FindBin(Quantile68(vh_SVfitMEMk0.at(5))[0]); int binxmax_SVfitMEMk0_10 = vh_SVfitMEMk0.at(5)->FindBin(Quantile68(vh_SVfitMEMk0.at(5))[1]);
    int binxmin_SVfitMEMk0_11 = vh_SVfitMEMk0.at(6)->FindBin(Quantile68(vh_SVfitMEMk0.at(6))[0]); int binxmax_SVfitMEMk0_11 = vh_SVfitMEMk0.at(6)->FindBin(Quantile68(vh_SVfitMEMk0.at(6))[1]);
    int binxmin_SVfitMEMk0_2  = vh_SVfitMEMk0.at(7)->FindBin(Quantile68(vh_SVfitMEMk0.at(7))[0]); int binxmax_SVfitMEMk0_2  = vh_SVfitMEMk0.at(7)->FindBin(Quantile68(vh_SVfitMEMk0.at(7))[1]);
    int binxmin_SVfitMEMk_0   = vh_SVfitMEMk.at(4)->FindBin(Quantile68(vh_SVfitMEMk.at(4))[0]);   int binxmax_SVfitMEMk_0  = vh_SVfitMEMk.at(4)->FindBin(Quantile68(vh_SVfitMEMk.at(4))[1]);
    int binxmin_SVfitMEMk_10  = vh_SVfitMEMk.at(5)->FindBin(Quantile68(vh_SVfitMEMk.at(5))[0]);   int binxmax_SVfitMEMk_10 = vh_SVfitMEMk.at(5)->FindBin(Quantile68(vh_SVfitMEMk.at(5))[1]);
    int binxmin_SVfitMEMk_11  = vh_SVfitMEMk.at(6)->FindBin(Quantile68(vh_SVfitMEMk.at(6))[0]);   int binxmax_SVfitMEMk_11 = vh_SVfitMEMk.at(6)->FindBin(Quantile68(vh_SVfitMEMk.at(6))[1]);
    int binxmin_SVfitMEMk_2   = vh_SVfitMEMk.at(7)->FindBin(Quantile68(vh_SVfitMEMk.at(7))[0]);   int binxmax_SVfitMEMk_2  = vh_SVfitMEMk.at(7)->FindBin(Quantile68(vh_SVfitMEMk.at(7))[1]);
    
    double bkg_SVfitMEMk0_0Jets             = vh_SVfitMEMk0[0]->Integral(binxmin_SVfitMEMk0_0,binxmax_SVfitMEMk0_0)   * dyxs     * CEfactor_visMass_svFit[0];
    double bkg_SVfitMEMk0_1JetNonBoosted    = vh_SVfitMEMk0[1]->Integral(binxmin_SVfitMEMk0_10,binxmax_SVfitMEMk0_10) * dyxs     * CEfactor_visMass_svFit[1];
    double bkg_SVfitMEMk0_1JetBoosted       = vh_SVfitMEMk0[2]->Integral(binxmin_SVfitMEMk0_11,binxmax_SVfitMEMk0_11) * dyxs     * CEfactor_visMass_svFit[2];
    double bkg_SVfitMEMk0_2Jets             = vh_SVfitMEMk0[3]->Integral(binxmin_SVfitMEMk0_2,binxmax_SVfitMEMk0_2)   * dyxs     * CEfactor_visMass_svFit[3];
    double signal_SVfitMEMk0_0Jets          = vh_SVfitMEMk0[4]->Integral(binxmin_SVfitMEMk0_0,binxmax_SVfitMEMk0_0)   * glugluxs * CEfactor_visMass_svFit[4];
    double signal_SVfitMEMk0_1JetNonBoosted = vh_SVfitMEMk0[5]->Integral(binxmin_SVfitMEMk0_10,binxmax_SVfitMEMk0_10) * glugluxs * CEfactor_visMass_svFit[5];
    double signal_SVfitMEMk0_1JetBoosted    = vh_SVfitMEMk0[6]->Integral(binxmin_SVfitMEMk0_11,binxmax_SVfitMEMk0_11) * glugluxs * CEfactor_visMass_svFit[6];
    double signal_SVfitMEMk0_2Jets          = vh_SVfitMEMk0[7]->Integral(binxmin_SVfitMEMk0_2,binxmax_SVfitMEMk0_2)   * vbfxs    * CEfactor_visMass_svFit[7];
    
    double bkg_SVfitMEMk_0Jets             = vh_SVfitMEMk[0]->Integral(binxmin_SVfitMEMk_0,binxmax_SVfitMEMk_0)   * dyxs     * CEfactor_visMass_svFit[0];
    double bkg_SVfitMEMk_1JetNonBoosted    = vh_SVfitMEMk[1]->Integral(binxmin_SVfitMEMk_10,binxmax_SVfitMEMk_10) * dyxs     * CEfactor_visMass_svFit[1];
    double bkg_SVfitMEMk_1JetBoosted       = vh_SVfitMEMk[2]->Integral(binxmin_SVfitMEMk_11,binxmax_SVfitMEMk_11) * dyxs     * CEfactor_visMass_svFit[2];
    double bkg_SVfitMEMk_2Jets             = vh_SVfitMEMk[3]->Integral(binxmin_SVfitMEMk_2,binxmax_SVfitMEMk_2)   * dyxs     * CEfactor_visMass_svFit[3];
    double signal_SVfitMEMk_0Jets          = vh_SVfitMEMk[4]->Integral(binxmin_SVfitMEMk_0,binxmax_SVfitMEMk_0)   * glugluxs * CEfactor_visMass_svFit[4];
    double signal_SVfitMEMk_1JetNonBoosted = vh_SVfitMEMk[5]->Integral(binxmin_SVfitMEMk_10,binxmax_SVfitMEMk_10) * glugluxs * CEfactor_visMass_svFit[5];
    double signal_SVfitMEMk_1JetBoosted    = vh_SVfitMEMk[6]->Integral(binxmin_SVfitMEMk_11,binxmax_SVfitMEMk_11) * glugluxs * CEfactor_visMass_svFit[6];
    double signal_SVfitMEMk_2Jets          = vh_SVfitMEMk[7]->Integral(binxmin_SVfitMEMk_2,binxmax_SVfitMEMk_2)   * vbfxs    * CEfactor_visMass_svFit[7];

    double ratio_SVfitMEMk0_0Jets             = signal_SVfitMEMk0_0Jets / ( signal_SVfitMEMk0_0Jets + bkg_SVfitMEMk0_0Jets );
    double ratio_SVfitMEMk0_1JetNonBoosted    = signal_SVfitMEMk0_1JetNonBoosted / ( signal_SVfitMEMk0_1JetNonBoosted + bkg_SVfitMEMk0_1JetNonBoosted );
    double ratio_SVfitMEMk0_1JetBoosted       = signal_SVfitMEMk0_1JetBoosted / ( signal_SVfitMEMk0_1JetBoosted + bkg_SVfitMEMk0_1JetBoosted );
    double ratio_SVfitMEMk0_2Jets             = signal_SVfitMEMk0_2Jets / ( signal_SVfitMEMk0_2Jets + bkg_SVfitMEMk0_2Jets );
    double ratio_SVfitMEMk_0Jets             = signal_SVfitMEMk_0Jets / ( signal_SVfitMEMk_0Jets + bkg_SVfitMEMk_0Jets );
    double ratio_SVfitMEMk_1JetNonBoosted    = signal_SVfitMEMk_1JetNonBoosted / ( signal_SVfitMEMk_1JetNonBoosted + bkg_SVfitMEMk_1JetNonBoosted );
    double ratio_SVfitMEMk_1JetBoosted       = signal_SVfitMEMk_1JetBoosted / ( signal_SVfitMEMk_1JetBoosted + bkg_SVfitMEMk_1JetBoosted );
    double ratio_SVfitMEMk_2Jets             = signal_SVfitMEMk_2Jets / ( signal_SVfitMEMk_2Jets + bkg_SVfitMEMk_2Jets );
    
    double err_ratio_SVfitMEMk_0Jets = ComputeStatisticalError(binxmin_SVfitMEMk_0,binxmax_SVfitMEMk_0,vh_SVfitMEMk[4],vh_SVfitMEMk[0],glugluxs,dyxs,CEfactor_CsvFit[4],CEfactor_CsvFit[0]);
    double err_ratio_SVfitMEMk_1JetNonBoosted = ComputeStatisticalError(binxmin_SVfitMEMk_10,binxmax_SVfitMEMk_10,vh_SVfitMEMk[5],vh_SVfitMEMk[1],glugluxs,dyxs,CEfactor_CsvFit[5],CEfactor_CsvFit[1]);
    double err_ratio_SVfitMEMk_1JetBoosted = ComputeStatisticalError(binxmin_SVfitMEMk_11,binxmax_SVfitMEMk_11,vh_SVfitMEMk[6],vh_SVfitMEMk[2],glugluxs,dyxs,CEfactor_CsvFit[6],CEfactor_CsvFit[2]);
    double err_ratio_SVfitMEMk_2Jets = ComputeStatisticalError(binxmin_SVfitMEMk_2,binxmax_SVfitMEMk_2,vh_SVfitMEMk[7],vh_SVfitMEMk[3],vbfxs,dyxs,CEfactor_CsvFit[7],CEfactor_CsvFit[3]);
    double err_ratio_SVfitMEMk0_0Jets = ComputeStatisticalError(binxmin_SVfitMEMk0_0,binxmax_SVfitMEMk0_0,vh_SVfitMEMk0[4],vh_SVfitMEMk0[0],glugluxs,dyxs,CEfactor_CsvFit[4],CEfactor_CsvFit[0]);
    double err_ratio_SVfitMEMk0_1JetNonBoosted = ComputeStatisticalError(binxmin_SVfitMEMk0_10,binxmax_SVfitMEMk0_10,vh_SVfitMEMk0[5],vh_SVfitMEMk0[1],glugluxs,dyxs,CEfactor_CsvFit[5],CEfactor_CsvFit[1]);
    double err_ratio_SVfitMEMk0_1JetBoosted = ComputeStatisticalError(binxmin_SVfitMEMk0_11,binxmax_SVfitMEMk0_11,vh_SVfitMEMk0[6],vh_SVfitMEMk0[2],glugluxs,dyxs,CEfactor_CsvFit[6],CEfactor_CsvFit[2]);
    double err_ratio_SVfitMEMk0_2Jets = ComputeStatisticalError(binxmin_SVfitMEMk0_2,binxmax_SVfitMEMk0_2,vh_SVfitMEMk0[7],vh_SVfitMEMk0[3],vbfxs,dyxs,CEfactor_CsvFit[7],CEfactor_CsvFit[3]);
    
    table3<< "\\begin{tabular}{|l|ccc|ccc|}"<<endl;
   
    table3<< "\\begin{tabular}{|l|ccc|ccc|}"<<endl;
    table3<< "\\hline"<<endl;
    table3<< "\\multicolumn{7}{|c|}{$\\tauh\\tauh$ decay channel} \\\\"<<endl;
    table3<< "\\hline"<<endl;
    table3<< "\\hline"<<endl;
    table3<< "\\multirow{2}{17mm}{Sample} & \\multicolumn{3}{c|}{$SVfitMEM, $\\kappa=0$$} & \\multicolumn{3}{c|}{SVfitMEM, $\\kappa=3$} \\\\"<<endl;
    table3<< "\\cline{2-7}"<<endl;
    table3<< "& $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $S/\\sqrt{B}$ \\\\"<<endl;
    table3<< "\\hline"<<endl;

    //Ztautau			    
    table3<< "$\\PZ \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
    table3<<"$\\quad$ $0$-jet              &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(0))<<"$ & $ "<<
	    rounded(vh_SVfitMEMk0.at(0)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(0))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitMEMk.at(0))<<"$ & $ "<<
		    rounded(vh_SVfitMEMk.at(0)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(0))) << "$ & $-$  \\\\" << endl;
    table3<<"$\\quad$ $1$-jet non--boosted &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(1))<<"$ & $ "<<
	    rounded(vh_SVfitMEMk0.at(1)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(1))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitMEMk.at(1))<<"$ & $ "<<
		    rounded(vh_SVfitMEMk.at(1)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(1))) << "$ & $-$  \\\\" << endl;
    table3<<"$\\quad$ $1$-jet boosted      &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(2))<<"$ & $ "<<
	    rounded(vh_SVfitMEMk0.at(2)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(2))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitMEMk.at(2))<<"$ & $ "<<
		    rounded(vh_SVfitMEMk.at(2)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(2))) << "$ & $-$  \\\\" << endl;
    table3<<"$\\quad$ $2$-jet VBF          &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(3))<<"$ & $ "<<
	    rounded(vh_SVfitMEMk0.at(3)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(3))) << "$ & $-$ &  $" << AlternativeMedian(vh_SVfitMEMk.at(3))<<"$ & $ "<<
		    rounded(vh_SVfitMEMk.at(3)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(3))) << "$ & $-$  \\\\" << endl;
    
    //SM GluGlu		    
    table3<< "SM $\\Pg\\Pg \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
    
    table3<<"$\\quad$ $0$-jet              &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(4))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(4)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(4))) << 
	    "$ & $" << rounded(ratio_SVfitMEMk0_0Jets*100) << "\\pm"<<rounded(err_ratio_SVfitMEMk0_0Jets*100) <<" $ &  $" << AlternativeMedian(vh_SVfitMEMk.at(4))<<"$ & $ "<<
		    rounded(vh_SVfitMEMk.at(4)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(4))) << "$ & $" << rounded(ratio_SVfitMEMk_0Jets*100) << "\\pm"<<rounded(err_ratio_SVfitMEMk_0Jets*100) <<" $ \\\\" << endl;

    table3<<"$\\quad$ $1$-jet non--boosted &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(5))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(5)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(5))) << 
	    "$ & $ " << rounded(ratio_SVfitMEMk0_1JetNonBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitMEMk0_1JetNonBoosted*100) << "$ &  $" << AlternativeMedian(vh_SVfitMEMk.at(5))<<"$ & $ "<<
		    rounded(vh_SVfitMEMk.at(5)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(5))) << "$ & $ " << rounded(ratio_SVfitMEMk_1JetNonBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitMEMk_1JetNonBoosted*100) << " $  \\\\" << endl;

    table3<<"$\\quad$ $1$-jet boosted      &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(6))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(6)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(6))) << 
	    "$ & $ " << rounded(ratio_SVfitMEMk0_1JetBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitMEMk0_1JetBoosted*100) << "$ &  $" << AlternativeMedian(vh_SVfitMEMk.at(6))<<"$ & $ "<<
		    rounded(vh_SVfitMEMk.at(6)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(6))) << "$ & $" << rounded(ratio_SVfitMEMk_1JetBoosted*100) << "\\pm"<<rounded(err_ratio_SVfitMEMk_1JetBoosted*100) <<  "$  \\\\" << endl;

    //SM VBF		    
    table3<< "SM $\\Pquark\\APquark \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & "<<endl; 
    table3<<"$\\quad$ $2$-jet VBF          &  $"<<AlternativeMedian(vh_SVfitMEMk0.at(7))<<"$ & $ "<< rounded(vh_SVfitMEMk0.at(7)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(7))) << 
	    "$ & $ "<< rounded(ratio_SVfitMEMk0_2Jets*100) << "\\pm"<<rounded(err_ratio_SVfitMEMk0_2Jets*100) << "$ &  $" << AlternativeMedian(vh_SVfitMEMk.at(7))<<"$ & $ "<<
		    rounded(vh_SVfitMEMk.at(7)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(7))) << "$ & $" << rounded(ratio_SVfitMEMk_2Jets*100) << "\\pm"<<rounded(err_ratio_SVfitMEMk_2Jets*100) <<  "$  \\\\" << endl;

    table3<<"\\hline"<<endl;
    table3<<"\\end{tabular}\n"<<endl;
    table3<<"\\end{table}\n"<<endl;

  table3.close();

} // void
