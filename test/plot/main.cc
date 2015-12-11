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
    string input {"svFitStudyNtuple_SUSYGluGluToHToTauTauM300_all.root"}; 
    cout << "Processing file: " << input << endl;
    string output {"Plot_svFitStudyNtuple_SUSYGluGluToHToTauTauM300_all.root"}; 

    TFile* ifile = new TFile(input.c_str(),"READ");
    if (!ifile->IsOpen()) { cout<<"Can't open "<<input<<endl; return 1; }

    TFile* ofile = new TFile(output.c_str(),"RECREATE");
    if (!ofile->IsOpen()) { cout<<"Can't create "<<output<<endl; return 1; }

    // directories
    vector<string>samples{"emu_gen", "emu_smeared", "hadhad_gen", "hadhad_smeared" ,"muhad_gen", "muhad_smeared"};
    double mass{300};

    // fill histogram
    cout<<"filling hist...\n";
    for(auto &sample : samples ){

     string treeName="ntupleProducer/"+sample+"/SVfitStudyNtupleProducer";
     cout<<"tree name: "<<treeName<<endl;

     TTree *tree = (TTree*) ifile->GetObjectChecked(treeName.c_str(), "TTree");
     //cout<<"tree class? "<<tree->ClassName()<<endl;

      // analysis
      SVfitMEM an(tree, sample, mass);

      an.Loop();

      cout<<"end loop!!"<<endl;

      delete tree;

    }
 
    ifile->Close();
    ofile->Close();


    return 0;

}


