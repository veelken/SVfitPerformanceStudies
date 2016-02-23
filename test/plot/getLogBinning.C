TArrayD getLogBinning(double xMin, double xMax, int numBins)
{
  TArrayD binning(numBins + 1);
  double log_xMin = TMath::Log(xMin);
  double log_xMax = TMath::Log(xMax);
    for ( int idxBin = 0; idxBin <= numBins; ++idxBin ) {
      double log_x = log_xMin + idxBin*(log_xMax - log_xMin)/numBins;
      binning[idxBin] = TMath::Exp(log_x);
      //std::cout << "bin #" << idxBin << " log(x) = " << log_x << ", x = " << binning[idxBin] << std::endl;
    }
  return binning;
}


