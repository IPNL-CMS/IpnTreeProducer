#!/bin/bash
# Small script to run hadd on miniTrees to concatene those in one miniTree__ALL.root
# Written by O. Bondu (June 2010)

for sample in `echo "DATA MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1 MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1"`
do
	echo "*********************************************"
	echo "Treating sample ${sample}"
	echo "*********************************************"

	if [[ -e miniTree_${sample}__ALL.root ]]
	then
		echo "miniTree_${sample}__ALL.root exists: deleting"
		rm miniTree_${sample}__ALL.root
	fi

	list=""
	for file in `ls miniTree_${sample}__*root`
	do
		list=`echo "${list} ${file}"`
	done
	#echo ${list}

	$ROOTSYS/bin/hadd miniTree_${sample}__ALL.root ${list}
	echo "miniTree_${sample}__ALL.root created"
	echo ""
done

exit 0
