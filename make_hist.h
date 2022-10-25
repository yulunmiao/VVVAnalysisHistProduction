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

#define LUMI2016APV 19.52
#define LUMI2016 16.81
#define LUMI2017 41.48
#define LUMI2018 59.83
//#define LUMI2018 137.65
#define mZ 91

typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<float> > LV;

struct LepInfo{
        float pt;
        float eta;
        float phi;
	float tight;
	int pdgid;
	float mt;
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
	float met;
	bool ist;
	bool isW;
	bool issingleWq;
};


class HistCollection{
        protected:
	TH1F* htotal;
	TH1F* hsfup;
	TH1F* hlepSFelup;
	TH1F* hlepSFeldn;
        TH1F* hlepSFmuup;
	TH1F* hlepSFmudn;
        TH1F* hfatjetSFup;
        TH1F* hfatjetSFdn;
        TH1F* hlep1pt;
        TH1F* hlep2pt;
        TH1F* hlep1eta;
        TH1F* hlep2eta;
        TH1F* hlep1phi;
        TH1F* hlep2phi;
        TH1F* hfatjetpt;
  	TH1F* hfatjetpt_isW;
   	TH1F* hfatjetpt_ist;
    	TH1F* hfatjetpt_issingleWq;
     	TH1F* hfatjetpt_isother;
        TH1F* hfatjeteta;
        TH1F* hfatjetphi;
        TH1F* hfatjetsdmass;
	TH1F* hfatjetsdmass_pt_200to300;
	TH1F* hfatjetsdmass_pt_300to400;
	TH1F* hfatjetsdmass_pt_400toInf;
        TH1F* hfatjettau1;
        TH1F* hfatjettau2;
        TH1F* hfatjettau21;
        TH1F* hfatjetdeepMDW;
        TH1F* hfatjetdeepW;
        TH1F* hfatjetdeepMDWn;
        TH1F* hfatjetdeepMDZ;
        TH1F* hfatjetdeepZ;
        TH1F* hfatjetdeepT;
        TH1F* hfatjetdeepMDbb;
	TH1F* hfatjetpassID;
        TH1F* hnlep;
        TH1F* hnjet;
	TH1F* hnjet_overlapremoved;
        TH1F* hnbloose;
	TH1F* hnbmedium;
        TH1F* hnfatjet;
        TH1F* hmll;
	TH1F* hmtmax;
	TH1F* hmtmin;
	TH1F* hmt1;
	TH1F* hmt2;
	TH1F* hmet;
        TH1F* hst;
	TH1F* hht;
	TH1F* hdeltaRll;
        TH1F* hdeltaphill;
	TH2F* hpt1pt2;
	TH1F* hOF;
	TH1F* hcategory;
	TH1F* hsdmass_isW;
	TH1F* hsdmass_ist;
	TH1F* hsdmass_issingleWq;
	TH1F* hsdmass_isother;
	TH1F* hsdmass_pt_200to300_isW;
	TH1F* hsdmass_pt_300to400_isW;
	TH1F* hsdmass_pt_400toInf_isW;
	TH1F* hfatjetdeepMDWn_isW;
	TH1F* hfatjetdeepMDWn_ist;
	TH1F* hfatjetdeepMDWn_issingleWq;
	TH1F* hfatjetdeepMDWn_isother;
	TH1F* htotal_FT0_m30;
        TH1F* htotal_FT0_m15;
        TH1F* htotal_FT0_m10;
        TH1F* htotal_FT0_m8;
        TH1F* htotal_FT0_m4;
        TH1F* htotal_FT0_m2;
        TH1F* htotal_FT0_p2;
        TH1F* htotal_FT0_p4;
        TH1F* htotal_FT0_p8;
        TH1F* htotal_FT0_p10;
        TH1F* htotal_FT0_p15;
        TH1F* htotal_FT0_p30;

	TH1F* hst_FT0_m30;
        TH1F* hst_FT0_m15;
        TH1F* hst_FT0_m10;
        TH1F* hst_FT0_m8;
        TH1F* hst_FT0_m4;
        TH1F* hst_FT0_m2;
        TH1F* hst_FT0_p2;
        TH1F* hst_FT0_p4;
        TH1F* hst_FT0_p8;
        TH1F* hst_FT0_p10;
        TH1F* hst_FT0_p15;
        TH1F* hst_FT0_p30;

	TH1F* hdeltaphill_FT0_m30;
        TH1F* hdeltaphill_FT0_m15;
        TH1F* hdeltaphill_FT0_m10;
        TH1F* hdeltaphill_FT0_m8;
        TH1F* hdeltaphill_FT0_m4;
        TH1F* hdeltaphill_FT0_m2;
        TH1F* hdeltaphill_FT0_p2;
        TH1F* hdeltaphill_FT0_p4;
        TH1F* hdeltaphill_FT0_p8;
        TH1F* hdeltaphill_FT0_p10;
        TH1F* hdeltaphill_FT0_p15;
        TH1F* hdeltaphill_FT0_p30;

        TH1F* hdeltaRll_FT0_m30;
        TH1F* hdeltaRll_FT0_m15;
        TH1F* hdeltaRll_FT0_m10;
        TH1F* hdeltaRll_FT0_m8;
        TH1F* hdeltaRll_FT0_m4;
        TH1F* hdeltaRll_FT0_m2;
        TH1F* hdeltaRll_FT0_p2;
        TH1F* hdeltaRll_FT0_p4;
        TH1F* hdeltaRll_FT0_p8;
        TH1F* hdeltaRll_FT0_p10;
        TH1F* hdeltaRll_FT0_p15;
        TH1F* hdeltaRll_FT0_p30;


        vector<unsigned long long> checkDuplicates;
/*	
	struct{
		vector<unsigned long long> checkrun;
		vector<int> checkevt;
		int size;
	}checkDuplicates;
*/	
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
//	checkDuplicates.checkrun.clear();
//	checkDuplicates.checkevt.clear();
//	checkDuplicates.size=0;
	htotal=		new TH1F("htotal","total;;Events",1,0,1);
	hsfup=		new TH1F("hsfup","",30,0,3);
	hlepSFelup=	new TH1F("hlepSFelup","electron scale factor up",1,0,1);
	hlepSFeldn=	new TH1F("hlepSFeldn","electron scale factor down",1,0,1);
	hlepSFmuup=	new TH1F("hlepSFmuup","muon scale factor up",1,0,1);
	hlepSFmudn=	new TH1F("hlepSFmudn","muon scale factor down",1,0,1);
	hfatjetSFup=	new TH1F("hfatjetSFup","fatjet scale factor up",1,0,1);
	hfatjetSFdn=	new TH1F("hfatjetSFdn","fatjet scale factor down",1,0,1);
        hlep1pt=	new TH1F("hlep1pt","leading lepton p_{T};p_{T}(GeV);Events",20,0.,300.);
        hlep2pt=	new TH1F("hlep2pt","trailing lepton p_{T};p_{T}(GeV);Events",20,0.,150.);
        hlep1eta=	new TH1F("hlep1eta","leading lepton #eta;#eta;Events",600,-2.5,2.5);
        hlep2eta=	new TH1F("hlep2eta","trailling lepton #eta;#eta;Events",600,-2.5,2.5);
        hlep1phi=	new TH1F("hlep1phi","leading lepton #phi;#phi;Events",800,-4,4);
        hlep2phi=	new TH1F("hlep2phi","trailing lepton #phi;#phi;Events",800,-4,4);
        hfatjetpt=	new TH1F("hfatjetpt","fatjet p_{T};p_{T}(GeV);Events",30,200,500);
        hfatjetpt_isW=	new TH1F("hfatjetpt_isW","fatjet p_{T};p_{T}(GeV);Events",30,200,500);
        hfatjetpt_ist=	new TH1F("hfatjetpt_ist","fatjet p_{T};p_{T}(GeV);Events",30,200,500);
        hfatjetpt_issingleWq=	new TH1F("hfatjetpt_issingleWq","fatjet p_{T};p_{T}(GeV);Events",30,200,500);
        hfatjetpt_isother=	new TH1F("hfatjetpt_isother","fatjet p_{T};p_{T}(GeV);Events",30,200,500);

	hfatjeteta=	new TH1F("hfatjeteta","fatjet #eta;#eta;Events",600,-2.5,2.5);
        hfatjetphi=	new TH1F("hfatjetphi","fatjet #phi;#phi;Events",800,-4,4);
        hfatjetsdmass=	new TH1F("hfatjetsdmass","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	hfatjetsdmass_pt_200to300=	new TH1F("hfatjetsdmass_pt_200to300","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	hfatjetsdmass_pt_300to400=	new TH1F("hfatjetsdmass_pt_300to400","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	hfatjetsdmass_pt_400toInf=	new TH1F("hfatjetsdmass_pt_400toInf","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200); 
        hfatjettau1=	new TH1F("hfatjettau1","fatjet #tau_{1};#tau_{1};Events",1000,0,1);
        hfatjettau2=	new TH1F("hfatjettau2","fatjet #tau_{2};#tau_{2};Events",1000,0,1);
        hfatjettau21=	new TH1F("hfatjettau21","fatjet #tau_{21};#tau_{21};Events",1000,0,1);
	float x[5]={0,0.59,0.82,0.90,1};
        hfatjetdeepMDW=	new TH1F("hfatjetdeepMDW","fatjet deepMD W;;Events",4,x);
	hfatjetpassID=  new TH1F("hfatjetpassID","fatjet ID;;Events",4,-0.5,3.5);
	hfatjetdeepMDWn=new TH1F("hfatjetdeepMDWn","fatjet deepMD W;;EVents",20,0,1);
       	hfatjetdeepMDWn_isW=new TH1F("hfatjetdeepMDWn_isW","fatjet deepMD W;;EVents",20,0,1);
    	hfatjetdeepMDWn_ist=new TH1F("hfatjetdeepMDWn_ist","fatjet deepMD W;;EVents",20,0,1);
    	hfatjetdeepMDWn_issingleWq=new TH1F("hfatjetdeepMDWn_issingleWq","fatjet deepMD W;;EVents",20,0,1);
    	hfatjetdeepMDWn_isother=new TH1F("hfatjetdeepMDWn_isother","fatjet deepMD W;;EVents",20,0,1);
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
        hmll=		new TH1F("hmll","invariant mass of lepton pair;m_{ll};Events",80,0,400);
	hmtmax=		new TH1F("hmtmax","maximum transverse mass of lepton;m_{T};Events",20,0,200);
	hmtmin=		new TH1F("hmtmin","minimum transverse mass of lepton;m_{T};Events",20,0,200);
	hmt1=		new TH1F("hmt1","transverse mass of leading lepton;m_{T};Events",20,0,200);
        hmt2=		new TH1F("hmt2","transverse mass of trailing lepton;m_{T};Events",20,0,200);
	hmet=		new TH1F("hmet","met of the event;p_{T,miss};Events",20,0,300);
        hst=		new TH1F("hst","S_{T};S_{T}(GeV);Events",27,300,3000);
        hht=		new TH1F("hht","H_{T};H_{T}(GeV);Events",2000,0,2000);
	hdeltaRll=	new TH1F("hdeltaRll","#DeltaR between lepton pair;#DeltaR_{ll};Events",20,0,4);
        hdeltaphill=	new TH1F("hdeltaphill","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
	hpt1pt2=	new TH2F("hpt1pt2","2D histogram of p_{T,1} and p_{T,2};p_{T,1};p_{T,2};Events",36,10,100,36,10,100);
	hOF=		new TH1F("hOF","isOF;;Events",2,-0.5,5.5);
	hcategory=	new TH1F("hcategory","",5,-0.5,4.5);
	hsdmass_isW=  new TH1F("hsdmass_isW","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	hsdmass_ist=  new TH1F("hsdmass_ist","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	hsdmass_issingleWq=  new TH1F("hsdmass_issingleWq","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	hsdmass_isother=  new TH1F("hsdmass_isother","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	hsdmass_pt_200to300_isW=  new TH1F("hsdmass_pt_200to300_isW","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	hsdmass_pt_300to400_isW=  new TH1F("hsdmass_pt_300to400_isW","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	hsdmass_pt_400toInf_isW=  new TH1F("hsdmass_pt_400toInf_isW","fatjet m_{sd};#m_{sd}(GeV);Events",40,0,200);
	htotal_FT0_m30= new TH1F("htotal_FT0_m30","total;;Events",1,0,1);
        htotal_FT0_m15= new TH1F("htotal_FT0_m15","total;;Events",1,0,1);
        htotal_FT0_m10= new TH1F("htotal_FT0_m10","total;;Events",1,0,1);
        htotal_FT0_m8=  new TH1F("htotal_FT0_m8","total;;Events",1,0,1);
        htotal_FT0_m4=  new TH1F("htotal_FT0_m4","total;;Events",1,0,1);
        htotal_FT0_m2=  new TH1F("htotal_FT0_m2","total;;Events",1,0,1);
        htotal_FT0_p2=  new TH1F("htotal_FT0_p2","total;;Events",1,0,1);
        htotal_FT0_p4=  new TH1F("htotal_FT0_p4","total;;Events",1,0,1);
        htotal_FT0_p8=  new TH1F("htotal_FT0_p8","total;;Events",1,0,1);
        htotal_FT0_p10= new TH1F("htotal_FT0_p10","total;;Events",1,0,1);
        htotal_FT0_p15= new TH1F("htotal_FT0_p15","total;;Events",1,0,1);
        htotal_FT0_p30= new TH1F("htotal_FT0_p30","total;;Events",1,0,1);

	hst_FT0_m30= new TH1F("hst_FT0_m30","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_m15= new TH1F("hst_FT0_m15","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_m10= new TH1F("hst_FT0_m10","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_m8=  new TH1F("hst_FT0_m8","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_m4=  new TH1F("hst_FT0_m4","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_m2=  new TH1F("hst_FT0_m2","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_p2=  new TH1F("hst_FT0_p2","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_p4=  new TH1F("hst_FT0_p4","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_p8=  new TH1F("hst_FT0_p8","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_p10= new TH1F("hst_FT0_p10","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_p15= new TH1F("hst_FT0_p15","s_{T};s_{T}(GeV);Events",27,300,3000);
        hst_FT0_p30= new TH1F("hst_FT0_p30","s_{T};s_{T}(GeV);Events",27,300,3000);

	hdeltaphill_FT0_m30= new TH1F("hdeltaphill_FT0_m30","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_m15= new TH1F("hdeltaphill_FT0_m15","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_m10= new TH1F("hdeltaphill_FT0_m10","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_m8=  new TH1F("hdeltaphill_FT0_m8","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_m4=  new TH1F("hdeltaphill_FT0_m4","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_m2=  new TH1F("hdeltaphill_FT0_m2","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_p2=  new TH1F("hdeltaphill_FT0_p2","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_p4=  new TH1F("hdeltaphill_FT0_p4","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_p8=  new TH1F("hdeltaphill_FT0_p8","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_p10= new TH1F("hdeltaphill_FT0_p10","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_p15= new TH1F("hdeltaphill_FT0_p15","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaphill_FT0_p30= new TH1F("hdeltaphill_FT0_p30","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);

	hdeltaRll_FT0_m30= new TH1F("hdeltaRll_FT0_m30","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_m15= new TH1F("hdeltaRll_FT0_m15","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_m10= new TH1F("hdeltaRll_FT0_m10","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_m8=  new TH1F("hdeltaRll_FT0_m8","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_m4=  new TH1F("hdeltaRll_FT0_m4","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_m2=  new TH1F("hdeltaRll_FT0_m2","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_p2=  new TH1F("hdeltaRll_FT0_p2","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_p4=  new TH1F("hdeltaRll_FT0_p4","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_p8=  new TH1F("hdeltaRll_FT0_p8","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_p10= new TH1F("hdeltaRll_FT0_p10","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_p15= new TH1F("hdeltaRll_FT0_p15","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);
        hdeltaRll_FT0_p30= new TH1F("hdeltaRll_FT0_p30","#Delta#phi between lepton pair;#Delta#phi_{ll};Events",20,0,4);



}

HistCollection::~HistCollection(){
	delete htotal;
	delete hsfup;
	delete hlepSFelup;
        delete hlepSFeldn;
        delete hlepSFmuup;
        delete hlepSFmudn;
        delete hfatjetSFup;
        delete hfatjetSFdn;
	delete hlep1pt;
        delete hlep2pt;
        delete hlep1eta;
        delete hlep2eta;
        delete hlep1phi;
        delete hlep2phi;
        delete hfatjetpt;
        delete hfatjetpt_isW;
        delete hfatjetpt_ist;
        delete hfatjetpt_issingleWq;
        delete hfatjetpt_isother;
       
	delete hfatjeteta;
        delete hfatjetphi;
        delete hfatjetsdmass;
	delete hfatjetsdmass_pt_200to300;
	delete hfatjetsdmass_pt_300to400;
	delete hfatjetsdmass_pt_400toInf; 
        delete hfatjettau1;
        delete hfatjettau2;
        delete hfatjettau21;
        delete hfatjetdeepMDW;
	delete hfatjetdeepMDWn;	
	delete hfatjetdeepMDWn_isW;
	delete hfatjetdeepMDWn_ist;
	delete hfatjetdeepMDWn_issingleWq;
	delete hfatjetdeepMDWn_isother;

        delete hfatjetdeepW;
        delete hfatjetdeepMDZ;
        delete hfatjetdeepZ;
        delete hfatjetdeepT;
        delete hfatjetdeepMDbb;
	delete hfatjetpassID;
        delete hnlep;
        delete hnjet;
	delete hnjet_overlapremoved;
        delete hnbloose;
	delete hnbmedium;
        delete hnfatjet;
        delete hmll;
	delete hmtmax;
	delete hmtmin;
	delete hmt1;
	delete hmt2;
	delete hmet;
        delete hst;
        delete hht;
        delete hdeltaphill;
	delete hdeltaRll;
	delete hpt1pt2;
	delete hOF;
	delete hcategory;
	delete hsdmass_isW;
	delete hsdmass_ist;
	delete hsdmass_issingleWq;
	delete hsdmass_isother;
        delete hsdmass_pt_200to300_isW;
        delete hsdmass_pt_300to400_isW;
        delete hsdmass_pt_400toInf_isW; 
        delete htotal_FT0_m30;
        delete htotal_FT0_m15;
        delete htotal_FT0_m10;
        delete htotal_FT0_m8;
        delete htotal_FT0_m4;
        delete htotal_FT0_m2;
        delete htotal_FT0_p2;
        delete htotal_FT0_p4;
        delete htotal_FT0_p8;
        delete htotal_FT0_p10;
        delete htotal_FT0_p15;
        delete htotal_FT0_p30;

        delete hst_FT0_m30;
        delete hst_FT0_m15;
        delete hst_FT0_m10;
        delete hst_FT0_m8;
        delete hst_FT0_m4;
        delete hst_FT0_m2;
        delete hst_FT0_p2;
        delete hst_FT0_p4;
        delete hst_FT0_p8;
        delete hst_FT0_p10;
        delete hst_FT0_p15;
        delete hst_FT0_p30;

        delete hdeltaphill_FT0_m30;
        delete hdeltaphill_FT0_m15;
        delete hdeltaphill_FT0_m10;
        delete hdeltaphill_FT0_m8;
        delete hdeltaphill_FT0_m4;
        delete hdeltaphill_FT0_m2;
        delete hdeltaphill_FT0_p2;
        delete hdeltaphill_FT0_p4;
        delete hdeltaphill_FT0_p8;
        delete hdeltaphill_FT0_p10;
        delete hdeltaphill_FT0_p15;
        delete hdeltaphill_FT0_p30;

	delete hdeltaRll_FT0_m30;
        delete hdeltaRll_FT0_m15;
        delete hdeltaRll_FT0_m10;
        delete hdeltaRll_FT0_m8;
        delete hdeltaRll_FT0_m4;
        delete hdeltaRll_FT0_m2;
        delete hdeltaRll_FT0_p2;
        delete hdeltaRll_FT0_p4;
        delete hdeltaRll_FT0_p8;
        delete hdeltaRll_FT0_p10;
        delete hdeltaRll_FT0_p15;
        delete hdeltaRll_FT0_p30;
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
        vector<LV> *lepp4=0,*jetp4=0,*fatjetp4=0,*genp4=0;
	LV *met=0;
	vector<bool> *jetbloose=0,*jetbmedium=0;
	vector<float> *fatjetsdm=0,*tau21=0,*tau2=0,*tau1=0,*deepMDW=0,*deepW=0,*deepMDZ=0,*deepZ=0,*deepT=0,*deepMDbb=0,*EFT=0;
	vector<int> *leptight=0,*WPid=0,*WPida=0,*pdgid=0,*genpdgid=0,*genidx=0,*genmotheridx=0,*genmotherid=0;
	float lepSF,fatjetSF,genWeight,lepSFelup,lepSFeldn,lepSFmuup,lepSFmudn,fatjetSFup,fatjetSFdn,btagSF;
	int nbmedium,nbloose,run,isData;
	bool pass_duplicate_removal;
	unsigned long long event;
	chain->SetBranchAddress("Common_lep_tight",		&leptight);
        chain->SetBranchAddress("Common_lep_p4",                &lepp4);
	chain->SetBranchAddress("Common_lep_pdgid",		&pdgid);
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
        chain->SetBranchAddress("Common_fatjet_particleNetMD_W",       &deepMDW);
        chain->SetBranchAddress("Common_fatjet_deep_W",         &deepW);
        chain->SetBranchAddress("Common_fatjet_deepMD_Z",       &deepMDZ);
        chain->SetBranchAddress("Common_fatjet_deep_Z",         &deepZ);
        chain->SetBranchAddress("Common_fatjet_deep_T",         &deepT);
        chain->SetBranchAddress("Common_fatjet_deepMD_bb",      &deepMDbb);
	chain->SetBranchAddress("Common_fatjet_WP_MD",		&WPid);
//	chain->SetBranchAddress("Common_fatjet_WP_antimasscut", &WPida);
        chain->SetBranchAddress("Common_met_p4",		&met);
	chain->SetBranchAddress("Common_run",			&run);
	chain->SetBranchAddress("Common_evt",			&event);
	chain->SetBranchAddress("Common_isData",		&isData);
	chain->SetBranchAddress("Common_LHEWeight_mg_reweighting", &EFT);
        chain->SetBranchAddress("Common_genWeight",             &genWeight);
	chain->SetBranchAddress("SS2jet_pass_duplicate_m_e", &pass_duplicate_removal);
	chain->SetBranchAddress("SS2jet_raw_gen_idx",            &genidx);
        chain->SetBranchAddress("SS2jet_raw_gen_mother_idx",     &genmotheridx);
        chain->SetBranchAddress("SS2jet_raw_gen_mother_id",      &genmotherid);
        chain->SetBranchAddress("SS2jet_raw_gen_pdgid",          &genpdgid);
        chain->SetBranchAddress("SS2jet_raw_gen_p4s",            &genp4);

	//scale factors
	chain->SetBranchAddress("Common_event_lepSFTight",		&lepSF);
	chain->SetBranchAddress("Common_eventweight_fatjet_SFLoose",	&fatjetSF);
	chain->SetBranchAddress("Common_event_lepSFelup",	&lepSFelup);
	chain->SetBranchAddress("Common_event_lepSFeldn",	&lepSFeldn);
	chain->SetBranchAddress("Common_event_lepSFmuup",       &lepSFmuup);
        chain->SetBranchAddress("Common_event_lepSFmudn",       &lepSFmudn);
	chain->SetBranchAddress("Common_event_mediumBtagSF",	&btagSF);
        chain->SetBranchAddress("Common_eventweight_fatjet_SFupLoose",    &fatjetSFup);
        chain->SetBranchAddress("Common_eventweight_fatjet_SFdnLoose",    &fatjetSFdn);


	chain->Add(path);
	TFile *file=TFile::Open(path);
	float scale;
	if(!file->IsOpen()) return false;
	scale = cross_section * 1000 * lumi / ((TH1F*) file->Get("Wgt__h_nevents"))->Integral();
        for(unsigned int i=0;i<chain->GetEntries();i++){
                chain->GetEntry(i);
//		if(EFT->size()!=0)      scale = cross_section * 1000 * lumi / ((TH1F*) file->Get("Wgt__h_nevents"))->Integral() * EFT->at(0);
		if(EFT->size()!=0)      scale = cross_section * 1000 * lumi / ((TH1F*) file->Get("Root__h_Common_LHEWeight_mg_reweighting_times_genWeight"))->GetBinContent(1) * EFT->at(0);
		if(isData) evt.scale=1;
		else evt.scale = ( (genWeight>0) - (genWeight<0) ) * scale * lepSF * btagSF;
		//build the event
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
		evt.isW=false;

		for(unsigned int ilep=0;ilep<lepp4->size();ilep++){
			LepInfo temp;
			temp.pt=lepp4->at(ilep).pt();
			temp.eta=lepp4->at(ilep).eta();
			temp.phi=lepp4->at(ilep).phi();
			temp.tight=leptight->at(ilep);
			temp.pdgid=pdgid->at(ilep);
			float phi1 = lepp4->at(ilep).Phi();
		    	float phi2 = met->Phi();
			float Et1  = lepp4->at(ilep).Et();
			float Et2  = met->Et();
			temp.mt=sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2)));
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
/*
			if(evt.fatjet.size()==0){
                                evt.isW=false;
                                for(unsigned igen=0;igen<genpdgid->size();igen++){
                                        if(!(abs(genpdgid->at(igen))==24)) continue;
                                        if(ROOT::Math::VectorUtil::DeltaR(genp4->at(igen),fatjetp4->at(ifatjet))<0.8){
                                                evt.isW=true;
                                                break;
                                        }
                                }
                        }
*/
			
                        if(evt.fatjet.size()==0){
				int W=-1;
				int Wq1=-1;
				int Wq2=-1;
				int b=-1;
				int t=-1;
				bool isWq1=false;
				bool isWq2=false;
				bool isb=false;
                                for(unsigned igen=0;igen<genpdgid->size();igen++){
					//search for first quark
					if(!((abs(genmotherid->at(igen))==24)&&(abs(genpdgid->at(igen))<=6))) continue;
					Wq1=igen;
					W=genmotheridx->at(igen);
					isWq1=ROOT::Math::VectorUtil::DeltaR(genp4->at(igen),fatjetp4->at(ifatjet))<0.8;
					//search for second quark
					for(unsigned int jgen=igen+1;jgen<genpdgid->size();jgen++){
						if((genmotheridx->at(jgen)==W)&&(abs(genpdgid->at(jgen))<=6)){
							Wq2=jgen;
							igen=jgen;
							isWq2=ROOT::Math::VectorUtil::DeltaR(genp4->at(jgen),fatjetp4->at(ifatjet))<0.8;
							break;
						}
					}
					t=genmotheridx->at(W);
					while(t!=-1 && abs(genpdgid->at(t))!=6){
						t=genmotheridx->at(t);
					}
					if(t!=-1){
						for(unsigned int jgen=0;igen<genpdgid->size();jgen++){
							if((genmotheridx->at(jgen)==t)&&(abs(genpdgid->at(jgen))==5)){
								b=jgen;
								isb=ROOT::Math::VectorUtil::DeltaR(genp4->at(jgen),fatjetp4->at(ifatjet))<0.8;
								break;
							}
						}
					}
				}
				evt.ist=isWq1&&isWq2&&isb;
				evt.isW=isWq1&&isWq2&&!isb;
				evt.issingleWq=(isWq1&&!isWq2)||(isWq2&&!isWq1);
			}
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
		evt.met=met->pt();
		evt.st+=met->pt();
		//build the event
		//fill in histograms
		if(Cut(evt)){//addition cut
			/*
			if(!isData){
				if(evt.isW){
					evt.scale*=0.861;
				}
				else{
					evt.scale*=1.1566;
				}
			}
			*/
			//cout<<evt.event<<endl;
		/*	
			if(!isData){
				FatJetInfo fatjet=evt.fatjet.at(0);
				if(fatjet.pt>=400.){	
					evt.scale*=0.87;
				}
				else if(fatjet.pt>=300.){
	       				evt.scale*=0.91;
				}
				else{
					evt.scale*=0.91;
				}
			}
		*/	
			if(isData && !pass_duplicate_removal) continue;
			/*
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
			}//reset the scale factor and duplicate removal for data
			*/
			htotal->Fill(0.,				evt.scale);
			hsfup->Fill(lepSFelup/lepSF);
			hlepSFelup->Fill(0.,				evt.scale/lepSF*lepSFelup);
			hlepSFeldn->Fill(0.,				evt.scale/lepSF*lepSFeldn);
			hlepSFmuup->Fill(0.,				evt.scale/lepSF*lepSFmuup);
			hlepSFmudn->Fill(0.,				evt.scale/lepSF*lepSFmudn);
			hfatjetSFup->Fill(0.,				evt.scale/fatjetSF*fatjetSFup);
		      	hfatjetSFdn->Fill(0.,				evt.scale/fatjetSF*fatjetSFdn);
			hlep1pt->Fill(evt.lep.at(0).pt<300?evt.lep.at(0).pt:299.5,			evt.scale);
			hlep1eta->Fill(evt.lep.at(0).eta,		evt.scale);
			hlep1phi->Fill(evt.lep.at(0).phi,		evt.scale);
			hfatjetpt->Fill(evt.fatjet.at(0).pt<500?evt.fatjet.at(0).pt:499.5,		evt.scale);			
			hfatjeteta->Fill(evt.fatjet.at(0).eta,		evt.scale);
			hfatjetphi->Fill(evt.fatjet.at(0).phi,		evt.scale);
			hfatjetsdmass->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale);
			if(evt.fatjet.at(0).pt<300){
				hfatjetsdmass_pt_200to300->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale);
			}
			else if(evt.fatjet.at(0).pt<400){
				hfatjetsdmass_pt_300to400->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale);
			}
			else{
				hfatjetsdmass_pt_400toInf->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale); 
			}
			hfatjettau1->Fill(evt.fatjet.at(0).tau1,	evt.scale);
			hfatjettau2->Fill(evt.fatjet.at(0).tau2,	evt.scale);
			hfatjettau21->Fill(evt.fatjet.at(0).tau21,	evt.scale);
			hfatjetdeepMDW->Fill(evt.fatjet.at(0).deepMDW,	evt.scale);
			hfatjetdeepMDWn->Fill(evt.fatjet.at(0).deepMDW, evt.scale);

			/*
			FatJetInfo fatjet=evt.fatjet.at(0);
			float scale=evt.scale;
			hfatjetpassID->Fill(0.,scale);
			if(fatjet.deepMDW>0.59){
				if(!isData){
					scale=evt.scale;
					if(fatjet.pt>=400.){	
						scale*=0.77;
					}
					else if(fatjet.pt>=300.){
	       					scale*=0.81;
					}
					else{
						scale*=0.81;
					}
				}
				hfatjetpassID->Fill(1.,scale);
			}
			if(fatjet.deepMDW>0.82){
				if(!isData){
					scale=evt.scale;
					if(fatjet.pt>=400.){	
						scale*=0.82;
					}
					else if(fatjet.pt>=300.){
	       					scale*=0.86;
					}
					else{
						scale*=0.86;
					}
				}
				hfatjetpassID->Fill(2.,scale);
			}


			if(fatjet.deepMDW>0.90){
				if(!isData){
					scale=evt.scale;
					if(fatjet.pt>=400.){	
						scale*=0.77;
					}
					else if(fatjet.pt>=300.){
	       					scale*=0.81;
					}
					else{
						scale*=0.81;
					}
				}
				hfatjetpassID->Fill(3.,scale);
			}
			*/
			hfatjetdeepW->Fill(evt.fatjet.at(0).deepW,	evt.scale);
			hfatjetdeepMDZ->Fill(evt.fatjet.at(0).deepMDZ,	evt.scale);
			hfatjetdeepZ->Fill(evt.fatjet.at(0).deepZ,	evt.scale);
			hfatjetdeepT->Fill(evt.fatjet.at(0).deepT,	evt.scale);
			hfatjetdeepMDbb->Fill(evt.fatjet.at(0).deepMDbb,evt.scale);
			hnlep->Fill(evt.lep.size(),			evt.scale);
			hnjet->Fill(evt.jet.size(),			evt.scale);
			hnjet_overlapremoved->Fill(evt.njet_overlapremoved,evt.scale);
			hnbloose->Fill(evt.nbloose,			evt.scale);
			hnbmedium->Fill(evt.nbmedium<4?evt.nbmedium:4,					evt.scale);
			hnfatjet->Fill(evt.fatjet.size(),		evt.scale);
			hmet->Fill(evt.met<350?evt.met:349.5,						evt.scale);
			hst->Fill(evt.st<3000?evt.st:2999.5,						evt.scale);
			hht->Fill(evt.ht,				evt.scale);

			if(evt.ist){
				hcategory->Fill(1.,			evt.scale);
				hsdmass_ist->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale);
				hfatjetpt_ist->Fill(evt.fatjet.at(0).pt<500?evt.fatjet.at(0).pt:499.5,		evt.scale);
				hfatjetdeepMDWn_ist->Fill(evt.fatjet.at(0).deepMDW,				evt.scale);	
			}

			else if(evt.isW){
				/*
				if(evt.fatjet.at(0).pt<300){
					hsdmass_pt_200to300_isW->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale);
				}
				else if(evt.fatjet.at(0).pt<400){
					hsdmass_pt_300to400_isW->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale);
				}
				else{
					hsdmass_pt_400toInf_isW->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale); 
				}
				*/
				hcategory->Fill(0.,			evt.scale);
				hsdmass_isW->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale);
				hfatjetpt_isW->Fill(evt.fatjet.at(0).pt<500?evt.fatjet.at(0).pt:499.5,		evt.scale);
				hfatjetdeepMDWn_isW->Fill(evt.fatjet.at(0).deepMDW,				evt.scale);
			}
			else if(evt.issingleWq){
				hcategory->Fill(2.,			evt.scale);
				hsdmass_issingleWq->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale);
				hfatjetdeepMDWn_issingleWq->Fill(evt.fatjet.at(0).deepMDW,				evt.scale);	
				hfatjetpt_issingleWq->Fill(evt.fatjet.at(0).pt<500?evt.fatjet.at(0).pt:499.5,		evt.scale);
			}
			else{
				hcategory->Fill(3.,			evt.scale);
				hsdmass_isother->Fill(evt.fatjet.at(0).sdmass<200?evt.fatjet.at(0).sdmass:199.5,	evt.scale);
				hfatjetdeepMDWn_isother->Fill(evt.fatjet.at(0).deepMDW,				evt.scale);
				hfatjetpt_isother->Fill(evt.fatjet.at(0).pt<500?evt.fatjet.at(0).pt:499.5,		evt.scale);
			}

			
			if(EFT->size()!=0){
				int EFT_index=85;
                                htotal_FT0_m30->Fill(0.,                                evt.scale/EFT->at(0)*EFT->at(EFT_index));
                                htotal_FT0_m15->Fill(0.,                                evt.scale/EFT->at(0)*EFT->at(EFT_index+1));
                                htotal_FT0_m10->Fill(0.,                                evt.scale/EFT->at(0)*EFT->at(EFT_index+2));
                                htotal_FT0_m8->Fill(0.,                                 evt.scale/EFT->at(0)*EFT->at(EFT_index+3));
                                htotal_FT0_m4->Fill(0.,                                 evt.scale/EFT->at(0)*EFT->at(EFT_index+4));
                                htotal_FT0_m2->Fill(0.,                                 evt.scale/EFT->at(0)*EFT->at(EFT_index+5));
                                htotal_FT0_p2->Fill(0.,                                 evt.scale/EFT->at(0)*EFT->at(EFT_index+6));
                                htotal_FT0_p4->Fill(0.,                                 evt.scale/EFT->at(0)*EFT->at(EFT_index+7));
                                htotal_FT0_p8->Fill(0.,                                 evt.scale/EFT->at(0)*EFT->at(EFT_index+8));
                                htotal_FT0_p10->Fill(0.,                                evt.scale/EFT->at(0)*EFT->at(EFT_index+9));
                                htotal_FT0_p15->Fill(0.,                                evt.scale/EFT->at(0)*EFT->at(EFT_index+10));
                                htotal_FT0_p30->Fill(0.,                                evt.scale/EFT->at(0)*EFT->at(EFT_index+11));

                                hst_FT0_m30->Fill(evt.st<3000?evt.st:2999.5,            evt.scale/EFT->at(0)*EFT->at(EFT_index));
                                hst_FT0_m15->Fill(evt.st<3000?evt.st:2999.5,            evt.scale/EFT->at(0)*EFT->at(EFT_index+1));
                                hst_FT0_m10->Fill(evt.st<3000?evt.st:2999.5,            evt.scale/EFT->at(0)*EFT->at(EFT_index+2));
                                hst_FT0_m8->Fill(evt.st<3000?evt.st:2999.5,             evt.scale/EFT->at(0)*EFT->at(EFT_index+3));
                                hst_FT0_m4->Fill(evt.st<3000?evt.st:2999.5,             evt.scale/EFT->at(0)*EFT->at(EFT_index+4));
                                hst_FT0_m2->Fill(evt.st<3000?evt.st:2999.5,             evt.scale/EFT->at(0)*EFT->at(EFT_index+5));
                                hst_FT0_p2->Fill(evt.st<3000?evt.st:2999.5,             evt.scale/EFT->at(0)*EFT->at(EFT_index+6));
                                hst_FT0_p4->Fill(evt.st<3000?evt.st:2999.5,             evt.scale/EFT->at(0)*EFT->at(EFT_index+7));
                                hst_FT0_p8->Fill(evt.st<3000?evt.st:2999.5,             evt.scale/EFT->at(0)*EFT->at(EFT_index+8));
                                hst_FT0_p10->Fill(evt.st<3000?evt.st:2999.5,            evt.scale/EFT->at(0)*EFT->at(EFT_index+9));
                                hst_FT0_p15->Fill(evt.st<3000?evt.st:2999.5,            evt.scale/EFT->at(0)*EFT->at(EFT_index+10));
				hst_FT0_p30->Fill(evt.st<3000?evt.st:2999.5,            evt.scale/EFT->at(0)*EFT->at(EFT_index+11));
	/*
					hdeltaphill_FT0_m30->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(85));
					hdeltaphill_FT0_m15->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(86));
					hdeltaphill_FT0_m10->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(87));
					hdeltaphill_FT0_m8->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(88));
					hdeltaphill_FT0_m4->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(89));
					hdeltaphill_FT0_m2->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(90));
					hdeltaphill_FT0_p2->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(91));
					hdeltaphill_FT0_p4->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(92));
					hdeltaphill_FT0_p8->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(93));
					hdeltaphill_FT0_p10->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(94));
					hdeltaphill_FT0_p15->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(95));
					hdeltaphill_FT0_p30->Fill(evt.deltaphill,		evt.scale/EFT->at(0)*EFT->at(96));

					hdeltaRll_FT0_m30->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(85));
					hdeltaRll_FT0_m15->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(86));
					hdeltaRll_FT0_m10->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(87));
					hdeltaRll_FT0_m8->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(88));
					hdeltaRll_FT0_m4->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(89));
					hdeltaRll_FT0_m2->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(90));
					hdeltaRll_FT0_p2->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(91));
					hdeltaRll_FT0_p4->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(92));
					hdeltaRll_FT0_p8->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(93));
					hdeltaRll_FT0_p10->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(94));
					hdeltaRll_FT0_p15->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(95));
					hdeltaRll_FT0_p30->Fill(evt.deltaRll,		evt.scale/EFT->at(0)*EFT->at(96));
	*/

				}

			}
			
			//fill in histograms
		}
		return true;
	}

	bool HistCollection::Write(const char* path){
		TFile *file=TFile::Open(path,"RECREATE");
		htotal->Write();
		hsfup->Write();
		hlepSFelup->Write();
		hlepSFeldn->Write();
		hlepSFmuup->Write();
		hlepSFmudn->Write();
		hfatjetSFup->Write();
		hfatjetSFdn->Write();
		hlep1pt->Write();
		hlep1eta->Write();
		hlep1phi->Write();
		hfatjetpt->Write();
		hfatjetpt_isW->Write();
		hfatjetpt_ist->Write();
		hfatjetpt_issingleWq->Write();
		hfatjetpt_isother->Write();
		hfatjeteta->Write();
		hfatjetphi->Write();
		hfatjetsdmass->Write();
		hfatjetsdmass_pt_200to300->Write();
		hfatjetsdmass_pt_300to400->Write();
		hfatjetsdmass_pt_400toInf->Write(); 
        
		hfatjettau1->Write();
		hfatjettau2->Write();
		hfatjettau21->Write();
		hfatjetdeepMDW->Write();
		hfatjetdeepMDWn->Write();
		hfatjetdeepMDWn_isW->Write();	
		hfatjetdeepMDWn_ist->Write();
		hfatjetdeepMDWn_issingleWq->Write();
		hfatjetdeepMDWn_isother->Write();
		hfatjetpassID->Write();
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
		hmet->Write();
		hst->Write();
		hht->Write();
		hOF->Write();
		hcategory->Write();
		hsdmass_isW->Write();
		hsdmass_ist->Write();
		hsdmass_issingleWq->Write();
		hsdmass_isother->Write();
		hsdmass_pt_200to300_isW->Write();
		hsdmass_pt_300to400_isW->Write();
		hsdmass_pt_400toInf_isW->Write();

		htotal_FT0_m30->Write();
		htotal_FT0_m15->Write();
		htotal_FT0_m10->Write();
		htotal_FT0_m8->Write();
		htotal_FT0_m4->Write();
		htotal_FT0_m2->Write();
		htotal_FT0_p2->Write();
		htotal_FT0_p4->Write();
		htotal_FT0_p8->Write();
		htotal_FT0_p10->Write();
		htotal_FT0_p15->Write();
		htotal_FT0_p30->Write();

		hst_FT0_m30->Write();
		hst_FT0_m15->Write();
		hst_FT0_m10->Write();
		hst_FT0_m8->Write();
		hst_FT0_m4->Write();
		hst_FT0_m2->Write();
		hst_FT0_p2->Write();
		hst_FT0_p4->Write();
		hst_FT0_p8->Write();
		hst_FT0_p10->Write();
		hst_FT0_p15->Write();
		hst_FT0_p30->Write();
		
		hdeltaphill_FT0_m30->Write();
		hdeltaphill_FT0_m15->Write();
		hdeltaphill_FT0_m10->Write();
		hdeltaphill_FT0_m8->Write();
		hdeltaphill_FT0_m4->Write();
		hdeltaphill_FT0_m2->Write();
		hdeltaphill_FT0_p2->Write();
		hdeltaphill_FT0_p4->Write();
		hdeltaphill_FT0_p8->Write();
		hdeltaphill_FT0_p10->Write();
		hdeltaphill_FT0_p15->Write();
		hdeltaphill_FT0_p30->Write();

		hdeltaRll_FT0_m30->Write();
		hdeltaRll_FT0_m15->Write();
		hdeltaRll_FT0_m10->Write();
		hdeltaRll_FT0_m8->Write();
		hdeltaRll_FT0_m4->Write();
		hdeltaRll_FT0_m2->Write();
		hdeltaRll_FT0_p2->Write();
		hdeltaRll_FT0_p4->Write();
		hdeltaRll_FT0_p8->Write();
		hdeltaRll_FT0_p10->Write();
		hdeltaRll_FT0_p15->Write();
		hdeltaRll_FT0_p30->Write();


		file->Close();
		return true;
	}

class ControlRegion_ttbar:public HistCollection{
	protected:
		bool LepID(const LepInfo &lep){
                        return (lep.tight==1);
                }

                bool FatJetID(const FatJetInfo &fatjet){
	  		return (fatjet.sdmass<=105. && fatjet.sdmass>=65. && fatjet.pt>200.);
			//return true;
                        //return (fatjet.WPid>=1);
                }

		bool Cut(const Event &evt){
			if(!(evt.lep.size()==1)) return false;
			//if(abs(evt.lep.at(0).pdgid)!=11) return false;
			if(!(evt.fatjet.size()==1)) return false;
			//if(evt.lep.at(0).pdgid * evt.lep.at(1).pdgid==121 && abs(evt.mll-mZ)<20) return false;
			//if(evt.scale!=1 && evt.nbmedium==0) hnbmedium->Fill(0.,evt.scale);
			if(!(evt.nbmedium>=2)) return false;
			return true;
		}
};



