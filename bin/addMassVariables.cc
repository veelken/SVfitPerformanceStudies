
/** \executable addMassVariables
 *
 * Compute Higgs mass variables in Z -> tautau and Higgs -> tautau events for SVfit performance studies.
 *
 * \author Christian Veelken, NICPB Tallinn
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "DataFormats/FWLite/interface/InputSource.h"
#include "DataFormats/FWLite/interface/OutputFiles.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "TauAnalysis/SVfitMEM/interface/SVfitMEM_lo.h"
//#include "TauAnalysis/SVfitMEM/interface/SVfitMEM_nlo.h"
#include "TauAnalysis/SVfitMEM/interface/MeasuredTauLepton.h"
#include "TauAnalysis/SVfitStandalone/interface/SVfitStandaloneAlgorithm.h"
#include "TauAnalysis/SVfitStandalone/interface/SVfitStandaloneLikelihood.h"
#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h"
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h"
#include "TauAnalysis/SVfitTF/interface/HadTauTFfromTGraph.h"
#include "TauAnalysis/SVfitTF/interface/HadTauTFCrystalBall2.h"

#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TPRegexp.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TString.h>
#include <TMatrixD.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TBenchmark.h>

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

typedef std::vector<double> vdouble;
typedef std::vector<std::string> vstring;

namespace
{
  std::string findFile(const std::string& fileName)
  {
    edm::FileInPath inputFile(fileName);
    if ( inputFile.fullPath() == "" ) {
      std::cerr << "Error: Cannot find file = " << fileName << " !!" << std::endl;
      assert(0);
    }
    return inputFile.fullPath().data();
  }

  template<typename T>
  const T* readGraph(TFile* inputFile, const std::string& graphName)
  {
    T* graph = dynamic_cast<T*>(inputFile->Get(graphName.data()));
    if ( !graph ) {
      std::cerr << "<readGraph>: Failed to load graph = " << graphName << " from file = " << inputFile->GetName() << " !!" << std::endl;
      assert(0);
    }
    return (T*)graph->Clone();
  }
  
  struct branchEntryType
  {
    std::string branchName_;
    std::string branchName_and_Type_;
    char branchType_;
    Float_t valueF_;
    Int_t valueI_;
    ULong64_t valueL_;
  };
  
  void createTDirectory_recursively(TDirectory* dir, const std::string& subdirHierarchy)
  {
    size_t pos = subdirHierarchy.find("/");
    std::string subdirName = std::string(subdirHierarchy, 0, pos);
    TDirectory* subdir = dir->mkdir(subdirName.data());
    subdir->cd();
    if ( pos != std::string::npos ) {
      std::string subdirHierarchy_remaining = std::string(subdirHierarchy, pos + 1);
      createTDirectory_recursively(subdir, subdirHierarchy_remaining);
    }
  }

  double compVisMass(reco::Candidate::PolarLorentzVector& leg1P4, 
		     reco::Candidate::PolarLorentzVector& leg2P4)
  {
    double visMass = (leg1P4 + leg2P4).mass();
    return visMass;
  }

  void compCollinearApproxMass(reco::Candidate::PolarLorentzVector& leg1P4, 
			       reco::Candidate::PolarLorentzVector& leg2P4, 
			       double mex, double mey, 
			       Float_t& caMass, Int_t& caMass_isValid)
  {
    double leg1Px = leg1P4.px();
    double leg1Py = leg1P4.py();

    double leg2Px = leg2P4.px();
    double leg2Py = leg2P4.py();

    double x1_numerator = leg1Px*leg2Py - leg2Px*leg1Py;
    double x1_denominator = leg2Py*(leg1Px + mex) - leg2Px*(leg1Py + mey);
    double x1 = ( x1_denominator != 0. ) ? x1_numerator/x1_denominator : -1.;
    
    double x2_numerator = x1_numerator;
    double x2_denominator = leg1Px*(leg2Py + mey) - leg1Py*(leg2Px + mex);
    double x2 = ( x2_denominator != 0. ) ? x2_numerator/x2_denominator : -1.;

    if ( x1 > 0. && x1 <= 1. && x2 > 0. && x2 <= 1. ) {
      reco::Candidate::PolarLorentzVector caP4 = (1./x1)*leg1P4 + (1./x2)*leg2P4;
      caMass = caP4.mass();
      caMass_isValid = 1;
    } else {
      caMass = -1.;
      caMass_isValid = 0;
    }
  }
  
  void compSVfitMass(svFitStandalone::kDecayType leg1Type, reco::Candidate::PolarLorentzVector& leg1P4, 
		     svFitStandalone::kDecayType leg2Type, reco::Candidate::PolarLorentzVector& leg2P4, 
		     double mex, double mey, const TMatrixD& metCov, 
		     Float_t& svfitPt, Float_t& svfitPtErr, Int_t& svfitPt_isValid,
		     Float_t& svfitEta, Float_t& svfitEtaErr, Int_t& svfitEta_isValid,
		     Float_t& svfitPhi, Float_t& svfitPhiErr, Int_t& svfitPhi_isValid,
		     Float_t& svfitMass, Float_t& svfitMassErr, Int_t& svfitMass_isValid,
		     Float_t& svfitTransverseMass, Float_t& svfitTransverseMassErr, Int_t& svfitTransverseMass_isValid,
		     Float_t& svfitComputingTime_cpu, Float_t& svfitComputingTime_real, 
		     int verbosity)
  {
    std::vector<svFitStandalone::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(leg1Type, leg1P4.pt(), leg1P4.eta(), leg1P4.phi(), leg1P4.mass()));
    measuredTauLeptons.push_back(svFitStandalone::MeasuredTauLepton(leg2Type, leg2P4.pt(), leg2P4.eta(), leg2P4.phi(), leg2P4.mass()));

    SVfitStandaloneAlgorithm svFitAlgo(measuredTauLeptons, mex, mey, metCov, verbosity);
    svFitAlgo.addLogM(false);
    svFitAlgo.maxObjFunctionCalls(10000);
    svFitAlgo.integrateVEGAS();
    if ( svFitAlgo.isValidSolution() ) {
      svfitPt = svFitAlgo.pt();
      svfitPtErr = svFitAlgo.ptUncert();
      svfitPt_isValid = ( svFitAlgo.ptLmax() > 0. ) ? 1 : 0;
      svfitEta = svFitAlgo.eta();
      svfitEtaErr = svFitAlgo.etaUncert();
      svfitEta_isValid = ( svFitAlgo.etaLmax() > 0. ) ? 1 : 0;
      svfitPhi = svFitAlgo.phi();
      svfitPhiErr = svFitAlgo.phiUncert();
      svfitPhi_isValid = ( svFitAlgo.phiLmax() > 0. ) ? 1 : 0;
      svfitMass = svFitAlgo.mass();
      svfitMassErr = svFitAlgo.massUncert();
      svfitMass_isValid = 1;
      svfitTransverseMass = svFitAlgo.transverseMass();
      svfitTransverseMassErr = svFitAlgo.transverseMassUncert();
      svfitTransverseMass_isValid = ( svFitAlgo.transverseMassLmax() > 0. ) ? 1 : 0;
    } else {
      svfitPt = -1.;
      svfitPtErr = -1.;
      svfitPt_isValid = 0;
      svfitEta = -1.;
      svfitEtaErr = -1.;
      svfitEta_isValid = 0;
      svfitPhi = -1.;
      svfitPhiErr = -1.;
      svfitPhi_isValid = 0;
      svfitMass = -1.;
      svfitMassErr = -1.;
      svfitMass_isValid = 0;
      svfitTransverseMass = -1.;
      svfitTransverseMassErr = -1.;
      svfitTransverseMass_isValid = 0;
    }
    svfitComputingTime_cpu = svFitAlgo.getComputingTime_cpu();
    svfitComputingTime_real = svFitAlgo.getComputingTime_real(); 
  }

  svFitMEM::MeasuredTauLepton::kDecayType getDecayTypeMEM(svFitStandalone::kDecayType type)
  {
    if      ( type == svFitStandalone::kTauToElecDecay ) return svFitMEM::MeasuredTauLepton::kTauToElecDecay;
    else if ( type == svFitStandalone::kTauToMuDecay   ) return svFitMEM::MeasuredTauLepton::kTauToMuDecay;
    else if ( type == svFitStandalone::kTauToHadDecay  ) return svFitMEM::MeasuredTauLepton::kTauToHadDecay;
    else assert(0);
  }

  classic_svFit::MeasuredTauLepton::kDecayType getDecayType_classic(svFitStandalone::kDecayType type)
  {
    if      ( type == svFitStandalone::kTauToElecDecay ) return classic_svFit::MeasuredTauLepton::kTauToElecDecay;
    else if ( type == svFitStandalone::kTauToMuDecay   ) return classic_svFit::MeasuredTauLepton::kTauToMuDecay;
    else if ( type == svFitStandalone::kTauToHadDecay  ) return classic_svFit::MeasuredTauLepton::kTauToHadDecay;
    else assert(0);
  }
  
  void compSVfitMassMEM_lo(SVfitMEM_lo& svFitAlgo, 
			   svFitMEM::MeasuredTauLepton::kDecayType leg1Type, reco::Candidate::PolarLorentzVector& leg1P4, 
			   svFitMEM::MeasuredTauLepton::kDecayType leg2Type, reco::Candidate::PolarLorentzVector& leg2P4, 
			   double mex, double mey, const TMatrixD& metCov, 
			   Float_t& svfitMass, Float_t& svfitMassErr, Int_t& svfitMass_isValid,
			   Float_t& svfitComputingTime_cpu, Float_t& svfitComputingTime_real)
  {
    //std::cout << "<compSVfitMassMEM_lo>:" << std::endl;	>:" << std::endl;	
    //std::cout << "leg1: Pt = " << leg1P4.pt() << ", eta = " << leg1P4.eta() << ", phi = " << leg1P4.phi() << ", mass = " << leg1P4.mass() << " (type = " << leg1Type << ")" << std::endl;
    //std::cout << "leg2: Pt = " << leg2P4.pt() << ", eta = " << leg2P4.eta() << ", phi = " << leg2P4.phi() << ", mass = " << leg2P4.mass() << " (type = " << leg2Type << ")" << std::endl;     
    //std::cout << "met: Px = " << mex << ", Py = " << mey << std::endl; 
    //std::cout << "metCov:" << std::endl;
    //metCov.Print();    
    std::vector<svFitMEM::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitMEM::MeasuredTauLepton(leg1Type, leg1P4.pt(), leg1P4.eta(), leg1P4.phi(), leg1P4.mass()));
    measuredTauLeptons.push_back(svFitMEM::MeasuredTauLepton(leg2Type, leg2P4.pt(), leg2P4.eta(), leg2P4.phi(), leg2P4.mass()));

    svFitAlgo.integrate(measuredTauLeptons, mex, mey, metCov);
    if ( svFitAlgo.isValidSolution() ) {
      svfitMass = svFitAlgo.mass();
      svfitMassErr = svFitAlgo.massErr();
      svfitMass_isValid = 1;
    } else {
      svfitMass = -1.;
      svfitMassErr = -1.;
      svfitMass_isValid = 0;
    }
    svfitComputingTime_cpu = svFitAlgo.getComputingTime_cpu();
    svfitComputingTime_real = svFitAlgo.getComputingTime_real(); 
  }
/*
  void compSVfitMassMEM_nlo(SVfitMEM_nlo& svFitAlgo, 
			    svFitMEM::MeasuredTauLepton::kDecayType leg1Type, reco::Candidate::PolarLorentzVector& leg1P4, 
			    svFitMEM::MeasuredTauLepton::kDecayType leg2Type, reco::Candidate::PolarLorentzVector& leg2P4, 
			    double hadRecoilPx, double hadRecoilPy, double hadRecoilPz, const TMatrixD& hadRecoilCov, 
			    Float_t& svfitMass, Float_t& svfitMassErr, Int_t& svfitMass_isValid,
			    Float_t& svfitComputingTime_cpu, Float_t& svfitComputingTime_real)
  {
    //std::cout << "<compSVfitMassMEM_nlo>:" << std::endl;	
    //std::cout << "leg1: Pt = " << leg1P4.pt() << ", eta = " << leg1P4.eta() << ", phi = " << leg1P4.phi() << ", mass = " << leg1P4.mass() << " (type = " << leg1Type << ")" << std::endl;
    //std::cout << "leg2: Pt = " << leg2P4.pt() << ", eta = " << leg2P4.eta() << ", phi = " << leg2P4.phi() << ", mass = " << leg2P4.mass() << " (type = " << leg2Type << ")" << std::endl;     
    //std::cout << "met: Px = " << mex << ", Py = " << mey << std::endl; 
    //std::cout << "metCov:" << std::endl;
    //metCov.Print();    
    std::vector<svFitMEM::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(svFitMEM::MeasuredTauLepton(leg1Type, leg1P4.pt(), leg1P4.eta(), leg1P4.phi(), leg1P4.mass()));
    measuredTauLeptons.push_back(svFitMEM::MeasuredTauLepton(leg2Type, leg2P4.pt(), leg2P4.eta(), leg2P4.phi(), leg2P4.mass()));

    svFitAlgo.integrate(measuredTauLeptons, hadRecoilPx, hadRecoilPy, hadRecoilPz, hadRecoilCov);
    if ( svFitAlgo.isValidSolution() ) {
      svfitMass = svFitAlgo.mass();
      svfitMassErr = svFitAlgo.massErr();
      svfitMass_isValid = 1;
    } else {
      svfitMass = -1.;
      svfitMassErr = -1.;
      svfitMass_isValid = 0;
    }
    svfitComputingTime_cpu = svFitAlgo.getComputingTime_cpu();
    svfitComputingTime_real = svFitAlgo.getComputingTime_real(); 
  }
 */
  void compClassicSVfitMass(ClassicSVfit& svFitAlgo,
			    classic_svFit::MeasuredTauLepton::kDecayType leg1Type, reco::Candidate::PolarLorentzVector& leg1P4, 
			    classic_svFit::MeasuredTauLepton::kDecayType leg2Type, reco::Candidate::PolarLorentzVector& leg2P4, 
			    double mex, double mey, const TMatrixD& metCov, 
			    Float_t& svfitPt, Float_t& svfitPtErr, Int_t& svfitPt_isValid,
			    Float_t& svfitEta, Float_t& svfitEtaErr, Int_t& svfitEta_isValid,
			    Float_t& svfitPhi, Float_t& svfitPhiErr, Int_t& svfitPhi_isValid,
			    Float_t& svfitMass, Float_t& svfitMassErr, Int_t& svfitMass_isValid, 			    
			    Float_t& svfitTransverseMass, Float_t& svfitTransverseMassErr, Int_t& svfitTransverseMass_isValid, 
			    Float_t& svfitComputingTime_cpu, Float_t& svfitComputingTime_real)
  {
    //std::cout << "<compClassicSVfitMass)>:" << std::endl;	
    //std::cout << "leg1: Pt = " << leg1P4.pt() << ", eta = " << leg1P4.eta() << ", phi = " << leg1P4.phi() << ", mass = " << leg1P4.mass() << " (type = " << leg1Type << ")" << std::endl;
    //std::cout << "leg2: Pt = " << leg2P4.pt() << ", eta = " << leg2P4.eta() << ", phi = " << leg2P4.phi() << ", mass = " << leg2P4.mass() << " (type = " << leg2Type << ")" << std::endl;     
    //std::cout << "met: Px = " << mex << ", Py = " << mey << std::endl; 
    //std::cout << "metCov:" << std::endl;
    //metCov.Print();    
    std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons;
    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(leg1Type, leg1P4.pt(), leg1P4.eta(), leg1P4.phi(), leg1P4.mass()));
    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(leg2Type, leg2P4.pt(), leg2P4.eta(), leg2P4.phi(), leg2P4.mass()));

    svFitAlgo.integrate(measuredTauLeptons, mex, mey, metCov);
    if ( svFitAlgo.isValidSolution() ) {
      svfitPt = svFitAlgo.pt();
      svfitPtErr = svFitAlgo.ptErr();
      svfitPt_isValid = ( svFitAlgo.ptLmax() > 0. ) ? 1 : 0;
      svfitEta = svFitAlgo.eta();
      svfitEtaErr = svFitAlgo.etaErr();
      svfitEta_isValid = ( svFitAlgo.etaLmax() > 0. ) ? 1 : 0;
      svfitPhi = svFitAlgo.phi();
      svfitPhiErr = svFitAlgo.phiErr();
      svfitPhi_isValid = ( svFitAlgo.phiLmax() > 0. ) ? 1 : 0;
      svfitMass = svFitAlgo.mass();
      svfitMassErr = svFitAlgo.massErr();
      svfitMass_isValid = 1;
      svfitTransverseMass = svFitAlgo.transverseMass();
      svfitTransverseMassErr = svFitAlgo.transverseMassErr();
      svfitTransverseMass_isValid = ( svFitAlgo.transverseMassLmax() > 0. ) ? 1 : 0;
    } else {
      svfitPt = -1.;
      svfitPtErr = -1.;
      svfitPt_isValid = 0;
      svfitEta = -1.;
      svfitEtaErr = -1.;
      svfitEta_isValid = 0;
      svfitPhi = -1.;
      svfitPhiErr = -1.;
      svfitPhi_isValid = 0;
      svfitMass = -1.;
      svfitMassErr = -1.;
      svfitMass_isValid = 0;
      svfitTransverseMass = -1.;
      svfitTransverseMassErr = -1.;
      svfitTransverseMass_isValid = 0;
    }
    svfitComputingTime_cpu = svFitAlgo.getComputingTime_cpu();
    svfitComputingTime_real = svFitAlgo.getComputingTime_real(); 
  }

  struct svFitMEM_logM_EntryType
  {
    enum { kLO, kNLO };
    int lo_or_nlo_;
    double addLogM_power_;
    bool useHadTauTF_;
    Float_t svfitMass_;
    Float_t svfitMassErr_;
    Int_t svfitMass_isValid_;
    Float_t svfitComputingTime_cpu_;
    Float_t svfitComputingTime_real_;
  };

  struct classicSVfit_logM_EntryType
  {
    double addLogM_power_;
    bool useHadTauTF_;
    Float_t svfitPt_;
    Float_t svfitPtErr_;
    Int_t svfitPt_isValid_;
    Float_t svfitEta_;
    Float_t svfitEtaErr_;
    Int_t svfitEta_isValid_;
    Float_t svfitPhi_;
    Float_t svfitPhiErr_;
    Int_t svfitPhi_isValid_;
    Float_t svfitMass_;
    Float_t svfitMassErr_;
    Int_t svfitMass_isValid_;
    Float_t svfitTransverseMass_;
    Float_t svfitTransverseMassErr_;
    Int_t svfitTransverseMass_isValid_;
    Float_t svfitComputingTime_cpu_;
    Float_t svfitComputingTime_real_;
  };

  double square(double x)
  {
    return x*x;
  }

  double compMt2(const reco::Candidate::PolarLorentzVector& leg1P4, const reco::Candidate::PolarLorentzVector& leg2P4)
  {
    double mt2 = square(leg1P4.Et() + leg2P4.Et()) - (square(leg1P4.px() + leg2P4.px()) + square(leg1P4.py() + leg2P4.py()));
    // CV: protection against rounding errors
    if ( mt2 < 0. ) mt2 = 0.; 
    return mt2;
  }
}

int main(int argc, char* argv[]) 
{
//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }

  std::cout << "<addMassVariables>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("addMassVariables");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") ) 
    throw cms::Exception("addMassVariables") 
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfgAddMassVariables = cfg.getParameter<edm::ParameterSet>("addMassVariables");
  
  std::string inputTreeName = cfgAddMassVariables.getParameter<std::string>("inputTreeName");
  std::string outputTreeName = cfgAddMassVariables.getParameter<std::string>("outputTreeName");

  std::string leg1BranchName = cfgAddMassVariables.getParameter<std::string>("leg1BranchName");
  svFitStandalone::kDecayType leg1Type = svFitStandalone::kUndefinedDecayType;
  if      ( leg1BranchName.find("Electron") != std::string::npos ) leg1Type = svFitStandalone::kTauToElecDecay;
  else if ( leg1BranchName.find("Muon") != std::string::npos     ) leg1Type = svFitStandalone::kTauToMuDecay;
  else if ( leg1BranchName.find("HadTau") != std::string::npos   ) leg1Type = svFitStandalone::kTauToHadDecay;
  else throw cms::Exception("addMassVariables") 
    << "Invalid Configuration parameter 'leg1BranchName' = " << leg1BranchName << " !!\n";
  svFitMEM::MeasuredTauLepton::kDecayType leg1TypeMEM = getDecayTypeMEM(leg1Type);
  double leg1minPt = cfgAddMassVariables.getParameter<double>("leg1minPt");
  double leg1maxAbsEta = cfgAddMassVariables.getParameter<double>("leg1maxAbsEta");

  std::string leg2BranchName = cfgAddMassVariables.getParameter<std::string>("leg2BranchName");
  svFitStandalone::kDecayType leg2Type = svFitStandalone::kUndefinedDecayType;
  if      ( leg2BranchName.find("Electron") != std::string::npos ) leg2Type = svFitStandalone::kTauToElecDecay;
  else if ( leg2BranchName.find("Muon") != std::string::npos     ) leg2Type = svFitStandalone::kTauToMuDecay;
  else if ( leg2BranchName.find("HadTau") != std::string::npos   ) leg2Type = svFitStandalone::kTauToHadDecay;
  else throw cms::Exception("addMassVariables") 
    << "Invalid Configuration parameter 'leg2BranchName' = " << leg2BranchName << " !!\n";
  svFitMEM::MeasuredTauLepton::kDecayType leg2TypeMEM = getDecayTypeMEM(leg2Type);
  double leg2minPt = cfgAddMassVariables.getParameter<double>("leg2minPt");
  double leg2maxAbsEta = cfgAddMassVariables.getParameter<double>("leg2maxAbsEta");

  std::string metBranchName = cfgAddMassVariables.getParameter<std::string>("metBranchName");
  std::string hadRecoilBranchName = cfgAddMassVariables.getParameter<std::string>("hadRecoilBranchName");

  //START ADDING
  std::string genJet1BranchName = cfgAddMassVariables.getParameter<std::string>("genJet1BranchName");
  std::string genJet2BranchName = cfgAddMassVariables.getParameter<std::string>("genJet2BranchName");
  std::string genJet3BranchName = cfgAddMassVariables.getParameter<std::string>("genJet3BranchName");
  std::string genJet4BranchName = cfgAddMassVariables.getParameter<std::string>("genJet4BranchName");
  std::string genJet5BranchName = cfgAddMassVariables.getParameter<std::string>("genJet5BranchName");
  std::string genJet6BranchName = cfgAddMassVariables.getParameter<std::string>("genJet6BranchName");
  enum {kInclusive, k0Jets, k1JetBoosted, k1JetNotBoosted, k2Jets};
  std::string eventSelection = cfgAddMassVariables.getParameter<std::string>("eventSelection");
  int eventSelection_categorization = -1;
  if      (eventSelection == "inclusive"      ) eventSelection_categorization = kInclusive;
  else if (eventSelection == "0Jets"          ) eventSelection_categorization = k0Jets;
  else if (eventSelection == "1JetBoosted"    ) eventSelection_categorization = k1JetBoosted;
  else if (eventSelection == "1JetNotBoosted" ) eventSelection_categorization = k1JetNotBoosted;
  else if (eventSelection == "2Jets"          ) eventSelection_categorization = k2Jets;
  else throw cms::Exception("addMassVariables") 
    << "Invalid Configuration parameter 'eventSelection' = " << eventSelection << " !!\n";
  //FINISH ADDING

  edm::ParameterSet cfgSVfitMEM = cfgAddMassVariables.getParameter<edm::ParameterSet>("svFitMEM");
  double svFitMEM_sqrtS = cfgSVfitMEM.getParameter<double>("sqrtS");
  std::string svFitMEM_apply_xSection_times_AccCorr_string = cfgSVfitMEM.getParameter<std::string>("apply_xSection_times_AccCorr");
  enum { kNone, kXS, kXS_times_Acc };
  int svFitMEM_apply_xSection_times_AccCorr = -1;
  if      ( svFitMEM_apply_xSection_times_AccCorr_string == "none"               ) svFitMEM_apply_xSection_times_AccCorr = kNone;
  else if ( svFitMEM_apply_xSection_times_AccCorr_string == "xSection"           ) svFitMEM_apply_xSection_times_AccCorr = kXS;
  else if ( svFitMEM_apply_xSection_times_AccCorr_string == "xSection_times_Acc" ) svFitMEM_apply_xSection_times_AccCorr = kXS_times_Acc;
  else throw cms::Exception("addMassVariables") 
    << "Invalid Configuration parameter 'apply_xSection_times_AccCorr' = " << svFitMEM_apply_xSection_times_AccCorr_string << " !!\n";
  const TGraphErrors* svFitMEM_graph_xSection_lo = 0;
  const TGraphErrors* svFitMEM_graph_Acc_lo = 0;
  const TGraphErrors* svFitMEM_graph_xSection_nlo = 0;
  const TGraphErrors* svFitMEM_graph_Acc_nlo = 0;
  if ( svFitMEM_apply_xSection_times_AccCorr == kXS || svFitMEM_apply_xSection_times_AccCorr == kXS_times_Acc ) {
    std::string inputFileName_xSection_times_AccCorr_lo = cfgSVfitMEM.getParameter<std::string>("inputFileName_xSection_times_AccCorr_lo");
    TFile* inputFile_xSection_times_AccCorr_lo = new TFile(findFile(inputFileName_xSection_times_AccCorr_lo).data());
    std::string graphName_xSection_lo = cfgSVfitMEM.getParameter<std::string>("graphName_xSection_lo");
    svFitMEM_graph_xSection_lo = readGraph<TGraphErrors>(inputFile_xSection_times_AccCorr_lo, graphName_xSection_lo);
    std::string graphName_Acc_lo = cfgSVfitMEM.getParameter<std::string>("graphName_Acc_lo");
    if ( svFitMEM_apply_xSection_times_AccCorr == kXS_times_Acc ) {
      svFitMEM_graph_Acc_lo = readGraph<TGraphErrors>(inputFile_xSection_times_AccCorr_lo, graphName_Acc_lo);
    }
    delete inputFile_xSection_times_AccCorr_lo;
/*
    std::string inputFileName_xSection_times_AccCorr_nlo = cfgSVfitMEM.getParameter<std::string>("inputFileName_xSection_times_AccCorr_nlo");
    TFile* inputFile_xSection_times_AccCorr_nlo = new TFile(findFile(inputFileName_xSection_times_AccCorr_nlo).data());
    std::string graphName_xSection_nlo = cfgSVfitMEM.getParameter<std::string>("graphName_xSection_nlo");
    svFitMEM_graph_xSection_nlo = readGraph<TGraphErrors>(inputFile_xSection_times_AccCorr_nlo, graphName_xSection_nlo);
    std::string graphName_Acc_nlo = cfgSVfitMEM.getParameter<std::string>("graphName_Acc_nlo");
    if ( svFitMEM_apply_xSection_times_AccCorr == kXS_times_Acc ) {
      svFitMEM_graph_Acc_nlo = readGraph<TGraphErrors>(inputFile_xSection_times_AccCorr_nlo, graphName_Acc_nlo);
    }
    delete inputFile_xSection_times_AccCorr_nlo;
 */
  }
  //double svFitMEM_minAcc = cfgSVfitMEM.getParameter<double>("minAcc");
  vdouble svFitMEM_addLogM_powers = cfgSVfitMEM.getParameter<vdouble>("addLogM_powers");
  std::string inputFileName_hadTauTF = cfgSVfitMEM.getParameter<std::string>("inputFileName_hadTauTF");
  TFile* inputFile_hadTauTF = new TFile(findFile(inputFileName_hadTauTF).data());
  std::string graphName_hadTauTF = cfgSVfitMEM.getParameter<std::string>("graphName_hadTauTF");
  const TGraph* svFitMEM_graph_hadTauTF = readGraph<TGraph>(inputFile_hadTauTF, graphName_hadTauTF);
  delete inputFile_hadTauTF;
  std::string svFitMEM_intMode_string = cfgSVfitMEM.getParameter<std::string>("intMode");
  int svFitMEM_intMode = 1;
  if      ( svFitMEM_intMode_string == "vamp"  ) svFitMEM_intMode = SVfitMEM_lo::kVAMP;
  else if ( svFitMEM_intMode_string == "vegas" ) svFitMEM_intMode = SVfitMEM_lo::kVEGAS;
  else throw cms::Exception("addMassVariables") 
    << "Invalid Configuration parameter 'intMode' = " << svFitMEM_intMode_string << " !!\n";
  unsigned svFitMEM_maxObjFunctionCalls = cfgSVfitMEM.getParameter<unsigned>("maxObjFunctionCalls");
  int svFitMEM_verbosity = cfgSVfitMEM.getParameter<int>("verbosity");

  bool keepAllBranches = cfgAddMassVariables.getParameter<bool>("keepAllBranches");

  int verbosity = cfgAddMassVariables.getParameter<int>("verbosity");

  fwlite::InputSource inputFiles(cfg); 
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  int skipEvents = cfg.getParameter<edm::ParameterSet>("fwliteInput").getParameter<unsigned>("skipEvents");
  std::cout << " skipEvents = " << skipEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  std::string outputFileName = cfgAddMassVariables.getParameter<std::string>("outputFileName");
  std::cout << " outputFileName = " << outputFileName << std::endl;

  TChain* inputTree = new TChain(inputTreeName.data());
  for ( vstring::const_iterator inputFileName = inputFiles.files().begin();
	inputFileName != inputFiles.files().end(); ++inputFileName ) {
    std::cout << "input Tree: adding file = " << (*inputFileName) << std::endl;
    inputTree->AddFile(inputFileName->data());
  }
  
  if ( !(inputTree->GetListOfFiles()->GetEntries() >= 1) ) {
    throw cms::Exception("addMassVariables") 
      << "Failed to identify input Tree !!\n";
  }

  std::cout << "input Tree contains " << inputTree->GetEntries() << " Entries in " << inputTree->GetListOfFiles()->GetEntries() << " files." << std::endl;

  // CV: need to call TChain::LoadTree before processing first event 
  //     in order to prevent ROOT causing a segmentation violation,
  //     cf. http://root.cern.ch/phpBB3/viewtopic.php?t=10062
  inputTree->LoadTree(0);

  vstring branchesToKeep_expressions;
  if ( keepAllBranches ) {
    TObjArray* branches = inputTree->GetListOfBranches();
    int numBranches = branches->GetEntries();
    for ( int iBranch = 0; iBranch < numBranches; ++iBranch ) {
      TBranch* branch = dynamic_cast<TBranch*>(branches->At(iBranch));
      assert(branch);
      std::string branchName = branch->GetName();
      branchesToKeep_expressions.push_back(branchName);
    }
  }

  std::string outputTreeName_base = outputTreeName;
  std::string outputDirName = "";
  if ( outputTreeName.find_last_of("/") != std::string::npos ) {
    size_t pos = outputTreeName.find_last_of("/");
    outputTreeName_base = std::string(outputTreeName, pos + 1);
    outputDirName = std::string(outputTreeName, 0, pos);
  } 
  TTree* outputTree = new TTree(outputTreeName_base.data(), outputTreeName_base.data());

  std::vector<branchEntryType*> branchesToKeep;

  TObjArray* branches = inputTree->GetListOfBranches();

  int numBranches = branches->GetEntries();
  for ( int iBranch = 0; iBranch < numBranches; ++iBranch ) {
    const TBranch* branch = dynamic_cast<const TBranch*>(branches->At(iBranch));
    assert(branch);

    bool isBranchToKeep = false;
    for ( std::vector<std::string>::const_iterator branchToKeep = branchesToKeep_expressions.begin();
	  branchToKeep != branchesToKeep_expressions.end(); ++branchToKeep ) {
      if ( (*branchToKeep) == "" ) continue;     
      if ( branchToKeep->find(branch->GetName()) != std::string::npos ) {
	std::string branchToKeep_substring(*branchToKeep, branchToKeep->find(branch->GetName()));
	std::string pattern = std::string(branch->GetName()).append("[a-zA-Z0-9]+").append(".*");
	TPRegexp regexp(pattern.data());
	if ( regexp.Match(branchToKeep_substring.data()) == 0 ) {
	  isBranchToKeep = true;
	  break;
	}
      }
    } 

    if ( isBranchToKeep ) {
      branchEntryType* branchEntry = new branchEntryType();
      branchEntry->branchName_ = branch->GetName();
      branchEntry->branchName_and_Type_ = branch->GetTitle();      
      int idx = branchEntry->branchName_and_Type_.find_last_of("/");
      if ( idx == ((int)branchEntry->branchName_and_Type_.length() - 2) ) {
	branchEntry->branchType_ = branchEntry->branchName_and_Type_[idx + 1];
	if ( branchEntry->branchType_ == 'F' ) {
	  inputTree->SetBranchAddress(branchEntry->branchName_.data(), &branchEntry->valueF_);
	  outputTree->Branch(branchEntry->branchName_.data(), &branchEntry->valueF_, branchEntry->branchName_and_Type_.data());
	} else if ( branchEntry->branchType_ == 'I' ) {
	  inputTree->SetBranchAddress(branchEntry->branchName_.data(), &branchEntry->valueI_);
	  outputTree->Branch(branchEntry->branchName_.data(), &branchEntry->valueI_, branchEntry->branchName_and_Type_.data());
	} else if ( branchEntry->branchType_ == 'l' ) {
	  inputTree->SetBranchAddress(branchEntry->branchName_.data(), &branchEntry->valueL_);
	  outputTree->Branch(branchEntry->branchName_.data(), &branchEntry->valueL_, branchEntry->branchName_and_Type_.data());
        } else {
	  throw cms::Exception("addMassVariables") 
	    << "Branch = " << branchEntry->branchName_ << " is of unsupported Type = " << branchEntry->branchName_and_Type_ << " !!\n";
	}
      }
      branchesToKeep.push_back(branchEntry);
    }
  }

  //std::cout << "keeping branches:" << std::endl;
  //for ( std::vector<branchEntryType*>::const_iterator branchEntry = branchesToKeep.begin();
  //	  branchEntry != branchesToKeep.end(); ++branchEntry ) {
  //  std::cout << " " << (*branchEntry)->branchName_ << " (type = " << (*branchEntry)->branchType_ << ")" << std::endl;
  //}

  std::cout << "adding branches:" << std::endl;
  // mass of visible tau decay products
  Float_t visMass = -1.;
  std::cout << " visMass (type = F)" << std::endl;
  outputTree->Branch("visMass", &visMass, "visMass/F");
  
  // mTauTau reconstructed using collinear approximation method
  Float_t caMass = -1.;
  std::cout << " caMass (type = F)" << std::endl;
  outputTree->Branch("caMass", &caMass, "caMass/F");
  Int_t caMass_isValid = 0;
  std::cout << " caMass_isValid (type = I)" << std::endl;
  outputTree->Branch("caMass_isValid", &caMass_isValid, "caMass_isValid/I");

  // mTtotal variable used by ATLAS MSSM Higgs->tautau analysis,
  // cf. https://cds.cern.ch/record/1744694/files/ATLAS-CONF-2014-049.pdf
  Float_t mTtotal = -1.;
  std::cout << " mTtotal (type = F)" << std::endl;
  outputTree->Branch("mTtotal", &mTtotal, "mTtotal/F");

  // mTauTau reconstructed by "old" SVfit
  Float_t svfitPt = -1.;
  std::cout << " svfitPt (type = F)" << std::endl;
  outputTree->Branch("svfitPt", &svfitPt, "svfitPt/F");
  Float_t svfitPtErr = -1.;
  std::cout << " svfitPtErr (type = F)" << std::endl;
  outputTree->Branch("svfitPtErr", &svfitPtErr, "svfitPtErr/F");
  Int_t svfitPt_isValid = 0;
  std::cout << " svfitPt_isValid (type = I)" << std::endl;
  outputTree->Branch("svfitPt_isValid", &svfitPt_isValid, "svfitPt_isValid/I");
  Float_t svfitEta = -1.;
  std::cout << " svfitEta (type = F)" << std::endl;
  outputTree->Branch("svfitEta", &svfitEta, "svfitEta/F");
  Float_t svfitEtaErr = -1.;
  std::cout << " svfitEtaErr (type = F)" << std::endl;
  outputTree->Branch("svfitEtaErr", &svfitEtaErr, "svfitEtaErr/F");
  Int_t svfitEta_isValid = 0;
  std::cout << " svfitEta_isValid (type = I)" << std::endl;
  outputTree->Branch("svfitEta_isValid", &svfitEta_isValid, "svfitEta_isValid/I");
  Float_t svfitPhi = -1.;
  std::cout << " svfitPhi (type = F)" << std::endl;
  outputTree->Branch("svfitPhi", &svfitPhi, "svfitPhi/F");
  Float_t svfitPhiErr = -1.;
  std::cout << " svfitPhiErr (type = F)" << std::endl;
  outputTree->Branch("svfitPhiErr", &svfitPhiErr, "svfitPhiErr/F");
  Int_t svfitPhi_isValid = 0;
  std::cout << " svfitPhi_isValid (type = I)" << std::endl;
  outputTree->Branch("svfitPhi_isValid", &svfitPhi_isValid, "svfitPhi_isValid/I");
  Float_t svfitMass = -1.;
  std::cout << " svfitMass (type = F)" << std::endl;
  outputTree->Branch("svfitMass", &svfitMass, "svfitMass/F");
  Float_t svfitMassErr = -1.;
  std::cout << " svfitMassErr (type = F)" << std::endl;
  outputTree->Branch("svfitMassErr", &svfitMassErr, "svfitMassErr/F");
  Int_t svfitMass_isValid = 0;
  std::cout << " svfitMass_isValid (type = I)" << std::endl;
  outputTree->Branch("svfitMass_isValid", &svfitMass_isValid, "svfitMass_isValid/I");
  Float_t svfitTransverseMass = -1.;
  std::cout << " svfitTransverseMass (type = F)" << std::endl;
  outputTree->Branch("svfitTransverseMass", &svfitTransverseMass, "svfitTransverseMass/F");
  Float_t svfitTransverseMassErr = -1.;
  std::cout << " svfitTransverseMassErr (type = F)" << std::endl;
  outputTree->Branch("svfitTransverseMassErr", &svfitTransverseMassErr, "svfitTransverseMassErr/F");
  Int_t svfitTransverseMass_isValid = 0;
  std::cout << " svfitTransverseMass_isValid (type = I)" << std::endl;
  outputTree->Branch("svfitTransverseMass_isValid", &svfitTransverseMass_isValid, "svfitTransverseMass_isValid/I");
  Float_t svfitComputingTime_cpu;
  std::cout << " svfitComputingTime_cpu (type = F)" << std::endl;
  outputTree->Branch("svfitComputingTime_cpu", &svfitComputingTime_cpu, "svfitComputingTime_cpu/F");
  Float_t svfitComputingTime_real;
  std::cout << " svfitComputingTime_real (type = F)" << std::endl;
  outputTree->Branch("svfitComputingTime_real", &svfitComputingTime_real, "svfitComputingTime_real/F");

  // mTauTau reconstructed by SVfitMEM 
  std::vector<svFitMEM_logM_EntryType*> svFitMEM_logM_entries;
  //for ( int lo_or_nlo = svFitMEM_logM_EntryType::kLO; lo_or_nlo <= svFitMEM_logM_EntryType::kNLO; ++lo_or_nlo ) {
  for ( int lo_or_nlo = svFitMEM_logM_EntryType::kLO; lo_or_nlo <= svFitMEM_logM_EntryType::kLO; ++lo_or_nlo ) {
    for ( vdouble::const_iterator svFitMEM_addLogM_power = svFitMEM_addLogM_powers.begin();
	  svFitMEM_addLogM_power != svFitMEM_addLogM_powers.end(); ++svFitMEM_addLogM_power ) {
      enum { kEnableHadTauTF, kDisableHadTauTF };
      for ( int optHadTauTF = kEnableHadTauTF; optHadTauTF <= kDisableHadTauTF; ++optHadTauTF ) {
	svFitMEM_logM_EntryType* svFitMEM_logM_entry = new svFitMEM_logM_EntryType();
	svFitMEM_logM_entry->lo_or_nlo_ = lo_or_nlo;
	std::string optLO_or_NLO_string;
        if ( lo_or_nlo == svFitMEM_logM_EntryType::kLO ) {
  	  optLO_or_NLO_string = "lo";
	//} else if ( lo_or_nlo == svFitMEM_logM_EntryType::kNLO ) {
	//  optLO_or_NLO_string = "nlo";
	} else assert(0);
	svFitMEM_logM_entry->addLogM_power_ = (*svFitMEM_addLogM_power);
        std::string optHadTauTF_string;
        if ( optHadTauTF == kEnableHadTauTF ) {
	  svFitMEM_logM_entry->useHadTauTF_ = true;
  	  optHadTauTF_string = "wHadTauTF";
        } else {
	  svFitMEM_logM_entry->useHadTauTF_ = false;
	  optHadTauTF_string = "woHadTauTF";
        }
	int addLogM_power_int = TMath::Nint(*svFitMEM_addLogM_power);
	std::string branchName_svfitMass = Form("svfitMassMEM%s%ilogM%s", optLO_or_NLO_string.data(), addLogM_power_int, optHadTauTF_string.data());
	std::cout << " " << branchName_svfitMass << " (type = F)" << std::endl;
	outputTree->Branch(branchName_svfitMass.data(), &svFitMEM_logM_entry->svfitMass_, Form("%s/F", branchName_svfitMass.data()));
	std::string branchName_svfitMassErr = Form("svfitMassErrMEM%s%ilogM%s", optLO_or_NLO_string.data(), addLogM_power_int, optHadTauTF_string.data());
	std::cout << " " << branchName_svfitMassErr << " (type = F)" << std::endl;
	outputTree->Branch(branchName_svfitMassErr.data(), &svFitMEM_logM_entry->svfitMassErr_, Form("%s/F", branchName_svfitMassErr.data()));
	std::string branchName_svfitMass_isValid = Form("svfitMass_isValidMEM%s%ilogM%s", optLO_or_NLO_string.data(), addLogM_power_int, optHadTauTF_string.data());
	std::cout << " " << branchName_svfitMass_isValid << " (type = I)" << std::endl;
	outputTree->Branch(branchName_svfitMass_isValid.data(), &svFitMEM_logM_entry->svfitMass_isValid_, Form("%s/I", branchName_svfitMass_isValid.data()));
	std::string branchName_svfitComputingTime_cpu = Form("svfitComputingTime_cpuMEM%s%ilogM%s", optLO_or_NLO_string.data(), addLogM_power_int, optHadTauTF_string.data());
	std::cout << " " << branchName_svfitComputingTime_cpu << " (type = F)" << std::endl;
	outputTree->Branch(branchName_svfitComputingTime_cpu.data(), &svFitMEM_logM_entry->svfitComputingTime_cpu_, Form("%s/F", branchName_svfitComputingTime_cpu.data()));
	std::string branchName_svfitComputingTime_real = Form("svfitComputingTime_realMEM%s%ilogM%s", optLO_or_NLO_string.data(), addLogM_power_int, optHadTauTF_string.data());
	std::cout << " " << branchName_svfitComputingTime_real << " (type = F)" << std::endl;
	outputTree->Branch(branchName_svfitComputingTime_real.data(), &svFitMEM_logM_entry->svfitComputingTime_real_, Form("%s/F", branchName_svfitComputingTime_real.data()));
	svFitMEM_logM_entries.push_back(svFitMEM_logM_entry);
      }
    }
  }
  
  // mTauTau reconstructed by ClassicSVfit
  std::vector<classicSVfit_logM_EntryType*> classicSVfit_logM_entries;
  for ( vdouble::const_iterator svFitMEM_addLogM_power = svFitMEM_addLogM_powers.begin();
	svFitMEM_addLogM_power != svFitMEM_addLogM_powers.end(); ++svFitMEM_addLogM_power ) {
    enum { kEnableHadTauTF, kDisableHadTauTF };
    for ( int optHadTauTF = kEnableHadTauTF; optHadTauTF <= kDisableHadTauTF; ++optHadTauTF ) {
      classicSVfit_logM_EntryType* classicSVfit_logM_entry = new classicSVfit_logM_EntryType();
      classicSVfit_logM_entry->addLogM_power_ = (*svFitMEM_addLogM_power);
      std::string optHadTauTF_string;
      if ( optHadTauTF == kEnableHadTauTF ) {
	classicSVfit_logM_entry->useHadTauTF_ = true;
	optHadTauTF_string = "wHadTauTF";
      } else {
	classicSVfit_logM_entry->useHadTauTF_ = false;
	optHadTauTF_string = "woHadTauTF";
      }
      int addLogM_power_int = TMath::Nint(*svFitMEM_addLogM_power);
      std::string branchName_svfitPt = Form("classicSVfitPt%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitPt << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitPt.data(), &classicSVfit_logM_entry->svfitPt_, Form("%s/F", branchName_svfitPt.data()));
      std::string branchName_svfitPtErr = Form("classicSVfitPtErr%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitPtErr << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitPtErr.data(), &classicSVfit_logM_entry->svfitPtErr_, Form("%s/F", branchName_svfitPtErr.data()));
      std::string branchName_svfitPt_isValid = Form("classicSVfitPt_isValid%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitPt_isValid << " (type = I)" << std::endl;
      outputTree->Branch(branchName_svfitPt_isValid.data(), &classicSVfit_logM_entry->svfitPt_isValid_, Form("%s/I", branchName_svfitPt_isValid.data()));
      std::string branchName_svfitEta = Form("classicSVfitEta%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitEta << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitEta.data(), &classicSVfit_logM_entry->svfitEta_, Form("%s/F", branchName_svfitEta.data()));
      std::string branchName_svfitEtaErr = Form("classicSVfitEtaErr%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitEtaErr << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitEtaErr.data(), &classicSVfit_logM_entry->svfitEtaErr_, Form("%s/F", branchName_svfitEtaErr.data()));
      std::string branchName_svfitEta_isValid = Form("classicSVfitEta_isValid%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitEta_isValid << " (type = I)" << std::endl;
      outputTree->Branch(branchName_svfitEta_isValid.data(), &classicSVfit_logM_entry->svfitEta_isValid_, Form("%s/I", branchName_svfitEta_isValid.data()));
      std::string branchName_svfitPhi = Form("classicSVfitPhi%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitPhi << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitPhi.data(), &classicSVfit_logM_entry->svfitPhi_, Form("%s/F", branchName_svfitPhi.data()));
      std::string branchName_svfitPhiErr = Form("classicSVfitPhiErr%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitPhiErr << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitPhiErr.data(), &classicSVfit_logM_entry->svfitPhiErr_, Form("%s/F", branchName_svfitPhiErr.data()));
      std::string branchName_svfitPhi_isValid = Form("classicSVfitPhi_isValid%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitPhi_isValid << " (type = I)" << std::endl;
      outputTree->Branch(branchName_svfitPhi_isValid.data(), &classicSVfit_logM_entry->svfitPhi_isValid_, Form("%s/I", branchName_svfitPhi_isValid.data()));
      std::string branchName_svfitMass = Form("classicSVfitMass%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitMass << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitMass.data(), &classicSVfit_logM_entry->svfitMass_, Form("%s/F", branchName_svfitMass.data()));
      std::string branchName_svfitMassErr = Form("classicSVfitMassErr%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitMassErr << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitMassErr.data(), &classicSVfit_logM_entry->svfitMassErr_, Form("%s/F", branchName_svfitMassErr.data()));
      std::string branchName_svfitMass_isValid = Form("classicSVfitMass_isValid%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitMass_isValid << " (type = I)" << std::endl;
      outputTree->Branch(branchName_svfitMass_isValid.data(), &classicSVfit_logM_entry->svfitMass_isValid_, Form("%s/I", branchName_svfitMass_isValid.data()));
      std::string branchName_svfitTransverseMass = Form("classicSVfitTransverseMass%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitTransverseMass << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitTransverseMass.data(), &classicSVfit_logM_entry->svfitTransverseMass_, Form("%s/F", branchName_svfitTransverseMass.data()));
      std::string branchName_svfitTransverseMassErr = Form("classicSVfitTransverseMassErr%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitTransverseMassErr << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitTransverseMassErr.data(), &classicSVfit_logM_entry->svfitTransverseMassErr_, Form("%s/F", branchName_svfitTransverseMassErr.data()));
      std::string branchName_svfitTransverseMass_isValid = Form("classicSVfitTransverseMass_isValid%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitTransverseMass_isValid << " (type = I)" << std::endl;
      outputTree->Branch(branchName_svfitTransverseMass_isValid.data(), &classicSVfit_logM_entry->svfitTransverseMass_isValid_, Form("%s/I", branchName_svfitTransverseMass_isValid.data()));
      std::string branchName_svfitComputingTime_cpu = Form("classicSVfitComputingTime_cpu%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitComputingTime_cpu << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitComputingTime_cpu.data(), &classicSVfit_logM_entry->svfitComputingTime_cpu_, Form("%s/F", branchName_svfitComputingTime_cpu.data()));
      std::string branchName_svfitComputingTime_real = Form("classicSVfitComputingTime_real%ilogM%s", addLogM_power_int, optHadTauTF_string.data());
      std::cout << " " << branchName_svfitComputingTime_real << " (type = F)" << std::endl;
      outputTree->Branch(branchName_svfitComputingTime_real.data(), &classicSVfit_logM_entry->svfitComputingTime_real_, Form("%s/F", branchName_svfitComputingTime_real.data()));
      classicSVfit_logM_entries.push_back(classicSVfit_logM_entry);
    }
  }

  const branchEntryType* branchEntryRun            = 0;
  const branchEntryType* branchEntryEvent          = 0;
  const branchEntryType* branchEntryLumi           = 0;
  const branchEntryType* branchEntryLeg1Pt         = 0;
  const branchEntryType* branchEntryLeg1Eta        = 0;
  const branchEntryType* branchEntryLeg1Phi        = 0;
  const branchEntryType* branchEntryLeg1Mass       = 0;
  const branchEntryType* branchEntryLeg2Pt         = 0;
  const branchEntryType* branchEntryLeg2Eta        = 0;
  const branchEntryType* branchEntryLeg2Phi        = 0;
  const branchEntryType* branchEntryLeg2Mass       = 0;
  const branchEntryType* branchEntryMEx            = 0;
  const branchEntryType* branchEntryMEy            = 0;
  const branchEntryType* branchEntryMEtCov00       = 0;
  const branchEntryType* branchEntryMEtCov01       = 0;
  const branchEntryType* branchEntryMEtCov10       = 0;
  const branchEntryType* branchEntryMEtCov11       = 0;
  const branchEntryType* branchEntryGenJet1Pt      = 0;
  const branchEntryType* branchEntryGenJet1Eta     = 0;
  const branchEntryType* branchEntryGenJet1Phi     = 0;
  const branchEntryType* branchEntryGenJet1Mass    = 0;
  const branchEntryType* branchEntryGenJet2Pt      = 0;
  const branchEntryType* branchEntryGenJet2Eta     = 0;
  const branchEntryType* branchEntryGenJet2Phi     = 0;
  const branchEntryType* branchEntryGenJet2Mass    = 0;
  const branchEntryType* branchEntryGenJet3Pt      = 0;
  const branchEntryType* branchEntryGenJet3Eta     = 0;
  const branchEntryType* branchEntryGenJet3Phi     = 0;
  const branchEntryType* branchEntryGenJet3Mass    = 0;
  const branchEntryType* branchEntryGenJet4Pt      = 0;
  const branchEntryType* branchEntryGenJet4Eta     = 0;
  const branchEntryType* branchEntryGenJet4Phi     = 0;
  const branchEntryType* branchEntryGenJet4Mass    = 0;
  const branchEntryType* branchEntryGenJet5Pt      = 0;
  const branchEntryType* branchEntryGenJet5Eta     = 0;
  const branchEntryType* branchEntryGenJet5Phi     = 0;
  const branchEntryType* branchEntryGenJet5Mass    = 0;
  const branchEntryType* branchEntryGenJet6Pt      = 0;
  const branchEntryType* branchEntryGenJet6Eta     = 0;
  const branchEntryType* branchEntryGenJet6Phi     = 0;
  const branchEntryType* branchEntryGenJet6Mass    = 0;

/*
  const branchEntryType* branchEntryHadRecoilPx    = 0;
  const branchEntryType* branchEntryHadRecoilPy    = 0;
  const branchEntryType* branchEntryHadRecoilPz    = 0;
  const branchEntryType* branchEntryHadRecoilCov00 = 0;
  const branchEntryType* branchEntryHadRecoilCov01 = 0;
  const branchEntryType* branchEntryHadRecoilCov10 = 0;
  const branchEntryType* branchEntryHadRecoilCov11 = 0;
 */

  const branchEntryType* branchEntryGenDiTauPt     = 0;

  for ( std::vector<branchEntryType*>::const_iterator branchEntry = branchesToKeep.begin();
	branchEntry != branchesToKeep.end(); ++branchEntry ) {
    if      ( (*branchEntry)->branchName_ == "run"                                       ) branchEntryRun            = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == "event"                                     ) branchEntryEvent          = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == "lumi"                                      ) branchEntryLumi           = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPt", leg1BranchName.data())         ) branchEntryLeg1Pt         = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sEta", leg1BranchName.data())        ) branchEntryLeg1Eta        = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPhi", leg1BranchName.data())        ) branchEntryLeg1Phi        = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sMass", leg1BranchName.data())       ) branchEntryLeg1Mass       = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPt", leg2BranchName.data())         ) branchEntryLeg2Pt         = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sEta", leg2BranchName.data())        ) branchEntryLeg2Eta        = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPhi", leg2BranchName.data())        ) branchEntryLeg2Phi        = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sMass", leg2BranchName.data())       ) branchEntryLeg2Mass       = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPx", metBranchName.data())          ) branchEntryMEx            = (*branchEntry);    
    else if ( (*branchEntry)->branchName_ == Form("%sPy", metBranchName.data())          ) branchEntryMEy            = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sCov00", metBranchName.data())       ) branchEntryMEtCov00       = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sCov01", metBranchName.data())       ) branchEntryMEtCov01       = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sCov10", metBranchName.data())       ) branchEntryMEtCov10       = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sCov11", metBranchName.data())       ) branchEntryMEtCov11       = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPt", genJet1BranchName.data())      ) branchEntryGenJet1Pt      = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sEta", genJet1BranchName.data())     ) branchEntryGenJet1Eta     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPhi", genJet1BranchName.data())     ) branchEntryGenJet1Phi     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sMass", genJet1BranchName.data())    ) branchEntryGenJet1Mass    = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPt", genJet2BranchName.data())      ) branchEntryGenJet2Pt      = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sEta", genJet2BranchName.data())     ) branchEntryGenJet2Eta     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPhi", genJet2BranchName.data())     ) branchEntryGenJet2Phi     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sMass", genJet2BranchName.data())    ) branchEntryGenJet2Mass    = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPt", genJet3BranchName.data())      ) branchEntryGenJet3Pt      = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sEta", genJet3BranchName.data())     ) branchEntryGenJet3Eta     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPhi", genJet3BranchName.data())     ) branchEntryGenJet3Phi     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sMass", genJet3BranchName.data())    ) branchEntryGenJet3Mass    = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPt", genJet4BranchName.data())      ) branchEntryGenJet4Pt      = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sEta", genJet4BranchName.data())     ) branchEntryGenJet4Eta     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPhi", genJet4BranchName.data())     ) branchEntryGenJet4Phi     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sMass", genJet4BranchName.data())    ) branchEntryGenJet4Mass    = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPt", genJet5BranchName.data())      ) branchEntryGenJet5Pt      = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sEta", genJet5BranchName.data())     ) branchEntryGenJet5Eta     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPhi", genJet5BranchName.data())     ) branchEntryGenJet5Phi     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sMass", genJet5BranchName.data())    ) branchEntryGenJet5Mass    = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPt", genJet6BranchName.data())      ) branchEntryGenJet6Pt      = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sEta", genJet6BranchName.data())     ) branchEntryGenJet6Eta     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPhi", genJet6BranchName.data())     ) branchEntryGenJet6Phi     = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sMass", genJet6BranchName.data())    ) branchEntryGenJet6Mass    = (*branchEntry);
/*
    else if ( (*branchEntry)->branchName_ == Form("%sPx", hadRecoilBranchName.data())    ) branchEntryHadRecoilPx    = (*branchEntry);    
    else if ( (*branchEntry)->branchName_ == Form("%sPy", hadRecoilBranchName.data())    ) branchEntryHadRecoilPy    = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sPz", hadRecoilBranchName.data())    ) branchEntryHadRecoilPz    = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sCov00", hadRecoilBranchName.data()) ) branchEntryHadRecoilCov00 = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sCov01", hadRecoilBranchName.data()) ) branchEntryHadRecoilCov01 = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sCov10", hadRecoilBranchName.data()) ) branchEntryHadRecoilCov10 = (*branchEntry);
    else if ( (*branchEntry)->branchName_ == Form("%sCov11", hadRecoilBranchName.data()) ) branchEntryHadRecoilCov11 = (*branchEntry);
 */
    else if ( (*branchEntry)->branchName_ == "genDiTauPt"                                ) branchEntryGenDiTauPt        = (*branchEntry);
  }
  if ( !(branchEntryLeg1Pt && branchEntryLeg1Eta && branchEntryLeg1Phi && branchEntryLeg1Mass) ) 
    throw cms::Exception("addMassVariables") 
      << "Branches for leg1 = '" << leg1BranchName << "*' do not exist !!\n";
  if ( !(branchEntryLeg2Pt && branchEntryLeg2Eta && branchEntryLeg2Phi && branchEntryLeg2Mass) ) 
    throw cms::Exception("addMassVariables") 
      << "Branches for leg2 = '" << leg2BranchName << "*' do not exist !!\n";
  if ( !(branchEntryMEx && branchEntryMEy && branchEntryMEtCov00 && branchEntryMEtCov01 && branchEntryMEtCov10 && branchEntryMEtCov11) )     
    throw cms::Exception("addMassVariables") 
      << "Branches for met = '" << metBranchName << "*' do not exist !!\n";
  if ( !(branchEntryGenJet1Pt && branchEntryGenJet1Eta && branchEntryGenJet1Phi && branchEntryGenJet1Mass) ) 
    throw cms::Exception("addMassVariables") 
      << "Branches for genJet1 = '" << genJet1BranchName << "*' do not exist !!\n";
  if ( !(branchEntryGenJet2Pt && branchEntryGenJet2Eta && branchEntryGenJet2Phi && branchEntryGenJet2Mass) ) 
    throw cms::Exception("addMassVariables") 
      << "Branches for genJet2 = '" << genJet2BranchName << "*' do not exist !!\n";
  if ( !(branchEntryGenJet3Pt && branchEntryGenJet3Eta && branchEntryGenJet3Phi && branchEntryGenJet3Mass) ) 
    throw cms::Exception("addMassVariables") 
      << "Branches for genJet3 = '" << genJet3BranchName << "*' do not exist !!\n";
  if ( !(branchEntryGenJet4Pt && branchEntryGenJet4Eta && branchEntryGenJet4Phi && branchEntryGenJet4Mass) ) 
    throw cms::Exception("addMassVariables") 
      << "Branches for genJet4 = '" << genJet4BranchName << "*' do not exist !!\n";
  if ( !(branchEntryGenJet5Pt && branchEntryGenJet5Eta && branchEntryGenJet5Phi && branchEntryGenJet5Mass) ) 
    throw cms::Exception("addMassVariables") 
      << "Branches for genJet5 = '" << genJet5BranchName << "*' do not exist !!\n";
  if ( !(branchEntryGenJet6Pt && branchEntryGenJet6Eta && branchEntryGenJet6Phi && branchEntryGenJet6Mass) ) 
    throw cms::Exception("addMassVariables") 
      << "Branches for genJet6 = '" << genJet6BranchName << "*' do not exist !!\n";
/*
  if ( !(branchEntryHadRecoilPx && branchEntryHadRecoilPy && branchEntryHadRecoilPz && branchEntryHadRecoilCov00 && branchEntryHadRecoilCov01 && branchEntryHadRecoilCov10 && branchEntryHadRecoilCov11) )     
    throw cms::Exception("addMassVariables") 
      << "Branches for hadRecoil = '" << hadRecoilBranchName << "*' do not exist !!\n";
 */
  if ( !branchEntryGenDiTauPt ) 
    throw cms::Exception("addMassVariables") 
      << "Branches for genDiTau = 'genDiTau*' do not exist !!\n";
    
  //std::string svFitMEM_pdfName = "cteq66";
  std::string svFitMEM_pdfName = "MSTW2008lo68cl";
  
  SVfitMEM_lo svFitAlgoMEM_lo(svFitMEM_sqrtS, svFitMEM_pdfName.data(), svFitMEM::SVfitIntegrand_lo::kLiterature, "", svFitMEM_verbosity);
  svFitAlgoMEM_lo.setCrossSection_and_Acc(svFitMEM_graph_xSection_lo, 0, 1.);
  HadTauTFfromTGraph hadTauTF(svFitMEM_graph_hadTauTF);
  //HadTauTFCrystalBall2 hadTauTF;
  svFitAlgoMEM_lo.setHadTauTF(&hadTauTF);
  svFitAlgoMEM_lo.setMaxObjFunctionCalls(svFitMEM_maxObjFunctionCalls);
  svFitAlgoMEM_lo.setIntMode(svFitMEM_intMode);
/*
  SVfitMEM_nlo svFitAlgoMEM_nlo(svFitMEM_sqrtS, svFitMEM_pdfName.data(), svFitMEM_verbosity);
  svFitAlgoMEM_nlo.setCrossSection_and_Acc(svFitMEM_graph_xSection_nlo, svFitMEM_graph_Acc_nlo, svFitMEM_minAcc);
  svFitAlgoMEM_nlo.enableAcceptanceCuts(leg1minPt, leg1maxAbsEta, leg2minPt, leg2maxAbsEta);
  svFitAlgoMEM_nlo.setHadTauTF(&hadTauTF);
  svFitAlgoMEM_nlo.setMaxObjFunctionCalls(svFitMEM_maxObjFunctionCalls);
  svFitAlgoMEM_nlo.setIntMode(svFitMEM_intMode);
 */
  ClassicSVfit classicSVfitAlgo(verbosity - 1);
  classicSVfitAlgo.setHadTauTF(&hadTauTF);
  classicSVfitAlgo.setMaxObjFunctionCalls(100000);

  int numEntries = inputTree->GetEntries();
  int selectedEntries = 0;
  for ( int iEntry = 0; iEntry < numEntries && (maxEvents == -1 || selectedEntries < maxEvents); ++iEntry ) {
    if ( !(iEntry >= skipEvents) ) continue;

    if ( iEntry > 0 && (iEntry % reportEvery) == 0 ) {
      std::cout << "processing Entry " << iEntry << std::endl;
    }
    
    inputTree->GetEntry(iEntry);

    // read momenta of visible tau decay products and of missing Et
    ULong64_t run          = branchEntryRun->valueL_;
    ULong64_t event        = branchEntryEvent->valueL_;
    ULong64_t lumi         = branchEntryLumi->valueL_;
    Float_t leg1Pt         = branchEntryLeg1Pt->valueF_;
    Float_t leg1Eta        = branchEntryLeg1Eta->valueF_;
    Float_t leg1Phi        = branchEntryLeg1Phi->valueF_;
    Float_t leg1Mass       = branchEntryLeg1Mass->valueF_;
    reco::Candidate::PolarLorentzVector leg1P4(leg1Pt, leg1Eta, leg1Phi, leg1Mass);
    Float_t leg2Pt         = branchEntryLeg2Pt->valueF_;
    Float_t leg2Eta        = branchEntryLeg2Eta->valueF_;
    Float_t leg2Phi        = branchEntryLeg2Phi->valueF_;
    Float_t leg2Mass       = branchEntryLeg2Mass->valueF_;
    reco::Candidate::PolarLorentzVector leg2P4(leg2Pt, leg2Eta, leg2Phi, leg2Mass);
    Float_t mex            = branchEntryMEx->valueF_;
    Float_t mey            = branchEntryMEy->valueF_;
    reco::Candidate::LorentzVector metP4_xyzt(mex, mey, 0., TMath::Sqrt(square(mex) + square(mey)));
    reco::Candidate::PolarLorentzVector metP4(metP4_xyzt.pt(), metP4_xyzt.eta(), metP4_xyzt.phi(), metP4_xyzt.mass());
    Float_t metCov00       = branchEntryMEtCov00->valueF_;
    Float_t metCov01       = branchEntryMEtCov01->valueF_;
    Float_t metCov10       = branchEntryMEtCov10->valueF_;
    Float_t metCov11       = branchEntryMEtCov11->valueF_;
    TMatrixD metCov(2,2);
    metCov[0][0] = metCov00;
    metCov[0][1] = metCov01;
    metCov[1][0] = metCov10;
    metCov[1][1] = metCov11;
    Float_t genJet1Pt         = branchEntryGenJet1Pt->valueF_;
    Float_t genJet1Eta        = branchEntryGenJet1Eta->valueF_;
    Float_t genJet1Phi        = branchEntryGenJet1Phi->valueF_;
    Float_t genJet1Mass       = branchEntryGenJet1Mass->valueF_;
    reco::Candidate::PolarLorentzVector genJet1P4(genJet1Pt, genJet1Eta, genJet1Phi, genJet1Mass);
    Float_t genJet2Pt         = branchEntryGenJet2Pt->valueF_;
    Float_t genJet2Eta        = branchEntryGenJet2Eta->valueF_;
    Float_t genJet2Phi        = branchEntryGenJet2Phi->valueF_;
    Float_t genJet2Mass       = branchEntryGenJet2Mass->valueF_;
    reco::Candidate::PolarLorentzVector genJet2P4(genJet2Pt, genJet2Eta, genJet2Phi, genJet2Mass);
    Float_t genJet3Pt         = branchEntryGenJet3Pt->valueF_;
    Float_t genJet3Eta        = branchEntryGenJet3Eta->valueF_;
    Float_t genJet3Phi        = branchEntryGenJet3Phi->valueF_;
    Float_t genJet3Mass       = branchEntryGenJet3Mass->valueF_;
    reco::Candidate::PolarLorentzVector genJet3P4(genJet3Pt, genJet3Eta, genJet3Phi, genJet3Mass);
    Float_t genJet4Pt         = branchEntryGenJet4Pt->valueF_;
    Float_t genJet4Eta        = branchEntryGenJet4Eta->valueF_;
    Float_t genJet4Phi        = branchEntryGenJet4Phi->valueF_;
    Float_t genJet4Mass       = branchEntryGenJet4Mass->valueF_;
    reco::Candidate::PolarLorentzVector genJet4P4(genJet4Pt, genJet4Eta, genJet4Phi, genJet4Mass);
    Float_t genJet5Pt         = branchEntryGenJet5Pt->valueF_;
    Float_t genJet5Eta        = branchEntryGenJet5Eta->valueF_;
    Float_t genJet5Phi        = branchEntryGenJet5Phi->valueF_;
    Float_t genJet5Mass       = branchEntryGenJet5Mass->valueF_;
    reco::Candidate::PolarLorentzVector genJet5P4(genJet5Pt, genJet5Eta, genJet5Phi, genJet5Mass);
    Float_t genJet6Pt         = branchEntryGenJet6Pt->valueF_;
    Float_t genJet6Eta        = branchEntryGenJet6Eta->valueF_;
    Float_t genJet6Phi        = branchEntryGenJet6Phi->valueF_;
    Float_t genJet6Mass       = branchEntryGenJet6Mass->valueF_;
    reco::Candidate::PolarLorentzVector genJet6P4(genJet6Pt, genJet6Eta, genJet6Phi, genJet6Mass);

    int  nGenJets  = 0;
    int  nVBFpairs = 0;
    bool category_0Jets          = false;
    bool category_1JetBoosted    = false;
    bool category_1JetNotBoosted = false;
    bool category_2Jets          = false;
    bool categorization          = false;

    std::vector<reco::Candidate::PolarLorentzVector> genJetsP4{genJet1P4,genJet2P4,genJet3P4,genJet4P4,genJet5P4,genJet6P4};
    for(size_t ijet=0; ijet<genJetsP4.size(); ijet++){
	    reco::Candidate::PolarLorentzVector genJetX1P4 = genJetsP4[ijet];
	    if(genJetX1P4.pt()>30 && TMath::Abs(genJetX1P4.eta())<4.5) nGenJets++;
	    for(size_t jjet=1; jjet<genJetsP4.size(); jjet++){
		    reco::Candidate::PolarLorentzVector genJetX2P4 = genJetsP4[jjet];
		    if(genJetX1P4.pt()>30 && TMath::Abs(genJetX1P4.eta())<4.5 && genJetX2P4.pt()>30 && TMath::Abs(genJetX2P4.eta())<4.5 &&
				    (genJetX1P4+genJetX2P4).mass()>500 && TMath::Abs( genJetX1P4.eta()-genJetX2P4.eta())>3.5) nVBFpairs++;
	    }
    }
      
    if ( nGenJets >= 2 && nVBFpairs >= 1 ) {
      category_2Jets = true;
    } else if ( nGenJets >= 1 ) {
      Float_t genDiTauPt = branchEntryGenDiTauPt->valueF_;
      if ( genDiTauPt > 100. ) category_1JetBoosted = true;
      else category_1JetNotBoosted = true;
    } else {
      category_0Jets = true;
    }
/*
    if(nGenJets==0)                               category_0Jets          = true;
    if(nGenJets>=2 && nVBFpairs>=1)               category_2Jets          = true;
    else{
	    if(nGenJets>=1 && (leg1P4+leg2P4).pt() < 100) category_1JetNotBoosted = true;
	    if(nGenJets>=1 && (leg1P4+leg2P4).pt() > 100) category_1JetBoosted    = true;
    }
 */
    if      (eventSelection_categorization == kInclusive)                                   { categorization = true; }
    if      (eventSelection_categorization == k0Jets && (category_0Jets))                   { categorization = true; }
    if      (eventSelection_categorization == k1JetBoosted && (category_1JetBoosted))       { categorization = true; }
    if      (eventSelection_categorization == k1JetNotBoosted && (category_1JetNotBoosted)) { categorization = true; }
    if      (eventSelection_categorization == k2Jets && (category_2Jets))                   { categorization = true; }
/*
    //Float_t hadRecoilPx    = branchEntryHadRecoilPx->valueF_;
    //Float_t hadRecoilPy    = branchEntryHadRecoilPy->valueF_;
    Float_t hadRecoilPx    = -(leg1P4.px() + leg2P4.px() + mex);
    //std::cout << "hadRecoilPx = " << branchEntryHadRecoilPx->valueF_ << ", -(leg1P4.px() + leg2P4.px() + mex) = " << -(leg1P4.px() + leg2P4.px() + mex) << std::endl;
    Float_t hadRecoilPy    = -(leg1P4.py() + leg2P4.py() + mey);
    //std::cout << "hadRecoilPy = " << branchEntryHadRecoilPy->valueF_ << ", -(leg1P4.py() + leg2P4.py() + mey) = " << -(leg1P4.py() + leg2P4.py() + mey) << std::endl;
    Float_t hadRecoilPz    = branchEntryHadRecoilPz->valueF_;
    Float_t hadRecoilCov00 = branchEntryHadRecoilCov00->valueF_;
    Float_t hadRecoilCov01 = branchEntryHadRecoilCov01->valueF_;
    Float_t hadRecoilCov10 = branchEntryHadRecoilCov10->valueF_;
    Float_t hadRecoilCov11 = branchEntryHadRecoilCov11->valueF_;
    TMatrixD hadRecoilCov(2,2);
    hadRecoilCov[0][0] = hadRecoilCov00;
    hadRecoilCov[0][1] = hadRecoilCov01;
    hadRecoilCov[1][0] = hadRecoilCov10;
    hadRecoilCov[1][1] = hadRecoilCov11;
    TMatrixD hadRecoilCov = metCov;
 */
    // compute mass variables
    
    

    if ( leg1P4.pt() > leg1minPt && TMath::Abs(leg1P4.eta()) < leg1maxAbsEta && leg2P4.pt() > leg2minPt && TMath::Abs(leg2P4.eta()) < leg2maxAbsEta && categorization) {
      visMass = compVisMass(
        leg1P4, 
        leg2P4);
      compCollinearApproxMass(
        leg1P4, 
        leg2P4, 
        mex, mey, 
        caMass, caMass_isValid);
      mTtotal = TMath::Sqrt(compMt2(leg1P4, leg2P4) + compMt2(leg1P4, metP4) + compMt2(leg2P4, metP4));     
      compSVfitMass(
        leg1Type, leg1P4, 
        leg2Type, leg2P4, 
        mex, mey, metCov, 
	svfitPt, svfitPtErr, svfitPt_isValid, 
	svfitEta, svfitEtaErr, svfitEta_isValid, 
	svfitPhi, svfitPhiErr, svfitPhi_isValid, 
        svfitMass, svfitMassErr, svfitMass_isValid, 
	svfitTransverseMass, svfitTransverseMassErr, svfitTransverseMass_isValid, 
	svfitComputingTime_cpu, svfitComputingTime_real,
	verbosity - 1);
      for ( std::vector<svFitMEM_logM_EntryType*>::iterator svFitMEM_logM_entry = svFitMEM_logM_entries.begin();
	    svFitMEM_logM_entry != svFitMEM_logM_entries.end(); ++svFitMEM_logM_entry ) {
	if ( (*svFitMEM_logM_entry)->lo_or_nlo_ == svFitMEM_logM_EntryType::kLO ) {
          if ( (*svFitMEM_logM_entry)->addLogM_power_ > 0. ) svFitAlgoMEM_lo.addLogM(true, (*svFitMEM_logM_entry)->addLogM_power_);
          else svFitAlgoMEM_lo.addLogM(false);
	  if ( (*svFitMEM_logM_entry)->useHadTauTF_ ) svFitAlgoMEM_lo.enableHadTauTF();
  	  else svFitAlgoMEM_lo.disableHadTauTF();
	  std::cout << "<compSVfitMassMEM_lo (useHadTauTF = " << (*svFitMEM_logM_entry)->useHadTauTF_ << ", addLogM_power = " << (*svFitMEM_logM_entry)->addLogM_power_ << ")>:" << std::endl;
          compSVfitMassMEM_lo(
            svFitAlgoMEM_lo, 
	    leg1TypeMEM, leg1P4, 
  	    leg2TypeMEM, leg2P4, 
	    mex, mey, metCov, 
	    (*svFitMEM_logM_entry)->svfitMass_, (*svFitMEM_logM_entry)->svfitMassErr_, (*svFitMEM_logM_entry)->svfitMass_isValid_,
	    (*svFitMEM_logM_entry)->svfitComputingTime_cpu_, (*svFitMEM_logM_entry)->svfitComputingTime_real_);
/*
	} else if ( (*svFitMEM_logM_entry)->lo_or_nlo_ == svFitMEM_logM_EntryType::kNLO ) {
	  if ( (*svFitMEM_logM_entry)->addLogM_power_ > 0. ) svFitAlgoMEM_nlo.addLogM(true, (*svFitMEM_logM_entry)->addLogM_power_);
          else svFitAlgoMEM_nlo.addLogM(false, (*svFitMEM_logM_entry)->addLogM_power_);
	  if ( (*svFitMEM_logM_entry)->useHadTauTF_ ) svFitAlgoMEM_nlo.enableHadTauTF();
  	  else svFitAlgoMEM_nlo.disableHadTauTF();
          compSVfitMassMEM_nlo(
            svFitAlgoMEM_nlo, 
	    leg1TypeMEM, leg1P4, 
  	    leg2TypeMEM, leg2P4, 
	    hadRecoilPx, hadRecoilPy, hadRecoilPz, hadRecoilCov, 
	    (*svFitMEM_logM_entry)->svfitMass_, (*svFitMEM_logM_entry)->svfitMassErr_, (*svFitMEM_logM_entry)->svfitMass_isValid_,
	    (*svFitMEM_logM_entry)->svfitComputingTime_cpu_, (*svFitMEM_logM_entry)->svfitComputingTime_real_);
 */
	} else assert(0);
      }
      for ( std::vector<classicSVfit_logM_EntryType*>::iterator classicSVfit_logM_entry = classicSVfit_logM_entries.begin();
	    classicSVfit_logM_entry != classicSVfit_logM_entries.end(); ++classicSVfit_logM_entry ) {
	classic_svFit::MeasuredTauLepton::kDecayType leg1Type_classic = getDecayType_classic(leg1Type);
	classic_svFit::MeasuredTauLepton::kDecayType leg2Type_classic = getDecayType_classic(leg2Type);
	if ( (*classicSVfit_logM_entry)->addLogM_power_ > 0. ) classicSVfitAlgo.addLogM_fixed(true, (*classicSVfit_logM_entry)->addLogM_power_);
	else classicSVfitAlgo.addLogM_fixed(false);
	if ( (*classicSVfit_logM_entry)->useHadTauTF_ ) classicSVfitAlgo.enableHadTauTF();
	else classicSVfitAlgo.disableHadTauTF();
	std::cout << "<compClassicSVfitMass (useHadTauTF = " << (*classicSVfit_logM_entry)->useHadTauTF_ << ", addLogM_power = " << (*classicSVfit_logM_entry)->addLogM_power_ << ")>:" << std::endl;
        compClassicSVfitMass(
	  classicSVfitAlgo,		     
	  leg1Type_classic, leg1P4, 
  	  leg2Type_classic, leg2P4, 
	  mex, mey, metCov, 
	  (*classicSVfit_logM_entry)->svfitPt_, (*classicSVfit_logM_entry)->svfitPtErr_, (*classicSVfit_logM_entry)->svfitPt_isValid_,
	  (*classicSVfit_logM_entry)->svfitEta_, (*classicSVfit_logM_entry)->svfitEtaErr_, (*classicSVfit_logM_entry)->svfitEta_isValid_,
	  (*classicSVfit_logM_entry)->svfitPhi_, (*classicSVfit_logM_entry)->svfitPhiErr_, (*classicSVfit_logM_entry)->svfitPhi_isValid_,
	  (*classicSVfit_logM_entry)->svfitMass_, (*classicSVfit_logM_entry)->svfitMassErr_, (*classicSVfit_logM_entry)->svfitMass_isValid_,
	  (*classicSVfit_logM_entry)->svfitTransverseMass_, (*classicSVfit_logM_entry)->svfitTransverseMassErr_, (*classicSVfit_logM_entry)->svfitTransverseMass_isValid_,
	  (*classicSVfit_logM_entry)->svfitComputingTime_cpu_, (*classicSVfit_logM_entry)->svfitComputingTime_real_);
      }
    } else {
      visMass = -1.;
      caMass = -1.;
      caMass_isValid = 0;
      mTtotal = -1.;
      svfitPt = -1.;
      svfitPtErr = 0.;
      svfitPt_isValid = 0;
      svfitEta = -1.;
      svfitEtaErr = 0.;
      svfitEta_isValid = 0;
      svfitPhi = -1.;
      svfitPhiErr = 0.;
      svfitPhi_isValid = 0;
      svfitMass = -1.;
      svfitMassErr = 0.;
      svfitMass_isValid = 0;
      svfitTransverseMass = -1.;
      svfitTransverseMassErr = 0.;
      svfitTransverseMass_isValid = 0;
      for ( std::vector<svFitMEM_logM_EntryType*>::iterator svFitMEM_logM_entry = svFitMEM_logM_entries.begin();
	    svFitMEM_logM_entry != svFitMEM_logM_entries.end(); ++svFitMEM_logM_entry ) {
	(*svFitMEM_logM_entry)->svfitMass_ = -1.;
	(*svFitMEM_logM_entry)->svfitMassErr_ = 0.;
	(*svFitMEM_logM_entry)->svfitMass_isValid_ = 0;
	(*svFitMEM_logM_entry)->svfitComputingTime_cpu_ = -1.;
	(*svFitMEM_logM_entry)->svfitComputingTime_real_ = -1.;
      }
      for ( std::vector<classicSVfit_logM_EntryType*>::iterator classicSVfit_logM_entry = classicSVfit_logM_entries.begin();
	    classicSVfit_logM_entry != classicSVfit_logM_entries.end(); ++classicSVfit_logM_entry ) {
	(*classicSVfit_logM_entry)->svfitPt_ = -1.;
	(*classicSVfit_logM_entry)->svfitPtErr_ = 0.;
	(*classicSVfit_logM_entry)->svfitPt_isValid_ = 0;
	(*classicSVfit_logM_entry)->svfitEta_ = -1.;
	(*classicSVfit_logM_entry)->svfitEtaErr_ = 0.;
	(*classicSVfit_logM_entry)->svfitEta_isValid_ = 0;
	(*classicSVfit_logM_entry)->svfitPhi_ = -1.;
	(*classicSVfit_logM_entry)->svfitPhiErr_ = 0.;
	(*classicSVfit_logM_entry)->svfitPhi_isValid_ = 0;
	(*classicSVfit_logM_entry)->svfitMass_ = -1.;
	(*classicSVfit_logM_entry)->svfitMassErr_ = 0.;
	(*classicSVfit_logM_entry)->svfitMass_isValid_ = 0;
	(*classicSVfit_logM_entry)->svfitTransverseMass_ = -1.;
	(*classicSVfit_logM_entry)->svfitTransverseMassErr_ = 0.;
	(*classicSVfit_logM_entry)->svfitTransverseMass_isValid_ = 0;
	(*classicSVfit_logM_entry)->svfitComputingTime_cpu_ = -1.;
	(*classicSVfit_logM_entry)->svfitComputingTime_real_ = -1.;
      }
    }

    if ( verbosity >= 1 ) {
      std::cout << "RUN: " << run << " LUMI: " << lumi << " EVENT: " << event << std::endl;
      std::cout << " leg1 (branch = " << leg1BranchName << "): Pt = " << leg1Pt << ", eta = " << leg1Eta << ", phi = " << leg1Phi << ", mass = " << leg1Mass << std::endl;
      std::cout << " leg2 (branch = " << leg2BranchName << "): Pt = " << leg2Pt << ", eta = " << leg2Eta << ", phi = " << leg2Phi << ", mass = " << leg2Mass << std::endl;
      std::cout << " MET (branch = " << metBranchName << "): Px = " << mex << ", Py = " << mey << std::endl;
      std::cout << " MET Cov.:" << std::endl;
      metCov.Print();
      std::cout << " visMass = " << visMass << ", caMass = " << caMass << " (isValid = " << caMass_isValid << ")," 
		<< " svFitMass = " << svfitMass << " +/- " << svfitMassErr << " (isValid = " << svfitMass_isValid << "),"  
		<< " svFitTransverseMass = " << svfitTransverseMass << " +/- " << svfitTransverseMassErr << " (isValid = " << svfitTransverseMass_isValid << ")" << std::endl;
      std::cout << " svFitMEM:" << std::endl;
      for ( std::vector<svFitMEM_logM_EntryType*>::const_iterator svFitMEM_logM_entry = svFitMEM_logM_entries.begin();
	    svFitMEM_logM_entry != svFitMEM_logM_entries.end(); ++svFitMEM_logM_entry ) {
	std::cout << "  logM = " << (*svFitMEM_logM_entry)->addLogM_power_ << ", hadTauTF = ";
	if ( (*svFitMEM_logM_entry)->useHadTauTF_ ) std::cout << "enabled";
	else std::cout << "disabled";
	std::cout << ":";
	std::cout << " mass = " << (*svFitMEM_logM_entry)->svfitMass_ << " +/- " << (*svFitMEM_logM_entry)->svfitMassErr_ << " (isValid = " << (*svFitMEM_logM_entry)->svfitMass_isValid_ << ")" << std::endl;
      }
      std::cout << " classicSVfit:" << std::endl;
      for ( std::vector<classicSVfit_logM_EntryType*>::const_iterator classicSVfit_logM_entry = classicSVfit_logM_entries.begin();
	    classicSVfit_logM_entry != classicSVfit_logM_entries.end(); ++classicSVfit_logM_entry ) {
	std::cout << "  logM = " << (*classicSVfit_logM_entry)->addLogM_power_ << ", hadTauTF = ";
	if ( (*classicSVfit_logM_entry)->useHadTauTF_ ) std::cout << "enabled";
	else std::cout << "disabled";
	std::cout << ":";
	std::cout << " mass = " << (*classicSVfit_logM_entry)->svfitMass_ << " +/- " << (*classicSVfit_logM_entry)->svfitMassErr_ << " (isValid = " << (*classicSVfit_logM_entry)->svfitMass_isValid_ << ")," 
		  << " transverse mass = " << (*classicSVfit_logM_entry)->svfitTransverseMass_ << " +/- " << (*classicSVfit_logM_entry)->svfitTransverseMassErr_ << " (isValid = " << (*classicSVfit_logM_entry)->svfitTransverseMass_isValid_ << ")" << std::endl;
      }
    }

    outputTree->Fill();
    ++selectedEntries;
  }

  for ( std::vector<branchEntryType*>::const_iterator it = branchesToKeep.begin();
	it != branchesToKeep.end(); ++it ) {
    delete (*it);
  }
  
  for ( std::vector<svFitMEM_logM_EntryType*>::const_iterator it = svFitMEM_logM_entries.begin();
	it != svFitMEM_logM_entries.end(); ++it ) {
    delete (*it);
  }
  for ( std::vector<classicSVfit_logM_EntryType*>::const_iterator it = classicSVfit_logM_entries.begin();
	it != classicSVfit_logM_entries.end(); ++it ) {
    delete (*it);
  }
  
  //if ( verbosity >= 2 ) {
  //  std::cout << "output Tree:" << std::endl;
  //  outputTree->Print();
  //  outputTree->Scan("*", "", "", 20, 0);
  //}

  std::cout << "writing output Tree to file = " << outputFileName << "." << std::endl;
  TFile* outputFile = new TFile(outputFileName.data(), "RECREATE");
  if ( outputDirName != "" ) {
    createTDirectory_recursively(outputFile, outputDirName);
  }
  outputTree->Write();
  delete outputFile;

  delete svFitMEM_graph_xSection_lo;
  delete svFitMEM_graph_Acc_lo;
  delete svFitMEM_graph_xSection_nlo;
  delete svFitMEM_graph_Acc_nlo;
  delete svFitMEM_graph_hadTauTF;

  delete inputTree;
  
  clock.Show("addMassVariables");

  return 0;
}
