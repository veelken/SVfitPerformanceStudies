#ifndef TauAnalysis_SVfitPerformanceStudies_SmearedGenHadTauProducer_h
#define TauAnalysis_SVfitPerformanceStudies_SmearedGenHadTauProducer_h

/** \class SmearedGenHadTauProducer
 *
 * Produce collection of GenJet objects corresponding to hadronic tau decays
 * with energy resolution smeared by Crystal-Ball function
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

#include <TGraph.h>
#include <TRandom3.h>

#include <string>

class SmearedGenHadTauProducer : public edm::EDProducer
{
 public:
  explicit SmearedGenHadTauProducer(const edm::ParameterSet&);
  ~SmearedGenHadTauProducer();
  
  void produce(edm::Event&, const edm::EventSetup&);

 private:
  edm::InputTag src_;

  std::string inputFileName_;
  std::string graphName_;
  const TGraph* graph_;

  TRandom3 rnd_;
};

#endif
