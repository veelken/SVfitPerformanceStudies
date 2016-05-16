#ifndef TauAnalysis_SVfitPerformanceStudies_SmearedHadRecoilProducer_h
#define TauAnalysis_SVfitPerformanceStudies_SmearedHadRecoilProducer_h

/** \class SmearedHadRecoilProducer
 *
 * Produce GenHadRecoil objects corresponding to vectorial sum of the momenta
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

#include "DataFormats/SVfitPerformanceStudies/interface/GenHadRecoilFwd.h"

#include <TRandom3.h>

class SmearedHadRecoilProducer : public edm::EDProducer
{
 public:
  explicit SmearedHadRecoilProducer(const edm::ParameterSet&);
  ~SmearedHadRecoilProducer();
  
  void produce(edm::Event&, const edm::EventSetup&);

 private:
  edm::EDGetTokenT<svFitMEM::GenHadRecoilCollection> src_;

  double sigmaPx_;
  double sigmaPy_;
  double sigmaPz_;
  double sigmaMass_;

  int verbosity_;

  TRandom3 rnd_;
};

#endif
