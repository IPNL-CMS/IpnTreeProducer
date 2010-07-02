#!/bin/bash
# Commands to launch the plots production on batch
# Written by O.Bondu (June 2010)

##############################################################
### Photon plots
##############################################################
for sample in `echo "MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1 MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1"`;
#for sample in `echo "MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1"`;
do
	counter=0;
	for cut in `echo "isAfterCut10 isAfterCut10_EB isAfterCut10_EE isAfterCut10_EEM isAfterCut10_EEP"`;
#	for cut in `echo "isAfterCut10"`;
	do
		echo -e "\n${sample}\t\t${cut}";
		cp plotDataMC_TDR_miniTree.C plotDataMC_TDR_miniTree_${sample}_${cut}.C;
		sed -i -e "/Plots for the photons/s/false/true/g" plotDataMC_TDR_miniTree_${sample}_${cut}.C;
		sed -i -e "/${sample}/s/^\/\///g" -e "/\"${cut}\"/{s_^\/\/__g;n;s_^\/\/__g;}" plotDataMC_TDR_miniTree_${sample}_${cut}.C;
		g++ plotDataMC_TDR_miniTree_${sample}_${cut}.C `root-config --libs --cflags` -m32 -O3 -o plotDataMC_TDR_miniTree_${sample}_${cut};
		cp batch_template.sh batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
		sed -i -e "s/TotoAna_miniTree_TEMPLATE/plotDataMC_TDR_miniTree_${sample}_${cut}/g" -e "s/TEMPLATE/Ph_${sample}_${counter}/g" batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
		qsub batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
		counter=$[${counter}+1];
	done
done

##############################################################
### SuperClu plots
##############################################################
for sample in `echo "MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1 MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1"`;
#for sample in `echo "MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1"`;
do
  counter=0;
  for cut in `echo "isAfterCut7 isAfterCut7_EE isAfterCut7_EB isAfterCut7_EEM isAfterCut7_EEP isAfterCut7_RawEtGT2 isAfterCut7_RawEtGT2_EE isAfterCut7_RawEtGT2_EB isAfterCut7_RawEtGT2_EEM isAfterCut7_RawEtGT2_EEP isAfterCut7_RawEtGT4 isAfterCut7_RawEtGT4_EE isAfterCut7_RawEtGT4_EB isAfterCut7_RawEtGT4_EEM isAfterCut7_RawEtGT4_EEP isAfterCut7_RawEtGT10 isAfterCut7_RawEtGT10_EE isAfterCut7_RawEtGT10_EB isAfterCut7_RawEtGT10_EEM isAfterCut7_RawEtGT10_EEP"`;
#	for cut in `echo "isAfterCut7"`;
  do
    echo -e "\n${sample}\t\t${cut}";
    cp plotDataMC_TDR_miniTree.C plotDataMC_TDR_miniTree_${sample}_${cut}.C;
		sed -i -e "/Plots for super-clusters/s/false/true/g" plotDataMC_TDR_miniTree_${sample}_${cut}.C;
    sed -i -e "/${sample}/s/^\/\///g" -e "/\"${cut}\"/{s_^\/\/__g;n;s_^\/\/__g;}" plotDataMC_TDR_miniTree_${sample}_${cut}.C;
    g++ plotDataMC_TDR_miniTree_${sample}_${cut}.C `root-config --libs --cflags` -m32 -O3 -o plotDataMC_TDR_miniTree_${sample}_${cut};
    cp batch_template.sh batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
    sed -i -e "s/TotoAna_miniTree_TEMPLATE/plotDataMC_TDR_miniTree_${sample}_${cut}/g" -e "s/TEMPLATE/SC_${sample}_${counter}/g" batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
    qsub batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
    counter=$[${counter}+1];
  done
done

##############################################################
### Event plots
##############################################################
for sample in `echo "MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1 MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1"`;
#for sample in `echo "MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1"`;
do
  counter=0;
  for cut in `echo "NoCuts"`;
  do
    echo -e "\n${sample}\t\t${cut}";
    cp plotDataMC_TDR_miniTree.C plotDataMC_TDR_miniTree_${sample}_${cut}.C;
		sed -i -e "/Plots for the events/s/false/true/g" plotDataMC_TDR_miniTree_${sample}_${cut}.C;
    sed -i -e "/${sample}/s/^\/\///g" -e "/\"${cut}\"/{s_^\/\/__g;n;s_^\/\/__g;}" plotDataMC_TDR_miniTree_${sample}_${cut}.C;
    g++ plotDataMC_TDR_miniTree_${sample}_${cut}.C `root-config --libs --cflags` -m32 -O3 -o plotDataMC_TDR_miniTree_${sample}_${cut};
    cp batch_template.sh batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
    sed -i -e "s/TotoAna_miniTree_TEMPLATE/plotDataMC_TDR_miniTree_${sample}_${cut}/g" -e "s/TEMPLATE/Ev_${sample}_${counter}/g" batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
    qsub batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
    counter=$[${counter}+1];
  done
done

##############################################################
### 2D plots
##############################################################
for sample in `echo "MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1 MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1 MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1"`;
do
  for cut in `echo "2D"`;
  do
    echo -e "\n${sample}\t\t${cut}";
    cp plotDataMC_TDR_miniTree.C plotDataMC_TDR_miniTree_${sample}_${cut}.C;
    sed -i -e "/2D plots/s/false/true/g" plotDataMC_TDR_miniTree_${sample}_${cut}.C;
    sed -i -e "/${sample}/s/^\/\///g" plotDataMC_TDR_miniTree_${sample}_${cut}.C;
    g++ plotDataMC_TDR_miniTree_${sample}_${cut}.C `root-config --libs --cflags` -m32 -O3 -o plotDataMC_TDR_miniTree_${sample}_${cut};
    cp batch_template.sh batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
    sed -i -e "s/TotoAna_miniTree_TEMPLATE/plotDataMC_TDR_miniTree_${sample}_${cut}/g" -e "s/TEMPLATE/Ev_${sample}_${counter}/g" batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
    qsub batch_plotDataMC_TDR_miniTree_${sample}_${cut}.sh;
  done
done




exit 0



