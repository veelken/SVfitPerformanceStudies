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
    vector<string> vinput {
    "/afs/cern.ch/work/c/calpas/ntuples/svFitStudyNtuple_SUSYGluGluToHToTauTauM200_all.root",
    "/afs/cern.ch/work/c/calpas/ntuples/svFitStudyNtuple_SUSYGluGluToHToTauTauM300_all.root",
    "/afs/cern.ch/work/c/calpas/ntuples/svFitStudyNtuple_SUSYGluGluToHToTauTauM500_all.root",
    "/afs/cern.ch/work/c/calpas/ntuples/svFitStudyNtuple_SUSYGluGluToHToTauTauM800_all.root",
    "/afs/cern.ch/work/c/calpas/ntuples/svFitStudyNtuple_SUSYGluGluToHToTauTauM1200_all.root",
    "/afs/cern.ch/work/c/calpas/ntuples/svFitStudyNtuple_SUSYGluGluToHToTauTauM1800_all.root",
    "/afs/cern.ch/work/c/calpas/ntuples/svFitStudyNtuple_SUSYGluGluToHToTauTauM2600_all.root",
    "/afs/cern.ch/work/c/calpas/ntuples/svFitStudyNtuple_GluGluHToTauTauM125_all.root",
    "/afs/cern.ch/work/c/calpas/ntuples/svFitStudyNtuple_DYJetsToLLM50_all.root"
    };  

    // directories
    vector<string>vdir{"emu_gen", "emu_smeared", "muhad_gen", "muhad_smeared" ,"hadhad_gen", "hadhad_smeared"};

    // loop over input files
    for (auto &input : vinput){ 	

      cout << "Processing file: " << input << endl;
      TFile* ifile = new TFile(input.c_str(),"READ");
      if (!ifile->IsOpen()) { cout<<"Can't open "<<input<<endl; return 1; }

      string output {input};
      output.replace(0, output.find_first_of("_"), "hist");
      cout << "output file: " << output << endl;

      TFile* ofile = new TFile(output.c_str(),"RECREATE");
      if (!ofile->IsOpen()) { cout<<"Can't create "<<output<<endl; return 1; }

      // fill histogram
      cout<<"filling hist...\n";
      for(auto &dir : vdir ){

        if(dir.find("gen")!=std::string::npos) continue;

	string treeName="ntupleProducer/"+dir+"/SVfitStudyNtupleProducer";
	//cout<<"tree name: "<<treeName<<endl;

	TTree *tree = (TTree*) ifile->GetObjectChecked(treeName.c_str(), "TTree");

	// analysis
	string sample{output};
	sample.replace(0, sample.find_first_of("_")+1, "");
	//cout<<"sample: "<<sample<<endl;

	string smass{sample};
	smass.replace(0, smass.find_first_of("M")+1, "");
	smass.replace(smass.find_first_of("_"), smass.find_last_of("t"),"");
	//cout<<"smass: "<<smass<<endl;

	double mass{stod(smass)};
	//cout<<"mass: "<<mass<<endl;

	SVfitMEM an(tree, dir, sample, mass);

	an.Loop();
	//cout<<"end loop!!"<<endl;

	delete tree;
	
      } // dir
      ifile->Close();
      ofile->Close();
    } // input file

    return 0;
}


