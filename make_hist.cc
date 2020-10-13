#include "make_hist.h"
#define LUMI 59.74

int make_hist(){
	//ttbar
	HistCollection ttbar;
        ttbar.Fill(LUMI,72.1,"./MC/2018/TTTo2L2Nu.root");
        ttbar.Fill(LUMI,365.34,"./MC/2018/TTToSemiLeptonic.root");
        ttbar.Write("./hist/2018/httbar.root");
	//ttbar
	//ttW
	HistCollection ttW;
	ttW.Fill(LUMI,0.2043,"./MC/2018/TTWJetsToLNu.root");
	ttW.Write("./hist/2018/httW.root");
	//ttW
	//ttZ
	HistCollection ttZ;
	ttZ.Fill(LUMI,0.0493,"./MC/2018/TTZToLL_M-1to10.root");
	ttZ.Fill(LUMI,0.2529,"./MC/2018/TTZToLLNuNu_M-10.root");
	ttZ.Write("./hist/2018/httZ.root");
	//ttZ
	//DY
	HistCollection DY;
	DY.Fill(LUMI,20657,"./MC/2018/DYJetsToLL_M-10to50.root");
	DY.Fill(LUMI,6197.9,"./MC/2018/DYJetsToLL_M-50.root");
	DY.Write("./hist/2018/hDY.root");
	//DY
	//WZ
	HistCollection WZ;
	WZ.Fill(LUMI,4.4296,"./MC/2018/WZTo3LNu.root");
	WZ.Write("./hist/2018/hWZ.root");
	//WZ
	//WW
	HistCollection WW;
	WW.Fill(LUMI,118.71,"./MC/2018/WW.root");
	WW.Fill(LUMI,1.617,"./MC/2018/WW_DoubleScattering.root");
	WW.Fill(LUMI,0.0539,"./MC/2018/WpWpJJ.root");
	WW.Write("./hist/2018/hWW.root");
	//WW
	//ZZ
	HistCollection ZZ;
	ZZ.Fill(LUMI,1.256,"./MC/2018/ZZTo4L.root");
	ZZ.Write("./hist/2018/hZZ.root");
	//ZZ
	//Wjets
	HistCollection Wjets;
	Wjets.Fill(LUMI,1676.9,"./MC/2018/WJetsToLNu_HT-100To200.root");
	Wjets.Fill(LUMI,494.43,"./MC/2018/WJetsToLNu_HT-200To400.root");
        Wjets.Fill(LUMI,70.189,"./MC/2018/WJetsToLNu_HT-400To600.root");
        Wjets.Fill(LUMI,17.439,"./MC/2018/WJetsToLNu_HT-600To800.root");
        Wjets.Fill(LUMI,7.8077,"./MC/2018/WJetsToLNu_HT-800To1200.root");
	Wjets.Write("./hist/2018/hWjets.root");
	//Wjets
	//WWW
	HistCollection WWW;
	WWW.Fill(LUMI,0.2086,"./MC/2018/WWW.root");
	WWW.Write("./hist/2018/hWWW.root");
	//WWW
	return 0;
}
