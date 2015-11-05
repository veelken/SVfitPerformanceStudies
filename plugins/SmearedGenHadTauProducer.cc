#include "TauAnalysis/SVfitPerformanceStudies/plugins/SmearedGenHadTauProducer.h"

#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "PhysicsTools/JetMCUtils/interface/JetMCTag.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include <TFile.h>
#include <TMath.h>

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
}

SmearedGenHadTauProducer::SmearedGenHadTauProducer(const edm::ParameterSet& cfg)
  : graph_(0)
{ 
  src_ = cfg.getParameter<edm::InputTag>("src");

  inputFileName_ = cfg.getParameter<std::string>("inputFileName");
  TFile* inputFile = new TFile(findFile(inputFileName_).data());
  graphName_ = cfg.getParameter<std::string>("graphName");
  graph_ = readGraph<TGraph>(inputFile, graphName_);
  delete inputFile;

  rnd_.SetSeed(0);

  produces<reco::GenJetCollection>("");
}

SmearedGenHadTauProducer::~SmearedGenHadTauProducer()
{
  delete graph_;
}

void SmearedGenHadTauProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  //std::cout << "<SmearedGenHadTauProducer::produce>:" << std::endl;

  edm::Handle<reco::GenJetCollection> genHadTaus;
  evt.getByLabel(src_, genHadTaus);

  std::auto_ptr<reco::GenJetCollection> genHadTaus_smeared(new reco::GenJetCollection());

  for ( reco::GenJetCollection::const_iterator genHadTau = genHadTaus->begin();
	genHadTau != genHadTaus->end(); ++genHadTau ) {
    reco::GenJet genHadTau_smeared(*genHadTau);

    //double smearFactor = rnd_.Gaus(1.0, 0.10); // CV: only for testing, to be replaced by Betty's crystal-ball code later !!
    double u = rnd_.Rndm();
    double smearFactor = graph_->Eval(u);

    std::string decayMode = JetMCTagUtils::genTauDecayMode(*genHadTau);
    if ( //decayMode == "electron"     || 
	 //decayMode == "muon"         ||
	 decayMode == "oneProng0Pi0" ) {
      const double electronMass = 0.51100e-3; // GeV
      const double muonMass = 0.10566; // GeV
      const double chargedPionMass = 0.13957; // GeV
      double mass;
      if      ( decayMode == "electron"     ) mass = electronMass;
      else if ( decayMode == "muon"         ) mass = muonMass;
      else if ( decayMode == "oneProng0Pi0" ) mass = chargedPionMass;
      else assert(0);
      double en_smeared = smearFactor*genHadTau->energy();
      if ( en_smeared < mass ) en_smeared = mass;
      double p_smeared = TMath::Sqrt(en_smeared*en_smeared - mass*mass);
      double px_smeared = TMath::Cos(genHadTau->phi())*TMath::Sin(genHadTau->theta())*p_smeared;
      double py_smeared = TMath::Sin(genHadTau->phi())*TMath::Sin(genHadTau->theta())*p_smeared;
      double pz_smeared = TMath::Cos(genHadTau->theta())*p_smeared;
      reco::Candidate::LorentzVector p4_smeared(px_smeared, py_smeared, pz_smeared, en_smeared);
      genHadTau_smeared.setP4(p4_smeared);
    } else if ( !(decayMode == "electron" || decayMode == "muon") ) {
      double mass = smearFactor*genHadTau->mass();
      if ( mass < 0.3 ) mass = 0.3;
      double en_smeared = smearFactor*genHadTau->energy();
      if ( en_smeared < mass ) en_smeared = mass;
      double p_smeared = TMath::Sqrt(en_smeared*en_smeared - mass*mass);
      double px_smeared = TMath::Cos(genHadTau->phi())*TMath::Sin(genHadTau->theta())*p_smeared;
      double py_smeared = TMath::Sin(genHadTau->phi())*TMath::Sin(genHadTau->theta())*p_smeared;
      double pz_smeared = TMath::Cos(genHadTau->theta())*p_smeared;
      reco::Candidate::LorentzVector p4_smeared(px_smeared, py_smeared, pz_smeared, en_smeared);
      genHadTau_smeared.setP4(p4_smeared);
    }

    genHadTaus_smeared->push_back(genHadTau_smeared);
  }

  evt.put(genHadTaus_smeared);
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(SmearedGenHadTauProducer);
