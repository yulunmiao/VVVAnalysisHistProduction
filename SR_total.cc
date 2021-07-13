#include "Color.h"
#define NAME "total"
#define NBIN 1

int SR_total(){
	//ttbar
	TFile *fttbar = new TFile("../hist/SR/httbar.root");
	TH1F *httbar = new TH1F("","",1,1,0);
	httbar = (TH1F*) fttbar->Get(NAME);
	httbar->Draw();
	cout<<"ttbar	"<<httbar->GetBinContent(1)<<"	"<<httbar->GetBinError(1)<<endl;
	httbar->SetFillColor(cBlue);
	//ttbar
	//WZ
	TFile *fWZ = new TFile("../hist/SR/hWZ.root");
        TH1F *hWZ = (TH1F*) fWZ->Get(NAME);
        cout<<"WZ	"<<hWZ->GetBinContent(1)<<"	"<<hWZ->GetBinError(1)<<endl;
	hWZ->SetFillColor(cViolet);
	//WZ
	//Wjets
	TFile *fWjets = new TFile("../hist/SR/hWjets.root");
        TH1F *hWjets = (TH1F*) fWjets->Get(NAME);
        cout<<"Wjets	"<<hWjets->GetBinContent(1)<<"	"<<hWjets->GetBinError(1)<<endl;
	hWjets->SetFillColor(kCyan);
	//Wjets
	//WW
	TFile *fWW = new TFile("../hist/SR/hWW.root");
        TH1F *hWW = (TH1F*) fWW->Get(NAME);
        cout<<"WW	"<<hWW->GetBinContent(1)<<"	"<<hWW->GetBinError(1)<<endl;
	hWW->SetFillColor(kRed);
	//WW
	//ttW
	TFile *fttW = new TFile("../hist/SR/httW.root");
        TH1F *httW = (TH1F*) fttW->Get(NAME);
        cout<<"ttW	"<<httW->GetBinContent(1)<<"	"<<httW->GetBinError(1)<<endl;
	httW->SetFillColor(cOrange);
	//ttW
	//ttZ
	TFile *fttZ = new TFile("../hist/SR/httZ.root");
        TH1F *httZ = (TH1F*) fttZ->Get(NAME);
        cout<<"ttZ	"<<httZ->GetBinContent(1)<<"	"<<httZ->GetBinError(1)<<endl;
	httZ->SetFillColor(cBrown);
	//ttZ
	//ZZ
	TFile *fZZ = new TFile("../hist/SR/hZZ.root");
        TH1F *hZZ = (TH1F*) fZZ->Get(NAME);
        cout<<"ZZ	"<<hZZ->GetBinContent(1)<<"	"<<hZZ->GetBinError(1)<<endl;
	hZZ->SetFillColor(kViolet);
	//ZZ
	//DY
	TFile *fDY = new TFile("../hist/SR/hDY.root");
        TH1F *hDY = (TH1F*) fDY->Get(NAME);
        cout<<"DY	"<<hDY->GetBinContent(1)<<"	"<<hDY->GetBinError(1)<<endl;
	hDY->SetFillColor(kYellow);
	//DY
	//WWW
	TFile *fWWW = new TFile("../hist/SR/hWWW.root");
        TH1F *hWWW = (TH1F*) fWWW->Get(NAME);
	hWWW->SetLineColor(kRed);
        cout<<"WWW	"<<hWWW->GetBinContent(1)<<"	"<<hWWW->GetBinError(1)<<endl;
	//WWW
	/*
	//data
	TFile *fdata= new TFile("../hist/SR/hdata.root");
	TH1F *hdata = (TH1F*) fdata->Get(NAME);
	hdata->SetMarkerStyle(8);
        hdata->SetMarkerColor(1);
        cout<<"data	"<<hdata->GetBinContent(1)<<"	"<<hdata->GetBinError(1)<<endl;
	//data
	*/
        THStack *hs=new THStack("",";;N/Events");
        TLegend *l=new TLegend(0.9,0.6,1.,0.85);

	//bkg
	hs->Add(httbar);
	hs->Add(httW);
	hs->Add(httZ);
	hs->Add(hDY);
	hs->Add(hWZ);
	hs->Add(hWW);
	hs->Add(hZZ);
	hs->Add(hWjets);
	l->AddEntry(httbar,"t#bar{t}","f");
	l->AddEntry(httW,"ttW","f");
        l->AddEntry(httZ,"ttZ","f");
        l->AddEntry(hDY,"DY","f");
        l->AddEntry(hWZ,"WZ","f");
        l->AddEntry(hWW,"WW","f");
        l->AddEntry(hZZ,"ZZ","f");
        l->AddEntry(hWjets,"W+jets","f");
	hs->Draw("hist");
	TH1F *hbkg=new TH1F;
	*hbkg=*httbar+*httW+*httZ+*hDY+*hWZ+*hWW+*hZZ+*hWjets;
	cout<<"bkg	"<<hbkg->GetBinContent(1)<<"	"<<hbkg->GetBinError(1)<<endl;

	//bkg
	
	//signal
	l->AddEntry(hWWW,"hWWW","l");
	hWWW->Draw("hist same");
	//signal
	/*
	//data
	l->AddEntry(hdata,"hdata");
	hdata->Draw("ex0 same");
	//data
	*/

	l->Draw();
	return 0;
}
