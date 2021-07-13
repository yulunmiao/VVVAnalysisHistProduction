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
dir=../data/$year
jobdir=$2

if [ ! -d ../data ]
then
	mkdir ../data
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
	hadd $dir/DoubleMuon.root $jobdir/$year/DoubleMuon*/output*
	hadd $dir/EGamma.root $jobdir/$year/EGamma*/output*
	hadd $dir/MuonEG.root $jobdir/$year/MuonEG*/output*
fi
