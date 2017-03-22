#include "func.C"
#include <fstream>
#include <vector>
#include <math.h>

void table4_hadhad()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

  // write table
  cout<<"writing table...\n";

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
  for ( int in = 0; in < vinput.size(); ++in ){ 
    string input{inputPath + "/" + vinput[in]};
    TFile* file = new TFile(input.c_str(), "READ");

    string sample = vsample[in];
    std::cout << "sample = " << sample << std::endl;

    string mass_string = std::string(sample, sample.find_last_of("M")+1);
    double mass = atof(mass_string.data());
    std::cout << "mass = " << mass << std::endl;

    // loop over hist
    TIter nextHist(file->GetListOfKeys());
    TKey* histKey(0);
    while ( (histKey = (TKey*)nextHist()) ) {
      if ( strcmp(histKey->GetClassName(),"TH1D") != 0 ) continue;
      TH1D* hmass = (TH1D*)histKey->ReadObj();
      TH1D* hmass_cloned = (TH1D*)hmass->Clone();
      //TAxis* xAxis = hmass_cloned->GetXaxis();
      //xAxis->SetRangeUser(0., 5.);
      string histname(hmass->GetName());
      // hist name match directory name
      if ( histname == "hadhad_smeared_vismass_ratio_fine_bin"      ) vh_mvis.push_back(hmass_cloned);
      if ( histname == "hadhad_smeared_svFit_ratio_fine_bin"        ) vh_SVfitSA.push_back(hmass_cloned);
      if ( histname == "hadhad_smeared_svfitmemtfk0_ratio_fine_bin" ) vh_SVfitMEMk0.push_back(hmass_cloned);
      if ( histname == "hadhad_smeared_svfitclatfk0_ratio_fine_bin" ) vh_SVfitCLAk0.push_back(hmass_cloned);
      if ( histname == "hadhad_smeared_svfitmemtfk5_ratio_fine_bin" ) vh_SVfitMEMk.push_back(hmass_cloned);
      if ( histname == "hadhad_smeared_svfitclatfk5_ratio_fine_bin" ) vh_SVfitCLAk.push_back(hmass_cloned);
    }
    
    delete file;
  }
  
  assert(vh_mvis.size() == vsample.size());
  assert(vh_SVfitSA.size() == vsample.size());
  assert(vh_SVfitMEMk0.size() == vsample.size());
  assert(vh_SVfitMEMk.size() == vsample.size());
  assert(vh_SVfitCLAk0.size() == vsample.size());
  assert(vh_SVfitCLAk.size() == vsample.size());

  ofstream table4;
  table4.open("table4_hadhad.txt");

  table4 << "\\begin{table}" << endl;
  table4 << "\\begin{center}" << endl;

  //-----------------------------------------------------------------------------
  // mVis and SVfitSA
  table4 << "\\begin{tabular}{|l|ccc|ccc|}" << endl;
  //table4 << "\\begin{tabular}{|l|C{1.2cm}C{1.2cm}C{1.2cm}|C{1.2cm}C{1.2cm}C{1.2cm}|}" << endl;
  table4 << "\\hline" << endl;
  table4 << "\\multicolumn{7}{|c|}{$\\tauh\\tauh$ decay channel} \\\\" << endl;
  table4 << "\\hline" << endl;
  table4 << "\\hline" << endl;
  table4 << "\\multirow{2}{17mm}{Sample} & \\multicolumn{3}{c|}{$m_{\\vis}$} & \\multicolumn{3}{c|}{SVfitSA} \\\\" << endl;
  table4 << "\\cline{2-7}" << endl;
  table4 << " & " 
	 << "$\\textrm{M}$~[\\GeV\\unskip] & "
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ & " 
	 << "$\\textrm{M}$~[\\GeV\\unskip] & " 
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ \\\\" << endl;
  table4 << "\\hline" << endl;
    
  // MSSM Higgs->tautau			    
  table4 << "$\\PHiggsps \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 200$~\\GeV", 200.,
    vh_mvis.at(0), vh_SVfitSA.at(0));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 300$~\\GeV", 300.,
    vh_mvis.at(1), vh_SVfitSA.at(1));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 500$~\\GeV", 500.,
    vh_mvis.at(2), vh_SVfitSA.at(2));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 800$~\\GeV", 800.,
    vh_mvis.at(3), vh_SVfitSA.at(3));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 1200$~\\GeV", 1200.,
    vh_mvis.at(4), vh_SVfitSA.at(4));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 1800$~\\GeV", 1800.,
    vh_mvis.at(5), vh_SVfitSA.at(5));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 2600$~\\GeV", 2600.,
    vh_mvis.at(6), vh_SVfitSA.at(6));

  // Z'->tautau	
  table4 << "$\\PZ' \\to \\Pgt\\Pgt$: & & & & & & \\\\ " << endl;
  addRow_woSoB_mssm(table4, "$m_{\\PZ'} = 2500$~\\GeV", 2500.,
    vh_mvis.at(7), vh_SVfitSA.at(7));
  
  table4 << "\\hline" << endl;
  table4 << "\\end{tabular}\n" << endl;
  //-----------------------------------------------------------------------------
  
  //-----------------------------------------------------------------------------
  // cSVfit (zero and non-zero kappa)
  table4 << "\\begin{tabular}{|l|ccc|ccc|}" << endl;
  //table4 << "\\begin{tabular}{|l|C{1.2cm}C{1.2cm}C{1.2cm}|C{1.2cm}C{1.2cm}C{1.2cm}|}" << endl;
  table4 << "\\hline" << endl;
  table4 << "\\multirow{2}{17mm}{Sample} & \\multicolumn{3}{c|}{cSVfit, $\\kappa=0$} & \\multicolumn{3}{c|}{cSVfit, $\\kappa=5$} \\\\" << endl;
  table4 << "\\cline{2-7}" << endl;
  table4 << " & " 
	 << "$\\textrm{M}$~[\\GeV\\unskip] & "
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ & " 
	 << "$\\textrm{M}$~[\\GeV\\unskip] & " 
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ \\\\" << endl;
  table4 << "\\hline" << endl;
    
  // MSSM Higgs->tautau			    
  table4 << "$\\PHiggsps \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 200$~\\GeV", 200.,
    vh_SVfitCLAk0.at(0), vh_SVfitCLAk.at(0));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 300$~\\GeV", 300.,
    vh_SVfitCLAk0.at(1), vh_SVfitCLAk.at(1));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 500$~\\GeV", 500.,
    vh_SVfitCLAk0.at(2), vh_SVfitCLAk.at(2));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 800$~\\GeV", 800.,
    vh_SVfitCLAk0.at(3), vh_SVfitCLAk.at(3));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 1200$~\\GeV", 1200.,
    vh_SVfitCLAk0.at(4), vh_SVfitCLAk.at(4));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 1800$~\\GeV", 1800.,
    vh_SVfitCLAk0.at(5), vh_SVfitCLAk.at(5));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 2600$~\\GeV", 2600.,
    vh_SVfitCLAk0.at(6), vh_SVfitCLAk.at(6));
  
  // Z'->tautau	
  table4 << "$\\PZ' \\to \\Pgt\\Pgt$: & & & & & & \\\\ " << endl;
  addRow_woSoB_mssm(table4, "$m_{\\PZ'} = 2500$~\\GeV", 2500.,
    vh_SVfitCLAk0.at(7), vh_SVfitCLAk.at(7));
  
  table4 << "\\hline" << endl;
  table4 << "\\end{tabular}\n" << endl;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // SVfitMEM (zero and non-zero kappa)
  table4 << "\\begin{tabular}{|l|ccc|ccc|}" << endl;
  //table4 << "\\begin{tabular}{|l|C{1.2cm}C{1.2cm}C{1.2cm}|C{1.2cm}C{1.2cm}C{1.2cm}|}" << endl;
  table4 << "\\hline" << endl;
  table4 << "\\multirow{2}{17mm}{Sample} & \\multicolumn{3}{c|}{SVfitMEM, $\\kappa=0$} & \\multicolumn{3}{c|}{SVfitMEM, $\\kappa=5$} \\\\" << endl;
  table4 << "\\cline{2-7}" << endl;
  table4 << " & " 
	 << "$\\textrm{M}$~[\\GeV\\unskip] & "
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ & " 
	 << "$\\textrm{M}$~[\\GeV\\unskip] & " 
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ \\\\" << endl;
  table4 << "\\hline" << endl;

  // MSSM Higgs->tautau			    
  table4 << "$\\PHiggsps \\to \\Pgt\\Pgt$: & & & & & & \\\\ "<<endl; 
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 200$~\\GeV", 200.,
    vh_SVfitMEMk0.at(0), vh_SVfitMEMk.at(0));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 300$~\\GeV", 300.,
    vh_SVfitMEMk0.at(1), vh_SVfitMEMk.at(1));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 500$~\\GeV", 500.,
    vh_SVfitMEMk0.at(2), vh_SVfitMEMk.at(2));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 800$~\\GeV", 800.,
    vh_SVfitMEMk0.at(3), vh_SVfitMEMk.at(3));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 1200$~\\GeV", 1200.,
    vh_SVfitMEMk0.at(4), vh_SVfitMEMk.at(4));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 1800$~\\GeV", 1800.,
    vh_SVfitMEMk0.at(5), vh_SVfitMEMk.at(5));
  addRow_woSoB_mssm(table4, "$m_{\\PHiggsps} = 2600$~\\GeV", 2600.,
    vh_SVfitMEMk0.at(6), vh_SVfitMEMk.at(6));

  // Z'->tautau	
  table4 << "$\\PZ' \\to \\Pgt\\Pgt$: & & & & & & \\\\ " << endl;
  addRow_woSoB_mssm(table4, "$m_{\\PZ'} = 2500$~\\GeV", 2500.,
    vh_SVfitMEMk0.at(7), vh_SVfitMEMk.at(7));
  
  table4 << "\\hline" << endl;
  table4 << "\\end{tabular}\n" << endl;
  //-----------------------------------------------------------------------------

  table4 << "\\end{table}\n" << endl;

  table4.close();

} // void
