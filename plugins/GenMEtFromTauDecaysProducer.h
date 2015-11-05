#ifndef TauAnalysis_SVfitPerformanceStudies_GenMEtFromTauDecaysProducer_h
#define TauAnalysis_SVfitPerformanceStudies_GenMEtFromTauDecaysProducer_h

/** \class GenMEtFromTauDecaysProducer
 *
 * Produce reco::GenMET objects corresponding to vectorial sum of the momenta
 * of all neutrinos produced in tau decays in the event
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

class GenMEtFromTauDecaysProducer : public edm::EDProducer
{
 public:
  explicit GenMEtFromTauDecaysProducer(const edm::ParameterSet&);
  ~GenMEtFromTauDecaysProducer();
  
  void produce(edm::Event&, const edm::EventSetup&);

 private:
  edm::InputTag src_;
};

#endif
