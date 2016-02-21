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

class GenHadRecoilProducer : public edm::EDProducer
{
 public:
  explicit GenHadRecoilProducer(const edm::ParameterSet&);
  ~GenHadRecoilProducer();
  
  void produce(edm::Event&, const edm::EventSetup&);

 private:
  edm::InputTag srcGenParticles_;
  edm::InputTag srcGenElectrons_;
  edm::InputTag srcGenMuons_;
  edm::InputTag srcGenHadTaus_;

  int verbosity_;
};

#endif
