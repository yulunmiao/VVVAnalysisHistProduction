#include "Color.h"
#define NAME "htotal"
#define NBIN 1

int CR_ttbar_total(){
	gStyle->SetOptStat(0);
	//ttbar
	TFile *fttbar = new TFile("../hist/CR_ttbar/httbar.root");
	TH1F *httbar = new TH1F("","",1,1,0);
	httbar = (TH1F*) fttbar->Get(NAME);
	httbar->Draw();
	cout<<"ttbar	"<<httbar->GetBinContent(1)<<"	"<<httbar->GetBinError(1)<<endl;
	httbar->SetFillColor(cBlue);
	//ttbar
	//WZ
	TFile *fWZ = new TFile("../hist/CR_ttbar/hWZ.root");
        TH1F *hWZ = (TH1F*) fWZ->Get(NAME);
        cout<<"WZ	"<<hWZ->GetBinContent(1)<<"	"<<hWZ->GetBinError(1)<<endl;
	hWZ->SetFillColor(cViolet);
	//WZ
	//Wjets
	TFile *fWjets = new TFile("../hist/CR_ttbar/hWjets.root");
        TH1F *hWjets = (TH1F*) fWjets->Get(NAME);
        cout<<"Wjets	"<<hWjets->GetBinContent(1)<<"	"<<hWjets->GetBinError(1)<<endl;
	hWjets->SetFillColor(kCyan);
	//Wjets
	//WW
	TFile *fWW = new TFile("../hist/CR_ttbar/hWW.root");
        TH1F *hWW = (TH1F*) fWW->Get(NAME);
        cout<<"WW	"<<hWW->GetBinContent(1)<<"	"<<hWW->GetBinError(1)<<endl;
	hWW->SetFillColor(kRed);
	//WW
	//ttW
	TFile *fttW = new TFile("../hist/CR_ttbar/httW.root");
        TH1F *httW = (TH1F*) fttW->Get(NAME);
        cout<<"ttW	"<<httW->GetBinContent(1)<<"	"<<httW->GetBinError(1)<<endl;
	httW->SetFillColor(cOrange);
	//ttW
	//ttZ
	TFile *fttZ = new TFile("../hist/CR_ttbar/httZ.root");
        TH1F *httZ = (TH1F*) fttZ->Get(NAME);
        cout<<"ttZ	"<<httZ->GetBinContent(1)<<"	"<<httZ->GetBinError(1)<<endl;
	httZ->SetFillColor(cBrown);
	//ttZ
	//ZZ
	TFile *fZZ = new TFile("../hist/CR_ttbar/hZZ.root");
        TH1F *hZZ = (TH1F*) fZZ->Get(NAME);
        cout<<"ZZ	"<<hZZ->GetBinContent(1)<<"	"<<hZZ->GetBinError(1)<<endl;
	hZZ->SetFillColor(kViolet);
	//ZZ
	//DY
	TFile *fDY = new TFile("../hist/CR_ttbar/hDY.root");
        TH1F *hDY = (TH1F*) fDY->Get(NAME);
        cout<<"DY	"<<hDY->GetBinContent(1)<<"	"<<hDY->GetBinError(1)<<endl;
	hDY->SetFillColor(kYellow);
	//DY
	/*
	//WWW
	TFile *fWWW = new TFile("../hist/CR_ttbar/hWWW.root");
        TH1F *hWWW = (TH1F*) fWWW->Get(NAME);
	hWWW->SetLineColor(kRed);
        cout<<"WWW	"<<hWWW->GetBinContent(1)<<"	"<<hWWW->GetBinError(1)<<endl;
	//WWW
	*/
	TFile *fTTTT = new TFile("../hist/CR_ttbar/hTTTT.root");
        TH1F *hTTTT = (TH1F*) fTTTT->Get(NAME);
        hTTTT->SetFillColor(kOrange);
        cout<<"TTTT	"<<hTTTT->GetBinContent(1)<<"	"<<hTTTT->GetBinError(1)<<endl;

	//data
	TFile *fdata= new TFile("../hist/CR_ttbar/hdata.root");
	TH1F *hdata = (TH1F*) fdata->Get(NAME);
	hdata->SetMarkerStyle(8);
        hdata->SetMarkerColor(1);
        cout<<"data	"<<hdata->GetBinContent(1)<<"	"<<hdata->GetBinError(1)<<endl;
	//data
	
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
	hs->Add(hTTTT);
	l->AddEntry(httbar,"t#bar{t}","f");
	l->AddEntry(httW,"ttW","f");
        l->AddEntry(httZ,"ttZ","f");
        l->AddEntry(hDY,"DY","f");
        l->AddEntry(hWZ,"WZ","f");
        l->AddEntry(hWW,"WW","f");
        l->AddEntry(hZZ,"ZZ","f");
        l->AddEntry(hWjets,"W+jets","f");
	l->AddEntry(hTTTT,"TTTT","f");

	TH1F *hbkg=new TH1F;
	TH1F *hratio=new TH1F;
	*hbkg=*httbar+*httW+*httZ+*hDY+*hWZ+*hWW+*hZZ+*hWjets+*hTTTT;

	cout<<"MC     "<<hbkg->GetBinContent(1)<<"   "<<hbkg->GetBinError(1)<<endl;

	*hratio=*hdata / *hbkg;

	//bkg
	/*
	//signal
	l->AddEntry(hWWW,"hWWW","l");
	hWWW->Draw("hist same");
	//signal
	*/
	
	//data
	l->AddEntry(hdata,"hdata");
	//data
        TCanvas *c=new TCanvas();

        TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
        pad1->Draw();
        pad1->cd();
        
	hbkg->GetYaxis()->SetNdivisions(505);
        hbkg->GetYaxis()->SetTitleSize(20);
        hbkg->GetYaxis()->SetTitleFont(43);
        hbkg->GetYaxis()->SetLabelFont(43);
        hbkg->GetYaxis()->SetLabelSize(15);
        hbkg->GetXaxis()->SetLabelSize(0);
	hs->SetHistogram(hbkg);
	hs->Draw("hist");
        hdata->Draw("same ex0");        
	l->Draw();
   	c->cd();
   	TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
     	pad2->Draw();
	pad2->cd();
	hratio->SetTitle(";;data/MC");
     	hratio->GetYaxis()->SetNdivisions(505);
	hratio->GetYaxis()->SetTitleOffset(1.1);
   	hratio->GetYaxis()->SetTitleSize(20);
   	hratio->GetYaxis()->SetTitleFont(43);
   	hratio->GetYaxis()->SetLabelFont(43);
   	hratio->GetYaxis()->SetLabelSize(15);
   	hratio->GetXaxis()->SetTitleSize(20);
   	hratio->GetXaxis()->SetTitleFont(43);
   	hratio->GetXaxis()->SetLabelFont(43);
   	hratio->GetXaxis()->SetLabelSize(15);
	hratio->Draw("ex0");
	return 0;
}
