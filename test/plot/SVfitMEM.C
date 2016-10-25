#define SVfitMEM_cxx
#include "SVfitMEM.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void SVfitMEM::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   cout << "sample: "   << sample   << endl;
   cout << "mass: "     << mass     << endl;
   cout << "dir: "      << dir      << endl;
   cout << "nentries: " << nentries << endl;
 
   int count{0};
   
   Long64_t nbytes = 0, nb = 0;
   //for (Long64_t jentry=0; jentry<5000;jentry++) {
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
       
      if(jentry > 0 && (jentry%10000)==0) cout << ">> processing event " << jentry << endl;
 
      passKin=false;
      isEMU=false;
      isMUHAD=false;
      isHADHAD=false;
      isGEN=false;
      isSMEARED=false;
 
      if(dir=="emu_gen" || dir=="emu_smeared")  isEMU=true;
      if(dir=="muhad_gen"){      isMUHAD=true;  isGEN=true; }
      if(dir=="hadhad_gen"){     isHADHAD=true; isGEN=true; }
      if(dir=="muhad_smeared"){  isMUHAD=true;  isSMEARED=true; }
      if(dir=="hadhad_smeared"){ isHADHAD=true; isSMEARED=true; }
      
      TLorentzVector GenElectron, GenMuon, GenHadTau1, GenHadTau2, SmearedHadTau1, SmearedHadTau2;
      TLorentzVector GenMEt, SmearedMEt;
      TLorentzVector GenTauLepton1, GenTauLepton2;
      TLorentzVector GenJet1, GenJet2, GenJet3, GenJet4;

      GenJet1.SetPxPyPzE(genJet1Px,genJet1Py,genJet1Pz,genJet1E);
      GenJet2.SetPxPyPzE(genJet2Px,genJet2Py,genJet2Pz,genJet2E);
      GenJet3.SetPxPyPzE(genJet3Px,genJet3Py,genJet3Pz,genJet3E);
      GenJet4.SetPxPyPzE(genJet4Px,genJet4Py,genJet4Pz,genJet4E);
     
      std::vector<TLorentzVector> GenJets;
      GenJets.push_back(GenJet1);
      GenJets.push_back(GenJet2);
      GenJets.push_back(GenJet3);
      GenJets.push_back(GenJet4);
 
      GenTauLepton1.SetPxPyPzE(genTauLepton1Px,genTauLepton1Py,genTauLepton1Pz,genTauLepton1E);
      GenTauLepton2.SetPxPyPzE(genTauLepton2Px,genTauLepton2Py,genTauLepton2Pz,genTauLepton2E);
      GenElectron.SetPxPyPzE(genElectron1Px,genElectron1Py,genElectron1Pz,genElectron1E);
      GenMuon.SetPxPyPzE(genMuon1Px,genMuon1Py,genMuon1Pz,genMuon1E);
      GenHadTau1.SetPxPyPzE(genHadTau1Px,genHadTau1Py,genHadTau1Pz,genHadTau1E);
      GenHadTau2.SetPxPyPzE(genHadTau2Px,genHadTau2Py,genHadTau2Pz,genHadTau2E);
      SmearedHadTau1.SetPxPyPzE(smearedHadTau1Px,smearedHadTau1Py,smearedHadTau1Pz,smearedHadTau1E);
      SmearedHadTau2.SetPxPyPzE(smearedHadTau2Px,smearedHadTau2Py,smearedHadTau2Pz,smearedHadTau2E);
  
      GenMEt.SetPxPyPzE(genMEtPx,genMEtPy,0,genMEtPt);
      SmearedMEt.SetPxPyPzE(smearedMEtPx,smearedMEtPy,0,smearedMEtPt);

      if(isEMU){ if(max(GenElectron.Pt(),GenMuon.Pt())>20 && min(GenElectron.Pt(),GenMuon.Pt())>10 &&
			      fabs(GenElectron.Eta())<2.4 && fabs(GenMuon.Eta())<2.1 ) passKin = true; }
      if(isMUHAD && isGEN){ if(GenMuon.Pt()>20 && GenHadTau1.Pt()>30 && fabs(GenMuon.Eta())<2.1 && fabs(GenHadTau1.Eta())<2.3 ) passKin = true; }
      if(isMUHAD && isSMEARED){ if(GenMuon.Pt()>20 && SmearedHadTau1.Pt()>30 && fabs(GenMuon.Eta())<2.1 && fabs(SmearedHadTau1.Eta())<2.3 ) passKin = true; }
      if(isHADHAD && isGEN){ if(GenHadTau1.Pt()>45 && GenHadTau2.Pt()>45 && fabs(GenHadTau1.Eta())<2.1 && fabs(GenHadTau2.Eta())<2.1 ) passKin = true; }
      if(isHADHAD && isSMEARED){ if(SmearedHadTau1.Pt()>45 && SmearedHadTau2.Pt()>45 && fabs(SmearedHadTau1.Eta())<2.1 && fabs(SmearedHadTau2.Eta())<2.1 ) passKin = true; }

      if(!passKin) continue; 
      
      //cout << " passed kinematic selection "<< endl;      

      TLorentzVector candVisiblePlusMET;
      TLorentzVector candVisible;
      TLorentzVector genDiTauCandidate;
      double dphi;     
 
      if(isEMU){
	      candVisiblePlusMET = GenElectron + GenMuon + SmearedMEt; //directly SmearedMEt here, in the end it will be what you will use
	      candVisible = GenElectron + GenMuon;
	      dphi = GenElectron.DeltaPhi(GenMuon);
      } 
      if(isMUHAD && isGEN){
	      candVisiblePlusMET = GenMuon + GenHadTau1 + GenMEt;
	      candVisible = GenMuon + GenHadTau1;
	      dphi = GenMuon.DeltaPhi(GenHadTau1);
      } 
      if(isMUHAD && isSMEARED){
	      candVisiblePlusMET = GenMuon + SmearedHadTau1 + SmearedMEt;
	      candVisible = GenMuon + SmearedHadTau1;
	      dphi = GenMuon.DeltaPhi(SmearedHadTau1);
      } 
      if(isHADHAD && isGEN){ 
	      candVisiblePlusMET = GenHadTau1 + GenHadTau2 + GenMEt;
	      candVisible = GenHadTau1 + GenHadTau2;
	      dphi = GenHadTau1.DeltaPhi(GenHadTau2);
      } 
      if(isHADHAD && isSMEARED){
	      candVisiblePlusMET = SmearedHadTau1 + SmearedHadTau2 + SmearedMEt;
	      candVisible = SmearedHadTau1 + SmearedHadTau2;
	      dphi = SmearedHadTau1.DeltaPhi(SmearedHadTau2);
      } 
      
      int  nGenJets  = 0;
      int  nVBFpairs = 0;
      bool category_0Jets          = false;
      bool category_1JetBoosted    = false;
      bool category_1JetNotBoosted = false;
      bool category_2Jets          = false;
      bool categorization          = false;
    
      for(size_t ijet=0; ijet<GenJets.size(); ijet++){
	      if(GenJets[ijet].Pt()>30 && TMath::Abs(GenJets[ijet].Eta())<4.5) nGenJets++;
	      for(size_t jjet=0; jjet<GenJets.size(); jjet++){
		      if( GenJets[ijet].Pt()>30 && TMath::Abs(GenJets[ijet].Eta())<4.5 && 
		          GenJets[jjet].Pt()>30 && TMath::Abs(GenJets[jjet].Eta())<4.5 && 
			  (GenJets[ijet]+GenJets[jjet]).M()>500 && 
			  TMath::Abs( GenJets[ijet].Eta()-GenJets[jjet].Eta() )>3.5) nVBFpairs++;
	      }
      }

      if ( nGenJets >= 2 && nVBFpairs >= 1 ) {
	      category_2Jets = true;
      } else if ( nGenJets >= 1 ) {
	      if ( genDiTauPt > 100. ) category_1JetBoosted = true;
	      else category_1JetNotBoosted = true;
      } else {
	      category_0Jets = true;
      } 

      hResolutionPt[0]->Fill(candVisiblePlusMET.Pt()-genDiTauPt);
      hResolutionEta[0]->Fill(candVisiblePlusMET.Eta()-genDiTauEta);
      hResolutionPhi[0]->Fill(candVisiblePlusMET.Phi()-genDiTauPhi);
      genDiTauCandidate = GenTauLepton1+GenTauLepton2;
      std::string category_string;
      if ( category_2Jets          ) category_string.append("2Jets");
      if ( category_1JetBoosted    ) category_string.append("1JetBoosted");
      if ( category_1JetNotBoosted ) category_string.append("1JetNotBoosted");
      if ( category_0Jets          ) category_string.append("0Jets");
      //std::cout << "category = " << category_string << ", genDiTauCandidate: pT = " << genDiTauCandidate.Pt() << ", mass = " << genDiTauCandidate.M() << std::endl;
      
      hDiTauPt->Fill(genDiTauCandidate.Pt());
      hTauDPhi->Fill(TMath::ACos(TMath::Cos(GenTauLepton1.Phi()-GenTauLepton2.Phi())));
      if(category_0Jets)          hDiTauPt_0Jets->Fill(genDiTauCandidate.Pt());
      if(category_1JetBoosted)    hDiTauPt_1JetBoosted->Fill(genDiTauCandidate.Pt());
      if(category_1JetNotBoosted) hDiTauPt_1JetNotBoosted->Fill(genDiTauCandidate.Pt());
      if(category_2Jets)          hDiTauPt_2Jets->Fill(genDiTauCandidate.Pt());
      if(category_0Jets)          hTauDPhi_0Jets->Fill(TMath::ACos(TMath::Cos(GenTauLepton1.Phi()-GenTauLepton2.Phi())));
      if(category_1JetBoosted)    hTauDPhi_1JetBoosted->Fill(TMath::ACos(TMath::Cos(GenTauLepton1.Phi()-GenTauLepton2.Phi())));
      if(category_1JetNotBoosted) hTauDPhi_1JetNotBoosted->Fill(TMath::ACos(TMath::Cos(GenTauLepton1.Phi()-GenTauLepton2.Phi())));
      if(category_2Jets)          hTauDPhi_2Jets->Fill(TMath::ACos(TMath::Cos(GenTauLepton1.Phi()-GenTauLepton2.Phi())));

      hpassCuts->Fill(0);

      if(svfitMass_isValid && svfitMass>270){ hmass_SVFIT_grt_270->Fill(visMass); hmass_SVFIT_grt_270_ratio->Fill(visMass/genDiTauMass); }
      if(svfitMass_isValid && svfitMass<120){ hmass_SVFIT_lst_120->Fill(visMass); hmass_SVFIT_lst_120_ratio->Fill(visMass/genDiTauMass); }
      if(svfitMass_isValid && svfitMass>270){
              if(isGEN) hmet_SVFIT_grt_270->Fill(genMEtPt);
	      if(isSMEARED) hmet_SVFIT_grt_270->Fill(smearedMEtPt);
	      if(isEMU){ hpt1_SVFIT_grt_270->Fill(GenElectron.Pt()); hpt2_SVFIT_grt_270->Fill(GenMuon.Pt()); }
	      if(isMUHAD && isGEN){ hpt1_SVFIT_grt_270->Fill(GenMuon.Pt()); hpt2_SVFIT_grt_270->Fill(GenHadTau1.Pt()); }
	      if(isMUHAD && isSMEARED){ hpt1_SVFIT_grt_270->Fill(GenMuon.Pt()); hpt2_SVFIT_grt_270->Fill(SmearedHadTau1.Pt()); }
	      if(isHADHAD && isGEN){ hpt1_SVFIT_grt_270->Fill(GenHadTau1.Pt()); hpt2_SVFIT_grt_270->Fill(GenHadTau2.Pt()); }
	      if(isHADHAD && isSMEARED){ hpt1_SVFIT_grt_270->Fill(SmearedHadTau1.Pt()); hpt2_SVFIT_grt_270->Fill(SmearedHadTau2.Pt()); }
      }
      if(svfitMass_isValid && svfitMass<120){
	      //cout << "I'm in the IF svfitMass_isValid && svfitMass>120" << endl;
	      if(isGEN) hmet_SVFIT_lst_120->Fill(genMEtPt);
	      if(isSMEARED) hmet_SVFIT_lst_120->Fill(smearedMEtPt);
	      if(isEMU){ hpt1_SVFIT_lst_120->Fill(GenElectron.Pt()); hpt2_SVFIT_lst_120->Fill(GenMuon.Pt()); }
	      if(isMUHAD && isGEN){ hpt1_SVFIT_lst_120->Fill(GenMuon.Pt()); hpt2_SVFIT_lst_120->Fill(GenHadTau1.Pt()); }
	      if(isMUHAD && isSMEARED){ hpt1_SVFIT_lst_120->Fill(GenMuon.Pt()); hpt2_SVFIT_lst_120->Fill(SmearedHadTau1.Pt()); }
	      if(isHADHAD && isGEN){ hpt1_SVFIT_lst_120->Fill(GenHadTau1.Pt()); hpt2_SVFIT_lst_120->Fill(GenHadTau2.Pt()); }
	      if(isHADHAD && isSMEARED){ hpt1_SVFIT_lst_120->Fill(SmearedHadTau1.Pt()); hpt2_SVFIT_lst_120->Fill(SmearedHadTau2.Pt()); }
      }

      hmass[0]->Fill(visMass); 
      if(category_0Jets)          hmass_0Jets[0]->Fill(visMass);
      if(category_1JetNotBoosted) hmass_1JetNotBoosted[0]->Fill(visMass);
      if(category_1JetBoosted)    hmass_1JetBoosted[0]->Fill(visMass);
      if(category_2Jets)          hmass_2Jets[0]->Fill(visMass);
  
      hmasslin[0]->Fill(visMass); 
      hmasslog[0]->Fill(visMass); 
      if(category_0Jets)          {hmasslin_0Jets[0]->Fill(visMass); hmasslog_0Jets[0]->Fill(visMass);}
      if(category_1JetNotBoosted) {hmasslin_1JetNotBoosted[0]->Fill(visMass); hmasslog_1JetNotBoosted[0]->Fill(visMass);}
      if(category_1JetBoosted)    {hmasslin_1JetBoosted[0]->Fill(visMass); hmasslog_1JetBoosted[0]->Fill(visMass);}
      if(category_2Jets)          {hmasslin_2Jets[0]->Fill(visMass); hmasslog_2Jets[0]->Fill(visMass);}
      
      hmasslin_ratio[0]->Fill(visMass/genDiTauMass);
      hmasslog_ratio[0]->Fill(visMass/genDiTauMass);
      if(category_0Jets)          {hmasslin_ratio_0Jets[0]->Fill(visMass/genDiTauMass); hmasslog_ratio_0Jets[0]->Fill(visMass/genDiTauMass);}
      if(category_1JetNotBoosted) {hmasslin_ratio_1JetNotBoosted[0]->Fill(visMass/genDiTauMass); hmasslog_ratio_1JetNotBoosted[0]->Fill(visMass/genDiTauMass);}
      if(category_1JetBoosted)    {hmasslin_ratio_1JetBoosted[0]->Fill(visMass/genDiTauMass); hmasslog_ratio_1JetBoosted[0]->Fill(visMass/genDiTauMass);}
      if(category_2Jets)          {hmasslin_ratio_2Jets[0]->Fill(visMass/genDiTauMass); hmasslog_ratio_2Jets[0]->Fill(visMass/genDiTauMass);}

      if(caMass_isValid){ 
	      hmass[1]->Fill(caMass); 
	      if(category_0Jets)          hmass_0Jets[1]->Fill(caMass);
	      if(category_1JetNotBoosted) hmass_1JetNotBoosted[1]->Fill(caMass);
	      if(category_1JetBoosted)    hmass_1JetBoosted[1]->Fill(caMass);
	      if(category_2Jets)          hmass_2Jets[1]->Fill(caMass);
	      hmasslin[1]->Fill(caMass); 
	      hmasslog[1]->Fill(caMass); 
	      if(category_0Jets)          {hmasslin_0Jets[1]->Fill(caMass); hmasslog_0Jets[1]->Fill(caMass);}
	      if(category_1JetNotBoosted) {hmasslin_1JetNotBoosted[1]->Fill(caMass); hmasslog_1JetNotBoosted[1]->Fill(caMass);}
	      if(category_1JetBoosted)    {hmasslin_1JetBoosted[1]->Fill(caMass); hmasslog_1JetBoosted[1]->Fill(caMass);}
	      if(category_2Jets)          {hmasslin_2Jets[1]->Fill(caMass); hmasslog_2Jets[1]->Fill(caMass);}
	      hmasslin_ratio[1]->Fill(caMass/genDiTauMass); 
	      hmasslog_ratio[1]->Fill(caMass/genDiTauMass); 
	      if(category_0Jets)          {hmasslin_ratio_0Jets[1]->Fill(caMass/genDiTauMass); hmasslog_ratio_0Jets[1]->Fill(caMass/genDiTauMass);}
	      if(category_1JetNotBoosted) {hmasslin_ratio_1JetNotBoosted[1]->Fill(caMass/genDiTauMass); hmasslog_ratio_1JetNotBoosted[1]->Fill(caMass/genDiTauMass);}
	      if(category_1JetBoosted)    {hmasslin_ratio_1JetBoosted[1]->Fill(caMass/genDiTauMass); hmasslog_ratio_1JetBoosted[1]->Fill(caMass/genDiTauMass);}
	      if(category_2Jets)          {hmasslin_ratio_2Jets[1]->Fill(caMass/genDiTauMass); hmasslog_ratio_2Jets[1]->Fill(caMass/genDiTauMass);}
      }
      if(svfitMass_isValid){
	      hmass[2]->Fill(svfitMass); 
	      if(category_0Jets)          hmass_0Jets[2]->Fill(svfitMass);
	      if(category_1JetNotBoosted) hmass_1JetNotBoosted[2]->Fill(svfitMass);
	      if(category_1JetBoosted)    hmass_1JetBoosted[2]->Fill(svfitMass);
	      if(category_2Jets)          hmass_2Jets[2]->Fill(svfitMass);
	      hmasslin[2]->Fill(svfitMass); 
	      hmasslog[2]->Fill(svfitMass); 
	      if(category_0Jets)          {hmasslin_0Jets[2]->Fill(svfitMass); hmasslog_0Jets[2]->Fill(svfitMass);}
	      if(category_1JetNotBoosted) {hmasslin_1JetNotBoosted[2]->Fill(svfitMass); hmasslog_1JetNotBoosted[2]->Fill(svfitMass);}
	      if(category_1JetBoosted)    {hmasslin_1JetBoosted[2]->Fill(svfitMass); hmasslog_1JetBoosted[2]->Fill(svfitMass);}
	      if(category_2Jets)          {hmasslin_2Jets[2]->Fill(svfitMass); hmasslog_2Jets[2]->Fill(svfitMass);}
	      hmasslin_ratio[2]->Fill(svfitMass/genDiTauMass); 
	      hmasslog_ratio[2]->Fill(svfitMass/genDiTauMass); 
	      if(category_0Jets)          {hmasslin_ratio_0Jets[2]->Fill(svfitMass/genDiTauMass); hmasslog_ratio_0Jets[2]->Fill(svfitMass/genDiTauMass);}
	      if(category_1JetNotBoosted) {hmasslin_ratio_1JetNotBoosted[2]->Fill(svfitMass/genDiTauMass); hmasslog_ratio_1JetNotBoosted[2]->Fill(svfitMass/genDiTauMass);}
	      if(category_1JetBoosted)    {hmasslin_ratio_1JetBoosted[2]->Fill(svfitMass/genDiTauMass); hmasslog_ratio_1JetBoosted[2]->Fill(svfitMass/genDiTauMass);}
	      if(category_2Jets)          {hmasslin_ratio_2Jets[2]->Fill(svfitMass/genDiTauMass); hmasslog_ratio_2Jets[2]->Fill(svfitMass/genDiTauMass);}
              hCPUtime_log[0]->Fill(svfitComputingTime_cpu);
      }

      int   istfk0     {svfitMass_isValidMEMlo0logMwHadTauTF};
      int   istfk1     {svfitMass_isValidMEMlo1logMwHadTauTF};
      int   istfk2     {svfitMass_isValidMEMlo2logMwHadTauTF};
      int   istfk3     {svfitMass_isValidMEMlo3logMwHadTauTF};
      int   istfk4     {svfitMass_isValidMEMlo4logMwHadTauTF};
      int   istfk5     {svfitMass_isValidMEMlo5logMwHadTauTF};
      int   istfk6     {svfitMass_isValidMEMlo6logMwHadTauTF};
      int   istfk7     {svfitMass_isValidMEMlo7logMwHadTauTF};
      int   istfk8     {svfitMass_isValidMEMlo8logMwHadTauTF};
      vector<int> vistfk{istfk0, istfk1, istfk2, istfk3, istfk4, istfk5, istfk6, istfk7, istfk8};

      int   isctfk0     {classicSVfitMass_isValid0logMwHadTauTF};
      int   isctfk1     {classicSVfitMass_isValid1logMwHadTauTF};
      int   isctfk2     {classicSVfitMass_isValid2logMwHadTauTF};
      int   isctfk3     {classicSVfitMass_isValid3logMwHadTauTF};
      int   isctfk4     {classicSVfitMass_isValid4logMwHadTauTF};
      int   isctfk5     {classicSVfitMass_isValid5logMwHadTauTF};
      int   isctfk6     {classicSVfitMass_isValid6logMwHadTauTF};
      int   isctfk7     {classicSVfitMass_isValid7logMwHadTauTF};
      int   isctfk8     {classicSVfitMass_isValid8logMwHadTauTF};
      vector<int> visctfk{isctfk0, isctfk1, isctfk2, isctfk3, isctfk4, isctfk5, isctfk6, isctfk7, isctfk8};

      float tfk0  {svfitMassMEMlo0logMwHadTauTF}; 
      float tfk1  {svfitMassMEMlo1logMwHadTauTF}; 
      float tfk2  {svfitMassMEMlo2logMwHadTauTF}; 
      float tfk3  {svfitMassMEMlo3logMwHadTauTF}; 
      float tfk4  {svfitMassMEMlo4logMwHadTauTF}; 
      float tfk5  {svfitMassMEMlo5logMwHadTauTF}; 
      float tfk6  {svfitMassMEMlo6logMwHadTauTF}; 
      float tfk7  {svfitMassMEMlo7logMwHadTauTF}; 
      float tfk8  {svfitMassMEMlo8logMwHadTauTF}; 
      vector<float> vtfk{tfk0, tfk1, tfk2, tfk3, tfk4, tfk5, tfk6, tfk7, tfk8};
      
      float ctfk0  {classicSVfitMass0logMwHadTauTF}; 
      float ctfk1  {classicSVfitMass1logMwHadTauTF}; 
      float ctfk2  {classicSVfitMass2logMwHadTauTF}; 
      float ctfk3  {classicSVfitMass3logMwHadTauTF}; 
      float ctfk4  {classicSVfitMass4logMwHadTauTF}; 
      float ctfk5  {classicSVfitMass5logMwHadTauTF}; 
      float ctfk6  {classicSVfitMass6logMwHadTauTF}; 
      float ctfk7  {classicSVfitMass7logMwHadTauTF}; 
      float ctfk8  {classicSVfitMass8logMwHadTauTF}; 
      vector<float> vctfk{ctfk0, ctfk1, ctfk2, ctfk3, ctfk4, ctfk5, ctfk6, ctfk7, ctfk8};
      
      float ctfk0Pt  {classicSVfitPt0logMwHadTauTF}; 
      float ctfk1Pt  {classicSVfitPt1logMwHadTauTF}; 
      float ctfk2Pt  {classicSVfitPt2logMwHadTauTF}; 
      float ctfk3Pt  {classicSVfitPt3logMwHadTauTF}; 
      float ctfk4Pt  {classicSVfitPt4logMwHadTauTF}; 
      float ctfk5Pt  {classicSVfitPt5logMwHadTauTF}; 
      float ctfk6Pt  {classicSVfitPt6logMwHadTauTF}; 
      float ctfk7Pt  {classicSVfitPt7logMwHadTauTF}; 
      float ctfk8Pt  {classicSVfitPt8logMwHadTauTF}; 
      vector<float> vctfkPt{ctfk0Pt, ctfk1Pt, ctfk2Pt, ctfk3Pt, ctfk4Pt, ctfk5Pt, ctfk6Pt, ctfk7Pt, ctfk8Pt};
      
      float ctfk0Eta  {classicSVfitEta0logMwHadTauTF}; 
      float ctfk1Eta  {classicSVfitEta1logMwHadTauTF}; 
      float ctfk2Eta  {classicSVfitEta2logMwHadTauTF}; 
      float ctfk3Eta  {classicSVfitEta3logMwHadTauTF}; 
      float ctfk4Eta  {classicSVfitEta4logMwHadTauTF}; 
      float ctfk5Eta  {classicSVfitEta5logMwHadTauTF}; 
      float ctfk6Eta  {classicSVfitEta6logMwHadTauTF}; 
      float ctfk7Eta  {classicSVfitEta7logMwHadTauTF}; 
      float ctfk8Eta  {classicSVfitEta8logMwHadTauTF}; 
      vector<float> vctfkEta{ctfk0Eta, ctfk1Eta, ctfk2Eta, ctfk3Eta, ctfk4Eta, ctfk5Eta, ctfk6Eta, ctfk7Eta, ctfk8Eta};
      
      float ctfk0Phi  {classicSVfitPhi0logMwHadTauTF}; 
      float ctfk1Phi  {classicSVfitPhi1logMwHadTauTF}; 
      float ctfk2Phi  {classicSVfitPhi2logMwHadTauTF}; 
      float ctfk3Phi  {classicSVfitPhi3logMwHadTauTF}; 
      float ctfk4Phi  {classicSVfitPhi4logMwHadTauTF}; 
      float ctfk5Phi  {classicSVfitPhi5logMwHadTauTF}; 
      float ctfk6Phi  {classicSVfitPhi6logMwHadTauTF}; 
      float ctfk7Phi  {classicSVfitPhi7logMwHadTauTF}; 
      float ctfk8Phi  {classicSVfitPhi8logMwHadTauTF}; 
      vector<float> vctfkPhi{ctfk0Phi, ctfk1Phi, ctfk2Phi, ctfk3Phi, ctfk4Phi, ctfk5Phi, ctfk6Phi, ctfk7Phi, ctfk8Phi};
        
      float cpuMEMlo0 {svfitComputingTime_cpuMEMlo0logMwHadTauTF};
      float cpuMEMlo1 {svfitComputingTime_cpuMEMlo1logMwHadTauTF};
      float cpuMEMlo2 {svfitComputingTime_cpuMEMlo2logMwHadTauTF};
      float cpuMEMlo3 {svfitComputingTime_cpuMEMlo3logMwHadTauTF};
      float cpuMEMlo4 {svfitComputingTime_cpuMEMlo4logMwHadTauTF};
      float cpuMEMlo5 {svfitComputingTime_cpuMEMlo5logMwHadTauTF};
      float cpuMEMlo6 {svfitComputingTime_cpuMEMlo6logMwHadTauTF};
      float cpuMEMlo7 {svfitComputingTime_cpuMEMlo7logMwHadTauTF};
      float cpuMEMlo8 {svfitComputingTime_cpuMEMlo8logMwHadTauTF};
      vector<float> vcpuMEM{cpuMEMlo0,cpuMEMlo1,cpuMEMlo2,cpuMEMlo3,cpuMEMlo4,cpuMEMlo5,cpuMEMlo6,cpuMEMlo7,cpuMEMlo8};
      
      float cpuCLAlo0 {classicSVfitComputingTime_cpu0logMwHadTauTF};
      float cpuCLAlo1 {classicSVfitComputingTime_cpu1logMwHadTauTF};
      float cpuCLAlo2 {classicSVfitComputingTime_cpu2logMwHadTauTF};
      float cpuCLAlo3 {classicSVfitComputingTime_cpu3logMwHadTauTF};
      float cpuCLAlo4 {classicSVfitComputingTime_cpu4logMwHadTauTF};
      float cpuCLAlo5 {classicSVfitComputingTime_cpu5logMwHadTauTF};
      float cpuCLAlo6 {classicSVfitComputingTime_cpu6logMwHadTauTF};
      float cpuCLAlo7 {classicSVfitComputingTime_cpu7logMwHadTauTF};
      float cpuCLAlo8 {classicSVfitComputingTime_cpu8logMwHadTauTF};
      vector<float> vcpuCLA{cpuCLAlo0,cpuCLAlo1,cpuCLAlo2,cpuCLAlo3,cpuCLAlo4,cpuCLAlo5,cpuCLAlo6,cpuCLAlo7,cpuCLAlo8};


      for(size_t itfk=0; itfk<vtfk.size(); itfk++){
	      if(vistfk[itfk]==1){ 
		      //hmass[itfk+3]->Fill(vtfk[itfk]); 
		      //hmasslin[itfk+3]->Fill(vtfk[itfk]); 
		      //hmasslog[itfk+3]->Fill(vtfk[itfk]);
		      //hmasslin_ratio[itfk+3]->Fill(vtfk[itfk]/genDiTauMass); 
		      //hmasslog_ratio[itfk+3]->Fill(vtfk[itfk]/genDiTauMass);
		      hmass[itfk+3]->Fill(vtfk[itfk]); 
		      if(category_0Jets)          hmass_0Jets[itfk+3]->Fill(vtfk[itfk]);
		      if(category_1JetNotBoosted) hmass_1JetNotBoosted[itfk+3]->Fill(vtfk[itfk]);
		      if(category_1JetBoosted)    hmass_1JetBoosted[itfk+3]->Fill(vtfk[itfk]);
		      if(category_2Jets)          hmass_2Jets[itfk+3]->Fill(vtfk[itfk]);
		      hmasslin[itfk+3]->Fill(vtfk[itfk]); 
		      hmasslog[itfk+3]->Fill(vtfk[itfk]); 
		      if(category_0Jets)          {hmasslin_0Jets[itfk+3]->Fill(vtfk[itfk]); hmasslog_0Jets[itfk+3]->Fill(vtfk[itfk]);}
		      if(category_1JetNotBoosted) {hmasslin_1JetNotBoosted[itfk+3]->Fill(vtfk[itfk]); hmasslog_1JetNotBoosted[itfk+3]->Fill(vtfk[itfk]);}
		      if(category_1JetBoosted)    {hmasslin_1JetBoosted[itfk+3]->Fill(vtfk[itfk]); hmasslog_1JetBoosted[itfk+3]->Fill(vtfk[itfk]);}
		      if(category_2Jets)          {hmasslin_2Jets[itfk+3]->Fill(vtfk[itfk]); hmasslog_2Jets[itfk+3]->Fill(vtfk[itfk]);}
		      hmasslin_ratio[itfk+3]->Fill(vtfk[itfk]/genDiTauMass); 
		      hmasslog_ratio[itfk+3]->Fill(vtfk[itfk]/genDiTauMass); 
		      if(category_0Jets)          {hmasslin_ratio_0Jets[itfk+3]->Fill(vtfk[itfk]/genDiTauMass); hmasslog_ratio_0Jets[itfk+3]->Fill(vtfk[itfk]/genDiTauMass);}
		      if(category_1JetNotBoosted) {hmasslin_ratio_1JetNotBoosted[itfk+3]->Fill(vtfk[itfk]/genDiTauMass); hmasslog_ratio_1JetNotBoosted[itfk+3]->Fill(vtfk[itfk]/genDiTauMass);}
		      if(category_1JetBoosted)    {hmasslin_ratio_1JetBoosted[itfk+3]->Fill(vtfk[itfk]/genDiTauMass); hmasslog_ratio_1JetBoosted[itfk+3]->Fill(vtfk[itfk]/genDiTauMass);}
		      if(category_2Jets)          {hmasslin_ratio_2Jets[itfk+3]->Fill(vtfk[itfk]/genDiTauMass); hmasslog_ratio_2Jets[itfk+3]->Fill(vtfk[itfk]/genDiTauMass);}
	      }
      }
      for(size_t itfk=0; itfk<vctfk.size(); itfk++){
	      if(visctfk[itfk]==1){ 
		      //hmass[itfk+12]->Fill(vctfk[itfk]); 
		      //hmasslin[itfk+12]->Fill(vctfk[itfk]); 
		      //hmasslog[itfk+12]->Fill(vctfk[itfk]);
		      //hmasslin_ratio[itfk+12]->Fill(vctfk[itfk]/genDiTauMass); 
		      //hmasslog_ratio[itfk+12]->Fill(vctfk[itfk]/genDiTauMass);
		      hmass[itfk+12]->Fill(vctfk[itfk]); 
		      if(category_0Jets)          hmass_0Jets[itfk+12]->Fill(vctfk[itfk]);
		      if(category_1JetNotBoosted) hmass_1JetNotBoosted[itfk+12]->Fill(vctfk[itfk]);
		      if(category_1JetBoosted)    hmass_1JetBoosted[itfk+12]->Fill(vctfk[itfk]);
		      if(category_2Jets)          hmass_2Jets[itfk+12]->Fill(vctfk[itfk]);
		      hmasslin[itfk+12]->Fill(vctfk[itfk]); 
		      hmasslog[itfk+12]->Fill(vctfk[itfk]); 
		      if(category_0Jets)          {hmasslin_0Jets[itfk+12]->Fill(vctfk[itfk]); hmasslog_0Jets[itfk+12]->Fill(vctfk[itfk]);}
		      if(category_1JetNotBoosted) {hmasslin_1JetNotBoosted[itfk+12]->Fill(vctfk[itfk]); hmasslog_1JetNotBoosted[itfk+12]->Fill(vctfk[itfk]);}
		      if(category_1JetBoosted)    {hmasslin_1JetBoosted[itfk+12]->Fill(vctfk[itfk]); hmasslog_1JetBoosted[itfk+12]->Fill(vctfk[itfk]);}
		      if(category_2Jets)          {hmasslin_2Jets[itfk+12]->Fill(vctfk[itfk]); hmasslog_2Jets[itfk+12]->Fill(vctfk[itfk]);}
		      hmasslin_ratio[itfk+12]->Fill(vctfk[itfk]/genDiTauMass); 
		      hmasslog_ratio[itfk+12]->Fill(vctfk[itfk]/genDiTauMass); 
		      if(category_0Jets)          {hmasslin_ratio_0Jets[itfk+12]->Fill(vctfk[itfk]/genDiTauMass); hmasslog_ratio_0Jets[itfk+12]->Fill(vctfk[itfk]/genDiTauMass);}
		      if(category_1JetNotBoosted) {hmasslin_ratio_1JetNotBoosted[itfk+12]->Fill(vctfk[itfk]/genDiTauMass); hmasslog_ratio_1JetNotBoosted[itfk+12]->Fill(vctfk[itfk]/genDiTauMass);}
		      if(category_1JetBoosted)    {hmasslin_ratio_1JetBoosted[itfk+12]->Fill(vctfk[itfk]/genDiTauMass); hmasslog_ratio_1JetBoosted[itfk+12]->Fill(vctfk[itfk]/genDiTauMass);}
		      if(category_2Jets)          {hmasslin_ratio_2Jets[itfk+12]->Fill(vctfk[itfk]/genDiTauMass); hmasslog_ratio_2Jets[itfk+12]->Fill(vctfk[itfk]/genDiTauMass);}
		      
                      hResolutionPt[itfk+1]->Fill(vctfkPt[itfk]-genDiTauPt);
		      hResolutionEta[itfk+1]->Fill(vctfkEta[itfk]-genDiTauEta);
		      hResolutionPhi[itfk+1]->Fill(vctfkPhi[itfk]-genDiTauPhi);
	      }
      }
      for(size_t icpu=0; icpu<vcpuMEM.size(); icpu++){
	      hCPUtime_log[icpu]->Fill(vcpuMEM[icpu]);
      }
      for(size_t icpu=0; icpu<vcpuMEM.size(); icpu++){
	      hCPUtime_log[icpu+10]->Fill(vcpuCLA[icpu]);
      }


   } //this bracket closes the loop on the event

   cout<<"\n writing hist..."<<endl;

   hmass_SVFIT_grt_270->Scale(1/hmass_SVFIT_grt_270->Integral()); hmass_SVFIT_grt_270->Write();
   hmass_SVFIT_lst_120->Scale(1/hmass_SVFIT_lst_120->Integral()); hmass_SVFIT_lst_120->Write();
   hmass_SVFIT_grt_270_ratio->Scale(1/hmass_SVFIT_grt_270_ratio->Integral()); hmass_SVFIT_grt_270_ratio->Write();
   hmass_SVFIT_lst_120_ratio->Scale(1/hmass_SVFIT_lst_120_ratio->Integral()); hmass_SVFIT_lst_120_ratio->Write();
   hpt1_SVFIT_grt_270->Scale(1/hpt1_SVFIT_grt_270->Integral());  hpt1_SVFIT_grt_270->Write();
   hpt1_SVFIT_lst_120->Scale(1/hpt1_SVFIT_lst_120->Integral());  hpt1_SVFIT_lst_120->Write();
   hpt2_SVFIT_grt_270->Scale(1/hpt2_SVFIT_grt_270->Integral());  hpt2_SVFIT_grt_270->Write();
   hpt2_SVFIT_lst_120->Scale(1/hpt2_SVFIT_lst_120->Integral());  hpt2_SVFIT_lst_120->Write();
   hmet_SVFIT_grt_270->Scale(1/hmet_SVFIT_grt_270->Integral());  hmet_SVFIT_grt_270->Write();
   hmet_SVFIT_lst_120->Scale(1/hmet_SVFIT_lst_120->Integral());  hmet_SVFIT_lst_120->Write();
   hDiTauPt->Scale(1/hDiTauPt->Integral());          hDiTauPt->Write();
   hDiTauPt_0Jets->Scale(1/hDiTauPt_0Jets->Integral());          hDiTauPt_0Jets->Write();
   hDiTauPt_2Jets->Scale(1/hDiTauPt_2Jets->Integral());          hDiTauPt_2Jets->Write();
   hDiTauPt_1JetNotBoosted->Scale(1/hDiTauPt_1JetNotBoosted->Integral());    hDiTauPt_1JetNotBoosted->Write();
   hDiTauPt_1JetBoosted->Scale(1/hDiTauPt_1JetBoosted->Integral());          hDiTauPt_1JetBoosted->Write();
   hTauDPhi->Scale(1/hTauDPhi->Integral());                      hTauDPhi->Write();
   hTauDPhi_0Jets->Scale(1/hTauDPhi_0Jets->Integral());                      hTauDPhi_0Jets->Write();
   hTauDPhi_2Jets->Scale(1/hTauDPhi_2Jets->Integral());                      hTauDPhi_2Jets->Write();
   hTauDPhi_1JetNotBoosted->Scale(1/hTauDPhi_1JetNotBoosted->Integral());    hTauDPhi_1JetNotBoosted->Write();
   hTauDPhi_1JetBoosted->Scale(1/hTauDPhi_1JetBoosted->Integral());          hTauDPhi_1JetBoosted->Write();

   for(size_t iplot=0; iplot<nplotToInclude; iplot++){
	   hmass[iplot]->Scale(1/hmass[iplot]->Integral()); hmass[iplot]->Write(); 
	   hmass_0Jets[iplot]->Scale(1/hmass_0Jets[iplot]->Integral()); hmass_0Jets[iplot]->Write(); 
	   hmass_1JetNotBoosted[iplot]->Scale(1/hmass_1JetNotBoosted[iplot]->Integral()); hmass_1JetNotBoosted[iplot]->Write(); 
	   hmass_1JetBoosted[iplot]->Scale(1/hmass_1JetBoosted[iplot]->Integral()); hmass_1JetBoosted[iplot]->Write(); 
	   hmass_2Jets[iplot]->Scale(1/hmass_2Jets[iplot]->Integral()); hmass_2Jets[iplot]->Write(); 
	   
           hmasslin[iplot]->Scale(1/hmasslin[iplot]->Integral()); hmasslin[iplot]->Write(); 
           hmasslin_0Jets[iplot]->Scale(1/hmasslin_0Jets[iplot]->Integral()); hmasslin_0Jets[iplot]->Write(); 
           hmasslin_1JetNotBoosted[iplot]->Scale(1/hmasslin_1JetNotBoosted[iplot]->Integral()); hmasslin_1JetNotBoosted[iplot]->Write(); 
           hmasslin_1JetBoosted[iplot]->Scale(1/hmasslin_1JetBoosted[iplot]->Integral()); hmasslin_1JetBoosted[iplot]->Write(); 
           hmasslin_2Jets[iplot]->Scale(1/hmasslin_2Jets[iplot]->Integral()); hmasslin_2Jets[iplot]->Write(); 
	   
           hmasslog[iplot]->Scale(1/hmasslog[iplot]->Integral()); hmasslog[iplot]->Write(); 
           hmasslog_0Jets[iplot]->Scale(1/hmasslog_0Jets[iplot]->Integral()); hmasslog_0Jets[iplot]->Write(); 
           hmasslog_1JetNotBoosted[iplot]->Scale(1/hmasslog_1JetNotBoosted[iplot]->Integral()); hmasslog_1JetNotBoosted[iplot]->Write(); 
           hmasslog_1JetBoosted[iplot]->Scale(1/hmasslog_1JetBoosted[iplot]->Integral()); hmasslog_1JetBoosted[iplot]->Write(); 
           hmasslog_2Jets[iplot]->Scale(1/hmasslog_2Jets[iplot]->Integral()); hmasslog_2Jets[iplot]->Write(); 
	   
           hmasslin_ratio[iplot]->Scale(1/hmasslin_ratio[iplot]->Integral()); hmasslin_ratio[iplot]->Write(); 
           hmasslin_ratio_0Jets[iplot]->Scale(1/hmasslin_ratio_0Jets[iplot]->Integral()); hmasslin_ratio_0Jets[iplot]->Write(); 
           hmasslin_ratio_1JetNotBoosted[iplot]->Scale(1/hmasslin_ratio_1JetNotBoosted[iplot]->Integral()); hmasslin_ratio_1JetNotBoosted[iplot]->Write(); 
           hmasslin_ratio_1JetBoosted[iplot]->Scale(1/hmasslin_ratio_1JetBoosted[iplot]->Integral()); hmasslin_ratio_1JetBoosted[iplot]->Write(); 
           hmasslin_ratio_2Jets[iplot]->Scale(1/hmasslin_ratio_2Jets[iplot]->Integral()); hmasslin_ratio_2Jets[iplot]->Write(); 
	   
           hmasslog_ratio[iplot]->Scale(1/hmasslog_ratio[iplot]->Integral()); hmasslog_ratio[iplot]->Write(); 
           hmasslog_ratio_0Jets[iplot]->Scale(1/hmasslog_ratio_0Jets[iplot]->Integral()); hmasslog_ratio_0Jets[iplot]->Write(); 
           hmasslog_ratio_1JetNotBoosted[iplot]->Scale(1/hmasslog_ratio_1JetNotBoosted[iplot]->Integral()); hmasslog_ratio_1JetNotBoosted[iplot]->Write(); 
           hmasslog_ratio_1JetBoosted[iplot]->Scale(1/hmasslog_ratio_1JetBoosted[iplot]->Integral()); hmasslog_ratio_1JetBoosted[iplot]->Write(); 
           hmasslog_ratio_2Jets[iplot]->Scale(1/hmasslog_ratio_2Jets[iplot]->Integral()); hmasslog_ratio_2Jets[iplot]->Write(); 

	   cout<<endl;
   }

   for(size_t iplot=0; iplot<nplotToIncludeForCPU; iplot++){
	   hCPUtime_log[iplot]->Scale(1./hCPUtime_log[iplot]->Integral());
	   hCPUtime_log[iplot]->Write();
   }
   for(size_t iplot=0; iplot<nplotToIncludeForResolution; iplot++){
	   hResolutionPt[iplot]->Scale(1./hResolutionPt[iplot]->Integral());
	   hResolutionEta[iplot]->Scale(1./hResolutionEta[iplot]->Integral());
	   hResolutionPhi[iplot]->Scale(1./hResolutionPhi[iplot]->Integral());
	   hResolutionPt[iplot]->Write();
	   hResolutionEta[iplot]->Write();
	   hResolutionPhi[iplot]->Write();
   }

   
   cout<<"processed "<<nentries<< " events!!"<<endl;
}
