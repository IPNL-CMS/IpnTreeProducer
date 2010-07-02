#!/usr/local/bin/bash
#PBS -l platform=LINUX,u_sps_cmsf
#PBS -l T=680000
#PBS -q T
#PBS -l M=512MB
#PBS -N TEMPLATE               # Job Name
#PBS -o TEMPLATE.out
#PBS -e TEMPLATE.err

export HOMEDIR=/afs/in2p3.fr/home/o/obondu
source ${HOMEDIR}/358p3.sh

echo "ROOTSYS :"
echo ${ROOTSYS}

echo "LD_LIBRARY_PATH"
echo ${LD_LIBRARY_PATH}

WORKDIR=/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/macros_10GeV_woSC
echo "Move to WORKDIR ${WORKDIR}"
cd ${WORKDIR}
pwd


echo "Running actual job"
./TotoAna_miniTree_TEMPLATE

exit 0
