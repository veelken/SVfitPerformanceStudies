#include "SVfitMEM.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <TKey.h>
#include "TCanvas.h"

using namespace std;

int main ( int argc, char * argv[]) {

    // root file
        string inputdir  = "/hdfs/local/lucia/SVfitFiles/";
        string outputdir  = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/plot/SVfitFiles_Output_IV/";
	vector<string> vinput {"hist_gen_ZprimeToTauTauM2500_inclusive",
                "hist_gen_SUSYGluGluToHToTauTauM1200_inclusive",
		"hist_gen_SUSYGluGluToHToTauTauM1800_inclusive",
		"hist_gen_SUSYGluGluToHToTauTauM200_inclusive",
		"hist_gen_SUSYGluGluToHToTauTauM2600_inclusive",
		"hist_gen_SUSYGluGluToHToTauTauM300_inclusive",
		"hist_gen_SUSYGluGluToHToTauTauM500_inclusive",
		"hist_gen_SUSYGluGluToHToTauTauM800_inclusive",
		"hist_gen_SUSYGluGluToHToTauTauM90_inclusive",
		"hist_gen_DYJetsToLLM50_0Jets",
		"hist_gen_DYJetsToLLM50_1JetBoosted",
		"hist_gen_DYJetsToLLM50_1JetNotBoosted",
		"hist_gen_DYJetsToLLM50_2Jets",
		"hist_gen_DYJetsToLLM50_inclusive",
		"hist_gen_GluGluHToTauTauM125_0Jets",
		"hist_gen_GluGluHToTauTauM125_1JetBoosted",
		"hist_gen_GluGluHToTauTauM125_1JetNotBoosted",
		"hist_gen_GluGluHToTauTauM125_2Jets",
		"hist_gen_GluGluHToTauTauM125_inclusive",
		"hist_gen_VBFHToTauTauM125_0Jets",
		"hist_gen_VBFHToTauTauM125_1JetBoosted",
		"hist_gen_VBFHToTauTauM125_1JetNotBoosted",
		"hist_gen_VBFHToTauTauM125_2Jets",
		"hist_gen_VBFHToTauTauM125_inclusive"}; 
	vector<string>vsample{"ZprimeToTauTauM2500",
                "SUSYGluGluToHToTauTauM1200",
		"SUSYGluGluToHToTauTauM1800_inclusive",
		"SUSYGluGluToHToTauTauM200_inclusive",
		"SUSYGluGluToHToTauTauM2600_inclusive",
		"SUSYGluGluToHToTauTauM300_inclusive",
		"SUSYGluGluToHToTauTauM500_inclusive",
		"SUSYGluGluToHToTauTauM800_inclusive",
                "SUSYGluGluToHToTauTauM90_inclusive",
		"DYJetsToLLM50",//_0Jets",
		"DYJetsToLLM50",//_1JetBoosted",
		"DYJetsToLLM50",//_1JetNotBoosted",
		"DYJetsToLLM50",//_2Jets",
		"DYJetsToLLM50",//_inclusive",
		"GluGluHToTauTauM125",//_0Jets",
		"GluGluHToTauTauM125",//_1JetBoosted",
		"GluGluHToTauTauM125",//_1JetNotBoosted",
		"GluGluHToTauTauM125",//_2Jets",
		"GluGluHToTauTauM125",//_inclusive",
		"VBFHToTauTauM125",//_0Jets",
		"VBFHToTauTauM125",//_1JetBoosted",
		"VBFHToTauTauM125",//_1JetNotBoosted",
		"VBFHToTauTauM125",//_2Jets",
		"VBFHToTauTauM125"//_inclusive"
	};

	// directories
	vector<string>vdir{};

	// loop over input files
	for (size_t iin=0; iin<vinput.size(); iin++){ 	

      cout << "Processing file: " << vinput.at(iin) << ".root" << endl;
      TFile* ifile = new TFile((inputdir+vinput.at(iin)+".root").c_str(),"READ");
      if (!ifile->IsOpen()) { cout<<"Can't open "<< vinput.at(iin) <<endl; return 1; }

      TFile* ofile = new TFile((outputdir+vinput.at(iin)+".root").c_str(),"RECREATE");
      if (!ofile->IsOpen()) { cout<<"Can't create output file " <<endl; return 1; }

      // fill histogram
      cout<<"filling hist...\n";
      vdir.clear();

      vdir.push_back("emu_gen");
      vdir.push_back("muhad_gen");
      vdir.push_back("hadhad_gen");
      for(auto &dir : vdir ){

	string treeName="ntupleProducer/"+dir+"/SVfitStudyNtupleProducer";
	TTree *tree = (TTree*) ifile->GetObjectChecked(treeName.c_str(), "TTree");
	string sample{vsample.at(iin)};
	string smass{sample};
	smass.replace(0, smass.find_first_of("M")+1, "");

	double mass{stod(smass)};

	SVfitMEM an(tree, dir, sample, mass);
        cout << "entering the loop...\n";
	an.Loop();

	delete tree;
	
      } // dir
      ifile->Close();
      ofile->Close();
    } // input file

    return 0;
}


