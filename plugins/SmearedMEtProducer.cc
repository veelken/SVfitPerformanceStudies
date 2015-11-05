#include "TauAnalysis/SVfitPerformanceStudies/plugins/SmearedMEtProducer.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"

#include <TMath.h>

SmearedMEtProducer::SmearedMEtProducer(const edm::ParameterSet& cfg)
{ 
  src_ = cfg.getParameter<edm::InputTag>("src");

  sigmaX_ = cfg.getParameter<double>("sigmaX");
  sigmaY_ = cfg.getParameter<double>("sigmaY");

  rnd_.SetSeed(0);

  produces<reco::GenMETCollection>("");
}

SmearedMEtProducer::~SmearedMEtProducer()
{
// nothing to be done yet...
}

void SmearedMEtProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  //std::cout << "<SmearedMEtProducer::produce>:" << std::endl;

  edm::Handle<reco::GenMETCollection> genMETs;
  evt.getByLabel(src_, genMETs);

  std::auto_ptr<reco::GenMETCollection> genMETs_smeared(new reco::GenMETCollection());

  for ( reco::GenMETCollection::const_iterator genMET = genMETs->begin();
	genMET != genMETs->end(); ++genMET ) {
    reco::GenMET genMET_smeared(*genMET);

    double mex_smeared = rnd_.Gaus(genMET->px(), sigmaX_);
    double mey_smeared = rnd_.Gaus(genMET->py(), sigmaY_);
    reco::Candidate::LorentzVector p4_smeared(mex_smeared, mey_smeared, 0., TMath::Sqrt(mex_smeared*mex_smeared + mey_smeared*mey_smeared));
    genMET_smeared.setP4(p4_smeared);

    reco::METCovMatrix cov;
    cov[0][0] = sigmaX_*sigmaX_;
    cov[0][1] = 0.;
    cov[1][0] = 0.;
    cov[1][1] = sigmaY_*sigmaY_;
    genMET_smeared.setSignificanceMatrix(cov);

    genMETs_smeared->push_back(genMET_smeared);
  }

  evt.put(genMETs_smeared);
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(SmearedMEtProducer);
