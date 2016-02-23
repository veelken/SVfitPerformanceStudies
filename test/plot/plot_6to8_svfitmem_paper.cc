#include "func.C"


void plot_6to8_svfitmem_paper(){

  // plot histogram
  cout<<"plotting hist...\n";

  //string savePath {"/home/calpas/svfitMEM/CMSSW_7_4_15_patch1/src/TauAnalysis/SVfitPerformanceStudies/test/plot/"};
  string savePath {"/afs/cern.ch/user/c/calpas/www/"};

  // root file
  vector<string> vinput {
    "hist_DYJetsToLLM50_all.root",
    "hist_GluGluHToTauTauM125_all.root",
    "hist_SUSYGluGluToHToTauTauM200_all.root",
    "hist_SUSYGluGluToHToTauTauM300_all.root",
    "hist_SUSYGluGluToHToTauTauM500_all.root",
    "hist_SUSYGluGluToHToTauTauM800_all.root",
  }; 

  func();

  bool log{1};
  int numbin{25};

  vector<string>vdir{"emu", "hadhad" ,"muhad"};
  vector<string>vdirleg{"e#mu", "#tau_{h}#tau_{h}" ,"#mu#tau_{h}"};

  int ndir{static_cast<int>(vdir.size())};
  //
  TLegend *legend1[ndir];
  TLegend *legend2[ndir];
  TLegend *legend3[ndir];
  TLegend *legend4[ndir];
  TLegend *legend5[ndir];
  TLegend *legend6[ndir];

  for(int i=0; i<ndir; i++){
    legend1[i] = new TLegend( 0.62, 0.55, 0.9, 0.9, NULL,"brNDC"); 
    //legend1[i] = new TLegend( 0.2, 0.40, 0.45, 0.9, NULL,"brNDC"); 
    legend1[i]->SetTextSize(0.04);
  }


  TCanvas *canvas[ndir];

  for(int i=0; i<ndir; i++){
    canvas[i] = new TCanvas(vdir[i].c_str(), vdir[i].c_str(), 900, 700); 
    canvas[i]->Divide(2, 3);

    canvas[i]->cd(1);
    if(log) gPad->SetLogx();
    gPad->SetLogy();

    canvas[i]->cd(2);
    if(log) gPad->SetLogx();
    gPad->SetLogy();

    canvas[i]->cd(3);
    if(log) gPad->SetLogx();
    gPad->SetLogy();

    canvas[i]->cd(4);
    if(log) gPad->SetLogx();
    gPad->SetLogy();

    canvas[i]->cd(5);
    if(log) gPad->SetLogx();
    gPad->SetLogy();

    canvas[i]->cd(6);
    if(log) gPad->SetLogx();
    gPad->SetLogy();

  }


  vector<TH1D*> vhmass;
  string header;
  string imagepng;
  string imageroot;

  // loop over directories
  for(int i=0; i<ndir; i++){
    cout<<"\ndir: "<<vdir[i]<<endl;

    // loop over input files
    for (int in=0; in<vinput.size(); in++){ 
      string input{vinput[in]};
      TFile *file = new TFile(input.c_str(), "READ");
      cout<<"input: "<<input<<endl;

      // extract sample name
      string sample{input};
      sample.replace(0, sample.find_first_of("_")+1, "");
      sample.replace(sample.find_first_of("_"), sample.find_last_of("t"), "");
      cout<<"sample: "<<sample<<endl;

      // loop over hist
      TIter nextHist(file->GetListOfKeys());
      TKey* histKey(0);
      while ((histKey=(TKey*)nextHist())) {
	if (strcmp(histKey->GetClassName(),"TH1D")!=0) continue;
	TH1D* hmass = (TH1D*)histKey->ReadObj();
	string histname(hmass->GetName());
	// hist name match directory name
	if(histname.find(vdir[i])==std::string::npos) continue; 
	// only smeared
	if(histname.find("_gen_")!=std::string::npos) continue; 
	if(log) {
	  if(histname.find("_log_")==std::string::npos) continue; 
	}
	else { if(histname.find("_lin_")==std::string::npos) continue; }
	cout<<"\nhistname: "<<histname<<endl;

	vhmass.push_back((TH1D*)hmass->Clone());
	vhmass.back()->SetLineWidth(2);
	vhmass.back()->GetYaxis()->SetRangeUser(0.0001, 0.05);

        //cout<<vhmass.back()->GetName()<<": "<<vhmass.back()->Integral()<<endl;
        cout<<"integral: "<<vhmass.back()->Integral()<<endl;
        cout<<"mean: "<<vhmass.back()->GetMean()<<endl;
        cout<<"mean/RMS: "<<vhmass.back()->GetMean()/vhmass.back()->GetRMS()<<endl;

	for(int j=0; j<vhmass.back()->GetNbinsX(); j++){
	  vhmass.back()->SetBinContent(j+1, vhmass.back()->GetBinContent(j+1)/vhmass.back()->GetBinWidth(j+1));
	  vhmass.back()->SetBinError(j+1, vhmass.back()->GetBinError(j+1)/vhmass.back()->GetBinWidth(j+1));
	}


	if     (histname.find("ca")!=std::string::npos)          {vhmass.back()->SetLineStyle(6); vhmass.back()->SetLineColor(kGreen); }

	else if(histname.find("svFit")!=std::string::npos)       {vhmass.back()->SetLineStyle(2); vhmass.back()->SetLineColor(kBlue); }

	else if(histname.find("svfitmemtfk0")!=std::string::npos){vhmass.back()->SetLineStyle(3); vhmass.back()->SetLineColor(kMagenta); }

	else if(histname.find("svfitmemtfk2")!=std::string::npos ||
	    histname.find("svfitmemtfk3")!=std::string::npos){vhmass.back()->SetLineStyle(1); vhmass.back()->SetLineColor(kRed);}


	if( vdir[i]=="emu"){
	  if( histname.find("_ca")!=std::string::npos || 
	      histname.find("_svFit")!=std::string::npos ||
	      histname.find("_svfitmemtfk0")!=std::string::npos || 
	      histname.find("_svfitmemtfk2")!=std::string::npos ){

	    if ( input.find("M50_")!=std::string::npos){ 
	      header = vdirleg[i] + "    Z#rightarrow#tau#tau";
	      legend1[i]->SetHeader(header.c_str());
	      if     (histname.find("_ca")!=std::string::npos) 	  	 legend1[i]->AddEntry( vhmass.back(), "m_{ca}", "l");
	      else if(histname.find("_svFit")!=std::string::npos)        legend1[i]->AddEntry( vhmass.back(), "SVfit", "l");
	      else if(histname.find("_svfitmemtfk0")!=std::string::npos) legend1[i]->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 0", "l");
	      else if(histname.find("_svfitmemtfk2")!=std::string::npos) legend1[i]->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 2", "l");

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (125 GeV)";
	      legend2[i]=(TLegend*)legend1[i]->Clone();
	      legend2[i]->SetHeader(header.c_str());

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (200 GeV)";
	      legend3[i]=(TLegend*)legend1[i]->Clone();
	      legend3[i]->SetHeader(header.c_str());

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (300 GeV)";
	      legend4[i]=(TLegend*)legend1[i]->Clone();
	      legend4[i]->SetHeader(header.c_str());

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (500 GeV)";
	      legend5[i]=(TLegend*)legend1[i]->Clone();
	      legend5[i]->SetHeader(header.c_str());

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (800 GeV)";
	      legend6[i]=(TLegend*)legend1[i]->Clone();
	      legend6[i]->SetHeader(header.c_str());

	    }
	    if(input.find("M50_")!=std::string::npos)  {canvas[i]->cd(1); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend1[i]->Draw("same");}
	    if(input.find("M125_")!=std::string::npos) {canvas[i]->cd(2); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend2[i]->Draw("same");}
	    if(input.find("M200_")!=std::string::npos) {canvas[i]->cd(3); /*pad5[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend3[i]->Draw("same");}
	    if(input.find("M300_")!=std::string::npos) {canvas[i]->cd(4); /*pad7[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend4[i]->Draw("same");}
	    if(input.find("M500_")!=std::string::npos) {canvas[i]->cd(5); /*pad7[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend5[i]->Draw("same");}
	    if(input.find("M800_")!=std::string::npos) {canvas[i]->cd(6); /*pad7[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend6[i]->Draw("same");}
	  } 
/*
	  else if( histname.find("_divca")!=std::string::npos || 
	      histname.find("_divsvFit")!=std::string::npos ||
	      histname.find("_divsvfitmemtfk0")!=std::string::npos || 
	      histname.find("_divsvfitmemtfk2")!=std::string::npos ){

	    if(input.find("M50_")!=std::string::npos)  {canvas[i]->cd(1); pad2[i]->cd(); vhmass.back()->Draw("same");}
	    if(input.find("M125_")!=std::string::npos) {canvas[i]->cd(2); pad4[i]->cd(); vhmass.back()->Draw("same");}
	    if(input.find("M200_")!=std::string::npos) {canvas[i]->cd(3); pad6[i]->cd(); vhmass.back()->Draw("same");}
	    if(input.find("M300_")!=std::string::npos) {canvas[i]->cd(4); pad8[i]->cd(); vhmass.back()->Draw("same");}
	  } 
*/
	}
	else { 
	  if( histname.find("_ca")!=std::string::npos || 
	      histname.find("_svFit")!=std::string::npos ||
	      histname.find("_svfitmemtfk0")!=std::string::npos || 
	      histname.find("_svfitmemtfk3")!=std::string::npos ){

	    if ( input.find("M50_")!=std::string::npos){ 
	      header = vdirleg[i] + "    Z#rightarrow#tau#tau";
	      legend1[i]->SetHeader(header.c_str());
	      if     (histname.find("_ca")!=std::string::npos) 	  legend1[i]->AddEntry( vhmass.back(), "m_{ca}", "l");
	      else if(histname.find("_svFit")!=std::string::npos)        legend1[i]->AddEntry( vhmass.back(), "SVfit", "l");
	      else if(histname.find("_svfitmemtfk0")!=std::string::npos) legend1[i]->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 0", "l");
	      else if(histname.find("_svfitmemtfk3")!=std::string::npos) legend1[i]->AddEntry( vhmass.back(), "SVfitMEM, #kappa = 3", "l");

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (125 GeV)";
	      legend2[i]=(TLegend*)legend1[i]->Clone();
	      legend2[i]->SetHeader(header.c_str());

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (200 GeV)";
	      legend3[i]=(TLegend*)legend1[i]->Clone();
	      legend3[i]->SetHeader(header.c_str());

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (300 GeV)";
	      legend4[i]=(TLegend*)legend1[i]->Clone();
	      legend4[i]->SetHeader(header.c_str());

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (500 GeV)";
	      legend5[i]=(TLegend*)legend1[i]->Clone();
	      legend5[i]->SetHeader(header.c_str());

	      header = vdirleg[i] + "    H#rightarrow#tau#tau (800 GeV)";
	      legend6[i]=(TLegend*)legend1[i]->Clone();
	      legend6[i]->SetHeader(header.c_str());

	    }

	  if(input.find("M50_")!=std::string::npos)  {canvas[i]->cd(1); /*pad1[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend1[i]->Draw("same");}
	  if(input.find("M125_")!=std::string::npos) {canvas[i]->cd(2); /*pad3[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend2[i]->Draw("same");}
	  if(input.find("M200_")!=std::string::npos) {canvas[i]->cd(3); /*pad5[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend3[i]->Draw("same");}
	  if(input.find("M300_")!=std::string::npos) {canvas[i]->cd(4); /*pad7[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend4[i]->Draw("same");}
	  if(input.find("M500_")!=std::string::npos) {canvas[i]->cd(5); /*pad7[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend5[i]->Draw("same");}
	  if(input.find("M800_")!=std::string::npos) {canvas[i]->cd(6); /*pad7[i]->cd();*/ vhmass.back()->Draw("same&hist"); legend6[i]->Draw("same");}
	}
/*
	else if( histname.find("_divca")!=std::string::npos || 
	    histname.find("_divsvFit")!=std::string::npos ||
	    histname.find("_divsvfitmemtfk0")!=std::string::npos || 
	    histname.find("_divsvfitmemtfk3")!=std::string::npos ){

	  if(input.find("M50_")!=std::string::npos)  {canvas[i]->cd(1); pad2[i]->cd(); vhmass.back()->Draw("same");}
	  if(input.find("M125_")!=std::string::npos) {canvas[i]->cd(2); pad4[i]->cd(); vhmass.back()->Draw("same");}
	  if(input.find("M200_")!=std::string::npos) {canvas[i]->cd(3); pad6[i]->cd(); vhmass.back()->Draw("same");}
	  if(input.find("M300_")!=std::string::npos) {canvas[i]->cd(4); pad8[i]->cd(); vhmass.back()->Draw("same");}
	}
*/

      } // else

    } // while hist
  } // input file
} // dir

//save canvas
for(int i=0; i<ndir; i++){
  if(log){ 
    imagepng = savePath+"plot_6to8_log_"+canvas[i]->GetName()+".png";
    imageroot = savePath+"plot_6to8_log_"+canvas[i]->GetName()+".root";
  }
  else {
    imagepng = savePath+"plot_6to8_lin_"+canvas[i]->GetName()+".png";
    imageroot = savePath+"plot_6to8_lin_"+canvas[i]->GetName()+".root";
  }
  canvas[i]->Print(imagepng.c_str()); 
  canvas[i]->Print(imageroot.c_str()); 
} 

} // void


