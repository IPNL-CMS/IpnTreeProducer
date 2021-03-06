#!/bin/bash
# Small screept to collect results on cuts
# Written by O.Bondu (June 2010)

syntax="Syntax ${0} {sample}"

if [[ -z ${1} ]]
then
  echo ${syntax}
  exit 1
fi

sample=${1}

nTotEventsSelectedRuns=0
nSelectedEvents=0
nEventsWithScHigherThan2GeV=0
nTotPhotons=0
nCut1=0
nCut2=0
nCut3=0
nCut4=0
nCut5=0
nCut6=0
nCut7=0
nCut8=0
nCut9=0
nCut10=0
nCut11=0
nCut12=0
nCut13=0
nCut14=0
nCut15=0
nSelectedPhotons=0
nTotSC=0
nSCAfterCut1=0
nSCAfterCut2=0
nSCAfterCut3=0
nSCAfterCut4=0
nSCAfterCut5=0
nSCAfterCut6=0
nSCAfterCut7=0
nSCAfterCut8=0
nSelectedSC=0

echo "" > TEMP_${sample}

numberOfFiles=`'ls' ${sample}_*.out | grep -v ALL | wc -l`
for (( ifile=0 ; ifile<${numberOfFiles} ; ifile++ ))
do
	echo "Scanning file ${sample}_${ifile}.out"
	for cut in `echo "nTotEventsSelectedRuns nSelectedEvents nEventsWithScHigherThan2GeV nSelectedPhotons nTotPhotons nCut1 nCut2 nCut3 nCut4 nCut5 nCut6 nCut7 nCut8 nCut9 nCut10 nCut11 nCut12 nCut13 nCut14 nCut15 nTotSC nSelectedSC nSCAfterCut1 nSCAfterCut2 nSCAfterCut3 nSCAfterCut4 nSCAfterCut5 nSCAfterCut6 nSCAfterCut7 nSCAfterCut8"`
	do
		cat ${sample}_${ifile}.out | grep = | sed 's/  /\n/g' | sed 's/\t/\n/g' | grep "${cut}=" | grep -v "\%" | sed 's/=/ /g' >> TEMP_${sample}
	done
done

nTotEventsSelectedRuns=`cat TEMP_${sample} | grep nTotEventsSelectedRuns | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSelectedEvents=`cat TEMP_${sample} | grep nSelectedEvents | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nEventsWithScHigherThan2GeV=`cat TEMP_${sample} | grep nEventsWithScHigherThan2GeV | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSelectedPhotons=`cat TEMP_${sample} | grep nSelectedPhotons | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nTotPhotons=`cat TEMP_${sample} | grep nTotPhotons | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut1=`cat TEMP_${sample} | grep "nCut1 " | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut2=`cat TEMP_${sample} | grep "nCut2 " | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut3=`cat TEMP_${sample} | grep "nCut3 " | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut4=`cat TEMP_${sample} | grep nCut4 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut5=`cat TEMP_${sample} | grep nCut5 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut6=`cat TEMP_${sample} | grep nCut6 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut7=`cat TEMP_${sample} | grep nCut7 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut8=`cat TEMP_${sample} | grep nCut8 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut9=`cat TEMP_${sample} | grep nCut9 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut10=`cat TEMP_${sample} | grep nCut10 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut11=`cat TEMP_${sample} | grep nCut11 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut12=`cat TEMP_${sample} | grep nCut12 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut13=`cat TEMP_${sample} | grep nCut13 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut14=`cat TEMP_${sample} | grep nCut14 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nCut15=`cat TEMP_${sample} | grep nCut15 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nTotSC=`cat TEMP_${sample} | grep nTotSC | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSelectedSC=`cat TEMP_${sample} | grep nSelectedSC | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSCAfterCut1=`cat TEMP_${sample} | grep nSCAfterCut1 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSCAfterCut2=`cat TEMP_${sample} | grep nSCAfterCut2 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSCAfterCut3=`cat TEMP_${sample} | grep nSCAfterCut3 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSCAfterCut4=`cat TEMP_${sample} | grep nSCAfterCut4 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSCAfterCut5=`cat TEMP_${sample} | grep nSCAfterCut5 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSCAfterCut6=`cat TEMP_${sample} | grep nSCAfterCut6 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSCAfterCut7=`cat TEMP_${sample} | grep nSCAfterCut7 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
nSCAfterCut8=`cat TEMP_${sample} | grep nSCAfterCut8 | awk 'BEGIN {SUM=0} {SUM+=$2} END {print SUM}'`
echo ""
rm TEMP_${sample}
echo "nTotEventsSelectedRuns= ${nTotEventsSelectedRuns}"
echo "nSelectedEvents= ${nSelectedEvents}"
echo "nEventsWithScHigherThan2GeV= ${nEventsWithScHigherThan2GeV}"
echo "*****************************************************"
echo ""
echo "nTotPhotons= ${nTotPhotons}"
echo "nCut1= ${nCut1}"
echo "nCut2= ${nCut2}"
echo "nCut3= ${nCut3}"
echo "nCut4= ${nCut4}"
echo "nCut5= ${nCut5}"
echo "nCut6= ${nCut6}"
echo "nCut7= ${nCut7}"
echo "nCut8= ${nCut8}"
echo "nCut9= ${nCut9}"
echo "nCut10= ${nCut10}"
echo "nCut11= ${nCut11}"
echo "nCut12= ${nCut12}"
echo "nCut13= ${nCut13}"
echo "nCut14= ${nCut14}"
echo "nCut15= ${nCut15}"
echo ""
echo "nSelectedPhotons= ${nSelectedPhotons}"
echo "*****************************************************"
echo ""
echo "nTotSC= ${nTotSC}"
echo "nSCAfterCut1= ${nSCAfterCut1}"
echo "nSCAfterCut2= ${nSCAfterCut2}"
echo "nSCAfterCut3= ${nSCAfterCut3}"
echo "nSCAfterCut4= ${nSCAfterCut4}"
echo "nSCAfterCut5= ${nSCAfterCut5}"
echo "nSCAfterCut6= ${nSCAfterCut6}"
echo "nSCAfterCut7= ${nSCAfterCut7}"
echo "nSCAfterCut8= ${nSCAfterCut8}"
echo ""
echo "nSelectedSC= ${nSelectedSC}"

exit 0

