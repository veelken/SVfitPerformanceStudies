#include "TauAnalysis/SVfitPerformanceStudies/plugins/GenMEtFromTauDecaysProducer.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"

#include <TMath.h>

GenMEtFromTauDecaysProducer::GenMEtFromTauDecaysProducer(const edm::ParameterSet& cfg)
 : src_(consumes<reco::GenJetCollection>(cfg.getParameter<edm::InputTag>("src")))
{ 
  verbosity_ = cfg.getParameter<int>("verbosity");

  produces<reco::GenMETCollection>("");
}

GenMEtFromTauDecaysProducer::~GenMEtFromTauDecaysProducer()
{
// nothing to be done yet...
}

void GenMEtFromTauDecaysProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  if ( verbosity_ >= 1 ) {
    std::cout << "<GenMEtFromTauDecaysProducer::produce>:" << std::endl;
  }
 
  edm::Handle<reco::GenJetCollection> genTaus;
  evt.getByToken(src_, genTaus);

  std::auto_ptr<reco::GenMETCollection> genMETs(new reco::GenMETCollection());

  reco::Candidate::LorentzVector genMEtP4;

  for ( reco::GenJetCollection::const_iterator genTau = genTaus->begin();
	genTau != genTaus->end(); ++genTau ) {
    std::vector<const reco::GenParticle*> daughters = genTau->getGenConstituents();
    for ( std::vector<const reco::GenParticle*>::const_iterator daughter = daughters.begin();
	  daughter != daughters.end(); ++daughter ) {
      if ( !((*daughter)->status() == 1) ) continue; // is stable
      int absPdgId = TMath::Abs((*daughter)->pdgId());
      if ( absPdgId == 12 || absPdgId == 14 || absPdgId == 16 ) { // is neutrino
        if ( verbosity_ >= 2 ) {
          std::cout << "adding genParticle: Pt = " << (*daughter)->pt() << " (Px = " << (*daughter)->px() << ", Py = " << (*daughter)->py() << ")" << ","	
                    << " eta = " << (*daughter)->eta() << ", phi = " << (*daughter)->phi() << " (pdgId = " << (*daughter)->pdgId() << ")" << std::endl;   
        }
	genMEtP4 += (*daughter)->p4();
      }
    }
  }
  if ( verbosity_ >= 1 ) {
    std::cout << "genMEt: Pt = " << genMEtP4.pt() << " (Px = " << genMEtP4.px() << ", Py = " << genMEtP4.py() << "), phi = " << genMEtP4.phi() << std::endl;  
  }

  reco::GenMET genMET;
  genMET.setP4(genMEtP4);

  genMETs->push_back(genMET);

  evt.put(genMETs);
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(GenMEtFromTauDecaysProducer);
