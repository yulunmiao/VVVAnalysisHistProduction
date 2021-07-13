#!/bin/bash

if [ $# -lt 2 ]
then
	echo "ERROR:Please input the correct parameters(year, jobdir)"
	exit 1
fi

if [ $1 -ne 2016 ] && [ $1 -ne 2017 ] && [ $1 -ne 2018 ]
then 
	echo "ERROR:Please input the correct year(2016 ,2017, 2018)"
	exit 1
fi

year=$1
dir=../MC/$year
jobdir=$2

if [ ! -d ../MC ]
then
	mkdir ../MC
fi

if [ -d $dir ]
then
        echo "ERROR:Directory for year $year alright exists!"
        exit 1
fi

mkdir $dir

#hadd $dir/name.root $jobdir/$year/*/output*
if [ $year -eq 2018 ]
then
	hadd $dir/TTTo2L2Nu.root $jobdir/$year/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8*/output*
	hadd $dir/TTToSemiLeptonic.root $jobdir/$year/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8*/output*
	hadd $dir/TTWJetsToLNu.root $jobdir/$year/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8*/output*
	hadd $dir/TTZToLL_M-1to10.root $jobdir/$year/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8*/output*
	hadd $dir/TTZToLLNuNu_M-10.root $jobdir/$year/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8*/output*
	hadd $dir/DYJetsToLL_M-10to50.root $jobdir/$year/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8*/output*
	hadd $dir/DYJetsToLL_M-50.root $jobdir/$year/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8*/output*
	hadd $dir/WZTo3LNu.root $jobdir/$year/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8*/output*
	hadd $dir/WW.root $jobdir/$year/WW_TuneCP5_13TeV-pythia8*/output*
	hadd $dir/WW_DoubleScattering.root $jobdir/$year/WW_DoubleScattering_13TeV-pythia8*/output*
	hadd $dir/WpWpJJ.root $jobdir/$year/WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8*/output*
	hadd $dir/ZZTo4L.root $jobdir/$year/ZZTo4L_TuneCP5_13TeV_powheg_pythia8*/output*
	hadd $dir/WJetsToLNu_HT-100To200.root $jobdir/$year/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8*/output*
	hadd $dir/WJetsToLNu_HT-200To400.root $jobdir/$year/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8*/output*
	hadd $dir/WJetsToLNu_HT-400To600.root $jobdir/$year/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8*/output*
	hadd $dir/WJetsToLNu_HT-600To800.root $jobdir/$year/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8*/output*
	hadd $dir/WJetsToLNu_HT-800To1200.root $jobdir/$year/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8*/output*
	hadd $dir/WJetsToLNu_HT-1200To2500.root $jobdir/$year/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8*/output*
        hadd $dir/WJetsToLNu_HT-2500ToInf.root $jobdir/$year/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8*/output*
	hadd $dir/WWW.root $jobdir/$year/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8*/output*
fi
