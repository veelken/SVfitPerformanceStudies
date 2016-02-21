#include "TauAnalysis/SVfitPerformanceStudies/plugins/GenHadRecoilProducer.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/SVfitPerformanceStudies/interface/GenHadRecoil.h"
#include "DataFormats/SVfitPerformanceStudies/interface/GenHadRecoilFwd.h"

#include <TMath.h>

GenHadRecoilProducer::GenHadRecoilProducer(const edm::ParameterSet& cfg)
{ 
  srcGenParticles_ = cfg.getParameter<edm::InputTag>("srcGenParticles");
  srcGenElectrons_ = cfg.getParameter<edm::InputTag>("srcGenElectrons");
  srcGenMuons_ = cfg.getParameter<edm::InputTag>("srcGenMuons");
  srcGenHadTaus_ = cfg.getParameter<edm::InputTag>("srcGenHadTaus");

  verbosity_ = cfg.getParameter<int>("verbosity");

  produces<svFitMEM::GenHadRecoilCollection>("");
}

GenHadRecoilProducer::~GenHadRecoilProducer()
{
// nothing to be done yet...
}

namespace
{
  bool isMatched(const reco::GenParticle& genParticle, const reco::GenJetCollection& genVisTaus)
  {
    for ( reco::GenJetCollection::const_iterator genVisTau = genVisTaus.begin();
	  genVisTau != genVisTaus.end(); ++genVisTau ) {
      std::vector<const reco::GenParticle*> genDaughters = genVisTau->getGenConstituents();
      for ( std::vector<const reco::GenParticle*>::const_iterator genDaughter = genDaughters.begin();
	    genDaughter != genDaughters.end(); ++genDaughter ) {
	int status = (*genDaughter)->status();
	if ( status != 1 ) continue; 
	int absPdgId = TMath::Abs((*genDaughter)->pdgId());
	if ( absPdgId == 12 || absPdgId == 14 || absPdgId == 16 ) continue;
	double dR = deltaR(genParticle.p4(), (*genDaughter)->p4());
	if ( dR < 1.e-2 ) return true;
      }
    }
    return false;
  }
}

void GenHadRecoilProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  if ( verbosity_ >= 1 ) {
    std::cout << "<GenHadRecoilProducer::produce>:" << std::endl;
  }
  
  edm::Handle<reco::GenParticleCollection> genParticles;
  evt.getByLabel(srcGenParticles_, genParticles);

  edm::Handle<reco::GenJetCollection> genElectrons;
  evt.getByLabel(srcGenElectrons_, genElectrons);
  edm::Handle<reco::GenJetCollection> genMuons;
  evt.getByLabel(srcGenMuons_, genMuons);
  edm::Handle<reco::GenJetCollection> genHadTaus;
  evt.getByLabel(srcGenHadTaus_, genHadTaus);

  std::auto_ptr<svFitMEM::GenHadRecoilCollection> genHadRecoils(new svFitMEM::GenHadRecoilCollection());

  reco::Candidate::LorentzVector genHadRecoilP4;
  reco::Candidate::Charge genHadRecoilCharge = 0;

  for ( reco::GenParticleCollection::const_iterator genParticle = genParticles->begin();
	genParticle != genParticles->end(); ++genParticle ) {
    // CV: consider "stable" particles only
    int status = genParticle->status();
    if ( status != 1 ) continue; 

    // CV: skip neutrinos
    int absPdgId = TMath::Abs(genParticle->pdgId());
    if ( absPdgId == 12 || absPdgId == 14 || absPdgId == 16 ) continue;

    // CV: skip electrons, muons, and hadronic taus
    bool isElectron = isMatched(*genParticle, *genElectrons);
    if ( isElectron ) continue;
    bool isMuon = isMatched(*genParticle, *genMuons);
    if ( isMuon ) continue;
    bool isHadTau = isMatched(*genParticle, *genHadTaus);
    if ( isHadTau ) continue;

    genHadRecoilP4 += genParticle->p4();
    genHadRecoilCharge += genParticle->charge();
  }
  if ( verbosity_ >= 1 ) {
    std::cout << "genHadRecoil: E = " << genHadRecoilP4.energy() << ", Px = " << genHadRecoilP4.px() << ", Py = " << genHadRecoilP4.py() << ", Pz = " << genHadRecoilP4.pz()
	      << " (charge = " << genHadRecoilCharge << ", mass = " << genHadRecoilP4.mass() << ")" << std::endl;
  }

  svFitMEM::GenHadRecoil genHadRecoil(genHadRecoilCharge, genHadRecoilP4);
  genHadRecoils->push_back(genHadRecoil);

  evt.put(genHadRecoils);
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(GenHadRecoilProducer);
