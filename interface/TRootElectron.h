#ifndef TRootElectron_h
#define TRootElectron_h

#include <map>

#include "../interface/TRootParticle.h"

using namespace std;

class TRootSuperCluster;

class TRootElectron : public TRootParticle
{
   
public:
   
   TRootElectron() :
   TRootParticle()
   ,classification_(-9999)
   ,fbrem_(-9999.)
   ,numberOfBrems_(-9999)
   ,caloEnergy_(-9999.)
   ,caloEnergyError_(-9999.)
   ,trackMomentum_(-9999.)
   ,trackMomentumError_(-9999.)
   ,trackMissedInnerLayers_(-1)
   ,distConvPartner_(-9999.)
   ,dcotConvPartner_(-9999.)
   ,radiusConv_(-9999.)
   ,hadOverEm_(-9999.)
   ,deltaEtaIn_(-9999.)
   ,deltaPhiIn_(-9999.)
   ,energySuperClusterOverPin_(-9999.)
   ,deltaEtaOut_(-9999.)
   ,deltaPhiOut_(-9999.)
   ,energySeedClusterOverPout_(-9999.)
   ,energyScaleCorrected_(false)
   ,dr03TkSumPt_(-9999.)
   ,dr03EcalRecHitSumEt_(-9999.)
   ,dr03HcalDepth1TowerSumEt_(-9999.)
   ,dr03HcalDepth2TowerSumEt_(-9999.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,pixelLayersWithMeasurement_(-1)
   ,stripLayersWithMeasurement_(-1)
   ,d0_(-9999.)
   ,d0Error_(-9999.)
   ,dsz_(-9999.)
   ,dszError_(-9999.)
   ,dB_(-9999.)
   ,normalizedChi2_(-9999.)
   ,ptError_(-9999.)
   ,etaError_(-9999.)
   ,phiError_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,nbClusters_(-9999)
   ,superClusterRawEnergy_(-9999.)
   ,preshowerEnergy_(-9999.)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-9999)
   ,caloConeSize_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,trackIso_(-9999)
   ,ecalIso_(-9999)
   ,hcalIso_(-9999)
   //,swissCross_(-9999)
   ,pfParticleIso_(-9999)
   ,pfChargedHadronIso_(-9999)
   ,pfNeutralHadronIso_(-9999)
   ,pfPhotonIso_(-9999)
   ,idCutBasedFixedThresholdLoose_(-1)
   ,idCutBasedFixedThresholdTight_(-1)
   ,idCutBasedFixedThresholdHighEnergy_(-1)
   ,idCutBasedCategorizedLoose_(-1)
   ,idCutBasedCategorizedTight_(-1)
   ,idLikelihood_(-9999.)
   ,idNeuralNet_(-9999.)
   ,idCutBasedsimpleEleId70cIso_(-1)
   ,idCutBasedsimpleEleId95cIso_(-1)
   ,idCutBasedsimpleEleId70relIso_(-1)
   ,idCutBasedsimpleEleId95relIso_(-1)
   ,isAlsoPhoton_(false)
   {;}
   
   TRootElectron(const TRootElectron& electron) :
   TRootParticle(electron)
   ,classification_(electron.classification_)
   ,fbrem_(electron.fbrem_)
   ,numberOfBrems_(electron.numberOfBrems_)
   ,caloEnergy_(electron.caloEnergy_)
   ,caloEnergyError_(electron.caloEnergyError_)
   ,trackMomentum_(electron.trackMomentum_)
   ,trackMomentumError_(electron.trackMomentumError_)
   ,trackMissedInnerLayers_(electron.trackMissedInnerLayers_)
   ,distConvPartner_(electron.distConvPartner_)
   ,dcotConvPartner_(electron.dcotConvPartner_)
   ,radiusConv_(electron.radiusConv_)
   ,hadOverEm_(electron.hadOverEm_)
   ,deltaEtaIn_(electron.deltaEtaIn_)
   ,deltaPhiIn_(electron.deltaPhiIn_)
   ,energySuperClusterOverPin_(electron.energySuperClusterOverPin_)
   ,deltaEtaOut_(electron.deltaEtaOut_)
   ,deltaPhiOut_(electron.deltaPhiOut_)
   ,energySeedClusterOverPout_(electron.energySeedClusterOverPout_)
   ,energyScaleCorrected_(electron.energyScaleCorrected_)
   ,dr03TkSumPt_(electron.dr03TkSumPt_)
   ,dr03EcalRecHitSumEt_(electron.dr03EcalRecHitSumEt_)
   ,dr03HcalDepth1TowerSumEt_(electron.dr03HcalDepth1TowerSumEt_)
   ,dr03HcalDepth2TowerSumEt_(electron.dr03HcalDepth2TowerSumEt_)
   ,sigmaEtaEta_(electron.sigmaEtaEta_)
   ,sigmaIetaIeta_(electron.sigmaIetaIeta_)
   ,pixelLayersWithMeasurement_(electron.pixelLayersWithMeasurement_)
   ,stripLayersWithMeasurement_(electron.stripLayersWithMeasurement_)
   ,d0_(electron.d0_)
   ,d0Error_(electron.d0Error_)
   ,dsz_(electron.dsz_)
   ,dszError_(electron.dszError_)
   ,dB_(electron.dB_)
   ,normalizedChi2_(electron.normalizedChi2_)
   ,ptError_(electron.ptError_)
   ,etaError_(electron.etaError_)
   ,phiError_(electron.phiError_)
   ,ip3DSignificance_(electron.ip3DSignificance_)
   ,nbClusters_(electron.nbClusters_)
   ,superClusterRawEnergy_(electron.superClusterRawEnergy_)
   ,preshowerEnergy_(electron.preshowerEnergy_)
   ,caloPosition_(electron.caloPosition_)
   ,scIndex_(electron.scIndex_)
   ,scRef_(electron.scRef_)
   ,clusterAlgo_(electron.clusterAlgo_)
   ,caloConeSize_(electron.caloConeSize_)
   ,e2x2_(electron.e2x2_)
   ,e3x3_(electron.e3x3_)
   ,e5x5_(electron.e5x5_)
   ,eMax_(electron.eMax_)
   ,trackIso_(electron.trackIso_)
   ,ecalIso_(electron.ecalIso_)
   ,hcalIso_(electron.hcalIso_)
   //,swissCross_(electron.swissCross_)
   ,pfParticleIso_(electron.pfParticleIso_)
   ,pfChargedHadronIso_(electron.pfChargedHadronIso_)
   ,pfNeutralHadronIso_(electron.pfNeutralHadronIso_)
   ,pfPhotonIso_(electron.pfPhotonIso_)
   ,idCutBasedFixedThresholdLoose_(electron.idCutBasedFixedThresholdLoose_)
   ,idCutBasedFixedThresholdTight_(electron.idCutBasedFixedThresholdTight_)
   ,idCutBasedFixedThresholdHighEnergy_(electron.idCutBasedFixedThresholdHighEnergy_)
   ,idCutBasedCategorizedLoose_(electron.idCutBasedCategorizedLoose_)
   ,idCutBasedCategorizedTight_(electron.idCutBasedCategorizedTight_)
   ,idLikelihood_(electron.idLikelihood_)
   ,idNeuralNet_(electron.idNeuralNet_)
   ,idCutBasedsimpleEleId70cIso_(electron.idCutBasedsimpleEleId70cIso_)
   ,idCutBasedsimpleEleId95cIso_(electron.idCutBasedsimpleEleId95cIso_)
   ,idCutBasedsimpleEleId70relIso_(electron.idCutBasedsimpleEleId70relIso_)
   ,idCutBasedsimpleEleId95relIso_(electron.idCutBasedsimpleEleId95relIso_)
   ,isAlsoPhoton_(electron.isAlsoPhoton_)
   {;}
   
   TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e) :
   TRootParticle(px,py,pz,e)
   ,classification_(-9999)
   ,fbrem_(-9999.)
   ,numberOfBrems_(-9999)
   ,caloEnergy_(-9999.)
   ,caloEnergyError_(-9999.)
   ,trackMomentum_(-9999.)
   ,trackMomentumError_(-9999.)
   ,trackMissedInnerLayers_(-1)
   ,distConvPartner_(-9999.)
   ,dcotConvPartner_(-9999.)
   ,radiusConv_(-9999.)
   ,hadOverEm_(-9999.)
   ,deltaEtaIn_(-9999.)
   ,deltaPhiIn_(-9999.)
   ,energySuperClusterOverPin_(-9999.)
   ,deltaEtaOut_(-9999.)
   ,deltaPhiOut_(-9999.)
   ,energySeedClusterOverPout_(-9999.)
   ,energyScaleCorrected_(false)
   ,dr03TkSumPt_(-9999.)
   ,dr03EcalRecHitSumEt_(-9999.)
   ,dr03HcalDepth1TowerSumEt_(-9999.)
   ,dr03HcalDepth2TowerSumEt_(-9999.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,pixelLayersWithMeasurement_(-1)
   ,stripLayersWithMeasurement_(-1)
   ,d0_(-9999.)
   ,d0Error_(-9999.)
   ,dsz_(-9999.)
   ,dszError_(-9999.)
   ,dB_(-9999.)
   ,normalizedChi2_(-9999.)
   ,ptError_(-9999.)
   ,etaError_(-9999.)
   ,phiError_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,nbClusters_(-9999)
   ,superClusterRawEnergy_(-9999.)
   ,preshowerEnergy_(-9999.)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-9999)
   ,caloConeSize_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,trackIso_(-9999)
   ,ecalIso_(-9999)
   ,hcalIso_(-9999)
   //,swissCross_(-9999)
   ,pfParticleIso_(-9999)
   ,pfChargedHadronIso_(-9999)
   ,pfNeutralHadronIso_(-9999)
   ,pfPhotonIso_(-9999)
   ,idCutBasedFixedThresholdLoose_(-1)
   ,idCutBasedFixedThresholdTight_(-1)
   ,idCutBasedFixedThresholdHighEnergy_(-1)
   ,idCutBasedCategorizedLoose_(-1)
   ,idCutBasedCategorizedTight_(-1)
   ,idLikelihood_(-9999.)
   ,idNeuralNet_(-9999.)
   ,idCutBasedsimpleEleId70cIso_(-1)
   ,idCutBasedsimpleEleId95cIso_(-1)
   ,idCutBasedsimpleEleId70relIso_(-1)
   ,idCutBasedsimpleEleId95relIso_(-1)
   ,isAlsoPhoton_(false)
   {;}
   
   TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
   ,classification_(-9999)
   ,fbrem_(-9999.)
   ,numberOfBrems_(-9999)
   ,caloEnergy_(-9999.)
   ,caloEnergyError_(-9999.)
   ,trackMomentum_(-9999.)
   ,trackMomentumError_(-9999.)
   ,trackMissedInnerLayers_(-1)
   ,distConvPartner_(-9999.)
   ,dcotConvPartner_(-9999.)
   ,radiusConv_(-9999.)
   ,hadOverEm_(-9999.)
   ,deltaEtaIn_(-9999.)
   ,deltaPhiIn_(-9999.)
   ,energySuperClusterOverPin_(-9999.)
   ,deltaEtaOut_(-9999.)
   ,deltaPhiOut_(-9999.)
   ,energySeedClusterOverPout_(-9999.)
   ,energyScaleCorrected_(false)
   ,dr03TkSumPt_(-9999.)
   ,dr03EcalRecHitSumEt_(-9999.)
   ,dr03HcalDepth1TowerSumEt_(-9999.)
   ,dr03HcalDepth2TowerSumEt_(-9999.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,pixelLayersWithMeasurement_(-1)
   ,stripLayersWithMeasurement_(-1)
   ,d0_(-9999.)
   ,d0Error_(-9999.)
   ,dsz_(-9999.)
   ,dszError_(-9999.)
   ,dB_(-9999.)
   ,normalizedChi2_(-9999.)
   ,ptError_(-9999.)
   ,etaError_(-9999.)
   ,phiError_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,nbClusters_(-9999)
   ,superClusterRawEnergy_(-9999.)
   ,preshowerEnergy_(-9999.)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-9999)
   ,caloConeSize_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,trackIso_(-9999)
   ,ecalIso_(-9999)
   ,hcalIso_(-9999)
   //,swissCross_(-9999)
   ,pfParticleIso_(-9999)
   ,pfChargedHadronIso_(-9999)
   ,pfNeutralHadronIso_(-9999)
   ,pfPhotonIso_(-9999)
   ,idCutBasedFixedThresholdLoose_(-1)
   ,idCutBasedFixedThresholdTight_(-1)
   ,idCutBasedFixedThresholdHighEnergy_(-1)
   ,idCutBasedCategorizedLoose_(-1)
   ,idCutBasedCategorizedTight_(-1)
   ,idLikelihood_(-9999.)
   ,idNeuralNet_(-9999.)
   ,isAlsoPhoton_(false)
   {;}
   
   TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
   ,classification_(-9999)
   ,fbrem_(-9999.)
   ,numberOfBrems_(-9999)
   ,caloEnergy_(-9999.)
   ,caloEnergyError_(-9999.)
   ,trackMomentum_(-9999.)
   ,trackMomentumError_(-9999.)
   ,trackMissedInnerLayers_(-1)
   ,distConvPartner_(-9999.)
   ,dcotConvPartner_(-9999.)
   ,radiusConv_(-9999.)
   ,hadOverEm_(-9999.)
   ,deltaEtaIn_(-9999.)
   ,deltaPhiIn_(-9999.)
   ,energySuperClusterOverPin_(-9999.)
   ,deltaEtaOut_(-9999.)
   ,deltaPhiOut_(-9999.)
   ,energySeedClusterOverPout_(-9999.)
   ,energyScaleCorrected_(false)
   ,dr03TkSumPt_(-9999.)
   ,dr03EcalRecHitSumEt_(-9999.)
   ,dr03HcalDepth1TowerSumEt_(-9999.)
   ,dr03HcalDepth2TowerSumEt_(-9999.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,pixelLayersWithMeasurement_(-1)
   ,stripLayersWithMeasurement_(-1)
   ,d0_(-9999.)
   ,d0Error_(-9999.)
   ,dsz_(-9999.)
   ,dszError_(-9999.)
   ,dB_(-9999.)
   ,normalizedChi2_(-9999.)
   ,ptError_(-9999.)
   ,etaError_(-9999.)
   ,phiError_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,nbClusters_(-9999)
   ,superClusterRawEnergy_(-9999.)
   ,preshowerEnergy_(-9999.)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-9999)
   ,caloConeSize_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,trackIso_(-9999)
   ,ecalIso_(-9999)
   ,hcalIso_(-9999)
   //,swissCross_(-9999)
   ,pfParticleIso_(-9999)
   ,pfChargedHadronIso_(-9999)
   ,pfNeutralHadronIso_(-9999)
   ,pfPhotonIso_(-9999)
   ,idCutBasedFixedThresholdLoose_(-1)
   ,idCutBasedFixedThresholdTight_(-1)
   ,idCutBasedFixedThresholdHighEnergy_(-1)
   ,idCutBasedCategorizedLoose_(-1)
   ,idCutBasedCategorizedTight_(-1)
   ,idLikelihood_(-9999.)
   ,idNeuralNet_(-9999.)
   ,idCutBasedsimpleEleId70cIso_(-1)
   ,idCutBasedsimpleEleId95cIso_(-1)
   ,idCutBasedsimpleEleId70relIso_(-1)
   ,idCutBasedsimpleEleId95relIso_(-1)
   ,isAlsoPhoton_(false)
   {;}
   
   TRootElectron(const TLorentzVector &momentum) :
   TRootParticle(momentum)
   ,classification_(-9999)
   ,fbrem_(-9999.)
   ,numberOfBrems_(-9999)
   ,caloEnergy_(-9999.)
   ,caloEnergyError_(-9999.)
   ,trackMomentum_(-9999.)
   ,trackMomentumError_(-9999.)
   ,trackMissedInnerLayers_(-1)
   ,distConvPartner_(-9999.)
   ,dcotConvPartner_(-9999.)
   ,radiusConv_(-9999.)
   ,hadOverEm_(-9999.)
   ,deltaEtaIn_(-9999.)
   ,deltaPhiIn_(-9999.)
   ,energySuperClusterOverPin_(-9999.)
   ,deltaEtaOut_(-9999.)
   ,deltaPhiOut_(-9999.)
   ,energySeedClusterOverPout_(-9999.)
   ,energyScaleCorrected_(false)
   ,dr03TkSumPt_(-9999.)
   ,dr03EcalRecHitSumEt_(-9999.)
   ,dr03HcalDepth1TowerSumEt_(-9999.)
   ,dr03HcalDepth2TowerSumEt_(-9999.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,pixelLayersWithMeasurement_(-1)
   ,stripLayersWithMeasurement_(-1)
   ,d0_(-9999.)
   ,d0Error_(-9999.)
   ,dsz_(-9999.)
   ,dszError_(-9999.)
   ,dB_(-9999.)
   ,normalizedChi2_(-9999.)
   ,ptError_(-9999.)
   ,etaError_(-9999.)
   ,phiError_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,nbClusters_(-9999)
   ,superClusterRawEnergy_(-9999.)
   ,preshowerEnergy_(-9999.)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-9999)
   ,caloConeSize_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,trackIso_(-9999)
   ,ecalIso_(-9999)
   ,hcalIso_(-9999)
   //,swissCross_(-9999)
   ,pfParticleIso_(-9999)
   ,pfChargedHadronIso_(-9999)
   ,pfNeutralHadronIso_(-9999)
   ,pfPhotonIso_(-9999)
   ,idCutBasedFixedThresholdLoose_(-1)
   ,idCutBasedFixedThresholdTight_(-1)
   ,idCutBasedFixedThresholdHighEnergy_(-1)
   ,idCutBasedCategorizedLoose_(-1)
   ,idCutBasedCategorizedTight_(-1)
   ,idLikelihood_(-9999.)
   ,idNeuralNet_(-9999.)
   ,idCutBasedsimpleEleId70cIso_(-1)
   ,idCutBasedsimpleEleId95cIso_(-1)
   ,idCutBasedsimpleEleId70relIso_(-1)
   ,idCutBasedsimpleEleId95relIso_(-1)
   ,isAlsoPhoton_(false)
   {;}
   
   TRootElectron(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
   TRootParticle(momentum, vertex, type, charge)
   ,classification_(-9999)
   ,fbrem_(-9999.)
   ,numberOfBrems_(-9999)
   ,caloEnergy_(-9999.)
   ,caloEnergyError_(-9999.)
   ,trackMomentum_(-9999.)
   ,trackMomentumError_(-9999.)
   ,trackMissedInnerLayers_(-1)
   ,distConvPartner_(-9999.)
   ,dcotConvPartner_(-9999.)
   ,radiusConv_(-9999.)
   ,hadOverEm_(-9999.)
   ,deltaEtaIn_(-9999.)
   ,deltaPhiIn_(-9999.)
   ,energySuperClusterOverPin_(-9999.)
   ,deltaEtaOut_(-9999.)
   ,deltaPhiOut_(-9999.)
   ,energySeedClusterOverPout_(-9999.)
   ,energyScaleCorrected_(false)
   ,dr03TkSumPt_(-9999.)
   ,dr03EcalRecHitSumEt_(-9999.)
   ,dr03HcalDepth1TowerSumEt_(-9999.)
   ,dr03HcalDepth2TowerSumEt_(-9999.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,pixelLayersWithMeasurement_(-1)
   ,stripLayersWithMeasurement_(-1)
   ,d0_(-9999.)
   ,d0Error_(-9999.)
   ,dsz_(-9999.)
   ,dszError_(-9999.)
   ,dB_(-9999.)
   ,normalizedChi2_(-9999.)
   ,ptError_(-9999.)
   ,etaError_(-9999.)
   ,phiError_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,nbClusters_(-9999)
   ,superClusterRawEnergy_(-9999.)
   ,preshowerEnergy_(-9999.)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-9999)
   ,caloConeSize_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,trackIso_(-9999)
   ,ecalIso_(-9999)
   ,hcalIso_(-9999)
   //,swissCross_(-9999)
   ,pfParticleIso_(-9999)
   ,pfChargedHadronIso_(-9999)
   ,pfNeutralHadronIso_(-9999)
   ,pfPhotonIso_(-9999)
   ,idCutBasedFixedThresholdLoose_(-1)
   ,idCutBasedFixedThresholdTight_(-1)
   ,idCutBasedFixedThresholdHighEnergy_(-1)
   ,idCutBasedCategorizedLoose_(-1)
   ,idCutBasedCategorizedTight_(-1)
   ,idLikelihood_(-9999.)
   ,idNeuralNet_(-9999.)
   ,idCutBasedsimpleEleId70cIso_(-1)
   ,idCutBasedsimpleEleId95cIso_(-1)
   ,idCutBasedsimpleEleId70relIso_(-1)
   ,idCutBasedsimpleEleId95relIso_(-1)
   ,isAlsoPhoton_(false)
   {;}
   
   ~TRootElectron() {;}
   
   
   Int_t classification() const { return classification_ ;}
   Float_t fbrem() const { return fbrem_ ;}
   Int_t numberOfBrems() const { return numberOfBrems_ ;}
   Float_t caloEnergy() const { return caloEnergy_ ;}
   Float_t caloEnergyError() const { return caloEnergyError_ ;}
   Float_t trackMomentum() const { return trackMomentum_ ;}
   Float_t trackMomentumError() const { return trackMomentumError_ ;}
   Int_t   trackMissedInnerLayers() const { return trackMissedInnerLayers_;}
   Float_t distConvPartner() const { return distConvPartner_ ;}
   Float_t dcotConvPartner() const { return dcotConvPartner_ ;}
   Float_t radiusConv() const { return radiusConv_ ;}
   Float_t hadOverEm() const { return hadOverEm_ ;}
   Float_t deltaEtaIn() const { return deltaEtaIn_ ;}
   Float_t deltaPhiIn() const { return deltaPhiIn_ ;}
   Float_t energySuperClusterOverPin() const { return energySuperClusterOverPin_ ;}
   Float_t deltaEtaOut() const { return deltaEtaOut_ ;}
   Float_t deltaPhiOut() const { return deltaPhiOut_ ;}
   Float_t energySeedClusterOverPout() const { return energySeedClusterOverPout_ ;}
   Bool_t energyScaleCorrected() const { return energyScaleCorrected_ ;}
   
   Float_t dr03TkSumPt() const { return dr03TkSumPt_ ;}
   Float_t dr03EcalRecHitSumEt() const { return dr03EcalRecHitSumEt_;}
   Float_t dr03HcalDepth1TowerSumEt() const { return dr03HcalDepth1TowerSumEt_ ;}
   Float_t dr03HcalDepth2TowerSumEt() const { return dr03HcalDepth2TowerSumEt_ ;}
   Float_t dr03HcalTowerSumEt() const { return dr03HcalDepth1TowerSumEt()+dr03HcalDepth2TowerSumEt() ;}
   
   Float_t sigmaEtaEta() const { return sigmaEtaEta_ ;}
   Float_t sigmaIetaIeta() const { return sigmaIetaIeta_ ;}
   
   Int_t pixelLayersWithMeasurement() const { return pixelLayersWithMeasurement_; }
   Int_t stripLayersWithMeasurement() const { return stripLayersWithMeasurement_; }
   Float_t d0() const { return d0_ ;}
   Float_t d0Error() const { return d0Error_ ;}
   Float_t dsz() const { return dsz_ ;}
   Float_t dszError() const { return dszError_ ;}
   Float_t dB() const {return dB_ ;}
   Float_t normalizedChi2() const { return normalizedChi2_ ;}
   Float_t ptError() const { return ptError_ ;}
   Float_t etaError() const { return etaError_ ;}
   Float_t phiError() const { return phiError_ ;}
   Float_t ip3DSignificance() const { return ip3DSignificance_ ;}
   
   Int_t nbClusters() const { return nbClusters_ ;}
   Float_t superClusterRawEnergy() const { return superClusterRawEnergy_ ;}
   Float_t preshowerEnergy() const { return preshowerEnergy_ ;}
   TVector3 caloPosition() const { return caloPosition_ ;}
   map<Int_t,Int_t> scIndexMap() const { return scIndex_; }
   map<Int_t,TRef> scRef() const { return scRef_ ;}
   Int_t nSuperClusters() const { return scRef_.size();}
   
   // Get index in TCloneArray of the supercluster associated by default
   // Default SC collection for electron producer defined in
   // RecoEgamma/EgammaElectronProducers/python/pixelMatchGsfElectrons_cfi
   Int_t scIndex()
   {
      // 0=island or multi5x5, 1=hybrid
      //if ( clusterAlgo_== 0 ) return scIndexOfType(122);
      if ( clusterAlgo_== 0 ) return scIndexOfType(322);
      else if ( clusterAlgo_== 1 ) return scIndexOfType(211);
      else return -1;
   }
   
   // Get ith element  in map scIndex_
   Int_t scIndexAt(UInt_t index)
   {
      if ( index>=scIndex_.size())
      {
         return -1;
      }
      else
      {
         map<Int_t,Int_t>::iterator it=scIndex_.begin();
         for (UInt_t i=0; i<index; ++i)  it++;
         return ( (*it).second );
      }
   }
   
   // Get index in TCloneArray of the seed supercluster of type "type"
   Int_t scIndexOfType(Int_t type)
   {
      map<Int_t,Int_t>::iterator it=scIndex_.find(type);
      return ( it ==scIndex_.end() ? -1 : (*it).second );
   }
   
   // Get supercluster associated by default
   // Default SC collection for electron producer defined in
   // RecoEgamma/EgammaElectronProducers/python/pixelMatchGsfElectrons_cfi
   TRootSuperCluster* superCluster()
   {
      // 0=island, 1=hybrid, 4=multi5x5
      if ( clusterAlgo_== 0 ) return superClusterOfType(122);
      else if ( clusterAlgo_== 1 ) return superClusterOfType(211);
      else if ( clusterAlgo_== 4 ) return superClusterOfType(322);
      else return 0;
   }
   
   // Get ith element  in map scRef_
   TRootSuperCluster* superClusterAt(UInt_t index)
   {
      if ( index>=scRef_.size())
      {
         return 0;
      }
      else
      {
         map<Int_t,TRef>::iterator it=scRef_.begin();
         for (UInt_t i=0; i<index; ++i)  it++;
         return ( (TRootSuperCluster*)(*it).second.GetObject() );
      }
   }
   
   // Get the seed supercluster of type "type"
   TRootSuperCluster* superClusterOfType(Int_t type)
   {
      map<Int_t,TRef>::iterator it=scRef_.find(type);
      return ( it ==scRef_.end() ? 0 : (TRootSuperCluster*) (*it).second.GetObject() );
   }
   
   Int_t clusterAlgo() const { return clusterAlgo_ ;}
   Float_t caloConeSize() const { return caloConeSize_ ;}
   Float_t e2x2() const { return e2x2_ ;}
   Float_t e3x3() const { return e3x3_ ;}
   Float_t e5x5() const { return e5x5_ ;}
   Float_t eMax() const { return eMax_ ;}
   Float_t r19() const { return ( e3x3_ == 0. ? -1. : eMax_/e3x3_ ); }  // ratio of Emax/E(3x3)
   // FIXME - Check definition of r9... include preshowerEnergy as in SimplePhotonAnalyzer.cc ?
   Float_t r9() const { return ( superClusterRawEnergy_ == 0. ? -1. : e3x3_/superClusterRawEnergy_ ); } // ratio of E(3x3)/ESC
   Float_t trackIso() const {return trackIso_;}
   Float_t ecalIso() const {return ecalIso_;}
   Float_t hcalIso() const {return hcalIso_;}
   //Double_t swissCross() const {return swissCross_;}
   
   Float_t pfParticleIso() const {return pfParticleIso_;}
   Float_t pfChargedHadronIso() const {return pfChargedHadronIso_;}
   Float_t pfNeutralHadronIso() const {return pfNeutralHadronIso_;}
   Float_t pfPhotonIso() const {return pfPhotonIso_;}
   
   Int_t idCutBasedFixedThresholdLoose() const { return idCutBasedFixedThresholdLoose_ ;}
   Int_t idCutBasedFixedThresholdTight() const { return idCutBasedFixedThresholdTight_ ;}
   Int_t idCutBasedFixedThresholdHighEnergy() const { return idCutBasedFixedThresholdHighEnergy_ ;}
   Int_t idCutBasedCategorizedLoose() const { return idCutBasedCategorizedLoose_ ;}
   Int_t idCutBasedCategorizedTight() const { return idCutBasedCategorizedTight_ ;}
   Float_t idLikelihood() const { return idLikelihood_ ;}
   Float_t idNeuralNet() const { return idNeuralNet_ ;}
   Int_t idCutBasedsimpleEleId70cIso() const { return idCutBasedsimpleEleId70cIso_;}
   Int_t idCutBasedsimpleEleId95cIso() const { return idCutBasedsimpleEleId95cIso_;}
   Int_t idCutBasedsimpleEleId70relIso() const { return idCutBasedsimpleEleId70relIso_;}
   Int_t idCutBasedsimpleEleId95relIso() const { return idCutBasedsimpleEleId95relIso_;}
   Bool_t isAlsoPhoton() const { return isAlsoPhoton_; }
   
   /* TODO - isBarrel / isEndcap / isCrack
    *      if (fabs (eta) <= 1.4442) {
    *  localElectron.setPosition (1);
    }
    else if (fabs (eta) > 1.4442 & fabs (eta) < 1.5560) {
       localElectron.setPosition (0);
    }
    else if (fabs (eta) >= 1.5560) {
       localElectron.setPosition (-1);
    }
    */
   
   virtual TString typeName() const { return "TRootElectron"; }
   
   
   void setClassification(Int_t classification) { classification_ = classification; }
   void setFbrem(Float_t fbrem) { fbrem_ = fbrem; }
   void setNumberOfBrems(Int_t numberOfBrems) { numberOfBrems_ = numberOfBrems; }
   void setCaloEnergy(Float_t caloEnergy) { caloEnergy_ = caloEnergy; }
   void setCaloEnergyError(Float_t caloEnergyError) { caloEnergyError_ = caloEnergyError; }
   void setTrackMomentum(Float_t trackMomentum) { trackMomentum_ = trackMomentum; }
   void setTrackMomentumError(Float_t trackMomentumError) { trackMomentumError_ = trackMomentumError; }
   void setTrackMissedInnerLayers(Int_t trackMissedInnerLayers) { trackMissedInnerLayers_ = trackMissedInnerLayers; }
   void setDistConvPartner(Float_t distConvPartner) { distConvPartner_ = distConvPartner; }
   void setDcotConvPartner(Float_t dcotConvPartner) { dcotConvPartner_ = dcotConvPartner; }
   void setRadiusConv(Float_t radiusConv) { radiusConv_ = radiusConv; }
   void setHadOverEm(Float_t hadOverEm) { hadOverEm_ = hadOverEm; }
   void setDeltaEtaIn(Float_t deltaEtaIn) { deltaEtaIn_ = deltaEtaIn; }
   void setDeltaPhiIn(Float_t deltaPhiIn) { deltaPhiIn_ = deltaPhiIn; }
   void setEnergySuperClusterOverPin(Float_t energySuperClusterOverPin) { energySuperClusterOverPin_ = energySuperClusterOverPin; }
   void setDeltaEtaOut(Float_t deltaEtaOut) { deltaEtaOut_ = deltaEtaOut; }
   void setDeltaPhiOut(Float_t deltaPhiOut) { deltaPhiOut_ = deltaPhiOut; }
   void setEnergySeedClusterOverPout(Float_t energySeedClusterOverPout) { energySeedClusterOverPout_ = energySeedClusterOverPout; }
   void setEnergyScaleCorrected(Bool_t energyScaleCorrected) { energyScaleCorrected_ = energyScaleCorrected; }
   void setDr03TkSumPt(Float_t dr03TkSumPt) { dr03TkSumPt_ = dr03TkSumPt; }
   void setDr03EcalRecHitSumEt(Float_t dr03EcalRecHitSumEt) { dr03EcalRecHitSumEt_ =  dr03EcalRecHitSumEt; }
   void setDr03HcalDepth1TowerSumEt(Float_t dr03HcalDepth1TowerSumEt) { dr03HcalDepth1TowerSumEt_ = dr03HcalDepth1TowerSumEt; }
   void setDr03HcalDepth2TowerSumEt(Float_t dr03HcalDepth2TowerSumEt) { dr03HcalDepth2TowerSumEt_ = dr03HcalDepth2TowerSumEt; }
   
   void setSigmaEtaEta(Float_t sigmaEtaEta) { sigmaEtaEta_ = sigmaEtaEta; }
   void setSigmaIetaIeta(Float_t sigmaIetaIeta) { sigmaIetaIeta_ = sigmaIetaIeta; }
   
   void setPixelLayersWithMeasurement(Int_t pixelLayersWithMeasurement) { pixelLayersWithMeasurement_ = pixelLayersWithMeasurement; }
   void setStripLayersWithMeasurement(Int_t stripLayersWithMeasurement) { stripLayersWithMeasurement_ = stripLayersWithMeasurement; }
   void setD0(Float_t d0) { d0_ = d0; }
   void setD0Error(Float_t d0Error) { d0Error_ = d0Error; }
   void setDsz(Float_t dsz) { dsz_ = dsz; }
   void setDszError(Float_t dszError) { dszError_ = dszError; }
   void setDB(Float_t dB) { dB_ = dB; }
   void setNormalizedChi2(Float_t normalizedChi2) { normalizedChi2_ = normalizedChi2; }
   void setPtError(Float_t ptError) { ptError_ = ptError; }
   void setEtaError(Float_t etaError) { etaError_ = etaError; }
   void setPhiError(Float_t phiError) { phiError_ = phiError; }
   void setIP3DSignificance(Float_t ip3DSignificance) { ip3DSignificance_ = ip3DSignificance; }
   
   void setNbClusters(Int_t nbClusters) { nbClusters_ = nbClusters; }
   void setSuperClusterRawEnergy(Float_t superClusterRawEnergy) { superClusterRawEnergy_ = superClusterRawEnergy; }
   void setPreshowerEnergy(Float_t preshowerEnergy) { preshowerEnergy_ = preshowerEnergy; }
   void setCaloPosition(TVector3 caloPosition) { caloPosition_ = caloPosition; }
   void setCaloPosition(Double_t x, Double_t y, Double_t z) { caloPosition_.SetXYZ(x, y ,z); }
   void setSCIndex(Int_t type, Int_t index) { scIndex_[type]=index; }
   void setSCRef(Int_t type, TObject* superCluster) { scRef_[type]=superCluster; }
   void setClusterAlgo(Int_t clusterAlgo) { clusterAlgo_ = clusterAlgo; }
   void setCaloConeSize(Float_t caloConeSize) { caloConeSize_ = caloConeSize; }
   void setE2x2(Float_t e2x2) { e2x2_ = e2x2; }
   void setE3x3(Float_t e3x3) { e3x3_ = e3x3; }
   void setE5x5(Float_t e5x5) { e5x5_ = e5x5; }
   void setEMax(Float_t eMax) { eMax_ = eMax; }
   void setTrackIso(Float_t trackIso) { trackIso_ = trackIso; }
   void setEcalIso(Float_t ecalIso) { ecalIso_ = ecalIso; }
   void setHcalIso(Float_t hcalIso) { hcalIso_ = hcalIso; }
   //void setSwissCross(Double_t swissCross) { swissCross_ = swissCross; }
   
   void setPFParticleIso(Float_t iso) { pfParticleIso_=iso; }
   void setPFChargedHadronIso(Float_t iso) { pfChargedHadronIso_=iso; }
   void setPFNeutralHadronIso(Float_t iso) { pfNeutralHadronIso_=iso; }
   void setPFPhotonIso(Float_t iso) { pfPhotonIso_=iso; }
   
   void setIDCutBasedFixedThresholdLoose(Int_t idCutBasedFixedThresholdLoose) { idCutBasedFixedThresholdLoose_ = idCutBasedFixedThresholdLoose; }
   void setIDCutBasedFixedThresholdTight(Int_t idCutBasedFixedThresholdTight) { idCutBasedFixedThresholdTight_ = idCutBasedFixedThresholdTight; }
   void setIDCutBasedFixedThresholdHighEnergy(Int_t idCutBasedFixedThresholdHighEnergy) { idCutBasedFixedThresholdHighEnergy_ = idCutBasedFixedThresholdHighEnergy; }
   void setIDCutBasedCategorizedLoose(Int_t idCutBasedCategorizedLoose) { idCutBasedCategorizedLoose_ = idCutBasedCategorizedLoose; }
   void setIDCutBasedCategorizedTight(Int_t idCutBasedCategorizedTight) { idCutBasedCategorizedTight_ = idCutBasedCategorizedTight; }
   void setIDLikelihood(Float_t idLikelihood) { idLikelihood_ = idLikelihood; }
   void setIDNeuralNet(Float_t idNeuralNet) { idNeuralNet_ = idNeuralNet; }
   void setIDCutBasedsimpleEleId70cIso(Int_t idCutBasedsimpleEleId70cIso) { idCutBasedsimpleEleId70cIso_ = idCutBasedsimpleEleId70cIso; }
   void setIDCutBasedsimpleEleId95cIso(Int_t idCutBasedsimpleEleId95cIso) { idCutBasedsimpleEleId95cIso_ = idCutBasedsimpleEleId95cIso; }
   void setIDCutBasedsimpleEleId70relIso(Int_t idCutBasedsimpleEleId70relIso) { idCutBasedsimpleEleId70relIso_ = idCutBasedsimpleEleId70relIso; }
   void setIDCutBasedsimpleEleId95relIso(Int_t idCutBasedsimpleEleId95relIso) { idCutBasedsimpleEleId95relIso_ = idCutBasedsimpleEleId95relIso; }
   void setIsAlsoPhoton(Bool_t isAlsoPhoton) { isAlsoPhoton_ = isAlsoPhoton; }
   
   friend std::ostream& operator<< (std::ostream& stream, const TRootElectron& electron)
   {
      stream << "TRootElectron - Charge=" << electron.charge() << " (E,Et,eta,phi)=("<< electron.Energy() <<","<< electron.Et() <<","<< electron.Eta() <<","<< electron.Phi() << ")"
      << " vertex(x,y,z)=("<< electron.vx() <<","<< electron.vy() <<","<< electron.vz() << ")";
      return stream;
   };

   void Print()
   {
      std::cout << "TRootElectron - Charge=" << this->charge() << " (E,Et,eta,phi)=("<< this->Energy() <<","<< this->Et() <<","<< this->Eta() <<","<< this->Phi() << ")"
      << "  vertex=("<< this->vx() <<","<< this->vy() <<","<< this->vz() << ")"
      << "  caloPosition=(" << this->caloPosition().X() << "," << this->caloPosition().Y() << "," << this->caloPosition().Z() << ")" << endl
      << "            trackMomentum=" << this->trackMomentum() << "+-" << this->trackMomentumError() <<"  track missed inner layers "<< this->trackMissedInnerLayers() << " nPixels=" << this->pixelLayersWithMeasurement()
      << " nStrips=" << this->stripLayersWithMeasurement() << " d0=" << this->d0() << "+-" << this->d0Error()<< " dsz=" << this->dsz() << "+-" << this->dszError() << endl
      << "            distConvPartner=" << this->distConvPartner() << " dcotConvPartner=" << this->dcotConvPartner() << " radiusConv=" << this->radiusConv()
      << " sigmaEtaEta=" << this->sigmaEtaEta() <<" sigmaIetaIeta=" << this->sigmaIetaIeta() << endl
      << "            algo=" << this->clusterAlgo() << " nBC=" << this->nbClusters() << "  caloEnergy=" << this->caloEnergy() << "+-" << this->caloEnergyError()
      << " scRawEnergy=" << this->superClusterRawEnergy() << " preshEnergy=" << this->preshowerEnergy()
      << " E2x2=" << this->e2x2() <<" E3x3=" << this->e3x3() <<" E5x5=" << this->e5x5() <<" Emax=" << this->eMax()
      << " R19=" << this->r19() <<" R9=" << this->r9() << endl
      <<"            fbrem=" << this->fbrem() << "  H/E=" << this->hadOverEm() <<"  deltaEtaIn=" << this->deltaEtaIn() <<"  deltaPhiIn=" << this->deltaPhiIn() <<"  deltaEtaOut=" << this->deltaEtaOut() <<"  deltaPhiOut=" << this->deltaPhiOut() <<"  E/p in=" << this->energySuperClusterOverPin() <<"  E/p out=" << this->energySeedClusterOverPout() << endl
      << "            reco iso03  ecal="<< this->dr03EcalRecHitSumEt() << " hcal1=" << this->dr03HcalDepth1TowerSumEt() << " hcal2=" << this->dr03HcalDepth2TowerSumEt() << " tracker=" << this->dr03TkSumPt() << endl
      //<< "            pat iso (no isodeposit) ecal="<< this->trackIso()<<" hcal="<<this->hcalIso()<< " swissCross= " << this->swissCross()<< " tracker="<<this->trackIso()<<endl
      << "            pat iso (no isodeposit) ecal="<< this->trackIso()<<" hcal="<<this->hcalIso()<< " tracker="<<this->trackIso()<<endl
      << "            PF Isolation : particleIso=" << this->pfParticleIso_ << "  chargedHadronIso=" << this->pfChargedHadronIso_ << "  NeutralHadronIso=" << this->pfNeutralHadronIso_ << endl
      <<"            ID:  Fixed-Threshold(Loose,Tight,HighEnergy)=(" << this->idCutBasedFixedThresholdLoose() << "," << this->idCutBasedFixedThresholdTight()  << "," << this->idCutBasedFixedThresholdHighEnergy() << ")"
      <<"  Categorized(Loose,Tight)=(" << this->idCutBasedCategorizedLoose() << "," << this->idCutBasedCategorizedTight()  << ")"
      <<"  LH=" << this->idLikelihood() << "  NN=" << this->idNeuralNet() << endl
      << "  idCutBasedsimpleEleId70cIso " << this->idCutBasedsimpleEleId70cIso() << "  idCutBasedsimpleEleId95cIso " << this->idCutBasedsimpleEleId95cIso() << "  idCutBasedsimpleEleId70relIso " << this->idCutBasedsimpleEleId70relIso() << "  idCutBasedsimpleEleId95relIso " << this->idCutBasedsimpleEleId95relIso() << "  isAlsoPhoton=" << this->isAlsoPhoton();
   };

   
   private:
      
      // Variables from reco::GsfElectron
      
      // Classification:
      // enum Classification { UNKNOWN=-1, GOLDEN=0, BIGBREM=1, OLDNARROW=2, SHOWERING=3, GAP=4 } ;
      Int_t classification_;              // Electron classification
      Float_t fbrem_;                     // the brem fraction from gsf fit: (track momentum in - track momentum out) / track momentum in
      Int_t numberOfBrems_;               // Number of basic clusters in SC around the seed BC
      
      Float_t caloEnergy_;                // SuperCluster energy corrected by EnergyScaleFactor
      Float_t caloEnergyError_;           // Error on caloEnergy_
      Float_t trackMomentum_;             // Track momentum at vertex
      Float_t trackMomentumError_;        // Error on trackMomentum_
      Int_t   trackMissedInnerLayers_;    // Track missed inner layers (for conversions rejection)
      Float_t distConvPartner_;           // distance to the conversion partner
      Float_t dcotConvPartner_;           // difference of cot(angle) with the conversion partner track
      Float_t radiusConv_;                // signed conversion radius
      
      Float_t hadOverEm_;                 // hadronic over electromagnetic fraction
      
      Float_t deltaEtaIn_;                // Supercluster eta - Track eta from helix extrapolation from impact point
      Float_t deltaPhiIn_;                // Supercluster phi - Track phi from helix extrapolation from impact point
      Float_t energySuperClusterOverPin_; // supercluster energy / track momentum at impact point
      
      Float_t deltaEtaOut_;               // SeedCluster eta - Track eta at calo from outermost state
      Float_t deltaPhiOut_;               // SeedCluster phi - Track phi at calo from outermost state
      Float_t energySeedClusterOverPout_; // SeedCluster energy / track momentum at calo from outermost state
      
      Bool_t energyScaleCorrected_;       // Has Energy Scale been applied ?
      
      Float_t dr03TkSumPt_;               // track iso deposit with electron footprint removed
      Float_t dr03EcalRecHitSumEt_;       // ecal iso deposit with electron footprint removed
      Float_t dr03HcalDepth1TowerSumEt_;  // hcal depht 1 iso deposit with electron footprint removed
      Float_t dr03HcalDepth2TowerSumEt_;  // hcal depht 2 iso deposit with electron footprint removed
      
      Float_t sigmaEtaEta_;               // sqrt(covariance(Eta,Eta)) taken from reco::Electron::ShowerShape struct
      Float_t sigmaIetaIeta_;             // sqrt(covariance(iEta,iEta)) taken from reco::Electron::ShowerShape struct
      
      
      // Variables from reco::GsfTrack
      
      /* cf: http://cmslxr.fnal.gov/lxr/source/DataFormats/TrackReco/interface/TrackBase.h
       *      For tracks reconstructed in the CMS Tracker, the reference position is the point of closest approach to the centre
       *      of CMS. For muons, this is not necessarily true. Parameters associated to the 5D curvilinear covariance matrix:
       *      qoverp = q / abs(p) = signed inverse of momentum [1/GeV]
       *      lambda = pi/2 - polar angle at the given point
       *      phi = azimuth angle at the given point
       *      dxy = -vx*sin(phi) + vy*cos(phi) [cm]
       *      dsz = vz*cos(lambda) - (vx*cos(phi)+vy*sin(phi))*sin(lambda) [cm]
       * 
       *      Geometrically, dxy is the signed distance in the XY plane between the straight line passing through (vx,vy) with
       *      azimuthal angle phi and the point (0,0). The dsz parameter is the signed distance in the SZ plane between the straight
       *      line passing through (vx,vy,vz) with angles (phi, lambda) and the point (s=0,z=0). The S axis is defined by the projection
       *      of the straight line onto the XY plane. The convention is to assign the S coordinate for (vx,vy) as the value
       *      vx*cos(phi)+vy*sin(phi). This value is zero when (vx,vy) is the point of minimum transverse distance to (0,0).
       * 
       *      Note that dxy and dsz provide sensible estimates of the distance from the true particle trajectory to (0,0,0) ONLY
       *      in two cases:
       *      - When (vx,vy,vz) already correspond to the point of minimum transverse distance to (0,0,0) or is close to it
       *      (so that the differences between considering the exact trajectory or a straight line in this range  are negligible).
       *      This is usually true for Tracker tracks.
       *      - When the track has infinite or extremely high momentum */
      
      Int_t pixelLayersWithMeasurement_; // Number of pixel layers with at least one valid hit
      Int_t stripLayersWithMeasurement_; // Number of strip layers with at least one valid hit
      
      Float_t d0_;             // d0=-dxy
      Float_t d0Error_;        // error on d0_
      Float_t dsz_;            // dsz parameter
      Float_t dszError_;       // error on dsz_
      Float_t dB_;             // absolute 2D impact parameter d0(Bsp)
      Float_t normalizedChi2_; // chi-squared divided by n.d.o.f. of track fit
      
      Float_t ptError_;        // needed ?  ptError()
      Float_t etaError_;       // needed ?  etaError()
      Float_t phiError_;       // needed ?  phiError()
      
      Float_t ip3DSignificance_;  // Significance of the impact parameter wrt to the selected primary vertex
      
      
      // Variables from reco::SuperCluster
      Int_t nbClusters_; // Number of related brem clusters
      Float_t superClusterRawEnergy_;
      Float_t preshowerEnergy_;
      TVector3 caloPosition_;     // SuperCluster centroid position
      map<Int_t,Int_t> scIndex_;  // indexes of the seed SuperClusters (one per SC tytpe)
      map<Int_t,TRef> scRef_;     // references to the seed SuperClusters (one per SC tytpe)
      
      
      // Cluster Shape variables
      // need reco::SuperCluster and reco::BasicCluster
      Int_t clusterAlgo_;    // reco::BasicCluster::algo() island = 0, hybrid = 1, fixedMatrix = 2, dynamicHybrid = 3, multi5x5 = 4
      Float_t caloConeSize_; // Delta_R of the cone centered on the reco::GsfElectron and containing all its basic clusters constituents
      // need reco::SuperCluster and reco::BasicCluster and reduced Ecal RecHits Collections for EcalClusterLazyTools
      Float_t e2x2_;
      Float_t e3x3_;
      Float_t e5x5_;
      Float_t eMax_;
      
      
      // pat::Electron Isolation
      // stephane 7/04/2010
      // We have to check this part
      // the results are not what we expect
      //      Float_t isoR01_sumPt_;
      //      Int_t isoR01_nTracks_;
      //
      //      Float_t isoR02_sumPt_;
      //      Int_t isoR02_nTracks_;
      //
      //      Float_t isoR03_emEt_;
      //      Float_t isoR03_hadEt_;
      //      Float_t isoR03_sumPt_;
      //      Int_t isoR03_nTracks_;
      //
      //      Float_t isoR05_emEt_;
      //      Float_t isoR05_hadEt_;
      //      Float_t isoR05_sumPt_; // Pt sum of tracks in a DR=0.5 cone around the electron
      //      Int_t isoR05_nTracks_; // Tracks multiplicity in a DR=0.5 cone around the electron
      
      // correct pat isolation (april 2010) -- electron footprint removed
      Float_t trackIso_; // returns the value of the summed track pt in a cone of deltaR<0.4
      Float_t ecalIso_; // returns the value of the summed Et of all recHits in the ecal in a cone of deltaR<0.4
      Float_t hcalIso_; // returns the value of the summed Et of all recHits in the hcal in a cone of deltaR<0.4
      //Double_t swissCross_; // returns the value of swiss cross for spikes rejection
      
      
      // Added by Stephane 23/04/2010 -- pat Isolation for PFlow muons
      Float_t pfParticleIso_; // isolation calculated with all the PFCandidates
      Float_t pfChargedHadronIso_; // isolation calculated with only the charged hadron PFCandidates
      Float_t pfNeutralHadronIso_; // isolation calculated with only the neutral hadron PFCandidates
      Float_t pfPhotonIso_; // Returns the isolation calculated with only the gamma PFCandidates
      
      
      // Electron ID (cf https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideElectronID)
      // By default in 2.2.X, only cut based identification is available in pat (https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideCutBasedElectronID
      Int_t idCutBasedFixedThresholdLoose_;      // Simple cut based ID (aka 'robust') - Loose Thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta
      Int_t idCutBasedFixedThresholdTight_;      // Simple cut based ID (default in EWK group) - Tight Thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta
      Int_t idCutBasedFixedThresholdHighEnergy_; // Simple cut based ID - Thresholds optimized for high energy electron (~TeV) - not activated by default in 2.2.X
      Int_t idCutBasedCategorizedLoose_;         // Category based ID - Different loose thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta, eSeedOverPin for differents regions in the E/p vs fBrem plane
      Int_t idCutBasedCategorizedTight_;         // Category based ID - Different tight thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta, eSeedOverPin for differents regions in the E/p vs fBrem plane
      Float_t idLikelihood_;                     // Lieklihood ID - not activated by default in 2.2.X
      Float_t idNeuralNet_;                      // NN ID - not activated by default in 2.2.X
      Float_t idCutBasedsimpleEleId70cIso_;      // VBTF simple cut-based e-ID W70 (working point for "70%" efficiency)
      Float_t idCutBasedsimpleEleId95cIso_;      // VBTF simple cut-based e-ID W95 (working point for "95%" efficiency)
      Float_t idCutBasedsimpleEleId70relIso_;      // VBTF simple cut-based e-ID W70 relative (working point for "70%" efficiency)
      Float_t idCutBasedsimpleEleId95relIso_;      // VBTF simple cut-based e-ID W95 relative (working point for "95%" efficiency)
      
      
      
      Bool_t isAlsoPhoton_;                      // is electron also a photon ?
      
      // needed ?
      //Float_t sigmaEtaEta_;
      //Float_t sigmaPhiPhi_;
      
      
      ClassDef (TRootElectron,11);
      
   };
   
   #endif
   
