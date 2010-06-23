#!/bin/bash
# Commands to launch the miniTree production on batch
# Written by O.Bondu (June 2010)

##############################################################
### DATA
##############################################################
for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27;
do
	base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
	cp ${base}.C ${base}_DATA_${i}.C;
	sed -i -e "/DATA/s/false/true/g" ${base}_DATA_${i}.C;
	sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=$[${i}*2250000]; ievt<$[${i}*2250000+1*2250000]; ievt++)/g" ${base}_DATA_${i}.C;
	sed -i -e "s/miniTree_DATA.root/miniTree_DATA__${i}.root/g" ${base}_DATA_${i}.C;
	g++ ${base}_DATA_${i}.C `root-config --libs --cflags` -m32 -O3 -o ${base}_DATA_${i};
done

base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
cp ${base}.C ${base}_DATA_28.C;
sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=60750000; ievt<61064434; ievt++)/g" ${base}_DATA_28.C;
sed -i -e "s/miniTree_DATA.root/miniTree_DATA__28.root/g" ${base}_DATA_28.C;
g++ ${base}_DATA_28.C `root-config --libs --cflags` -m32 -O3 -o ${base}_DATA_28;

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28;
do
	cp batch_template.sh batch_DATA_${i}.sh;
	sed -i -e "s/TEMPLATE/DATA_${i}/g" batch_DATA_${i}.sh; qsub batch_DATA_${i}.sh;
done

##############################################################
### MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1
##############################################################
for i in 0 1 2;
do
	base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
	cp ${base}.C ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	sed -i -e "/MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1/s/false/true/g" ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=$[${i}*2250000]; ievt<$[${i}*2250000+1*2250000]; ievt++)/g" ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	sed -i -e "s/miniTree_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root/miniTree_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1___${i}.root/g" ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	g++ ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C `root-config --libs --cflags` -m32 -O3 -o ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i};
done

base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
cp ${base}.C ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_3.C;
sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=6750000; ievt<7255858; ievt++)/g" ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_3.C;
sed -i -e "s/miniTree_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root/miniTree_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1___3.root/g" ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_3.C;
g++ ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_3.C `root-config --libs --cflags` -m32 -O3 -o ${base}_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_3;

for i in 0 1 2 3;
do
	cp batch_template.sh batch_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.sh;
	sed -i -e "s/TEMPLATE/MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}/g" batch_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.sh;
	qsub batch_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.sh;
done


##############################################################
### MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1
##############################################################
for i in 0 1 2;
do
	base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
	cp ${base}.C ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
  sed -i -e "/MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1/s/false/true/g" ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=$[${i}*2250000]; ievt<$[${i}*2250000+1*2250000]; ievt++)/g" ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	sed -i -e "s/miniTree_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root/miniTree_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1___${i}.root/g" ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	g++ ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C `root-config --libs --cflags` -m32 -O3 -o ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i};
done

base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
cp ${base}.C ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_3.C;
sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=6750000; ievt<8534549; ievt++)/g" ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_3.C;
sed -i -e "s/miniTree_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root/miniTree_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1___3.root/g" ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_3.C;
g++ ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_3.C `root-config --libs --cflags` -m32 -O3 -o ${base}_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_3;

for i in 0 1 2 3;
do
	cp batch_template.sh batch_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.sh;
	sed -i -e "s/TEMPLATE/MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}/g" batch_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.sh;
	qsub batch_MC_MinBias_TuneP0_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.sh;
done


##############################################################
### MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1
##############################################################
for i in 0 1 2;
do
	base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
	cp ${base}.C ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i}.C;
  sed -i -e "/MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1/s/false/true/g" ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i}.C;
	sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=$[${i}*2250000]; ievt<$[${i}*2250000+1*2250000]; ievt++)/g" ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i}.C;
	sed -i -e "s/miniTree_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root/miniTree_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1___${i}.root/g" ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i}.C;
	g++ ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i}.C `root-config --libs --cflags` -m32 -O3 -o ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i};
done

base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
cp ${base}.C ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_3.C;
sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=6750000; ievt<8336188; ievt++)/g" ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_3.C;
sed -i -e "s/miniTree_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root/miniTree_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1___3.root/g" ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_3.C;
g++ ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_3.C `root-config --libs --cflags` -m32 -O3 -o ${base}_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_3;

for i in 0 1 2 3;
do
	cp batch_template.sh batch_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i}.sh;
	sed -i -e "s/TEMPLATE/MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i}/g" batch_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i}.sh;
	qsub batch_MC_MinBias_7TeV-pythia8_Spring10-START3X_V26B-v1_${i}.sh;
done


##############################################################
### MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1
##############################################################
for i in 0 1;
do
	base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
	cp ${base}.C ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
  sed -i -e "/MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1/s/false/true/g" ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=$[${i}*2250000]; ievt<$[${i}*2250000+1*2250000]; ievt++)/g" ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	sed -i -e "s/miniTree_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root/miniTree_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1___${i}.root/g" ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C;
	g++ ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.C `root-config --libs --cflags` -m32 -O3 -o ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i};
done

base=`echo "TotoAna_miniTree.C" | cut -d . -f -1`;
cp ${base}.C ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_2.C;
sed -i -e "s/for(unsigned int ievt=0; ievt<nTotEvents; ievt++)/for(unsigned int ievt=4500000; ievt<5305984; ievt++)/g" ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_2.C;
sed -i -e "s/miniTree_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root/miniTree_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1___2.root/g" ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_2.C;
g++ ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_2.C `root-config --libs --cflags` -m32 -O3 -o ${base}_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_2;

for i in 0 1 2;
do
	cp batch_template.sh batch_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.sh;
	sed -i -e "s/TEMPLATE/MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}/g" batch_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.sh;
	qsub batch_MC_QCD_Pt-15_7TeV-pythia6_Spring10-START3X_V26B-v1_${i}.sh;
done

exit 0;

