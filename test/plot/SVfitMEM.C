#define SVfitMEM_cxx
#include "SVfitMEM.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


void SVfitMEM::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  cout<<"sample: "  <<sample  <<endl;
  cout<<"mass: "    <<mass    <<endl;
  cout<<"dir: "     <<dir     <<endl;
  cout<<"nentries: "<<nentries<<endl;

  int count{0};

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    if((nentries+1)%1000==0) cout<<"processing event "<<nentries<<endl;

    vector<double>vemu_gen_smeared{genElectron1Pt, fabs(genElectron1Eta), genMuon1Pt, fabs(genMuon1Eta) }; // only had smeared
    vector<double>vemu_cut{10, 2.4, 10, 2.1}; // cuts from paper   
    //
    vector<double>vmuhad_gen{genMuon1Pt, fabs(genMuon1Eta), genHadTau1Pt, fabs(genHadTau1Eta) };    
    vector<double>vmuhad_smeared{genMuon1Pt, fabs(genMuon1Eta), smearedHadTau1Pt, fabs(smearedHadTau1Eta) };  
    vector<double>vmuhad_cut{20, 2.1, 30, 2.3};    
    //
    vector<double>vhadhad_gen{genHadTau1Pt, fabs(genHadTau1Eta), genHadTau2Pt, fabs(genHadTau2Eta)};    
    vector<double>vhadhad_smeared{smearedHadTau1Pt, fabs(smearedHadTau1Eta), smearedHadTau2Pt, fabs(smearedHadTau2Eta)};    
    vector<double>vhadhad_cut{45, 2.1, 45, 2.1};    

    // apply cuts 
    if(sample.find("GluGlu")!=std::string::npos) if(genDiTauMass<0.95*mass || genDiTauMass>1.05*mass) continue;

    bool passCuts{1};

    int i, j;
    int ncutmuhad{static_cast<int>(vmuhad_cut.size())};
    int ncuthadhad{static_cast<int>(vhadhad_cut.size())};

    if     (dir.find("emu")!=string::npos) {
      if( max(genElectron1Pt, genMuon1Pt)<20 || min(genElectron1Pt, genMuon1Pt)<10 || 
	  vemu_gen_smeared[1]>vemu_cut[1] || vemu_gen_smeared[3]>vemu_cut[3]) passCuts=0; 
    }
    else if(dir=="muhad_gen") {
      for(i=0, j=1; i<ncutmuhad, j<ncutmuhad; i+=2, j+=2)   if(vmuhad_gen[i]<vmuhad_cut[i] || vmuhad_gen[j]>vmuhad_cut[j]) passCuts=0; 
    }
    else if(dir=="muhad_smeared") {
      for(i=0, j=1; i<ncutmuhad, j<ncutmuhad; i+=2, j+=2)   if(vmuhad_smeared[i]<vmuhad_cut[i] || vmuhad_smeared[j]>vmuhad_cut[j]) passCuts=0; 
    }
    else if(dir=="hadhad_gen") {
      for(i=0, j=1; i<ncuthadhad, j<ncuthadhad; i+=2, j+=2) if(vhadhad_gen[i]<vhadhad_cut[i] || vhadhad_gen[j]>vhadhad_cut[j]) passCuts=0; 
    }
    else if(dir=="hadhad_smeared") {
      for(i=0, j=1; i<ncuthadhad, j<ncuthadhad; i+=2, j+=2) if(vhadhad_smeared[i]<vhadhad_cut[i] || vhadhad_smeared[j]>vhadhad_cut[j]) passCuts=0; 
    }

    if(!passCuts) continue;

    npassCuts->Fill(0);

    hmasslin[0] ->Fill(visMass);
    if(caMass_isValid) hmasslin[1] ->Fill(caMass);
    if(svfitMass_isValid) hmasslin[2] ->Fill(svfitMass);
    //
    hmasslog[0] ->Fill(visMass);
    if(caMass_isValid) hmasslog[1] ->Fill(caMass);
    if(svfitMass_isValid) hmasslog[2] ->Fill(svfitMass);


    // tf hist
    int   istfk0     {svfitMass_isValidMEM0logMwHadTauTF};
    int   istfk1     {svfitMass_isValidMEM1logMwHadTauTF};
    int   istfk2     {svfitMass_isValidMEM2logMwHadTauTF};
    int   istfk3     {svfitMass_isValidMEM3logMwHadTauTF};
    int   istfk4     {svfitMass_isValidMEM4logMwHadTauTF};
    int   istfk5     {svfitMass_isValidMEM5logMwHadTauTF};
    vector<int> vistfk{istfk0, istfk1, istfk2, istfk3, istfk4, istfk5};
    //
    float tfk0  {svfitMassMEM0logMwHadTauTF}; 
    float tfk1  {svfitMassMEM1logMwHadTauTF}; 
    float tfk2  {svfitMassMEM2logMwHadTauTF}; 
    float tfk3  {svfitMassMEM3logMwHadTauTF}; 
    float tfk4  {svfitMassMEM4logMwHadTauTF}; 
    float tfk5  {svfitMassMEM5logMwHadTauTF}; 
    vector<float> vtfk{tfk0, tfk1, tfk2, tfk3, tfk4, tfk5};
    //
    for(int i=0; i<6; i++) if(vistfk[i]==1) { hmasslin[i+3]->Fill(vtfk[i]); hmasslog[i+3]->Fill(vtfk[i]);}

  }

  cout<<"\nwriting hist..."<<endl;

  // normalise histogram to probability to find a valid solution
  for(int i=0; i<9; i++) { 
    hmasslin[i]->Scale(1/(npassCuts->Integral()/npassCuts->GetBinWidth(1))); hmasslin[i]->Write(); 
    hmasslog[i]->Scale(1/(npassCuts->Integral()/npassCuts->GetBinWidth(1))); hmasslog[i]->Write(); 
    cout<<endl;
    cout<<"integral lin: "<<hmasslin[i]->GetName()<<": "<<hmasslin[i]->Integral()<<endl;
    cout<<"integral log: "<<hmasslog[i]->GetName()<<": "<<hmasslog[i]->Integral()<<endl;
  }

  cout<<"processed "<<nentries<< " events!!"<<endl;
}  


// efficiency check
//if(numGenMuons     >1)nmu->Fill(0);
//if(numGenElectrons >1)nel->Fill(0);
//if(numGenHadTaus   >1)nha->Fill(0);
//if(numGenMuons >0 && numGenElectrons >0)nem->Fill(0);


//cout<<"\nefficiency\n";
//cout<<"% nmu>1: "<< (nmu->Integral()/nmu->GetBinWidth(1))/nentries<<endl;
//cout<<"% nel>1: "  << (nel->Integral()/nel->GetBinWidth(1))/nentries<<endl;
//cout<<"% nha>1: "  << (nha->Integral()/nha->GetBinWidth(1))/nentries<<endl;
//cout<<"% ne>1 && nm>1: "<< (nem->Integral()/nem->GetBinWidth(1))/nentries<<endl;

