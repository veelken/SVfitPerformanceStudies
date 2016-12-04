#include "func.C"
#include <fstream>
#include <vector>
#include <math.h>

double AlternativeMedian(const TH1D * h1);
std::string rounded_1digit(double val);
std::string rounded_3digits(double val);

void table6_emu(){

  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  // write table
  cout<<"writing table...\n";

  //string inputPath {"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_V"};
  string inputPath {"/home/veelken/SVfitMEM_paper_v2/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_V/"};
  string savePath {"/home/veelken/SVfitMEM_paper_v2/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot"};

  // root file
  vector<string> vinput {
          "hist_smeared_SUSYGluGluToHToTauTauM200_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM300_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM500_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM800_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM1200_inclusive.root",
          "hist_smeared_SUSYGluGluToHToTauTauM1800_inclusive.root",
	  "hist_smeared_SUSYGluGluToHToTauTauM2600_inclusive.root",
          "hist_smeared_ZprimeToTauTauM2500_inclusive.root"
  };

  vector<string>vsample{
          "SUSYGluGluToHToTauTauM200",
          "SUSYGluGluToHToTauTauM300",
          "SUSYGluGluToHToTauTauM500",
          "SUSYGluGluToHToTauTauM800",
          "SUSYGluGluToHToTauTauM1200",
          "SUSYGluGluToHToTauTauM1800",
          "SUSYGluGluToHToTauTauM2600",
          "ZprimeToTauTauM2500"
  };

  assert(vinput.size() == vsample.size());

  func();

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

	  string sample = vsample[in];
	  std::cout << "sample = " << sample << std::endl;

	  string mass_string = std::string(sample, sample.find_last_of("M")+1);
	  double mass = atof(mass_string.data());
	  std::cout << "mass = " << mass << std::endl;

	  // loop over hist
	  TIter nextHist(file->GetListOfKeys());
	  TKey* histKey(0);
	  while ((histKey=(TKey*)nextHist())) {
		  if (strcmp(histKey->GetClassName(),"TH1D")!=0) continue;
		  TH1D* hmass = (TH1D*)histKey->ReadObj();
		  TH1D* hmass_cloned = (TH1D*)hmass->Clone();
		  //TAxis* xAxis = hmass_cloned->GetXaxis();
		  //xAxis->SetRangeUser(0., 5.);
		  string histname(hmass->GetName());
		  // hist name match directory name
		  if(histname == "emu_smeared_vismass_ratio_fine_bin")         vh_mvis.push_back(hmass_cloned);
		  if(histname == "emu_smeared_svFit_ratio_fine_bin")           vh_SVfitSA.push_back(hmass_cloned);
		  if(histname == "emu_smeared_svfitmemtfk0_ratio_fine_bin")    vh_SVfitMEMk0.push_back(hmass_cloned);
		  if(histname == "emu_smeared_svfitclatfk0_ratio_fine_bin")    vh_SVfitCLAk0.push_back(hmass_cloned);
		  if(histname == "emu_smeared_svfitmemtfk3_ratio_fine_bin")    vh_SVfitMEMk.push_back(hmass_cloned);
		  if(histname == "emu_smeared_svfitclatfk3_ratio_fine_bin")    vh_SVfitCLAk.push_back(hmass_cloned);
	  }
  }
  
  ofstream table6;
  table6.open("table6_emu.txt");

  //table6 << "\\begin{table}" << endl;
  table6 << "\\begin{center}" << endl;

    ///////////////////// latex table //////////////////
    table6 << "\\begin{tabular}{|l|C{1.5cm}C{1.5cm}|C{1.5cm}C{1.5cm}|}" << endl;
    table6 << "\\hline" << endl;
    table6 << "\\multicolumn{5}{|c|}{$\\Pe\\Pgm$ decay channel} \\\\" << endl;
    table6 << "\\hline" << endl;
    table6 << "\\hline" << endl;
    table6 << "\\multirow{2}{17mm}{Sample} & \\multicolumn{2}{c|}{$m_{\\vis}$} & \\multicolumn{2}{c|}{SVfitSA} \\\\" << endl;
    table6 << "\\cline{2-5}" << endl;
    table6 << " & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ \\\\" << endl;
    table6 << "\\hline" << endl;
    
    table6 << "$\\PHiggsps \\to \\Pgt\\Pgt$: & & & & \\\\ "<<endl; 
    table6 << "$\\quad m_{\\PHiggsps} = 200$~\\GeV  & $" 
	   << rounded_1digit(200.*AlternativeMedian(vh_mvis.at(0))) << "$ & $ "
	   << rounded_3digits(vh_mvis.at(0)->GetRMS()/AlternativeMedian(vh_mvis.at(0))) << " $ & $" 
	   << rounded_1digit(200.*AlternativeMedian(vh_SVfitSA.at(0))) << "$ & $ "
	   << rounded_3digits(vh_SVfitSA.at(0)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(0))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 300$~\\GeV  & $"
	   << rounded_1digit(300.*AlternativeMedian(vh_mvis.at(1))) << "$ & $ "
	   << rounded_3digits(vh_mvis.at(1)->GetRMS()/AlternativeMedian(vh_mvis.at(1))) << " $ & $" 
	   << rounded_1digit(300.*AlternativeMedian(vh_SVfitSA.at(1))) << "$ & $ "
	   << rounded_3digits(vh_SVfitSA.at(1)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(1))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 500$~\\GeV  & $"
	   << rounded_1digit(500.*AlternativeMedian(vh_mvis.at(2))) << "$ & $ "
	   << rounded_3digits(vh_mvis.at(2)->GetRMS()/AlternativeMedian(vh_mvis.at(2))) << " $ & $" 
	   << rounded_1digit(500.*AlternativeMedian(vh_SVfitSA.at(2))) << "$ & $ "
	   << rounded_3digits(vh_SVfitSA.at(2)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(2))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 800$~\\GeV  & $"
	   << rounded_1digit(800.*AlternativeMedian(vh_mvis.at(3))) << "$ & $ "
	   << rounded_3digits(vh_mvis.at(3)->GetRMS()/AlternativeMedian(vh_mvis.at(3))) << " $ & $" 
	   << rounded_1digit(800.*AlternativeMedian(vh_SVfitSA.at(3))) << "$ & $ "
	   << rounded_3digits(vh_SVfitSA.at(3)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(3))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 1200$~\\GeV & $"
	   << rounded_1digit(1200.*AlternativeMedian(vh_mvis.at(4))) << "$ & $ "
	   << rounded_3digits(vh_mvis.at(4)->GetRMS()/AlternativeMedian(vh_mvis.at(4))) << " $ & $" 
	   << rounded_1digit(1200.*AlternativeMedian(vh_SVfitSA.at(4))) << "$ & $ "
	   << rounded_3digits(vh_SVfitSA.at(4)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(4))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 1800$~\\GeV & $"
	   << rounded_1digit(1800.*AlternativeMedian(vh_mvis.at(5))) << "$ & $ "
	   << rounded_3digits(vh_mvis.at(5)->GetRMS()/AlternativeMedian(vh_mvis.at(5))) << " $ & $" 
	   << rounded_1digit(1800.*AlternativeMedian(vh_SVfitSA.at(5))) << "$ & $ "
	   << rounded_3digits(vh_SVfitSA.at(5)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(5))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 2600$~\\GeV & $"
	   << rounded_1digit(2600.*AlternativeMedian(vh_mvis.at(6))) << "$ & $ "
	   << rounded_3digits(vh_mvis.at(6)->GetRMS()/AlternativeMedian(vh_mvis.at(6))) << " $ & $" 
	   << rounded_1digit(2600.*AlternativeMedian(vh_SVfitSA.at(6))) << "$ & $ "
	   << rounded_3digits(vh_SVfitSA.at(6)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(6))) << "$ \\\\" << endl;
    table6 << "$\\PZ' \\to \\Pgt\\Pgt$: & & & & \\\\ " << endl;
    table6 << "$\\quad m_{\\PZ'} = 2500$~\\GeV      & $"
	   << rounded_1digit(2500.*AlternativeMedian(vh_mvis.at(7))) << "$ & $ "
	   << rounded_3digits(vh_mvis.at(7)->GetRMS()/AlternativeMedian(vh_mvis.at(7))) << " $ & $" 
	   << rounded_1digit(2500.*AlternativeMedian(vh_SVfitSA.at(7))) << "$ & $ "
	   << rounded_3digits(vh_SVfitSA.at(7)->GetRMS()/AlternativeMedian(vh_SVfitSA.at(7))) << "$ \\\\" << endl;
    
    table6 << "\\hline" << endl;
    table6 << "\\end{tabular}" << endl;
    table6 << endl;
    table6 << "\\begin{tabular}{|l|C{1.5cm}C{1.5cm}|C{1.5cm}C{1.5cm}|}" << endl;
    table6 << "\\hline" << endl;
    table6 << "\\multirow{2}{17mm}{Sample} & \\multicolumn{2}{c|}{cSVfit, $\\kappa=0$} & \\multicolumn{2}{c|}{cSVfit, $\\kappa=3$} \\\\" << endl;
    table6 << "\\cline{2-5}" << endl;
    table6 << " & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ \\\\" << endl;
    table6 << "\\hline" << endl;

    table6 << "$\\PHiggsps \\to \\Pgt\\Pgt$: & & & & \\\\ " << endl; 
    table6 << "$\\quad m_{\\PHiggsps} = 200$~\\GeV  & $"
	   << rounded_1digit(200.*AlternativeMedian(vh_SVfitCLAk0.at(0))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk0.at(0)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(0))) << "$ & $ "
	   << rounded_1digit(200.*AlternativeMedian(vh_SVfitCLAk.at(0))) << " $ & $" 
	   << rounded_3digits(vh_SVfitCLAk.at(0)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(0))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 300$~\\GeV  & $"
	   << rounded_1digit(300.*AlternativeMedian(vh_SVfitCLAk0.at(1))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk0.at(1)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(1))) << "$ & $ "
	   << rounded_1digit(300.*AlternativeMedian(vh_SVfitCLAk.at(1))) << " $ & $" 
	   << rounded_3digits(vh_SVfitCLAk.at(1)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(1))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 500$~\\GeV  & $"
	   << rounded_1digit(500.*AlternativeMedian(vh_SVfitCLAk0.at(2))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk0.at(2)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(2))) << " $ & $" 
	   << rounded_1digit(500.*AlternativeMedian(vh_SVfitCLAk.at(2))) << " $ & $" 
	   << rounded_3digits(vh_SVfitCLAk.at(2)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(2))) << "$  \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 800$~\\GeV  & $" 
	   << rounded_1digit(800.*AlternativeMedian(vh_SVfitCLAk0.at(3))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk0.at(3)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(3))) << " $ & $" 
	   << rounded_1digit(800.*AlternativeMedian(vh_SVfitCLAk.at(3))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk.at(3)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(3))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 1200$~\\GeV & $"
	   << rounded_1digit(1200.*AlternativeMedian(vh_SVfitCLAk0.at(4))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk0.at(4)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(4))) << " $ & $" 
	   << rounded_1digit(1200.*AlternativeMedian(vh_SVfitCLAk.at(4))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk.at(4)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(4))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 1800$~\\GeV & $"
	   << rounded_1digit(1800.*AlternativeMedian(vh_SVfitCLAk0.at(5))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk0.at(5)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(5))) << " $ & $" 
	   << rounded_1digit(1800.*AlternativeMedian(vh_SVfitCLAk.at(5))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk.at(5)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(5))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 2600$~\\GeV & $"
	   << rounded_1digit(2600.*AlternativeMedian(vh_SVfitCLAk0.at(6))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk0.at(6)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(6))) << " $ & $" 
	   << rounded_1digit(2600.*AlternativeMedian(vh_SVfitCLAk.at(6))) << "$ & $ " 
	   << rounded_3digits(vh_SVfitCLAk.at(6)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(6))) << "$ \\\\" << endl;
    table6 << "$\\PZ' \\to \\Pgt\\Pgt$: & & & & \\\\ " << endl;
    table6 << "$\\quad m_{\\PZ'} = 2500$~\\GeV      & $"
	   << rounded_1digit(2500.*AlternativeMedian(vh_SVfitCLAk0.at(7))) << "$ & $ "
	   << rounded_3digits(vh_SVfitCLAk0.at(7)->GetRMS()/AlternativeMedian(vh_SVfitCLAk0.at(7))) << " $ & $" 
	   << rounded_1digit(2500.*AlternativeMedian(vh_SVfitCLAk.at(7))) << "$ & $ " 
	   << rounded_3digits(vh_SVfitCLAk.at(7)->GetRMS()/AlternativeMedian(vh_SVfitCLAk.at(7))) << "$ \\\\" << endl;

    table6 << "\\hline" << endl;
    table6 << "\\end{tabular}" << endl;
    table6 << endl;
    table6 << "\\begin{tabular}{|l|C{1.5cm}C{1.5cm}|C{1.5cm}C{1.5cm}|}" << endl;
    table6 << "\\hline" << endl;
    table6 << "\\multirow{2}{17mm}{Sample} & \\multicolumn{2}{c|}{SVfitMEM, $\\kappa=0$} & \\multicolumn{2}{c|}{SVfitMEM, $\\kappa=3$} \\\\" << endl;
    table6 << "\\cline{2-5}" << endl;
    table6 << " & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ & $\\textrm{M}$~[\\GeV\\unskip] & $\\sigma/\\textrm{M}$ \\\\" << endl;
    table6 << "\\hline" << endl;
    
    table6 << "$\\PHiggsps \\to \\Pgt\\Pgt$: & & & & \\\\ "<<endl; 
    table6 << "$\\quad m_{\\PHiggsps} = 200$~\\GeV  & $"
	   << rounded_1digit(200.*AlternativeMedian(vh_SVfitMEMk0.at(0))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk0.at(0)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(0))) << "$ & $ " 
	   << rounded_1digit(200.*AlternativeMedian(vh_SVfitMEMk.at(0))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk.at(0)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(0))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 300$~\\GeV  & $"
	   << rounded_1digit(300.*AlternativeMedian(vh_SVfitMEMk0.at(1))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk0.at(1)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(1))) << " $ & $" 
	   << rounded_1digit(300.*AlternativeMedian(vh_SVfitMEMk.at(1))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk.at(1)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(1))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 500$~\\GeV  & $"
	   << rounded_1digit(500.*AlternativeMedian(vh_SVfitMEMk0.at(2))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk0.at(2)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(2))) << "$ & $ "
	   << rounded_1digit(500.*AlternativeMedian(vh_SVfitMEMk.at(2))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk.at(2)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(2))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 800$~\\GeV  & $"
	   << rounded_1digit(800.*AlternativeMedian(vh_SVfitMEMk0.at(3))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk0.at(3)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(3))) << "$ & $ " 
	   << rounded_1digit(800.*AlternativeMedian(vh_SVfitMEMk.at(3))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk.at(3)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(3))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 1200$~\\GeV & $"
	   << rounded_1digit(1200.*AlternativeMedian(vh_SVfitMEMk0.at(4))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk0.at(4)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(4))) << "$ & $ " 
	   << rounded_1digit(1200.*AlternativeMedian(vh_SVfitMEMk.at(4))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk.at(4)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(4))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 1800$~\\GeV & $"
	   << rounded_1digit(1800.*AlternativeMedian(vh_SVfitMEMk0.at(5))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk0.at(5)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(5))) << "$ & $ " 
	   << rounded_1digit(1800.*AlternativeMedian(vh_SVfitMEMk.at(5))) << "$ & $ " 
	   << rounded_3digits(vh_SVfitMEMk.at(5)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(5))) << "$ \\\\" << endl;
    table6 << "$\\quad m_{\\PHiggsps} = 2600$~\\GeV & $"
	   << rounded_1digit(2600.*AlternativeMedian(vh_SVfitMEMk0.at(6))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk0.at(6)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(6))) << "$ & $ " 
	   << rounded_1digit(2600.*AlternativeMedian(vh_SVfitMEMk.at(6))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk.at(6)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(6))) << "$ \\\\" << endl;
    table6 << "$\\PZ' \\to \\Pgt\\Pgt$: & & & & \\\\ " << endl;
    table6 << "$\\quad m_{\\PZ'} = 2500$~\\GeV      & $"
	   << rounded_1digit(2500.*AlternativeMedian(vh_SVfitMEMk0.at(7))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk0.at(7)->GetRMS()/AlternativeMedian(vh_SVfitMEMk0.at(7))) << "$ & $ " 
	   << rounded_1digit(2500.*AlternativeMedian(vh_SVfitMEMk.at(7))) << "$ & $ "
	   << rounded_3digits(vh_SVfitMEMk.at(7)->GetRMS()/AlternativeMedian(vh_SVfitMEMk.at(7))) << "$ \\\\" << endl;

    table6 << "\\hline" << endl;
    table6 << "\\end{tabular}" << endl;
    table6 << "\\end{center}" << endl;
    //table6 << "\\end{table}" << endl;

  table6.close();

} // void
