#include "make_hist_data.h"
#define mZ 91
#define LUMI2018 59.74


class ControlRegion_ttbar:public HistCollection{
	protected:
		bool cut(Event &evt){
			bool duplicates=false;
			long long RUNPREF=1000*1000;
			long long dupCheck = evt.run*RUNPREF + evt.event;
			for (unsigned int uid = 0; uid < checkDuplicates.size(); uid++){
				if (checkDuplicates[uid] == dupCheck){
					duplicates=true;
	 				break;
	     			}
			}
			if(duplicates==true) return false;
			checkDuplicates.push_back(dupCheck);

			if(!(evt.lep.size()==2)) return false;
			if(!(evt.fatjet.size()==1)) return false;
			if(!(evt.nbmedium>=1)) return false;
			if(!(abs(evt.mll-mZ)>20)) return false;
			if(!(evt.lep.at(0).pt>40 && evt.lep.at(1).pt>30)) return false;
			return true;
		}
};
int CR_ttbar_make_hist_data(){
	//data
	ControlRegion_ttbar *data=new ControlRegion_ttbar;
	data->Fill("../data/2018/DoubleMuon.root");
        data->Fill("../data/2018/EGamma.root");
	data->Fill("../data/2018/MuonEG.root");
        data->Write("../hist/CR_ttbar/hdata.root");
	delete data;
	//data
	return 0;
}
