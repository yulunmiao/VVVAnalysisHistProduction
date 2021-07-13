#include <TF1.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <TGraphAsymmErrors.h>
#include <TVector3.h>
#include <TGraph.h>
#include <TRandom.h>
#include <TMath.h>
#include <fstream>
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <THStack.h>
#include "Math/GenVector/LorentzVector.h"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "Math/GenVector/VectorUtil.h"
#include "Math/Point3D.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> > LV;

struct LepInfo{
        float pt;
        float eta;
        float phi;
	float tight;
};

struct FatJetInfo{
	float sdmass;
        float pt;
        float eta;
        float phi;
        float tau21;
        float tau2;
        float tau1;
        float deepMDW;
        float deepW;
	float deepMDZ;
        float deepZ;
        float deepT;
        float deepMDbb;
	float WPid;
};

struct JetInfo{
        float pt;
        float eta;
        float phi;
        bool passbloose;
        bool passbmedium;
        bool overlapwithfatjet;
};

struct Event{
	float scale;
        vector<LepInfo> lep;
        vector<FatJetInfo> fatjet;
        vector<JetInfo> jet;
	int run;
	unsigned long long event;
        float mll;
        float ht;
        float st;
	float deltaRll;
        float deltaphill;
	float njet_overlapremoved;
	float nbloose;
	float nbmedium;
};


class HistCollection{
        protected:
	TH1F* htotal;
        TH1F* hlep1pt;
        TH1F* hlep2pt;
        TH1F* hlep1eta;
        TH1F* hlep2eta;
        TH1F* hlep1phi;
        TH1F* hlep2phi;
        TH1F* hfatjetpt;
        TH1F* hfatjeteta;
        TH1F* hfatjetphi;
        TH1F* hfatjetsdmass;
        TH1F* hfatjettau1;
        TH1F* hfatjettau2;
        TH1F* hfatjettau21;
        TH1F* hfatjetdeepMDW;
        TH1F* hfatjetdeepW;
        TH1F* hfatjetdeepMDZ;
        TH1F* hfatjetdeepZ;
        TH1F* hfatjetdeepT;
        TH1F* hfatjetdeepMDbb;
        TH1F* hnlep;
        TH1F* hnjet;
	TH1F* hnjet_overlapremoved;
        TH1F* hnbloose;
	TH1F* hnbmedium;
        TH1F* hnfatjet;
        TH1F* hmll;
        TH1F* hst;
	TH1F* hht;
	TH1F* hdeltaRll;
        TH1F* hdeltaphill;
	TH2F* hpt1pt2;

	vector<long long> checkDuplicates;
	virtual bool Cut(const Event &evt);
	virtual bool LepID(const LepInfo &lep);
	virtual bool FatJetID(const FatJetInfo &fatjet);
	virtual bool JetID(const JetInfo &jet);
        public:
        HistCollection();
        ~HistCollection();
        bool Write(const char* path);
        bool Fill(const float lumi,const float cross_section,const char* path);
};

HistCollection::HistCollection(){
	checkDuplicates.clear();
	htotal=		new TH1F("htotal","total;;Events",1,0,1);
        hlep1pt=	new TH1F("hlep1pt","leading lepton p_{T};p_{T}(GeV);Events",1000,0.,1000.);
        hlep2pt=	new TH1F("hlep2pt","trailing lepton p_{T};p_{T}(GeV);Events",1000,0.,1000.);
        hlep1eta=	new TH1F("hlep1eta","leading lepton #eta;#eta;Events",600,-2.5,2.5);
        hlep2eta=	new TH1F("hlep2eta","trailling lepton #eta;#eta;Events",600,-2.5,2.5);
        hlep1phi=	new TH1F("hlep1phi","leading lepton #phi;#phi;Events",800,-4,4);
        hlep2phi=	new TH1F("hlep2phi","trailing lepton #phi;#phi;Events",800,-4,4);
        hfatjetpt=	new TH1F("hfatjetp4","fatjet p_{T};p_{T}(GeV);Events",1000,0,1000);
        hfatjeteta=	new TH1F("hfatjeteta","fatjet #eta;#eta;Events",600,-2.5,2.5);
        hfatjetphi=	new TH1F("hfatjetphi","fatjet #phi;#phi;Events",800,-4,4);
        hfatjetsdmass=	new TH1F("hfatjetsdmass","fatjet m_{sd};#m_{sd}(GeV);Events",1000,0,1000);
        hfatjettau1=	new TH1F("hfatjettau1","fatjet #tau_{1};#tau_{1};Events",1000,0,1);
        hfatjettau2=	new TH1F("hfatjettau2","fatjet #tau_{2};#tau_{2};Events",1000,0,1);
        hfatjettau21=	new TH1F("hfatjettau21","fatjet #tau_{21};#tau_{21};Events",1000,0,1);
        hfatjetdeepMDW=	new TH1F("hfatjetdeepMDW","fatjet deepMD W;;Events",1000,0,1);
        hfatjetdeepW=	new TH1F("hfatjetdeepW","fatjet deep W;;Evnets",200,0,1);
        hfatjetdeepMDZ= new TH1F("hfatjetdeepMDZ","fatjet deepMD Z;;Events",1000,0,1);
        hfatjetdeepZ=	new TH1F("hfatjetdeepZ","fatjet deep Z;;Events",1000,0,1);
        hfatjetdeepT=	new TH1F("hfatjetdeepT","fatjet deep T;;Events",1000,0,1);
        hfatjetdeepMDbb=new TH1F("hfatjetdeepMD_bb","fatjet deepMD bb;;Events",1000,0,1);
        hnlep=		new TH1F("hnlep","number of leptons;n_{lepton};Events",5,0,5);
        hnjet=		new TH1F("hnjet","number of jets;n_{jet};Events",10,0,10);
	hnjet_overlapremoved=new TH1F("hnjet_overlapremoved","number of jets;n_{jet};Events",10,0,10);
        hnbloose=	new TH1F("hnbloose","number of loose b jets;n_{bjet};Events",5,-.5,4.5);
	hnbmedium=	new TH1F("hnbmedium","number of medium b jets;n_{bjet};Events",5,-.5,4.5);
        hnfatjet=	new TH1F("hnfatjet","number of fatjets;n_{fatjet};Events",5,0,5);
        hmll=		new TH1F("hmll","invariant mass of lepton pair;m_{ll};Events",1000,0,1000);
        hst=		new TH1F("hst","S_{T};S_{T}(GeV);Events",2000,0,2000);
        hht=		new TH1F("hht","H_{T};H_{T}(GeV);Events",2000,0,2000);
	hdeltaRll=	new TH1F("hdeltaRll","#DeltaR between lepton pair;#DeltaR_{ll};Events",800,0,4);
        hdeltaphill=	new TH1F("hdeltaphill","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",800,0,4);
	hpt1pt2=	new TH2F("hpt1pt2","2D histogram of p_{T,1} and p_{T,2};p_{T,1};p_{T,2};Events",36,10,100,36,10,100);
}

HistCollection::~HistCollection(){
	delete htotal;
	delete hlep1pt;
        delete hlep2pt;
        delete hlep1eta;
        delete hlep2eta;
        delete hlep1phi;
        delete hlep2phi;
        delete hfatjetpt;
        delete hfatjeteta;
        delete hfatjetphi;
        delete hfatjetsdmass;
        delete hfatjettau1;
        delete hfatjettau2;
        delete hfatjettau21;
        delete hfatjetdeepMDW;
        delete hfatjetdeepW;
        delete hfatjetdeepMDZ;
        delete hfatjetdeepZ;
        delete hfatjetdeepT;
        delete hfatjetdeepMDbb;
        delete hnlep;
        delete hnjet;
	delete hnjet_overlapremoved;
        delete hnbloose;
	delete hnbmedium;
        delete hnfatjet;
        delete hmll;
        delete hst;
        delete hht;
        delete hdeltaphill;
	delete hdeltaRll;
	delete hpt1pt2;

}

bool HistCollection::Cut(const Event &evt){
        return true;
}

bool HistCollection::LepID(const LepInfo &lep){
	return true;
}

bool HistCollection::FatJetID(const FatJetInfo &fatjet){
	return true;
}

bool HistCollection::JetID(const JetInfo &jet){
	return true;
}

bool HistCollection::Fill(const float lumi,const float cross_section,const char* path){
        TChain *chain=new TChain("t");
	Event evt;
        vector<LV> *lepp4=0,*jetp4=0,*fatjetp4=0;
	LV *met=0;
	vector<bool> *jetbloose=0,*jetbmedium=0;
	vector<float> *fatjetsdm=0,*tau21=0,*tau2=0,*tau1=0,*deepMDW=0,*deepW=0,*deepMDZ=0,*deepZ=0,*deepT=0,*deepMDbb=0;
	vector<int> *leptight=0,*WPid=0;
	int nbmedium,nbloose,run,isData;
	unsigned long long event;
	chain->SetBranchAddress("Common_lep_tight",		&leptight);
        chain->SetBranchAddress("Common_lep_p4",                &lepp4);
        chain->SetBranchAddress("Common_jet_p4",                &jetp4);
	chain->SetBranchAddress("Common_jet_passBloose",	&jetbloose);
	chain->SetBranchAddress("Common_jet_passBmedium",       &jetbmedium);
	chain->SetBranchAddress("Common_nb_loose",		&nbloose);
	chain->SetBranchAddress("Common_nb_medium",             &nbmedium);
        chain->SetBranchAddress("Common_fatjet_p4",             &fatjetp4);
        chain->SetBranchAddress("Common_fatjet_msoftdrop",      &fatjetsdm);
        chain->SetBranchAddress("Common_fatjet_tau21",          &tau21);
        chain->SetBranchAddress("Common_fatjet_tau2",           &tau2);
        chain->SetBranchAddress("Common_fatjet_tau1",           &tau1);
        chain->SetBranchAddress("Common_fatjet_deepMD_W",       &deepMDW);
        chain->SetBranchAddress("Common_fatjet_deep_W",         &deepW);
        chain->SetBranchAddress("Common_fatjet_deepMD_Z",       &deepMDZ);
        chain->SetBranchAddress("Common_fatjet_deep_Z",         &deepZ);
        chain->SetBranchAddress("Common_fatjet_deep_T",         &deepT);
        chain->SetBranchAddress("Common_fatjet_deepMD_bb",      &deepMDbb);
	chain->SetBranchAddress("Common_fatjet_WP",		&WPid);
        chain->SetBranchAddress("Common_met_p4",		&met);
	chain->SetBranchAddress("Common_run",			&run);
	chain->SetBranchAddress("Common_evt",			&event);
	chain->SetBranchAddress("Common_isData",		&isData);
	chain->Add(path);
	TFile *file=TFile::Open(path);
	if(!file->IsOpen()) return false;
	evt.scale = cross_section * 1000 * lumi / ((TH1F*) file->Get("Wgt__h_nevents"))->Integral();
        for(unsigned int i=0;i<chain->GetEntries();i++){
                chain->GetEntry(i);
		//build the event
		if(isData){
			bool duplicates=false;
			long long RUNPREF=1000*1000;
			long long dupCheck = run*RUNPREF + event;
			for (unsigned int uid = 0; uid < checkDuplicates.size(); uid++){
				if (checkDuplicates[uid] == dupCheck){
					duplicates=true;
					break;
				}
			}
			if(duplicates==true) continue;
			checkDuplicates.push_back(dupCheck);
			evt.scale=1;
		}//reset the scale factor and duplicate removal for data
		evt.lep.clear();
		evt.fatjet.clear();
		evt.jet.clear();
		evt.ht=0;
		evt.st=0;
		evt.nbloose=0;
		evt.nbmedium=0;
		evt.njet_overlapremoved=0;
		evt.run=run;
		evt.event=event;

		for(unsigned int ilep=0;ilep<lepp4->size();ilep++){
			LepInfo temp;
			temp.pt=lepp4->at(ilep).pt();
			temp.eta=lepp4->at(ilep).eta();
			temp.phi=lepp4->at(ilep).phi();
			temp.tight=leptight->at(ilep);

			if(!LepID(temp)) continue;
			evt.lep.push_back(temp);
			evt.st+=lepp4->at(ilep).pt();
		}

		for(unsigned int ifatjet=0;ifatjet<fatjetp4->size();ifatjet++){
			FatJetInfo temp;
			temp.sdmass=fatjetsdm->at(ifatjet);
			temp.pt=fatjetp4->at(ifatjet).pt();
			temp.eta=fatjetp4->at(ifatjet).eta();
			temp.phi=fatjetp4->at(ifatjet).phi();
			temp.tau21=tau21->at(ifatjet);
			temp.tau2=tau2->at(ifatjet);
			temp.tau1=tau1->at(ifatjet);
			temp.deepMDW=deepMDW->at(ifatjet);
			temp.deepW=deepW->at(ifatjet);
			temp.deepMDZ=deepZ->at(ifatjet);
			temp.deepZ=deepZ->at(ifatjet);
			temp.deepT=deepT->at(ifatjet);
			temp.deepMDbb=deepMDbb->at(ifatjet);
			temp.WPid=WPid->at(ifatjet);

			if(!FatJetID(temp)) continue;
			evt.fatjet.push_back(temp);
			evt.st+=fatjetp4->at(ifatjet).pt();
			evt.ht+=fatjetp4->at(ifatjet).pt();
		}

		for(unsigned int ijet=0;ijet<jetp4->size();ijet++){
			JetInfo temp;
			temp.pt=jetp4->at(ijet).pt();
			temp.eta=jetp4->at(ijet).eta();
			temp.phi=jetp4->at(ijet).phi();
			temp.passbloose=jetbloose->at(ijet);
			temp.passbmedium=jetbmedium->at(ijet);
			bool overlap=false;
			for(unsigned int ifatjet=0;ifatjet<fatjetp4->size();ifatjet++){
				if(ROOT::Math::VectorUtil::DeltaR(jetp4->at(ijet),fatjetp4->at(ifatjet))<0.8){
					overlap=true;
					break;
				}				
			}
			temp.overlapwithfatjet=overlap;
			if(!JetID(temp)) continue;
			evt.jet.push_back(temp);
			if(!overlap){
				evt.st+=jetp4->at(ijet).pt();
				evt.ht+=jetp4->at(ijet).pt();
				evt.njet_overlapremoved++;
			}
		}
		evt.nbmedium=nbmedium;
		evt.nbloose=nbloose;
		evt.st+=met->pt();
		evt.mll=(lepp4->at(0)+lepp4->at(1)).M();
		evt.deltaRll=fabs(ROOT::Math::VectorUtil::DeltaR(lepp4->at(0),lepp4->at(1)));
		evt.deltaphill=fabs(ROOT::Math::VectorUtil::DeltaPhi(lepp4->at(0),lepp4->at(1)));
		//build the event
		//fill in histograms
		if(Cut(evt)){//addition cut
			htotal->Fill(0.,				evt.scale);
			hlep1pt->Fill(evt.lep.at(0).pt,			evt.scale);
			hlep2pt->Fill(evt.lep.at(1).pt,			evt.scale);
			hlep1eta->Fill(evt.lep.at(0).eta,		evt.scale);
			hlep2eta->Fill(evt.lep.at(1).eta,		evt.scale);
			hlep1phi->Fill(evt.lep.at(0).phi,		evt.scale);
			hlep2phi->Fill(evt.lep.at(1).phi,		evt.scale);
			hfatjetpt->Fill(evt.fatjet.at(0).pt,		evt.scale);
			hfatjeteta->Fill(evt.fatjet.at(0).eta,		evt.scale);
			hfatjetphi->Fill(evt.fatjet.at(0).phi,		evt.scale);
			hfatjetsdmass->Fill(evt.fatjet.at(0).sdmass,	evt.scale);
			hfatjettau1->Fill(evt.fatjet.at(0).tau1,	evt.scale);
			hfatjettau2->Fill(evt.fatjet.at(0).tau2,	evt.scale);
			hfatjettau21->Fill(evt.fatjet.at(0).tau21,	evt.scale);
			hfatjetdeepMDW->Fill(evt.fatjet.at(0).deepMDW,	evt.scale);
			hfatjetdeepW->Fill(evt.fatjet.at(0).deepW,	evt.scale);
			hfatjetdeepMDZ->Fill(evt.fatjet.at(0).deepMDZ,	evt.scale);
			hfatjetdeepZ->Fill(evt.fatjet.at(0).deepZ,	evt.scale);
			hfatjetdeepT->Fill(evt.fatjet.at(0).deepT,	evt.scale);
			hfatjetdeepMDbb->Fill(evt.fatjet.at(0).deepMDbb,evt.scale);
			hnlep->Fill(evt.lep.size(),			evt.scale);
			hnjet->Fill(evt.jet.size(),			evt.scale);
			hnjet_overlapremoved->Fill(evt.njet_overlapremoved,evt.scale);
			hnbloose->Fill(evt.nbloose,			evt.scale);
			hnbmedium->Fill(evt.nbmedium,			evt.scale);
			hnfatjet->Fill(evt.fatjet.size(),		evt.scale);
			hmll->Fill(evt.mll,				evt.scale);
			hst->Fill(evt.st,				evt.scale);
			hht->Fill(evt.ht,				evt.scale);
			hdeltaRll->Fill(evt.deltaRll,			evt.scale);
			hdeltaphill->Fill(evt.deltaphill,		evt.scale);
			hpt1pt2->Fill((evt.lep.at(0).pt<100?evt.lep.at(0).pt:98),(evt.lep.at(1).pt<100?evt.lep.at(1).pt:98),evt.scale);
		
		}
		
		//fill in histograms
        }
        return true;
}

bool HistCollection::Write(const char* path){
	TFile *file=TFile::Open(path,"RECREATE");
	htotal->Write();
        hlep1pt->Write();
        hlep2pt->Write();
        hlep1eta->Write();
        hlep2eta->Write();
        hlep1phi->Write();
        hlep2phi->Write();
        hfatjetpt->Write();
        hfatjeteta->Write();
        hfatjetphi->Write();
        hfatjetsdmass->Write();
        hfatjettau1->Write();
        hfatjettau2->Write();
        hfatjettau21->Write();
        hfatjetdeepMDW->Write();
        hfatjetdeepW->Write();
        hfatjetdeepMDZ->Write();
        hfatjetdeepZ->Write();
        hfatjetdeepT->Write();
        hfatjetdeepMDbb->Write();
        hnlep->Write();
        hnjet->Write();
	hnjet_overlapremoved->Write();
        hnbloose->Write();
	hnbmedium->Write();
        hnfatjet->Write();
        hmll->Write();
        hst->Write();
        hht->Write();
	hdeltaRll->Write();
        hdeltaphill->Write();
	hpt1pt2->Write();
	file->Close();
	return true;
}

