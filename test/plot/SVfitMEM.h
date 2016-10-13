//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 18 15:06:26 2016 by ROOT version 6.02/13
// from TTree SVfitStudyNtupleProducer/SVfitStudyNtupleProducer
// found on file: ../batchJobs/output/hadhad/gen/SUSYGluGluToHToTauTauM90/svFitStudyNtuple_hadhad_gen_40.root
//////////////////////////////////////////////////////////

#ifndef SVfitMEM_h
#define SVfitMEM_h

#include <TROOT.h>
#include <TChain.h>
#include <TH1.h>
#include <TFile.h>

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
   Float_t         genHadRecoilE;
   Float_t         genHadRecoilPx;
   Float_t         genHadRecoilPy;
   Float_t         genHadRecoilPz;
   Float_t         genHadRecoilPt;
   Float_t         genHadRecoilEta;
   Float_t         genHadRecoilPhi;
   Float_t         genHadRecoilMass;
   Float_t         genHadRecoilCharge;
   Float_t         genHadRecoilCov00;
   Float_t         genHadRecoilCov01;
   Float_t         genHadRecoilCov02;
   Float_t         genHadRecoilCov03;
   Float_t         genHadRecoilCov10;
   Float_t         genHadRecoilCov11;
   Float_t         genHadRecoilCov12;
   Float_t         genHadRecoilCov13;
   Float_t         genHadRecoilCov20;
   Float_t         genHadRecoilCov21;
   Float_t         genHadRecoilCov22;
   Float_t         genHadRecoilCov23;
   Float_t         genHadRecoilCov30;
   Float_t         genHadRecoilCov31;
   Float_t         genHadRecoilCov32;
   Float_t         genHadRecoilCov33;
   Float_t         smearedHadRecoilE;
   Float_t         smearedHadRecoilPx;
   Float_t         smearedHadRecoilPy;
   Float_t         smearedHadRecoilPz;
   Float_t         smearedHadRecoilPt;
   Float_t         smearedHadRecoilEta;
   Float_t         smearedHadRecoilPhi;
   Float_t         smearedHadRecoilMass;
   Float_t         smearedHadRecoilCharge;
   Float_t         smearedHadRecoilCov00;
   Float_t         smearedHadRecoilCov01;
   Float_t         smearedHadRecoilCov02;
   Float_t         smearedHadRecoilCov03;
   Float_t         smearedHadRecoilCov10;
   Float_t         smearedHadRecoilCov11;
   Float_t         smearedHadRecoilCov12;
   Float_t         smearedHadRecoilCov13;
   Float_t         smearedHadRecoilCov20;
   Float_t         smearedHadRecoilCov21;
   Float_t         smearedHadRecoilCov22;
   Float_t         smearedHadRecoilCov23;
   Float_t         smearedHadRecoilCov30;
   Float_t         smearedHadRecoilCov31;
   Float_t         smearedHadRecoilCov32;
   Float_t         smearedHadRecoilCov33;
   Float_t         genJet1E;
   Float_t         genJet1Px;
   Float_t         genJet1Py;
   Float_t         genJet1Pz;
   Float_t         genJet1Pt;
   Float_t         genJet1Eta;
   Float_t         genJet1Phi;
   Float_t         genJet1Mass;
   Float_t         genJet1Charge;
   Float_t         genJet2E;
   Float_t         genJet2Px;
   Float_t         genJet2Py;
   Float_t         genJet2Pz;
   Float_t         genJet2Pt;
   Float_t         genJet2Eta;
   Float_t         genJet2Phi;
   Float_t         genJet2Mass;
   Float_t         genJet2Charge;
   Float_t         genJet3E;
   Float_t         genJet3Px;
   Float_t         genJet3Py;
   Float_t         genJet3Pz;
   Float_t         genJet3Pt;
   Float_t         genJet3Eta;
   Float_t         genJet3Phi;
   Float_t         genJet3Mass;
   Float_t         genJet3Charge;
   Float_t         genJet4E;
   Float_t         genJet4Px;
   Float_t         genJet4Py;
   Float_t         genJet4Pz;
   Float_t         genJet4Pt;
   Float_t         genJet4Eta;
   Float_t         genJet4Phi;
   Float_t         genJet4Mass;
   Float_t         genJet4Charge;
   Float_t         genJet5E;
   Float_t         genJet5Px;
   Float_t         genJet5Py;
   Float_t         genJet5Pz;
   Float_t         genJet5Pt;
   Float_t         genJet5Eta;
   Float_t         genJet5Phi;
   Float_t         genJet5Mass;
   Float_t         genJet5Charge;
   Float_t         genJet6E;
   Float_t         genJet6Px;
   Float_t         genJet6Py;
   Float_t         genJet6Pz;
   Float_t         genJet6Pt;
   Float_t         genJet6Eta;
   Float_t         genJet6Phi;
   Float_t         genJet6Mass;
   Float_t         genJet6Charge;
   Int_t           numGenJets;
   Float_t         genBosonE;
   Float_t         genBosonPx;
   Float_t         genBosonPy;
   Float_t         genBosonPz;
   Float_t         genBosonPt;
   Float_t         genBosonEta;
   Float_t         genBosonPhi;
   Float_t         genBosonMass;
   Float_t         genBosonCharge;
   Int_t           genBosonPdgId;
   Float_t         genBosonDaughter1E;
   Float_t         genBosonDaughter1Px;
   Float_t         genBosonDaughter1Py;
   Float_t         genBosonDaughter1Pz;
   Float_t         genBosonDaughter1Pt;
   Float_t         genBosonDaughter1Eta;
   Float_t         genBosonDaughter1Phi;
   Float_t         genBosonDaughter1Mass;
   Float_t         genBosonDaughter1Charge;
   Int_t           genBosonDaughter1PdgId;
   Float_t         genBosonDaughter2E;
   Float_t         genBosonDaughter2Px;
   Float_t         genBosonDaughter2Py;
   Float_t         genBosonDaughter2Pz;
   Float_t         genBosonDaughter2Pt;
   Float_t         genBosonDaughter2Eta;
   Float_t         genBosonDaughter2Phi;
   Float_t         genBosonDaughter2Mass;
   Float_t         genBosonDaughter2Charge;
   Int_t           genBosonDaughter2PdgId;
   Float_t         visMass;
   Float_t         caMass;
   Int_t           caMass_isValid;
   Float_t         mTtotal;
   Float_t         svfitPt;
   Float_t         svfitPtErr;
   Int_t           svfitPt_isValid;
   Float_t         svfitEta;
   Float_t         svfitEtaErr;
   Int_t           svfitEta_isValid;
   Float_t         svfitPhi;
   Float_t         svfitPhiErr;
   Int_t           svfitPhi_isValid;
   Float_t         svfitMass;
   Float_t         svfitMassErr;
   Int_t           svfitMass_isValid;
   Float_t         svfitTransverseMass;
   Float_t         svfitTransverseMassErr;
   Int_t           svfitTransverseMass_isValid;
   Float_t         svfitComputingTime_cpu;
   Float_t         svfitComputingTime_real;
   Float_t         svfitMassMEMlo0logMwHadTauTF;
   Float_t         svfitMassErrMEMlo0logMwHadTauTF;
   Int_t           svfitMass_isValidMEMlo0logMwHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo0logMwHadTauTF;
   Float_t         svfitComputingTime_realMEMlo0logMwHadTauTF;
   Float_t         svfitMassMEMlo0logMwoHadTauTF;
   Float_t         svfitMassErrMEMlo0logMwoHadTauTF;
   Int_t           svfitMass_isValidMEMlo0logMwoHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo0logMwoHadTauTF;
   Float_t         svfitComputingTime_realMEMlo0logMwoHadTauTF;
   Float_t         svfitMassMEMlo1logMwHadTauTF;
   Float_t         svfitMassErrMEMlo1logMwHadTauTF;
   Int_t           svfitMass_isValidMEMlo1logMwHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo1logMwHadTauTF;
   Float_t         svfitComputingTime_realMEMlo1logMwHadTauTF;
   Float_t         svfitMassMEMlo1logMwoHadTauTF;
   Float_t         svfitMassErrMEMlo1logMwoHadTauTF;
   Int_t           svfitMass_isValidMEMlo1logMwoHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo1logMwoHadTauTF;
   Float_t         svfitComputingTime_realMEMlo1logMwoHadTauTF;
   Float_t         svfitMassMEMlo2logMwHadTauTF;
   Float_t         svfitMassErrMEMlo2logMwHadTauTF;
   Int_t           svfitMass_isValidMEMlo2logMwHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo2logMwHadTauTF;
   Float_t         svfitComputingTime_realMEMlo2logMwHadTauTF;
   Float_t         svfitMassMEMlo2logMwoHadTauTF;
   Float_t         svfitMassErrMEMlo2logMwoHadTauTF;
   Int_t           svfitMass_isValidMEMlo2logMwoHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo2logMwoHadTauTF;
   Float_t         svfitComputingTime_realMEMlo2logMwoHadTauTF;
   Float_t         svfitMassMEMlo3logMwHadTauTF;
   Float_t         svfitMassErrMEMlo3logMwHadTauTF;
   Int_t           svfitMass_isValidMEMlo3logMwHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo3logMwHadTauTF;
   Float_t         svfitComputingTime_realMEMlo3logMwHadTauTF;
   Float_t         svfitMassMEMlo3logMwoHadTauTF;
   Float_t         svfitMassErrMEMlo3logMwoHadTauTF;
   Int_t           svfitMass_isValidMEMlo3logMwoHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo3logMwoHadTauTF;
   Float_t         svfitComputingTime_realMEMlo3logMwoHadTauTF;
   Float_t         svfitMassMEMlo4logMwHadTauTF;
   Float_t         svfitMassErrMEMlo4logMwHadTauTF;
   Int_t           svfitMass_isValidMEMlo4logMwHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo4logMwHadTauTF;
   Float_t         svfitComputingTime_realMEMlo4logMwHadTauTF;
   Float_t         svfitMassMEMlo4logMwoHadTauTF;
   Float_t         svfitMassErrMEMlo4logMwoHadTauTF;
   Int_t           svfitMass_isValidMEMlo4logMwoHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo4logMwoHadTauTF;
   Float_t         svfitComputingTime_realMEMlo4logMwoHadTauTF;
   Float_t         svfitMassMEMlo5logMwHadTauTF;
   Float_t         svfitMassErrMEMlo5logMwHadTauTF;
   Int_t           svfitMass_isValidMEMlo5logMwHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo5logMwHadTauTF;
   Float_t         svfitComputingTime_realMEMlo5logMwHadTauTF;
   Float_t         svfitMassMEMlo5logMwoHadTauTF;
   Float_t         svfitMassErrMEMlo5logMwoHadTauTF;
   Int_t           svfitMass_isValidMEMlo5logMwoHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo5logMwoHadTauTF;
   Float_t         svfitComputingTime_realMEMlo5logMwoHadTauTF;
   Float_t         svfitMassMEMlo6logMwHadTauTF;
   Float_t         svfitMassErrMEMlo6logMwHadTauTF;
   Int_t           svfitMass_isValidMEMlo6logMwHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo6logMwHadTauTF;
   Float_t         svfitComputingTime_realMEMlo6logMwHadTauTF;
   Float_t         svfitMassMEMlo6logMwoHadTauTF;
   Float_t         svfitMassErrMEMlo6logMwoHadTauTF;
   Int_t           svfitMass_isValidMEMlo6logMwoHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo6logMwoHadTauTF;
   Float_t         svfitComputingTime_realMEMlo6logMwoHadTauTF;
   Float_t         svfitMassMEMlo7logMwHadTauTF;
   Float_t         svfitMassErrMEMlo7logMwHadTauTF;
   Int_t           svfitMass_isValidMEMlo7logMwHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo7logMwHadTauTF;
   Float_t         svfitComputingTime_realMEMlo7logMwHadTauTF;
   Float_t         svfitMassMEMlo7logMwoHadTauTF;
   Float_t         svfitMassErrMEMlo7logMwoHadTauTF;
   Int_t           svfitMass_isValidMEMlo7logMwoHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo7logMwoHadTauTF;
   Float_t         svfitComputingTime_realMEMlo7logMwoHadTauTF;
   Float_t         svfitMassMEMlo8logMwHadTauTF;
   Float_t         svfitMassErrMEMlo8logMwHadTauTF;
   Int_t           svfitMass_isValidMEMlo8logMwHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo8logMwHadTauTF;
   Float_t         svfitComputingTime_realMEMlo8logMwHadTauTF;
   Float_t         svfitMassMEMlo8logMwoHadTauTF;
   Float_t         svfitMassErrMEMlo8logMwoHadTauTF;
   Int_t           svfitMass_isValidMEMlo8logMwoHadTauTF;
   Float_t         svfitComputingTime_cpuMEMlo8logMwoHadTauTF;
   Float_t         svfitComputingTime_realMEMlo8logMwoHadTauTF;
   Float_t         classicSVfitPt0logMwHadTauTF;
   Float_t         classicSVfitPtErr0logMwHadTauTF;
   Int_t           classicSVfitPt_isValid0logMwHadTauTF;
   Float_t         classicSVfitEta0logMwHadTauTF;
   Float_t         classicSVfitEtaErr0logMwHadTauTF;
   Int_t           classicSVfitEta_isValid0logMwHadTauTF;
   Float_t         classicSVfitPhi0logMwHadTauTF;
   Float_t         classicSVfitPhiErr0logMwHadTauTF;
   Int_t           classicSVfitPhi_isValid0logMwHadTauTF;
   Float_t         classicSVfitMass0logMwHadTauTF;
   Float_t         classicSVfitMassErr0logMwHadTauTF;
   Int_t           classicSVfitMass_isValid0logMwHadTauTF;
   Float_t         classicSVfitTransverseMass0logMwHadTauTF;
   Float_t         classicSVfitTransverseMassErr0logMwHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid0logMwHadTauTF;
   Float_t         classicSVfitComputingTime_cpu0logMwHadTauTF;
   Float_t         classicSVfitComputingTime_real0logMwHadTauTF;
   Float_t         classicSVfitPt0logMwoHadTauTF;
   Float_t         classicSVfitPtErr0logMwoHadTauTF;
   Int_t           classicSVfitPt_isValid0logMwoHadTauTF;
   Float_t         classicSVfitEta0logMwoHadTauTF;
   Float_t         classicSVfitEtaErr0logMwoHadTauTF;
   Int_t           classicSVfitEta_isValid0logMwoHadTauTF;
   Float_t         classicSVfitPhi0logMwoHadTauTF;
   Float_t         classicSVfitPhiErr0logMwoHadTauTF;
   Int_t           classicSVfitPhi_isValid0logMwoHadTauTF;
   Float_t         classicSVfitMass0logMwoHadTauTF;
   Float_t         classicSVfitMassErr0logMwoHadTauTF;
   Int_t           classicSVfitMass_isValid0logMwoHadTauTF;
   Float_t         classicSVfitTransverseMass0logMwoHadTauTF;
   Float_t         classicSVfitTransverseMassErr0logMwoHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid0logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_cpu0logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_real0logMwoHadTauTF;
   Float_t         classicSVfitPt1logMwHadTauTF;
   Float_t         classicSVfitPtErr1logMwHadTauTF;
   Int_t           classicSVfitPt_isValid1logMwHadTauTF;
   Float_t         classicSVfitEta1logMwHadTauTF;
   Float_t         classicSVfitEtaErr1logMwHadTauTF;
   Int_t           classicSVfitEta_isValid1logMwHadTauTF;
   Float_t         classicSVfitPhi1logMwHadTauTF;
   Float_t         classicSVfitPhiErr1logMwHadTauTF;
   Int_t           classicSVfitPhi_isValid1logMwHadTauTF;
   Float_t         classicSVfitMass1logMwHadTauTF;
   Float_t         classicSVfitMassErr1logMwHadTauTF;
   Int_t           classicSVfitMass_isValid1logMwHadTauTF;
   Float_t         classicSVfitTransverseMass1logMwHadTauTF;
   Float_t         classicSVfitTransverseMassErr1logMwHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid1logMwHadTauTF;
   Float_t         classicSVfitComputingTime_cpu1logMwHadTauTF;
   Float_t         classicSVfitComputingTime_real1logMwHadTauTF;
   Float_t         classicSVfitPt1logMwoHadTauTF;
   Float_t         classicSVfitPtErr1logMwoHadTauTF;
   Int_t           classicSVfitPt_isValid1logMwoHadTauTF;
   Float_t         classicSVfitEta1logMwoHadTauTF;
   Float_t         classicSVfitEtaErr1logMwoHadTauTF;
   Int_t           classicSVfitEta_isValid1logMwoHadTauTF;
   Float_t         classicSVfitPhi1logMwoHadTauTF;
   Float_t         classicSVfitPhiErr1logMwoHadTauTF;
   Int_t           classicSVfitPhi_isValid1logMwoHadTauTF;
   Float_t         classicSVfitMass1logMwoHadTauTF;
   Float_t         classicSVfitMassErr1logMwoHadTauTF;
   Int_t           classicSVfitMass_isValid1logMwoHadTauTF;
   Float_t         classicSVfitTransverseMass1logMwoHadTauTF;
   Float_t         classicSVfitTransverseMassErr1logMwoHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid1logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_cpu1logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_real1logMwoHadTauTF;
   Float_t         classicSVfitPt2logMwHadTauTF;
   Float_t         classicSVfitPtErr2logMwHadTauTF;
   Int_t           classicSVfitPt_isValid2logMwHadTauTF;
   Float_t         classicSVfitEta2logMwHadTauTF;
   Float_t         classicSVfitEtaErr2logMwHadTauTF;
   Int_t           classicSVfitEta_isValid2logMwHadTauTF;
   Float_t         classicSVfitPhi2logMwHadTauTF;
   Float_t         classicSVfitPhiErr2logMwHadTauTF;
   Int_t           classicSVfitPhi_isValid2logMwHadTauTF;
   Float_t         classicSVfitMass2logMwHadTauTF;
   Float_t         classicSVfitMassErr2logMwHadTauTF;
   Int_t           classicSVfitMass_isValid2logMwHadTauTF;
   Float_t         classicSVfitTransverseMass2logMwHadTauTF;
   Float_t         classicSVfitTransverseMassErr2logMwHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid2logMwHadTauTF;
   Float_t         classicSVfitComputingTime_cpu2logMwHadTauTF;
   Float_t         classicSVfitComputingTime_real2logMwHadTauTF;
   Float_t         classicSVfitPt2logMwoHadTauTF;
   Float_t         classicSVfitPtErr2logMwoHadTauTF;
   Int_t           classicSVfitPt_isValid2logMwoHadTauTF;
   Float_t         classicSVfitEta2logMwoHadTauTF;
   Float_t         classicSVfitEtaErr2logMwoHadTauTF;
   Int_t           classicSVfitEta_isValid2logMwoHadTauTF;
   Float_t         classicSVfitPhi2logMwoHadTauTF;
   Float_t         classicSVfitPhiErr2logMwoHadTauTF;
   Int_t           classicSVfitPhi_isValid2logMwoHadTauTF;
   Float_t         classicSVfitMass2logMwoHadTauTF;
   Float_t         classicSVfitMassErr2logMwoHadTauTF;
   Int_t           classicSVfitMass_isValid2logMwoHadTauTF;
   Float_t         classicSVfitTransverseMass2logMwoHadTauTF;
   Float_t         classicSVfitTransverseMassErr2logMwoHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid2logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_cpu2logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_real2logMwoHadTauTF;
   Float_t         classicSVfitPt3logMwHadTauTF;
   Float_t         classicSVfitPtErr3logMwHadTauTF;
   Int_t           classicSVfitPt_isValid3logMwHadTauTF;
   Float_t         classicSVfitEta3logMwHadTauTF;
   Float_t         classicSVfitEtaErr3logMwHadTauTF;
   Int_t           classicSVfitEta_isValid3logMwHadTauTF;
   Float_t         classicSVfitPhi3logMwHadTauTF;
   Float_t         classicSVfitPhiErr3logMwHadTauTF;
   Int_t           classicSVfitPhi_isValid3logMwHadTauTF;
   Float_t         classicSVfitMass3logMwHadTauTF;
   Float_t         classicSVfitMassErr3logMwHadTauTF;
   Int_t           classicSVfitMass_isValid3logMwHadTauTF;
   Float_t         classicSVfitTransverseMass3logMwHadTauTF;
   Float_t         classicSVfitTransverseMassErr3logMwHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid3logMwHadTauTF;
   Float_t         classicSVfitComputingTime_cpu3logMwHadTauTF;
   Float_t         classicSVfitComputingTime_real3logMwHadTauTF;
   Float_t         classicSVfitPt3logMwoHadTauTF;
   Float_t         classicSVfitPtErr3logMwoHadTauTF;
   Int_t           classicSVfitPt_isValid3logMwoHadTauTF;
   Float_t         classicSVfitEta3logMwoHadTauTF;
   Float_t         classicSVfitEtaErr3logMwoHadTauTF;
   Int_t           classicSVfitEta_isValid3logMwoHadTauTF;
   Float_t         classicSVfitPhi3logMwoHadTauTF;
   Float_t         classicSVfitPhiErr3logMwoHadTauTF;
   Int_t           classicSVfitPhi_isValid3logMwoHadTauTF;
   Float_t         classicSVfitMass3logMwoHadTauTF;
   Float_t         classicSVfitMassErr3logMwoHadTauTF;
   Int_t           classicSVfitMass_isValid3logMwoHadTauTF;
   Float_t         classicSVfitTransverseMass3logMwoHadTauTF;
   Float_t         classicSVfitTransverseMassErr3logMwoHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid3logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_cpu3logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_real3logMwoHadTauTF;
   Float_t         classicSVfitPt4logMwHadTauTF;
   Float_t         classicSVfitPtErr4logMwHadTauTF;
   Int_t           classicSVfitPt_isValid4logMwHadTauTF;
   Float_t         classicSVfitEta4logMwHadTauTF;
   Float_t         classicSVfitEtaErr4logMwHadTauTF;
   Int_t           classicSVfitEta_isValid4logMwHadTauTF;
   Float_t         classicSVfitPhi4logMwHadTauTF;
   Float_t         classicSVfitPhiErr4logMwHadTauTF;
   Int_t           classicSVfitPhi_isValid4logMwHadTauTF;
   Float_t         classicSVfitMass4logMwHadTauTF;
   Float_t         classicSVfitMassErr4logMwHadTauTF;
   Int_t           classicSVfitMass_isValid4logMwHadTauTF;
   Float_t         classicSVfitTransverseMass4logMwHadTauTF;
   Float_t         classicSVfitTransverseMassErr4logMwHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid4logMwHadTauTF;
   Float_t         classicSVfitComputingTime_cpu4logMwHadTauTF;
   Float_t         classicSVfitComputingTime_real4logMwHadTauTF;
   Float_t         classicSVfitPt4logMwoHadTauTF;
   Float_t         classicSVfitPtErr4logMwoHadTauTF;
   Int_t           classicSVfitPt_isValid4logMwoHadTauTF;
   Float_t         classicSVfitEta4logMwoHadTauTF;
   Float_t         classicSVfitEtaErr4logMwoHadTauTF;
   Int_t           classicSVfitEta_isValid4logMwoHadTauTF;
   Float_t         classicSVfitPhi4logMwoHadTauTF;
   Float_t         classicSVfitPhiErr4logMwoHadTauTF;
   Int_t           classicSVfitPhi_isValid4logMwoHadTauTF;
   Float_t         classicSVfitMass4logMwoHadTauTF;
   Float_t         classicSVfitMassErr4logMwoHadTauTF;
   Int_t           classicSVfitMass_isValid4logMwoHadTauTF;
   Float_t         classicSVfitTransverseMass4logMwoHadTauTF;
   Float_t         classicSVfitTransverseMassErr4logMwoHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid4logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_cpu4logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_real4logMwoHadTauTF;
   Float_t         classicSVfitPt5logMwHadTauTF;
   Float_t         classicSVfitPtErr5logMwHadTauTF;
   Int_t           classicSVfitPt_isValid5logMwHadTauTF;
   Float_t         classicSVfitEta5logMwHadTauTF;
   Float_t         classicSVfitEtaErr5logMwHadTauTF;
   Int_t           classicSVfitEta_isValid5logMwHadTauTF;
   Float_t         classicSVfitPhi5logMwHadTauTF;
   Float_t         classicSVfitPhiErr5logMwHadTauTF;
   Int_t           classicSVfitPhi_isValid5logMwHadTauTF;
   Float_t         classicSVfitMass5logMwHadTauTF;
   Float_t         classicSVfitMassErr5logMwHadTauTF;
   Int_t           classicSVfitMass_isValid5logMwHadTauTF;
   Float_t         classicSVfitTransverseMass5logMwHadTauTF;
   Float_t         classicSVfitTransverseMassErr5logMwHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid5logMwHadTauTF;
   Float_t         classicSVfitComputingTime_cpu5logMwHadTauTF;
   Float_t         classicSVfitComputingTime_real5logMwHadTauTF;
   Float_t         classicSVfitPt5logMwoHadTauTF;
   Float_t         classicSVfitPtErr5logMwoHadTauTF;
   Int_t           classicSVfitPt_isValid5logMwoHadTauTF;
   Float_t         classicSVfitEta5logMwoHadTauTF;
   Float_t         classicSVfitEtaErr5logMwoHadTauTF;
   Int_t           classicSVfitEta_isValid5logMwoHadTauTF;
   Float_t         classicSVfitPhi5logMwoHadTauTF;
   Float_t         classicSVfitPhiErr5logMwoHadTauTF;
   Int_t           classicSVfitPhi_isValid5logMwoHadTauTF;
   Float_t         classicSVfitMass5logMwoHadTauTF;
   Float_t         classicSVfitMassErr5logMwoHadTauTF;
   Int_t           classicSVfitMass_isValid5logMwoHadTauTF;
   Float_t         classicSVfitTransverseMass5logMwoHadTauTF;
   Float_t         classicSVfitTransverseMassErr5logMwoHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid5logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_cpu5logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_real5logMwoHadTauTF;
   Float_t         classicSVfitPt6logMwHadTauTF;
   Float_t         classicSVfitPtErr6logMwHadTauTF;
   Int_t           classicSVfitPt_isValid6logMwHadTauTF;
   Float_t         classicSVfitEta6logMwHadTauTF;
   Float_t         classicSVfitEtaErr6logMwHadTauTF;
   Int_t           classicSVfitEta_isValid6logMwHadTauTF;
   Float_t         classicSVfitPhi6logMwHadTauTF;
   Float_t         classicSVfitPhiErr6logMwHadTauTF;
   Int_t           classicSVfitPhi_isValid6logMwHadTauTF;
   Float_t         classicSVfitMass6logMwHadTauTF;
   Float_t         classicSVfitMassErr6logMwHadTauTF;
   Int_t           classicSVfitMass_isValid6logMwHadTauTF;
   Float_t         classicSVfitTransverseMass6logMwHadTauTF;
   Float_t         classicSVfitTransverseMassErr6logMwHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid6logMwHadTauTF;
   Float_t         classicSVfitComputingTime_cpu6logMwHadTauTF;
   Float_t         classicSVfitComputingTime_real6logMwHadTauTF;
   Float_t         classicSVfitPt6logMwoHadTauTF;
   Float_t         classicSVfitPtErr6logMwoHadTauTF;
   Int_t           classicSVfitPt_isValid6logMwoHadTauTF;
   Float_t         classicSVfitEta6logMwoHadTauTF;
   Float_t         classicSVfitEtaErr6logMwoHadTauTF;
   Int_t           classicSVfitEta_isValid6logMwoHadTauTF;
   Float_t         classicSVfitPhi6logMwoHadTauTF;
   Float_t         classicSVfitPhiErr6logMwoHadTauTF;
   Int_t           classicSVfitPhi_isValid6logMwoHadTauTF;
   Float_t         classicSVfitMass6logMwoHadTauTF;
   Float_t         classicSVfitMassErr6logMwoHadTauTF;
   Int_t           classicSVfitMass_isValid6logMwoHadTauTF;
   Float_t         classicSVfitTransverseMass6logMwoHadTauTF;
   Float_t         classicSVfitTransverseMassErr6logMwoHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid6logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_cpu6logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_real6logMwoHadTauTF;
   Float_t         classicSVfitPt7logMwHadTauTF;
   Float_t         classicSVfitPtErr7logMwHadTauTF;
   Int_t           classicSVfitPt_isValid7logMwHadTauTF;
   Float_t         classicSVfitEta7logMwHadTauTF;
   Float_t         classicSVfitEtaErr7logMwHadTauTF;
   Int_t           classicSVfitEta_isValid7logMwHadTauTF;
   Float_t         classicSVfitPhi7logMwHadTauTF;
   Float_t         classicSVfitPhiErr7logMwHadTauTF;
   Int_t           classicSVfitPhi_isValid7logMwHadTauTF;
   Float_t         classicSVfitMass7logMwHadTauTF;
   Float_t         classicSVfitMassErr7logMwHadTauTF;
   Int_t           classicSVfitMass_isValid7logMwHadTauTF;
   Float_t         classicSVfitTransverseMass7logMwHadTauTF;
   Float_t         classicSVfitTransverseMassErr7logMwHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid7logMwHadTauTF;
   Float_t         classicSVfitComputingTime_cpu7logMwHadTauTF;
   Float_t         classicSVfitComputingTime_real7logMwHadTauTF;
   Float_t         classicSVfitPt7logMwoHadTauTF;
   Float_t         classicSVfitPtErr7logMwoHadTauTF;
   Int_t           classicSVfitPt_isValid7logMwoHadTauTF;
   Float_t         classicSVfitEta7logMwoHadTauTF;
   Float_t         classicSVfitEtaErr7logMwoHadTauTF;
   Int_t           classicSVfitEta_isValid7logMwoHadTauTF;
   Float_t         classicSVfitPhi7logMwoHadTauTF;
   Float_t         classicSVfitPhiErr7logMwoHadTauTF;
   Int_t           classicSVfitPhi_isValid7logMwoHadTauTF;
   Float_t         classicSVfitMass7logMwoHadTauTF;
   Float_t         classicSVfitMassErr7logMwoHadTauTF;
   Int_t           classicSVfitMass_isValid7logMwoHadTauTF;
   Float_t         classicSVfitTransverseMass7logMwoHadTauTF;
   Float_t         classicSVfitTransverseMassErr7logMwoHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid7logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_cpu7logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_real7logMwoHadTauTF;
   Float_t         classicSVfitPt8logMwHadTauTF;
   Float_t         classicSVfitPtErr8logMwHadTauTF;
   Int_t           classicSVfitPt_isValid8logMwHadTauTF;
   Float_t         classicSVfitEta8logMwHadTauTF;
   Float_t         classicSVfitEtaErr8logMwHadTauTF;
   Int_t           classicSVfitEta_isValid8logMwHadTauTF;
   Float_t         classicSVfitPhi8logMwHadTauTF;
   Float_t         classicSVfitPhiErr8logMwHadTauTF;
   Int_t           classicSVfitPhi_isValid8logMwHadTauTF;
   Float_t         classicSVfitMass8logMwHadTauTF;
   Float_t         classicSVfitMassErr8logMwHadTauTF;
   Int_t           classicSVfitMass_isValid8logMwHadTauTF;
   Float_t         classicSVfitTransverseMass8logMwHadTauTF;
   Float_t         classicSVfitTransverseMassErr8logMwHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid8logMwHadTauTF;
   Float_t         classicSVfitComputingTime_cpu8logMwHadTauTF;
   Float_t         classicSVfitComputingTime_real8logMwHadTauTF;
   Float_t         classicSVfitPt8logMwoHadTauTF;
   Float_t         classicSVfitPtErr8logMwoHadTauTF;
   Int_t           classicSVfitPt_isValid8logMwoHadTauTF;
   Float_t         classicSVfitEta8logMwoHadTauTF;
   Float_t         classicSVfitEtaErr8logMwoHadTauTF;
   Int_t           classicSVfitEta_isValid8logMwoHadTauTF;
   Float_t         classicSVfitPhi8logMwoHadTauTF;
   Float_t         classicSVfitPhiErr8logMwoHadTauTF;
   Int_t           classicSVfitPhi_isValid8logMwoHadTauTF;
   Float_t         classicSVfitMass8logMwoHadTauTF;
   Float_t         classicSVfitMassErr8logMwoHadTauTF;
   Int_t           classicSVfitMass_isValid8logMwoHadTauTF;
   Float_t         classicSVfitTransverseMass8logMwoHadTauTF;
   Float_t         classicSVfitTransverseMassErr8logMwoHadTauTF;
   Int_t           classicSVfitTransverseMass_isValid8logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_cpu8logMwoHadTauTF;
   Float_t         classicSVfitComputingTime_real8logMwoHadTauTF;

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
   TBranch        *b_genHadRecoilE;   //!
   TBranch        *b_genHadRecoilPx;   //!
   TBranch        *b_genHadRecoilPy;   //!
   TBranch        *b_genHadRecoilPz;   //!
   TBranch        *b_genHadRecoilPt;   //!
   TBranch        *b_genHadRecoilEta;   //!
   TBranch        *b_genHadRecoilPhi;   //!
   TBranch        *b_genHadRecoilMass;   //!
   TBranch        *b_genHadRecoilCharge;   //!
   TBranch        *b_genHadRecoilCov00;   //!
   TBranch        *b_genHadRecoilCov01;   //!
   TBranch        *b_genHadRecoilCov02;   //!
   TBranch        *b_genHadRecoilCov03;   //!
   TBranch        *b_genHadRecoilCov10;   //!
   TBranch        *b_genHadRecoilCov11;   //!
   TBranch        *b_genHadRecoilCov12;   //!
   TBranch        *b_genHadRecoilCov13;   //!
   TBranch        *b_genHadRecoilCov20;   //!
   TBranch        *b_genHadRecoilCov21;   //!
   TBranch        *b_genHadRecoilCov22;   //!
   TBranch        *b_genHadRecoilCov23;   //!
   TBranch        *b_genHadRecoilCov30;   //!
   TBranch        *b_genHadRecoilCov31;   //!
   TBranch        *b_genHadRecoilCov32;   //!
   TBranch        *b_genHadRecoilCov33;   //!
   TBranch        *b_smearedHadRecoilE;   //!
   TBranch        *b_smearedHadRecoilPx;   //!
   TBranch        *b_smearedHadRecoilPy;   //!
   TBranch        *b_smearedHadRecoilPz;   //!
   TBranch        *b_smearedHadRecoilPt;   //!
   TBranch        *b_smearedHadRecoilEta;   //!
   TBranch        *b_smearedHadRecoilPhi;   //!
   TBranch        *b_smearedHadRecoilMass;   //!
   TBranch        *b_smearedHadRecoilCharge;   //!
   TBranch        *b_smearedHadRecoilCov00;   //!
   TBranch        *b_smearedHadRecoilCov01;   //!
   TBranch        *b_smearedHadRecoilCov02;   //!
   TBranch        *b_smearedHadRecoilCov03;   //!
   TBranch        *b_smearedHadRecoilCov10;   //!
   TBranch        *b_smearedHadRecoilCov11;   //!
   TBranch        *b_smearedHadRecoilCov12;   //!
   TBranch        *b_smearedHadRecoilCov13;   //!
   TBranch        *b_smearedHadRecoilCov20;   //!
   TBranch        *b_smearedHadRecoilCov21;   //!
   TBranch        *b_smearedHadRecoilCov22;   //!
   TBranch        *b_smearedHadRecoilCov23;   //!
   TBranch        *b_smearedHadRecoilCov30;   //!
   TBranch        *b_smearedHadRecoilCov31;   //!
   TBranch        *b_smearedHadRecoilCov32;   //!
   TBranch        *b_smearedHadRecoilCov33;   //!
   TBranch        *b_genJet1E;   //!
   TBranch        *b_genJet1Px;   //!
   TBranch        *b_genJet1Py;   //!
   TBranch        *b_genJet1Pz;   //!
   TBranch        *b_genJet1Pt;   //!
   TBranch        *b_genJet1Eta;   //!
   TBranch        *b_genJet1Phi;   //!
   TBranch        *b_genJet1Mass;   //!
   TBranch        *b_genJet1Charge;   //!
   TBranch        *b_genJet2E;   //!
   TBranch        *b_genJet2Px;   //!
   TBranch        *b_genJet2Py;   //!
   TBranch        *b_genJet2Pz;   //!
   TBranch        *b_genJet2Pt;   //!
   TBranch        *b_genJet2Eta;   //!
   TBranch        *b_genJet2Phi;   //!
   TBranch        *b_genJet2Mass;   //!
   TBranch        *b_genJet2Charge;   //!
   TBranch        *b_genJet3E;   //!
   TBranch        *b_genJet3Px;   //!
   TBranch        *b_genJet3Py;   //!
   TBranch        *b_genJet3Pz;   //!
   TBranch        *b_genJet3Pt;   //!
   TBranch        *b_genJet3Eta;   //!
   TBranch        *b_genJet3Phi;   //!
   TBranch        *b_genJet3Mass;   //!
   TBranch        *b_genJet3Charge;   //!
   TBranch        *b_genJet4E;   //!
   TBranch        *b_genJet4Px;   //!
   TBranch        *b_genJet4Py;   //!
   TBranch        *b_genJet4Pz;   //!
   TBranch        *b_genJet4Pt;   //!
   TBranch        *b_genJet4Eta;   //!
   TBranch        *b_genJet4Phi;   //!
   TBranch        *b_genJet4Mass;   //!
   TBranch        *b_genJet4Charge;   //!
   TBranch        *b_genJet5E;   //!
   TBranch        *b_genJet5Px;   //!
   TBranch        *b_genJet5Py;   //!
   TBranch        *b_genJet5Pz;   //!
   TBranch        *b_genJet5Pt;   //!
   TBranch        *b_genJet5Eta;   //!
   TBranch        *b_genJet5Phi;   //!
   TBranch        *b_genJet5Mass;   //!
   TBranch        *b_genJet5Charge;   //!
   TBranch        *b_genJet6E;   //!
   TBranch        *b_genJet6Px;   //!
   TBranch        *b_genJet6Py;   //!
   TBranch        *b_genJet6Pz;   //!
   TBranch        *b_genJet6Pt;   //!
   TBranch        *b_genJet6Eta;   //!
   TBranch        *b_genJet6Phi;   //!
   TBranch        *b_genJet6Mass;   //!
   TBranch        *b_genJet6Charge;   //!
   TBranch        *b_numGenJets;   //!
   TBranch        *b_genBosonE;   //!
   TBranch        *b_genBosonPx;   //!
   TBranch        *b_genBosonPy;   //!
   TBranch        *b_genBosonPz;   //!
   TBranch        *b_genBosonPt;   //!
   TBranch        *b_genBosonEta;   //!
   TBranch        *b_genBosonPhi;   //!
   TBranch        *b_genBosonMass;   //!
   TBranch        *b_genBosonCharge;   //!
   TBranch        *b_genBosonPdgId;   //!
   TBranch        *b_genBosonDaughter1E;   //!
   TBranch        *b_genBosonDaughter1Px;   //!
   TBranch        *b_genBosonDaughter1Py;   //!
   TBranch        *b_genBosonDaughter1Pz;   //!
   TBranch        *b_genBosonDaughter1Pt;   //!
   TBranch        *b_genBosonDaughter1Eta;   //!
   TBranch        *b_genBosonDaughter1Phi;   //!
   TBranch        *b_genBosonDaughter1Mass;   //!
   TBranch        *b_genBosonDaughter1Charge;   //!
   TBranch        *b_genBosonDaughter1PdgId;   //!
   TBranch        *b_genBosonDaughter2E;   //!
   TBranch        *b_genBosonDaughter2Px;   //!
   TBranch        *b_genBosonDaughter2Py;   //!
   TBranch        *b_genBosonDaughter2Pz;   //!
   TBranch        *b_genBosonDaughter2Pt;   //!
   TBranch        *b_genBosonDaughter2Eta;   //!
   TBranch        *b_genBosonDaughter2Phi;   //!
   TBranch        *b_genBosonDaughter2Mass;   //!
   TBranch        *b_genBosonDaughter2Charge;   //!
   TBranch        *b_genBosonDaughter2PdgId;   //!
   TBranch        *b_visMass;   //!
   TBranch        *b_caMass;   //!
   TBranch        *b_caMass_isValid;   //!
   TBranch        *b_mTtotal;   //!
   TBranch        *b_svfitPt;   //!
   TBranch        *b_svfitPtErr;   //!
   TBranch        *b_svfitPt_isValid;   //!
   TBranch        *b_svfitEta;   //!
   TBranch        *b_svfitEtaErr;   //!
   TBranch        *b_svfitEta_isValid;   //!
   TBranch        *b_svfitPhi;   //!
   TBranch        *b_svfitPhiErr;   //!
   TBranch        *b_svfitPhi_isValid;   //!
   TBranch        *b_svfitMass;   //!
   TBranch        *b_svfitMassErr;   //!
   TBranch        *b_svfitMass_isValid;   //!
   TBranch        *b_svfitTransverseMass;   //!
   TBranch        *b_svfitTransverseMassErr;   //!
   TBranch        *b_svfitTransverseMass_isValid;   //!
   TBranch        *b_svfitComputingTime_cpu;   //!
   TBranch        *b_svfitComputingTime_real;   //!
   TBranch        *b_svfitMassMEMlo0logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo0logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo0logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo0logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo0logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo0logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo0logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo0logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo0logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo0logMwoHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo1logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo1logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo1logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo1logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo1logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo1logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo1logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo1logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo1logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo1logMwoHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo2logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo2logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo2logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo2logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo2logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo2logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo2logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo2logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo2logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo2logMwoHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo3logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo3logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo3logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo3logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo3logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo3logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo3logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo3logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo3logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo3logMwoHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo4logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo4logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo4logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo4logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo4logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo4logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo4logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo4logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo4logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo4logMwoHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo5logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo5logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo5logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo5logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo5logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo5logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo5logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo5logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo5logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo5logMwoHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo6logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo6logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo6logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo6logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo6logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo6logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo6logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo6logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo6logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo6logMwoHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo7logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo7logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo7logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo7logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo7logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo7logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo7logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo7logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo7logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo7logMwoHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo8logMwHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo8logMwHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo8logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo8logMwHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo8logMwHadTauTF;   //!
   TBranch        *b_svfitMassMEMlo8logMwoHadTauTF;   //!
   TBranch        *b_svfitMassErrMEMlo8logMwoHadTauTF;   //!
   TBranch        *b_svfitMass_isValidMEMlo8logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_cpuMEMlo8logMwoHadTauTF;   //!
   TBranch        *b_svfitComputingTime_realMEMlo8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real0logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real0logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real1logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real1logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real2logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real2logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real3logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real3logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real4logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real4logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real5logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real5logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real6logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real6logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real7logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real7logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real8logMwHadTauTF;   //!
   TBranch        *b_classicSVfitPt8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPtErr8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPt_isValid8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEtaErr8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitEta_isValid8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhiErr8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitPhi_isValid8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMassErr8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitMass_isValid8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMassErr8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitTransverseMass_isValid8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_cpu8logMwoHadTauTF;   //!
   TBranch        *b_classicSVfitComputingTime_real8logMwoHadTauTF;   //!

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

   bool passKin;
   bool isEMU;
   bool isMUHAD;
   bool isHADHAD;
   bool isGEN;
   bool isSMEARED;

   int nplotToInclude;
   int nplotToIncludeForCPU;
   int nplotToIncludeForResolution;

   TH1D *hmass[21];    //very fine binning for the computation of S/TMath::Sqrt(B)
   TH1D *hmasslin[21]; //3 standard + 9 k SVfitMEM + 9 k Classic SVfit = 21
   TH1D *hmasslog[21];
   TH1D *hmasslin_ratio[21];
   TH1D *hmasslog_ratio[21];
   TH1D *hCPUtime_log[19];  
   TH1D *hResolutionPt[10];
   TH1D *hResolutionEta[10];
   TH1D *hResolutionPhi[10];
   TH1D *hmass_SVFIT_grt_270;
   TH1D *hmass_SVFIT_lst_120;
   TH1D *hmass_SVFIT_grt_270_ratio;
   TH1D *hmass_SVFIT_lst_120_ratio;
   TH1D *hDiTauPt;
   TH1D *hTauDPhi;
   TH1D *hpt1_SVFIT_grt_270;
   TH1D *hpt1_SVFIT_lst_120;
   TH1D *hpt2_SVFIT_grt_270;
   TH1D *hpt2_SVFIT_lst_120;
   TH1D *hmet_SVFIT_grt_270;
   TH1D *hmet_SVFIT_lst_120;
   TH1I *hpassCuts;
};

#endif

#ifdef SVfitMEM_cxx
#include "getLogBinning.C"

SVfitMEM::SVfitMEM(TTree *tree, std::string dir, std::string sample, double mass) : fChain(0), dir{dir}, sample{sample}, mass{mass} 
{

	Init(tree);
	TH1::SetDefaultSumw2();

	std::map<int, double> xMax;
	xMax[50]   = 450;
	xMax[90]   = 500; //added by Lucia
	xMax[125]  = 620; 
	xMax[200]  = 1000;
	xMax[300]  = 1500;
	xMax[500]  = 2500;
	xMax[800]  = 4000;
	xMax[1200] = 6000;
	xMax[1800] = 9000;
	xMax[2500] = 10000;
	xMax[2600] = 13000;

	//bin for tables
	int numbin=0;
	if(dir.find("emu")!=std::string::npos) numbin=xMax[mass]-30;
	else numbin=xMax[mass]-50;

        //for the ratio plots  40, getLogBinning(0.1, 10.0, 40).GetArray
        //

	std::vector<std::string> vplotToInclude {"vismass", "ca", "svFit",
		"svfitmemtfk0","svfitmemtfk1","svfitmemtfk2","svfitmemtfk3","svfitmemtfk4","svfitmemtfk5","svfitmemtfk6","svfitmemtfk7","svfitmemtfk8",
		"svfitclatfk0","svfitclatfk1","svfitclatfk2","svfitclatfk3","svfitclatfk4","svfitclatfk5","svfitclatfk6","svfitclatfk7","svfitclatfk8"};
	nplotToInclude=vplotToInclude.size();

        std::vector<std::string> vplotToIncludeForCPU {"svfitComputingTime_cpu","memSVfitComputingTime_cpulo0","memSVfitComputingTime_cpulo1", 
        "memSVfitComputingTime_cpulo2","memSVfitComputingTime_cpulo3","memSVfitComputingTime_cpulo4","memSVfitComputingTime_cpulo5", 
        "memSVfitComputingTime_cpulo6","memSVfitComputingTime_cpulo7","memSVfitComputingTime_cpulo8","classicSVfitComputingTime_cpu0", 
	"classicSVfitComputingTime_cpu1","classicSVfitComputingTime_cpu2","classicSVfitComputingTime_cpu3","classicSVfitComputingTime_cpu4", 
	"classicSVfitComputingTime_cpu5","classicSVfitComputingTime_cpu6","classicSVfitComputingTime_cpu7","classicSVfitComputingTime_cpu8"}; 
        nplotToIncludeForCPU=vplotToIncludeForCPU.size();
        
        std::vector<std::string> vplotToIncludeForResolution {"genMinusVisible","genMinusClassicSVfitComputingTime_cpu0",
        "genMinusClassicSVfitComputingTime_cpu1","genMinusClassicSVfitComputingTime_cpu2",
        "genMinusClassicSVfitComputingTime_cpu3","genMinusClassicSVfitComputingTime_cpu4","genMinusClassicSVfitComputingTime_cpu5",
        "genMinusClassicSVfitComputingTime_cpu6","genMinusClassicSVfitComputingTime_cpu7","genMinusClassicSVfitComputingTime_cpu8"}; 
        nplotToIncludeForResolution=vplotToIncludeForResolution.size();

        hpassCuts= new TH1I("hcut","hcut", 1, 0, 1);
	hmass_SVFIT_grt_270 = new TH1D(("mVis_SVFIT_grt_270_"+dir).c_str(),("mVis_SVFIT_grt_270_"+dir).c_str(), numbin, xMax[mass]-numbin, xMax[mass]);	
	hmass_SVFIT_lst_120 = new TH1D(("mVis_SVFIT_lst_120_"+dir).c_str(),("mVis_SVFIT_lst_120_"+dir).c_str(), numbin, xMax[mass]-numbin, xMax[mass]);
	hmass_SVFIT_grt_270_ratio = new TH1D(("mVis_SVFIT_grt_270_ratio_"+dir).c_str(),("mVis_SVFIT_grt_270_ratio_"+dir).c_str(), 100,0,10);	
	hmass_SVFIT_lst_120_ratio = new TH1D(("mVis_SVFIT_lst_120_ratio_"+dir).c_str(),("mVis_SVFIT_lst_120_ratio_"+dir).c_str(), 100,0,10);
        hDiTauPt            = new TH1D(("diTauPt_"+dir).c_str(),("diTauPt_"+dir).c_str(), 100,0,1000);
        hTauDPhi            = new TH1D(("tauDPhi_"+dir).c_str(),("tauDPhi_"+dir).c_str(), 100,-5,5);
	hpt1_SVFIT_grt_270 = new TH1D(("pT1_SVFIT_grt_270_"+dir).c_str(),("pT1_SVFIT_grt_270_"+dir).c_str(), 100,0,1000); 
	hpt2_SVFIT_grt_270 = new TH1D(("pT2_SVFIT_grt_270_"+dir).c_str(),("pT2_SVFIT_grt_270_"+dir).c_str(), 100,0,1000); 
	hpt1_SVFIT_lst_120 = new TH1D(("pT1_SVFIT_lst_120_"+dir).c_str(),("pT1_SVFIT_lst_120_"+dir).c_str(), 100,0,1000); 
	hpt2_SVFIT_lst_120 = new TH1D(("pT2_SVFIT_lst_120_"+dir).c_str(),("pT2_SVFIT_lst_120_"+dir).c_str(), 100,0,1000); 
	hmet_SVFIT_grt_270 = new TH1D(("MET_SVFIT_grt_270_"+dir).c_str(),("MET_SVFIT_grt_270_"+dir).c_str(), 100,0,1000); 
	hmet_SVFIT_lst_120 = new TH1D(("MET_SVFIT_lst_120_"+dir).c_str(),("MET_SVFIT_lst_120_"+dir).c_str(), 100,0,1000); 

	for(int iplot=0; iplot<nplotToInclude; iplot++) {
		TH1D *tmp_h = new TH1D((dir+"_"+vplotToInclude[iplot]+"_fine_bin").c_str(),
				(vplotToInclude[iplot]+"_fine_bin").c_str(), 12000,0,6000);

		TH1D *tmp_hlog = new TH1D((dir+"_"+vplotToInclude[iplot]+"_LOG").c_str(),
				(vplotToInclude[iplot]+"_LOG").c_str(),numbin, getLogBinning(xMax[mass]-numbin, xMax[mass], numbin).GetArray());
		TH1D *tmp_hlin = new TH1D((dir+"_"+vplotToInclude[iplot]+"_LIN").c_str(),
				(vplotToInclude[iplot]+"_LIN").c_str(),numbin, xMax[mass]-numbin, xMax[mass]);
		TH1D *tmp_hlog_ratio = new TH1D((dir+"_"+vplotToInclude[iplot]+"_ratio_LOG").c_str(),
				(vplotToInclude[iplot]+"_ratio_LOG").c_str(), 25, getLogBinning(0.1, 10.0, 25).GetArray() );
		//TH1D *tmp_hlog_ratio = new TH1D((dir+"_"+vplotToInclude[iplot]+"_ratio_LOG").c_str(),
		//		(vplotToInclude[iplot]+"_ratio_LOG").c_str(), 40, getLogBinning(0.1, 10.0, 40).GetArray() );
		TH1D *tmp_hlin_ratio = new TH1D((dir+"_"+vplotToInclude[iplot]+"_ratio_LIN").c_str(),
				(vplotToInclude[iplot]+"_ratio_LIN").c_str(),100,0.01,10);
		hmass[iplot]          = (TH1D*)tmp_h->Clone();
		hmasslog[iplot]       = (TH1D*)tmp_hlog->Clone();
		hmasslin[iplot]       = (TH1D*)tmp_hlin->Clone();
		hmasslog_ratio[iplot] = (TH1D*)tmp_hlog_ratio->Clone();
		hmasslin_ratio[iplot] = (TH1D*)tmp_hlin_ratio->Clone();
	}

	for(int iplot=0; iplot<nplotToIncludeForCPU; iplot++) {
		TH1D *tmp_hCPU = new TH1D((dir+"_"+vplotToIncludeForCPU[iplot]+"_LOG").c_str(),
				(vplotToIncludeForCPU[iplot]+"_LOG").c_str(), 80, getLogBinning(0.1, 1000.0, 80).GetArray() );
                hCPUtime_log[iplot] = (TH1D*)tmp_hCPU->Clone();
	}
	for(int iplot=0; iplot<nplotToIncludeForResolution; iplot++) {
		TH1D *tmp_resolution_pt = new TH1D((dir+"_"+vplotToIncludeForResolution[iplot]+"_pt").c_str(),
				(vplotToIncludeForResolution[iplot]+"_pt").c_str(),700,-100,250);
		TH1D *tmp_resolution_eta = new TH1D((dir+"_"+vplotToIncludeForResolution[iplot]+"_eta").c_str(),
				(vplotToIncludeForResolution[iplot]+"_eta").c_str(),100,-5,5);
		TH1D *tmp_resolution_phi = new TH1D((dir+"_"+vplotToIncludeForResolution[iplot]+"_phi").c_str(),
				(vplotToIncludeForResolution[iplot]+"_phi").c_str(),100,-5,5);
                hResolutionPt[iplot]  = (TH1D*)tmp_resolution_pt->Clone();
                hResolutionPhi[iplot] = (TH1D*)tmp_resolution_phi->Clone();
                hResolutionEta[iplot] = (TH1D*)tmp_resolution_eta->Clone();
	}


}

SVfitMEM::~SVfitMEM()
{
	if (!fChain) return;
	delete fChain->GetCurrentFile();
	//for(int i=0; i<3; i++ ) { delete hmasslin[i]; delete hmasslog[i]; }
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
   fChain->SetBranchAddress("genHadRecoilE", &genHadRecoilE, &b_genHadRecoilE);
   fChain->SetBranchAddress("genHadRecoilPx", &genHadRecoilPx, &b_genHadRecoilPx);
   fChain->SetBranchAddress("genHadRecoilPy", &genHadRecoilPy, &b_genHadRecoilPy);
   fChain->SetBranchAddress("genHadRecoilPz", &genHadRecoilPz, &b_genHadRecoilPz);
   fChain->SetBranchAddress("genHadRecoilPt", &genHadRecoilPt, &b_genHadRecoilPt);
   fChain->SetBranchAddress("genHadRecoilEta", &genHadRecoilEta, &b_genHadRecoilEta);
   fChain->SetBranchAddress("genHadRecoilPhi", &genHadRecoilPhi, &b_genHadRecoilPhi);
   fChain->SetBranchAddress("genHadRecoilMass", &genHadRecoilMass, &b_genHadRecoilMass);
   fChain->SetBranchAddress("genHadRecoilCharge", &genHadRecoilCharge, &b_genHadRecoilCharge);
   fChain->SetBranchAddress("genHadRecoilCov00", &genHadRecoilCov00, &b_genHadRecoilCov00);
   fChain->SetBranchAddress("genHadRecoilCov01", &genHadRecoilCov01, &b_genHadRecoilCov01);
   fChain->SetBranchAddress("genHadRecoilCov02", &genHadRecoilCov02, &b_genHadRecoilCov02);
   fChain->SetBranchAddress("genHadRecoilCov03", &genHadRecoilCov03, &b_genHadRecoilCov03);
   fChain->SetBranchAddress("genHadRecoilCov10", &genHadRecoilCov10, &b_genHadRecoilCov10);
   fChain->SetBranchAddress("genHadRecoilCov11", &genHadRecoilCov11, &b_genHadRecoilCov11);
   fChain->SetBranchAddress("genHadRecoilCov12", &genHadRecoilCov12, &b_genHadRecoilCov12);
   fChain->SetBranchAddress("genHadRecoilCov13", &genHadRecoilCov13, &b_genHadRecoilCov13);
   fChain->SetBranchAddress("genHadRecoilCov20", &genHadRecoilCov20, &b_genHadRecoilCov20);
   fChain->SetBranchAddress("genHadRecoilCov21", &genHadRecoilCov21, &b_genHadRecoilCov21);
   fChain->SetBranchAddress("genHadRecoilCov22", &genHadRecoilCov22, &b_genHadRecoilCov22);
   fChain->SetBranchAddress("genHadRecoilCov23", &genHadRecoilCov23, &b_genHadRecoilCov23);
   fChain->SetBranchAddress("genHadRecoilCov30", &genHadRecoilCov30, &b_genHadRecoilCov30);
   fChain->SetBranchAddress("genHadRecoilCov31", &genHadRecoilCov31, &b_genHadRecoilCov31);
   fChain->SetBranchAddress("genHadRecoilCov32", &genHadRecoilCov32, &b_genHadRecoilCov32);
   fChain->SetBranchAddress("genHadRecoilCov33", &genHadRecoilCov33, &b_genHadRecoilCov33);
   fChain->SetBranchAddress("smearedHadRecoilE", &smearedHadRecoilE, &b_smearedHadRecoilE);
   fChain->SetBranchAddress("smearedHadRecoilPx", &smearedHadRecoilPx, &b_smearedHadRecoilPx);
   fChain->SetBranchAddress("smearedHadRecoilPy", &smearedHadRecoilPy, &b_smearedHadRecoilPy);
   fChain->SetBranchAddress("smearedHadRecoilPz", &smearedHadRecoilPz, &b_smearedHadRecoilPz);
   fChain->SetBranchAddress("smearedHadRecoilPt", &smearedHadRecoilPt, &b_smearedHadRecoilPt);
   fChain->SetBranchAddress("smearedHadRecoilEta", &smearedHadRecoilEta, &b_smearedHadRecoilEta);
   fChain->SetBranchAddress("smearedHadRecoilPhi", &smearedHadRecoilPhi, &b_smearedHadRecoilPhi);
   fChain->SetBranchAddress("smearedHadRecoilMass", &smearedHadRecoilMass, &b_smearedHadRecoilMass);
   fChain->SetBranchAddress("smearedHadRecoilCharge", &smearedHadRecoilCharge, &b_smearedHadRecoilCharge);
   fChain->SetBranchAddress("smearedHadRecoilCov00", &smearedHadRecoilCov00, &b_smearedHadRecoilCov00);
   fChain->SetBranchAddress("smearedHadRecoilCov01", &smearedHadRecoilCov01, &b_smearedHadRecoilCov01);
   fChain->SetBranchAddress("smearedHadRecoilCov02", &smearedHadRecoilCov02, &b_smearedHadRecoilCov02);
   fChain->SetBranchAddress("smearedHadRecoilCov03", &smearedHadRecoilCov03, &b_smearedHadRecoilCov03);
   fChain->SetBranchAddress("smearedHadRecoilCov10", &smearedHadRecoilCov10, &b_smearedHadRecoilCov10);
   fChain->SetBranchAddress("smearedHadRecoilCov11", &smearedHadRecoilCov11, &b_smearedHadRecoilCov11);
   fChain->SetBranchAddress("smearedHadRecoilCov12", &smearedHadRecoilCov12, &b_smearedHadRecoilCov12);
   fChain->SetBranchAddress("smearedHadRecoilCov13", &smearedHadRecoilCov13, &b_smearedHadRecoilCov13);
   fChain->SetBranchAddress("smearedHadRecoilCov20", &smearedHadRecoilCov20, &b_smearedHadRecoilCov20);
   fChain->SetBranchAddress("smearedHadRecoilCov21", &smearedHadRecoilCov21, &b_smearedHadRecoilCov21);
   fChain->SetBranchAddress("smearedHadRecoilCov22", &smearedHadRecoilCov22, &b_smearedHadRecoilCov22);
   fChain->SetBranchAddress("smearedHadRecoilCov23", &smearedHadRecoilCov23, &b_smearedHadRecoilCov23);
   fChain->SetBranchAddress("smearedHadRecoilCov30", &smearedHadRecoilCov30, &b_smearedHadRecoilCov30);
   fChain->SetBranchAddress("smearedHadRecoilCov31", &smearedHadRecoilCov31, &b_smearedHadRecoilCov31);
   fChain->SetBranchAddress("smearedHadRecoilCov32", &smearedHadRecoilCov32, &b_smearedHadRecoilCov32);
   fChain->SetBranchAddress("smearedHadRecoilCov33", &smearedHadRecoilCov33, &b_smearedHadRecoilCov33);
   fChain->SetBranchAddress("genJet1E", &genJet1E, &b_genJet1E);
   fChain->SetBranchAddress("genJet1Px", &genJet1Px, &b_genJet1Px);
   fChain->SetBranchAddress("genJet1Py", &genJet1Py, &b_genJet1Py);
   fChain->SetBranchAddress("genJet1Pz", &genJet1Pz, &b_genJet1Pz);
   fChain->SetBranchAddress("genJet1Pt", &genJet1Pt, &b_genJet1Pt);
   fChain->SetBranchAddress("genJet1Eta", &genJet1Eta, &b_genJet1Eta);
   fChain->SetBranchAddress("genJet1Phi", &genJet1Phi, &b_genJet1Phi);
   fChain->SetBranchAddress("genJet1Mass", &genJet1Mass, &b_genJet1Mass);
   fChain->SetBranchAddress("genJet1Charge", &genJet1Charge, &b_genJet1Charge);
   fChain->SetBranchAddress("genJet2E", &genJet2E, &b_genJet2E);
   fChain->SetBranchAddress("genJet2Px", &genJet2Px, &b_genJet2Px);
   fChain->SetBranchAddress("genJet2Py", &genJet2Py, &b_genJet2Py);
   fChain->SetBranchAddress("genJet2Pz", &genJet2Pz, &b_genJet2Pz);
   fChain->SetBranchAddress("genJet2Pt", &genJet2Pt, &b_genJet2Pt);
   fChain->SetBranchAddress("genJet2Eta", &genJet2Eta, &b_genJet2Eta);
   fChain->SetBranchAddress("genJet2Phi", &genJet2Phi, &b_genJet2Phi);
   fChain->SetBranchAddress("genJet2Mass", &genJet2Mass, &b_genJet2Mass);
   fChain->SetBranchAddress("genJet2Charge", &genJet2Charge, &b_genJet2Charge);
   fChain->SetBranchAddress("genJet3E", &genJet3E, &b_genJet3E);
   fChain->SetBranchAddress("genJet3Px", &genJet3Px, &b_genJet3Px);
   fChain->SetBranchAddress("genJet3Py", &genJet3Py, &b_genJet3Py);
   fChain->SetBranchAddress("genJet3Pz", &genJet3Pz, &b_genJet3Pz);
   fChain->SetBranchAddress("genJet3Pt", &genJet3Pt, &b_genJet3Pt);
   fChain->SetBranchAddress("genJet3Eta", &genJet3Eta, &b_genJet3Eta);
   fChain->SetBranchAddress("genJet3Phi", &genJet3Phi, &b_genJet3Phi);
   fChain->SetBranchAddress("genJet3Mass", &genJet3Mass, &b_genJet3Mass);
   fChain->SetBranchAddress("genJet3Charge", &genJet3Charge, &b_genJet3Charge);
   fChain->SetBranchAddress("genJet4E", &genJet4E, &b_genJet4E);
   fChain->SetBranchAddress("genJet4Px", &genJet4Px, &b_genJet4Px);
   fChain->SetBranchAddress("genJet4Py", &genJet4Py, &b_genJet4Py);
   fChain->SetBranchAddress("genJet4Pz", &genJet4Pz, &b_genJet4Pz);
   fChain->SetBranchAddress("genJet4Pt", &genJet4Pt, &b_genJet4Pt);
   fChain->SetBranchAddress("genJet4Eta", &genJet4Eta, &b_genJet4Eta);
   fChain->SetBranchAddress("genJet4Phi", &genJet4Phi, &b_genJet4Phi);
   fChain->SetBranchAddress("genJet4Mass", &genJet4Mass, &b_genJet4Mass);
   fChain->SetBranchAddress("genJet4Charge", &genJet4Charge, &b_genJet4Charge);
   fChain->SetBranchAddress("genJet5E", &genJet5E, &b_genJet5E);
   fChain->SetBranchAddress("genJet5Px", &genJet5Px, &b_genJet5Px);
   fChain->SetBranchAddress("genJet5Py", &genJet5Py, &b_genJet5Py);
   fChain->SetBranchAddress("genJet5Pz", &genJet5Pz, &b_genJet5Pz);
   fChain->SetBranchAddress("genJet5Pt", &genJet5Pt, &b_genJet5Pt);
   fChain->SetBranchAddress("genJet5Eta", &genJet5Eta, &b_genJet5Eta);
   fChain->SetBranchAddress("genJet5Phi", &genJet5Phi, &b_genJet5Phi);
   fChain->SetBranchAddress("genJet5Mass", &genJet5Mass, &b_genJet5Mass);
   fChain->SetBranchAddress("genJet5Charge", &genJet5Charge, &b_genJet5Charge);
   fChain->SetBranchAddress("genJet6E", &genJet6E, &b_genJet6E);
   fChain->SetBranchAddress("genJet6Px", &genJet6Px, &b_genJet6Px);
   fChain->SetBranchAddress("genJet6Py", &genJet6Py, &b_genJet6Py);
   fChain->SetBranchAddress("genJet6Pz", &genJet6Pz, &b_genJet6Pz);
   fChain->SetBranchAddress("genJet6Pt", &genJet6Pt, &b_genJet6Pt);
   fChain->SetBranchAddress("genJet6Eta", &genJet6Eta, &b_genJet6Eta);
   fChain->SetBranchAddress("genJet6Phi", &genJet6Phi, &b_genJet6Phi);
   fChain->SetBranchAddress("genJet6Mass", &genJet6Mass, &b_genJet6Mass);
   fChain->SetBranchAddress("genJet6Charge", &genJet6Charge, &b_genJet6Charge);
   fChain->SetBranchAddress("numGenJets", &numGenJets, &b_numGenJets);
   fChain->SetBranchAddress("genBosonE", &genBosonE, &b_genBosonE);
   fChain->SetBranchAddress("genBosonPx", &genBosonPx, &b_genBosonPx);
   fChain->SetBranchAddress("genBosonPy", &genBosonPy, &b_genBosonPy);
   fChain->SetBranchAddress("genBosonPz", &genBosonPz, &b_genBosonPz);
   fChain->SetBranchAddress("genBosonPt", &genBosonPt, &b_genBosonPt);
   fChain->SetBranchAddress("genBosonEta", &genBosonEta, &b_genBosonEta);
   fChain->SetBranchAddress("genBosonPhi", &genBosonPhi, &b_genBosonPhi);
   fChain->SetBranchAddress("genBosonMass", &genBosonMass, &b_genBosonMass);
   fChain->SetBranchAddress("genBosonCharge", &genBosonCharge, &b_genBosonCharge);
   fChain->SetBranchAddress("genBosonPdgId", &genBosonPdgId, &b_genBosonPdgId);
   fChain->SetBranchAddress("genBosonDaughter1E", &genBosonDaughter1E, &b_genBosonDaughter1E);
   fChain->SetBranchAddress("genBosonDaughter1Px", &genBosonDaughter1Px, &b_genBosonDaughter1Px);
   fChain->SetBranchAddress("genBosonDaughter1Py", &genBosonDaughter1Py, &b_genBosonDaughter1Py);
   fChain->SetBranchAddress("genBosonDaughter1Pz", &genBosonDaughter1Pz, &b_genBosonDaughter1Pz);
   fChain->SetBranchAddress("genBosonDaughter1Pt", &genBosonDaughter1Pt, &b_genBosonDaughter1Pt);
   fChain->SetBranchAddress("genBosonDaughter1Eta", &genBosonDaughter1Eta, &b_genBosonDaughter1Eta);
   fChain->SetBranchAddress("genBosonDaughter1Phi", &genBosonDaughter1Phi, &b_genBosonDaughter1Phi);
   fChain->SetBranchAddress("genBosonDaughter1Mass", &genBosonDaughter1Mass, &b_genBosonDaughter1Mass);
   fChain->SetBranchAddress("genBosonDaughter1Charge", &genBosonDaughter1Charge, &b_genBosonDaughter1Charge);
   fChain->SetBranchAddress("genBosonDaughter1PdgId", &genBosonDaughter1PdgId, &b_genBosonDaughter1PdgId);
   fChain->SetBranchAddress("genBosonDaughter2E", &genBosonDaughter2E, &b_genBosonDaughter2E);
   fChain->SetBranchAddress("genBosonDaughter2Px", &genBosonDaughter2Px, &b_genBosonDaughter2Px);
   fChain->SetBranchAddress("genBosonDaughter2Py", &genBosonDaughter2Py, &b_genBosonDaughter2Py);
   fChain->SetBranchAddress("genBosonDaughter2Pz", &genBosonDaughter2Pz, &b_genBosonDaughter2Pz);
   fChain->SetBranchAddress("genBosonDaughter2Pt", &genBosonDaughter2Pt, &b_genBosonDaughter2Pt);
   fChain->SetBranchAddress("genBosonDaughter2Eta", &genBosonDaughter2Eta, &b_genBosonDaughter2Eta);
   fChain->SetBranchAddress("genBosonDaughter2Phi", &genBosonDaughter2Phi, &b_genBosonDaughter2Phi);
   fChain->SetBranchAddress("genBosonDaughter2Mass", &genBosonDaughter2Mass, &b_genBosonDaughter2Mass);
   fChain->SetBranchAddress("genBosonDaughter2Charge", &genBosonDaughter2Charge, &b_genBosonDaughter2Charge);
   fChain->SetBranchAddress("genBosonDaughter2PdgId", &genBosonDaughter2PdgId, &b_genBosonDaughter2PdgId);
   fChain->SetBranchAddress("visMass", &visMass, &b_visMass);
   fChain->SetBranchAddress("caMass", &caMass, &b_caMass);
   fChain->SetBranchAddress("caMass_isValid", &caMass_isValid, &b_caMass_isValid);
   fChain->SetBranchAddress("mTtotal", &mTtotal, &b_mTtotal);
   fChain->SetBranchAddress("svfitPt", &svfitPt, &b_svfitPt);
   fChain->SetBranchAddress("svfitPtErr", &svfitPtErr, &b_svfitPtErr);
   fChain->SetBranchAddress("svfitPt_isValid", &svfitPt_isValid, &b_svfitPt_isValid);
   fChain->SetBranchAddress("svfitEta", &svfitEta, &b_svfitEta);
   fChain->SetBranchAddress("svfitEtaErr", &svfitEtaErr, &b_svfitEtaErr);
   fChain->SetBranchAddress("svfitEta_isValid", &svfitEta_isValid, &b_svfitEta_isValid);
   fChain->SetBranchAddress("svfitPhi", &svfitPhi, &b_svfitPhi);
   fChain->SetBranchAddress("svfitPhiErr", &svfitPhiErr, &b_svfitPhiErr);
   fChain->SetBranchAddress("svfitPhi_isValid", &svfitPhi_isValid, &b_svfitPhi_isValid);
   fChain->SetBranchAddress("svfitMass", &svfitMass, &b_svfitMass);
   fChain->SetBranchAddress("svfitMassErr", &svfitMassErr, &b_svfitMassErr);
   fChain->SetBranchAddress("svfitMass_isValid", &svfitMass_isValid, &b_svfitMass_isValid);
   fChain->SetBranchAddress("svfitTransverseMass", &svfitTransverseMass, &b_svfitTransverseMass);
   fChain->SetBranchAddress("svfitTransverseMassErr", &svfitTransverseMassErr, &b_svfitTransverseMassErr);
   fChain->SetBranchAddress("svfitTransverseMass_isValid", &svfitTransverseMass_isValid, &b_svfitTransverseMass_isValid);
   fChain->SetBranchAddress("svfitComputingTime_cpu", &svfitComputingTime_cpu, &b_svfitComputingTime_cpu);
   fChain->SetBranchAddress("svfitComputingTime_real", &svfitComputingTime_real, &b_svfitComputingTime_real);
   fChain->SetBranchAddress("svfitMassMEMlo0logMwHadTauTF", &svfitMassMEMlo0logMwHadTauTF, &b_svfitMassMEMlo0logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo0logMwHadTauTF", &svfitMassErrMEMlo0logMwHadTauTF, &b_svfitMassErrMEMlo0logMwHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo0logMwHadTauTF", &svfitMass_isValidMEMlo0logMwHadTauTF, &b_svfitMass_isValidMEMlo0logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo0logMwHadTauTF", &svfitComputingTime_cpuMEMlo0logMwHadTauTF, &b_svfitComputingTime_cpuMEMlo0logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo0logMwHadTauTF", &svfitComputingTime_realMEMlo0logMwHadTauTF, &b_svfitComputingTime_realMEMlo0logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo0logMwoHadTauTF", &svfitMassMEMlo0logMwoHadTauTF, &b_svfitMassMEMlo0logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo0logMwoHadTauTF", &svfitMassErrMEMlo0logMwoHadTauTF, &b_svfitMassErrMEMlo0logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo0logMwoHadTauTF", &svfitMass_isValidMEMlo0logMwoHadTauTF, &b_svfitMass_isValidMEMlo0logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo0logMwoHadTauTF", &svfitComputingTime_cpuMEMlo0logMwoHadTauTF, &b_svfitComputingTime_cpuMEMlo0logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo0logMwoHadTauTF", &svfitComputingTime_realMEMlo0logMwoHadTauTF, &b_svfitComputingTime_realMEMlo0logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo1logMwHadTauTF", &svfitMassMEMlo1logMwHadTauTF, &b_svfitMassMEMlo1logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo1logMwHadTauTF", &svfitMassErrMEMlo1logMwHadTauTF, &b_svfitMassErrMEMlo1logMwHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo1logMwHadTauTF", &svfitMass_isValidMEMlo1logMwHadTauTF, &b_svfitMass_isValidMEMlo1logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo1logMwHadTauTF", &svfitComputingTime_cpuMEMlo1logMwHadTauTF, &b_svfitComputingTime_cpuMEMlo1logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo1logMwHadTauTF", &svfitComputingTime_realMEMlo1logMwHadTauTF, &b_svfitComputingTime_realMEMlo1logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo1logMwoHadTauTF", &svfitMassMEMlo1logMwoHadTauTF, &b_svfitMassMEMlo1logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo1logMwoHadTauTF", &svfitMassErrMEMlo1logMwoHadTauTF, &b_svfitMassErrMEMlo1logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo1logMwoHadTauTF", &svfitMass_isValidMEMlo1logMwoHadTauTF, &b_svfitMass_isValidMEMlo1logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo1logMwoHadTauTF", &svfitComputingTime_cpuMEMlo1logMwoHadTauTF, &b_svfitComputingTime_cpuMEMlo1logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo1logMwoHadTauTF", &svfitComputingTime_realMEMlo1logMwoHadTauTF, &b_svfitComputingTime_realMEMlo1logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo2logMwHadTauTF", &svfitMassMEMlo2logMwHadTauTF, &b_svfitMassMEMlo2logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo2logMwHadTauTF", &svfitMassErrMEMlo2logMwHadTauTF, &b_svfitMassErrMEMlo2logMwHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo2logMwHadTauTF", &svfitMass_isValidMEMlo2logMwHadTauTF, &b_svfitMass_isValidMEMlo2logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo2logMwHadTauTF", &svfitComputingTime_cpuMEMlo2logMwHadTauTF, &b_svfitComputingTime_cpuMEMlo2logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo2logMwHadTauTF", &svfitComputingTime_realMEMlo2logMwHadTauTF, &b_svfitComputingTime_realMEMlo2logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo2logMwoHadTauTF", &svfitMassMEMlo2logMwoHadTauTF, &b_svfitMassMEMlo2logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo2logMwoHadTauTF", &svfitMassErrMEMlo2logMwoHadTauTF, &b_svfitMassErrMEMlo2logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo2logMwoHadTauTF", &svfitMass_isValidMEMlo2logMwoHadTauTF, &b_svfitMass_isValidMEMlo2logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo2logMwoHadTauTF", &svfitComputingTime_cpuMEMlo2logMwoHadTauTF, &b_svfitComputingTime_cpuMEMlo2logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo2logMwoHadTauTF", &svfitComputingTime_realMEMlo2logMwoHadTauTF, &b_svfitComputingTime_realMEMlo2logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo3logMwHadTauTF", &svfitMassMEMlo3logMwHadTauTF, &b_svfitMassMEMlo3logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo3logMwHadTauTF", &svfitMassErrMEMlo3logMwHadTauTF, &b_svfitMassErrMEMlo3logMwHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo3logMwHadTauTF", &svfitMass_isValidMEMlo3logMwHadTauTF, &b_svfitMass_isValidMEMlo3logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo3logMwHadTauTF", &svfitComputingTime_cpuMEMlo3logMwHadTauTF, &b_svfitComputingTime_cpuMEMlo3logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo3logMwHadTauTF", &svfitComputingTime_realMEMlo3logMwHadTauTF, &b_svfitComputingTime_realMEMlo3logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo3logMwoHadTauTF", &svfitMassMEMlo3logMwoHadTauTF, &b_svfitMassMEMlo3logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo3logMwoHadTauTF", &svfitMassErrMEMlo3logMwoHadTauTF, &b_svfitMassErrMEMlo3logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo3logMwoHadTauTF", &svfitMass_isValidMEMlo3logMwoHadTauTF, &b_svfitMass_isValidMEMlo3logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo3logMwoHadTauTF", &svfitComputingTime_cpuMEMlo3logMwoHadTauTF, &b_svfitComputingTime_cpuMEMlo3logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo3logMwoHadTauTF", &svfitComputingTime_realMEMlo3logMwoHadTauTF, &b_svfitComputingTime_realMEMlo3logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo4logMwHadTauTF", &svfitMassMEMlo4logMwHadTauTF, &b_svfitMassMEMlo4logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo4logMwHadTauTF", &svfitMassErrMEMlo4logMwHadTauTF, &b_svfitMassErrMEMlo4logMwHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo4logMwHadTauTF", &svfitMass_isValidMEMlo4logMwHadTauTF, &b_svfitMass_isValidMEMlo4logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo4logMwHadTauTF", &svfitComputingTime_cpuMEMlo4logMwHadTauTF, &b_svfitComputingTime_cpuMEMlo4logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo4logMwHadTauTF", &svfitComputingTime_realMEMlo4logMwHadTauTF, &b_svfitComputingTime_realMEMlo4logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo4logMwoHadTauTF", &svfitMassMEMlo4logMwoHadTauTF, &b_svfitMassMEMlo4logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo4logMwoHadTauTF", &svfitMassErrMEMlo4logMwoHadTauTF, &b_svfitMassErrMEMlo4logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo4logMwoHadTauTF", &svfitMass_isValidMEMlo4logMwoHadTauTF, &b_svfitMass_isValidMEMlo4logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo4logMwoHadTauTF", &svfitComputingTime_cpuMEMlo4logMwoHadTauTF, &b_svfitComputingTime_cpuMEMlo4logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo4logMwoHadTauTF", &svfitComputingTime_realMEMlo4logMwoHadTauTF, &b_svfitComputingTime_realMEMlo4logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo5logMwHadTauTF", &svfitMassMEMlo5logMwHadTauTF, &b_svfitMassMEMlo5logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo5logMwHadTauTF", &svfitMassErrMEMlo5logMwHadTauTF, &b_svfitMassErrMEMlo5logMwHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo5logMwHadTauTF", &svfitMass_isValidMEMlo5logMwHadTauTF, &b_svfitMass_isValidMEMlo5logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo5logMwHadTauTF", &svfitComputingTime_cpuMEMlo5logMwHadTauTF, &b_svfitComputingTime_cpuMEMlo5logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo5logMwHadTauTF", &svfitComputingTime_realMEMlo5logMwHadTauTF, &b_svfitComputingTime_realMEMlo5logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo5logMwoHadTauTF", &svfitMassMEMlo5logMwoHadTauTF, &b_svfitMassMEMlo5logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo5logMwoHadTauTF", &svfitMassErrMEMlo5logMwoHadTauTF, &b_svfitMassErrMEMlo5logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo5logMwoHadTauTF", &svfitMass_isValidMEMlo5logMwoHadTauTF, &b_svfitMass_isValidMEMlo5logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo5logMwoHadTauTF", &svfitComputingTime_cpuMEMlo5logMwoHadTauTF, &b_svfitComputingTime_cpuMEMlo5logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo5logMwoHadTauTF", &svfitComputingTime_realMEMlo5logMwoHadTauTF, &b_svfitComputingTime_realMEMlo5logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo6logMwHadTauTF", &svfitMassMEMlo6logMwHadTauTF, &b_svfitMassMEMlo6logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo6logMwHadTauTF", &svfitMassErrMEMlo6logMwHadTauTF, &b_svfitMassErrMEMlo6logMwHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo6logMwHadTauTF", &svfitMass_isValidMEMlo6logMwHadTauTF, &b_svfitMass_isValidMEMlo6logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo6logMwHadTauTF", &svfitComputingTime_cpuMEMlo6logMwHadTauTF, &b_svfitComputingTime_cpuMEMlo6logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo6logMwHadTauTF", &svfitComputingTime_realMEMlo6logMwHadTauTF, &b_svfitComputingTime_realMEMlo6logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo6logMwoHadTauTF", &svfitMassMEMlo6logMwoHadTauTF, &b_svfitMassMEMlo6logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo6logMwoHadTauTF", &svfitMassErrMEMlo6logMwoHadTauTF, &b_svfitMassErrMEMlo6logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo6logMwoHadTauTF", &svfitMass_isValidMEMlo6logMwoHadTauTF, &b_svfitMass_isValidMEMlo6logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo6logMwoHadTauTF", &svfitComputingTime_cpuMEMlo6logMwoHadTauTF, &b_svfitComputingTime_cpuMEMlo6logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo6logMwoHadTauTF", &svfitComputingTime_realMEMlo6logMwoHadTauTF, &b_svfitComputingTime_realMEMlo6logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo7logMwHadTauTF", &svfitMassMEMlo7logMwHadTauTF, &b_svfitMassMEMlo7logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo7logMwHadTauTF", &svfitMassErrMEMlo7logMwHadTauTF, &b_svfitMassErrMEMlo7logMwHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo7logMwHadTauTF", &svfitMass_isValidMEMlo7logMwHadTauTF, &b_svfitMass_isValidMEMlo7logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo7logMwHadTauTF", &svfitComputingTime_cpuMEMlo7logMwHadTauTF, &b_svfitComputingTime_cpuMEMlo7logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo7logMwHadTauTF", &svfitComputingTime_realMEMlo7logMwHadTauTF, &b_svfitComputingTime_realMEMlo7logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo7logMwoHadTauTF", &svfitMassMEMlo7logMwoHadTauTF, &b_svfitMassMEMlo7logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo7logMwoHadTauTF", &svfitMassErrMEMlo7logMwoHadTauTF, &b_svfitMassErrMEMlo7logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo7logMwoHadTauTF", &svfitMass_isValidMEMlo7logMwoHadTauTF, &b_svfitMass_isValidMEMlo7logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo7logMwoHadTauTF", &svfitComputingTime_cpuMEMlo7logMwoHadTauTF, &b_svfitComputingTime_cpuMEMlo7logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo7logMwoHadTauTF", &svfitComputingTime_realMEMlo7logMwoHadTauTF, &b_svfitComputingTime_realMEMlo7logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo8logMwHadTauTF", &svfitMassMEMlo8logMwHadTauTF, &b_svfitMassMEMlo8logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo8logMwHadTauTF", &svfitMassErrMEMlo8logMwHadTauTF, &b_svfitMassErrMEMlo8logMwHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo8logMwHadTauTF", &svfitMass_isValidMEMlo8logMwHadTauTF, &b_svfitMass_isValidMEMlo8logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo8logMwHadTauTF", &svfitComputingTime_cpuMEMlo8logMwHadTauTF, &b_svfitComputingTime_cpuMEMlo8logMwHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo8logMwHadTauTF", &svfitComputingTime_realMEMlo8logMwHadTauTF, &b_svfitComputingTime_realMEMlo8logMwHadTauTF);
   fChain->SetBranchAddress("svfitMassMEMlo8logMwoHadTauTF", &svfitMassMEMlo8logMwoHadTauTF, &b_svfitMassMEMlo8logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMassErrMEMlo8logMwoHadTauTF", &svfitMassErrMEMlo8logMwoHadTauTF, &b_svfitMassErrMEMlo8logMwoHadTauTF);
   fChain->SetBranchAddress("svfitMass_isValidMEMlo8logMwoHadTauTF", &svfitMass_isValidMEMlo8logMwoHadTauTF, &b_svfitMass_isValidMEMlo8logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_cpuMEMlo8logMwoHadTauTF", &svfitComputingTime_cpuMEMlo8logMwoHadTauTF, &b_svfitComputingTime_cpuMEMlo8logMwoHadTauTF);
   fChain->SetBranchAddress("svfitComputingTime_realMEMlo8logMwoHadTauTF", &svfitComputingTime_realMEMlo8logMwoHadTauTF, &b_svfitComputingTime_realMEMlo8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt0logMwHadTauTF", &classicSVfitPt0logMwHadTauTF, &b_classicSVfitPt0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr0logMwHadTauTF", &classicSVfitPtErr0logMwHadTauTF, &b_classicSVfitPtErr0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid0logMwHadTauTF", &classicSVfitPt_isValid0logMwHadTauTF, &b_classicSVfitPt_isValid0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta0logMwHadTauTF", &classicSVfitEta0logMwHadTauTF, &b_classicSVfitEta0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr0logMwHadTauTF", &classicSVfitEtaErr0logMwHadTauTF, &b_classicSVfitEtaErr0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid0logMwHadTauTF", &classicSVfitEta_isValid0logMwHadTauTF, &b_classicSVfitEta_isValid0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi0logMwHadTauTF", &classicSVfitPhi0logMwHadTauTF, &b_classicSVfitPhi0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr0logMwHadTauTF", &classicSVfitPhiErr0logMwHadTauTF, &b_classicSVfitPhiErr0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid0logMwHadTauTF", &classicSVfitPhi_isValid0logMwHadTauTF, &b_classicSVfitPhi_isValid0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass0logMwHadTauTF", &classicSVfitMass0logMwHadTauTF, &b_classicSVfitMass0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr0logMwHadTauTF", &classicSVfitMassErr0logMwHadTauTF, &b_classicSVfitMassErr0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid0logMwHadTauTF", &classicSVfitMass_isValid0logMwHadTauTF, &b_classicSVfitMass_isValid0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass0logMwHadTauTF", &classicSVfitTransverseMass0logMwHadTauTF, &b_classicSVfitTransverseMass0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr0logMwHadTauTF", &classicSVfitTransverseMassErr0logMwHadTauTF, &b_classicSVfitTransverseMassErr0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid0logMwHadTauTF", &classicSVfitTransverseMass_isValid0logMwHadTauTF, &b_classicSVfitTransverseMass_isValid0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu0logMwHadTauTF", &classicSVfitComputingTime_cpu0logMwHadTauTF, &b_classicSVfitComputingTime_cpu0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real0logMwHadTauTF", &classicSVfitComputingTime_real0logMwHadTauTF, &b_classicSVfitComputingTime_real0logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt0logMwoHadTauTF", &classicSVfitPt0logMwoHadTauTF, &b_classicSVfitPt0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr0logMwoHadTauTF", &classicSVfitPtErr0logMwoHadTauTF, &b_classicSVfitPtErr0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid0logMwoHadTauTF", &classicSVfitPt_isValid0logMwoHadTauTF, &b_classicSVfitPt_isValid0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta0logMwoHadTauTF", &classicSVfitEta0logMwoHadTauTF, &b_classicSVfitEta0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr0logMwoHadTauTF", &classicSVfitEtaErr0logMwoHadTauTF, &b_classicSVfitEtaErr0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid0logMwoHadTauTF", &classicSVfitEta_isValid0logMwoHadTauTF, &b_classicSVfitEta_isValid0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi0logMwoHadTauTF", &classicSVfitPhi0logMwoHadTauTF, &b_classicSVfitPhi0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr0logMwoHadTauTF", &classicSVfitPhiErr0logMwoHadTauTF, &b_classicSVfitPhiErr0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid0logMwoHadTauTF", &classicSVfitPhi_isValid0logMwoHadTauTF, &b_classicSVfitPhi_isValid0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass0logMwoHadTauTF", &classicSVfitMass0logMwoHadTauTF, &b_classicSVfitMass0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr0logMwoHadTauTF", &classicSVfitMassErr0logMwoHadTauTF, &b_classicSVfitMassErr0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid0logMwoHadTauTF", &classicSVfitMass_isValid0logMwoHadTauTF, &b_classicSVfitMass_isValid0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass0logMwoHadTauTF", &classicSVfitTransverseMass0logMwoHadTauTF, &b_classicSVfitTransverseMass0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr0logMwoHadTauTF", &classicSVfitTransverseMassErr0logMwoHadTauTF, &b_classicSVfitTransverseMassErr0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid0logMwoHadTauTF", &classicSVfitTransverseMass_isValid0logMwoHadTauTF, &b_classicSVfitTransverseMass_isValid0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu0logMwoHadTauTF", &classicSVfitComputingTime_cpu0logMwoHadTauTF, &b_classicSVfitComputingTime_cpu0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real0logMwoHadTauTF", &classicSVfitComputingTime_real0logMwoHadTauTF, &b_classicSVfitComputingTime_real0logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt1logMwHadTauTF", &classicSVfitPt1logMwHadTauTF, &b_classicSVfitPt1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr1logMwHadTauTF", &classicSVfitPtErr1logMwHadTauTF, &b_classicSVfitPtErr1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid1logMwHadTauTF", &classicSVfitPt_isValid1logMwHadTauTF, &b_classicSVfitPt_isValid1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta1logMwHadTauTF", &classicSVfitEta1logMwHadTauTF, &b_classicSVfitEta1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr1logMwHadTauTF", &classicSVfitEtaErr1logMwHadTauTF, &b_classicSVfitEtaErr1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid1logMwHadTauTF", &classicSVfitEta_isValid1logMwHadTauTF, &b_classicSVfitEta_isValid1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi1logMwHadTauTF", &classicSVfitPhi1logMwHadTauTF, &b_classicSVfitPhi1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr1logMwHadTauTF", &classicSVfitPhiErr1logMwHadTauTF, &b_classicSVfitPhiErr1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid1logMwHadTauTF", &classicSVfitPhi_isValid1logMwHadTauTF, &b_classicSVfitPhi_isValid1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass1logMwHadTauTF", &classicSVfitMass1logMwHadTauTF, &b_classicSVfitMass1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr1logMwHadTauTF", &classicSVfitMassErr1logMwHadTauTF, &b_classicSVfitMassErr1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid1logMwHadTauTF", &classicSVfitMass_isValid1logMwHadTauTF, &b_classicSVfitMass_isValid1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass1logMwHadTauTF", &classicSVfitTransverseMass1logMwHadTauTF, &b_classicSVfitTransverseMass1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr1logMwHadTauTF", &classicSVfitTransverseMassErr1logMwHadTauTF, &b_classicSVfitTransverseMassErr1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid1logMwHadTauTF", &classicSVfitTransverseMass_isValid1logMwHadTauTF, &b_classicSVfitTransverseMass_isValid1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu1logMwHadTauTF", &classicSVfitComputingTime_cpu1logMwHadTauTF, &b_classicSVfitComputingTime_cpu1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real1logMwHadTauTF", &classicSVfitComputingTime_real1logMwHadTauTF, &b_classicSVfitComputingTime_real1logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt1logMwoHadTauTF", &classicSVfitPt1logMwoHadTauTF, &b_classicSVfitPt1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr1logMwoHadTauTF", &classicSVfitPtErr1logMwoHadTauTF, &b_classicSVfitPtErr1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid1logMwoHadTauTF", &classicSVfitPt_isValid1logMwoHadTauTF, &b_classicSVfitPt_isValid1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta1logMwoHadTauTF", &classicSVfitEta1logMwoHadTauTF, &b_classicSVfitEta1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr1logMwoHadTauTF", &classicSVfitEtaErr1logMwoHadTauTF, &b_classicSVfitEtaErr1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid1logMwoHadTauTF", &classicSVfitEta_isValid1logMwoHadTauTF, &b_classicSVfitEta_isValid1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi1logMwoHadTauTF", &classicSVfitPhi1logMwoHadTauTF, &b_classicSVfitPhi1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr1logMwoHadTauTF", &classicSVfitPhiErr1logMwoHadTauTF, &b_classicSVfitPhiErr1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid1logMwoHadTauTF", &classicSVfitPhi_isValid1logMwoHadTauTF, &b_classicSVfitPhi_isValid1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass1logMwoHadTauTF", &classicSVfitMass1logMwoHadTauTF, &b_classicSVfitMass1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr1logMwoHadTauTF", &classicSVfitMassErr1logMwoHadTauTF, &b_classicSVfitMassErr1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid1logMwoHadTauTF", &classicSVfitMass_isValid1logMwoHadTauTF, &b_classicSVfitMass_isValid1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass1logMwoHadTauTF", &classicSVfitTransverseMass1logMwoHadTauTF, &b_classicSVfitTransverseMass1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr1logMwoHadTauTF", &classicSVfitTransverseMassErr1logMwoHadTauTF, &b_classicSVfitTransverseMassErr1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid1logMwoHadTauTF", &classicSVfitTransverseMass_isValid1logMwoHadTauTF, &b_classicSVfitTransverseMass_isValid1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu1logMwoHadTauTF", &classicSVfitComputingTime_cpu1logMwoHadTauTF, &b_classicSVfitComputingTime_cpu1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real1logMwoHadTauTF", &classicSVfitComputingTime_real1logMwoHadTauTF, &b_classicSVfitComputingTime_real1logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt2logMwHadTauTF", &classicSVfitPt2logMwHadTauTF, &b_classicSVfitPt2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr2logMwHadTauTF", &classicSVfitPtErr2logMwHadTauTF, &b_classicSVfitPtErr2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid2logMwHadTauTF", &classicSVfitPt_isValid2logMwHadTauTF, &b_classicSVfitPt_isValid2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta2logMwHadTauTF", &classicSVfitEta2logMwHadTauTF, &b_classicSVfitEta2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr2logMwHadTauTF", &classicSVfitEtaErr2logMwHadTauTF, &b_classicSVfitEtaErr2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid2logMwHadTauTF", &classicSVfitEta_isValid2logMwHadTauTF, &b_classicSVfitEta_isValid2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi2logMwHadTauTF", &classicSVfitPhi2logMwHadTauTF, &b_classicSVfitPhi2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr2logMwHadTauTF", &classicSVfitPhiErr2logMwHadTauTF, &b_classicSVfitPhiErr2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid2logMwHadTauTF", &classicSVfitPhi_isValid2logMwHadTauTF, &b_classicSVfitPhi_isValid2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass2logMwHadTauTF", &classicSVfitMass2logMwHadTauTF, &b_classicSVfitMass2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr2logMwHadTauTF", &classicSVfitMassErr2logMwHadTauTF, &b_classicSVfitMassErr2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid2logMwHadTauTF", &classicSVfitMass_isValid2logMwHadTauTF, &b_classicSVfitMass_isValid2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass2logMwHadTauTF", &classicSVfitTransverseMass2logMwHadTauTF, &b_classicSVfitTransverseMass2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr2logMwHadTauTF", &classicSVfitTransverseMassErr2logMwHadTauTF, &b_classicSVfitTransverseMassErr2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid2logMwHadTauTF", &classicSVfitTransverseMass_isValid2logMwHadTauTF, &b_classicSVfitTransverseMass_isValid2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu2logMwHadTauTF", &classicSVfitComputingTime_cpu2logMwHadTauTF, &b_classicSVfitComputingTime_cpu2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real2logMwHadTauTF", &classicSVfitComputingTime_real2logMwHadTauTF, &b_classicSVfitComputingTime_real2logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt2logMwoHadTauTF", &classicSVfitPt2logMwoHadTauTF, &b_classicSVfitPt2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr2logMwoHadTauTF", &classicSVfitPtErr2logMwoHadTauTF, &b_classicSVfitPtErr2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid2logMwoHadTauTF", &classicSVfitPt_isValid2logMwoHadTauTF, &b_classicSVfitPt_isValid2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta2logMwoHadTauTF", &classicSVfitEta2logMwoHadTauTF, &b_classicSVfitEta2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr2logMwoHadTauTF", &classicSVfitEtaErr2logMwoHadTauTF, &b_classicSVfitEtaErr2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid2logMwoHadTauTF", &classicSVfitEta_isValid2logMwoHadTauTF, &b_classicSVfitEta_isValid2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi2logMwoHadTauTF", &classicSVfitPhi2logMwoHadTauTF, &b_classicSVfitPhi2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr2logMwoHadTauTF", &classicSVfitPhiErr2logMwoHadTauTF, &b_classicSVfitPhiErr2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid2logMwoHadTauTF", &classicSVfitPhi_isValid2logMwoHadTauTF, &b_classicSVfitPhi_isValid2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass2logMwoHadTauTF", &classicSVfitMass2logMwoHadTauTF, &b_classicSVfitMass2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr2logMwoHadTauTF", &classicSVfitMassErr2logMwoHadTauTF, &b_classicSVfitMassErr2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid2logMwoHadTauTF", &classicSVfitMass_isValid2logMwoHadTauTF, &b_classicSVfitMass_isValid2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass2logMwoHadTauTF", &classicSVfitTransverseMass2logMwoHadTauTF, &b_classicSVfitTransverseMass2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr2logMwoHadTauTF", &classicSVfitTransverseMassErr2logMwoHadTauTF, &b_classicSVfitTransverseMassErr2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid2logMwoHadTauTF", &classicSVfitTransverseMass_isValid2logMwoHadTauTF, &b_classicSVfitTransverseMass_isValid2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu2logMwoHadTauTF", &classicSVfitComputingTime_cpu2logMwoHadTauTF, &b_classicSVfitComputingTime_cpu2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real2logMwoHadTauTF", &classicSVfitComputingTime_real2logMwoHadTauTF, &b_classicSVfitComputingTime_real2logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt3logMwHadTauTF", &classicSVfitPt3logMwHadTauTF, &b_classicSVfitPt3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr3logMwHadTauTF", &classicSVfitPtErr3logMwHadTauTF, &b_classicSVfitPtErr3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid3logMwHadTauTF", &classicSVfitPt_isValid3logMwHadTauTF, &b_classicSVfitPt_isValid3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta3logMwHadTauTF", &classicSVfitEta3logMwHadTauTF, &b_classicSVfitEta3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr3logMwHadTauTF", &classicSVfitEtaErr3logMwHadTauTF, &b_classicSVfitEtaErr3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid3logMwHadTauTF", &classicSVfitEta_isValid3logMwHadTauTF, &b_classicSVfitEta_isValid3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi3logMwHadTauTF", &classicSVfitPhi3logMwHadTauTF, &b_classicSVfitPhi3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr3logMwHadTauTF", &classicSVfitPhiErr3logMwHadTauTF, &b_classicSVfitPhiErr3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid3logMwHadTauTF", &classicSVfitPhi_isValid3logMwHadTauTF, &b_classicSVfitPhi_isValid3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass3logMwHadTauTF", &classicSVfitMass3logMwHadTauTF, &b_classicSVfitMass3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr3logMwHadTauTF", &classicSVfitMassErr3logMwHadTauTF, &b_classicSVfitMassErr3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid3logMwHadTauTF", &classicSVfitMass_isValid3logMwHadTauTF, &b_classicSVfitMass_isValid3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass3logMwHadTauTF", &classicSVfitTransverseMass3logMwHadTauTF, &b_classicSVfitTransverseMass3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr3logMwHadTauTF", &classicSVfitTransverseMassErr3logMwHadTauTF, &b_classicSVfitTransverseMassErr3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid3logMwHadTauTF", &classicSVfitTransverseMass_isValid3logMwHadTauTF, &b_classicSVfitTransverseMass_isValid3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu3logMwHadTauTF", &classicSVfitComputingTime_cpu3logMwHadTauTF, &b_classicSVfitComputingTime_cpu3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real3logMwHadTauTF", &classicSVfitComputingTime_real3logMwHadTauTF, &b_classicSVfitComputingTime_real3logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt3logMwoHadTauTF", &classicSVfitPt3logMwoHadTauTF, &b_classicSVfitPt3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr3logMwoHadTauTF", &classicSVfitPtErr3logMwoHadTauTF, &b_classicSVfitPtErr3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid3logMwoHadTauTF", &classicSVfitPt_isValid3logMwoHadTauTF, &b_classicSVfitPt_isValid3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta3logMwoHadTauTF", &classicSVfitEta3logMwoHadTauTF, &b_classicSVfitEta3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr3logMwoHadTauTF", &classicSVfitEtaErr3logMwoHadTauTF, &b_classicSVfitEtaErr3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid3logMwoHadTauTF", &classicSVfitEta_isValid3logMwoHadTauTF, &b_classicSVfitEta_isValid3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi3logMwoHadTauTF", &classicSVfitPhi3logMwoHadTauTF, &b_classicSVfitPhi3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr3logMwoHadTauTF", &classicSVfitPhiErr3logMwoHadTauTF, &b_classicSVfitPhiErr3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid3logMwoHadTauTF", &classicSVfitPhi_isValid3logMwoHadTauTF, &b_classicSVfitPhi_isValid3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass3logMwoHadTauTF", &classicSVfitMass3logMwoHadTauTF, &b_classicSVfitMass3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr3logMwoHadTauTF", &classicSVfitMassErr3logMwoHadTauTF, &b_classicSVfitMassErr3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid3logMwoHadTauTF", &classicSVfitMass_isValid3logMwoHadTauTF, &b_classicSVfitMass_isValid3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass3logMwoHadTauTF", &classicSVfitTransverseMass3logMwoHadTauTF, &b_classicSVfitTransverseMass3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr3logMwoHadTauTF", &classicSVfitTransverseMassErr3logMwoHadTauTF, &b_classicSVfitTransverseMassErr3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid3logMwoHadTauTF", &classicSVfitTransverseMass_isValid3logMwoHadTauTF, &b_classicSVfitTransverseMass_isValid3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu3logMwoHadTauTF", &classicSVfitComputingTime_cpu3logMwoHadTauTF, &b_classicSVfitComputingTime_cpu3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real3logMwoHadTauTF", &classicSVfitComputingTime_real3logMwoHadTauTF, &b_classicSVfitComputingTime_real3logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt4logMwHadTauTF", &classicSVfitPt4logMwHadTauTF, &b_classicSVfitPt4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr4logMwHadTauTF", &classicSVfitPtErr4logMwHadTauTF, &b_classicSVfitPtErr4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid4logMwHadTauTF", &classicSVfitPt_isValid4logMwHadTauTF, &b_classicSVfitPt_isValid4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta4logMwHadTauTF", &classicSVfitEta4logMwHadTauTF, &b_classicSVfitEta4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr4logMwHadTauTF", &classicSVfitEtaErr4logMwHadTauTF, &b_classicSVfitEtaErr4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid4logMwHadTauTF", &classicSVfitEta_isValid4logMwHadTauTF, &b_classicSVfitEta_isValid4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi4logMwHadTauTF", &classicSVfitPhi4logMwHadTauTF, &b_classicSVfitPhi4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr4logMwHadTauTF", &classicSVfitPhiErr4logMwHadTauTF, &b_classicSVfitPhiErr4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid4logMwHadTauTF", &classicSVfitPhi_isValid4logMwHadTauTF, &b_classicSVfitPhi_isValid4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass4logMwHadTauTF", &classicSVfitMass4logMwHadTauTF, &b_classicSVfitMass4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr4logMwHadTauTF", &classicSVfitMassErr4logMwHadTauTF, &b_classicSVfitMassErr4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid4logMwHadTauTF", &classicSVfitMass_isValid4logMwHadTauTF, &b_classicSVfitMass_isValid4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass4logMwHadTauTF", &classicSVfitTransverseMass4logMwHadTauTF, &b_classicSVfitTransverseMass4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr4logMwHadTauTF", &classicSVfitTransverseMassErr4logMwHadTauTF, &b_classicSVfitTransverseMassErr4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid4logMwHadTauTF", &classicSVfitTransverseMass_isValid4logMwHadTauTF, &b_classicSVfitTransverseMass_isValid4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu4logMwHadTauTF", &classicSVfitComputingTime_cpu4logMwHadTauTF, &b_classicSVfitComputingTime_cpu4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real4logMwHadTauTF", &classicSVfitComputingTime_real4logMwHadTauTF, &b_classicSVfitComputingTime_real4logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt4logMwoHadTauTF", &classicSVfitPt4logMwoHadTauTF, &b_classicSVfitPt4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr4logMwoHadTauTF", &classicSVfitPtErr4logMwoHadTauTF, &b_classicSVfitPtErr4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid4logMwoHadTauTF", &classicSVfitPt_isValid4logMwoHadTauTF, &b_classicSVfitPt_isValid4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta4logMwoHadTauTF", &classicSVfitEta4logMwoHadTauTF, &b_classicSVfitEta4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr4logMwoHadTauTF", &classicSVfitEtaErr4logMwoHadTauTF, &b_classicSVfitEtaErr4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid4logMwoHadTauTF", &classicSVfitEta_isValid4logMwoHadTauTF, &b_classicSVfitEta_isValid4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi4logMwoHadTauTF", &classicSVfitPhi4logMwoHadTauTF, &b_classicSVfitPhi4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr4logMwoHadTauTF", &classicSVfitPhiErr4logMwoHadTauTF, &b_classicSVfitPhiErr4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid4logMwoHadTauTF", &classicSVfitPhi_isValid4logMwoHadTauTF, &b_classicSVfitPhi_isValid4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass4logMwoHadTauTF", &classicSVfitMass4logMwoHadTauTF, &b_classicSVfitMass4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr4logMwoHadTauTF", &classicSVfitMassErr4logMwoHadTauTF, &b_classicSVfitMassErr4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid4logMwoHadTauTF", &classicSVfitMass_isValid4logMwoHadTauTF, &b_classicSVfitMass_isValid4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass4logMwoHadTauTF", &classicSVfitTransverseMass4logMwoHadTauTF, &b_classicSVfitTransverseMass4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr4logMwoHadTauTF", &classicSVfitTransverseMassErr4logMwoHadTauTF, &b_classicSVfitTransverseMassErr4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid4logMwoHadTauTF", &classicSVfitTransverseMass_isValid4logMwoHadTauTF, &b_classicSVfitTransverseMass_isValid4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu4logMwoHadTauTF", &classicSVfitComputingTime_cpu4logMwoHadTauTF, &b_classicSVfitComputingTime_cpu4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real4logMwoHadTauTF", &classicSVfitComputingTime_real4logMwoHadTauTF, &b_classicSVfitComputingTime_real4logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt5logMwHadTauTF", &classicSVfitPt5logMwHadTauTF, &b_classicSVfitPt5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr5logMwHadTauTF", &classicSVfitPtErr5logMwHadTauTF, &b_classicSVfitPtErr5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid5logMwHadTauTF", &classicSVfitPt_isValid5logMwHadTauTF, &b_classicSVfitPt_isValid5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta5logMwHadTauTF", &classicSVfitEta5logMwHadTauTF, &b_classicSVfitEta5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr5logMwHadTauTF", &classicSVfitEtaErr5logMwHadTauTF, &b_classicSVfitEtaErr5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid5logMwHadTauTF", &classicSVfitEta_isValid5logMwHadTauTF, &b_classicSVfitEta_isValid5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi5logMwHadTauTF", &classicSVfitPhi5logMwHadTauTF, &b_classicSVfitPhi5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr5logMwHadTauTF", &classicSVfitPhiErr5logMwHadTauTF, &b_classicSVfitPhiErr5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid5logMwHadTauTF", &classicSVfitPhi_isValid5logMwHadTauTF, &b_classicSVfitPhi_isValid5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass5logMwHadTauTF", &classicSVfitMass5logMwHadTauTF, &b_classicSVfitMass5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr5logMwHadTauTF", &classicSVfitMassErr5logMwHadTauTF, &b_classicSVfitMassErr5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid5logMwHadTauTF", &classicSVfitMass_isValid5logMwHadTauTF, &b_classicSVfitMass_isValid5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass5logMwHadTauTF", &classicSVfitTransverseMass5logMwHadTauTF, &b_classicSVfitTransverseMass5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr5logMwHadTauTF", &classicSVfitTransverseMassErr5logMwHadTauTF, &b_classicSVfitTransverseMassErr5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid5logMwHadTauTF", &classicSVfitTransverseMass_isValid5logMwHadTauTF, &b_classicSVfitTransverseMass_isValid5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu5logMwHadTauTF", &classicSVfitComputingTime_cpu5logMwHadTauTF, &b_classicSVfitComputingTime_cpu5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real5logMwHadTauTF", &classicSVfitComputingTime_real5logMwHadTauTF, &b_classicSVfitComputingTime_real5logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt5logMwoHadTauTF", &classicSVfitPt5logMwoHadTauTF, &b_classicSVfitPt5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr5logMwoHadTauTF", &classicSVfitPtErr5logMwoHadTauTF, &b_classicSVfitPtErr5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid5logMwoHadTauTF", &classicSVfitPt_isValid5logMwoHadTauTF, &b_classicSVfitPt_isValid5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta5logMwoHadTauTF", &classicSVfitEta5logMwoHadTauTF, &b_classicSVfitEta5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr5logMwoHadTauTF", &classicSVfitEtaErr5logMwoHadTauTF, &b_classicSVfitEtaErr5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid5logMwoHadTauTF", &classicSVfitEta_isValid5logMwoHadTauTF, &b_classicSVfitEta_isValid5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi5logMwoHadTauTF", &classicSVfitPhi5logMwoHadTauTF, &b_classicSVfitPhi5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr5logMwoHadTauTF", &classicSVfitPhiErr5logMwoHadTauTF, &b_classicSVfitPhiErr5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid5logMwoHadTauTF", &classicSVfitPhi_isValid5logMwoHadTauTF, &b_classicSVfitPhi_isValid5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass5logMwoHadTauTF", &classicSVfitMass5logMwoHadTauTF, &b_classicSVfitMass5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr5logMwoHadTauTF", &classicSVfitMassErr5logMwoHadTauTF, &b_classicSVfitMassErr5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid5logMwoHadTauTF", &classicSVfitMass_isValid5logMwoHadTauTF, &b_classicSVfitMass_isValid5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass5logMwoHadTauTF", &classicSVfitTransverseMass5logMwoHadTauTF, &b_classicSVfitTransverseMass5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr5logMwoHadTauTF", &classicSVfitTransverseMassErr5logMwoHadTauTF, &b_classicSVfitTransverseMassErr5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid5logMwoHadTauTF", &classicSVfitTransverseMass_isValid5logMwoHadTauTF, &b_classicSVfitTransverseMass_isValid5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu5logMwoHadTauTF", &classicSVfitComputingTime_cpu5logMwoHadTauTF, &b_classicSVfitComputingTime_cpu5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real5logMwoHadTauTF", &classicSVfitComputingTime_real5logMwoHadTauTF, &b_classicSVfitComputingTime_real5logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt6logMwHadTauTF", &classicSVfitPt6logMwHadTauTF, &b_classicSVfitPt6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr6logMwHadTauTF", &classicSVfitPtErr6logMwHadTauTF, &b_classicSVfitPtErr6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid6logMwHadTauTF", &classicSVfitPt_isValid6logMwHadTauTF, &b_classicSVfitPt_isValid6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta6logMwHadTauTF", &classicSVfitEta6logMwHadTauTF, &b_classicSVfitEta6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr6logMwHadTauTF", &classicSVfitEtaErr6logMwHadTauTF, &b_classicSVfitEtaErr6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid6logMwHadTauTF", &classicSVfitEta_isValid6logMwHadTauTF, &b_classicSVfitEta_isValid6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi6logMwHadTauTF", &classicSVfitPhi6logMwHadTauTF, &b_classicSVfitPhi6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr6logMwHadTauTF", &classicSVfitPhiErr6logMwHadTauTF, &b_classicSVfitPhiErr6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid6logMwHadTauTF", &classicSVfitPhi_isValid6logMwHadTauTF, &b_classicSVfitPhi_isValid6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass6logMwHadTauTF", &classicSVfitMass6logMwHadTauTF, &b_classicSVfitMass6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr6logMwHadTauTF", &classicSVfitMassErr6logMwHadTauTF, &b_classicSVfitMassErr6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid6logMwHadTauTF", &classicSVfitMass_isValid6logMwHadTauTF, &b_classicSVfitMass_isValid6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass6logMwHadTauTF", &classicSVfitTransverseMass6logMwHadTauTF, &b_classicSVfitTransverseMass6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr6logMwHadTauTF", &classicSVfitTransverseMassErr6logMwHadTauTF, &b_classicSVfitTransverseMassErr6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid6logMwHadTauTF", &classicSVfitTransverseMass_isValid6logMwHadTauTF, &b_classicSVfitTransverseMass_isValid6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu6logMwHadTauTF", &classicSVfitComputingTime_cpu6logMwHadTauTF, &b_classicSVfitComputingTime_cpu6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real6logMwHadTauTF", &classicSVfitComputingTime_real6logMwHadTauTF, &b_classicSVfitComputingTime_real6logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt6logMwoHadTauTF", &classicSVfitPt6logMwoHadTauTF, &b_classicSVfitPt6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr6logMwoHadTauTF", &classicSVfitPtErr6logMwoHadTauTF, &b_classicSVfitPtErr6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid6logMwoHadTauTF", &classicSVfitPt_isValid6logMwoHadTauTF, &b_classicSVfitPt_isValid6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta6logMwoHadTauTF", &classicSVfitEta6logMwoHadTauTF, &b_classicSVfitEta6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr6logMwoHadTauTF", &classicSVfitEtaErr6logMwoHadTauTF, &b_classicSVfitEtaErr6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid6logMwoHadTauTF", &classicSVfitEta_isValid6logMwoHadTauTF, &b_classicSVfitEta_isValid6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi6logMwoHadTauTF", &classicSVfitPhi6logMwoHadTauTF, &b_classicSVfitPhi6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr6logMwoHadTauTF", &classicSVfitPhiErr6logMwoHadTauTF, &b_classicSVfitPhiErr6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid6logMwoHadTauTF", &classicSVfitPhi_isValid6logMwoHadTauTF, &b_classicSVfitPhi_isValid6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass6logMwoHadTauTF", &classicSVfitMass6logMwoHadTauTF, &b_classicSVfitMass6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr6logMwoHadTauTF", &classicSVfitMassErr6logMwoHadTauTF, &b_classicSVfitMassErr6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid6logMwoHadTauTF", &classicSVfitMass_isValid6logMwoHadTauTF, &b_classicSVfitMass_isValid6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass6logMwoHadTauTF", &classicSVfitTransverseMass6logMwoHadTauTF, &b_classicSVfitTransverseMass6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr6logMwoHadTauTF", &classicSVfitTransverseMassErr6logMwoHadTauTF, &b_classicSVfitTransverseMassErr6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid6logMwoHadTauTF", &classicSVfitTransverseMass_isValid6logMwoHadTauTF, &b_classicSVfitTransverseMass_isValid6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu6logMwoHadTauTF", &classicSVfitComputingTime_cpu6logMwoHadTauTF, &b_classicSVfitComputingTime_cpu6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real6logMwoHadTauTF", &classicSVfitComputingTime_real6logMwoHadTauTF, &b_classicSVfitComputingTime_real6logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt7logMwHadTauTF", &classicSVfitPt7logMwHadTauTF, &b_classicSVfitPt7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr7logMwHadTauTF", &classicSVfitPtErr7logMwHadTauTF, &b_classicSVfitPtErr7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid7logMwHadTauTF", &classicSVfitPt_isValid7logMwHadTauTF, &b_classicSVfitPt_isValid7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta7logMwHadTauTF", &classicSVfitEta7logMwHadTauTF, &b_classicSVfitEta7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr7logMwHadTauTF", &classicSVfitEtaErr7logMwHadTauTF, &b_classicSVfitEtaErr7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid7logMwHadTauTF", &classicSVfitEta_isValid7logMwHadTauTF, &b_classicSVfitEta_isValid7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi7logMwHadTauTF", &classicSVfitPhi7logMwHadTauTF, &b_classicSVfitPhi7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr7logMwHadTauTF", &classicSVfitPhiErr7logMwHadTauTF, &b_classicSVfitPhiErr7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid7logMwHadTauTF", &classicSVfitPhi_isValid7logMwHadTauTF, &b_classicSVfitPhi_isValid7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass7logMwHadTauTF", &classicSVfitMass7logMwHadTauTF, &b_classicSVfitMass7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr7logMwHadTauTF", &classicSVfitMassErr7logMwHadTauTF, &b_classicSVfitMassErr7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid7logMwHadTauTF", &classicSVfitMass_isValid7logMwHadTauTF, &b_classicSVfitMass_isValid7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass7logMwHadTauTF", &classicSVfitTransverseMass7logMwHadTauTF, &b_classicSVfitTransverseMass7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr7logMwHadTauTF", &classicSVfitTransverseMassErr7logMwHadTauTF, &b_classicSVfitTransverseMassErr7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid7logMwHadTauTF", &classicSVfitTransverseMass_isValid7logMwHadTauTF, &b_classicSVfitTransverseMass_isValid7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu7logMwHadTauTF", &classicSVfitComputingTime_cpu7logMwHadTauTF, &b_classicSVfitComputingTime_cpu7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real7logMwHadTauTF", &classicSVfitComputingTime_real7logMwHadTauTF, &b_classicSVfitComputingTime_real7logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt7logMwoHadTauTF", &classicSVfitPt7logMwoHadTauTF, &b_classicSVfitPt7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr7logMwoHadTauTF", &classicSVfitPtErr7logMwoHadTauTF, &b_classicSVfitPtErr7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid7logMwoHadTauTF", &classicSVfitPt_isValid7logMwoHadTauTF, &b_classicSVfitPt_isValid7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta7logMwoHadTauTF", &classicSVfitEta7logMwoHadTauTF, &b_classicSVfitEta7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr7logMwoHadTauTF", &classicSVfitEtaErr7logMwoHadTauTF, &b_classicSVfitEtaErr7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid7logMwoHadTauTF", &classicSVfitEta_isValid7logMwoHadTauTF, &b_classicSVfitEta_isValid7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi7logMwoHadTauTF", &classicSVfitPhi7logMwoHadTauTF, &b_classicSVfitPhi7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr7logMwoHadTauTF", &classicSVfitPhiErr7logMwoHadTauTF, &b_classicSVfitPhiErr7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid7logMwoHadTauTF", &classicSVfitPhi_isValid7logMwoHadTauTF, &b_classicSVfitPhi_isValid7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass7logMwoHadTauTF", &classicSVfitMass7logMwoHadTauTF, &b_classicSVfitMass7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr7logMwoHadTauTF", &classicSVfitMassErr7logMwoHadTauTF, &b_classicSVfitMassErr7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid7logMwoHadTauTF", &classicSVfitMass_isValid7logMwoHadTauTF, &b_classicSVfitMass_isValid7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass7logMwoHadTauTF", &classicSVfitTransverseMass7logMwoHadTauTF, &b_classicSVfitTransverseMass7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr7logMwoHadTauTF", &classicSVfitTransverseMassErr7logMwoHadTauTF, &b_classicSVfitTransverseMassErr7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid7logMwoHadTauTF", &classicSVfitTransverseMass_isValid7logMwoHadTauTF, &b_classicSVfitTransverseMass_isValid7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu7logMwoHadTauTF", &classicSVfitComputingTime_cpu7logMwoHadTauTF, &b_classicSVfitComputingTime_cpu7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real7logMwoHadTauTF", &classicSVfitComputingTime_real7logMwoHadTauTF, &b_classicSVfitComputingTime_real7logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt8logMwHadTauTF", &classicSVfitPt8logMwHadTauTF, &b_classicSVfitPt8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr8logMwHadTauTF", &classicSVfitPtErr8logMwHadTauTF, &b_classicSVfitPtErr8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid8logMwHadTauTF", &classicSVfitPt_isValid8logMwHadTauTF, &b_classicSVfitPt_isValid8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta8logMwHadTauTF", &classicSVfitEta8logMwHadTauTF, &b_classicSVfitEta8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr8logMwHadTauTF", &classicSVfitEtaErr8logMwHadTauTF, &b_classicSVfitEtaErr8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid8logMwHadTauTF", &classicSVfitEta_isValid8logMwHadTauTF, &b_classicSVfitEta_isValid8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi8logMwHadTauTF", &classicSVfitPhi8logMwHadTauTF, &b_classicSVfitPhi8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr8logMwHadTauTF", &classicSVfitPhiErr8logMwHadTauTF, &b_classicSVfitPhiErr8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid8logMwHadTauTF", &classicSVfitPhi_isValid8logMwHadTauTF, &b_classicSVfitPhi_isValid8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass8logMwHadTauTF", &classicSVfitMass8logMwHadTauTF, &b_classicSVfitMass8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr8logMwHadTauTF", &classicSVfitMassErr8logMwHadTauTF, &b_classicSVfitMassErr8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid8logMwHadTauTF", &classicSVfitMass_isValid8logMwHadTauTF, &b_classicSVfitMass_isValid8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass8logMwHadTauTF", &classicSVfitTransverseMass8logMwHadTauTF, &b_classicSVfitTransverseMass8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr8logMwHadTauTF", &classicSVfitTransverseMassErr8logMwHadTauTF, &b_classicSVfitTransverseMassErr8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid8logMwHadTauTF", &classicSVfitTransverseMass_isValid8logMwHadTauTF, &b_classicSVfitTransverseMass_isValid8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu8logMwHadTauTF", &classicSVfitComputingTime_cpu8logMwHadTauTF, &b_classicSVfitComputingTime_cpu8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real8logMwHadTauTF", &classicSVfitComputingTime_real8logMwHadTauTF, &b_classicSVfitComputingTime_real8logMwHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt8logMwoHadTauTF", &classicSVfitPt8logMwoHadTauTF, &b_classicSVfitPt8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPtErr8logMwoHadTauTF", &classicSVfitPtErr8logMwoHadTauTF, &b_classicSVfitPtErr8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPt_isValid8logMwoHadTauTF", &classicSVfitPt_isValid8logMwoHadTauTF, &b_classicSVfitPt_isValid8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta8logMwoHadTauTF", &classicSVfitEta8logMwoHadTauTF, &b_classicSVfitEta8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEtaErr8logMwoHadTauTF", &classicSVfitEtaErr8logMwoHadTauTF, &b_classicSVfitEtaErr8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitEta_isValid8logMwoHadTauTF", &classicSVfitEta_isValid8logMwoHadTauTF, &b_classicSVfitEta_isValid8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi8logMwoHadTauTF", &classicSVfitPhi8logMwoHadTauTF, &b_classicSVfitPhi8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhiErr8logMwoHadTauTF", &classicSVfitPhiErr8logMwoHadTauTF, &b_classicSVfitPhiErr8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitPhi_isValid8logMwoHadTauTF", &classicSVfitPhi_isValid8logMwoHadTauTF, &b_classicSVfitPhi_isValid8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass8logMwoHadTauTF", &classicSVfitMass8logMwoHadTauTF, &b_classicSVfitMass8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMassErr8logMwoHadTauTF", &classicSVfitMassErr8logMwoHadTauTF, &b_classicSVfitMassErr8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitMass_isValid8logMwoHadTauTF", &classicSVfitMass_isValid8logMwoHadTauTF, &b_classicSVfitMass_isValid8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass8logMwoHadTauTF", &classicSVfitTransverseMass8logMwoHadTauTF, &b_classicSVfitTransverseMass8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMassErr8logMwoHadTauTF", &classicSVfitTransverseMassErr8logMwoHadTauTF, &b_classicSVfitTransverseMassErr8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitTransverseMass_isValid8logMwoHadTauTF", &classicSVfitTransverseMass_isValid8logMwoHadTauTF, &b_classicSVfitTransverseMass_isValid8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_cpu8logMwoHadTauTF", &classicSVfitComputingTime_cpu8logMwoHadTauTF, &b_classicSVfitComputingTime_cpu8logMwoHadTauTF);
   fChain->SetBranchAddress("classicSVfitComputingTime_real8logMwoHadTauTF", &classicSVfitComputingTime_real8logMwoHadTauTF, &b_classicSVfitComputingTime_real8logMwoHadTauTF);
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
