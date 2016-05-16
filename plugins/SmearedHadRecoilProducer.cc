#include "TauAnalysis/SVfitPerformanceStudies/plugins/SmearedHadRecoilProducer.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/SVfitPerformanceStudies/interface/GenHadRecoil.h"

#include <TMath.h>

SmearedHadRecoilProducer::SmearedHadRecoilProducer(const edm::ParameterSet& cfg)
 : src_(consumes<svFitMEM::GenHadRecoilCollection>(cfg.getParameter<edm::InputTag>("src")))
{ 
  sigmaPx_   = cfg.getParameter<double>("sigmaPx");
  sigmaPy_   = cfg.getParameter<double>("sigmaPy");
  sigmaPz_   = cfg.getParameter<double>("sigmaPz");
  sigmaMass_ = cfg.getParameter<double>("sigmaMass");

  rnd_.SetSeed(0);

  produces<svFitMEM::GenHadRecoilCollection>("");
}

SmearedHadRecoilProducer::~SmearedHadRecoilProducer()
{
// nothing to be done yet...
}

void SmearedHadRecoilProducer::produce(edm::Event& evt, const edm::EventSetup& es)
{
  if ( verbosity_ >= 1 ) {
    std::cout << "<SmearedHadRecoilProducer::produce>:" << std::endl;
  }

  edm::Handle<svFitMEM::GenHadRecoilCollection> genHadRecoils;
  evt.getByToken(src_, genHadRecoils);

  std::auto_ptr<svFitMEM::GenHadRecoilCollection> genHadRecoils_smeared(new svFitMEM::GenHadRecoilCollection());

  for ( svFitMEM::GenHadRecoilCollection::const_iterator genHadRecoil = genHadRecoils->begin();
	genHadRecoil != genHadRecoils->end(); ++genHadRecoil ) {
    svFitMEM::GenHadRecoil genHadRecoil_smeared(*genHadRecoil);

    double px_smeared   = (sigmaPx_   > 0. ) ? rnd_.Gaus(genHadRecoil->px(),   sigmaPx_)   : genHadRecoil->px();
    double py_smeared   = (sigmaPy_   > 0. ) ? rnd_.Gaus(genHadRecoil->py(),   sigmaPy_)   : genHadRecoil->py();
    double pz_smeared   = (sigmaPz_   > 0. ) ? rnd_.Gaus(genHadRecoil->pz(),   sigmaPz_)   : genHadRecoil->pz();
    double mass_smeared = (sigmaMass_ > 0. ) ? rnd_.Gaus(genHadRecoil->mass(), sigmaMass_) : genHadRecoil->mass();
    double energy_smeared = TMath::Sqrt(px_smeared*px_smeared + py_smeared*py_smeared + pz_smeared*pz_smeared + mass_smeared*mass_smeared);   
    reco::Candidate::LorentzVector p4_smeared(px_smeared, py_smeared, pz_smeared, energy_smeared);
    genHadRecoil_smeared.setP4(p4_smeared);

    if ( verbosity_ >= 1 ) {
      std::cout << "genHadRecoil: Px = " << genHadRecoil->px() << ", Py = " << genHadRecoil->py() << ", Pz = " << genHadRecoil->pz() << "," 
		<< " mass = " << genHadRecoil->mass() << std::endl;
      std::cout << "genHadRecoil(smeared): Px = " << genHadRecoil_smeared.px() << ", Py = " << genHadRecoil_smeared.py() << ", Pz = " << genHadRecoil_smeared.pz() << "," 
		<< " mass = " << genHadRecoil_smeared.mass() << std::endl;
    }

    svFitMEM::GenHadRecoil::CovMatrix cov;
    for ( int idxRow = 0; idxRow < 4; ++idxRow ) {
      for ( int idxColumn = 0; idxColumn < 4; ++idxColumn ) {
	if      ( idxRow == 0 && idxColumn == 0 ) cov[idxRow][idxColumn] = sigmaPx_*sigmaPx_;
	else if ( idxRow == 1 && idxColumn == 1 ) cov[idxRow][idxColumn] = sigmaPy_*sigmaPy_;
	else if ( idxRow == 2 && idxColumn == 2 ) cov[idxRow][idxColumn] = sigmaPz_*sigmaPz_;
	else if ( idxRow == 3 && idxColumn == 3 ) cov[idxRow][idxColumn] = sigmaPx_*sigmaPx_ + sigmaPy_*sigmaPy_ + sigmaPz_*sigmaPz_ + sigmaMass_*sigmaMass_;
	else                                      cov[idxRow][idxColumn] = 0.;
      }
    }
    genHadRecoil_smeared.setSignificanceMatrix(cov);

    genHadRecoils_smeared->push_back(genHadRecoil_smeared);
  }

  evt.put(genHadRecoils_smeared);
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(SmearedHadRecoilProducer);
