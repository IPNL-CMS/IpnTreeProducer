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
   ,nbClusters_(-1)
   ,superClusterRawEnergy_(-1.)
   ,preshowerEnergy_(-1.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-1)
   ,hcalDepth1OverEcal_(-1.)
   ,hcalDepth2OverEcal_(-1.)
   ,hcalDepth1OverEcalBC_(-1.)
   ,hcalDepth2OverEcalBC_(-1.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,e2nd_(-9999.)
   ,covEtaEta_(-9999.)
   ,covEtaPhi_(-9999.)
   ,covPhiPhi_(-9999.)
   ,etaLAT_(-9999.)
   ,phiLAT_(-9999.)
   ,lat_(-9999.)
   ,zernike20_(-9999.)
   ,zernike42_(-9999.)
   ,secondMomentMaj_(-9999.)
   ,secondMomentMin_(-9999.)
   ,secondMomentAlpha_(-9999.)
   ,scEcalEnergy_(-1.)
   ,scEcalEnergyError_(-1.)
   ,scEcalP4_(0.,0.,0.,0.)
   ,phoEcalEnergy_(-1.)
   ,phoEcalEnergyError_(-1.)
   ,phoEcalP4_(0.,0.,0.,0.)
   ,regression1Energy_(-1.)
   ,regression1EnergyError_(-1.)
   ,regression1P4_(0.,0.,0.,0.)
   ,regression2Energy_(-1.)
   ,regression2EnergyError_(-1.)
   ,regression2P4_(0.,0.,0.,0.)
   ,joshEnergyRegressionV3_(-1.)
   ,joshEnergyRegressionV3Error_(-1.)
   ,joshEnergyRegressionV4_(-1.)
   ,joshEnergyRegressionV4Error_(-1.)
   ,joshEnergyRegressionV5_(-1.)
   ,joshEnergyRegressionV5Error_(-1.)
   ,joshEnergyRegressionV8_(-1.)
   ,joshEnergyRegressionV8Error_(-1.) 
   ,isEB_(false)
   ,isEE_(false)
   ,isEBEtaGap_(false)
   ,isEBPhiGap_(false)
   ,isEERingGap_(false)
   ,isEEDeeGap_(false)
   ,isEBEEGap_(false)
   ,dR03IsolationEcalRecHit_(-1.)
   ,dR03IsolationHcalRecHit_(-1.)
   ,dR03IsolationHcalDepth1RecHit_(-1.)
   ,dR03IsolationHcalDepth2RecHit_(-1.)
   ,dR03IsolationSolidTrkCone_(-1.)
   ,dR03IsolationHollowTrkCone_(-1.)
   ,dR03IsolationNTracksSolidCone_(-1)
   ,dR03IsolationNTracksHollowCone_(-1)
   ,dR04IsolationEcalRecHit_(-1.)
   ,dR04IsolationHcalRecHit_(-1.)
   ,dR04IsolationHcalDepth1RecHit_(-1.)
   ,dR04IsolationHcalDepth2RecHit_(-1.)
   ,dR04IsolationSolidTrkCone_(-1.)
   ,dR04IsolationHollowTrkCone_(-1.)
   ,dR04IsolationNTracksSolidCone_(-1)
   ,dR04IsolationNTracksHollowCone_(-1)
   ,isolationPersoBasicClusters_(-1.)
   ,isolationPersoBasicClustersDoubleCone_(-1.)
   ,isolationPersoHcalRecHit_(-1.)
   ,isolationPersoTracksSolidCone_(-1.)
   ,isolationPersoNTracksSolidCone_(-1)
   ,dR04IsolationNNiceTracks_(-1)
   ,pfChargedHadronIso_(-1.)
   ,pfNeutralHadronIso_(-1.)
   ,pfPhotonIso_(-1.)
   ,pfModFrixione_(-1.)
   ,pfNClusterOutsideMustache_(-1)
   ,pfEtOutsideMustache_(-1.)
   ,pfMVA_(-1.)
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
   ,hasPixelSeed_(false)
   ,isPFlowPhoton_(false)
   ,isStandardPhoton_(false)
   ,isAlsoElectron_(false)
   {;}
   
   TRootPhoton(const TRootPhoton& photon) :
   TRootParticle(photon)
   ,caloPosition_(photon.caloPosition_)
   ,nbClusters_(photon.nbClusters_)
   ,superClusterRawEnergy_(photon.superClusterRawEnergy_)
   ,preshowerEnergy_(photon.preshowerEnergy_)
   ,scIndex_(photon.scIndex_)
   ,scRef_(photon.scRef_)
   ,clusterAlgo_(photon.clusterAlgo_)
   ,hcalDepth1OverEcal_(photon.hcalDepth1OverEcal_)
   ,hcalDepth2OverEcal_(photon.hcalDepth2OverEcal_)
   ,hcalDepth1OverEcalBC_(photon.hcalDepth1OverEcalBC_)
   ,hcalDepth2OverEcalBC_(photon.hcalDepth2OverEcalBC_)
   ,sigmaEtaEta_(photon.sigmaEtaEta_)
   ,sigmaIetaIeta_(photon.sigmaIetaIeta_)
   ,e2x2_(photon.e2x2_)
   ,e3x3_(photon.e3x3_)
   ,e5x5_(photon.e5x5_)
   ,eMax_(photon.eMax_)
   ,e2nd_(photon.e2nd_)
   ,covEtaEta_(photon.covEtaEta_)
   ,covEtaPhi_(photon.covEtaPhi_)
   ,covPhiPhi_(photon.covPhiPhi_)
   ,etaLAT_(photon.etaLAT_)
   ,phiLAT_(photon.phiLAT_)
   ,lat_(photon.lat_)
   ,zernike20_(photon.zernike20_)
   ,zernike42_(photon.zernike42_)
   ,secondMomentMaj_(photon.secondMomentMaj_)
   ,secondMomentMin_(photon.secondMomentMin_)
   ,secondMomentAlpha_(photon.secondMomentAlpha_)
   ,scEcalEnergy_(photon.scEcalEnergy_)
   ,scEcalEnergyError_(photon.scEcalEnergyError_)
   ,scEcalP4_(photon.scEcalP4_)
   ,phoEcalEnergy_(photon.phoEcalEnergy_)
   ,phoEcalEnergyError_(photon.phoEcalEnergyError_)
   ,phoEcalP4_(photon.phoEcalP4_)
   ,regression1Energy_(photon.regression1Energy_)
   ,regression1EnergyError_(photon.regression1EnergyError_)
   ,regression1P4_(photon.regression1P4_)
   ,regression2Energy_(photon.regression2Energy_)
   ,regression2EnergyError_(photon.regression2EnergyError_)
   ,regression2P4_(photon.regression2P4_)
   ,joshEnergyRegressionV3_(photon.joshEnergyRegressionV3_)
   ,joshEnergyRegressionV3Error_(photon.joshEnergyRegressionV3Error_)
   ,joshEnergyRegressionV4_(photon.joshEnergyRegressionV4_)
   ,joshEnergyRegressionV4Error_(photon.joshEnergyRegressionV4Error_)
   ,joshEnergyRegressionV5_(photon.joshEnergyRegressionV5_)
   ,joshEnergyRegressionV5Error_(photon.joshEnergyRegressionV5Error_)
   ,joshEnergyRegressionV8_(photon.joshEnergyRegressionV8_)
   ,joshEnergyRegressionV8Error_(photon.joshEnergyRegressionV8Error_)
   ,isEB_(photon.isEB_)
   ,isEE_(photon.isEE_)
   ,isEBEtaGap_(photon.isEBEtaGap_)
   ,isEBPhiGap_(photon.isEBPhiGap_)
   ,isEERingGap_(photon.isEERingGap_)
   ,isEEDeeGap_(photon.isEEDeeGap_)
   ,isEBEEGap_(photon.isEBEEGap_)
   ,dR03IsolationEcalRecHit_(photon.dR03IsolationEcalRecHit_)
   ,dR03IsolationHcalRecHit_(photon.dR03IsolationHcalRecHit_)
   ,dR03IsolationHcalDepth1RecHit_(photon.dR03IsolationHcalDepth1RecHit_)
   ,dR03IsolationHcalDepth2RecHit_(photon.dR03IsolationHcalDepth2RecHit_)
   ,dR03IsolationSolidTrkCone_(photon.dR03IsolationSolidTrkCone_)
   ,dR03IsolationHollowTrkCone_(photon.dR03IsolationHollowTrkCone_)
   ,dR03IsolationNTracksSolidCone_(photon.dR03IsolationNTracksSolidCone_)
   ,dR03IsolationNTracksHollowCone_(photon.dR03IsolationNTracksHollowCone_)
   ,dR04IsolationEcalRecHit_(photon.dR04IsolationEcalRecHit_)
   ,dR04IsolationHcalRecHit_(photon.dR04IsolationHcalRecHit_)
   ,dR04IsolationHcalDepth1RecHit_(photon.dR04IsolationHcalDepth1RecHit_)
   ,dR04IsolationHcalDepth2RecHit_(photon.dR04IsolationHcalDepth2RecHit_)
   ,dR04IsolationSolidTrkCone_(photon.dR04IsolationSolidTrkCone_)
   ,dR04IsolationHollowTrkCone_(photon.dR04IsolationHollowTrkCone_)
   ,dR04IsolationNTracksSolidCone_(photon.dR04IsolationNTracksSolidCone_)
   ,dR04IsolationNTracksHollowCone_(photon.dR04IsolationNTracksHollowCone_)
   ,isolationPersoBasicClusters_(photon.isolationPersoBasicClusters_)
   ,isolationPersoBasicClustersDoubleCone_(photon.isolationPersoBasicClustersDoubleCone_)
   ,isolationPersoHcalRecHit_(photon.isolationPersoHcalRecHit_)
   ,isolationPersoTracksSolidCone_(photon.isolationPersoTracksSolidCone_)
   ,isolationPersoNTracksSolidCone_(photon.isolationPersoNTracksSolidCone_)
   ,dR04IsolationNNiceTracks_(photon.dR04IsolationNNiceTracks_)
   ,pfChargedHadronIso_(photon.pfChargedHadronIso_)
   ,pfNeutralHadronIso_(photon.pfNeutralHadronIso_)
   ,pfPhotonIso_(photon.pfPhotonIso_)
   ,pfModFrixione_(photon.pfModFrixione_)
   ,pfNClusterOutsideMustache_(photon.pfNClusterOutsideMustache_)
   ,pfEtOutsideMustache_(photon.pfEtOutsideMustache_)
   ,pfMVA_(photon.pfMVA_)
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
   ,hasPixelSeed_(photon.hasPixelSeed_)
   ,isPFlowPhoton_(photon.isPFlowPhoton_)
   ,isStandardPhoton_(photon.isStandardPhoton_)
   ,isAlsoElectron_(photon.isAlsoElectron_)
   {;}
   
   TRootPhoton(Double_t px, Double_t py, Double_t pz, Double_t e) :
   TRootParticle(px,py,pz,e)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,nbClusters_(-1)
   ,superClusterRawEnergy_(-1.)
   ,preshowerEnergy_(-1.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-1)
   ,hcalDepth1OverEcal_(-1.)
   ,hcalDepth2OverEcal_(-1.)
   ,hcalDepth1OverEcalBC_(-1.)
   ,hcalDepth2OverEcalBC_(-1.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,e2nd_(-9999.)
   ,covEtaEta_(-9999.)
   ,covEtaPhi_(-9999.)
   ,covPhiPhi_(-9999.)
   ,etaLAT_(-9999.)
   ,phiLAT_(-9999.)
   ,lat_(-9999.)
   ,zernike20_(-9999.)
   ,zernike42_(-9999.)
   ,secondMomentMaj_(-9999.)
   ,secondMomentMin_(-9999.)
   ,secondMomentAlpha_(-9999.)
   ,scEcalEnergy_(-1.)
   ,scEcalEnergyError_(-1.)
   ,scEcalP4_(0.,0.,0.,0.)
   ,phoEcalEnergy_(-1.)
   ,phoEcalEnergyError_(-1.)
   ,phoEcalP4_(0.,0.,0.,0.)
   ,regression1Energy_(-1.)
   ,regression1EnergyError_(-1.)
   ,regression1P4_(0.,0.,0.,0.)
   ,regression2Energy_(-1.)
   ,regression2EnergyError_(-1.)
   ,regression2P4_(0.,0.,0.,0.)
   ,joshEnergyRegressionV3_(-1.)
   ,joshEnergyRegressionV3Error_(-1.)
   ,joshEnergyRegressionV4_(-1.)
   ,joshEnergyRegressionV4Error_(-1.)
   ,joshEnergyRegressionV5_(-1.)
   ,joshEnergyRegressionV5Error_(-1.)
   ,joshEnergyRegressionV8_(-1.)
   ,joshEnergyRegressionV8Error_(-1.)
   ,isEB_(false)
   ,isEE_(false)
   ,isEBEtaGap_(false)
   ,isEBPhiGap_(false)
   ,isEERingGap_(false)
   ,isEEDeeGap_(false)
   ,isEBEEGap_(false)
   ,dR03IsolationEcalRecHit_(-1.)
   ,dR03IsolationHcalRecHit_(-1.)
   ,dR03IsolationHcalDepth1RecHit_(-1.)
   ,dR03IsolationHcalDepth2RecHit_(-1.)
   ,dR03IsolationSolidTrkCone_(-1.)
   ,dR03IsolationHollowTrkCone_(-1.)
   ,dR03IsolationNTracksSolidCone_(-1)
   ,dR03IsolationNTracksHollowCone_(-1)
   ,dR04IsolationEcalRecHit_(-1.)
   ,dR04IsolationHcalRecHit_(-1.)
   ,dR04IsolationHcalDepth1RecHit_(-1.)
   ,dR04IsolationHcalDepth2RecHit_(-1.)
   ,dR04IsolationSolidTrkCone_(-1.)
   ,dR04IsolationHollowTrkCone_(-1.)
   ,dR04IsolationNTracksSolidCone_(-1)
   ,dR04IsolationNTracksHollowCone_(-1)
   ,isolationPersoBasicClusters_(-1.)
   ,isolationPersoBasicClustersDoubleCone_(-1.)
   ,isolationPersoHcalRecHit_(-1.)
   ,isolationPersoTracksSolidCone_(-1.)
   ,isolationPersoNTracksSolidCone_(-1)
   ,dR04IsolationNNiceTracks_(-1)
   ,pfChargedHadronIso_(-1.)
   ,pfNeutralHadronIso_(-1.)
   ,pfPhotonIso_(-1.)
   ,pfModFrixione_(-1.)
   ,pfNClusterOutsideMustache_(-1)
   ,pfEtOutsideMustache_(-1.)
   ,pfMVA_(-1.)
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
   ,hasPixelSeed_(false)
   ,isPFlowPhoton_(false)
   ,isStandardPhoton_(false)
   ,isAlsoElectron_(false)
   {;}
   
   TRootPhoton(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,nbClusters_(-1)
   ,superClusterRawEnergy_(-1.)
   ,preshowerEnergy_(-1.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-1)
   ,hcalDepth1OverEcal_(-1.)
   ,hcalDepth2OverEcal_(-1.)
   ,hcalDepth1OverEcalBC_(-1.)
   ,hcalDepth2OverEcalBC_(-1.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,e2nd_(-9999.)
   ,covEtaEta_(-9999.)
   ,covEtaPhi_(-9999.)
   ,covPhiPhi_(-9999.)
   ,etaLAT_(-9999.)
   ,phiLAT_(-9999.)
   ,lat_(-9999.)
   ,zernike20_(-9999.)
   ,zernike42_(-9999.)
   ,secondMomentMaj_(-9999.)
   ,secondMomentMin_(-9999.)
   ,secondMomentAlpha_(-9999.)
   ,scEcalEnergy_(-1.)
   ,scEcalEnergyError_(-1.)
   ,scEcalP4_(0.,0.,0.,0.)
   ,phoEcalEnergy_(-1.)
   ,phoEcalEnergyError_(-1.)
   ,phoEcalP4_(0.,0.,0.,0.)
   ,regression1Energy_(-1.)
   ,regression1EnergyError_(-1.)
   ,regression1P4_(0.,0.,0.,0.)
   ,regression2Energy_(-1.)
   ,regression2EnergyError_(-1.)
   ,regression2P4_(0.,0.,0.,0.)
   ,joshEnergyRegressionV3_(-1.)
   ,joshEnergyRegressionV3Error_(-1.)
   ,joshEnergyRegressionV4_(-1.)
   ,joshEnergyRegressionV4Error_(-1.)
   ,joshEnergyRegressionV5_(-1.)
   ,joshEnergyRegressionV5Error_(-1.)
   ,joshEnergyRegressionV8_(-1.)
   ,joshEnergyRegressionV8Error_(-1.)
   ,isEB_(false)
   ,isEE_(false)
   ,isEBEtaGap_(false)
   ,isEBPhiGap_(false)
   ,isEERingGap_(false)
   ,isEEDeeGap_(false)
   ,isEBEEGap_(false)
   ,dR03IsolationEcalRecHit_(-1.)
   ,dR03IsolationHcalRecHit_(-1.)
   ,dR03IsolationHcalDepth1RecHit_(-1.)
   ,dR03IsolationHcalDepth2RecHit_(-1.)
   ,dR03IsolationSolidTrkCone_(-1.)
   ,dR03IsolationHollowTrkCone_(-1.)
   ,dR03IsolationNTracksSolidCone_(-1)
   ,dR03IsolationNTracksHollowCone_(-1)
   ,dR04IsolationEcalRecHit_(-1.)
   ,dR04IsolationHcalRecHit_(-1.)
   ,dR04IsolationHcalDepth1RecHit_(-1.)
   ,dR04IsolationHcalDepth2RecHit_(-1.)
   ,dR04IsolationSolidTrkCone_(-1.)
   ,dR04IsolationHollowTrkCone_(-1.)
   ,dR04IsolationNTracksSolidCone_(-1)
   ,dR04IsolationNTracksHollowCone_(-1)
   ,isolationPersoBasicClusters_(-1.)
   ,isolationPersoBasicClustersDoubleCone_(-1.)
   ,isolationPersoHcalRecHit_(-1.)
   ,isolationPersoTracksSolidCone_(-1.)
   ,isolationPersoNTracksSolidCone_(-1)
   ,dR04IsolationNNiceTracks_(-1)
   ,pfChargedHadronIso_(-1.)
   ,pfNeutralHadronIso_(-1.)
   ,pfPhotonIso_(-1.)
   ,pfModFrixione_(-1.)
   ,pfNClusterOutsideMustache_(-1)
   ,pfEtOutsideMustache_(-1.)
   ,pfMVA_(-1.)
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
   ,hasPixelSeed_(false)
   ,isPFlowPhoton_(false)
   ,isStandardPhoton_(false)
   ,isAlsoElectron_(false)
   {;}
   
   TRootPhoton(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,nbClusters_(-1)
   ,superClusterRawEnergy_(-1.)
   ,preshowerEnergy_(-1.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-1)
   ,hcalDepth1OverEcal_(-1.)
   ,hcalDepth2OverEcal_(-1.)
   ,hcalDepth1OverEcalBC_(-1.)
   ,hcalDepth2OverEcalBC_(-1.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,e2nd_(-9999.)
   ,covEtaEta_(-9999.)
   ,covEtaPhi_(-9999.)
   ,covPhiPhi_(-9999.)
   ,etaLAT_(-9999.)
   ,phiLAT_(-9999.)
   ,lat_(-9999.)
   ,zernike20_(-9999.)
   ,zernike42_(-9999.)
   ,secondMomentMaj_(-9999.)
   ,secondMomentMin_(-9999.)
   ,secondMomentAlpha_(-9999.)
   ,scEcalEnergy_(-1.)
   ,scEcalEnergyError_(-1.)
   ,scEcalP4_(0.,0.,0.,0.)
   ,phoEcalEnergy_(-1.)
   ,phoEcalEnergyError_(-1.)
   ,phoEcalP4_(0.,0.,0.,0.)
   ,regression1Energy_(-1.)
   ,regression1EnergyError_(-1.)
   ,regression1P4_(0.,0.,0.,0.)
   ,regression2Energy_(-1.)
   ,regression2EnergyError_(-1.)
   ,regression2P4_(0.,0.,0.,0.)
   ,joshEnergyRegressionV3_(-1.)
   ,joshEnergyRegressionV3Error_(-1.)
   ,joshEnergyRegressionV4_(-1.)
   ,joshEnergyRegressionV4Error_(-1.)
   ,joshEnergyRegressionV5_(-1.)
   ,joshEnergyRegressionV5Error_(-1.)
   ,joshEnergyRegressionV8_(-1.)
   ,joshEnergyRegressionV8Error_(-1.)
   ,isEB_(false)
   ,isEE_(false)
   ,isEBEtaGap_(false)
   ,isEBPhiGap_(false)
   ,isEERingGap_(false)
   ,isEEDeeGap_(false)
   ,isEBEEGap_(false)
   ,dR03IsolationEcalRecHit_(-1.)
   ,dR03IsolationHcalRecHit_(-1.)
   ,dR03IsolationHcalDepth1RecHit_(-1.)
   ,dR03IsolationHcalDepth2RecHit_(-1.)
   ,dR03IsolationSolidTrkCone_(-1.)
   ,dR03IsolationHollowTrkCone_(-1.)
   ,dR03IsolationNTracksSolidCone_(-1)
   ,dR03IsolationNTracksHollowCone_(-1)
   ,dR04IsolationEcalRecHit_(-1.)
   ,dR04IsolationHcalRecHit_(-1.)
   ,dR04IsolationHcalDepth1RecHit_(-1.)
   ,dR04IsolationHcalDepth2RecHit_(-1.)
   ,dR04IsolationSolidTrkCone_(-1.)
   ,dR04IsolationHollowTrkCone_(-1.)
   ,dR04IsolationNTracksSolidCone_(-1)
   ,dR04IsolationNTracksHollowCone_(-1)
   ,isolationPersoBasicClusters_(-1.)
   ,isolationPersoBasicClustersDoubleCone_(-1.)
   ,isolationPersoHcalRecHit_(-1.)
   ,isolationPersoTracksSolidCone_(-1.)
   ,isolationPersoNTracksSolidCone_(-1)
   ,dR04IsolationNNiceTracks_(-1)
   ,pfChargedHadronIso_(-1.)
   ,pfNeutralHadronIso_(-1.)
   ,pfPhotonIso_(-1.)
   ,pfModFrixione_(-1.)
   ,pfNClusterOutsideMustache_(-1)
   ,pfEtOutsideMustache_(-1.)
   ,pfMVA_(-1.)
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
   ,hasPixelSeed_(false)
   ,isPFlowPhoton_(false)
   ,isStandardPhoton_(false)
   ,isAlsoElectron_(false)
   {;}
   
   TRootPhoton(const TLorentzVector &momentum) :
   TRootParticle(momentum)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,nbClusters_(-1)
   ,superClusterRawEnergy_(-1.)
   ,preshowerEnergy_(-1.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-1)
   ,hcalDepth1OverEcal_(-1.)
   ,hcalDepth2OverEcal_(-1.)
   ,hcalDepth1OverEcalBC_(-1.)
   ,hcalDepth2OverEcalBC_(-1.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,e2nd_(-9999.)
   ,covEtaEta_(-9999.)
   ,covEtaPhi_(-9999.)
   ,covPhiPhi_(-9999.)
   ,etaLAT_(-9999.)
   ,phiLAT_(-9999.)
   ,lat_(-9999.)
   ,zernike20_(-9999.)
   ,zernike42_(-9999.)
   ,secondMomentMaj_(-9999.)
   ,secondMomentMin_(-9999.)
   ,secondMomentAlpha_(-9999.)
   ,scEcalEnergy_(-1.)
   ,scEcalEnergyError_(-1.)
   ,scEcalP4_(0.,0.,0.,0.)
   ,phoEcalEnergy_(-1.)
   ,phoEcalEnergyError_(-1.)
   ,phoEcalP4_(0.,0.,0.,0.)
   ,regression1Energy_(-1.)
   ,regression1EnergyError_(-1.)
   ,regression1P4_(0.,0.,0.,0.)
   ,regression2Energy_(-1.)
   ,regression2EnergyError_(-1.)
   ,regression2P4_(0.,0.,0.,0.)
   ,joshEnergyRegressionV3_(-1.)
   ,joshEnergyRegressionV3Error_(-1.)
   ,joshEnergyRegressionV4_(-1.)
   ,joshEnergyRegressionV4Error_(-1.)
   ,joshEnergyRegressionV5_(-1.)
   ,joshEnergyRegressionV5Error_(-1.)
   ,joshEnergyRegressionV8_(-1.)
   ,joshEnergyRegressionV8Error_(-1.)
   ,isEB_(false)
   ,isEE_(false)
   ,isEBEtaGap_(false)
   ,isEBPhiGap_(false)
   ,isEERingGap_(false)
   ,isEEDeeGap_(false)
   ,isEBEEGap_(false)
   ,dR03IsolationEcalRecHit_(-1.)
   ,dR03IsolationHcalRecHit_(-1.)
   ,dR03IsolationHcalDepth1RecHit_(-1.)
   ,dR03IsolationHcalDepth2RecHit_(-1.)
   ,dR03IsolationSolidTrkCone_(-1.)
   ,dR03IsolationHollowTrkCone_(-1.)
   ,dR03IsolationNTracksSolidCone_(-1)
   ,dR03IsolationNTracksHollowCone_(-1)
   ,dR04IsolationEcalRecHit_(-1.)
   ,dR04IsolationHcalRecHit_(-1.)
   ,dR04IsolationHcalDepth1RecHit_(-1.)
   ,dR04IsolationHcalDepth2RecHit_(-1.)
   ,dR04IsolationSolidTrkCone_(-1.)
   ,dR04IsolationHollowTrkCone_(-1.)
   ,dR04IsolationNTracksSolidCone_(-1)
   ,dR04IsolationNTracksHollowCone_(-1)
   ,isolationPersoBasicClusters_(-1.)
   ,isolationPersoBasicClustersDoubleCone_(-1.)
   ,isolationPersoHcalRecHit_(-1.)
   ,isolationPersoTracksSolidCone_(-1.)
   ,isolationPersoNTracksSolidCone_(-1)
   ,dR04IsolationNNiceTracks_(-1)
   ,pfChargedHadronIso_(-1.)
   ,pfNeutralHadronIso_(-1.)
   ,pfPhotonIso_(-1.)
   ,pfModFrixione_(-1.)
   ,pfNClusterOutsideMustache_(-1)
   ,pfEtOutsideMustache_(-1.)
   ,pfMVA_(-1.)
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
   ,hasPixelSeed_(false)
   ,isPFlowPhoton_(false)
   ,isStandardPhoton_(false)
   ,isAlsoElectron_(false)
   {;}
   
   TRootPhoton(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
   TRootParticle(momentum, vertex, type, charge)
   ,caloPosition_(-9999.,-9999.,-9999.)
   ,nbClusters_(-1)
   ,superClusterRawEnergy_(-1.)
   ,preshowerEnergy_(-1.)
   ,scIndex_()
   ,scRef_()
   ,clusterAlgo_(-1)
   ,hcalDepth1OverEcal_(-1.)
   ,hcalDepth2OverEcal_(-1.)
   ,hcalDepth1OverEcalBC_(-1.)
   ,hcalDepth2OverEcalBC_(-1.)
   ,sigmaEtaEta_(-9999.)
   ,sigmaIetaIeta_(-9999.)
   ,e2x2_(-9999.)
   ,e3x3_(-9999.)
   ,e5x5_(-9999.)
   ,eMax_(-9999.)
   ,e2nd_(-9999.)
   ,covEtaEta_(-9999.)
   ,covEtaPhi_(-9999.)
   ,covPhiPhi_(-9999.)
   ,etaLAT_(-9999.)
   ,phiLAT_(-9999.)
   ,lat_(-9999.)
   ,zernike20_(-9999.)
   ,zernike42_(-9999.)
   ,secondMomentMaj_(-9999.)
   ,secondMomentMin_(-9999.)
   ,secondMomentAlpha_(-9999.)
   ,scEcalEnergy_(-1.)
   ,scEcalEnergyError_(-1.)
   ,scEcalP4_(0.,0.,0.,0.)
   ,phoEcalEnergy_(-1.)
   ,phoEcalEnergyError_(-1.)
   ,phoEcalP4_(0.,0.,0.,0.)
   ,regression1Energy_(-1.)
   ,regression1EnergyError_(-1.)
   ,regression1P4_(0.,0.,0.,0.)
   ,regression2Energy_(-1.)
   ,regression2EnergyError_(-1.)
   ,regression2P4_(0.,0.,0.,0.)
   ,joshEnergyRegressionV3_(-1.)
   ,joshEnergyRegressionV3Error_(-1.)
   ,joshEnergyRegressionV4_(-1.)
   ,joshEnergyRegressionV4Error_(-1.)
   ,joshEnergyRegressionV5_(-1.)
   ,joshEnergyRegressionV5Error_(-1.)
   ,joshEnergyRegressionV8_(-1.)
   ,joshEnergyRegressionV8Error_(-1.)
   ,isEB_(false)
   ,isEE_(false)
   ,isEBEtaGap_(false)
   ,isEBPhiGap_(false)
   ,isEERingGap_(false)
   ,isEEDeeGap_(false)
   ,isEBEEGap_(false)
   ,dR03IsolationEcalRecHit_(-1.)
   ,dR03IsolationHcalRecHit_(-1.)
   ,dR03IsolationHcalDepth1RecHit_(-1.)
   ,dR03IsolationHcalDepth2RecHit_(-1.)
   ,dR03IsolationSolidTrkCone_(-1.)
   ,dR03IsolationHollowTrkCone_(-1.)
   ,dR03IsolationNTracksSolidCone_(-1)
   ,dR03IsolationNTracksHollowCone_(-1)
   ,dR04IsolationEcalRecHit_(-1.)
   ,dR04IsolationHcalRecHit_(-1.)
   ,dR04IsolationHcalDepth1RecHit_(-1.)
   ,dR04IsolationHcalDepth2RecHit_(-1.)
   ,dR04IsolationSolidTrkCone_(-1.)
   ,dR04IsolationHollowTrkCone_(-1.)
   ,dR04IsolationNTracksSolidCone_(-1)
   ,dR04IsolationNTracksHollowCone_(-1)
   ,isolationPersoBasicClusters_(-1.)
   ,isolationPersoBasicClustersDoubleCone_(-1.)
   ,isolationPersoHcalRecHit_(-1.)
   ,isolationPersoTracksSolidCone_(-1.)
   ,isolationPersoNTracksSolidCone_(-1)
   ,dR04IsolationNNiceTracks_(-1)
   ,pfChargedHadronIso_(-1.)
   ,pfNeutralHadronIso_(-1.)
   ,pfPhotonIso_(-1.)
   ,pfModFrixione_(-1.)
   ,pfNClusterOutsideMustache_(-1)
   ,pfEtOutsideMustache_(-1.)
   ,pfMVA_(-1.)
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
   ,hasPixelSeed_(false)
   ,isPFlowPhoton_(false)
   ,isStandardPhoton_(false)
   ,isAlsoElectron_(false)
   {;}
   
   ~TRootPhoton() {;}
   
   
   
   // Get variables from reco::Photon
   TVector3 caloPosition() const { return caloPosition_; }
   
   //=======================================================
   // Supercluster infos
   //=======================================================
   
   // Get variables from reco::SuperCluster
   Int_t nbClusters() const { return nbClusters_ ;}
   Float_t scRawEnergy() const { return superClusterRawEnergy_; }
   Float_t superClusterRawEnergy() const { return superClusterRawEnergy_; }
   Float_t preshowerEnergy() const { return preshowerEnergy_ ;}
   map<Int_t,Int_t> scIndexMap() const { return scIndex_; }
   map<Int_t,TRef> scRefMap() const { return scRef_; }
   Int_t nSuperClusters() const { return scRef_.size();}
   Int_t clusterAlgo() const { return clusterAlgo_ ;}
   
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
   
   
   //=======================================================
   // Shower Shape Variables
   //=======================================================
   
   Float_t hoe() const { return hadronicOverEm(); }
   Float_t hadronicOverEm() const {return hcalDepth1OverEcal_ + hcalDepth2OverEcal_ ;}
   Float_t hadronicDepth1OverEm() const { return hcalDepth1OverEcal_ ;}
   Float_t hadronicDepth2OverEm() const { return hcalDepth2OverEcal_ ;}
   
   Float_t hadTowOverEm() const {return hcalDepth1OverEcalBC_ + hcalDepth2OverEcalBC_ ;}
   Float_t hadTowDepth1OverEm() const { return hcalDepth1OverEcalBC_ ;}
   Float_t hadTowDepth2OverEm() const { return hcalDepth2OverEcalBC_ ;}
   
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
   Float_t etaLAT() const {return etaLAT_ ;}
   Float_t phiLAT() const {return phiLAT_ ;}
   Float_t lat() const {return lat_ ;}
   Float_t zernike20() const {return zernike20_ ;}
   Float_t zernike42() const {return zernike42_ ;}
   Float_t secondMomentMaj() const {return secondMomentMaj_ ;}
   Float_t secondMomentMin() const {return secondMomentMin_ ;}
   Float_t secondMomentAlpha() const {return secondMomentAlpha_ ;}
   Float_t r19() const { return ( e3x3_ == 0. ? -1. : eMax_/e3x3_ ); }  // ratio of Emax/E(3x3)
   Float_t r9() const { return ( superClusterRawEnergy_ == 0. ? -1. : e3x3_/superClusterRawEnergy_ ); } // ratio of E(3x3)/ESC
   
   
   //=======================================================
   // Energy Determinations  (stored in reco::Photon)
   //=======================================================
   
   Float_t energy_ecalStandard() const { return scEcalEnergy_; }
   Float_t energyError_ecalStandard() const { return scEcalEnergyError_; }
   const TLorentzVector& p4_ecalStandard() const  { return scEcalP4_; };
   
   Float_t energy_ecalPhoton() const { return phoEcalEnergy_; }
   Float_t energyError_ecalPhoton() const { return phoEcalEnergyError_; }
   const TLorentzVector& p4_ecalPhoton() const  { return phoEcalP4_; };
   
   Float_t energy_regression1() const { return regression1Energy_; }
   Float_t energyError_regression1() const { return regression1EnergyError_; }
   const TLorentzVector& p4_regression1() const  { return regression1P4_; };
   
   Float_t energy_regression2() const { return regression2Energy_; }
   Float_t energyError_regression2() const { return regression2EnergyError_; }
   const TLorentzVector& p4_regression2() const  { return regression2P4_; };
   
   
   //=======================================================
   // Energy Regression  (calculated on the fly)
   //=======================================================
   
   Float_t joshEnergyRegressionV3() const { return joshEnergyRegressionV3_; }
   Float_t joshEnergyRegressionV3Error() const { return joshEnergyRegressionV3Error_; } 
   Float_t joshEnergyRegressionV4() const { return joshEnergyRegressionV4_; }
   Float_t joshEnergyRegressionV4Error() const { return joshEnergyRegressionV4Error_; } 
   Float_t joshEnergyRegressionV5() const { return joshEnergyRegressionV5_; }
   Float_t joshEnergyRegressionV5Error() const { return joshEnergyRegressionV5Error_; } 
   Float_t joshEnergyRegressionV8() const { return joshEnergyRegressionV8_; }
   Float_t joshEnergyRegressionV8Error() const { return joshEnergyRegressionV8Error_; } 
   
   //=======================================================
   // Fiducial flags  (stored in reco::Photon)
   //=======================================================
   
   // Get fiducial flags
   bool isEB() const{return  isEB_; }
   bool isEE() const{return isEE_; }
   bool isEBGap() const { return (isEBEtaGap() || isEBPhiGap()); }
   bool isEBEtaGap() const{return isEBEtaGap_; }
   bool isEBPhiGap() const{return isEBPhiGap_; }
   bool isEEGap() const { return (isEERingGap() || isEEDeeGap()); }
   bool isEERingGap() const{return isEERingGap_; }
   bool isEEDeeGap() const{return isEEDeeGap_; }
   bool isEBEEGap() const{return isEBEEGap_; }
   
   
   
   //=======================================================
   // Isolation Variables
   //=======================================================
   
   // standard reco isolation (stored in reco::Photon)
   Float_t dR03IsolationEcalRecHit() const { return dR03IsolationEcalRecHit_; }
   Float_t dR03IsolationHcalRecHit() const { return dR03IsolationHcalRecHit_; }
   Float_t dR03IsolationHcalDepth1RecHit() const { return dR03IsolationHcalDepth1RecHit_; }
   Float_t dR03IsolationHcalDepth2RecHit() const { return dR03IsolationHcalDepth2RecHit_; }
   Float_t dR03IsolationSolidTrkCone() const { return dR03IsolationSolidTrkCone_; }
   Float_t dR03IsolationHollowTrkCone() const { return dR03IsolationHollowTrkCone_; }
   Int_t dR03IsolationNTracksSolidCone() const { return dR03IsolationNTracksSolidCone_; }
   Int_t dR03IsolationNTracksHollowCone() const { return dR03IsolationNTracksHollowCone_; }
   
   Float_t dR04IsolationEcalRecHit() const { return dR04IsolationEcalRecHit_; }
   Float_t dR04IsolationHcalRecHit() const { return dR04IsolationHcalRecHit_; }
   Float_t dR04IsolationHcalDepth1RecHit() const { return dR04IsolationHcalDepth1RecHit_; }
   Float_t dR04IsolationHcalDepth2RecHit() const { return dR04IsolationHcalDepth2RecHit_; }
   Float_t dR04IsolationSolidTrkCone() const { return dR04IsolationSolidTrkCone_; }
   Float_t dR04IsolationHollowTrkCone() const { return dR04IsolationHollowTrkCone_; }
   Int_t dR04IsolationNTracksSolidCone() const { return dR04IsolationNTracksSolidCone_; }
   Int_t dR04IsolationNTracksHollowCone() const { return dR04IsolationNTracksHollowCone_; }
   
   // Isolation Variables calculated by PhotonIsolator
   Float_t isolationPersoBasicClusters() const { return isolationPersoBasicClusters_; }
   Float_t isolationPersoBasicClustersDoubleCone() const { return isolationPersoBasicClustersDoubleCone_; }
   Float_t isolationPersoHcalRecHit() const { return isolationPersoHcalRecHit_; }
   Float_t isolationPersoTracksSolidCone() const { return isolationPersoTracksSolidCone_; }
   Int_t isolationPersoNTracksSolidCone() const { return isolationPersoNTracksSolidCone_; }
   Int_t dR04IsolationNNiceTracks() const { return dR04IsolationNNiceTracks_; }
   
   
   //=======================================================
   // PFlow Variables
   //=======================================================
   
   Float_t pfChargedHadronIso() const { return pfChargedHadronIso_; }
   Float_t pfNeutralHadronIso() const { return pfNeutralHadronIso_; }
   Float_t pfPhotonIso() const { return pfPhotonIso_; }
   Float_t pfModFrixione() const { return pfModFrixione_; }
   
   Int_t pfNClusterOutsideMustache() const { return pfNClusterOutsideMustache_; }
   Float_t pfEtOutsideMustache() const { return pfEtOutsideMustache_; }
   Float_t pfMVA() const { return pfMVA_; }

   
   //=======================================================
   // Conversions - to be updated
   //=======================================================

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
   
   
   //=======================================================
   // Type
   //=======================================================
   
   Bool_t hasPixelSeed() const { return hasPixelSeed_; }
   Bool_t isPFlowPhoton() const { return isPFlowPhoton_; }
   Bool_t isStandardPhoton() const { return isStandardPhoton_; }
   Bool_t isAlsoElectron() const { return isAlsoElectron_; }
   
   TRootParticle* genPhoton() const { return genParticle(); }
   virtual TString typeName() const { return "TRootPhoton"; }

   
   
   //=======================================================
   // Cluster position
   //=======================================================
   void setCaloPosition(TVector3 caloPosition) { caloPosition_ = caloPosition; }
   void setCaloPosition(Double_t x, Double_t y, Double_t z) { caloPosition_.SetXYZ(x, y ,z); }


   //=======================================================
   // Supercluster infos
   //=======================================================
   void setNbClusters(Int_t nbClusters) { nbClusters_ = nbClusters; }
   void setSCRawEnergy(Float_t superClusterRawEnergy) { superClusterRawEnergy_ = superClusterRawEnergy; }
   void setSuperClusterRawEnergy(Float_t superClusterRawEnergy) { superClusterRawEnergy_ = superClusterRawEnergy; }
   void setPreshowerEnergy(Float_t preshowerEnergy) { preshowerEnergy_ = preshowerEnergy; }
   void setSCIndex(Int_t type, Int_t index) { scIndex_[type]=index; }
   void setSCRef(Int_t type, TObject* superCluster) { scRef_[type]=superCluster; }
   void setClusterAlgo(Int_t clusterAlgo) { clusterAlgo_ = clusterAlgo; }

   
   //=======================================================
   // Shower Shape Variables
   //=======================================================
   void setHcalDepth1OverEcal(Float_t hcalDepth1OverEcal) { hcalDepth1OverEcal_ = hcalDepth1OverEcal; }
   void setHcalDepth2OverEcal(Float_t hcalDepth2OverEcal) { hcalDepth2OverEcal_ = hcalDepth2OverEcal; }
   void setHcalDepth1OverEcalBC(Float_t hcalDepth1OverEcalBC) { hcalDepth1OverEcalBC_ = hcalDepth1OverEcalBC; }
   void setHcalDepth2OverEcalBC(Float_t hcalDepth2OverEcalBC) { hcalDepth2OverEcalBC_ = hcalDepth2OverEcalBC; }
   
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
   void setEtaLAT(Float_t etaLAT) { etaLAT_= etaLAT;}
   void setPhiLAT(Float_t phiLAT) { phiLAT_= phiLAT;}
   void setLAT(Float_t lat) { lat_= lat;}
   void setZernike20(Float_t zernike20) { zernike20_= zernike20;}
   void setZernike42(Float_t zernike42) { zernike42_= zernike42;}
   void setSecondMomentMaj(Float_t secondMomentMaj) { secondMomentMaj_= secondMomentMaj;}
   void setSecondMomentMin(Float_t secondMomentMin) { secondMomentMin_= secondMomentMin;}
   void setSecondMomentAlpha(Float_t secondMomentAlpha) { secondMomentAlpha_= secondMomentAlpha;}
   
   
   //=======================================================
   // Energy Determinations  (stored in reco::Photon)
   //=======================================================
   void set_energy_ecalStandard(Float_t energy, Float_t error, Float_t px, Float_t py, Float_t pz, Float_t e)
   {
      scEcalEnergy_ = energy;
      scEcalEnergyError_ = error;
      scEcalP4_.SetPxPyPzE(px,py,pz,e);
   }
   
   void set_energy_ecalPhoton(Float_t energy, Float_t error, Float_t px, Float_t py, Float_t pz, Float_t e)
   {
      phoEcalEnergy_ = energy;
      phoEcalEnergyError_ = error;
      phoEcalP4_.SetPxPyPzE(px,py,pz,e);
   }
   
   void set_energy_regression1(Float_t energy, Float_t error, Float_t px, Float_t py, Float_t pz, Float_t e)
   {
      regression1Energy_ = energy;
      regression1EnergyError_ = error;
      regression1P4_.SetPxPyPzE(px,py,pz,e);
   }
   
   void set_energy_regression2(Float_t energy, Float_t error, Float_t px, Float_t py, Float_t pz, Float_t e)
   {
      regression2Energy_ = energy;
      regression2EnergyError_ = error;
      regression2P4_.SetPxPyPzE(px,py,pz,e);
   }
   
   
   //=======================================================
   // Energy Regression  (calculated on the fly)
   //=======================================================
   
   void setJoshEnergyRegressionV3(Float_t joshEnergyRegressionV3) { joshEnergyRegressionV3_= joshEnergyRegressionV3;}
   void setJoshEnergyRegressionV3Error(Float_t joshEnergyRegressionV3Error) { joshEnergyRegressionV3Error_= joshEnergyRegressionV3Error;}
   void setJoshEnergyRegressionV4(Float_t joshEnergyRegressionV4) { joshEnergyRegressionV4_= joshEnergyRegressionV4;}
   void setJoshEnergyRegressionV4Error(Float_t joshEnergyRegressionV4Error) { joshEnergyRegressionV4Error_= joshEnergyRegressionV4Error;}
   void setJoshEnergyRegressionV5(Float_t joshEnergyRegressionV5) { joshEnergyRegressionV5_= joshEnergyRegressionV5;}
   void setJoshEnergyRegressionV5Error(Float_t joshEnergyRegressionV5Error) { joshEnergyRegressionV5Error_= joshEnergyRegressionV5Error;}
   void setJoshEnergyRegressionV8(Float_t joshEnergyRegressionV8) { joshEnergyRegressionV8_= joshEnergyRegressionV8;}
   void setJoshEnergyRegressionV8Error(Float_t joshEnergyRegressionV8Error) { joshEnergyRegressionV8Error_= joshEnergyRegressionV8Error;}
 
   
   //=======================================================
   // Fiducial flags  (stored in reco::Photon)
   //=======================================================
   void setFiducialFlags(Bool_t isEB, Bool_t isEE, Bool_t isEBEtaGap, Bool_t isEBPhiGap, Bool_t isEERingGap, Bool_t isEEDeeGap, Bool_t isEBEEGap)
   {
      isEB_ = isEB;
      isEE_ = isEE;
      isEBEtaGap_= isEBEtaGap;
      isEBPhiGap_ = isEBPhiGap;
      isEERingGap_ = isEERingGap;
      isEEDeeGap_ = isEEDeeGap;
      isEBEEGap_ = isEBEEGap;
   }
   
   
   //=======================================================
   // Isolation Variables
   //=======================================================
   
   // Set standard reco isolation
   void setDR03IsolationEcalRecHit(Float_t dR03IsolationEcalRecHit) { dR03IsolationEcalRecHit_ = dR03IsolationEcalRecHit; }
   void setDR03IsolationHcalRecHit(Float_t dR03IsolationHcalRecHit) { dR03IsolationHcalRecHit_ = dR03IsolationHcalRecHit; }
   void setDR03IsolationHcalDepth1RecHit(Float_t dR03IsolationHcalDepth1RecHit) { dR03IsolationHcalDepth1RecHit_ = dR03IsolationHcalDepth1RecHit; }
   void setDR03IsolationHcalDepth2RecHit(Float_t dR03IsolationHcalDepth2RecHit) { dR03IsolationHcalDepth2RecHit_ = dR03IsolationHcalDepth2RecHit; }
   void setDR03IsolationSolidTrkCone(Float_t dR03IsolationSolidTrkCone) { dR03IsolationSolidTrkCone_ = dR03IsolationSolidTrkCone; }
   void setDR03IsolationHollowTrkCone(Float_t dR03IsolationHollowTrkCone) { dR03IsolationHollowTrkCone_ = dR03IsolationHollowTrkCone; }
   void setDR03IsolationNTracksSolidCone(Int_t dR03IsolationNTracksSolidCone) { dR03IsolationNTracksSolidCone_ = dR03IsolationNTracksSolidCone; }
   void setDR03IsolationNTracksHollowCone(Int_t dR03IsolationNTracksHollowCone) { dR03IsolationNTracksHollowCone_ = dR03IsolationNTracksHollowCone; }
   void setDR03Isolation(Float_t dR03IsolationEcalRecHit, Float_t dR03IsolationHcalRecHit, Float_t dR03IsolationHcalDepth1RecHit, Float_t dR03IsolationHcalDepth2RecHit, Float_t dR03IsolationSolidTrkCone, Float_t dR03IsolationHollowTrkCone, Int_t dR03IsolationNTracksSolidCone, Int_t dR03IsolationNTracksHollowCone)
   {
      dR03IsolationEcalRecHit_ = dR03IsolationEcalRecHit;
      dR03IsolationHcalRecHit_ = dR03IsolationHcalRecHit;
      dR03IsolationHcalDepth1RecHit_ = dR03IsolationHcalDepth1RecHit;
      dR03IsolationHcalDepth2RecHit_ = dR03IsolationHcalDepth2RecHit;
      dR03IsolationSolidTrkCone_ = dR03IsolationSolidTrkCone;
      dR03IsolationHollowTrkCone_ = dR03IsolationHollowTrkCone;
      dR03IsolationNTracksSolidCone_ = dR03IsolationNTracksSolidCone;
      dR03IsolationNTracksHollowCone_ = dR03IsolationNTracksHollowCone;
   }
   
   void setDR04IsolationEcalRecHit(Float_t dR04IsolationEcalRecHit) { dR04IsolationEcalRecHit_ = dR04IsolationEcalRecHit; }
   void setDR04IsolationHcalRecHit(Float_t dR04IsolationHcalRecHit) { dR04IsolationHcalRecHit_ = dR04IsolationHcalRecHit; }
   void setDR04IsolationHcalDepth1RecHit(Float_t dR04IsolationHcalDepth1RecHit) { dR04IsolationHcalDepth1RecHit_ = dR04IsolationHcalDepth1RecHit; }
   void setDR04IsolationHcalDepth2RecHit(Float_t dR04IsolationHcalDepth2RecHit) { dR04IsolationHcalDepth2RecHit_ = dR04IsolationHcalDepth2RecHit; }
   void setDR04IsolationSolidTrkCone(Float_t dR04IsolationSolidTrkCone) { dR04IsolationSolidTrkCone_ = dR04IsolationSolidTrkCone; }
   void setDR04IsolationHollowTrkCone(Float_t dR04IsolationHollowTrkCone) { dR04IsolationHollowTrkCone_ = dR04IsolationHollowTrkCone; }
   void setDR04IsolationNTracksSolidCone(Int_t dR04IsolationNTracksSolidCone) { dR04IsolationNTracksSolidCone_ = dR04IsolationNTracksSolidCone; }
   void setDR04IsolationNTracksHollowCone(Int_t dR04IsolationNTracksHollowCone) { dR04IsolationNTracksHollowCone_ = dR04IsolationNTracksHollowCone; }
   void setDR04Isolation(Float_t dR04IsolationEcalRecHit, Float_t dR04IsolationHcalRecHit, Float_t dR04IsolationHcalDepth1RecHit, Float_t dR04IsolationHcalDepth2RecHit, Float_t dR04IsolationSolidTrkCone, Float_t dR04IsolationHollowTrkCone, Int_t dR04IsolationNTracksSolidCone, Int_t dR04IsolationNTracksHollowCone)
   {
      dR04IsolationEcalRecHit_ = dR04IsolationEcalRecHit;
      dR04IsolationHcalRecHit_ = dR04IsolationHcalRecHit;
      dR04IsolationHcalDepth1RecHit_ = dR04IsolationHcalDepth1RecHit;
      dR04IsolationHcalDepth2RecHit_ = dR04IsolationHcalDepth2RecHit;
      dR04IsolationSolidTrkCone_ = dR04IsolationSolidTrkCone;
      dR04IsolationHollowTrkCone_ = dR04IsolationHollowTrkCone;
      dR04IsolationNTracksSolidCone_ = dR04IsolationNTracksSolidCone;
      dR04IsolationNTracksHollowCone_ = dR04IsolationNTracksHollowCone;
   }
   
   
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
   void setDR04IsolationNNiceTracks(Int_t dR04IsolationNNiceTracks) { dR04IsolationNNiceTracks_ = dR04IsolationNNiceTracks;}
   
   
   //=======================================================
   // PFlow Variables
   //=======================================================
   
   void setPFiso(Float_t pfChargedHadronIso, Float_t pfNeutralHadronIso, Float_t pfPhotonIso, Float_t pfModFrixione)
   {
      pfChargedHadronIso_ = pfChargedHadronIso;
      pfNeutralHadronIso_ = pfNeutralHadronIso;
      pfPhotonIso_ = pfPhotonIso;
      pfModFrixione_ = pfModFrixione;
   }
   
   void setPFid(Int_t pfNClusterOutsideMustache, Float_t pfEtOutsideMustache, Float_t pfMVA)
   {
      pfNClusterOutsideMustache_ = pfNClusterOutsideMustache;
      pfEtOutsideMustache_ = pfEtOutsideMustache;
      pfMVA_ = pfMVA;
   }
   
   
   
   //=======================================================
   // Conversions - to be updated
   //=======================================================
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
   
   
   //=======================================================
   // Type
   //=======================================================
   void setHasPixelSeed(Bool_t hasPixelSeed) { hasPixelSeed_ = hasPixelSeed; }
   void setIsPFlowPhoton(Bool_t isPFlowPhoton) { isPFlowPhoton_ = isPFlowPhoton; }
   void sertIsStandardPhoton(Bool_t isStandardPhoton) { isStandardPhoton_ = isStandardPhoton; }
   void setIsAlsoElectron(Bool_t isAlsoElectron) { isAlsoElectron_ = isAlsoElectron; }
   

   
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
      <<"  R9=" << photon.r9() <<"  hoe=" << photon.hoe() <<"  nTracksConv=" << photon.convNTracks();
      return stream;
   };
   
   void Print()
   {
      std::cout << "TRootPhoton  (E,Et,eta,phi)=("<< this->Energy() <<","<< this->Et() <<","<< this->Eta() <<","<< this->Phi() << ")"
      << "  vertex=("<< this->vx() <<","<< this->vy() <<","<< this->vz() << ")"
      << "  caloPosition=(" << this->caloPosition().X() << "," << this->caloPosition().Y() << "," << this->caloPosition().Z() << ")" << endl
      << "            'ecal_standard' energy=" << this->energy_ecalStandard() << " +- " << this->energyError_ecalStandard() <<" (E,Et,eta,phi)=("<< this->p4_ecalStandard().Energy() <<","<< this->p4_ecalStandard().Et() <<","<< this->p4_ecalStandard().Eta() <<","<< this->p4_ecalStandard().Phi() << ")" << endl
      << "            'ecal_photons'  energy=" << this->energy_ecalPhoton() << " +- " << this->energyError_ecalPhoton() <<" (E,Et,eta,phi)=("<< this->p4_ecalPhoton().Energy() <<","<< this->p4_ecalPhoton().Et() <<","<< this->p4_ecalPhoton().Eta() <<","<< this->p4_ecalPhoton().Phi() << ")" << endl
      << "            'regression1'   energy=" << this->energy_regression1() << " +- " << this->energyError_regression1() <<" (E,Et,eta,phi)=("<< this->p4_regression1().Energy() <<","<< this->p4_regression1().Et() <<","<< this->p4_regression1().Eta() <<","<< this->p4_regression1().Phi() << ")" << endl
      << "            'regression2'   energy=" << this->energy_regression2() << " +- " << this->energyError_regression2() <<" (E,Et,eta,phi)=("<< this->p4_regression2().Energy() <<","<< this->p4_regression2().Et() <<","<< this->p4_regression2().Eta() <<","<< this->p4_regression2().Phi() << ")" << endl
      << "            'Josh reg V3'   energy=" << this->joshEnergyRegressionV3() << " +- " << this->joshEnergyRegressionV3Error() << endl
      << "            'Josh reg V4'   energy=" << this->joshEnergyRegressionV4() << " +- " << this->joshEnergyRegressionV4Error() << endl
      << "            'Josh reg V5'   energy=" << this->joshEnergyRegressionV5() << " +- " << this->joshEnergyRegressionV5Error() << endl
      << "            'Josh reg V8'   energy=" << this->joshEnergyRegressionV8() << " +- " << this->joshEnergyRegressionV8Error() << endl
      << "            algo=" << this->clusterAlgo() << "  nBC=" << this->nbClusters() << " scRawEnergy=" << this->scRawEnergy() << " preshEnergy=" << this->preshowerEnergy() << endl
      << "            hadronicOverEm=" << this->hadronicOverEm() << " hadTowOverm=" << this->hadTowOverEm()  << " E2x2=" << this->e2x2() <<" E3x3=" << this->e3x3() <<" E5x5=" << this->e5x5() <<" Emax=" << this->eMax()
      << " E2nd=" << this->e2nd() <<" R19=" << this->r19() <<" R9=" << this->r9() << endl
      << "            sigmaEtaEta=" << this->sigmaEtaEta() <<" sigmaIetaIeta=" << this->sigmaIetaIeta()
      << " cEtaEta=" << this->covEtaEta() <<" cEtaPhi=" << this->covEtaPhi() <<" cPhiPhi=" << this->covPhiPhi() << endl
      << "            etaLAT=" << this->etaLAT() <<" phiLAT=" << this->phiLAT() <<" LAT=" << this->lat() <<" zernike20=" << this->zernike20() <<" zernike42=" << this->zernike42() << endl
      << "            2nd MomentMaj=" << this->secondMomentMaj() <<" 2nd MomentMin=" << this->secondMomentMin() <<" 2nd Moment alpha=" << this->secondMomentAlpha() << endl
      << "            isoPerso  BC="<< this->isolationPersoBasicClusters() << " DoubleConeBC=" << this->isolationPersoBasicClustersDoubleCone()
      << " hcal=" << this->isolationPersoHcalRecHit() << " track=" << this->isolationPersoTracksSolidCone() << " ntracks=" << this->isolationPersoNTracksSolidCone()  << " nNiceTracks=" << this->dR04IsolationNNiceTracks() << endl
      << "            dR03 isoPhotonID  ecal="<< this->dR03IsolationEcalRecHit() << " hcal=" << this->dR03IsolationHcalRecHit() << " track-hollow=" << this->dR03IsolationHollowTrkCone()
      << " ntracks-hollow=" << this->dR03IsolationNTracksHollowCone() << " track-solid=" << this->dR03IsolationSolidTrkCone() << " ntracks-solid=" << this->dR03IsolationNTracksSolidCone() << endl
      << "            dR04 isoPhotonID  ecal="<< this->dR04IsolationEcalRecHit() << " hcal=" << this->dR04IsolationHcalRecHit() << " track-hollow=" << this->dR04IsolationHollowTrkCone()
      << " ntracks-hollow=" << this->dR04IsolationNTracksHollowCone() << " track-solid=" << this->dR04IsolationSolidTrkCone() << " ntracks-solid=" << this->dR04IsolationNTracksSolidCone() << endl
      << "            isEB=" << this->isEB() << " isEE=" << this->isEE()  << " isEBGap=" << this->isEBGap() << " isEBEtaGap=" << this->isEBEtaGap() << " isEBPhiGap=" << this->isEBPhiGap()  
      << " isEEGap=" << this->isEEGap() << " isEERingGap=" << this->isEERingGap() << " isEEDeeGap=" << this->isEEDeeGap() << " isEBEEGap=" << this->isEBEEGap() << endl
      << "            hasPxlSeed=" << this-> hasPixelSeed() << " isPFlowPhoton=" << this->isPFlowPhoton() << " isStandardPhoton=" << this->isStandardPhoton() << " isAlsoElectron=" << this->isAlsoElectron() << endl
      << "            pfChargedHadronIso=" << this->pfChargedHadronIso()  << " pfNeutralHadronIso=" << this->pfNeutralHadronIso() << " pfPhotonIso=" << this->pfPhotonIso() << " pfModFrixione=" << this->pfModFrixione() << endl
      << "            pfNClusterOutsideMustache=" << this->pfNClusterOutsideMustache()  << " pfEtOutsideMustache=" << this->pfEtOutsideMustache() << " pfMVA=" << this->pfMVA() << endl
      << "            nTracksConv=" << this->convNTracks();
      
      if (this->convNTracks()>1)
         std::cout << endl << "            Conversion: E/p=" << this->convEoverP() << " Mass=" << this->convMass() << " cotan(Theta)=" << this->convCotanTheta() << " Likely=" << this->convLikely()
         << " (vx,vy,vz)=(" << this->convVertex().X() << ","<< this->convVertex().Y() << ","<< this->convVertex().Z() << ")";
   };
   
   
private:

   
   //=======================================================
   // Cluster position
   //=======================================================
   TVector3 caloPosition_;         // SC position if r9<0.93,  position of seed BasicCluster (taking shower depth for unconverted photon) if r9>0.93
   
   
   //=======================================================
   // Supercluster infos
   //=======================================================
   
   // (need reco::SuperCluster)
   Int_t nbClusters_;              // Number of basic clusters components
   Float_t superClusterRawEnergy_; // SuperCluster raw energy
   Float_t preshowerEnergy_;       // Endcap preshower energy
   map<Int_t,Int_t> scIndex_;      // indexes of the seed SuperClusters (one per SC tytpe)
   map<Int_t,TRef> scRef_;         // references to the seed SuperClusters (one per SC tytpe)
   
   // (need reco::SuperCluster and reco::BasicCluster)
   Int_t clusterAlgo_;             // reco::BasicCluster::algo() island = 0, hybrid = 1, fixedMatrix = 2, dynamicHybrid = 3, multi5x5 = 4
   
   
   
   //=======================================================
   // Shower Shape Variables
   //=======================================================
   
   // (stored in reco::Photon)
   Float_t hcalDepth1OverEcal_;    // hcal over ecal energy using first hcal depth
   Float_t hcalDepth2OverEcal_;    // hcal over ecal energy using 2nd hcal depth
   Float_t hcalDepth1OverEcalBC_;   // ratio of hadronic energy in towers depth1 behind the BCs in the SC  and the SC energy 
   Float_t hcalDepth2OverEcalBC_;   // ratio of hadronic energy in towers depth2 behind the BCs in the SC  and the SC energy 
   Float_t sigmaEtaEta_;           // sqrt(covariance(Eta,Eta)) taken from reco::Photon::ShowerShape struct
   Float_t sigmaIetaIeta_;         // sqrt(covariance(iEta,iEta)) taken from reco::Photon::ShowerShape struct
   
   // Calculated by EcalClusterLazyTools 
   // need reco::SuperCluster and reco::BasicCluster and reduced Ecal RecHits Collections
   Float_t e2x2_;                  // 2x2 energy
   Float_t e3x3_;                  // 3x3 energy
   Float_t e5x5_;                  // 5x5 energy
   Float_t eMax_;                  // energy of crystal with max energy
   Float_t e2nd_;                  // energy of crystal with 2nd max energy
   Float_t covEtaEta_;             // Covariance (Eta,Eta) of xtals composing the photon seed BasicCluster (weighted by their energy) calculated by lazytools
   Float_t covEtaPhi_;             // Covariance (Eta,Phi) of xtals composing the photon seed BasicCluster (weighted by their energy) calculated by lazytools
   Float_t covPhiPhi_;             // Covariance (Phi,Phi) of xtals composing the photon seed BasicCluster (weighted by their energy) calculated by lazytools
   Float_t etaLAT_ ;               // lateral moment in Eta
   Float_t phiLAT_ ;               // lateral moment in Phi
   Float_t lat_ ;                  // lateral moment
   Float_t zernike20_ ;            // zernike moment
   Float_t zernike42_ ;            // zernike moment
   Float_t secondMomentMaj_ ;      // cluster second moments with respect to principal axes - Major
   Float_t secondMomentMin_ ;      // cluster second moments with respect to principal axes - Minor
   Float_t secondMomentAlpha_ ;    // angle between Maj and phi:
   
   

   //=======================================================
   // Energy Determinations  (stored in reco::Photon)
   //=======================================================

   Float_t scEcalEnergy_;
   Float_t scEcalEnergyError_;
   TLorentzVector scEcalP4_;
   Float_t phoEcalEnergy_;
   Float_t phoEcalEnergyError_;
   TLorentzVector phoEcalP4_;
   Float_t regression1Energy_;
   Float_t regression1EnergyError_;
   TLorentzVector regression1P4_;
   Float_t regression2Energy_;
   Float_t regression2EnergyError_;
   TLorentzVector regression2P4_;
   
   
   //=======================================================
   // Energy Regression  (calculated on the fly)
   // https://twiki.cern.ch/twiki/bin/view/CMS/RegressionSCCorrections
   //=======================================================
   
   Float_t joshEnergyRegressionV3_;
   Float_t joshEnergyRegressionV3Error_;
   Float_t joshEnergyRegressionV4_;
   Float_t joshEnergyRegressionV4Error_;
   Float_t joshEnergyRegressionV5_;
   Float_t joshEnergyRegressionV5Error_;
   Float_t joshEnergyRegressionV8_;
   Float_t joshEnergyRegressionV8Error_; 
   
   //=======================================================
   // Fiducial flags  (stored in reco::Photon)
   //=======================================================

   Bool_t isEB_;        // Photon is in EB
   Bool_t isEE_;        // Photon is in EE
   Bool_t isEBEtaGap_;  // Photon is in supermodule/supercrystal eta gap in EB
   Bool_t isEBPhiGap_;  // Photon is in supermodule/supercrystal phi gap in EB
   Bool_t isEERingGap_; // Photon is in crystal ring gap in EE
   Bool_t isEEDeeGap_;  // Photon is in crystal dee gap in EE
   Bool_t isEBEEGap_;   // Photon is in border between EB and EE.
   
   
   //=======================================================
   // Isolation Variables
   //=======================================================
   
   // standard reco isolation (stored in reco::Photon)
   Float_t dR03IsolationEcalRecHit_;       // Jurassic isolation (Sum of ecal rechits in DRmin < DR < DRmax around the photon, excluding an eta slice)
   Float_t dR03IsolationHcalRecHit_;       // Sum of HCAL rechits in DRmin < DR < DRmax around the photon
   Float_t dR03IsolationHcalDepth1RecHit_; // Sum of HCAL rechits in depth1 in DRmin < DR < DRmax around the photon
   Float_t dR03IsolationHcalDepth2RecHit_; // Sum of HCAL rechits in depth2 in DRmin < DR < DRmax around the photon
   Float_t dR03IsolationSolidTrkCone_;     // Pt sum of tracks in a cone around the photon
   Float_t dR03IsolationHollowTrkCone_;    // Pt sum of tracks in DRmin < DR < DRmax around the photon
   Int_t dR03IsolationNTracksSolidCone_;   // Tracks multiplicity in a cone around the photon
   Int_t dR03IsolationNTracksHollowCone_;  // Tracks multiplicity in DRmin < DR < DRmax around the photon
   
   Float_t dR04IsolationEcalRecHit_;       // Jurassic isolation (Sum of ecal rechits in DRmin < DR < DRmax around the photon, excluding an eta slice)
   Float_t dR04IsolationHcalRecHit_;       // Sum of HCAL rechits in DRmin < DR < DRmax around the photon
   Float_t dR04IsolationHcalDepth1RecHit_; // Sum of HCAL rechits in depth1 in DRmin < DR < DRmax around the photon
   Float_t dR04IsolationHcalDepth2RecHit_; // Sum of HCAL rechits in depth2 in DRmin < DR < DRmax around the photon
   Float_t dR04IsolationSolidTrkCone_;     // Pt sum of tracks in a cone around the photon
   Float_t dR04IsolationHollowTrkCone_;    // Pt sum of tracks in DRmin < DR < DRmax around the photon
   Int_t dR04IsolationNTracksSolidCone_;   // Tracks multiplicity in a cone around the photon
   Int_t dR04IsolationNTracksHollowCone_;  // Tracks multiplicity in DRmin < DR < DRmax around the photon

   // Isolation Variables calculated by PhotonIsolator
   Float_t isolationPersoBasicClusters_;           // Et sum of BCs in a cone around the photon - sub BasicClusters of photon SuperCluster are excluded.
   Float_t isolationPersoBasicClustersDoubleCone_; // Et sum of BCs in DRmin < DR < DRmax around photon
   Float_t isolationPersoHcalRecHit_;              // Et sum of HCAL rechits in a cone around the photon
   Float_t isolationPersoTracksSolidCone_;         // Pt sum of tracks in a cone around the photon
   Int_t isolationPersoNTracksSolidCone_;          // Tracks multiplicity in a cone around the photon
   Int_t dR04IsolationNNiceTracks_;                // Nb of NiceTrack in the cone
   

   //=======================================================
   // PFlow Variables
   //=======================================================
   
   // PFlow based Isolation Variables (stored in reco::Photon)
   Float_t pfChargedHadronIso_;
   Float_t pfNeutralHadronIso_;
   Float_t pfPhotonIso_;
   Float_t pfModFrixione_;      
   
   // PFlow based photon ID (stored in reco::Photon)
   Int_t pfNClusterOutsideMustache_;
   Float_t pfEtOutsideMustache_;
   Float_t pfMVA_;
   
 
   //=======================================================
   // Conversions - to be updated
   //=======================================================
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
   
   
   
   //=======================================================
   // Type
   //=======================================================
   
   Bool_t hasPixelSeed_;      // has the SuperCluster a matched pixel seed ?
   Bool_t isPFlowPhoton_;     // is it a PF photon ?
   Bool_t isStandardPhoton_;  // is it a standard reco photon ?
   Bool_t isAlsoElectron_;    // is photon also a GsfElectron ?
   
   ClassDef (TRootPhoton,16);
   
};

#endif
