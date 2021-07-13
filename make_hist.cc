#include "make_hist.h"
#define LUMI 59.74

class SignalRegion:public HistCollection{
	protected:
		bool cut(Event &evt){
			return true;
		}
};
int make_hist(){
	//WWW
	SignalRegion *WWW=new SignalRegion;
	WWW->Fill(LUMI,0.2086,"../MC/2018/WWW.root");
	WWW->Write("./hWWW.root");
	delete WWW;
	//WWW
	return 0;
}
