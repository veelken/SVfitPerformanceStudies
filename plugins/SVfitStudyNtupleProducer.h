#ifndef TauAnalysis_SVfitPerformanceStudies_SVfitStudyNtupleProducer_h  
#define TauAnalysis_SVfitPerformanceStudies_SVfitStudyNtupleProducer_h  

/** \class SVfitStudyNtupleProducer
 *
 * Produce Ntuple for SVfit performance studies 
 * using (smeared) generator level information as input
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/SVfitPerformanceStudies/interface/GenHadRecoil.h"
#include "DataFormats/SVfitPerformanceStudies/interface/GenHadRecoilFwd.h"

#include <TTree.h>

#include <map>
#include <string>
#include <vector>
#include <ostream>

class SVfitStudyNtupleProducer : public edm::EDAnalyzer 
{
 public:
  
  SVfitStudyNtupleProducer(const edm::ParameterSet&);
  ~SVfitStudyNtupleProducer();

  void analyze(const edm::Event&, const edm::EventSetup&);
  void beginJob();

 private:

  void addBranchF(const std::string&);
  void addBranchI(const std::string&);
  void addBranchUL(const std::string&);

  void addBranch_genTauLepton(const std::string&);
  void addBranch_genElectron(const std::string&);
  void addBranch_genMuon(const std::string&);
  void addBranch_genHadTau(const std::string&);
  void addBranch_genMET(const std::string&);
  void addBranch_genHadRecoil(const std::string&);
  void addBranch_genParticle(const std::string&);
  void addBranch_genJet(const std::string&);
  
  void addBranch_EnPxPyPz(const std::string&);
  void addBranch_PxPyPz(const std::string&);
  void addBranch_PtEtaPhiMass(const std::string&);
  void addBranch_PtEtaPhi(const std::string&);
  void addBranch_Cov2d(const std::string&);
  void addBranch_Cov4d(const std::string&);
    
  void resetBranches();

  void printBranches(std::ostream&);

  void setValueF(const std::string&, double);
  void setValueI(const std::string&, int);
  void setValueUL(const std::string&, unsigned long);

  void setValue_genTauLepton(const std::string&, const reco::GenJet&);
  void setValue_genElectron(const std::string&, const reco::GenJet&);
  void setValue_genMuon(const std::string&, const reco::GenJet&);
  void setValue_genHadTau(const std::string&, const reco::GenJet&);
  void setValue_genMET(const std::string&, const reco::GenMET&);
  void setValue_genHadRecoil(const std::string&, const svFitMEM::GenHadRecoil&);
  void setValue_genParticle(const std::string&, const reco::GenParticle&);
  void setValue_genJet(const std::string&, const reco::GenJet&);

  template <typename T>
  void setValue_EnPxPyPz(const std::string&, const T&);
  void setValue_PxPyPz(const std::string&, double, double, double);
  template <typename T>
  void setValue_PtEtaPhiMass(const std::string&, const T&);
  void setValue_PtEtaPhi(const std::string&, double, double, double);
  template <typename T>
  void setValue_Cov2d(const std::string&, const T&);
  template <typename T>
  void setValue_Cov4d(const std::string&, const T&);

  std::string moduleLabel_;

  edm::EDGetTokenT<reco::GenJetCollection> srcGenTauLeptons_;
  edm::EDGetTokenT<reco::GenJetCollection> srcGenElectrons_;
  edm::EDGetTokenT<reco::GenJetCollection> srcGenMuons_;  
  edm::EDGetTokenT<reco::GenJetCollection> srcGenHadTaus_;
  edm::EDGetTokenT<reco::GenMETCollection> srcGenMET_;
  edm::InputTag srcGenMET_label_;
  edm::EDGetTokenT<svFitMEM::GenHadRecoilCollection> srcGenHadRecoil_;
  edm::InputTag srcGenHadRecoil_label_;
  edm::EDGetTokenT<reco::GenParticleCollection> srcGenParticles_;
  edm::EDGetTokenT<reco::GenJetCollection> srcGenJets_;
  double minJetPt_;
  double maxJetAbsEta_;

  edm::EDGetTokenT<reco::GenJetCollection> srcSmearedHadTaus_;  
  edm::EDGetTokenT<reco::GenMETCollection> srcSmearedMET_;
  edm::InputTag srcSmearedMET_label_;   
  edm::EDGetTokenT<svFitMEM::GenHadRecoilCollection> srcSmearedHadRecoil_;
  edm::InputTag srcSmearedHadRecoil_label_;

  struct InputTagEntryType
  {
    InputTagEntryType(const std::string& branchName, const edm::EDGetTokenT<double>& src)
      : branchName_(branchName),
        src_(src)
    {}
    ~InputTagEntryType() {}
    std::string branchName_;
    edm::EDGetTokenT<double> src_;
  };
  std::vector<InputTagEntryType> evtWeightsToStore_;

  struct branchEntryType
  {
    branchEntryType()
      : valueF_(0.),
        valueI_(0),
	valueUL_(0)
    {}
    ~branchEntryType() {}
    Float_t valueF_;
    Int_t valueI_;
    ULong_t valueUL_;
  };
  typedef std::map<std::string, branchEntryType> branchMap; // key = branch name
  branchMap branches_;

  TTree* ntuple_;

  int verbosity_;
};

#endif


