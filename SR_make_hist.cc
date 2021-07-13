#include "make_hist.h"
#define mZ 91
#define LUMI2018 59.74

class SignalRegion:public HistCollection{
	protected:
		bool cut(Event &evt){
			if(!(evt.lep.size()==2)) return false;
			if(!(evt.fatjet.size()==1)) return false;
			if(!(evt.nbmedium==0)) return false;
			if(!(abs(evt.mll-mZ)>20)) return false;
			if(!(evt.lep.at(0).pt>40 && evt.lep.at(1).pt>30)) return false;
			return true;
		}
};
int SR_make_hist(){
	//ttbar
	SignalRegion *ttbar=new SignalRegion;
        ttbar->Fill(LUMI2018,72.1,"../MC/2018/TTTo2L2Nu.root");
        ttbar->Fill(LUMI2018,365.34,"../MC/2018/TTToSemiLeptonic.root");
        ttbar->Write("../hist/SR/httbar.root");
	delete ttbar;
	//ttbar
	//ttW
	SignalRegion *ttW=new SignalRegion;
	ttW->Fill(LUMI2018,0.2043,"../MC/2018/TTWJetsToLNu.root");
	ttW->Write("../hist/SR/httW.root");
	delete ttW;
	//ttW
	//ttZ
	SignalRegion *ttZ=new SignalRegion;
	ttZ->Fill(LUMI2018,0.0493,"../MC/2018/TTZToLL_M-1to10.root");
	ttZ->Fill(LUMI2018,0.2529,"../MC/2018/TTZToLLNuNu_M-10.root");
	ttZ->Write("../hist/SR/httZ.root");
	delete ttZ;
	//ttZ
	//DY
	SignalRegion *DY=new SignalRegion;
	DY->Fill(LUMI2018,20657,"../MC/2018/DYJetsToLL_M-10to50.root");
	DY->Fill(LUMI2018,6197.9,"../MC/2018/DYJetsToLL_M-50.root");
	DY->Write("../hist/SR/hDY.root");
	delete DY;
	//DY
	//WZ
	SignalRegion *WZ=new SignalRegion;
	WZ->Fill(LUMI2018,4.4297,"../MC/2018/WZTo3LNu.root");
	WZ->Write("../hist/SR/hWZ.root");
	delete WZ;
	//WZ
	//WW
	SignalRegion *WW=new SignalRegion;
	WW->Fill(LUMI2018,118.71,"../MC/2018/WW.root");
	WW->Fill(LUMI2018,1.617,"../MC/2018/WW_DoubleScattering.root");
	WW->Fill(LUMI2018,0.0539,"../MC/2018/WpWpJJ.root");
	WW->Write("../hist/SR/hWW.root");
	delete WW;
	//WW
	//ZZ
	SignalRegion *ZZ=new SignalRegion;
	ZZ->Fill(LUMI2018,1.256,"../MC/2018/ZZTo4L.root");
	ZZ->Write("../hist/SR/hZZ.root");
	delete ZZ;
	//ZZ
	//Wjets
	SignalRegion *Wjets=new SignalRegion;
	Wjets->Fill(LUMI2018,1603.5,"../MC/2018/WJetsToLNu_HT-100To200.root");
	Wjets->Fill(LUMI2018,473.97,"../MC/2018/WJetsToLNu_HT-200To400.root");
        Wjets->Fill(LUMI2018,67.348,"../MC/2018/WJetsToLNu_HT-400To600.root");
        Wjets->Fill(LUMI2018,16.928,"../MC/2018/WJetsToLNu_HT-600To800.root");
        Wjets->Fill(LUMI2018,7.4483,"../MC/2018/WJetsToLNu_HT-800To1200.root");
	Wjets->Fill(LUMI2018,1.7978,"../MC/2018/WJetsToLNu_HT-1200To2500.root");
	Wjets->Fill(LUMI2018,0.038914,"../MC/2018/WJetsToLNu_HT-2500ToInf.root");
	Wjets->Write("../hist/SR/hWjets.root");
	delete Wjets;
	//Wjets
	//WWW
	SignalRegion *WWW=new SignalRegion;
	WWW->Fill(LUMI2018,0.2086,"../MC/2018/WWW.root");
	WWW->Write("../hist/SR/hWWW.root");
	delete WWW;
	//WWW
	return 0;
}
