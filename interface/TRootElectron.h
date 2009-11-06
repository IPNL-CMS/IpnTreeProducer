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
      ,caloEnergy_(-9999.)
      ,caloEnergyError_(-9999.)
      ,trackMomentum_(-9999.)
      ,trackMomentumError_(-9999.)
      ,hadOverEm_(-9999.)
      ,deltaEtaIn_(-9999.)
      ,deltaPhiIn_(-9999.)
      ,energySuperClusterOverPin_(-9999.)
      ,deltaEtaOut_(-9999.)
      ,deltaPhiOut_(-9999.)
      ,energySeedClusterOverPout_(-9999.)
      ,energyScaleCorrected_(false)
      ,momentumCorrected_(false)
		,dr03TkSumPt_(-9999.)
		,dr03EcalRecHitSumEt_(-9999.)
		,dr03HcalDepth1TowerSumEt_(-9999.)
		,dr03HcalDepth2TowerSumEt_(-9999.)
      ,pixelLayersWithMeasurement_(-1)
      ,stripLayersWithMeasurement_(-1)
      ,d0_(-9999.)
      ,d0Error_(-9999.)
      ,dsz_(-9999.)
      ,dszError_(-9999.)
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
      ,isoR01_sumPt_(-9999.)
      ,isoR01_nTracks_(-9999)
      ,isoR02_sumPt_(-9999.)
      ,isoR02_nTracks_(-9999)
      ,isoR03_emEt_(-9999.)
      ,isoR03_hadEt_(-9999.)
      ,isoR03_sumPt_(-9999.)
      ,isoR03_nTracks_(-9999)
      ,isoR05_emEt_(-9999.)
      ,isoR05_hadEt_(-9999.)
      ,isoR05_sumPt_(-9999.)
      ,isoR05_nTracks_(-9999)
      ,idCutBasedFixedThresholdLoose_(-1)
      ,idCutBasedFixedThresholdTight_(-1)
      ,idCutBasedFixedThresholdHighEnergy_(-1)
      ,idCutBasedCategorizedLoose_(-1)
      ,idCutBasedCategorizedTight_(-1)
      ,idLikelihood_(-9999.)
      ,idNeuralNet_(-9999.)
      ,isAlsoPhoton_(false)
      {;}

      TRootElectron(const TRootElectron& electron) :
      TRootParticle(electron)
      ,classification_(electron.classification_)
      ,caloEnergy_(electron.caloEnergy_)
      ,caloEnergyError_(electron.caloEnergyError_)
      ,trackMomentum_(electron.trackMomentum_)
      ,trackMomentumError_(electron.trackMomentumError_)
      ,hadOverEm_(electron.hadOverEm_)
      ,deltaEtaIn_(electron.deltaEtaIn_)
      ,deltaPhiIn_(electron.deltaPhiIn_)
      ,energySuperClusterOverPin_(electron.energySuperClusterOverPin_)
      ,deltaEtaOut_(electron.deltaEtaOut_)
      ,deltaPhiOut_(electron.deltaPhiOut_)
      ,energySeedClusterOverPout_(electron.energySeedClusterOverPout_)
      ,energyScaleCorrected_(electron.energyScaleCorrected_)
      ,momentumCorrected_(electron.momentumCorrected_)
		,dr03TkSumPt_(electron.dr03TkSumPt_)
		,dr03EcalRecHitSumEt_(electron.dr03EcalRecHitSumEt_)
		,dr03HcalDepth1TowerSumEt_(electron.dr03HcalDepth1TowerSumEt_)
		,dr03HcalDepth2TowerSumEt_(electron.dr03HcalDepth2TowerSumEt_)
      ,pixelLayersWithMeasurement_(electron.pixelLayersWithMeasurement_)
      ,stripLayersWithMeasurement_(electron.stripLayersWithMeasurement_)
      ,d0_(electron.d0_)
      ,d0Error_(electron.d0Error_)
      ,dsz_(electron.dsz_)
      ,dszError_(electron.dszError_)
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
      ,isoR01_sumPt_(electron.isoR01_sumPt_)
      ,isoR01_nTracks_(electron.isoR01_nTracks_)
      ,isoR02_sumPt_(electron.isoR02_sumPt_)
      ,isoR02_nTracks_(electron.isoR02_nTracks_)
      ,isoR03_emEt_(electron.isoR03_emEt_)
      ,isoR03_hadEt_(electron.isoR03_hadEt_)
      ,isoR03_sumPt_(electron.isoR03_sumPt_)
      ,isoR03_nTracks_(electron.isoR03_nTracks_)
      ,isoR05_emEt_(electron.isoR05_emEt_)
      ,isoR05_hadEt_(electron.isoR05_hadEt_)
      ,isoR05_sumPt_(electron.isoR05_sumPt_)
      ,isoR05_nTracks_(electron.isoR05_nTracks_)
      ,idCutBasedFixedThresholdLoose_(electron.idCutBasedFixedThresholdLoose_)
      ,idCutBasedFixedThresholdTight_(electron.idCutBasedFixedThresholdTight_)
      ,idCutBasedFixedThresholdHighEnergy_(electron.idCutBasedFixedThresholdHighEnergy_)
      ,idCutBasedCategorizedLoose_(electron.idCutBasedCategorizedLoose_)
      ,idCutBasedCategorizedTight_(electron.idCutBasedCategorizedTight_)
      ,idLikelihood_(electron.idLikelihood_)
      ,idNeuralNet_(electron.idNeuralNet_)
      ,isAlsoPhoton_(electron.isAlsoPhoton_)
      {;}

      TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e) :
      TRootParticle(px,py,pz,e)
      ,classification_(-9999)
      ,caloEnergy_(-9999.)
      ,caloEnergyError_(-9999.)
      ,trackMomentum_(-9999.)
      ,trackMomentumError_(-9999.)
      ,hadOverEm_(-9999.)
      ,deltaEtaIn_(-9999.)
      ,deltaPhiIn_(-9999.)
      ,energySuperClusterOverPin_(-9999.)
      ,deltaEtaOut_(-9999.)
      ,deltaPhiOut_(-9999.)
      ,energySeedClusterOverPout_(-9999.)
      ,energyScaleCorrected_(false)
      ,momentumCorrected_(false)
		,dr03TkSumPt_(-9999.)
		,dr03EcalRecHitSumEt_(-9999.)
		,dr03HcalDepth1TowerSumEt_(-9999.)
		,dr03HcalDepth2TowerSumEt_(-9999.)
      ,pixelLayersWithMeasurement_(-1)
      ,stripLayersWithMeasurement_(-1)
      ,d0_(-9999.)
      ,d0Error_(-9999.)
      ,dsz_(-9999.)
      ,dszError_(-9999.)
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
      ,isoR01_sumPt_(-9999.)
      ,isoR01_nTracks_(-9999)
      ,isoR02_sumPt_(-9999.)
      ,isoR02_nTracks_(-9999)
      ,isoR03_emEt_(-9999.)
      ,isoR03_hadEt_(-9999.)
      ,isoR03_sumPt_(-9999.)
      ,isoR03_nTracks_(-9999)
      ,isoR05_emEt_(-9999.)
      ,isoR05_hadEt_(-9999.)
      ,isoR05_sumPt_(-9999.)
      ,isoR05_nTracks_(-9999)
      ,idCutBasedFixedThresholdLoose_(-1)
      ,idCutBasedFixedThresholdTight_(-1)
      ,idCutBasedFixedThresholdHighEnergy_(-1)
      ,idCutBasedCategorizedLoose_(-1)
      ,idCutBasedCategorizedTight_(-1)
      ,idLikelihood_(-9999.)
      ,idNeuralNet_(-9999.)
      ,isAlsoPhoton_(false)
      {;}

      TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
      ,classification_(-9999)
      ,caloEnergy_(-9999.)
      ,caloEnergyError_(-9999.)
      ,trackMomentum_(-9999.)
      ,trackMomentumError_(-9999.)
      ,hadOverEm_(-9999.)
      ,deltaEtaIn_(-9999.)
      ,deltaPhiIn_(-9999.)
      ,energySuperClusterOverPin_(-9999.)
      ,deltaEtaOut_(-9999.)
      ,deltaPhiOut_(-9999.)
      ,energySeedClusterOverPout_(-9999.)
      ,energyScaleCorrected_(false)
      ,momentumCorrected_(false)
		,dr03TkSumPt_(-9999.)
		,dr03EcalRecHitSumEt_(-9999.)
		,dr03HcalDepth1TowerSumEt_(-9999.)
		,dr03HcalDepth2TowerSumEt_(-9999.)
      ,pixelLayersWithMeasurement_(-1)
      ,stripLayersWithMeasurement_(-1)
      ,d0_(-9999.)
      ,d0Error_(-9999.)
      ,dsz_(-9999.)
      ,dszError_(-9999.)
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
      ,isoR01_sumPt_(-9999.)
      ,isoR01_nTracks_(-9999)
      ,isoR02_sumPt_(-9999.)
      ,isoR02_nTracks_(-9999)
      ,isoR03_emEt_(-9999.)
      ,isoR03_hadEt_(-9999.)
      ,isoR03_sumPt_(-9999.)
      ,isoR03_nTracks_(-9999)
      ,isoR05_emEt_(-9999.)
      ,isoR05_hadEt_(-9999.)
      ,isoR05_sumPt_(-9999.)
      ,isoR05_nTracks_(-9999)
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
      ,caloEnergy_(-9999.)
      ,caloEnergyError_(-9999.)
      ,trackMomentum_(-9999.)
      ,trackMomentumError_(-9999.)
      ,hadOverEm_(-9999.)
      ,deltaEtaIn_(-9999.)
      ,deltaPhiIn_(-9999.)
      ,energySuperClusterOverPin_(-9999.)
      ,deltaEtaOut_(-9999.)
      ,deltaPhiOut_(-9999.)
      ,energySeedClusterOverPout_(-9999.)
      ,energyScaleCorrected_(false)
      ,momentumCorrected_(false)
		,dr03TkSumPt_(-9999.)
		,dr03EcalRecHitSumEt_(-9999.)
		,dr03HcalDepth1TowerSumEt_(-9999.)
		,dr03HcalDepth2TowerSumEt_(-9999.)
      ,pixelLayersWithMeasurement_(-1)
      ,stripLayersWithMeasurement_(-1)
      ,d0_(-9999.)
      ,d0Error_(-9999.)
      ,dsz_(-9999.)
      ,dszError_(-9999.)
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
      ,isoR01_sumPt_(-9999.)
      ,isoR01_nTracks_(-9999)
      ,isoR02_sumPt_(-9999.)
      ,isoR02_nTracks_(-9999)
      ,isoR03_emEt_(-9999.)
      ,isoR03_hadEt_(-9999.)
      ,isoR03_sumPt_(-9999.)
      ,isoR03_nTracks_(-9999)
      ,isoR05_emEt_(-9999.)
      ,isoR05_hadEt_(-9999.)
      ,isoR05_sumPt_(-9999.)
      ,isoR05_nTracks_(-9999)
      ,idCutBasedFixedThresholdLoose_(-1)
      ,idCutBasedFixedThresholdTight_(-1)
      ,idCutBasedFixedThresholdHighEnergy_(-1)
      ,idCutBasedCategorizedLoose_(-1)
      ,idCutBasedCategorizedTight_(-1)
      ,idLikelihood_(-9999.)
      ,idNeuralNet_(-9999.)
      ,isAlsoPhoton_(false)
      {;}

      TRootElectron(const TLorentzVector &momentum) :
      TRootParticle(momentum)
      ,classification_(-9999)
      ,caloEnergy_(-9999.)
      ,caloEnergyError_(-9999.)
      ,trackMomentum_(-9999.)
      ,trackMomentumError_(-9999.)
      ,hadOverEm_(-9999.)
      ,deltaEtaIn_(-9999.)
      ,deltaPhiIn_(-9999.)
      ,energySuperClusterOverPin_(-9999.)
      ,deltaEtaOut_(-9999.)
      ,deltaPhiOut_(-9999.)
      ,energySeedClusterOverPout_(-9999.)
      ,energyScaleCorrected_(false)
      ,momentumCorrected_(false)
		,dr03TkSumPt_(-9999.)
		,dr03EcalRecHitSumEt_(-9999.)
		,dr03HcalDepth1TowerSumEt_(-9999.)
		,dr03HcalDepth2TowerSumEt_(-9999.)
      ,pixelLayersWithMeasurement_(-1)
      ,stripLayersWithMeasurement_(-1)
      ,d0_(-9999.)
      ,d0Error_(-9999.)
      ,dsz_(-9999.)
      ,dszError_(-9999.)
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
      ,isoR01_sumPt_(-9999.)
      ,isoR01_nTracks_(-9999)
      ,isoR02_sumPt_(-9999.)
      ,isoR02_nTracks_(-9999)
      ,isoR03_emEt_(-9999.)
      ,isoR03_hadEt_(-9999.)
      ,isoR03_sumPt_(-9999.)
      ,isoR03_nTracks_(-9999)
      ,isoR05_emEt_(-9999.)
      ,isoR05_hadEt_(-9999.)
      ,isoR05_sumPt_(-9999.)
      ,isoR05_nTracks_(-9999)
      ,idCutBasedFixedThresholdLoose_(-1)
      ,idCutBasedFixedThresholdTight_(-1)
      ,idCutBasedFixedThresholdHighEnergy_(-1)
      ,idCutBasedCategorizedLoose_(-1)
      ,idCutBasedCategorizedTight_(-1)
      ,idLikelihood_(-9999.)
      ,idNeuralNet_(-9999.)
      ,isAlsoPhoton_(false)
      {;}

      TRootElectron(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
      TRootParticle(momentum, vertex, type, charge)
      ,classification_(-9999)
      ,caloEnergy_(-9999.)
      ,caloEnergyError_(-9999.)
      ,trackMomentum_(-9999.)
      ,trackMomentumError_(-9999.)
      ,hadOverEm_(-9999.)
      ,deltaEtaIn_(-9999.)
      ,deltaPhiIn_(-9999.)
      ,energySuperClusterOverPin_(-9999.)
      ,deltaEtaOut_(-9999.)
      ,deltaPhiOut_(-9999.)
      ,energySeedClusterOverPout_(-9999.)
      ,energyScaleCorrected_(false)
      ,momentumCorrected_(false)
		,dr03TkSumPt_(-9999.)
		,dr03EcalRecHitSumEt_(-9999.)
		,dr03HcalDepth1TowerSumEt_(-9999.)
		,dr03HcalDepth2TowerSumEt_(-9999.)
      ,pixelLayersWithMeasurement_(-1)
      ,stripLayersWithMeasurement_(-1)
      ,d0_(-9999.)
      ,d0Error_(-9999.)
      ,dsz_(-9999.)
      ,dszError_(-9999.)
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
      ,isoR01_sumPt_(-9999.)
      ,isoR01_nTracks_(-9999)
      ,isoR02_sumPt_(-9999.)
      ,isoR02_nTracks_(-9999)
      ,isoR03_emEt_(-9999.)
      ,isoR03_hadEt_(-9999.)
      ,isoR03_sumPt_(-9999.)
      ,isoR03_nTracks_(-9999)
      ,isoR05_emEt_(-9999.)
      ,isoR05_hadEt_(-9999.)
      ,isoR05_sumPt_(-9999.)
      ,isoR05_nTracks_(-9999)
      ,idCutBasedFixedThresholdLoose_(-1)
      ,idCutBasedFixedThresholdTight_(-1)
      ,idCutBasedFixedThresholdHighEnergy_(-1)
      ,idCutBasedCategorizedLoose_(-1)
      ,idCutBasedCategorizedTight_(-1)
      ,idLikelihood_(-9999.)
      ,idNeuralNet_(-9999.)
      ,isAlsoPhoton_(false)
      {;}

      ~TRootElectron() {;}


      Int_t classification() const { return classification_ ;}
      Float_t caloEnergy() const { return caloEnergy_ ;}
      Float_t caloEnergyError() const { return caloEnergyError_ ;}
      Float_t trackMomentum() const { return trackMomentum_ ;}
      Float_t trackMomentumError() const { return trackMomentumError_ ;}
      Float_t hadOverEm() const { return hadOverEm_ ;}
      Float_t deltaEtaIn() const { return deltaEtaIn_ ;}
      Float_t deltaPhiIn() const { return deltaPhiIn_ ;}
      Float_t energySuperClusterOverPin() const { return energySuperClusterOverPin_ ;}
      Float_t deltaEtaOut() const { return deltaEtaOut_ ;}
      Float_t deltaPhiOut() const { return deltaPhiOut_ ;}
      Float_t energySeedClusterOverPout() const { return energySeedClusterOverPout_ ;}
      Bool_t energyScaleCorrected() const { return energyScaleCorrected_ ;}
      Bool_t momentumCorrected() const { return momentumCorrected_ ;}
		
		Float_t dr03TkSumPt() const { return dr03TkSumPt_ ;}
		Float_t dr03EcalRecHitSumEt() const { return dr03EcalRecHitSumEt_;}
		Float_t dr03HcalDepth1TowerSumEt() const { return dr03HcalDepth1TowerSumEt_ ;}
		Float_t dr03HcalDepth2TowerSumEt() const { return dr03HcalDepth2TowerSumEt_ ;}
		Float_t dr03HcalTowerSumEt() const { return dr03HcalDepth1TowerSumEt()+dr03HcalDepth2TowerSumEt() ;}

      Int_t pixelLayersWithMeasurement() const { return pixelLayersWithMeasurement_; }
      Int_t stripLayersWithMeasurement() const { return stripLayersWithMeasurement_; }
      Float_t d0() const { return d0_ ;}
      Float_t d0Error() const { return d0Error_ ;}
      Float_t dsz() const { return dsz_ ;}
      Float_t dszError() const { return dszError_ ;}
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
         // 0=island or multi5x5, 1=hybrid
         //if ( clusterAlgo_== 0 ) return superClusterOfType(122);
         if ( clusterAlgo_== 0 ) return superClusterOfType(322);
         else if ( clusterAlgo_== 1 ) return superClusterOfType(211);
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
      Float_t isoR01_sumPt() const { return isoR01_sumPt_ ;}
      Int_t isoR01_nTracks() const { return isoR01_nTracks_ ;}
      Float_t isoR02_sumPt() const { return isoR02_sumPt_ ;}
      Int_t isoR02_nTracks() const { return isoR02_nTracks_ ;}
      Float_t isoR03_emEt() const { return isoR03_emEt_ ;}
      Float_t isoR03_hadEt() const { return isoR03_hadEt_ ;}
      Float_t isoR03_sumPt() const { return isoR03_sumPt_ ;}
      Int_t isoR03_nTracks() const { return isoR03_nTracks_ ;}
      Float_t isoR05_emEt() const { return isoR05_emEt_ ;}
      Float_t isoR05_hadEt() const { return isoR05_hadEt_ ;}
      Float_t isoR05_sumPt() const { return isoR05_sumPt_ ;}
      Int_t isoR05_nTracks() const { return isoR05_nTracks_ ;}
      Int_t idCutBasedFixedThresholdLoose() const { return idCutBasedFixedThresholdLoose_ ;}
      Int_t idCutBasedFixedThresholdTight() const { return idCutBasedFixedThresholdTight_ ;}
      Int_t idCutBasedFixedThresholdHighEnergy() const { return idCutBasedFixedThresholdHighEnergy_ ;}
      Int_t idCutBasedCategorizedLoose() const { return idCutBasedCategorizedLoose_ ;}
      Int_t idCutBasedCategorizedTight() const { return idCutBasedCategorizedTight_ ;}
      Float_t idLikelihood() const { return idLikelihood_ ;}
      Float_t idNeuralNet() const { return idNeuralNet_ ;}
      Bool_t isAlsoPhoton() const { return isAlsoPhoton_; }
      
      /* TODO - isBarrel / isEndcap / isCrack
      if (fabs (eta) <= 1.4442) {
         localElectron.setPosition (1);
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
      void setCaloEnergy(Float_t caloEnergy) { caloEnergy_ = caloEnergy; }
      void setCaloEnergyError(Float_t caloEnergyError) { caloEnergyError_ = caloEnergyError; }
      void setTrackMomentum(Float_t trackMomentum) { trackMomentum_ = trackMomentum; }
      void setTrackMomentumError(Float_t trackMomentumError) { trackMomentumError_ = trackMomentumError; }
      void setHadOverEm(Float_t hadOverEm) { hadOverEm_ = hadOverEm; }
      void setDeltaEtaIn(Float_t deltaEtaIn) { deltaEtaIn_ = deltaEtaIn; }
      void setDeltaPhiIn(Float_t deltaPhiIn) { deltaPhiIn_ = deltaPhiIn; }
      void setEnergySuperClusterOverPin(Float_t energySuperClusterOverPin) { energySuperClusterOverPin_ = energySuperClusterOverPin; }
      void setDeltaEtaOut(Float_t deltaEtaOut) { deltaEtaOut_ = deltaEtaOut; }
      void setDeltaPhiOut(Float_t deltaPhiOut) { deltaPhiOut_ = deltaPhiOut; }
      void setEnergySeedClusterOverPout(Float_t energySeedClusterOverPout) { energySeedClusterOverPout_ = energySeedClusterOverPout; }
      void setEnergyScaleCorrected(Bool_t energyScaleCorrected) { energyScaleCorrected_ = energyScaleCorrected; }
      void setMomentumCorrected(Bool_t momentumCorrected) { momentumCorrected_ = momentumCorrected; }
		void setDr03TkSumPt(Float_t dr03TkSumPt) { dr03TkSumPt_ = dr03TkSumPt; }
		void setDr03EcalRecHitSumEt(Float_t dr03EcalRecHitSumEt) { dr03EcalRecHitSumEt_ =  dr03EcalRecHitSumEt; }
		void setDr03HcalDepth1TowerSumEt(Float_t dr03HcalDepth1TowerSumEt) { dr03HcalDepth1TowerSumEt_ = dr03HcalDepth1TowerSumEt; }
		void setDr03HcalDepth2TowerSumEt(Float_t dr03HcalDepth2TowerSumEt) { dr03HcalDepth2TowerSumEt_ = dr03HcalDepth2TowerSumEt; }

      void setPixelLayersWithMeasurement(Int_t pixelLayersWithMeasurement) { pixelLayersWithMeasurement_ = pixelLayersWithMeasurement; }
      void setStripLayersWithMeasurement(Int_t stripLayersWithMeasurement) { stripLayersWithMeasurement_ = stripLayersWithMeasurement; }
      void setD0(Float_t d0) { d0_ = d0; }
      void setD0Error(Float_t d0Error) { d0Error_ = d0Error; }
      void setDsz(Float_t dsz) { dsz_ = dsz; }
      void setDszError(Float_t dszError) { dszError_ = dszError; }
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
      void setIsoR01_sumPt(Float_t isoR01_sumPt) { isoR01_sumPt_ = isoR01_sumPt; }
      void setIsoR01_nTracks(Int_t isoR01_nTracks) { isoR01_nTracks_ = isoR01_nTracks; }
      void setIsoR02_sumPt(Float_t isoR02_sumPt) { isoR02_sumPt_ = isoR02_sumPt; }
      void setIsoR02_nTracks(Int_t isoR02_nTracks) { isoR02_nTracks_ = isoR02_nTracks; }
      void setIsoR03_emEt(Float_t isoR03_emEt) { isoR03_emEt_ = isoR03_emEt; }
      void setIsoR03_hadEt(Float_t isoR03_hadEt) { isoR03_hadEt_ = isoR03_hadEt; }
      void setIsoR03_sumPt(Float_t isoR03_sumPt) { isoR03_sumPt_ = isoR03_sumPt; }
      void setIsoR03_nTracks(Int_t isoR03_nTracks) { isoR03_nTracks_ = isoR03_nTracks; }
      void setIsoR05_emEt(Float_t isoR05_emEt) { isoR05_emEt_ = isoR05_emEt; }
      void setIsoR05_hadEt(Float_t isoR05_hadEt) { isoR05_hadEt_ = isoR05_hadEt; }
      void setIsoR05_sumPt(Float_t isoR05_sumPt) { isoR05_sumPt_ = isoR05_sumPt; }
      void setIsoR05_nTracks(Int_t isoR05_nTracks) { isoR05_nTracks_ = isoR05_nTracks; }
      void setIDCutBasedFixedThresholdLoose(Int_t idCutBasedFixedThresholdLoose) { idCutBasedFixedThresholdLoose_ = idCutBasedFixedThresholdLoose; }
      void setIDCutBasedFixedThresholdTight(Int_t idCutBasedFixedThresholdTight) { idCutBasedFixedThresholdTight_ = idCutBasedFixedThresholdTight; }
      void setIDCutBasedFixedThresholdHighEnergy(Int_t idCutBasedFixedThresholdHighEnergy) { idCutBasedFixedThresholdHighEnergy_ = idCutBasedFixedThresholdHighEnergy; }
      void setIDCutBasedCategorizedLoose(Int_t idCutBasedCategorizedLoose) { idCutBasedCategorizedLoose_ = idCutBasedCategorizedLoose; }
      void setIDCutBasedCategorizedTight(Int_t idCutBasedCategorizedTight) { idCutBasedCategorizedTight_ = idCutBasedCategorizedTight; }
      void setIDLikelihood(Float_t idLikelihood) { idLikelihood_ = idLikelihood; }
      void setIDNeuralNet(Float_t idNeuralNet) { idNeuralNet_ = idNeuralNet; }
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
         << "            trackMomentum=" << this->trackMomentum() << "+-" << this->trackMomentumError() << " nPixels=" << this->pixelLayersWithMeasurement()
         << " nStrips=" << this->stripLayersWithMeasurement() << " d0=" << this->d0() << "+-" << this->d0Error()<< " dsz=" << this->dsz() << "+-" << this->dszError() << endl
         << "            algo=" << this->clusterAlgo() << " nBC=" << this->nbClusters() << "  caloEnergy=" << this->caloEnergy() << "+-" << this->caloEnergyError()
         << " scRawEnergy=" << this->superClusterRawEnergy() << " preshEnergy=" << this->preshowerEnergy()
         << " E2x2=" << this->e2x2() <<" E3x3=" << this->e3x3() <<" E5x5=" << this->e5x5() <<" Emax=" << this->eMax()
         << " R19=" << this->r19() <<" R9=" << this->r9() << endl
         <<"            H/E=" << this->hadOverEm() <<"  deltaEtaIn=" << this->deltaEtaIn() <<"  deltaPhiIn=" << this->deltaPhiIn() <<"  deltaEtaOut=" << this->deltaEtaOut() <<"  deltaPhiOut=" << this->deltaPhiOut() <<"  E/p in=" << this->energySuperClusterOverPin() <<"  E/p out=" << this->energySeedClusterOverPout() << endl
         << "            reco iso03  ecal="<< this->dr03EcalRecHitSumEt() << " hcal1=" << this->dr03HcalDepth1TowerSumEt() << " hcal2=" << this->dr03HcalDepth2TowerSumEt() << " tracker=" << this->dr03TkSumPt() << endl 
         << "            pat iso03  ecal="<< this->isoR03_emEt() << " hcal=" << this->isoR03_hadEt() << " tracker=" << this->isoR03_sumPt() << " ntracks=" << this->isoR03_nTracks() << endl
         << "            pat iso05  ecal="<< this->isoR05_emEt() << " hcal=" << this->isoR05_hadEt() << " tracker=" << this->isoR05_sumPt() << " ntracks=" << this->isoR05_nTracks() << endl
         <<"            ID:  Fixed-Threshold(Loose,Tight,HighEnergy)=(" << this->idCutBasedFixedThresholdLoose() << "," << this->idCutBasedFixedThresholdTight()  << "," << this->idCutBasedFixedThresholdHighEnergy() << ")"
         <<"  Categorized(Loose,Tight)=(" << this->idCutBasedCategorizedLoose() << "," << this->idCutBasedCategorizedTight()  << ")"
         <<"  LH=" << this->idLikelihood() << "  NN=" << this->idNeuralNet() << "  isAlsoPhoton=" << this->isAlsoPhoton();
      };


   private:

      // Variables from reco::GsfElectron

      // Classification:
      //	barrel  :   0: golden,  10: bigbrem,  20: narrow,  30-34: showering,  40: crack
      //          (30: showering nbrem=0, 31: showering nbrem=1, 32: showering nbrem=2 ,33: showering nbrem=3, 34: showering nbrem>=4)
      //	endcaps : 100: golden, 110: bigbrem, 120: narrow, 130-134: showering
      //            (130: showering nbrem=0, 131: showering nbrem=1, 132: showering nbrem=2 ,133: showering nbrem=3, 134: showering nbrem>=4)

      Int_t classification_;             // Electron classification

      Float_t caloEnergy_;                // SuperCluster energy corrected by EnergyScaleFactor
      Float_t caloEnergyError_;           // Error on caloEnergy_
      Float_t trackMomentum_;             // Track momentum at vertex
      Float_t trackMomentumError_;        // Error on trackMomentum_

      Float_t hadOverEm_;                 // hadronic over electromagnetic fraction

      Float_t deltaEtaIn_;                // Supercluster eta - Track eta from helix extrapolation from impact point
      Float_t deltaPhiIn_;                // Supercluster phi - Track phi from helix extrapolation from impact point
      Float_t energySuperClusterOverPin_; // supercluster energy / track momentum at impact point

      Float_t deltaEtaOut_;               // SeedCluster eta - Track eta at calo from outermost state
      Float_t deltaPhiOut_;               // SeedCluster phi - Track phi at calo from outermost state
      Float_t energySeedClusterOverPout_; // SeedCluster energy / track momentum at calo from outermost state

      Bool_t energyScaleCorrected_;       // Has Energy Scale been applied ?
      Bool_t momentumCorrected_;          // Tell if class dependant E-p combination has been determined

		Float_t dr03TkSumPt_;					// track iso deposit with electron footprint removed
		Float_t dr03EcalRecHitSumEt_;			// ecal iso deposit with electron footprint removed
		Float_t dr03HcalDepth1TowerSumEt_;  // hcal depht 1 iso deposit with electron footprint removed
		Float_t dr03HcalDepth2TowerSumEt_;  // hcal depht 2 iso deposit with electron footprint removed
  
      // Variables from reco::GsfTrack

      /* cf: http://cmslxr.fnal.gov/lxr/source/DataFormats/TrackReco/interface/TrackBase.h
      For tracks reconstructed in the CMS Tracker, the reference position is the point of closest approach to the centre
      of CMS. For muons, this is not necessarily true. Parameters associated to the 5D curvilinear covariance matrix:
      qoverp = q / abs(p) = signed inverse of momentum [1/GeV]
      lambda = pi/2 - polar angle at the given point
      phi = azimuth angle at the given point
      dxy = -vx*sin(phi) + vy*cos(phi) [cm]
      dsz = vz*cos(lambda) - (vx*cos(phi)+vy*sin(phi))*sin(lambda) [cm]

      Geometrically, dxy is the signed distance in the XY plane between the straight line passing through (vx,vy) with
      azimuthal angle phi and the point (0,0). The dsz parameter is the signed distance in the SZ plane between the straight
      line passing through (vx,vy,vz) with angles (phi, lambda) and the point (s=0,z=0). The S axis is defined by the projection
      of the straight line onto the XY plane. The convention is to assign the S coordinate for (vx,vy) as the value
      vx*cos(phi)+vy*sin(phi). This value is zero when (vx,vy) is the point of minimum transverse distance to (0,0).

      Note that dxy and dsz provide sensible estimates of the distance from the true particle trajectory to (0,0,0) ONLY
      in two cases:
      - When (vx,vy,vz) already correspond to the point of minimum transverse distance to (0,0,0) or is close to it
      (so that the differences between considering the exact trajectory or a straight line in this range  are negligible).
      This is usually true for Tracker tracks.
      - When the track has infinite or extremely high momentum */

      Int_t pixelLayersWithMeasurement_; // Number of pixel layers with at least one valid hit
      Int_t stripLayersWithMeasurement_; // Number of strip layers with at least one valid hit

      Float_t d0_;             // d0=-dxy
      Float_t d0Error_;        // error on d0_
      Float_t dsz_;            // dsz parameter
      Float_t dszError_;       // error on dsz_
      Float_t normalizedChi2_; // chi-squared divided by n.d.o.f. of track fit

      Float_t ptError_;        // needed ?  ptError()
      Float_t etaError_;       // needed ?  etaError()
      Float_t phiError_;       // needed ?  phiError()

      Float_t ip3DSignificance_;  // Significance of the impact parameter wrt to the selected primary vertex


      // Variables from reco::SuperCluster
      Int_t nbClusters_; // Number of related brem clusters
      Float_t superClusterRawEnergy_;
      Float_t preshowerEnergy_;
      TVector3 caloPosition_;		 // SuperCluster centroid position
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
      Float_t isoR01_sumPt_;
      Int_t isoR01_nTracks_;

      Float_t isoR02_sumPt_;
      Int_t isoR02_nTracks_;

      Float_t isoR03_emEt_;
      Float_t isoR03_hadEt_;
      Float_t isoR03_sumPt_;
      Int_t isoR03_nTracks_;

      Float_t isoR05_emEt_;
      Float_t isoR05_hadEt_;
      Float_t isoR05_sumPt_; // Pt sum of tracks in a DR=0.5 cone around the electron
      Int_t isoR05_nTracks_; // Tracks multiplicity in a DR=0.5 cone around the electron


      // Electron ID (cf https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideElectronID)
      // By default in 2.2.X, only cut based identification is available in pat (https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideCutBasedElectronID
      Int_t idCutBasedFixedThresholdLoose_;      // Simple cut based ID (aka 'robust') - Loose Thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta
      Int_t idCutBasedFixedThresholdTight_;      // Simple cut based ID (default in EWK group) - Tight Thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta
      Int_t idCutBasedFixedThresholdHighEnergy_; // Simple cut based ID - Thresholds optimized for high energy electron (~TeV) - not activated by default in 2.2.X
      Int_t idCutBasedCategorizedLoose_;         // Category based ID - Different loose thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta, eSeedOverPin for differents regions in the E/p vs fBrem plane
      Int_t idCutBasedCategorizedTight_;         // Category based ID - Different tight thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta, eSeedOverPin for differents regions in the E/p vs fBrem plane
      Float_t idLikelihood_;                     // Lieklihood ID - not activated by default in 2.2.X
      Float_t idNeuralNet_;                      // NN ID - not activated by default in 2.2.X

      Bool_t isAlsoPhoton_;                      // is electron also a photon ?

      // needed ?
      //Float_t sigmaEtaEta_;
      //Float_t sigmaPhiPhi_;


      ClassDef (TRootElectron,6);

};

#endif
