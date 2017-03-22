#include "func.C"
#include <fstream>
#include <vector>
#include <math.h>

void table2_muhad()
{
  // write table
  cout<<"writing table...\n";

  //string inputPath {"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_V"};
  //string savePath {"/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot"};
  string inputPath {"/home/veelken/SVfitMEM_paper/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_V"};
  string savePath {"/home/veelken/SVfitMEM_paper/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot"};

  // root file
  vector<double> CEfactor {0.00182226, 0.000355142, 0.000125415, 0.00000538775,
                           0.022621, 0.00897221, 0.0039879, 0.0138281};
  
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
  double glugluxs = 43.92*0.0632; //pb
  double vbfxs    = 3.748*0.0632; //pb
  double dyxs     = 5765.4; //NNLO pb

  vector<TH1D*> vh_mvis;
  vector<TH1D*> vh_SVfitSA;
  vector<TH1D*> vh_SVfitMEMk0;
  vector<TH1D*> vh_SVfitMEMk;
  vector<TH1D*> vh_SVfitCLAk0;
  vector<TH1D*> vh_SVfitCLAk;

  // loop over input files
  for ( int in = 0; in < vinput.size(); ++in ) { 
    string input{inputPath + "/" + vinput[in]};
    TFile* file = new TFile(input.c_str(), "READ");

    string sample{input};
    sample.replace(0, sample.find_first_of("_")+1, "");
    sample.replace(sample.find_first_of("_"), sample.find_last_of("t"), "");
    
    string mass{sample};
    mass.replace(0, mass.find_first_of("M")+1, "");

    // loop over hist
    TIter nextHist(file->GetListOfKeys());
    TKey* histKey(0);
    while ( (histKey = (TKey*)nextHist()) ) {
      if ( strcmp(histKey->GetClassName(),"TH1D") != 0 ) continue;
      TH1D* hmass = (TH1D*)histKey->ReadObj();
      string histname(hmass->GetName());
      // hist name match directory name
      if ( histname.find("muhad")                         == std::string::npos ) continue; 
      if ( histname.find("Jet")                           != std::string::npos ) continue; 
      if ( histname.find("fine_bin")                      == std::string::npos ) continue; 
      if ( histname.find("smeared_vismass_fine_bin")      != std::string::npos ) vh_mvis.push_back((TH1D*)hmass->Clone());
      if ( histname.find("smeared_svFit_fine_bin")        != std::string::npos ) vh_SVfitSA.push_back((TH1D*)hmass->Clone());
      if ( histname.find("smeared_svfitmemtfk0_fine_bin") != std::string::npos ) vh_SVfitMEMk0.push_back((TH1D*)hmass->Clone());
      if ( histname.find("smeared_svfitclatfk0_fine_bin") != std::string::npos ) vh_SVfitCLAk0.push_back((TH1D*)hmass->Clone());
      if ( histname.find("smeared_svfitmemtfk4_fine_bin") != std::string::npos ) vh_SVfitMEMk.push_back((TH1D*)hmass->Clone());
      if ( histname.find("smeared_svfitclatfk4_fine_bin") != std::string::npos ) vh_SVfitCLAk.push_back((TH1D*)hmass->Clone());
    }
  }	

  ofstream table2;
  table2.open("table2_muhad.txt");

  table2 << "\\begin{table}" << endl;
  table2 << "\\begin{center}" << endl;

  //-----------------------------------------------------------------------------
  // mVis and SVfitSA
  table2 << "\\begin{tabular}{|l|cccc|cccc|}" << endl;
  //table2 << "\\begin{tabular}{|l|C{1.2cm}C{0.9cm}C{0.9cm}C{1.2cm}|C{1.2cm}C{0.9cm}C{0.9cm}C{1.2cm}|}" << endl;
  table2 << "\\hline" << endl;
  table2 << "\\multicolumn{9}{|c|}{$\\Pgm\\tauh$ decay channel} \\\\" << endl;
  table2 << "\\hline" << endl;
  table2 << "\\hline" << endl;
  table2 << "\\multirow{2}{17mm}{Sample} & \\multicolumn{4}{c|}{$m_{\\vis}$} & \\multicolumn{4}{c|}{SVfitSA} \\\\" << endl;
  table2 << "\\cline{2-9}" << endl;
  table2 << " & " 
	 << "$\\textrm{M}$~[\\GeV\\unskip] & "
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ & " 
	 << "$\\tfrac{S}{S+B}$ & "
	 << "$\\textrm{M}$~[\\GeV\\unskip] & " 
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ & " 
	 << "$\\tfrac{S}{S+B}$ \\\\" << endl;
  table2 << "\\hline" << endl;
    
  // Z->tautau			    
  table2 << "$\\PZ \\to \\Pgt\\Pgt$: & & & & & & & & \\\\ " << endl; 
  addRow_woSoB(table2, "$0$-jet", 
	       vh_mvis.at(0), vh_SVfitSA.at(0));
  addRow_woSoB(table2, "$1$-jet non--boosted", 
	       vh_mvis.at(1), vh_SVfitSA.at(1));
  addRow_woSoB(table2, "$1$-jet boosted", 
	       vh_mvis.at(2), vh_SVfitSA.at(2));
  addRow_woSoB(table2, "$2$-jet VBF", 
	       vh_mvis.at(3), vh_SVfitSA.at(3));

  // SM Higgs->tautau produced via gluon fusion
  table2 << "SM $\\Pg\\Pg \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & & & \\\\ " << endl; 
  addRow_wSoB(table2, "$0$-jet", 
	      vh_mvis.at(4), glugluxs*CEfactor[4], vh_mvis.at(0), dyxs*CEfactor[0], 
	      vh_SVfitSA.at(4), glugluxs*CEfactor[4], vh_SVfitSA.at(0), dyxs*CEfactor[0]);
  addRow_wSoB(table2, "$1$-jet non--boosted", 
	      vh_mvis.at(5), glugluxs*CEfactor[5], vh_mvis.at(1), dyxs*CEfactor[1], 
	      vh_SVfitSA.at(5), glugluxs*CEfactor[5], vh_SVfitSA.at(1), dyxs*CEfactor[1]);
  addRow_wSoB(table2, "$1$-jet boosted", 
	      vh_mvis.at(6), glugluxs*CEfactor[6], vh_mvis.at(2), dyxs*CEfactor[2], 
	      vh_SVfitSA.at(6), glugluxs*CEfactor[6], vh_SVfitSA.at(2), dyxs*CEfactor[2]);
  
  // SM Higgs->tautau produced via VBF
  table2 << "SM $\\Pquark\\APquark \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & & & \\\\ " << endl; 
  addRow_wSoB(table2, "$2$-jet VBF", 
	      vh_mvis.at(7), vbfxs*CEfactor[7], vh_mvis.at(3), dyxs*CEfactor[3],
	      vh_SVfitSA.at(7), vbfxs*CEfactor[7], vh_SVfitSA.at(3), dyxs*CEfactor[3]);
  
  table2 << "\\hline" << endl;
  table2 << "\\end{tabular}\n" << endl;
  //-----------------------------------------------------------------------------

  //-----------------------------------------------------------------------------
  // cSVfit (zero and non-zero kappa)
  table2 << "\\begin{tabular}{|l|cccc|cccc|}" << endl;
  //table2 << "\\begin{tabular}{|l|C{1.2cm}C{0.9cm}C{0.9cm}C{1.2cm}|C{1.2cm}C{0.9cm}C{0.9cm}C{1.2cm}|}" << endl;
  table2 << "\\hline" << endl;
  table2 << "\\multirow{2}{17mm}{Sample} & \\multicolumn{4}{c|}{cSVfit, $\\kappa=0$} & \\multicolumn{4}{c|}{cSVfit, $\\kappa=4$} \\\\" << endl;
  table2 << "\\cline{2-9}" << endl;
  table2 << " & " 
	 << "$\\textrm{M}$~[\\GeV\\unskip] & "
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ & " 
	 << "$\\tfrac{S}{S+B}$ & "
	 << "$\\textrm{M}$~[\\GeV\\unskip] & " 
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ & " 
	 << "$\\tfrac{S}{S+B}$ \\\\" << endl;
  table2 << "\\hline" << endl;
  
  // Z->tautau			    
  table2 << "$\\PZ \\to \\Pgt\\Pgt$: & & & & & & & & \\\\ " << endl; 
  addRow_woSoB(table2, "$0$-jet", 
	       vh_SVfitCLAk0.at(0), vh_SVfitCLAk.at(0));
  addRow_woSoB(table2, "$1$-jet non--boosted", 
	       vh_SVfitCLAk0.at(1), vh_SVfitCLAk.at(1));
  addRow_woSoB(table2, "$1$-jet boosted", 
	       vh_SVfitCLAk0.at(2), vh_SVfitCLAk.at(2));
  addRow_woSoB(table2, "$2$-jet VBF", 
	       vh_SVfitCLAk0.at(3), vh_SVfitCLAk.at(3));

  // SM Higgs->tautau produced via gluon fusion
  table2 << "SM $\\Pg\\Pg \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & & & \\\\ " << endl; 
  addRow_wSoB(table2, "$0$-jet", 
	      vh_SVfitCLAk0.at(4), glugluxs*CEfactor[4], vh_SVfitCLAk0.at(0), dyxs*CEfactor[0], 
	      vh_SVfitCLAk.at(4), glugluxs*CEfactor[4], vh_SVfitCLAk.at(0), dyxs*CEfactor[0]);
  addRow_wSoB(table2, "$1$-jet non--boosted", 
	      vh_SVfitCLAk0.at(5), glugluxs*CEfactor[5], vh_SVfitCLAk0.at(1), dyxs*CEfactor[1], 
	      vh_SVfitCLAk.at(5), glugluxs*CEfactor[5], vh_SVfitCLAk.at(1), dyxs*CEfactor[1]);
  addRow_wSoB(table2, "$1$-jet boosted", 
	      vh_SVfitCLAk0.at(6), glugluxs*CEfactor[6], vh_SVfitCLAk0.at(2), dyxs*CEfactor[2], 
	      vh_SVfitCLAk.at(6), glugluxs*CEfactor[6], vh_SVfitCLAk.at(2), dyxs*CEfactor[2]);
  
  // SM Higgs->tautau produced via VBF
  table2 << "SM $\\Pquark\\APquark \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & & & \\\\ " << endl; 
  addRow_wSoB(table2, "$2$-jet VBF", 
	      vh_SVfitCLAk0.at(7), vbfxs*CEfactor[7], vh_SVfitCLAk0.at(3), dyxs*CEfactor[3], 
	      vh_SVfitCLAk.at(7), vbfxs*CEfactor[7], vh_SVfitCLAk.at(3), dyxs*CEfactor[3]);
  
  table2 << "\\hline" << endl;
  table2 << "\\end{tabular}\n" << endl;
  //-----------------------------------------------------------------------------
  
  //-----------------------------------------------------------------------------
  // SVfitMEM (zero and non-zero kappa)
  table2 << "\\begin{tabular}{|l|cccc|cccc|}" << endl;
  //table2 << "\\begin{tabular}{|l|C{1.2cm}C{0.9cm}C{0.9cm}C{1.2cm}|C{1.2cm}C{0.9cm}C{0.9cm}C{1.2cm}|}" << endl;
  table2 << "\\hline" << endl;
  table2 << "\\multirow{2}{17mm}{Sample} & \\multicolumn{4}{c|}{SVfitMEM, $\\kappa=0$} & \\multicolumn{4}{c|}{SVfitMEM, $\\kappa=4$} \\\\" << endl;
  table2 << "\\cline{2-9}" << endl;
  table2 << " & " 
	 << "$\\textrm{M}$~[\\GeV\\unskip] & "
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ & " 
	 << "$\\tfrac{S}{S+B}$ & "
	 << "$\\textrm{M}$~[\\GeV\\unskip] & " 
	 << "$\\sigma_{l}/\\textrm{M}$ & $\\sigma_{h}/\\textrm{M}$ & " 
	 << "$\\tfrac{S}{S+B}$ \\\\" << endl;
  table2 << "\\hline" << endl;
  
  // Z->tautau			    
  table2 << "$\\PZ \\to \\Pgt\\Pgt$: & & & & & & & & \\\\ " << endl; 
  addRow_woSoB(table2, "$0$-jet", 
	       vh_SVfitMEMk0.at(0), vh_SVfitMEMk.at(0));
  addRow_woSoB(table2, "$1$-jet non--boosted", 
	       vh_SVfitMEMk0.at(1), vh_SVfitMEMk.at(1));
  addRow_woSoB(table2, "$1$-jet boosted", 
	       vh_SVfitMEMk0.at(2), vh_SVfitMEMk.at(2));
  addRow_woSoB(table2, "$2$-jet VBF", 
	       vh_SVfitMEMk0.at(3), vh_SVfitMEMk.at(3));

  // SM Higgs->tautau produced via gluon fusion
  table2 << "SM $\\Pg\\Pg \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & & & \\\\ " << endl; 
  addRow_wSoB(table2, "$0$-jet", 
	      vh_SVfitMEMk0.at(4), glugluxs*CEfactor[4], vh_SVfitMEMk0.at(0), dyxs*CEfactor[0], 
	      vh_SVfitMEMk.at(4), glugluxs*CEfactor[4], vh_SVfitMEMk.at(0), dyxs*CEfactor[0]);
  addRow_wSoB(table2, "$1$-jet non--boosted", 
	      vh_SVfitMEMk0.at(5), glugluxs*CEfactor[5], vh_SVfitMEMk0.at(1), dyxs*CEfactor[1], 
	      vh_SVfitMEMk.at(5), glugluxs*CEfactor[5], vh_SVfitMEMk.at(1), dyxs*CEfactor[1]);
  addRow_wSoB(table2, "$1$-jet boosted", 
	      vh_SVfitMEMk0.at(6), glugluxs*CEfactor[6], vh_SVfitMEMk0.at(2), dyxs*CEfactor[2], 
	      vh_SVfitMEMk.at(6), glugluxs*CEfactor[6], vh_SVfitMEMk.at(2), dyxs*CEfactor[2]);
  
  // SM Higgs->tautau produced via VBF
  table2 << "SM $\\Pquark\\APquark \\to \\PHiggs$, $\\PHiggs \\to \\Pgt\\Pgt$: & & & & & & & & \\\\ " << endl; 
  addRow_wSoB(table2, "$2$-jet VBF", 
	      vh_SVfitMEMk0.at(7), vbfxs*CEfactor[7], vh_SVfitMEMk0.at(3), dyxs*CEfactor[3], 
	      vh_SVfitMEMk.at(7), vbfxs*CEfactor[7], vh_SVfitMEMk.at(3), dyxs*CEfactor[3]);
  
  table2 << "\\hline" << endl;
  table2 << "\\end{tabular}\n" << endl;
  //-----------------------------------------------------------------------------
      
  table2 << "\\end{table}\n" << endl;
  
  table2.close();

} // void
