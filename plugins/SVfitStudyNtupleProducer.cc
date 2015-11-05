#include "TauAnalysis/SVfitPerformanceStudies/plugins/SVfitStudyNtupleProducer.h"

#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/TauReco/interface/PFTau.h"

#include "PhysicsTools/JetMCUtils/interface/JetMCTag.h"

#include <TMath.h>
#include <TString.h>

#include <iostream>

SVfitStudyNtupleProducer::SVfitStudyNtupleProducer(const edm::ParameterSet& cfg) 
  : moduleLabel_(cfg.getParameter<std::string>("@module_label")),
    ntuple_(0)
{
  srcGenTauLeptons_ = cfg.getParameter<edm::InputTag>("srcGenTauLeptons");
  srcGenElectrons_ = cfg.getParameter<edm::InputTag>("srcGenElectrons");
  srcGenMuons_ = cfg.getParameter<edm::InputTag>("srcGenMuons");
  srcGenHadTaus_ = cfg.getParameter<edm::InputTag>("srcGenHadTaus");
  srcGenMET_ = cfg.getParameter<edm::InputTag>("srcGenMET");

  srcSmearedHadTaus_ = cfg.getParameter<edm::InputTag>("srcSmearedHadTaus");
  srcSmearedMET_ = cfg.getParameter<edm::InputTag>("srcSmearedMET");

  edm::ParameterSet evtWeights = cfg.getParameter<edm::ParameterSet>("evtWeights");
  typedef std::vector<std::string> vstring;
  vstring evtWeightNames = evtWeights.getParameterNamesForType<edm::InputTag>();
  for ( vstring::const_iterator name = evtWeightNames.begin();
        name != evtWeightNames.end(); ++name ) {    
    edm::InputTag src = evtWeights.getParameter<edm::InputTag>(*name);
    evtWeightsToStore_.push_back(InputTagEntryType(*name, src));
  }

  verbosity_ = ( cfg.exists("verbosity") ) ?
    cfg.getParameter<int>("verbosity") : 0;
}

SVfitStudyNtupleProducer::~SVfitStudyNtupleProducer()
{
// nothing to be done yet...
}

void SVfitStudyNtupleProducer::beginJob()
{
//--- create TTree
  edm::Service<TFileService> fs;
  ntuple_ = fs->make<TTree>("SVfitStudyNtupleProducer", "SVfitStudyNtupleProducer");

//--- add branches 
  addBranchUL("run");
  addBranchUL("event");
  addBranchUL("lumi");

  // tau lepton variables
  addBranch_genTauLepton("genTauLepton1");
  addBranch_genTauLepton("genTauLepton2");
  addBranchI("numGenTauLeptons");
  addBranch_PtEtaPhiMass("genDiTau");

  // electron variables
  addBranch_genElectron("genElectron1");
  addBranch_genElectron("genElectron2");
  addBranchI("numGenElectrons");

  // muon variables
  addBranch_genMuon("genMuon1");
  addBranch_genMuon("genMuon2");
  addBranchI("numGenMuons");

  // variables for hadronic tau decays (generator level)
  addBranch_genHadTau("genHadTau1");
  addBranch_genHadTau("genHadTau2");
  addBranchI("numGenHadTaus");

  // variables for hadronic tau decays (smeared)
  addBranch_genHadTau("smearedHadTau1");
  addBranch_genHadTau("smearedHadTau2");
  addBranchI("numSmearedHadTaus");

  // variables for missing Et (generator level)
  addBranch_genMET("genMEt");

  // variables for missing Et (smeared)
  addBranch_genMET("smearedMEt");

  // event weights/efficiencies
  for ( std::vector<InputTagEntryType>::const_iterator evtWeight = evtWeightsToStore_.begin();
	evtWeight != evtWeightsToStore_.end(); ++evtWeight ) {
    addBranchF(evtWeight->branchName_);
  }
}

namespace
{
  reco::Candidate::LorentzVector getGenTauLeptonP4(const reco::GenJet& genTau)
  {
    reco::Candidate::LorentzVector genTauLeptonP4;
    std::vector<const reco::GenParticle*> daughters = genTau.getGenConstituents();
    for ( std::vector<const reco::GenParticle*>::const_iterator daughter = daughters.begin();
	  daughter != daughters.end(); ++daughter ) {
      if ( !((*daughter)->status() == 1) ) continue; // is stable
      genTauLeptonP4 += (*daughter)->p4();
    }
    return genTauLeptonP4;
  }
}

void SVfitStudyNtupleProducer::analyze(const edm::Event& evt, const edm::EventSetup& es) 
{
  if ( verbosity_ >= 1 ) {
    std::cout << "<SVfitStudyNtupleProducer::analyze>:" << std::endl;
  }

  assert(ntuple_);

  resetBranches();

  setValueUL("run" ,evt.run());
  setValueUL("event", evt.eventAuxiliary().event());
  setValueUL("lumi", evt.luminosityBlock());
  
  edm::Handle<reco::GenJetCollection> genTauLeptons;
  evt.getByLabel(srcGenTauLeptons_, genTauLeptons);
  if ( genTauLeptons->size() >= 1 ) setValue_genTauLepton("genTauLepton1", genTauLeptons->at(0));
  if ( genTauLeptons->size() >= 2 ) setValue_genTauLepton("genTauLepton2", genTauLeptons->at(1));
  setValueI("numGenTauLeptons", genTauLeptons->size());
  if ( genTauLeptons->size() >= 2 ) setValue_PtEtaPhiMass("genDiTau", getGenTauLeptonP4(genTauLeptons->at(0)) + getGenTauLeptonP4(genTauLeptons->at(1)));

  edm::Handle<reco::GenJetCollection> genElectrons;
  evt.getByLabel(srcGenElectrons_, genElectrons);
  if ( genElectrons->size() >= 1 ) setValue_genElectron("genElectron1", genElectrons->at(0));
  if ( genElectrons->size() >= 2 ) setValue_genElectron("genElectron2", genElectrons->at(1));
  setValueI("numGenElectrons", genElectrons->size());

  edm::Handle<reco::GenJetCollection> genMuons;
  evt.getByLabel(srcGenMuons_, genMuons);
  if ( genMuons->size() >= 1 ) setValue_genMuon("genMuon1", genMuons->at(0));
  if ( genMuons->size() >= 2 ) setValue_genMuon("genMuon2", genMuons->at(1));
  setValueI("numGenMuons", genMuons->size());

  edm::Handle<reco::GenJetCollection> genHadTaus;
  evt.getByLabel(srcGenHadTaus_, genHadTaus);
  if ( genHadTaus->size() >= 1 ) setValue_genHadTau("genHadTau1", genHadTaus->at(0));
  if ( genHadTaus->size() >= 2 ) setValue_genHadTau("genHadTau2", genHadTaus->at(1));
  setValueI("numGenHadTaus", genHadTaus->size());
  
  edm::Handle<reco::GenJetCollection> smearedHadTaus;
  evt.getByLabel(srcSmearedHadTaus_, smearedHadTaus);
  if ( smearedHadTaus->size() >= 1 ) setValue_genHadTau("smearedHadTau1", smearedHadTaus->at(0));
  if ( smearedHadTaus->size() >= 2 ) setValue_genHadTau("smearedHadTau2", smearedHadTaus->at(1));
  setValueI("numSmearedHadTaus", smearedHadTaus->size());

  edm::Handle<reco::GenMETCollection> genMETs;
  evt.getByLabel(srcGenMET_, genMETs);
  if ( !(genMETs->size() == 1) ) 
    throw cms::Exception("SVfitStudyNtupleProducer") 
      << " Collection = '" << srcGenMET_.label() << "' does not contain exactly one reco::GenMET object !!\n";
  const reco::GenMET genMEt = genMETs->front();
  //setValue_genMET("genMEt", genMEt);

  edm::Handle<reco::GenMETCollection> smearedMETs;
  evt.getByLabel(srcSmearedMET_, smearedMETs);
  if ( !(smearedMETs->size() == 1) ) 
    throw cms::Exception("SVfitStudyNtupleProducer") 
      << " Collection = '" << srcSmearedMET_.label() << "' does not contain exactly one reco::GenMET object !!\n";
  const reco::GenMET smearedMEt = smearedMETs->front();
  setValue_genMET("smearedMEt", smearedMEt);

  reco::GenMET genMEt_with_Cov(genMEt);
  genMEt_with_Cov.setSignificanceMatrix(smearedMEt.getSignificanceMatrix());
  setValue_genMET("genMEt", genMEt_with_Cov);

  for ( std::vector<InputTagEntryType>::const_iterator evtWeight = evtWeightsToStore_.begin();
	evtWeight != evtWeightsToStore_.end(); ++evtWeight ) {
    edm::Handle<double> evtWeightValue;
    evt.getByLabel(evtWeight->src_, evtWeightValue);
    setValueF(evtWeight->branchName_, *evtWeightValue);
  }

  if ( verbosity_ >= 2 ) {
    printBranches(std::cout);
  }

//--- fill all computed quantities into TTree
  ntuple_->Fill();
}

void SVfitStudyNtupleProducer::addBranchF(const std::string& name) 
{
  if ( branches_.count(name) != 0 )
    throw cms::Exception("SVfitStudyNtupleProducer") 
      << " Branch with name = " << name << " already exists !!\n";
  std::string name_and_format = name + "/F";
  ntuple_->Branch(name.c_str(), &branches_[name].valueF_, name_and_format.c_str());
}

void SVfitStudyNtupleProducer::addBranchI(const std::string& name) 
{
  if ( branches_.count(name) != 0 )
    throw cms::Exception("SVfitStudyNtupleProducer") 
      << " Branch with name = " << name << " already exists !!\n";
  std::string name_and_format = name + "/I";
  ntuple_->Branch(name.c_str(), &branches_[name].valueI_, name_and_format.c_str());
}

void SVfitStudyNtupleProducer::addBranchUL(const std::string& name) 
{
  if ( branches_.count(name) != 0 ) 
    throw cms::Exception("SVfitStudyNtupleProducer") 
      << " Branch with name = " << name << " already exists !!\n";
  std::string name_and_format = name + "/l";
  ntuple_->Branch(name.c_str(), &branches_[name].valueUL_, name_and_format.c_str());
}

void SVfitStudyNtupleProducer::resetBranches()
{
  for ( branchMap::iterator branch = branches_.begin();
	branch != branches_.end(); ++branch ) {
    branch->second.valueF_  = 0.;
    branch->second.valueI_  = 0;
    branch->second.valueUL_ = 0;
  }
}

void SVfitStudyNtupleProducer::printBranches(std::ostream& stream)
{
  stream << "<SVfitStudyNtupleProducer::printBranches>:" << std::endl;
  stream << " registered branches for module = " << moduleLabel_ << std::endl;
  for ( branchMap::const_iterator branch = branches_.begin();
	branch != branches_.end(); ++branch ) {
    stream << " " << branch->first << std::endl;
  }
  stream << std::endl;
}

void SVfitStudyNtupleProducer::setValueF(const std::string& name, double value) 
{
  if ( verbosity_ >= 1 ) std::cout << "branch = " << name << ": value = " << value << std::endl;
  branchMap::iterator branch = branches_.find(name);
  if ( branch != branches_.end() ) {
    branch->second.valueF_ = value;
  } else {
    throw cms::Exception("InvalidParameter") 
      << "No branch with name = " << name << " defined !!\n";
  }
}

void SVfitStudyNtupleProducer::setValueI(const std::string& name, int value) 
{
  if ( verbosity_ >= 1 ) std::cout << "branch = " << name << ": value = " << value << std::endl;
  branchMap::iterator branch = branches_.find(name);
  if ( branch != branches_.end() ) {
    branch->second.valueI_ = value;
  } else {
    throw cms::Exception("InvalidParameter") 
      << "No branch with name = " << name << " defined !!\n";
  }
}

void SVfitStudyNtupleProducer::setValueUL(const std::string& name, unsigned long value) 
{
  if ( verbosity_ >= 1 ) std::cout << "branch = " << name << ": value = " << value << std::endl;
  branchMap::iterator branch = branches_.find(name);
  if ( branch != branches_.end() ) {
    branch->second.valueUL_ = value;
  } else {
    throw cms::Exception("InvalidParameter") 
      << "No branch with name = " << name << " defined !!\n";
  }
}

//
//-------------------------------------------------------------------------------
//

void SVfitStudyNtupleProducer::addBranch_genTauLepton(const std::string& name) 
{
  addBranch_EnPxPyPz(name);
  addBranch_PtEtaPhiMass(name);
  addBranchF(name + "Charge");
}

void SVfitStudyNtupleProducer::addBranch_genElectron(const std::string& name) 
{
  addBranch_EnPxPyPz(name);
  addBranch_PtEtaPhiMass(name);
  addBranchF(name + "Charge");
}

void SVfitStudyNtupleProducer::addBranch_genMuon(const std::string& name) 
{
  addBranch_EnPxPyPz(name);
  addBranch_PtEtaPhiMass(name);
  addBranchF(name + "Charge");
}

void SVfitStudyNtupleProducer::addBranch_genHadTau(const std::string& name) 
{
  addBranch_EnPxPyPz(name);
  addBranch_PtEtaPhiMass(name);
  addBranchF(name + "Charge");
  addBranchI(name + "DecayMode");
}

void SVfitStudyNtupleProducer::addBranch_genMET(const std::string& name) 
{
  addBranchF(name + "Px");
  addBranchF(name + "Py");
  addBranchF(name + "Pt");
  addBranchF(name + "Phi");
  addBranch_Cov2d(name);
}

void SVfitStudyNtupleProducer::addBranch_EnPxPyPz(const std::string& name) 
{
  addBranchF(name + "E");
  addBranch_PxPyPz(name);
}

void SVfitStudyNtupleProducer::addBranch_PxPyPz(const std::string& name) 
{  
  addBranchF(name + "Px");
  addBranchF(name + "Py");
  addBranchF(name + "Pz");
}

void SVfitStudyNtupleProducer::addBranch_PtEtaPhiMass(const std::string& name) 
{
  addBranch_PtEtaPhi(name);
  addBranchF(name + "Mass");
}

void SVfitStudyNtupleProducer::addBranch_PtEtaPhi(const std::string& name) 
{
  addBranchF(name + "Pt");
  addBranchF(name + "Eta");
  addBranchF(name + "Phi");
}

void SVfitStudyNtupleProducer::addBranch_Cov2d(const std::string& name)
{
  addBranchF(name + "Cov00");
  addBranchF(name + "Cov01");
  addBranchF(name + "Cov10");
  addBranchF(name + "Cov11");
}

//
//-------------------------------------------------------------------------------
//

void SVfitStudyNtupleProducer::setValue_genTauLepton(const std::string& name, const reco::GenJet& genTauLepton) 
{
  reco::Candidate::LorentzVector genTauLeptonP4 = getGenTauLeptonP4(genTauLepton);
  setValue_EnPxPyPz(name, genTauLeptonP4);
  setValue_PtEtaPhiMass(name, genTauLeptonP4);
  setValueF(name + "Charge", genTauLepton.charge());
}

void SVfitStudyNtupleProducer::setValue_genElectron(const std::string& name, const reco::GenJet& genElectron) 
{
  setValue_EnPxPyPz(name, genElectron.p4());
  setValue_PtEtaPhiMass(name, genElectron.p4());
  setValueF(name + "Charge", genElectron.charge());
}

void SVfitStudyNtupleProducer::setValue_genMuon(const std::string& name, const reco::GenJet& genMuon) 
{
  setValue_EnPxPyPz(name, genMuon.p4());
  setValue_PtEtaPhiMass(name, genMuon.p4());
  setValueF(name + "Charge", genMuon.charge());
}

void SVfitStudyNtupleProducer::setValue_genHadTau(const std::string& name, const reco::GenJet& genHadTau) 
{
  setValue_EnPxPyPz(name, genHadTau.p4());
  setValue_PtEtaPhiMass(name, genHadTau.p4());
  setValueF(name + "Charge", genHadTau.charge());
  int decayMode_int = -1;
  std::string decayMode = JetMCTagUtils::genTauDecayMode(genHadTau);
  if      ( decayMode == "oneProng0Pi0"   )  decayMode_int = reco::PFTau::kOneProng0PiZero;
  else if ( decayMode == "oneProng1Pi0"   )  decayMode_int = reco::PFTau::kOneProng1PiZero;
  else if ( decayMode == "oneProng2Pi0"   )  decayMode_int = reco::PFTau::kOneProng2PiZero;
  else if ( decayMode == "threeProng0Pi0" )  decayMode_int = reco::PFTau::kThreeProng0PiZero;
  else if ( decayMode == "threeProng1Pi0" )  decayMode_int = reco::PFTau::kThreeProng1PiZero;
  else if ( !(decayMode == "electron" || decayMode == "muon") ) decayMode_int = reco::PFTau::kRareDecayMode;
  setValueF(name + "DecayMode", decayMode_int);
}

void SVfitStudyNtupleProducer::setValue_genMET(const std::string& name, const reco::GenMET& genMET) 
{
  setValueF(name + "Px", genMET.px());
  setValueF(name + "Py", genMET.py());
  setValueF(name + "Pt", genMET.pt());
  setValueF(name + "Phi", genMET.phi());
  setValue_Cov2d(name, genMET.getSignificanceMatrix());
}

template <typename T>
void SVfitStudyNtupleProducer::setValue_EnPxPyPz(const std::string& name, const T& p4)
{
  setValueF(name + "E",  p4.E());
  setValue_PxPyPz(name,  p4.px(), p4.py(), p4.pz());  
}

void SVfitStudyNtupleProducer::setValue_PxPyPz(const std::string& name, double px, double py, double pz)
{
  setValueF(name + "Px", px);
  setValueF(name + "Py", py);
  setValueF(name + "Pz", pz);
}

template <typename T>
void SVfitStudyNtupleProducer::setValue_PtEtaPhiMass(const std::string& name, const T& p4)
{
  setValue_PtEtaPhi(name, p4.pt(), p4.eta(), p4.phi());
  setValueF(name + "Mass", p4.M());
}

void SVfitStudyNtupleProducer::setValue_PtEtaPhi(const std::string& name, double pt, double eta, double phi)
{
  setValueF(name + "Pt", pt);
  setValueF(name + "Eta", eta);
  setValueF(name + "Phi", phi);
}

template <typename T>
void SVfitStudyNtupleProducer::setValue_Cov2d(const std::string& name, const T& cov)
{
  setValueF(name + "Cov00", cov[0][0]);
  setValueF(name + "Cov01", cov[0][1]);
  setValueF(name + "Cov10", cov[1][0]);
  setValueF(name + "Cov11", cov[1][1]);
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(SVfitStudyNtupleProducer);
