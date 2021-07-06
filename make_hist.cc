#include "make_hist.h"
#define LUMI 59.74

class SignalRegion:public HistCollection{
	protected:
		bool cut(Event &evt){
			if(evt.fatjet.size()==0) return true;
			return false;
		}
};
int make_hist(){
	//WWW
	SignalRegion *WWW=new SignalRegion;
	WWW->Fill(LUMI,0.2086,"./WWW.root");
	WWW->Write("./hWWW.root");
	delete WWW;
	//WWW
	return 0;
}
