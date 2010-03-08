# Needed to re-run Egamma Reco
from RecoEgamma.Configuration.RecoEgamma_cff import *

# Replace RecoEgamma/EgammaPhotonProducers/python/photons_cfi.py parameters
photons.minSCEtBarrel = 1.
photons.minSCEtEndcap =1.
photonCore.minSCEt = 1.

# Replace RecoEgamma/EgammaPhotonProducers/python/photons_cfi.py parameters
# (from RecoEgamma/PhotonIdentification/python/isolationCalculator_cfi.py)
photons.isolationSumsCalculatorSet.isolationtrackThresholdA_Barrel=0.7
photons.isolationSumsCalculatorSet.isolationtrackThresholdB_Barrel=0.7
photons.isolationSumsCalculatorSet.isolationtrackThresholdA_Endcap=0.7
photons.isolationSumsCalculatorSet.isolationtrackThresholdB_Endcap=0.7

photons.isolationSumsCalculatorSet.transImpactParameterA_Barrel=999.
photons.isolationSumsCalculatorSet.transImpactParameterB_Barrel=999.
photons.isolationSumsCalculatorSet.transImpactParameterA_Endcap=999.
photons.isolationSumsCalculatorSet.transImpactParameterB_Endcap=999.

photons.isolationSumsCalculatorSet.longImpactParameterA_Barrel=999.
photons.isolationSumsCalculatorSet.longImpactParameterB_Barrel=999.
photons.isolationSumsCalculatorSet.longImpactParameterA_Endcap=999.
photons.isolationSumsCalculatorSet.longImpactParameterB_Endcap=999.
