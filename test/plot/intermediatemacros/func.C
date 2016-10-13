// style for plots for CMS - to be addapted to official style

void func(){

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLabelFont(102,"xyz");
  gStyle->SetTitleFont(102);
  gStyle->SetTitleFont(102,"xyz");
  gStyle->SetStatFont(102);
  gStyle->SetOptFit(111);
  gStyle->SetOptTitle(0);
  gStyle->SetPaintTextFormat(".3f");

  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetCanvasColor(kWhite);  
  gStyle->SetOptStat(0); //don't show statistics box
  gStyle->SetTitleSize(0.05, "xyz"); 
  gStyle->SetLegendBorderSize(1);

  gStyle->SetPadTopMargin(0.1);
  //gStyle->SetPadBottomMargin(0.14);
  gStyle->SetPadBottomMargin(0.1);
  //gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);

  gROOT->ForceStyle();

  TH1::SetDefaultSumw2(kTRUE);	

}

double Median(const TH1D * h1) {
  int n = h1->GetXaxis()->GetNbins(); 
  std::vector<double>  x(n);
  h1->GetXaxis()->GetCenter( &x[0] );
  const double * y = h1->GetArray();
  // exclude underflow/overflows from bin content array y
  return TMath::Median(n, &x[0], &y[1]);
}

double AlternativeMedian(const TH1D * h1){
   double median;
   if ( h1->Integral() > 0. ) {
      double q[1];
      double probSum[1];
      probSum[0] = 0.50;
      (const_cast<TH1D*>(h1))->GetQuantiles(1, q, probSum);
      median = q[0];
   }else{
      median = 0.;
   }
   return median;
}

double rounded(double val)
{
  double decimal;
  double resultat;

  val*=1000;

  decimal=val-floor(val);
  if (decimal< 0.5) resultat=floor(val);
  else resultat=ceil(val);

  resultat/=1000;

  return resultat;
}
