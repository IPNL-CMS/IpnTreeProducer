#ifndef TRootPhoton_h
#define TRootPhoton_h

#include <vector>
#include <map>

#include "../interface/TRootParticle.h"

using namespace std;

class TRootTrack;
class TRootSuperCluster;

class TRootPhoton : public TRootParticle
{
   
   public:
      
      TRootPhoton() :
      TRootParticle()
      ,caloPosition_(-9999.,-9999.,-9999.)
      ,hoe_(-1.)
      ,hasPixelSeed_(false)
      ,nbClusters_(-1)
      ,superClusterRawEnergy_(-1.)
      ,preshowerEnergy_(-1.)
      ,scIndex_()
      ,scRef_()
      ,sigmaEtaEta_(-9999.)
      ,sigmaIetaIeta_(-9999.)
      ,clusterAlgo_(-1)
      ,caloConeSize_(-1.)
      ,e2x2_(-9999.)
      ,e3x3_(-9999.)
      ,e5x5_(-9999.)
      ,eMax_(-9999.)
      ,e2nd_(-9999.)
      ,covEtaEta_(-9999.)
      ,covEtaPhi_(-9999.)
      ,covPhiPhi_(-9999.)
      ,convNTracks_(-1)
      ,convEoverP_(-1.)
      ,convMass_(-1.)
      ,convCotanTheta_(-999.)
      ,convLikely_(-1.)
      ,convVertex_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition1_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition2_(-9999.,-9999.,-9999.)
      ,convIndexTrack1_(-1)
      ,convIndexTrack2_(-1)
      ,convTrack1_(0)
      ,convTrack2_(0)
      ,isolationPersoBasicClusters_(-1.)
      ,isolationPersoBasicClustersDoubleCone_(-1.)
      ,isolationPersoHcalRecHit_(-1.)
      ,isolationPersoTracksSolidCone_(-1.)
      ,isolationPersoNTracksSolidCone_(-1)
      ,dR03IsolationEcalRecHit_(-1.)
      ,dR03IsolationHcalRecHit_(-1.)
      ,dR03IsolationSolidTrkCone_(-1.)
      ,dR03IsolationHollowTrkCone_(-1.)
      ,dR03IsolationNTracksSolidCone_(-1)
      ,dR03IsolationNTracksHollowCone_(-1)
      ,dR04IsolationEcalRecHit_(-1.)
      ,dR04IsolationHcalRecHit_(-1.)
      ,dR04IsolationSolidTrkCone_(-1.)
      ,dR04IsolationHollowTrkCone_(-1.)
      ,dR04IsolationNTracksSolidCone_(-1)
      ,dR04IsolationNTracksHollowCone_(-1)
      ,isLooseEMPhoton_(false)
      ,isLoosePhoton_(false)
      ,isTightPhoton_(false)
      ,isEBPho_(false)
      ,isEEPho_(false)
      ,isEBGap_(false)
      ,isEEGap_(false)
      ,isEBEEGap_(false)
      ,isAlsoElectron_(false)
      ,pi0nn_(-1.)
      {;}
      
      TRootPhoton(const TRootPhoton& photon) :
      TRootParticle(photon)
      ,caloPosition_(photon.caloPosition_)
      ,hoe_(photon.hoe_)
      ,hasPixelSeed_(photon.hasPixelSeed_)
      ,nbClusters_(photon.nbClusters_)
      ,superClusterRawEnergy_(photon.superClusterRawEnergy_)
      ,preshowerEnergy_(photon.preshowerEnergy_)
      ,scIndex_(photon.scIndex_)
      ,scRef_(photon.scRef_)
      ,sigmaEtaEta_(photon.sigmaEtaEta_)
      ,sigmaIetaIeta_(photon.sigmaIetaIeta_)
      ,clusterAlgo_(photon.clusterAlgo_)
      ,caloConeSize_(photon.caloConeSize_)
      ,e2x2_(photon.e2x2_)
      ,e3x3_(photon.e3x3_)
      ,e5x5_(photon.e5x5_)
      ,eMax_(photon.eMax_)
      ,e2nd_(photon.e2nd_)
      ,covEtaEta_(photon.covEtaEta_)
      ,covEtaPhi_(photon.covEtaPhi_)
      ,covPhiPhi_(photon.covPhiPhi_)
      ,convNTracks_(photon.convNTracks_)
      ,convEoverP_(photon.convEoverP_)
      ,convMass_(photon.convMass_)
      ,convCotanTheta_(photon.convCotanTheta_)
      ,convLikely_(photon.convLikely_)
      ,convVertex_(photon.convVertex_)
      ,convEcalImpactPosition1_(photon.convEcalImpactPosition1_)
      ,convEcalImpactPosition2_(photon.convEcalImpactPosition2_)
      ,convIndexTrack1_(photon.convIndexTrack1_)
      ,convIndexTrack2_(photon.convIndexTrack2_)
      ,convTrack1_(photon.convTrack1_)
      ,convTrack2_(photon.convTrack2_)
      ,isolationPersoBasicClusters_(photon.isolationPersoBasicClusters_)
      ,isolationPersoBasicClustersDoubleCone_(photon.isolationPersoBasicClustersDoubleCone_)
      ,isolationPersoHcalRecHit_(photon.isolationPersoHcalRecHit_)
      ,isolationPersoTracksSolidCone_(photon.isolationPersoTracksSolidCone_)
      ,isolationPersoNTracksSolidCone_(photon.isolationPersoNTracksSolidCone_)
      ,dR03IsolationEcalRecHit_(photon.dR03IsolationEcalRecHit_)
      ,dR03IsolationHcalRecHit_(photon.dR03IsolationHcalRecHit_)
      ,dR03IsolationSolidTrkCone_(photon.dR03IsolationSolidTrkCone_)
      ,dR03IsolationHollowTrkCone_(photon.dR03IsolationHollowTrkCone_)
      ,dR03IsolationNTracksSolidCone_(photon.dR03IsolationNTracksSolidCone_)
      ,dR03IsolationNTracksHollowCone_(photon.dR03IsolationNTracksHollowCone_)
      ,dR04IsolationEcalRecHit_(photon.dR04IsolationEcalRecHit_)
      ,dR04IsolationHcalRecHit_(photon.dR04IsolationHcalRecHit_)
      ,dR04IsolationSolidTrkCone_(photon.dR04IsolationSolidTrkCone_)
      ,dR04IsolationHollowTrkCone_(photon.dR04IsolationHollowTrkCone_)
      ,dR04IsolationNTracksSolidCone_(photon.dR04IsolationNTracksSolidCone_)
      ,dR04IsolationNTracksHollowCone_(photon.dR04IsolationNTracksHollowCone_)
      ,isLooseEMPhoton_(photon.isLooseEMPhoton_)
      ,isLoosePhoton_(photon.isLoosePhoton_)
      ,isTightPhoton_(photon.isTightPhoton_)
      ,isEBPho_(photon.isEBPho_)
      ,isEEPho_(photon.isEEPho_)
      ,isEBGap_(photon.isEBGap_)
      ,isEEGap_(photon.isEEGap_)
      ,isEBEEGap_(photon.isEBEEGap_)
      ,isAlsoElectron_(photon.isAlsoElectron_)
      ,pi0nn_(photon.pi0nn_)
      {;}
      
      TRootPhoton(Double_t px, Double_t py, Double_t pz, Double_t e) :
      TRootParticle(px,py,pz,e)
      ,caloPosition_(-9999.,-9999.,-9999.)
      ,hoe_(-1.)
      ,hasPixelSeed_(false)
      ,nbClusters_(-1)
      ,superClusterRawEnergy_(-1.)
      ,preshowerEnergy_(-1.)
      ,scIndex_()
      ,scRef_()
      ,sigmaEtaEta_(-9999.)
      ,sigmaIetaIeta_(-9999.)
      ,clusterAlgo_(-1)
      ,caloConeSize_(-1.)
      ,e2x2_(-9999.)
      ,e3x3_(-9999.)
      ,e5x5_(-9999.)
      ,eMax_(-9999.)
      ,e2nd_(-9999.)
      ,covEtaEta_(-9999.)
      ,covEtaPhi_(-9999.)
      ,covPhiPhi_(-9999.)
      ,convNTracks_(-1)
      ,convEoverP_(-1.)
      ,convMass_(-1.)
      ,convCotanTheta_(-999.)
      ,convLikely_(-1.)
      ,convVertex_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition1_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition2_(-9999.,-9999.,-9999.)
      ,convIndexTrack1_(-1)
      ,convIndexTrack2_(-1)
      ,convTrack1_(0)
      ,convTrack2_(0)
      ,isolationPersoBasicClusters_(-1.)
      ,isolationPersoBasicClustersDoubleCone_(-1.)
      ,isolationPersoHcalRecHit_(-1.)
      ,isolationPersoTracksSolidCone_(-1.)
      ,isolationPersoNTracksSolidCone_(-1)
      ,dR03IsolationEcalRecHit_(-1.)
      ,dR03IsolationHcalRecHit_(-1.)
      ,dR03IsolationSolidTrkCone_(-1.)
      ,dR03IsolationHollowTrkCone_(-1.)
      ,dR03IsolationNTracksSolidCone_(-1)
      ,dR03IsolationNTracksHollowCone_(-1)
      ,dR04IsolationEcalRecHit_(-1.)
      ,dR04IsolationHcalRecHit_(-1.)
      ,dR04IsolationSolidTrkCone_(-1.)
      ,dR04IsolationHollowTrkCone_(-1.)
      ,dR04IsolationNTracksSolidCone_(-1)
      ,dR04IsolationNTracksHollowCone_(-1)
      ,isLooseEMPhoton_(false)
      ,isLoosePhoton_(false)
      ,isTightPhoton_(false)
      ,isEBPho_(false)
      ,isEEPho_(false)
      ,isEBGap_(false)
      ,isEEGap_(false)
      ,isEBEEGap_(false)
      ,isAlsoElectron_(false)
      ,pi0nn_(-1.)
      {;}
      
      TRootPhoton(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
      ,caloPosition_(-9999.,-9999.,-9999.)
      ,hoe_(-1.)
      ,hasPixelSeed_(false)
      ,nbClusters_(-1)
      ,superClusterRawEnergy_(-1.)
      ,preshowerEnergy_(-1.)
      ,scIndex_()
      ,scRef_()
      ,sigmaEtaEta_(-9999.)
      ,sigmaIetaIeta_(-9999.)
      ,clusterAlgo_(-1)
      ,caloConeSize_(-1.)
      ,e2x2_(-9999.)
      ,e3x3_(-9999.)
      ,e5x5_(-9999.)
      ,eMax_(-9999.)
      ,e2nd_(-9999.)
      ,covEtaEta_(-9999.)
      ,covEtaPhi_(-9999.)
      ,covPhiPhi_(-9999.)
      ,convNTracks_(-1)
      ,convEoverP_(-1.)
      ,convMass_(-1.)
      ,convCotanTheta_(-999.)
      ,convLikely_(-1.)
      ,convVertex_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition1_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition2_(-9999.,-9999.,-9999.)
      ,convIndexTrack1_(-1)
      ,convIndexTrack2_(-1)
      ,convTrack1_(0)
      ,convTrack2_(0)
      ,isolationPersoBasicClusters_(-1.)
      ,isolationPersoBasicClustersDoubleCone_(-1.)
      ,isolationPersoHcalRecHit_(-1.)
      ,isolationPersoTracksSolidCone_(-1.)
      ,isolationPersoNTracksSolidCone_(-1)
      ,dR03IsolationEcalRecHit_(-1.)
      ,dR03IsolationHcalRecHit_(-1.)
      ,dR03IsolationSolidTrkCone_(-1.)
      ,dR03IsolationHollowTrkCone_(-1.)
      ,dR03IsolationNTracksSolidCone_(-1)
      ,dR03IsolationNTracksHollowCone_(-1)
      ,dR04IsolationEcalRecHit_(-1.)
      ,dR04IsolationHcalRecHit_(-1.)
      ,dR04IsolationSolidTrkCone_(-1.)
      ,dR04IsolationHollowTrkCone_(-1.)
      ,dR04IsolationNTracksSolidCone_(-1)
      ,dR04IsolationNTracksHollowCone_(-1)
      ,isLooseEMPhoton_(false)
      ,isLoosePhoton_(false)
      ,isTightPhoton_(false)
      ,isEBPho_(false)
      ,isEEPho_(false)
      ,isEBGap_(false)
      ,isEEGap_(false)
      ,isEBEEGap_(false)
      ,isAlsoElectron_(false)
      ,pi0nn_(-1.)
      {;}
      
      TRootPhoton(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
      ,caloPosition_(-9999.,-9999.,-9999.)
      ,hoe_(-1.)
      ,hasPixelSeed_(false)
      ,nbClusters_(-1)
      ,superClusterRawEnergy_(-1.)
      ,preshowerEnergy_(-1.)
      ,scIndex_()
      ,scRef_()
      ,sigmaEtaEta_(-9999.)
      ,sigmaIetaIeta_(-9999.)
      ,clusterAlgo_(-1)
      ,caloConeSize_(-1.)
      ,e2x2_(-9999.)
      ,e3x3_(-9999.)
      ,e5x5_(-9999.)
      ,eMax_(-9999.)
      ,e2nd_(-9999.)
      ,covEtaEta_(-9999.)
      ,covEtaPhi_(-9999.)
      ,covPhiPhi_(-9999.)
      ,convNTracks_(-1)
      ,convEoverP_(-1.)
      ,convMass_(-1.)
      ,convCotanTheta_(-999.)
      ,convLikely_(-1.)
      ,convVertex_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition1_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition2_(-9999.,-9999.,-9999.)
      ,convIndexTrack1_(-1)
      ,convIndexTrack2_(-1)
      ,convTrack1_(0)
      ,convTrack2_(0)
      ,isolationPersoBasicClusters_(-1.)
      ,isolationPersoBasicClustersDoubleCone_(-1.)
      ,isolationPersoHcalRecHit_(-1.)
      ,isolationPersoTracksSolidCone_(-1.)
      ,isolationPersoNTracksSolidCone_(-1)
      ,dR03IsolationEcalRecHit_(-1.)
      ,dR03IsolationHcalRecHit_(-1.)
      ,dR03IsolationSolidTrkCone_(-1.)
      ,dR03IsolationHollowTrkCone_(-1.)
      ,dR03IsolationNTracksSolidCone_(-1)
      ,dR03IsolationNTracksHollowCone_(-1)
      ,dR04IsolationEcalRecHit_(-1.)
      ,dR04IsolationHcalRecHit_(-1.)
      ,dR04IsolationSolidTrkCone_(-1.)
      ,dR04IsolationHollowTrkCone_(-1.)
      ,dR04IsolationNTracksSolidCone_(-1)
      ,dR04IsolationNTracksHollowCone_(-1)
      ,isLooseEMPhoton_(false)
      ,isLoosePhoton_(false)
      ,isTightPhoton_(false)
      ,isEBPho_(false)
      ,isEEPho_(false)
      ,isEBGap_(false)
      ,isEEGap_(false)
      ,isEBEEGap_(false)
      ,isAlsoElectron_(false)
      ,pi0nn_(-1.)
      {;}
      
      TRootPhoton(const TLorentzVector &momentum) :
      TRootParticle(momentum)
      ,caloPosition_(-9999.,-9999.,-9999.)
      ,hoe_(-1.)
      ,hasPixelSeed_(false)
      ,nbClusters_(-1)
      ,superClusterRawEnergy_(-1.)
      ,preshowerEnergy_(-1.)
      ,scIndex_()
      ,scRef_()
      ,sigmaEtaEta_(-9999.)
      ,sigmaIetaIeta_(-9999.)
      ,clusterAlgo_(-1)
      ,caloConeSize_(-1.)
      ,e2x2_(-9999.)
      ,e3x3_(-9999.)
      ,e5x5_(-9999.)
      ,eMax_(-9999.)
      ,e2nd_(-9999.)
      ,covEtaEta_(-9999.)
      ,covEtaPhi_(-9999.)
      ,covPhiPhi_(-9999.)
      ,convNTracks_(-1)
      ,convEoverP_(-1.)
      ,convMass_(-1.)
      ,convCotanTheta_(-999.)
      ,convLikely_(-1.)
      ,convVertex_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition1_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition2_(-9999.,-9999.,-9999.)
      ,convIndexTrack1_(-1)
      ,convIndexTrack2_(-1)
      ,convTrack1_(0)
      ,convTrack2_(0)
      ,isolationPersoBasicClusters_(-1.)
      ,isolationPersoBasicClustersDoubleCone_(-1.)
      ,isolationPersoHcalRecHit_(-1.)
      ,isolationPersoTracksSolidCone_(-1.)
      ,isolationPersoNTracksSolidCone_(-1)
      ,dR03IsolationEcalRecHit_(-1.)
      ,dR03IsolationHcalRecHit_(-1.)
      ,dR03IsolationSolidTrkCone_(-1.)
      ,dR03IsolationHollowTrkCone_(-1.)
      ,dR03IsolationNTracksSolidCone_(-1)
      ,dR03IsolationNTracksHollowCone_(-1)
      ,dR04IsolationEcalRecHit_(-1.)
      ,dR04IsolationHcalRecHit_(-1.)
      ,dR04IsolationSolidTrkCone_(-1.)
      ,dR04IsolationHollowTrkCone_(-1.)
      ,dR04IsolationNTracksSolidCone_(-1)
      ,dR04IsolationNTracksHollowCone_(-1)
      ,isLooseEMPhoton_(false)
      ,isLoosePhoton_(false)
      ,isTightPhoton_(false)
      ,isEBPho_(false)
      ,isEEPho_(false)
      ,isEBGap_(false)
      ,isEEGap_(false)
      ,isEBEEGap_(false)
      ,isAlsoElectron_(false)
      ,pi0nn_(-1.)
      {;}
      
      TRootPhoton(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
      TRootParticle(momentum, vertex, type, charge)
      ,caloPosition_(-9999.,-9999.,-9999.)
      ,hoe_(-1.)
      ,hasPixelSeed_(false)
      ,nbClusters_(-1)
      ,superClusterRawEnergy_(-1.)
      ,preshowerEnergy_(-1.)
      ,scIndex_()
      ,scRef_()
      ,sigmaEtaEta_(-9999.)
      ,sigmaIetaIeta_(-9999.)
      ,clusterAlgo_(-1)
      ,caloConeSize_(-1.)
      ,e2x2_(-9999.)
      ,e3x3_(-9999.)
      ,e5x5_(-9999.)
      ,eMax_(-9999.)
      ,e2nd_(-9999.)
      ,covEtaEta_(-9999.)
      ,covEtaPhi_(-9999.)
      ,covPhiPhi_(-9999.)
      ,convNTracks_(-1)
      ,convEoverP_(-1.)
      ,convMass_(-1.)
      ,convCotanTheta_(-999.)
      ,convLikely_(-1.)
      ,convVertex_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition1_(-9999.,-9999.,-9999.)
      ,convEcalImpactPosition2_(-9999.,-9999.,-9999.)
      ,convIndexTrack1_(-1)
      ,convIndexTrack2_(-1)
      ,convTrack1_(0)
      ,convTrack2_(0)
      ,isolationPersoBasicClusters_(-1.)
      ,isolationPersoBasicClustersDoubleCone_(-1.)
      ,isolationPersoHcalRecHit_(-1.)
      ,isolationPersoTracksSolidCone_(-1.)
      ,isolationPersoNTracksSolidCone_(-1)
      ,dR03IsolationEcalRecHit_(-1.)
      ,dR03IsolationHcalRecHit_(-1.)
      ,dR03IsolationSolidTrkCone_(-1.)
      ,dR03IsolationHollowTrkCone_(-1.)
      ,dR03IsolationNTracksSolidCone_(-1)
      ,dR03IsolationNTracksHollowCone_(-1)
      ,dR04IsolationEcalRecHit_(-1.)
      ,dR04IsolationHcalRecHit_(-1.)
      ,dR04IsolationSolidTrkCone_(-1.)
      ,dR04IsolationHollowTrkCone_(-1.)
      ,dR04IsolationNTracksSolidCone_(-1)
      ,dR04IsolationNTracksHollowCone_(-1)
      ,isLooseEMPhoton_(false)
      ,isLoosePhoton_(false)
      ,isTightPhoton_(false)
      ,isEBPho_(false)
      ,isEEPho_(false)
      ,isEBGap_(false)
      ,isEEGap_(false)
      ,isEBEEGap_(false)
      ,isAlsoElectron_(false)
      ,pi0nn_(-1.)
      {;}
      
      ~TRootPhoton() {;}
      
      
      // Get variables from reco::Photon
      TVector3 caloPosition() const { return caloPosition_; }
      Float_t hoe() const { return hoe_; }
      Bool_t hasPixelSeed() const { return hasPixelSeed_; }
      
      // Get variables from reco::SuperCluster
      Int_t nbClusters() const { return nbClusters_ ;}
      Float_t scRawEnergy() const { return superClusterRawEnergy_; }
      Float_t superClusterRawEnergy() const { return superClusterRawEnergy_; }
      Float_t preshowerEnergy() const { return preshowerEnergy_ ;}
      map<Int_t,Int_t> scIndexMap() const { return scIndex_; }
      map<Int_t,TRef> scRefMap() const { return scRef_; }
      Int_t nSuperClusters() const { return scRef_.size();}
      
      // Get index in TCloneArray of the supercluster associated by default
      // Default SC collection for photon producer defined in
      // RecoEgamma/EgammaPhotonProducers/python/photons_cfi.py
      Int_t scIndex()
      {
         // 0=island, 1=hybrid, 4=multi5x5
         if ( clusterAlgo_== 0 ) return scIndexOfType(122);
         else if ( clusterAlgo_== 1 ) return scIndexOfType(211);
         else if ( clusterAlgo_== 4 ) return scIndexOfType(322);
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
      // Default SC collection for photon producer defined in
      // RecoEgamma/EgammaPhotonProducers/python/photons_cfi.py
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
      
      
      // Get cluster Shape variables
      Int_t clusterAlgo() const { return clusterAlgo_ ;}
      Float_t caloConeSize() const { return caloConeSize_ ;}
      Float_t e2x2() const { return e2x2_ ;}
      Float_t e3x3() const { return e3x3_ ;}
      Float_t e5x5() const { return e5x5_ ;}
      Float_t eMax() const { return eMax_ ;}
      Float_t e2nd() const { return e2nd_ ;}
      Float_t sigmaEtaEta() const { return sigmaEtaEta_ ;}
      Float_t sigmaIetaIeta() const { return sigmaIetaIeta_ ;}
      Float_t covEtaEta() const { return covEtaEta_ ;}
      Float_t covEtaPhi() const { return covEtaPhi_ ;}
      Float_t covPhiPhi() const { return covPhiPhi_ ;}
      Float_t r19() const { return ( e3x3_ == 0. ? -1. : eMax_/e3x3_ ); }  // ratio of Emax/E(3x3)
      // FIXME - Check definition of r9... include preshowerEnergy as in SimplePhotonAnalyzer.cc ?
      Float_t r9() const { return ( superClusterRawEnergy_ == 0. ? -1. : e3x3_/superClusterRawEnergy_ ); } // ratio of E(3x3)/ESC
      
      // Get photon conversions infos
      Int_t convNTracks() const { return convNTracks_; }
      Float_t convEoverP() const { return convEoverP_; }
      Float_t convMass() const { return convMass_; }
      Float_t convCotanTheta() const { return convCotanTheta_; }
      Float_t convLikely() const { return convLikely_; }
      TVector3 convVertex() const { return convVertex_; }
      TVector3 convEcalImpactPosition1() const { return convEcalImpactPosition1_; }
      TVector3 convEcalImpactPosition2() const { return convEcalImpactPosition2_; }
      Int_t convIndexTrack1() const { return convIndexTrack1_; }
      Int_t convIndexTrack2() const { return convIndexTrack2_; }
      TRootTrack* convTrack1() const { return (TRootTrack*) convTrack1_.GetObject(); }
      TRootTrack* convTrack2() const { return (TRootTrack*) convTrack2_.GetObject(); }
      
      // Get photon isolation calculated by PhotonIsolator
      Float_t isolationPersoBasicClusters() const { return isolationPersoBasicClusters_; }
      Float_t isolationPersoBasicClustersDoubleCone() const { return isolationPersoBasicClustersDoubleCone_; }
      Float_t isolationPersoHcalRecHit() const { return isolationPersoHcalRecHit_; }
      Float_t isolationPersoTracksSolidCone() const { return isolationPersoTracksSolidCone_; }
      Int_t isolationPersoNTracksSolidCone() const { return isolationPersoNTracksSolidCone_; }
      
      // Get photon isolation calculated by PhotonID
      Float_t dR03IsolationEcalRecHit() const { return dR03IsolationEcalRecHit_; }
      Float_t dR03IsolationHcalRecHit() const { return dR03IsolationHcalRecHit_; }
      Float_t dR03IsolationSolidTrkCone() const { return dR03IsolationSolidTrkCone_; }
      Float_t dR03IsolationHollowTrkCone() const { return dR03IsolationHollowTrkCone_; }
      Int_t dR03IsolationNTracksSolidCone() const { return dR03IsolationNTracksSolidCone_; }
      Int_t dR03IsolationNTracksHollowCone() const { return dR03IsolationNTracksHollowCone_; }
      
      Float_t dR04IsolationEcalRecHit() const { return dR04IsolationEcalRecHit_; }
      Float_t dR04IsolationHcalRecHit() const { return dR04IsolationHcalRecHit_; }
      Float_t dR04IsolationSolidTrkCone() const { return dR04IsolationSolidTrkCone_; }
      Float_t dR04IsolationHollowTrkCone() const { return dR04IsolationHollowTrkCone_; }
      Int_t dR04IsolationNTracksSolidCone() const { return dR04IsolationNTracksSolidCone_; }
      Int_t dR04IsolationNTracksHollowCone() const { return dR04IsolationNTracksHollowCone_; }
      
      // Get photon ID
      Bool_t isLooseEMPhoton() const { return isLooseEMPhoton_; }
      Bool_t isLoosePhoton() const { return isLoosePhoton_; }
      Bool_t isTightPhoton() const { return isTightPhoton_; }
      Bool_t isEBPho() const { return isEBPho_; }
      Bool_t isEEPho() const { return isEEPho_; }
      Bool_t isEBGap() const { return isEBGap_; }
      Bool_t isEEGap() const { return isEEGap_; }
      Bool_t isEBEEGap() const { return isEBEEGap_; }
      Bool_t isAlsoElectron() const { return isAlsoElectron_; }
      
      // Get Pi0 rejection global variable
      Float_t pi0nn() const { return pi0nn_; }
      
      TRootParticle* genPhoton() const { return genParticle(); }
      virtual TString typeName() const { return "TRootPhoton"; }
      
      
      // Set variables from reco::Photon
      void setCaloPosition(TVector3 caloPosition) { caloPosition_ = caloPosition; }
      void setCaloPosition(Double_t x, Double_t y, Double_t z) { caloPosition_.SetXYZ(x, y ,z); }
      void setHoe(Float_t hoe) { hoe_ = hoe; }
      void setHoE(Float_t hoe) { hoe_ = hoe; }
      void setHasPixelSeed(Bool_t hasPixelSeed) { hasPixelSeed_ = hasPixelSeed; }
      
      // Set variables from reco::SuperCluster
      void setNbClusters(Int_t nbClusters) { nbClusters_ = nbClusters; }
      void setSCRawEnergy(Float_t superClusterRawEnergy) { superClusterRawEnergy_ = superClusterRawEnergy; }
      void setSuperClusterRawEnergy(Float_t superClusterRawEnergy) { superClusterRawEnergy_ = superClusterRawEnergy; }
      void setPreshowerEnergy(Float_t preshowerEnergy) { preshowerEnergy_ = preshowerEnergy; }
      void setSCIndex(Int_t type, Int_t index) { scIndex_[type]=index; }
      void setSCRef(Int_t type, TObject* superCluster) { scRef_[type]=superCluster; }
      
      // Set cluster Shape variables
      void setClusterAlgo(Int_t clusterAlgo) { clusterAlgo_ = clusterAlgo; }
      void setCaloConeSize(Float_t caloConeSize) { caloConeSize_ = caloConeSize; }
      void setE2x2(Float_t e2x2) { e2x2_ = e2x2; }
      void setE3x3(Float_t e3x3) { e3x3_ = e3x3; }
      void setE5x5(Float_t e5x5) { e5x5_ = e5x5; }
      void setEMax(Float_t eMax) { eMax_ = eMax; }
      void setE2nd(Float_t e2nd) { e2nd_ = e2nd; }
      void setSigmaEtaEta(Float_t sigmaEtaEta) { sigmaEtaEta_ = sigmaEtaEta; }
      void setSigmaIetaIeta(Float_t sigmaIetaIeta) { sigmaIetaIeta_ = sigmaIetaIeta; }
      void setCovEtaEta(Float_t covEtaEta) { covEtaEta_ = covEtaEta; }
      void setCovEtaPhi(Float_t covEtaPhi) { covEtaPhi_ = covEtaPhi; }
      void setCovPhiPhi(Float_t covPhiPhi) { covPhiPhi_ = covPhiPhi; }
      
      // Set photon conversions infos
      void setConvNTracks(Int_t convNTracks) { convNTracks_=convNTracks; }
      void setConvEoverP(Float_t convEoverP) { convEoverP_=convEoverP; }
      void setConvMass(Float_t convMass) { convMass_=convMass; }
      void setConvCotanTheta(Float_t convCotanTheta) { convCotanTheta_=convCotanTheta; }
      void setConvLikely(Float_t convLikely) { convLikely_=convLikely; }
      void setConvVertex(TVector3 convVertex) { convVertex_=convVertex; }
      void setConvVertex(Double_t x, Double_t y, Double_t z) { convVertex_.SetXYZ(x, y ,z); }
      void setConvEcalImpactPosition1(TVector3 convEcalImpactPosition1) { convEcalImpactPosition1_=convEcalImpactPosition1; }
      void setConvEcalImpactPosition1(Double_t x, Double_t y, Double_t z) { convEcalImpactPosition1_.SetXYZ(x, y ,z); }
      void setConvEcalImpactPosition2(TVector3 convEcalImpactPosition2) { convEcalImpactPosition2_=convEcalImpactPosition2; }
      void setConvEcalImpactPosition2(Double_t x, Double_t y, Double_t z) { convEcalImpactPosition2_.SetXYZ(x, y ,z); }
      void setConvIndexTrack1(Int_t convIndexTrack1) { convIndexTrack1_=convIndexTrack1; }
      void setConvIndexTrack2(Int_t convIndexTrack2) { convIndexTrack2_=convIndexTrack2; }
      void setConvTrack1(TObject* convTrack1) { convTrack1_=convTrack1; }
      void setConvTrack2(TObject* convTrack2) { convTrack2_=convTrack2; }
      
      // Set photon isolation calculated by PhotonIsolator
      void setIsolationPersoBasicClusters(Float_t isolationPersoBasicClusters) { isolationPersoBasicClusters_ = isolationPersoBasicClusters; }
      void setIsolationPersoBasicClustersDoubleCone(Float_t isolationPersoBasicClustersDoubleCone) { isolationPersoBasicClustersDoubleCone_ = isolationPersoBasicClustersDoubleCone; }
      void setIsolationPersoHcalRecHit(Float_t isolationPersoHcalRecHit) { isolationPersoHcalRecHit_ = isolationPersoHcalRecHit; }
      void setIsolationPersoTracksSolidCone(Float_t isolationPersoTracksSolidCone) { isolationPersoTracksSolidCone_ = isolationPersoTracksSolidCone; }
      void setIsolationPersoNTracksSolidCone(Int_t isolationPersoNTracksSolidCone) { isolationPersoNTracksSolidCone_ = isolationPersoNTracksSolidCone; }
      void setIsolationPerso(Float_t isolationPersoBasicClusters, Float_t isolationPersoBasicClustersDoubleCone, Float_t isolationPersoHcalRecHit, Float_t isolationPersoTracksSolidCone, Int_t isolationPersoNTracksSolidCone)
      {
         isolationPersoBasicClusters_ = isolationPersoBasicClusters;
         isolationPersoBasicClustersDoubleCone_ = isolationPersoBasicClustersDoubleCone;
         isolationPersoHcalRecHit_ = isolationPersoHcalRecHit;
         isolationPersoTracksSolidCone_ = isolationPersoTracksSolidCone;
         isolationPersoNTracksSolidCone_ = isolationPersoNTracksSolidCone;
      }
      
      // Set photon isolation calculated by PhotonID
      void setDR03IsolationEcalRecHit(Float_t dR03IsolationEcalRecHit) { dR03IsolationEcalRecHit_ = dR03IsolationEcalRecHit; }
      void setDR03IsolationHcalRecHit(Float_t dR03IsolationHcalRecHit) { dR03IsolationHcalRecHit_ = dR03IsolationHcalRecHit; }
      void setDR03IsolationSolidTrkCone(Float_t dR03IsolationSolidTrkCone) { dR03IsolationSolidTrkCone_ = dR03IsolationSolidTrkCone; }
      void setDR03IsolationHollowTrkCone(Float_t dR03IsolationHollowTrkCone) { dR03IsolationHollowTrkCone_ = dR03IsolationHollowTrkCone; }
      void setDR03IsolationNTracksSolidCone(Int_t dR03IsolationNTracksSolidCone) { dR03IsolationNTracksSolidCone_ = dR03IsolationNTracksSolidCone; }
      void setDR03IsolationNTracksHollowCone(Int_t dR03IsolationNTracksHollowCone) { dR03IsolationNTracksHollowCone_ = dR03IsolationNTracksHollowCone; }
      void setDR03Isolation(Float_t dR03IsolationEcalRecHit, Float_t dR03IsolationHcalRecHit, Float_t dR03IsolationSolidTrkCone, Float_t dR03IsolationHollowTrkCone, Int_t dR03IsolationNTracksSolidCone, Int_t dR03IsolationNTracksHollowCone)
      {
         dR03IsolationEcalRecHit_ = dR03IsolationEcalRecHit;
         dR03IsolationHcalRecHit_ = dR03IsolationHcalRecHit;
         dR03IsolationSolidTrkCone_ = dR03IsolationSolidTrkCone;
         dR03IsolationHollowTrkCone_ = dR03IsolationHollowTrkCone;
         dR03IsolationNTracksSolidCone_ = dR03IsolationNTracksSolidCone;
         dR03IsolationNTracksHollowCone_ = dR03IsolationNTracksHollowCone;
      }
      
      void setDR04IsolationEcalRecHit(Float_t dR04IsolationEcalRecHit) { dR04IsolationEcalRecHit_ = dR04IsolationEcalRecHit; }
      void setDR04IsolationHcalRecHit(Float_t dR04IsolationHcalRecHit) { dR04IsolationHcalRecHit_ = dR04IsolationHcalRecHit; }
      void setDR04IsolationSolidTrkCone(Float_t dR04IsolationSolidTrkCone) { dR04IsolationSolidTrkCone_ = dR04IsolationSolidTrkCone; }
      void setDR04IsolationHollowTrkCone(Float_t dR04IsolationHollowTrkCone) { dR04IsolationHollowTrkCone_ = dR04IsolationHollowTrkCone; }
      void setDR04IsolationNTracksSolidCone(Int_t dR04IsolationNTracksSolidCone) { dR04IsolationNTracksSolidCone_ = dR04IsolationNTracksSolidCone; }
      void setDR04IsolationNTracksHollowCone(Int_t dR04IsolationNTracksHollowCone) { dR04IsolationNTracksHollowCone_ = dR04IsolationNTracksHollowCone; }
      void setDR04Isolation(Float_t dR04IsolationEcalRecHit, Float_t dR04IsolationHcalRecHit, Float_t dR04IsolationSolidTrkCone, Float_t dR04IsolationHollowTrkCone, Int_t dR04IsolationNTracksSolidCone, Int_t dR04IsolationNTracksHollowCone)
      {
         dR04IsolationEcalRecHit_ = dR04IsolationEcalRecHit;
         dR04IsolationHcalRecHit_ = dR04IsolationHcalRecHit;
         dR04IsolationSolidTrkCone_ = dR04IsolationSolidTrkCone;
         dR04IsolationHollowTrkCone_ = dR04IsolationHollowTrkCone;
         dR04IsolationNTracksSolidCone_ = dR04IsolationNTracksSolidCone;
         dR04IsolationNTracksHollowCone_ = dR04IsolationNTracksHollowCone;
      }
      
      // Set photon ID
      void setIsLooseEMPhoton(Bool_t isLooseEMPhoton) { isLooseEMPhoton_ = isLooseEMPhoton; }
      void setIsLoosePhoton(Bool_t isLoosePhoton) { isLoosePhoton_ = isLoosePhoton; }
      void setIsTightPhoton(Bool_t isTightPhoton) { isTightPhoton_= isTightPhoton; }
      void setIsEBPho(Bool_t isEBPho) { isEBPho_ = isEBPho; }
      void setIsEEPho(Bool_t isEEPho) { isEEPho_ = isEEPho; }
      void setIsEBGap(Bool_t isEBGap) { isEBGap_ = isEBGap; }
      void setIsEEGap(Bool_t isEEGap) { isEEGap_ = isEEGap; }
      void setIsEBEEGap(Bool_t isEBEEGap) { isEBEEGap_ = isEBEEGap; }
      void setIsAlsoElectron(Bool_t isAlsoElectron) { isAlsoElectron_ = isAlsoElectron; }
      void setBitsID(Bool_t isLooseEMPhoton, Bool_t isLoosePhoton, Bool_t isTightPhoton, Bool_t isEBPho, Bool_t isEEPho, Bool_t isEBGap, Bool_t isEEGap, Bool_t isEBEEGap)
      {
         isLooseEMPhoton_ = isLooseEMPhoton;
         isLoosePhoton_ = isLoosePhoton;
         isTightPhoton_= isTightPhoton;
         isEBPho_ = isEBPho;
         isEEPho_ = isEEPho;
         isEBGap_ = isEBGap;
         isEEGap_ = isEEGap;
         isEBEEGap_ = isEBEEGap;
      }
      
      // Set Pi0 rejection global variable
      void setPi0nn(Float_t pi0nn) { pi0nn_ = pi0nn; }
      
      // Attach new vertex position to the photon - Et, Eta, Phi corrected accordingly
      void setVertex(TVector3 vertex) {
         TVector3 direction = caloPosition() - vertex;
         double energy = this->Energy();
         TVector3 momentum = direction.Unit() * energy;
         this->SetXYZT(momentum.x(), momentum.y(), momentum.z(), energy );
         vertex_ = vertex;
      }
      
      
      friend std::ostream& operator<< (std::ostream& stream, const TRootPhoton& photon)
      {
         stream << "TRootPhoton  (E,Et,eta,phi)=("<< photon.Energy() <<","<< photon.Et() <<","<< photon.Eta() <<","<< photon.Phi() << ")"
         << " vertex=("<< photon.vx() <<","<< photon.vy() <<","<< photon.vz() << ")"
         << " caloPosition=(" << photon.caloPosition().X() << "," << photon.caloPosition().Y() << "," << photon.caloPosition().Z() << ")"
         << " hasPxlSeed=" << photon. hasPixelSeed() <<"  E5x5=" << photon.e5x5() <<"  R19=" << photon.r19()
         <<"  R9=" << photon.r9() <<"  hoe=" << photon.hoe()  <<"  Pi0=" << photon.pi0nn()  <<"  nTracksConv=" << photon.convNTracks();
         return stream;
      };
      
      void Print()
      {
         std::cout << "TRootPhoton  (E,Et,eta,phi)=("<< this->Energy() <<","<< this->Et() <<","<< this->Eta() <<","<< this->Phi() << ")"
         << "  vertex=("<< this->vx() <<","<< this->vy() <<","<< this->vz() << ")"
         << "  caloPosition=(" << this->caloPosition().X() << "," << this->caloPosition().Y() << "," << this->caloPosition().Z() << ")" << endl
         << "            algo=" << this->clusterAlgo() << " hasPxlSeed=" << this-> hasPixelSeed() <<"  H/E=" << this->hoe() <<"  Pi0=" << this->pi0nn()
         <<"  nBC=" << this->nbClusters() << " scRawEnergy=" << this->scRawEnergy() << " preshEnergy=" << this->preshowerEnergy() << endl
         <<"            E2x2=" << this->e2x2() <<" E3x3=" << this->e3x3() <<" E5x5=" << this->e5x5() <<" Emax=" << this->eMax()
         <<" E2nd=" << this->e2nd() <<" R19=" << this->r19() <<" R9=" << this->r9() << endl
         <<"            sigmaEtaEta=" << this->sigmaEtaEta() <<" sigmaIetaIeta=" << this->sigmaIetaIeta()
         <<" cEtaEta=" << this->covEtaEta() <<" cEtaPhi=" << this->covEtaPhi() <<" cPhiPhi=" << this->covPhiPhi() << endl
         << "            isoPerso  BC="<< this->isolationPersoBasicClusters() << " DoubleConeBC=" << this->isolationPersoBasicClustersDoubleCone()
         << " hcal=" << this->isolationPersoHcalRecHit() << " track=" << this->isolationPersoTracksSolidCone() << " ntracks=" << this->isolationPersoNTracksSolidCone() << endl
         << "            dR03 isoPhotonID  ecal="<< this->dR03IsolationEcalRecHit() << " hcal=" << this->dR03IsolationHcalRecHit() << " track-hollow=" << this->dR03IsolationHollowTrkCone()
         << " ntracks-hollow=" << this->dR03IsolationNTracksHollowCone() << " track-solid=" << this->dR03IsolationSolidTrkCone() << " ntracks-solid=" << this->dR03IsolationNTracksSolidCone() << endl
         << "            dR04 isoPhotonID  ecal="<< this->dR04IsolationEcalRecHit() << " hcal=" << this->dR04IsolationHcalRecHit() << " track-hollow=" << this->dR04IsolationHollowTrkCone()
         << " ntracks-hollow=" << this->dR04IsolationNTracksHollowCone() << " track-solid=" << this->dR04IsolationSolidTrkCone() << " ntracks-solid=" << this->dR04IsolationNTracksSolidCone() << endl
         <<"            isLooseEMPhoton=" << this->isLooseEMPhoton()  << " isLoosePhoton=" << this->isLoosePhoton()  << " isTightPhoton=" << this->isTightPhoton()
         <<"  isEBPho=" << this->isEBPho() << " isEEPho=" << this->isEEPho()  << " isEBGap=" << this->isEBGap()
         <<"  isEEGap=" << this->isEEGap() << " isEBEEGap=" << this->isEBEEGap()  << " isAlsoElectron=" << this->isAlsoElectron()  <<"  nTracksConv=" << this->convNTracks();
         if (this->convNTracks()>1)
            std::cout << endl << "            Conversion: E/p=" << this->convEoverP() << " Mass=" << this->convMass() << " cotan(Theta)=" << this->convCotanTheta() << " Likely=" << this->convLikely()
            << " (vx,vy,vz)=(" << this->convVertex().X() << ","<< this->convVertex().Y() << ","<< this->convVertex().Z() << ")";
      };
      
      
   private:
      
      // Variables from reco::Photon
      TVector3 caloPosition_;         // SC position if r9<0.93,  position of seed BasicCluster (taking shower depth for unconverted photon) if r9>0.93
      Float_t hoe_;                   // Hadronic energy in HCAL tower matching SuperCluster position over electromagnetic energy
      Bool_t hasPixelSeed_;           // has the SuperCluster a matched pixel seed ?
      
      // Variables from reco::SuperCluster
      Int_t nbClusters_;              // Number of basic clusters components
      Float_t superClusterRawEnergy_; // SuperCluster raw energy
      Float_t preshowerEnergy_;       // Endcap preshower energy
      map<Int_t,Int_t> scIndex_;      // indexes of the seed SuperClusters (one per SC tytpe)
      map<Int_t,TRef> scRef_;         // references to the seed SuperClusters (one per SC tytpe)
      
      // Cluster Shape variables
      // already kept in reco::Photon
      Float_t sigmaEtaEta_;           // sqrt(covariance(Eta,Eta)) taken from reco::Photon::ShowerShape struct
      Float_t sigmaIetaIeta_;         // sqrt(covariance(iEta,iEta)) taken from reco::Photon::ShowerShape struct
      // need reco::SuperCluster and reco::BasicCluster
      Int_t clusterAlgo_;             // reco::BasicCluster::algo() island = 0, hybrid = 1, fixedMatrix = 2, dynamicHybrid = 3, multi5x5 = 4
      Float_t caloConeSize_;          // Delta_R of the cone centered on the reco::GsfElectron and containing all its basic clusters constituents
      // need reco::SuperCluster and reco::BasicCluster and reduced Ecal RecHits Collections for EcalClusterLazyTools calculations
      Float_t e2x2_;                  // 2x2 energy
      Float_t e3x3_;                  // 3x3 energy
      Float_t e5x5_;                  // 5x5 energy
      Float_t eMax_;                  // energy of crystal with max energy
      Float_t e2nd_;                  // energy of crystal with 2nd max energy
      Float_t covEtaEta_;             // Covariance (Eta,Eta) of xtals composing the photon seed BasicCluster (weighted by their energy) calculated by lazytools
      Float_t covEtaPhi_;             // Covariance (Eta,Phi) of xtals composing the photon seed BasicCluster (weighted by their energy) calculated by lazytools
      Float_t covPhiPhi_;             // Covariance (Phi,Phi) of xtals composing the photon seed BasicCluster (weighted by their energy) calculated by lazytools
      
      // Photon conversions
      // Variables from reco::Conversion
      // need reco::Track and reco::TrackExtras specifics to conversions
      // (ckfInOutTracksFromConversions and ckfOutInTracksFromConversions collections)
      Int_t convNTracks_;             // Number of reconstructed tracks associated to the converted photon candidate
      Float_t convEoverP_;            // Super Cluster energy divided by track pair momentum if Standard seeing method. If a pointer to two (or more clusters) is stored in the conversion, this method returns the energy sum of clusters divided by the  track pair momentum
      Float_t convMass_;              // Conversion tracks pair invariant mass
      Float_t convCotanTheta_;        // Cotan(Theta) of conversion tracks pair
      Float_t convLikely_;            // Likelihood value of the tracks pair candidate (Ted's Likelihood)
      TVector3 convVertex_;           // Position of the conversion vertex
      TVector3 convEcalImpactPosition1_;  // Impact position at Ecal front face of the first conversion track
      TVector3 convEcalImpactPosition2_;  // Impact position at Ecal front face of the second conversion track
      Int_t convIndexTrack1_;         // Index of first conversion track (in conversionTracks TCloneArray)
      Int_t convIndexTrack2_;         // Index of second conversion track (in conversionTracks TCloneArray)
      TRef convTrack1_;               // reference of first conversion track (in conversionTracks TCloneArray)
      TRef convTrack2_;               // reference of second conversion track (in conversionTracks TCloneArray)
      
      // Photon isolation calculated by PhotonIsolator
      Float_t isolationPersoBasicClusters_;           // Et sum of BCs in a cone around the photon - sub BasicClusters of photon SuperCluster are excluded.
      Float_t isolationPersoBasicClustersDoubleCone_; // Et sum of BCs in DRmin < DR < DRmax around photon
      Float_t isolationPersoHcalRecHit_;              // Et sum of HCAL rechits in a cone around the photon
      Float_t isolationPersoTracksSolidCone_;         // Pt sum of tracks in a cone around the photon
      Int_t isolationPersoNTracksSolidCone_;          // Tracks multiplicity in a cone around the photon
      
      // Photon isolation calculated by PhotonID
      // need PhotonID ValueMap
      // Isolation parameters defined in  RecoEgamma/PhotonIdentification/python/photonId_cfi.py
      Float_t dR03IsolationEcalRecHit_;      // Jurassic isolation (Sum of ecal rechits in DRmin < DR < DRmax around the photon, excluding an eta slice)
      Float_t dR03IsolationHcalRecHit_;      // Sum of HCAL rechits in DRmin < DR < DRmax around the photon
      Float_t dR03IsolationSolidTrkCone_;    // Pt sum of tracks in a cone around the photon
      Float_t dR03IsolationHollowTrkCone_;   // Pt sum of tracks in DRmin < DR < DRmax around the photon
      Int_t dR03IsolationNTracksSolidCone_;  // Tracks multiplicity in a cone around the photon
      Int_t dR03IsolationNTracksHollowCone_; // Tracks multiplicity in DRmin < DR < DRmax around the photon
      
      Float_t dR04IsolationEcalRecHit_;      // Jurassic isolation (Sum of ecal rechits in DRmin < DR < DRmax around the photon, excluding an eta slice)
      Float_t dR04IsolationHcalRecHit_;      // Sum of HCAL rechits in DRmin < DR < DRmax around the photon
      Float_t dR04IsolationSolidTrkCone_;    // Pt sum of tracks in a cone around the photon
      Float_t dR04IsolationHollowTrkCone_;   // Pt sum of tracks in DRmin < DR < DRmax around the photon
      Int_t dR04IsolationNTracksSolidCone_;  // Tracks multiplicity in a cone around the photon
      Int_t dR04IsolationNTracksHollowCone_; // Tracks multiplicity in DRmin < DR < DRmax around the photon
      
      // Photon ID
      // need PhotonID ValueMap
      // PhotonID criteria defined in RecoEgamma/PhotonIdentification/python/photonId_cfi.py
      // https://twiki.cern.ch/twiki/bin/view/CMS/PhotonIDAnalysis
      Bool_t isLooseEMPhoton_; // is photon passing looseEM ID criteria
      Bool_t isLoosePhoton_;   // is photon passing looseID criteria
      Bool_t isTightPhoton_;   // is pohotn passing tightID criteria
      Bool_t isEBPho_;         // is photon in ECAL barrel ?
      Bool_t isEEPho_;         // is photon in ECAL endcap ?
      Bool_t isEBGap_;         // is photon in EB, and inside the boundaries in super crystals/modules ?
      Bool_t isEEGap_;         // is photon in EE, and inside the boundaries in supercrystal/D ?
      Bool_t isEBEEGap_;       // is photon in boundary between EB and EE ?
      Bool_t isAlsoElectron_;  // is photon also a GsfElectron ?
      
      // Pi0 rejection
      // not working in 2.2.X
      Float_t pi0nn_;          // neural network output of gamma/pi0 discriminator  (0=pi0-like  1=photon-like)
      
      ClassDef (TRootPhoton,10);
      
};

#endif
