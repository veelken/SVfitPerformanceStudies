//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Dec  5 01:26:15 2015 by ROOT version 6.02/05
// from TTree SVfitStudyNtupleProducer/SVfitStudyNtupleProducer
// found on file: ntuples/svFitStudyNtuple_SUSYGluGluToHToTauTauM300_all.root
//////////////////////////////////////////////////////////

#ifndef SVfitMEM_h
#define SVfitMEM_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string>
#include <TH1.h>
#include <TLegend.h>
#include <iostream>
#include <TMath.h>


// Header file for the classes stored in the TTree if any.

class SVfitMEM {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   ULong64_t       run;
   ULong64_t       event;
   ULong64_t       lumi;
   Float_t         genTauLepton1E;
   Float_t         genTauLepton1Px;
   Float_t         genTauLepton1Py;
   Float_t         genTauLepton1Pz;
   Float_t         genTauLepton1Pt;
   Float_t         genTauLepton1Eta;
   Float_t         genTauLepton1Phi;
   Float_t         genTauLepton1Mass;
   Float_t         genTauLepton1Charge;
   Float_t         genTauLepton2E;
   Float_t         genTauLepton2Px;
   Float_t         genTauLepton2Py;
   Float_t         genTauLepton2Pz;
   Float_t         genTauLepton2Pt;
   Float_t         genTauLepton2Eta;
   Float_t         genTauLepton2Phi;
   Float_t         genTauLepton2Mass;
   Float_t         genTauLepton2Charge;
   Int_t           numGenTauLeptons;
   Float_t         genDiTauPt;
   Float_t         genDiTauEta;
   Float_t         genDiTauPhi;
   Float_t         genDiTauMass;
   Float_t         genElectron1E;
   Float_t         genElectron1Px;
   Float_t         genElectron1Py;
   Float_t         genElectron1Pz;
   Float_t         genElectron1Pt;
   Float_t         genElectron1Eta;
   Float_t         genElectron1Phi;
   Float_t         genElectron1Mass;
   Float_t         genElectron1Charge;
   Float_t         genElectron2E;
   Float_t         genElectron2Px;
   Float_t         genElectron2Py;
   Float_t         genElectron2Pz;
   Float_t         genElectron2Pt;
   Float_t         genElectron2Eta;
   Float_t         genElectron2Phi;
   Float_t         genElectron2Mass;
   Float_t         genElectron2Charge;
   Int_t           numGenElectrons;
   Float_t         genMuon1E;
   Float_t         genMuon1Px;
   Float_t         genMuon1Py;
   Float_t         genMuon1Pz;
   Float_t         genMuon1Pt;
   Float_t         genMuon1Eta;
   Float_t         genMuon1Phi;
   Float_t         genMuon1Mass;
   Float_t         genMuon1Charge;
   Float_t         genMuon2E;
   Float_t         genMuon2Px;
   Float_t         genMuon2Py;
   Float_t         genMuon2Pz;
   Float_t         genMuon2Pt;
   Float_t         genMuon2Eta;
   Float_t         genMuon2Phi;
   Float_t         genMuon2Mass;
   Float_t         genMuon2Charge;
   Int_t           numGenMuons;
   Float_t         genHadTau1E;
   Float_t         genHadTau1Px;
   Float_t         genHadTau1Py;
   Float_t         genHadTau1Pz;
   Float_t         genHadTau1Pt;
   Float_t         genHadTau1Eta;
   Float_t         genHadTau1Phi;
   Float_t         genHadTau1Mass;
   Float_t         genHadTau1Charge;
   Int_t           genHadTau1DecayMode;
   Float_t         genHadTau2E;
   Float_t         genHadTau2Px;
   Float_t         genHadTau2Py;
   Float_t         genHadTau2Pz;
   Float_t         genHadTau2Pt;
   Float_t         genHadTau2Eta;
   Float_t         genHadTau2Phi;
   Float_t         genHadTau2Mass;
   Float_t         genHadTau2Charge;
   Int_t           genHadTau2DecayMode;
   Int_t           numGenHadTaus;
   Float_t         smearedHadTau1E;
   Float_t         smearedHadTau1Px;
   Float_t         smearedHadTau1Py;
   Float_t         smearedHadTau1Pz;
   Float_t         smearedHadTau1Pt;
   Float_t         smearedHadTau1Eta;
   Float_t         smearedHadTau1Phi;
   Float_t         smearedHadTau1Mass;
   Float_t         smearedHadTau1Charge;
   Int_t           smearedHadTau1DecayMode;
   Float_t         smearedHadTau2E;
   Float_t         smearedHadTau2Px;
   Float_t         smearedHadTau2Py;
   Float_t         smearedHadTau2Pz;
   Float_t         smearedHadTau2Pt;
   Float_t         smearedHadTau2Eta;
   Float_t         smearedHadTau2Phi;
   Float_t         smearedHadTau2Mass;
   Float_t         smearedHadTau2Charge;
   Int_t           smearedHadTau2DecayMode;
   Int_t           numSmearedHadTaus;
   Float_t         genMEtPx;
   Float_t         genMEtPy;
   Float_t         genMEtPt;
   Float_t         genMEtPhi;
   Float_t         genMEtCov00;
   Float_t         genMEtCov01;
   Float_t         genMEtCov10;
   Float_t         genMEtCov11;
   Float_t         smearedMEtPx;
   Float_t         smearedMEtPy;
   Float_t         smearedMEtPt;
   Float_t         smearedMEtPhi;
   Float_t         smearedMEtCov00;
   Float_t         smearedMEtCov01;
   Float_t         smearedMEtCov10;
   Float_t         smearedMEtCov11;
   Float_t         visMass;
   Float_t         caMass;
   Int_t           caMass_isValid;
   Float_t         svfitMass;
   Float_t         svfitMassErr;
   Int_t           svfitMass_isValid;
   Float_t         svfitMassMEM0logMwHadTauTF;
   Float_t         svfitMassErrMEM0logMwHadTauTF;
   Int_t           svfitMass_isValidMEM0logMwHadTauTF;
   Float_t         svfitMassMEM0logMwoHadTauTF;
   Float_t         svfitMassErrMEM0logMwoHadTauTF;
   Int_t           svfitMass_isValidMEM0logMwoHadTauTF;
   //
   Float_t         svfitMassMEM1logMwHadTauTF;
   Float_t         svfitMassErrMEM1logMwHadTauTF;
   Int_t           svfitMass_isValidMEM1logMwHadTauTF;
   Float_t         svfitMassMEM1logMwoHadTauTF;
   Float_t         svfitMassErrMEM1logMwoHadTauTF;
   Int_t           svfitMass_isValidMEM1logMwoHadTauTF;
   //
   Float_t         svfitMassMEM2logMwHadTauTF;
   Float_t         svfitMassErrMEM2logMwHadTauTF;
   Int_t           svfitMass_isValidMEM2logMwHadTauTF;
   Float_t         svfitMassMEM2logMwoHadTauTF;
   Float_t         svfitMassErrMEM2logMwoHadTauTF;
   Int_t           svfitMass_isValidMEM2logMwoHadTauTF;
   //
   Float_t         svfitMassMEM3logMwHadTauTF;
   Float_t         svfitMassErrMEM3logMwHadTauTF;
   Int_t           svfitMass_isValidMEM3logMwHadTauTF;
   Float_t         svfitMassMEM3logMwoHadTauTF;
   Float_t         svfitMassErrMEM3logMwoHadTauTF;
   Int_t           svfitMass_isValidMEM3logMwoHadTauTF;
   //
   Float_t         svfitMassMEM4logMwHadTauTF;
   Float_t         svfitMassErrMEM4logMwHadTauTF;
   Int_t           svfitMass_isValidMEM4logMwHadTauTF;
   Float_t         svfitMassMEM4logMwoHadTauTF;
   Float_t         svfitMassErrMEM4logMwoHadTauTF;
   Int_t           svfitMass_isValidMEM4logMwoHadTauTF;
   //
   Float_t         svfitMassMEM5logMwHadTauTF;
   Float_t         svfitMassErrMEM5logMwHadTauTF;
   Int_t           svfitMass_isValidMEM5logMwHadTauTF;
   Float_t         svfitMassMEM5logMwoHadTauTF;
   Float_t         svfitMassErrMEM5logMwoHadTauTF;
   Int_t           svfitMass_isValidMEM5logMwoHadTauTF;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_genTauLepton1E;   //!
   TBranch        *b_genTauLepton1Px;   //!
   TBranch        *b_genTauLepton1Py;   //!
   TBranch        *b_genTauLepton1Pz;   //!
   TBranch        *b_genTauLepton1Pt;   //!
   TBranch        *b_genTauLepton1Eta;   //!
   TBranch        *b_genTauLepton1Phi;   //!
   TBranch        *b_genTauLepton1Mass;   //!
   TBranch        *b_genTauLepton1Charge;   //!
   TBranch        *b_genTauLepton2E;   //!
   TBranch        *b_genTauLepton2Px;   //!
   TBranch        *b_genTauLepton2Py;   //!
   TBranch        *b_genTauLepton2Pz;   //!
   TBranch        *b_genTauLepton2Pt;   //!
   TBranch        *b_genTauLepton2Eta;   //!
   TBranch        *b_genTauLepton2Phi;   //!
   TBranch        *b_genTauLepton2Mass;   //!
   TBranch        *b_genTauLepton2Charge;   //!
   TBranch        *b_numGenTauLeptons;   //!
   TBranch        *b_genDiTauPt;   //!
   TBranch        *b_genDiTauEta;   //!
   TBranch        *b_genDiTauPhi;   //!
   TBranch        *b_genDiTauMass;   //!
   TBranch        *b_genElectron1E;   //!
   TBranch        *b_genElectron1Px;   //!
   TBranch        *b_genElectron1Py;   //!
   TBranch        *b_genElectron1Pz;   //!
   TBranch        *b_genElectron1Pt;   //!
   TBranch        *b_genElectron1Eta;   //!
   TBranch        *b_genElectron1Phi;   //!
   TBranch        *b_genElectron1Mass;   //!
   TBranch        *b_genElectron1Charge;   //!
   TBranch        *b_genElectron2E;   //!
   TBranch        *b_genElectron2Px;   //!
   TBranch        *b_genElectron2Py;   //!
   TBranch        *b_genElectron2Pz;   //!
   TBranch        *b_genElectron2Pt;   //!
   TBranch        *b_genElectron2Eta;   //!
   TBranch        *b_genElectron2Phi;   //!
   TBranch        *b_genElectron2Mass;   //!
   TBranch        *b_genElectron2Charge;   //!
   TBranch        *b_numGenElectrons;   //!
   TBranch        *b_genMuon1E;   //!
   TBranch        *b_genMuon1Px;   //!
   TBranch        *b_genMuon1Py;   //!
   TBranch        *b_genMuon1Pz;   //!
   TBranch        *b_genMuon1Pt;   //!
   TBranch        *b_genMuon1Eta;   //!
   TBranch        *b_genMuon1Phi;   //!
   TBranch        *b_genMuon1Mass;   //!
   TBranch        *b_genMuon1Charge;   //!
   TBranch        *b_genMuon2E;   //!
   TBranch        *b_genMuon2Px;   //!
   TBranch        *b_genMuon2Py;   //!
   TBranch        *b_genMuon2Pz;   //!
   TBranch        *b_genMuon2Pt;   //!
   TBranch        *b_genMuon2Eta;   //!
   TBranch        *b_genMuon2Phi;   //!
   TBranch        *b_genMuon2Mass;   //!
   TBranch        *b_genMuon2Charge;   //!
   TBranch        *b_numGenMuons;   //!
   TBranch        *b_genHadTau1E;   //!
   TBranch        *b_genHadTau1Px;   //!
   TBranch        *b_genHadTau1Py;   //!
   TBranch        *b_genHadTau1Pz;   //!
   TBranch        *b_genHadTau1Pt;   //!
   TBranch        *b_genHadTau1Eta;   //!
   TBranch        *b_genHadTau1Phi;   //!
   TBranch        *b_genHadTau1Mass;   //!
   TBranch        *b_genHadTau1Charge;   //!
   TBranch        *b_genHadTau1DecayMode;   //!
   TBranch        *b_genHadTau2E;   //!
   TBranch        *b_genHadTau2Px;   //!
   TBranch        *b_genHadTau2Py;   //!
   TBranch        *b_genHadTau2Pz;   //!
   TBranch        *b_genHadTau2Pt;   //!
   TBranch        *b_genHadTau2Eta;   //!
   TBranch        *b_genHadTau2Phi;   //!
   TBranch        *b_genHadTau2Mass;   //!
   TBranch        *b_genHadTau2Charge;   //!
   TBranch        *b_genHadTau2DecayMode;   //!
   TBranch        *b_numGenHadTaus;   //!
   TBranch        *b_smearedHadTau1E;   //!
   TBranch        *b_smearedHadTau1Px;   //!
   TBranch        *b_smearedHadTau1Py;   //!
   TBranch        *b_smearedHadTau1Pz;   //!
   TBranch        *b_smearedHadTau1Pt;   //!
   TBranch        *b_smearedHadTau1Eta;   //!
   TBranch        *b_smearedHadTau1Phi;   //!
   TBranch        *b_smearedHadTau1Mass;   //!
   TBranch        *b_smearedHadTau1Charge;   //!
   TBranch        *b_smearedHadTau1DecayMode;   //!
   TBranch        *b_smearedHadTau2E;   //!
   TBranch        *b_smearedHadTau2Px;   //!
   TBranch        *b_smearedHadTau2Py;   //!
   TBranch        *b_smearedHadTau2Pz;   //!
   TBranch        *b_smearedHadTau2Pt;   //!
   TBranch        *b_smearedHadTau2Eta;   //!
   TBranch        *b_smearedHadTau2Phi;   //!
   TBranch        *b_smearedHadTau2Mass;   //!
   TBranch        *b_smearedHadTau2Charge;   //!
   TBranch        *b_smearedHadTau2DecayMode;   //!
   TBranch        *b_numSmearedHadTaus;   //!
   TBranch        *b_genMEtPx;   //!
   TBranch        *b_genMEtPy;   //!
   TBranch        *b_genMEtPt;   //!
   TBranch        *b_genMEtPhi;   //!
   TBranch        *b_genMEtCov00;   //!
   TBranch        *b_genMEtCov01;   //!
   TBranch        *b_genMEtCov10;   //!
   TBranch        *b_genMEtCov11;   //!
   TBranch        *b_smearedMEtPx;   //!
   TBranch        *b_smearedMEtPy;   //!
   TBranch        *b_smearedMEtPt;   //!
   TBranch        *b_smearedMEtPhi;   //!
   TBranch        *b_smearedMEtCov00;   //!
   TBranch        *b_smearedMEtCov01;   //!
   TBranch        *b_smearedMEtCov10;   //!
   TBranch        *b_smearedMEtCov11;   //!
   TBranch        *b_visMass;   //!
   TBranch        *b_caMass;   //!
   TBranch        *b_caMass_isValid;   //!
   TBranch        *b_svfitMass;   //!
   TBranch        *b_svfitMassErr;   //!
   TBranch        *b_svfitMass_isValid;   //!
   TBranch        *b_svfitMassMEM0logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM0logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM0logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEM0logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM0logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM0logMwoHadTauTF;   //!
   //
   TBranch        *b_svfitMassMEM1logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM1logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM1logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEM1logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM1logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM1logMwoHadTauTF;   //!
   //
   TBranch        *b_svfitMassMEM2logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM2logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM2logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEM2logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM2logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM2logMwoHadTauTF;   //!
   //
   TBranch        *b_svfitMassMEM3logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM3logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM3logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEM3logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM3logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM3logMwoHadTauTF;   //!
   //
   TBranch        *b_svfitMassMEM4logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM4logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM4logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEM4logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM4logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM4logMwoHadTauTF;   //!
   //
   TBranch        *b_svfitMassMEM5logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM5logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM5logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEM5logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEM5logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEM5logMwoHadTauTF;   //!

   SVfitMEM(TTree *tree=0, std::string dir=(""), std::string sample=(""), double mass=0);
   virtual ~SVfitMEM();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   std::string dir;
   std::string sample;
   double mass;

   TH1D *hmasslin[9];
   TH1D *hmasslog[9];
   //TH1D *hmassdiv[4];
   TH1I *npassCuts;
   //TH1I *nmu, *nel, *nha, *nem; 

};

#endif

#ifdef SVfitMEM_cxx

#include "getLogBinning.C"
SVfitMEM::SVfitMEM(TTree *tree, std::string dir, std::string sample, double mass) : fChain(0), dir{dir}, sample{sample}, mass{mass}
{

  Init(tree);

  TH1::SetDefaultSumw2();

  //nmu = new TH1I("nmu", "nmu", 1, 0, 1);
  //nel = new TH1I("nel", "nel", 1, 0, 1);
  //nha = new TH1I("nha", "nha", 1, 0, 1);
  //nem = new TH1I("nem", "nem", 1, 0, 1);

  npassCuts= new TH1I(dir.c_str(), dir.c_str(), 1, 0, 1);

  std::vector<std::string> vdirlin {dir+"_lin_vismass", dir+"_lin_ca", dir+"_lin_svFit", dir+"_lin_svfitmemtfk0", 
    dir+"_lin_svfitmemtfk1",dir+"_lin_svfitmemtfk2",dir+"_lin_svfitmemtfk3",dir+"_lin_svfitmemtfk4",dir+"_lin_svfitmemtfk5"};

  std::vector<std::string> vdirlog {dir+"_log_vismass", dir+"_log_ca", dir+"_log_svFit", dir+"_log_svfitmemtfk0", 
    dir+"_log_svfitmemtfk1",dir+"_log_svfitmemtfk2",dir+"_log_svfitmemtfk3",dir+"_log_svfitmemtfk4",dir+"_log_svfitmemtfk5"};


  std::map<int, double> xMax;
  xMax[50]   = 450;
  xMax[125]  = 620;
  xMax[200]  = 1000;
  xMax[300]  = 1500;
  xMax[500]  = 2500;
  xMax[800]  = 4000;
  xMax[1200] = 6000;
  xMax[1800] = 9000;
  xMax[2600] = 13000;

/*
  // plot for paper
  int numbin{35};
  if(dir.find("emu")!=std::string::npos) 
    for(int i=0; i<vdirlog.size(); i++) {
      hmasslog[i] = new TH1D(vdirlog[i].c_str(), vdirlog[i].c_str(), numbin, getLogBinning(30, xMax[mass], numbin).GetArray());
      hmasslin[i] = new TH1D(vdirlin[i].c_str(), vdirlin[i].c_str(), numbin, 30, xMax[mass]);
    }
  else {
    for(int i=0; i<vdirlog.size(); i++){
      hmasslog[i] = new TH1D(vdirlog[i].c_str(), vdirlog[i].c_str(), numbin, getLogBinning(50, xMax[mass], numbin).GetArray());
      hmasslin[i] = new TH1D(vdirlin[i].c_str(), vdirlin[i].c_str(), numbin, 50, xMax[mass]);
    }
  }
*/

  // bin for paper table
  int numbin{0};
  if(dir.find("emu")!=std::string::npos){ 
    numbin=xMax[mass]-30;
    for(int i=0; i<vdirlog.size(); i++) {
      hmasslog[i] = new TH1D(vdirlog[i].c_str(), vdirlog[i].c_str(), numbin, getLogBinning(30, xMax[mass], numbin).GetArray());
      hmasslin[i] = new TH1D(vdirlin[i].c_str(), vdirlin[i].c_str(), numbin, 30, xMax[mass]);
    }
  }
  else {
    numbin=xMax[mass]-50;
    for(int i=0; i<vdirlog.size(); i++){
      hmasslog[i] = new TH1D(vdirlog[i].c_str(), vdirlog[i].c_str(), numbin, getLogBinning(50, xMax[mass], numbin).GetArray());
      hmasslin[i] = new TH1D(vdirlin[i].c_str(), vdirlin[i].c_str(), numbin, 50, xMax[mass]);
    }
  }


}

SVfitMEM::~SVfitMEM()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
  for(int i=0; i<9; i++ ) { delete hmasslin[i]; delete hmasslog[i]; }
  //for(int i=0; i<4; i++ ) delete hmassdiv[i]; 
}


Int_t SVfitMEM::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t SVfitMEM::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void SVfitMEM::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("genTauLepton1E", &genTauLepton1E, &b_genTauLepton1E);
  fChain->SetBranchAddress("genTauLepton1Px", &genTauLepton1Px, &b_genTauLepton1Px);
  fChain->SetBranchAddress("genTauLepton1Py", &genTauLepton1Py, &b_genTauLepton1Py);
  fChain->SetBranchAddress("genTauLepton1Pz", &genTauLepton1Pz, &b_genTauLepton1Pz);
  fChain->SetBranchAddress("genTauLepton1Pt", &genTauLepton1Pt, &b_genTauLepton1Pt);
  fChain->SetBranchAddress("genTauLepton1Eta", &genTauLepton1Eta, &b_genTauLepton1Eta);
  fChain->SetBranchAddress("genTauLepton1Phi", &genTauLepton1Phi, &b_genTauLepton1Phi);
  fChain->SetBranchAddress("genTauLepton1Mass", &genTauLepton1Mass, &b_genTauLepton1Mass);
  fChain->SetBranchAddress("genTauLepton1Charge", &genTauLepton1Charge, &b_genTauLepton1Charge);
  fChain->SetBranchAddress("genTauLepton2E", &genTauLepton2E, &b_genTauLepton2E);
  fChain->SetBranchAddress("genTauLepton2Px", &genTauLepton2Px, &b_genTauLepton2Px);
  fChain->SetBranchAddress("genTauLepton2Py", &genTauLepton2Py, &b_genTauLepton2Py);
  fChain->SetBranchAddress("genTauLepton2Pz", &genTauLepton2Pz, &b_genTauLepton2Pz);
  fChain->SetBranchAddress("genTauLepton2Pt", &genTauLepton2Pt, &b_genTauLepton2Pt);
  fChain->SetBranchAddress("genTauLepton2Eta", &genTauLepton2Eta, &b_genTauLepton2Eta);
  fChain->SetBranchAddress("genTauLepton2Phi", &genTauLepton2Phi, &b_genTauLepton2Phi);
  fChain->SetBranchAddress("genTauLepton2Mass", &genTauLepton2Mass, &b_genTauLepton2Mass);
  fChain->SetBranchAddress("genTauLepton2Charge", &genTauLepton2Charge, &b_genTauLepton2Charge);
  fChain->SetBranchAddress("numGenTauLeptons", &numGenTauLeptons, &b_numGenTauLeptons);
  fChain->SetBranchAddress("genDiTauPt", &genDiTauPt, &b_genDiTauPt);
  fChain->SetBranchAddress("genDiTauEta", &genDiTauEta, &b_genDiTauEta);
  fChain->SetBranchAddress("genDiTauPhi", &genDiTauPhi, &b_genDiTauPhi);
  fChain->SetBranchAddress("genDiTauMass", &genDiTauMass, &b_genDiTauMass);
  fChain->SetBranchAddress("genElectron1E", &genElectron1E, &b_genElectron1E);
  fChain->SetBranchAddress("genElectron1Px", &genElectron1Px, &b_genElectron1Px);
  fChain->SetBranchAddress("genElectron1Py", &genElectron1Py, &b_genElectron1Py);
  fChain->SetBranchAddress("genElectron1Pz", &genElectron1Pz, &b_genElectron1Pz);
  fChain->SetBranchAddress("genElectron1Pt", &genElectron1Pt, &b_genElectron1Pt);
  fChain->SetBranchAddress("genElectron1Eta", &genElectron1Eta, &b_genElectron1Eta);
  fChain->SetBranchAddress("genElectron1Phi", &genElectron1Phi, &b_genElectron1Phi);
  fChain->SetBranchAddress("genElectron1Mass", &genElectron1Mass, &b_genElectron1Mass);
  fChain->SetBranchAddress("genElectron1Charge", &genElectron1Charge, &b_genElectron1Charge);
  fChain->SetBranchAddress("genElectron2E", &genElectron2E, &b_genElectron2E);
  fChain->SetBranchAddress("genElectron2Px", &genElectron2Px, &b_genElectron2Px);
  fChain->SetBranchAddress("genElectron2Py", &genElectron2Py, &b_genElectron2Py);
  fChain->SetBranchAddress("genElectron2Pz", &genElectron2Pz, &b_genElectron2Pz);
  fChain->SetBranchAddress("genElectron2Pt", &genElectron2Pt, &b_genElectron2Pt);
  fChain->SetBranchAddress("genElectron2Eta", &genElectron2Eta, &b_genElectron2Eta);
  fChain->SetBranchAddress("genElectron2Phi", &genElectron2Phi, &b_genElectron2Phi);
  fChain->SetBranchAddress("genElectron2Mass", &genElectron2Mass, &b_genElectron2Mass);
  fChain->SetBranchAddress("genElectron2Charge", &genElectron2Charge, &b_genElectron2Charge);
  fChain->SetBranchAddress("numGenElectrons", &numGenElectrons, &b_numGenElectrons);
  fChain->SetBranchAddress("genMuon1E", &genMuon1E, &b_genMuon1E);
  fChain->SetBranchAddress("genMuon1Px", &genMuon1Px, &b_genMuon1Px);
  fChain->SetBranchAddress("genMuon1Py", &genMuon1Py, &b_genMuon1Py);
  fChain->SetBranchAddress("genMuon1Pz", &genMuon1Pz, &b_genMuon1Pz);
  fChain->SetBranchAddress("genMuon1Pt", &genMuon1Pt, &b_genMuon1Pt);
  fChain->SetBranchAddress("genMuon1Eta", &genMuon1Eta, &b_genMuon1Eta);
  fChain->SetBranchAddress("genMuon1Phi", &genMuon1Phi, &b_genMuon1Phi);
  fChain->SetBranchAddress("genMuon1Mass", &genMuon1Mass, &b_genMuon1Mass);
  fChain->SetBranchAddress("genMuon1Charge", &genMuon1Charge, &b_genMuon1Charge);
  fChain->SetBranchAddress("genMuon2E", &genMuon2E, &b_genMuon2E);
  fChain->SetBranchAddress("genMuon2Px", &genMuon2Px, &b_genMuon2Px);
  fChain->SetBranchAddress("genMuon2Py", &genMuon2Py, &b_genMuon2Py);
  fChain->SetBranchAddress("genMuon2Pz", &genMuon2Pz, &b_genMuon2Pz);
  fChain->SetBranchAddress("genMuon2Pt", &genMuon2Pt, &b_genMuon2Pt);
  fChain->SetBranchAddress("genMuon2Eta", &genMuon2Eta, &b_genMuon2Eta);
  fChain->SetBranchAddress("genMuon2Phi", &genMuon2Phi, &b_genMuon2Phi);
  fChain->SetBranchAddress("genMuon2Mass", &genMuon2Mass, &b_genMuon2Mass);
  fChain->SetBranchAddress("genMuon2Charge", &genMuon2Charge, &b_genMuon2Charge);
  fChain->SetBranchAddress("numGenMuons", &numGenMuons, &b_numGenMuons);
  fChain->SetBranchAddress("genHadTau1E", &genHadTau1E, &b_genHadTau1E);
  fChain->SetBranchAddress("genHadTau1Px", &genHadTau1Px, &b_genHadTau1Px);
  fChain->SetBranchAddress("genHadTau1Py", &genHadTau1Py, &b_genHadTau1Py);
  fChain->SetBranchAddress("genHadTau1Pz", &genHadTau1Pz, &b_genHadTau1Pz);
  fChain->SetBranchAddress("genHadTau1Pt", &genHadTau1Pt, &b_genHadTau1Pt);
  fChain->SetBranchAddress("genHadTau1Eta", &genHadTau1Eta, &b_genHadTau1Eta);
  fChain->SetBranchAddress("genHadTau1Phi", &genHadTau1Phi, &b_genHadTau1Phi);
  fChain->SetBranchAddress("genHadTau1Mass", &genHadTau1Mass, &b_genHadTau1Mass);
  fChain->SetBranchAddress("genHadTau1Charge", &genHadTau1Charge, &b_genHadTau1Charge);
  fChain->SetBranchAddress("genHadTau1DecayMode", &genHadTau1DecayMode, &b_genHadTau1DecayMode);
  fChain->SetBranchAddress("genHadTau2E", &genHadTau2E, &b_genHadTau2E);
  fChain->SetBranchAddress("genHadTau2Px", &genHadTau2Px, &b_genHadTau2Px);
  fChain->SetBranchAddress("genHadTau2Py", &genHadTau2Py, &b_genHadTau2Py);
  fChain->SetBranchAddress("genHadTau2Pz", &genHadTau2Pz, &b_genHadTau2Pz);
  fChain->SetBranchAddress("genHadTau2Pt", &genHadTau2Pt, &b_genHadTau2Pt);
  fChain->SetBranchAddress("genHadTau2Eta", &genHadTau2Eta, &b_genHadTau2Eta);
  fChain->SetBranchAddress("genHadTau2Phi", &genHadTau2Phi, &b_genHadTau2Phi);
  fChain->SetBranchAddress("genHadTau2Mass", &genHadTau2Mass, &b_genHadTau2Mass);
  fChain->SetBranchAddress("genHadTau2Charge", &genHadTau2Charge, &b_genHadTau2Charge);
  fChain->SetBranchAddress("genHadTau2DecayMode", &genHadTau2DecayMode, &b_genHadTau2DecayMode);
  fChain->SetBranchAddress("numGenHadTaus", &numGenHadTaus, &b_numGenHadTaus);
  fChain->SetBranchAddress("smearedHadTau1E", &smearedHadTau1E, &b_smearedHadTau1E);
  fChain->SetBranchAddress("smearedHadTau1Px", &smearedHadTau1Px, &b_smearedHadTau1Px);
  fChain->SetBranchAddress("smearedHadTau1Py", &smearedHadTau1Py, &b_smearedHadTau1Py);
  fChain->SetBranchAddress("smearedHadTau1Pz", &smearedHadTau1Pz, &b_smearedHadTau1Pz);
  fChain->SetBranchAddress("smearedHadTau1Pt", &smearedHadTau1Pt, &b_smearedHadTau1Pt);
  fChain->SetBranchAddress("smearedHadTau1Eta", &smearedHadTau1Eta, &b_smearedHadTau1Eta);
  fChain->SetBranchAddress("smearedHadTau1Phi", &smearedHadTau1Phi, &b_smearedHadTau1Phi);
  fChain->SetBranchAddress("smearedHadTau1Mass", &smearedHadTau1Mass, &b_smearedHadTau1Mass);
  fChain->SetBranchAddress("smearedHadTau1Charge", &smearedHadTau1Charge, &b_smearedHadTau1Charge);
  fChain->SetBranchAddress("smearedHadTau1DecayMode", &smearedHadTau1DecayMode, &b_smearedHadTau1DecayMode);
  fChain->SetBranchAddress("smearedHadTau2E", &smearedHadTau2E, &b_smearedHadTau2E);
  fChain->SetBranchAddress("smearedHadTau2Px", &smearedHadTau2Px, &b_smearedHadTau2Px);
  fChain->SetBranchAddress("smearedHadTau2Py", &smearedHadTau2Py, &b_smearedHadTau2Py);
  fChain->SetBranchAddress("smearedHadTau2Pz", &smearedHadTau2Pz, &b_smearedHadTau2Pz);
  fChain->SetBranchAddress("smearedHadTau2Pt", &smearedHadTau2Pt, &b_smearedHadTau2Pt);
  fChain->SetBranchAddress("smearedHadTau2Eta", &smearedHadTau2Eta, &b_smearedHadTau2Eta);
  fChain->SetBranchAddress("smearedHadTau2Phi", &smearedHadTau2Phi, &b_smearedHadTau2Phi);
  fChain->SetBranchAddress("smearedHadTau2Mass", &smearedHadTau2Mass, &b_smearedHadTau2Mass);
  fChain->SetBranchAddress("smearedHadTau2Charge", &smearedHadTau2Charge, &b_smearedHadTau2Charge);
  fChain->SetBranchAddress("smearedHadTau2DecayMode", &smearedHadTau2DecayMode, &b_smearedHadTau2DecayMode);
  fChain->SetBranchAddress("numSmearedHadTaus", &numSmearedHadTaus, &b_numSmearedHadTaus);
  fChain->SetBranchAddress("genMEtPx", &genMEtPx, &b_genMEtPx);
  fChain->SetBranchAddress("genMEtPy", &genMEtPy, &b_genMEtPy);
  fChain->SetBranchAddress("genMEtPt", &genMEtPt, &b_genMEtPt);
  fChain->SetBranchAddress("genMEtPhi", &genMEtPhi, &b_genMEtPhi);
  fChain->SetBranchAddress("genMEtCov00", &genMEtCov00, &b_genMEtCov00);
  fChain->SetBranchAddress("genMEtCov01", &genMEtCov01, &b_genMEtCov01);
  fChain->SetBranchAddress("genMEtCov10", &genMEtCov10, &b_genMEtCov10);
  fChain->SetBranchAddress("genMEtCov11", &genMEtCov11, &b_genMEtCov11);
  fChain->SetBranchAddress("smearedMEtPx", &smearedMEtPx, &b_smearedMEtPx);
  fChain->SetBranchAddress("smearedMEtPy", &smearedMEtPy, &b_smearedMEtPy);
  fChain->SetBranchAddress("smearedMEtPt", &smearedMEtPt, &b_smearedMEtPt);
  fChain->SetBranchAddress("smearedMEtPhi", &smearedMEtPhi, &b_smearedMEtPhi);
  fChain->SetBranchAddress("smearedMEtCov00", &smearedMEtCov00, &b_smearedMEtCov00);
  fChain->SetBranchAddress("smearedMEtCov01", &smearedMEtCov01, &b_smearedMEtCov01);
  fChain->SetBranchAddress("smearedMEtCov10", &smearedMEtCov10, &b_smearedMEtCov10);
  fChain->SetBranchAddress("smearedMEtCov11", &smearedMEtCov11, &b_smearedMEtCov11);
  fChain->SetBranchAddress("visMass", &visMass, &b_visMass);
  fChain->SetBranchAddress("caMass", &caMass, &b_caMass);
  fChain->SetBranchAddress("caMass_isValid", &caMass_isValid, &b_caMass_isValid);
  fChain->SetBranchAddress("svfitMass", &svfitMass, &b_svfitMass);
  fChain->SetBranchAddress("svfitMassErr", &svfitMassErr, &b_svfitMassErr);
  fChain->SetBranchAddress("svfitMass_isValid", &svfitMass_isValid, &b_svfitMass_isValid);
  fChain->SetBranchAddress("svfitMassMEM0logMwHadTauTF", &svfitMassMEM0logMwHadTauTF, &b_svfitMassMEM0logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM0logMwHadTauTF", &svfitMassErrMEM0logMwHadTauTF, &b_svfitMassErrMEM0logMwHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM0logMwHadTauTF", &svfitMass_isValidMEM0logMwHadTauTF, &b_svfitMass_isValidMEM0logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassMEM0logMwoHadTauTF", &svfitMassMEM0logMwoHadTauTF, &b_svfitMassMEM0logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM0logMwoHadTauTF", &svfitMassErrMEM0logMwoHadTauTF, &b_svfitMassErrMEM0logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM0logMwoHadTauTF", &svfitMass_isValidMEM0logMwoHadTauTF, &b_svfitMass_isValidMEM0logMwoHadTauTF);
  //
  fChain->SetBranchAddress("svfitMassMEM1logMwHadTauTF", &svfitMassMEM1logMwHadTauTF, &b_svfitMassMEM1logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM1logMwHadTauTF", &svfitMassErrMEM1logMwHadTauTF, &b_svfitMassErrMEM1logMwHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM1logMwHadTauTF", &svfitMass_isValidMEM1logMwHadTauTF, &b_svfitMass_isValidMEM1logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassMEM1logMwoHadTauTF", &svfitMassMEM1logMwoHadTauTF, &b_svfitMassMEM1logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM1logMwoHadTauTF", &svfitMassErrMEM1logMwoHadTauTF, &b_svfitMassErrMEM1logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM1logMwoHadTauTF", &svfitMass_isValidMEM1logMwoHadTauTF, &b_svfitMass_isValidMEM1logMwoHadTauTF);
  //
  fChain->SetBranchAddress("svfitMassMEM2logMwHadTauTF", &svfitMassMEM2logMwHadTauTF, &b_svfitMassMEM2logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM2logMwHadTauTF", &svfitMassErrMEM2logMwHadTauTF, &b_svfitMassErrMEM2logMwHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM2logMwHadTauTF", &svfitMass_isValidMEM2logMwHadTauTF, &b_svfitMass_isValidMEM2logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassMEM2logMwoHadTauTF", &svfitMassMEM2logMwoHadTauTF, &b_svfitMassMEM2logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM2logMwoHadTauTF", &svfitMassErrMEM2logMwoHadTauTF, &b_svfitMassErrMEM2logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM2logMwoHadTauTF", &svfitMass_isValidMEM2logMwoHadTauTF, &b_svfitMass_isValidMEM2logMwoHadTauTF);
  //
  fChain->SetBranchAddress("svfitMassMEM3logMwHadTauTF", &svfitMassMEM3logMwHadTauTF, &b_svfitMassMEM3logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM3logMwHadTauTF", &svfitMassErrMEM3logMwHadTauTF, &b_svfitMassErrMEM3logMwHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM3logMwHadTauTF", &svfitMass_isValidMEM3logMwHadTauTF, &b_svfitMass_isValidMEM3logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassMEM3logMwoHadTauTF", &svfitMassMEM3logMwoHadTauTF, &b_svfitMassMEM3logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM3logMwoHadTauTF", &svfitMassErrMEM3logMwoHadTauTF, &b_svfitMassErrMEM3logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM3logMwoHadTauTF", &svfitMass_isValidMEM3logMwoHadTauTF, &b_svfitMass_isValidMEM3logMwoHadTauTF);
  //
  fChain->SetBranchAddress("svfitMassMEM4logMwHadTauTF", &svfitMassMEM4logMwHadTauTF, &b_svfitMassMEM4logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM4logMwHadTauTF", &svfitMassErrMEM4logMwHadTauTF, &b_svfitMassErrMEM4logMwHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM4logMwHadTauTF", &svfitMass_isValidMEM4logMwHadTauTF, &b_svfitMass_isValidMEM4logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassMEM4logMwoHadTauTF", &svfitMassMEM4logMwoHadTauTF, &b_svfitMassMEM4logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM4logMwoHadTauTF", &svfitMassErrMEM4logMwoHadTauTF, &b_svfitMassErrMEM4logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM4logMwoHadTauTF", &svfitMass_isValidMEM4logMwoHadTauTF, &b_svfitMass_isValidMEM4logMwoHadTauTF);
  //
  fChain->SetBranchAddress("svfitMassMEM5logMwHadTauTF", &svfitMassMEM5logMwHadTauTF, &b_svfitMassMEM5logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM5logMwHadTauTF", &svfitMassErrMEM5logMwHadTauTF, &b_svfitMassErrMEM5logMwHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM5logMwHadTauTF", &svfitMass_isValidMEM5logMwHadTauTF, &b_svfitMass_isValidMEM5logMwHadTauTF);
  fChain->SetBranchAddress("svfitMassMEM5logMwoHadTauTF", &svfitMassMEM5logMwoHadTauTF, &b_svfitMassMEM5logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMassErrMEM5logMwoHadTauTF", &svfitMassErrMEM5logMwoHadTauTF, &b_svfitMassErrMEM5logMwoHadTauTF);
  fChain->SetBranchAddress("svfitMass_isValidMEM5logMwoHadTauTF", &svfitMass_isValidMEM5logMwoHadTauTF, &b_svfitMass_isValidMEM5logMwoHadTauTF);
  Notify();
}

Bool_t SVfitMEM::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void SVfitMEM::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t SVfitMEM::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef SVfitMEM_cxx
