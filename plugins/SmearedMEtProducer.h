#ifndef TauAnalysis_SVfitPerformanceStudies_SmearedMEtProducer_h
#define TauAnalysis_SVfitPerformanceStudies_SmearedMEtProducer_h

/** \class SmearedMEtProducer
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
#include "FWCore/Utilities/interface/EDGetToken.h"

#include "DataFormats/METReco/interface/GenMETCollection.h"

#include <TRandom3.h>

class SmearedMEtProducer : public edm::EDProducer
{
 public:
  explicit SmearedMEtProducer(const edm::ParameterSet&);
  ~SmearedMEtProducer();
  
  void produce(edm::Event&, const edm::EventSetup&);

 private:
  edm::EDGetTokenT<reco::GenMETCollection> src_;

  double sigmaX_;
  double sigmaY_;

  int verbosity_;

  TRandom3 rnd_;
};

#endif
