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
       
      if((nentries+1)%1000==0) cout << ">> processing event " << nentries << endl;
 
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
      
      hResolutionPt[0]->Fill(candVisiblePlusMET.Pt()-genDiTauPt);
      hResolutionEta[0]->Fill(candVisiblePlusMET.Eta()-genDiTauEta);
      hResolutionPhi[0]->Fill(candVisiblePlusMET.Phi()-genDiTauPhi);
      hDiTauPt->Fill(candVisible.Pt());
      hTauDPhi->Fill(dphi);

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
      hmasslin[0]->Fill(visMass); 
      hmasslin_ratio[0]->Fill(visMass/genDiTauMass);
      if(caMass_isValid){ 
	      hmass[1]->Fill(caMass); 
	      hmasslin[1]->Fill(caMass); 
	      hmasslin_ratio[1]->Fill(caMass/genDiTauMass); 
      }
      if(svfitMass_isValid){
	      hmass[2]->Fill(svfitMass);
	      hmasslin[2]->Fill(svfitMass);
	      hmasslin_ratio[2]->Fill(svfitMass/genDiTauMass);
              hCPUtime_log[0]->Fill(svfitComputingTime_cpu);
      }

      hmasslog[0]->Fill(visMass);
      hmasslog_ratio[0]->Fill(visMass/genDiTauMass);
      if(caMass_isValid){
	      hmasslog[1]->Fill(caMass);
	      hmasslog_ratio[1]->Fill(caMass/genDiTauMass);
      }
      if(svfitMass_isValid){
	      hmasslog[2]->Fill(svfitMass);     
	      hmasslog_ratio[2]->Fill(svfitMass/genDiTauMass);     
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
		      hmass[itfk+3]->Fill(vtfk[itfk]); 
		      hmasslin[itfk+3]->Fill(vtfk[itfk]); 
		      hmasslog[itfk+3]->Fill(vtfk[itfk]);
		      hmasslin_ratio[itfk+3]->Fill(vtfk[itfk]/genDiTauMass); 
		      hmasslog_ratio[itfk+3]->Fill(vtfk[itfk]/genDiTauMass);
	      }
      }
      for(size_t itfk=0; itfk<vctfk.size(); itfk++){
	      if(visctfk[itfk]==1){ 
		      hmass[itfk+12]->Fill(vctfk[itfk]); 
		      hmasslin[itfk+12]->Fill(vctfk[itfk]); 
		      hmasslog[itfk+12]->Fill(vctfk[itfk]);
		      hmasslin_ratio[itfk+12]->Fill(vctfk[itfk]/genDiTauMass); 
		      hmasslog_ratio[itfk+12]->Fill(vctfk[itfk]/genDiTauMass);
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
   hDiTauPt->Scale(1/hDiTauPt->Integral());                      hDiTauPt->Write();
   hTauDPhi->Scale(1/hTauDPhi->Integral());                      hTauDPhi->Write();

   for(size_t iplot=0; iplot<nplotToInclude; iplot++){
	   hmass[iplot]->Scale(1/hmass[iplot]->Integral()); hmass[iplot]->Write(); 
	   hmasslin[iplot]->Scale(1/hmasslin[iplot]->Integral()); hmasslin[iplot]->Write(); 
	   hmasslog[iplot]->Scale(1/hmasslog[iplot]->Integral()); hmasslog[iplot]->Write(); 
	   hmasslin_ratio[iplot]->Scale(1/hmasslin_ratio[iplot]->Integral()); hmasslin_ratio[iplot]->Write(); 
	   hmasslog_ratio[iplot]->Scale(1/hmasslog_ratio[iplot]->Integral()); hmasslog_ratio[iplot]->Write(); 
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
