#ifndef TauAnalysis_SVfitPerformanceStudies_GenHadRecoilProducer_h
#define TauAnalysis_SVfitPerformanceStudies_GenHadRecoilProducer_h

/** \class GenHadRecoilProducer
 *
 * Produce svFitMEM::GenHadRecoil objects corresponding to vectorial sum of the momenta
 * of all particles in the "hadronic recoil" of the event
 * 
 * \author Christian Veelken, Tallinn
 *
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"

class GenHadRecoilProducer : public edm::EDProducer
{
 public:
  explicit GenHadRecoilProducer(const edm::ParameterSet&);
  ~GenHadRecoilProducer();
  
  void produce(edm::Event&, const edm::EventSetup&);

 private:
  edm::EDGetTokenT<reco::GenParticleCollection> srcGenParticles_;
  edm::EDGetTokenT<reco::GenJetCollection> srcGenElectrons_;
  edm::EDGetTokenT<reco::GenJetCollection> srcGenMuons_;
  edm::EDGetTokenT<reco::GenJetCollection> srcGenHadTaus_;

  int verbosity_;
};

#endif
