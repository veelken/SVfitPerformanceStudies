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

using namespace std;

TH1I *nmu = new TH1I("nmu", "nmu", 10, 0, 10);
TH1I *nel = new TH1I("nel", "nel", 10, 0, 10);
TH1I *nha = new TH1I("nha", "nha", 10, 0, 10);
TH1I *nem = new TH1I("nem", "nem", 10, 0, 10);

void SVfitMEM::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  cout<<"sample: "<<sample<<endl;
  cout<<"nentries: "<<nentries<<endl;
  //cout<<"mass: "<<mass<<endl;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
  //for (Long64_t jentry=0; jentry<10000;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;


    if((nentries+1)%1000==0) cout<<"processing event "<<nentries<<endl;

    // efficiency check
    if(numGenMuons     >1)nmu->Fill(1);
    if(numGenElectrons >1)nel->Fill(1);
    if(numGenHadTaus   >1)nha->Fill(1);
    if(numGenMuons >0 && numGenElectrons >0)nem->Fill(1);


    // k==0 && k==5, tf && notf
    vector<double>vemu_gen_smeared{genElectron1Pt, genElectron1Eta, genMuon1Pt, genMuon1Eta }; // values from tree   
    vector<double>vemu_cut{10, 2.4, 10, 2.1}; // cuts from paper   
    //
    vector<double>vmuhad_gen{genMuon1Pt, fabs(genMuon1Eta), genHadTau1Pt, fabs(genHadTau1Eta) };    
    vector<double>vmuhad_smeared{genMuon1Pt, fabs(genMuon1Eta), smearedHadTau1Pt, fabs(smearedHadTau1Eta) };  // only had smeared
    vector<double>vmuhad_cut{20, 2.1, 30, 2.3};    
    //
    vector<double>vhadhad_gen{genHadTau1Pt, fabs(genHadTau1Eta), genHadTau2Pt, fabs(genHadTau2Eta)};    
    vector<double>vhadhad_smeared{smearedHadTau1Pt, fabs(smearedHadTau1Eta), smearedHadTau2Pt, fabs(smearedHadTau2Eta)};    
    vector<double>vhadhad_cut{45, 2.1, 45, 2.1};    

    // apply cuts 
    if(genDiTauMass<0.95*mass || genDiTauMass>1.05*mass) continue;

    bool passCuts{1};

    int i, j;
    int ncut{static_cast<int>(vhadhad_gen.size())};

    if     (sample=="emu_gen" || sample=="emu_smeared") {
      for(i=0, j=1; i<ncut, j<ncut; i+=2, j+=2) if(vemu_gen_smeared[i]<vemu_cut[i] || vemu_gen_smeared[j]>vemu_cut[j]) passCuts=0; 
    }
    else if(sample=="muhad_gen") {
      for(i=0, j=1; i<ncut, j<ncut; i+=2, j+=2) if(vmuhad_gen[i]<vmuhad_cut[i] || vmuhad_gen[j]>vmuhad_cut[j]) passCuts=0; 
    }
    else if(sample=="muhad_smeared") {
      for(i=0, j=1; i<ncut, j<ncut; i+=2, j+=2) if(vmuhad_smeared[i]<vmuhad_cut[i] || vmuhad_smeared[j]>vmuhad_cut[j]) passCuts=0; 
    }
    else if(sample=="hadhad_gen") {
      for(i=0, j=1; i<ncut, j<ncut; i+=2, j+=2) if(vhadhad_gen[i]<vhadhad_cut[i] || vhadhad_gen[j]>vhadhad_cut[j]) passCuts=0; 
    }
    else if(sample=="hadhad_smeared") {
      for(i=0, j=1; i<ncut, j<ncut; i+=2, j+=2) if(vhadhad_smeared[i]<vhadhad_cut[i] || vhadhad_smeared[j]>vhadhad_cut[j]) passCuts=0; 
    }


    if(!passCuts) continue;

    npassCuts->Fill(0);

    int   k0     {svfitMass_isValidMEM0logMwHadTauTF};
    int   k5     {svfitMass_isValidMEM5logMwHadTauTF};
    float k0_notf{svfitMassMEM0logMwoHadTauTF}; 
    float k0_tf  {svfitMassMEM0logMwHadTauTF}; 
    float k5_notf{svfitMassMEM5logMwoHadTauTF}; 
    float k5_tf  {svfitMassMEM5logMwHadTauTF}; 
    if(k0==1){
	h[0]->Fill(k0_tf);
	h[1]->Fill(k0_notf);
    }
    if(k5==1){
	h[2]->Fill(k5_tf);
	h[3]->Fill(k5_notf);
    }
  }
  cout<<"\nefficiency\n";
  cout<<"% nmu>1: "<< (nmu->Integral()/nmu->GetBinWidth(1))/nentries<<endl;
  cout<<"% nel>1: "  << (nel->Integral()/nel->GetBinWidth(1))/nentries<<endl;
  cout<<"% nha>1: "  << (nha->Integral()/nha->GetBinWidth(1))/nentries<<endl;
  cout<<"% ne>1 && nm>1: "<< (nem->Integral()/nem->GetBinWidth(1))/nentries<<endl;

  cout<<"\nwriting hist..."<<endl;

  for(int i=0; i<hmax; i++) h[i]->Write(); npassCuts->Write();

  cout<<"processed "<<nentries<< " events!!"<<endl;
}
