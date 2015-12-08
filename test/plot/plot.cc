void plot(){

  // plot histogram
  cout<<"plotting hist...\n";
  string output {"Plot_svFitStudyNtuple_SUSYGluGluToHToTauTauM300_all.root"}; 
  TFile *file = new TFile(output.c_str(), "READ");

  string mass{"Higgs 300 GeV to "};

  TH1D *haxisk0_log = new TH1D("", "", 100, 0.0001, 1500);
  haxisk0_log->SetTitle("K0");
  haxisk0_log->SetStats(false);
  haxisk0_log->GetXaxis()->SetRangeUser(0, 1500);
  haxisk0_log->GetYaxis()->SetRangeUser(0.0001, 1);
  haxisk0_log->GetXaxis()->SetTitleOffset(1.2);
  haxisk0_log->GetYaxis()->SetTitleOffset(1.3);
  haxisk0_log->GetXaxis()->SetTitle("m[GeV]");
  haxisk0_log->GetYaxis()->SetTitle("1/dm[1/GeV]");

  TH1D *haxisk5_log = new TH1D("", "", 100, 0.0001, 1500);
  haxisk5_log->SetTitle("K5");
  haxisk5_log->SetStats(false);
  haxisk5_log->GetXaxis()->SetRangeUser(0, 1500);
  haxisk5_log->GetYaxis()->SetRangeUser(0.0001, 1);
  haxisk5_log->GetXaxis()->SetTitleOffset(1.2);
  haxisk5_log->GetYaxis()->SetTitleOffset(1.3);
  haxisk5_log->GetXaxis()->SetTitle("m[GeV]");
  haxisk5_log->GetYaxis()->SetTitle("1/dm[1/GeV]");

  TH1D *haxisk0_lin = new TH1D("", "", 100, 0.0001, 1500);
  haxisk0_lin->SetTitle("K0");
  haxisk0_lin->SetStats(false);
  haxisk0_lin->GetXaxis()->SetRangeUser(0, 1500);
  haxisk0_lin->GetYaxis()->SetRangeUser(0, 0.5);
  haxisk0_lin->GetXaxis()->SetTitleOffset(1.2);
  haxisk0_lin->GetYaxis()->SetTitleOffset(1.3);
  haxisk0_lin->GetXaxis()->SetTitle("m[GeV]");
  haxisk0_lin->GetYaxis()->SetTitle("1/dm[1/GeV]");

  TH1D *haxisk5_lin = new TH1D("", "", 100, 0.0001, 1500);
  haxisk5_lin->SetTitle("K5");
  haxisk5_lin->SetStats(false);
  haxisk5_lin->GetXaxis()->SetRangeUser(0, 1500);
  haxisk5_lin->GetYaxis()->SetRangeUser(0, 0.5);
  haxisk5_lin->GetXaxis()->SetTitleOffset(1.2);
  haxisk5_lin->GetYaxis()->SetTitleOffset(1.3);
  haxisk5_lin->GetXaxis()->SetTitle("m[GeV]");
  haxisk5_lin->GetYaxis()->SetTitle("1/dm[1/GeV]");

  vector<string>vsample{"emu", "hadhad" ,"muhad"};
  vector<string>vlegend{"gen_TF", "gen_noTF", "smeared_TF", "smeared_noTF"};

  map<string, vector<TH1D*>> map_sample_hmass;
  vector<TH1D*> vhmass;

  int nhist{12};
  TPaveStats *paveStatK0[nhist];
  TPaveStats *paveStatK5[nhist];

  int nsample{static_cast<int>(vsample.size())};
  TCanvas *c[nsample];
  TLegend *legend[nsample];

  for(int i=0; i<nsample; i++){
    c[i] = new TCanvas(vsample[i].c_str(), vsample[i].c_str(), 1200, 750);
    c[i]->Divide(2,2);
    c[i]->cd(1);
    haxisk0_lin->Draw();
    c[i]->cd(2);
    haxisk5_lin->Draw();
    c[i]->cd(3);
    gPad->SetLogy();
    haxisk0_log->Draw();
    c[i]->cd(4);
    gPad->SetLogy();
    haxisk5_log->Draw();
    //
    //legend[i] = new TLegend( 0.65, 0.6, 0.9, 0.9, NULL,"brNDC");
    legend[i] = new TLegend( 0.5, 0.55, 0.75, 0.9, NULL,"brNDC");
    legend[i]->SetTextSize(0.034);
  }

  gStyle->SetOptStat("RM");

  int npaveStatK0{0};
  int npaveStatK5{0};

  for(int i=0; i<nsample; i++){

    cout<<"\nsample: "<<vsample[i]<<endl;

    TIter nextHist(file->GetListOfKeys());
    TKey* histKey(0);
    while ((histKey=(TKey*)nextHist())) {
      if (strcmp(histKey->GetClassName(),"TH1D")!=0) continue;
      TH1D* hmass = (TH1D*)histKey->ReadObj();
      string histname(hmass->GetName());
      if(histname.find(vsample[i])==std::string::npos) continue; // histogram
      cout<<"histname: "<<histname<<endl;

      // legend array [for each sample]
      string header {mass+vsample[i]};
      legend[i]->SetHeader(header.c_str());
      if     (histname.find("gen_tf_k0")!=std::string::npos)      legend[i]->AddEntry( hmass, vlegend[0].c_str(), "lp");
      else if(histname.find("gen_notf_k0")!=std::string::npos)    legend[i]->AddEntry( hmass, vlegend[1].c_str(), "lp");
      else if(histname.find("smeared_tf_k0")!=std::string::npos)  legend[i]->AddEntry( hmass, vlegend[2].c_str(), "lp");
      else if(histname.find("smeared_notf_k0")!=std::string::npos)legend[i]->AddEntry( hmass, vlegend[3].c_str(), "lp");

      TIter nextHistCut(file->GetListOfKeys());
      TKey* histKeyCut(0);
      while ((histKeyCut=(TKey*)nextHistCut())) {
	if (strcmp(histKeyCut->GetClassName(),"TH1I")!=0) continue;
	TH1I* hcut = (TH1I*)histKeyCut->ReadObj();
	string histnamecut(hcut->GetName());
        if(histname.find(histnamecut)==std::string::npos) continue;
	cout<<"histnamescale: "<<histnamecut<<endl;

	//
	vhmass.push_back((TH1D*)hmass->Clone());
	vhmass.back()->SetStats(kTRUE);
	if(hcut->Integral()!=0) vhmass.back()->Scale(1/hcut->Integral());
        cout<<"vhmass size: "<<vhmass.size()<<endl;


	// canvas array [for each sample]
	if (histname.find("k0")!=std::string::npos){
	  c[i]->cd(1); vhmass.back()->Draw("sames&e1&l&c"); legend[i]->Draw("sames&e1&l&c"); gPad->Modified(); gPad->Update();
	  c[i]->cd(3); vhmass.back()->Draw("sames&e1&l&c"); legend[i]->Draw("sames&e1&l&c"); gPad->Modified(); gPad->Update();
	}
	else { 
	  c[i]->cd(2); vhmass.back()->Draw("sames&e1&l&c"); legend[i]->Draw("sames&e1&l&c"); gPad->Modified(); gPad->Update();
	  c[i]->cd(4); vhmass.back()->Draw("sames&e1&l&c"); legend[i]->Draw("sames&e1&l&c"); gPad->Modified(); gPad->Update();
	}

	// TPaveStats array [for each histogram]
	paveStatK5[npaveStatK5]=(TPaveStats*)vhmass.back()->FindObject("stats");
	paveStatK5[npaveStatK5]->SetLineColor(vhmass.back()->GetLineColor());
	paveStatK5[npaveStatK5]->SetLineStyle(vhmass.back()->GetLineStyle());
	paveStatK5[npaveStatK5]->SetLineWidth(vhmass.back()->GetLineWidth());
	if (histname.find("k0")!=std::string::npos){
	  //cout<<"npaveStatK0: "<<npaveStatK0<<endl;
	  //
	  if(npaveStatK0==0 || npaveStatK0==4 || npaveStatK0==8 ){ 
	    paveStatK0[npaveStatK0]=(TPaveStats*)vhmass.back()->FindObject("stats");
	    paveStatK0[npaveStatK0]->SetLineColor(vhmass.back()->GetLineColor());
	    paveStatK0[npaveStatK0]->SetLineStyle(vhmass.back()->GetLineStyle());
	    paveStatK0[npaveStatK0]->SetLineWidth(vhmass.back()->GetLineWidth());
            //cout<<"Yhight: "<<paveStatK0[npaveStatK0]->GetY2NDC()<<endl;
            //cout<<"Ylow: "<<paveStatK0[npaveStatK0]->GetY1NDC()<<endl;
	  }
	  else{
	    paveStatK0[npaveStatK0]=(TPaveStats*)vhmass.back()->FindObject("stats");
	    paveStatK0[npaveStatK0]->SetLineColor(vhmass.back()->GetLineColor());
	    paveStatK0[npaveStatK0]->SetLineStyle(vhmass.back()->GetLineStyle());
	    paveStatK0[npaveStatK0]->SetLineWidth(vhmass.back()->GetLineWidth());
	    //
	    double delta{paveStatK0[npaveStatK0]->GetY2NDC() - paveStatK0[npaveStatK0]->GetY1NDC()};
	    paveStatK0[npaveStatK0]->SetY2NDC(paveStatK0[npaveStatK0-1]->GetY1NDC() );
	    paveStatK0[npaveStatK0]->SetY1NDC(paveStatK0[npaveStatK0-1]->GetY1NDC()-delta );
            //cout<<"Yhight: "<<paveStatK0[npaveStatK0]->GetY2NDC()<<endl;
            //cout<<"Ylow: "<<paveStatK0[npaveStatK0]->GetY1NDC()<<endl;
	  }
	  npaveStatK0++;
	}
	else{
	  //cout<<"npaveStatK5: "<<npaveStatK5<<endl;
	  //
	  if(npaveStatK5==0 || npaveStatK5==4 || npaveStatK5==8 ){ 
	    paveStatK5[npaveStatK5]=(TPaveStats*)vhmass.back()->FindObject("stats");
	    paveStatK5[npaveStatK5]->SetLineColor(vhmass.back()->GetLineColor());
	    paveStatK5[npaveStatK5]->SetLineStyle(vhmass.back()->GetLineStyle());
	    paveStatK5[npaveStatK5]->SetLineWidth(vhmass.back()->GetLineWidth());
	  }
	  else{
	    paveStatK5[npaveStatK5]=(TPaveStats*)vhmass.back()->FindObject("stats");
	    paveStatK5[npaveStatK5]->SetLineColor(vhmass.back()->GetLineColor());
	    paveStatK5[npaveStatK5]->SetLineStyle(vhmass.back()->GetLineStyle());
	    paveStatK5[npaveStatK5]->SetLineWidth(vhmass.back()->GetLineWidth());
	    //
	    double delta{paveStatK5[npaveStatK5]->GetY2NDC() - paveStatK5[npaveStatK5]->GetY1NDC()};
	    paveStatK5[npaveStatK5]->SetY2NDC(paveStatK5[npaveStatK5-1]->GetY1NDC() );
	    paveStatK5[npaveStatK5]->SetY1NDC(paveStatK5[npaveStatK5-1]->GetY1NDC()-delta );
	  }
	  npaveStatK5++;

	}

      } // while histscal
    } // while hist mass
  } // sample


  string savePath {"/home/calpas/svfitMEM/CMSSW_7_4_15_patch1/src/TauAnalysis/SVfitPerformanceStudies/test/"};

  for(int i=0; i<nsample; i++){

    // update canvas for box stat
    for( int j=0; j<4; j++)  { c[i]->cd(j+1);  gPad->Modified(); gPad->Update(); }

    //save canvas
    string image{savePath+"_plot_"+to_string(i)+".png"};

    c[i]->Print(image.c_str()); 
  }
}
