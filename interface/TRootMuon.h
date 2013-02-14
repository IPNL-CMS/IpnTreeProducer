#ifndef TRootMuon_h
#define TRootMuon_h

#include "../interface/TRootParticle.h"

using namespace std;

class TRootMuon : public TRootParticle
{
   
public:
   
   TRootMuon() :
   TRootParticle()
   ,isGlobalMuon_(false)
   ,isTrackerMuon_(false)
   ,isStandAloneMuon_(false)
   ,isCaloMuon_(false)
   ,isPFMuon_(false)
   ,isRPCMuon_(false)
   ,isEnergyValid_(false)
   ,isIsolationValid_(false)
   ,isPfIsolationValid_(false)
   ,isQualityValid_(false)
   ,id_(-9999)
   ,numberOfChambers_(-1)
   ,numberOfMatches_(-1)
   ,numberOfMatchedStations_(-1)
   ,timeDirection_(-9999)
   ,et_em_(-9999.)
   ,et_emS9_(-9999.)
   ,et_emS25_(-9999.)
   ,et_emMax_(-9999.)
   ,et_had_(-9999.)
   ,et_hadS9_(-9999.)
   ,et_hadMax_(-9999.)
   ,et_ho_(-9999.)
   ,et_hoS9_(-9999.)
   ,caloCompatibility_(-9999.)
   ,pfIsoChargedHadronPt04_(-9999.)
   ,pfIsoChargedParticlePt04_(-9999.)
   ,pfIsoNeutralHadronEt04_(-9999.)
   ,pfIsoPhotonEt04_(-9999.)
   ,pfIsoNeutralHadronEtHighThreshold04_(-9999.)
   ,pfIsoPhotonEtHighThreshold04_(-9999.)
   ,pfIsoPUPt04_(-9999.)
   ,isoR03_emEt_(-9999.)
   ,isoR03_hadEt_(-9999.)
   ,isoR03_hoEt_(-9999.)
   ,isoR03_sumPt_(-9999.)
   ,isoR03_nTracks_(-9999)
   ,isoR03_nJets_(-9999)
   ,isoR05_emEt_(-9999.)
   ,isoR05_hadEt_(-9999.)
   ,isoR05_hoEt_(-9999.)
   ,isoR05_sumPt_(-9999.)
   ,isoR05_nTracks_(-9999)
   ,isoR05_nJets_(-9999)
   ,numberOfValidPixelHitsInInnerTrack_(-1)
   ,numberOfValidTrackerHitsInInnerTrack_(-1)
   ,numberOfValidMuonHitsInGlobalTrack_(-1)
   ,pixelLayersWithMeasurementInInnerTrack_(-1)
   ,stripLayersWithMeasurementInInnerTrack_(-1)
   ,normalizedChi2InnerTrack_(-9999.)
   ,normalizedChi2GlobalTrack_(-9999.)
   ,innerTrackDxy_(-9999.)
   ,innerTrackDz_(-9999.)
   ,bestTrackDxy_(-9999.)
   ,bestTrackDz_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,innerTrack_(0.,0.,0.,0.)
   ,outerTrack_(0.,0.,0.,0.)
   ,globalTrack_(0.,0.,0.,0.)
   ,pfTrack_(0.,0.,0.,0.)
   ,ptErrorInnerTrack_(-9999.)
   ,etaErrorInnerTrack_(-9999.)
   ,phiErrorInnerTrack_(-9999.)
   {;}
   
   TRootMuon(const TRootMuon& muon) :
   TRootParticle(muon)
   ,isGlobalMuon_(muon.isGlobalMuon_)
   ,isTrackerMuon_(muon.isTrackerMuon_)
   ,isStandAloneMuon_(muon.isStandAloneMuon_)
   ,isCaloMuon_(muon.isCaloMuon_)
   ,isPFMuon_(muon.isPFMuon_)
   ,isRPCMuon_(muon.isRPCMuon_)
   ,isEnergyValid_(muon.isEnergyValid_)
   ,isIsolationValid_(muon.isIsolationValid_)
   ,isPfIsolationValid_(muon.isPfIsolationValid_)
   ,isQualityValid_(muon.isQualityValid_)
   ,id_(muon.id_)
   ,numberOfChambers_(muon.numberOfChambers_)
   ,numberOfMatches_(muon.numberOfMatches_)
   ,numberOfMatchedStations_(muon.numberOfMatchedStations_)
   ,timeDirection_(muon.timeDirection_)
   ,et_em_(muon.et_em_)
   ,et_emS9_(muon.et_emS9_)
   ,et_emS25_(muon.et_emS25_)
   ,et_emMax_(muon.et_emMax_)
   ,et_had_(muon.et_had_)
   ,et_hadS9_(muon.et_hadS9_)
   ,et_hadMax_(muon.et_hadMax_)
   ,et_ho_(muon.et_ho_)
   ,et_hoS9_(muon.et_hoS9_)
   ,caloCompatibility_(muon.caloCompatibility_)
   ,pfIsoChargedHadronPt04_(muon.pfIsoChargedHadronPt04_)
   ,pfIsoChargedParticlePt04_(muon.pfIsoChargedParticlePt04_)
   ,pfIsoNeutralHadronEt04_(muon.pfIsoNeutralHadronEt04_)
   ,pfIsoPhotonEt04_(muon.pfIsoPhotonEt04_)
   ,pfIsoNeutralHadronEtHighThreshold04_(muon.pfIsoNeutralHadronEtHighThreshold04_)
   ,pfIsoPhotonEtHighThreshold04_(muon.pfIsoPhotonEtHighThreshold04_)
   ,pfIsoPUPt04_(muon.pfIsoPUPt04_)
   ,isoR03_emEt_(muon.isoR03_emEt_)
   ,isoR03_hadEt_(muon.isoR03_hadEt_)
   ,isoR03_hoEt_(muon.isoR03_hoEt_)
   ,isoR03_sumPt_(muon.isoR03_sumPt_)
   ,isoR03_nTracks_(muon.isoR03_nTracks_)
   ,isoR03_nJets_(muon.isoR03_nJets_)
   ,isoR05_emEt_(muon.isoR05_emEt_)
   ,isoR05_hadEt_(muon.isoR05_hadEt_)
   ,isoR05_hoEt_(muon.isoR05_hoEt_)
   ,isoR05_sumPt_(muon.isoR05_sumPt_)
   ,isoR05_nTracks_(muon.isoR05_nTracks_)
   ,isoR05_nJets_(muon.isoR05_nJets_)
   ,numberOfValidPixelHitsInInnerTrack_(muon.numberOfValidPixelHitsInInnerTrack_)
   ,numberOfValidTrackerHitsInInnerTrack_(muon.numberOfValidTrackerHitsInInnerTrack_)
   ,numberOfValidMuonHitsInGlobalTrack_(muon.numberOfValidMuonHitsInGlobalTrack_)
   ,pixelLayersWithMeasurementInInnerTrack_(muon.pixelLayersWithMeasurementInInnerTrack_)
   ,stripLayersWithMeasurementInInnerTrack_(muon.stripLayersWithMeasurementInInnerTrack_)   
   ,normalizedChi2InnerTrack_(muon.normalizedChi2InnerTrack_)
   ,normalizedChi2GlobalTrack_(muon.normalizedChi2GlobalTrack_)
   ,innerTrackDxy_(muon.innerTrackDxy_)
   ,innerTrackDz_(muon.innerTrackDz_)
   ,bestTrackDxy_(muon.bestTrackDxy_)
   ,bestTrackDz_(muon.bestTrackDz_)
   ,ip3DSignificance_(muon.ip3DSignificance_)
   ,innerTrack_(muon.innerTrack_)
   ,outerTrack_(muon.outerTrack_)
   ,globalTrack_(muon.globalTrack_)
   ,pfTrack_(muon.pfTrack_)
   ,ptErrorInnerTrack_(muon.ptErrorInnerTrack_)
   ,etaErrorInnerTrack_(muon.etaErrorInnerTrack_)
   ,phiErrorInnerTrack_(muon.phiErrorInnerTrack_)
   {;}
   
   TRootMuon(Double_t px, Double_t py, Double_t pz, Double_t e) :
   TRootParticle(px,py,pz,e)
   ,isGlobalMuon_(false)
   ,isTrackerMuon_(false)
   ,isStandAloneMuon_(false)
   ,isCaloMuon_(false)
   ,isPFMuon_(false)
   ,isRPCMuon_(false)
   ,isEnergyValid_(false)
   ,isIsolationValid_(false)
   ,isPfIsolationValid_(false)
   ,isQualityValid_(false)
   ,id_(-9999)
   ,numberOfChambers_(-1)
   ,numberOfMatches_(-1)
   ,numberOfMatchedStations_(-1)
   ,timeDirection_(-9999)
   ,et_em_(-9999.)
   ,et_emS9_(-9999.)
   ,et_emS25_(-9999.)
   ,et_emMax_(-9999.)
   ,et_had_(-9999.)
   ,et_hadS9_(-9999.)
   ,et_hadMax_(-9999.)
   ,et_ho_(-9999.)
   ,et_hoS9_(-9999.)
   ,caloCompatibility_(-9999.)
   ,pfIsoChargedHadronPt04_(-9999.)
   ,pfIsoChargedParticlePt04_(-9999.)
   ,pfIsoNeutralHadronEt04_(-9999.)
   ,pfIsoPhotonEt04_(-9999.)
   ,pfIsoNeutralHadronEtHighThreshold04_(-9999.)
   ,pfIsoPhotonEtHighThreshold04_(-9999.)
   ,pfIsoPUPt04_(-9999.)
   ,isoR03_emEt_(-9999.)
   ,isoR03_hadEt_(-9999.)
   ,isoR03_hoEt_(-9999.)
   ,isoR03_sumPt_(-9999.)
   ,isoR03_nTracks_(-9999)
   ,isoR03_nJets_(-9999)
   ,isoR05_emEt_(-9999.)
   ,isoR05_hadEt_(-9999.)
   ,isoR05_hoEt_(-9999.)
   ,isoR05_sumPt_(-9999.)
   ,isoR05_nTracks_(-9999)
   ,isoR05_nJets_(-9999)
   ,numberOfValidPixelHitsInInnerTrack_(-1)
   ,numberOfValidTrackerHitsInInnerTrack_(-1)
   ,numberOfValidMuonHitsInGlobalTrack_(-1)
   ,pixelLayersWithMeasurementInInnerTrack_(-1)
   ,stripLayersWithMeasurementInInnerTrack_(-1)
   ,normalizedChi2InnerTrack_(-9999.)
   ,normalizedChi2GlobalTrack_(-9999.)
   ,innerTrackDxy_(-9999.)
   ,innerTrackDz_(-9999.)
   ,bestTrackDxy_(-9999.)
   ,bestTrackDz_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,innerTrack_(0.,0.,0.,0.)
   ,outerTrack_(0.,0.,0.,0.)
   ,globalTrack_(0.,0.,0.,0.)
   ,pfTrack_(0.,0.,0.,0.)
   ,ptErrorInnerTrack_(-9999.)
   ,etaErrorInnerTrack_(-9999.)
   ,phiErrorInnerTrack_(-9999.)
   {;}
   
   TRootMuon(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
   ,isGlobalMuon_(false)
   ,isTrackerMuon_(false)
   ,isStandAloneMuon_(false)
   ,isCaloMuon_(false)
   ,isPFMuon_(false)
   ,isRPCMuon_(false)
   ,isEnergyValid_(false)
   ,isIsolationValid_(false)
   ,isPfIsolationValid_(false)
   ,isQualityValid_(false)
   ,id_(-9999)
   ,numberOfChambers_(-1)
   ,numberOfMatches_(-1)
   ,numberOfMatchedStations_(-1)
   ,timeDirection_(-9999)
   ,et_em_(-9999.)
   ,et_emS9_(-9999.)
   ,et_emS25_(-9999.)
   ,et_emMax_(-9999.)
   ,et_had_(-9999.)
   ,et_hadS9_(-9999.)
   ,et_hadMax_(-9999.)
   ,et_ho_(-9999.)
   ,et_hoS9_(-9999.)
   ,caloCompatibility_(-9999.)
   ,pfIsoChargedHadronPt04_(-9999.)
   ,pfIsoChargedParticlePt04_(-9999.)
   ,pfIsoNeutralHadronEt04_(-9999.)
   ,pfIsoPhotonEt04_(-9999.)
   ,pfIsoNeutralHadronEtHighThreshold04_(-9999.)
   ,pfIsoPhotonEtHighThreshold04_(-9999.)
   ,pfIsoPUPt04_(-9999.)
   ,isoR03_emEt_(-9999.)
   ,isoR03_hadEt_(-9999.)
   ,isoR03_hoEt_(-9999.)
   ,isoR03_sumPt_(-9999.)
   ,isoR03_nTracks_(-9999)
   ,isoR03_nJets_(-9999)
   ,isoR05_emEt_(-9999.)
   ,isoR05_hadEt_(-9999.)
   ,isoR05_hoEt_(-9999.)
   ,isoR05_sumPt_(-9999.)
   ,isoR05_nTracks_(-9999)
   ,isoR05_nJets_(-9999)
   ,numberOfValidPixelHitsInInnerTrack_(-1)
   ,numberOfValidTrackerHitsInInnerTrack_(-1)
   ,numberOfValidMuonHitsInGlobalTrack_(-1)
   ,pixelLayersWithMeasurementInInnerTrack_(-1)
   ,stripLayersWithMeasurementInInnerTrack_(-1)
   ,normalizedChi2InnerTrack_(-9999.)
   ,normalizedChi2GlobalTrack_(-9999.)
   ,innerTrackDxy_(-9999.)
   ,innerTrackDz_(-9999.)
   ,bestTrackDxy_(-9999.)
   ,bestTrackDz_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,innerTrack_(0.,0.,0.,0.)
   ,outerTrack_(0.,0.,0.,0.)
   ,globalTrack_(0.,0.,0.,0.)
   ,pfTrack_(0.,0.,0.,0.)
   ,ptErrorInnerTrack_(-9999.)
   ,etaErrorInnerTrack_(-9999.)
   ,phiErrorInnerTrack_(-9999.)
   {;}
   
   TRootMuon(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
   ,isGlobalMuon_(false)
   ,isTrackerMuon_(false)
   ,isStandAloneMuon_(false)
   ,isCaloMuon_(false)
   ,isPFMuon_(false)
   ,isRPCMuon_(false)
   ,isEnergyValid_(false)
   ,isIsolationValid_(false)
   ,isPfIsolationValid_(false)
   ,isQualityValid_(false)
   ,id_(-9999)
   ,numberOfChambers_(-1)
   ,numberOfMatches_(-1)
   ,numberOfMatchedStations_(-1)
   ,timeDirection_(-9999)
   ,et_em_(-9999.)
   ,et_emS9_(-9999.)
   ,et_emS25_(-9999.)
   ,et_emMax_(-9999.)
   ,et_had_(-9999.)
   ,et_hadS9_(-9999.)
   ,et_hadMax_(-9999.)
   ,et_ho_(-9999.)
   ,et_hoS9_(-9999.)
   ,caloCompatibility_(-9999.)
   ,pfIsoChargedHadronPt04_(-9999.)
   ,pfIsoChargedParticlePt04_(-9999.)
   ,pfIsoNeutralHadronEt04_(-9999.)
   ,pfIsoPhotonEt04_(-9999.)
   ,pfIsoNeutralHadronEtHighThreshold04_(-9999.)
   ,pfIsoPhotonEtHighThreshold04_(-9999.)
   ,pfIsoPUPt04_(-9999.)
   ,isoR03_emEt_(-9999.)
   ,isoR03_hadEt_(-9999.)
   ,isoR03_hoEt_(-9999.)
   ,isoR03_sumPt_(-9999.)
   ,isoR03_nTracks_(-9999)
   ,isoR03_nJets_(-9999)
   ,isoR05_emEt_(-9999.)
   ,isoR05_hadEt_(-9999.)
   ,isoR05_hoEt_(-9999.)
   ,isoR05_sumPt_(-9999.)
   ,isoR05_nTracks_(-9999)
   ,isoR05_nJets_(-9999)
   ,numberOfValidPixelHitsInInnerTrack_(-1)
   ,numberOfValidTrackerHitsInInnerTrack_(-1)
   ,numberOfValidMuonHitsInGlobalTrack_(-1)
   ,pixelLayersWithMeasurementInInnerTrack_(-1)
   ,stripLayersWithMeasurementInInnerTrack_(-1)
   ,normalizedChi2InnerTrack_(-9999.)
   ,normalizedChi2GlobalTrack_(-9999.)
   ,innerTrackDxy_(-9999.)
   ,innerTrackDz_(-9999.)
   ,bestTrackDxy_(-9999.)
   ,bestTrackDz_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,innerTrack_(0.,0.,0.,0.)
   ,outerTrack_(0.,0.,0.,0.)
   ,globalTrack_(0.,0.,0.,0.)
   ,pfTrack_(0.,0.,0.,0.)
   ,ptErrorInnerTrack_(-9999.)
   ,etaErrorInnerTrack_(-9999.)
   ,phiErrorInnerTrack_(-9999.)
   {;}
   
   TRootMuon(const TLorentzVector &momentum) :
   TRootParticle(momentum)
   ,isGlobalMuon_(false)
   ,isTrackerMuon_(false)
   ,isStandAloneMuon_(false)
   ,isCaloMuon_(false)
   ,isPFMuon_(false)
   ,isRPCMuon_(false)
   ,isEnergyValid_(false)
   ,isIsolationValid_(false)
   ,isPfIsolationValid_(false)
   ,isQualityValid_(false)
   ,id_(-9999)
   ,numberOfChambers_(-1)
   ,numberOfMatches_(-1)
   ,numberOfMatchedStations_(-1)
   ,timeDirection_(-9999)
   ,et_em_(-9999.)
   ,et_emS9_(-9999.)
   ,et_emS25_(-9999.)
   ,et_emMax_(-9999.)
   ,et_had_(-9999.)
   ,et_hadS9_(-9999.)
   ,et_hadMax_(-9999.)
   ,et_ho_(-9999.)
   ,et_hoS9_(-9999.)
   ,caloCompatibility_(-9999.)
   ,pfIsoChargedHadronPt04_(-9999.)
   ,pfIsoChargedParticlePt04_(-9999.)
   ,pfIsoNeutralHadronEt04_(-9999.)
   ,pfIsoPhotonEt04_(-9999.)
   ,pfIsoNeutralHadronEtHighThreshold04_(-9999.)
   ,pfIsoPhotonEtHighThreshold04_(-9999.)
   ,pfIsoPUPt04_(-9999.)
   ,isoR03_emEt_(-9999.)
   ,isoR03_hadEt_(-9999.)
   ,isoR03_hoEt_(-9999.)
   ,isoR03_sumPt_(-9999.)
   ,isoR03_nTracks_(-9999)
   ,isoR03_nJets_(-9999)
   ,isoR05_emEt_(-9999.)
   ,isoR05_hadEt_(-9999.)
   ,isoR05_hoEt_(-9999.)
   ,isoR05_sumPt_(-9999.)
   ,isoR05_nTracks_(-9999)
   ,isoR05_nJets_(-9999)
   ,numberOfValidPixelHitsInInnerTrack_(-1)
   ,numberOfValidTrackerHitsInInnerTrack_(-1)
   ,numberOfValidMuonHitsInGlobalTrack_(-1)
   ,pixelLayersWithMeasurementInInnerTrack_(-1)
   ,stripLayersWithMeasurementInInnerTrack_(-1)
   ,normalizedChi2InnerTrack_(-9999.)
   ,normalizedChi2GlobalTrack_(-9999.)
   ,innerTrackDxy_(-9999.)
   ,innerTrackDz_(-9999.)
   ,bestTrackDxy_(-9999.)
   ,bestTrackDz_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,innerTrack_(0.,0.,0.,0.)
   ,outerTrack_(0.,0.,0.,0.)
   ,globalTrack_(0.,0.,0.,0.)
   ,pfTrack_(0.,0.,0.,0.)
   ,ptErrorInnerTrack_(-9999.)
   ,etaErrorInnerTrack_(-9999.)
   ,phiErrorInnerTrack_(-9999.)
   {;}
   
   TRootMuon(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
   TRootParticle(momentum, vertex, type, charge)
   ,isGlobalMuon_(false)
   ,isTrackerMuon_(false)
   ,isStandAloneMuon_(false)
   ,isCaloMuon_(false)
   ,isPFMuon_(false)
   ,isRPCMuon_(false)
   ,isEnergyValid_(false)
   ,isIsolationValid_(false)
   ,isPfIsolationValid_(false)
   ,isQualityValid_(false)
   ,id_(-9999)
   ,numberOfChambers_(-1)
   ,numberOfMatches_(-1)
   ,numberOfMatchedStations_(-1)
   ,timeDirection_(-9999)
   ,et_em_(-9999.)
   ,et_emS9_(-9999.)
   ,et_emS25_(-9999.)
   ,et_emMax_(-9999.)
   ,et_had_(-9999.)
   ,et_hadS9_(-9999.)
   ,et_hadMax_(-9999.)
   ,et_ho_(-9999.)
   ,et_hoS9_(-9999.)
   ,caloCompatibility_(-9999.)
   ,pfIsoChargedHadronPt04_(-9999.)
   ,pfIsoChargedParticlePt04_(-9999.)
   ,pfIsoNeutralHadronEt04_(-9999.)
   ,pfIsoPhotonEt04_(-9999.)
   ,pfIsoNeutralHadronEtHighThreshold04_(-9999.)
   ,pfIsoPhotonEtHighThreshold04_(-9999.)
   ,pfIsoPUPt04_(-9999.)
   ,isoR03_emEt_(-9999.)
   ,isoR03_hadEt_(-9999.)
   ,isoR03_hoEt_(-9999.)
   ,isoR03_sumPt_(-9999.)
   ,isoR03_nTracks_(-9999)
   ,isoR03_nJets_(-9999)
   ,isoR05_emEt_(-9999.)
   ,isoR05_hadEt_(-9999.)
   ,isoR05_hoEt_(-9999.)
   ,isoR05_sumPt_(-9999.)
   ,isoR05_nTracks_(-9999)
   ,isoR05_nJets_(-9999)
   ,numberOfValidPixelHitsInInnerTrack_(-1)
   ,numberOfValidTrackerHitsInInnerTrack_(-1)
   ,numberOfValidMuonHitsInGlobalTrack_(-1)
   ,pixelLayersWithMeasurementInInnerTrack_(-1)
   ,stripLayersWithMeasurementInInnerTrack_(-1)
   ,normalizedChi2InnerTrack_(-9999.)
   ,normalizedChi2GlobalTrack_(-9999.)
   ,innerTrackDxy_(-9999.)
   ,innerTrackDz_(-9999.)
   ,bestTrackDxy_(-9999.)
   ,bestTrackDz_(-9999.)
   ,ip3DSignificance_(-9999.)
   ,innerTrack_(0.,0.,0.,0.)
   ,outerTrack_(0.,0.,0.,0.)
   ,globalTrack_(0.,0.,0.,0.)
   ,pfTrack_(0.,0.,0.,0.)
   ,ptErrorInnerTrack_(-9999.)
   ,etaErrorInnerTrack_(-9999.)
   ,phiErrorInnerTrack_(-9999.)
   {;}
   
   ~TRootMuon() {;}
   
   
   // Muon type
   Bool_t isGlobalMuon() const { return isGlobalMuon_;}
   Bool_t isTrackerMuon() const { return isTrackerMuon_;}
   Bool_t isStandAloneMuon() const { return isStandAloneMuon_;}
   Bool_t isCaloMuon() const { return isCaloMuon_;}
   Bool_t isPFMuon() const { return isPFMuon_;}
   Bool_t isRPCMuon() const { return isRPCMuon_;}
   
   // Muon block validity
   Bool_t isEnergyValid() const { return isEnergyValid_;}
   Bool_t isIsolationValid() const { return isIsolationValid_;}
   Bool_t isPfIsolationValid() const { return isPfIsolationValid_;}
   Bool_t isQualityValid() const { return isQualityValid_;}
   
   // Muon ID
   Int_t id() const { return id_;}
   Bool_t idTrackerMuonArbitrated() const { return id_ & 1; }
   Bool_t idAllArbitrated() const { return id_ & 2; }
   Bool_t idGlobalMuonPromptTight() const { return id_ & 4; }
   Bool_t idTMLastStationLoose() const { return id_ & 8; }
   Bool_t idTMLastStationTight() const { return id_ & 16; }
   Bool_t idTM2DCompatibilityLoose() const { return id_ & 32; }
   Bool_t idTM2DCompatibilityTight() const { return id_ & 64; }
   
   // Muon ID Perso
   // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Tight_Muon
   Bool_t isTightMuonPerso() const;
   
   
   Int_t numberOfChambers() const { return numberOfChambers_;}
   Int_t numberOfMatches() const { return numberOfMatches_;}
   Int_t numberOfMatchedStations() const { return numberOfMatchedStations_;}
   Int_t timeDirection() const { return timeDirection_;}
   
   
   // Muon energy 
   Float_t et_em() const { return et_em_;}
   Float_t et_emS9() const { return et_emS9_;}
   Float_t et_emS25() const { return et_emS25_;}
   Float_t et_emMax() const { return et_emMax_;}
   Float_t et_had() const { return et_had_;}
   Float_t et_hadS9() const { return et_hadS9_;}
   Float_t et_hadMax() const { return et_hadMax_;}
   Float_t et_ho() const { return et_ho_;}
   Float_t et_hoS9() const { return et_hoS9_;}
   Float_t caloCompatibility() const { return caloCompatibility_;}
   
   // Muon PF isolation 
   Float_t pfIsoChargedHadronPt04() const { return pfIsoChargedHadronPt04_;}
   Float_t pfIsoChargedParticlePt04() const { return pfIsoChargedParticlePt04_;}
   Float_t pfIsoNeutralHadronEt04() const { return pfIsoNeutralHadronEt04_;}
   Float_t pfIsoPhotonEt04() const { return pfIsoPhotonEt04_;}
   Float_t pfIsoNeutralHadronEtHighThreshold04() const { return pfIsoNeutralHadronEtHighThreshold04_;}
   Float_t pfIsoPhotonEtHighThreshold04() const { return pfIsoPhotonEtHighThreshold04_;}
   Float_t pfIsoPUPt04() const { return pfIsoPUPt04_;}
   
   // Muon PF isolation Perso
   // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Accessing_PF_Isolation_from_reco
   Float_t deltaBetaPfIso04() const
   { 
      Float_t iso=999999.;
      if(this->Pt()>0) iso = ( pfIsoChargedHadronPt04_ + max(0., pfIsoNeutralHadronEt04_ + pfIsoPhotonEt04_ - 0.5*pfIsoPUPt04_ ) )/ (this->Pt());
      return iso;      
   }
   Bool_t passLooseDeltaBetaPfIso04() const { return (this->deltaBetaPfIso04())<0.20;}
   Bool_t passTightDeltaBetaPfIso04() const { return (this->deltaBetaPfIso04())<0.12;}
   
   
   // Muon detector isolation (cone DR=0.3)
   Float_t isoR03_emEt() const { return isoR03_emEt_;}
   Float_t isoR03_hadEt() const { return isoR03_hadEt_;}
   Float_t isoR03_hoEt() const { return isoR03_hoEt_;}
   Float_t isoR03_sumPt() const { return isoR03_sumPt_;}
   Int_t isoR03_nTracks() const { return isoR03_nTracks_;}
   Int_t isoR03_nJets() const { return isoR03_nJets_;}
   
   // Muon detector isolation (cone DR=0.5)
   Float_t isoR05_emEt() const { return isoR05_emEt_;}
   Float_t isoR05_hadEt() const { return isoR05_hadEt_;}
   Float_t isoR05_hoEt() const { return isoR05_hoEt_;}
   Float_t isoR05_sumPt() const { return isoR05_sumPt_;}
   Int_t isoR05_nTracks() const { return isoR05_nTracks_;}
   Int_t isoR05_nJets() const { return isoR05_nJets_;}
   
   
   // Track & Hits pattern 
   Int_t numberOfValidPixelHitsInInnerTrack() const { return numberOfValidPixelHitsInInnerTrack_; }
   Int_t numberOfValidTrackerHitsInInnerTrack() const { return numberOfValidTrackerHitsInInnerTrack_; }
   Int_t numberOfValidMuonHitsInGlobalTrack() const { return numberOfValidMuonHitsInGlobalTrack_; }
   Int_t pixelLayersWithMeasurementInInnerTrack() const { return pixelLayersWithMeasurementInInnerTrack_; }
   Int_t stripLayersWithMeasurementInInnerTrack() const { return stripLayersWithMeasurementInInnerTrack_; }
   Int_t trackerLayersWithMeasurementInInnerTrack() const { return (pixelLayersWithMeasurementInInnerTrack_ + stripLayersWithMeasurementInInnerTrack_); }
   
   Float_t normalizedChi2InnerTrack() const { return normalizedChi2InnerTrack_;}
   Float_t normalizedChi2GlobalTrack() const { return normalizedChi2GlobalTrack_;}
   Float_t innerTrackDxy() const { return innerTrackDxy_;}
   Float_t innerTrackDz() const { return innerTrackDz_;}
   Float_t bestTrackDxy() const { return bestTrackDxy_;}
   Float_t bestTrackDz() const { return bestTrackDz_;}
   Float_t ip3DSignificance() const { return ip3DSignificance_;}
      
   TLorentzVector innerTrack() const { return innerTrack_; }
   TLorentzVector outerTrack() const { return outerTrack_; }
   TLorentzVector globalTrack() const { return globalTrack_; }
   TLorentzVector pfTrack() const { return pfTrack_; }
   
   Float_t ptErrorInnerTrack() const { return ptErrorInnerTrack_; }
   Float_t etaErrorInnerTrack() const { return etaErrorInnerTrack_; }
   Float_t phiErrorInnerTrack() const { return phiErrorInnerTrack_; }
   
   
   //TObject* genMuon() const { return genMuon_.GetObject() ;}
   virtual TString typeName() const { return "TRootMuon"; }
   
   
   
   // Set Muon type
   void setMuonType(Bool_t isGlobalMuon, Bool_t isTrackerMuon, Bool_t isStandAloneMuon, Bool_t isCaloMuon, Bool_t isPFMuon, Bool_t isRPCMuon)
   {
      isGlobalMuon_ = isGlobalMuon;
      isTrackerMuon_ = isTrackerMuon;
      isStandAloneMuon_ = isStandAloneMuon;
      isCaloMuon_ = isCaloMuon;
      isPFMuon_ = isPFMuon;
      isRPCMuon_ = isRPCMuon;
   }
   
   // Set Muon block validity
   void setValidity(Bool_t isEnergyValid, Bool_t isIsolationValid, Bool_t isPfIsolationValid, Bool_t isQualityValid)
   {
      isEnergyValid_ = isEnergyValid;
      isIsolationValid_ = isIsolationValid;
      isPfIsolationValid_ = isPfIsolationValid;
      isQualityValid_ = isQualityValid;
   }
   
   // Set Muon ID
   void setID(Int_t id) { id_ = id; }
   void setID(
      Int_t trackerMuonArbitrated
      ,Int_t allArbitrated
      ,Int_t globalMuonPromptTight
      ,Int_t tmLastStationLoose
      ,Int_t tmLastStationTight
      ,Int_t tm2DCompatibilityLoose
      ,Int_t tm2DCompatibilityTight
   )
   { id_ = trackerMuonArbitrated*1 + allArbitrated*2 + globalMuonPromptTight*4 + tmLastStationLoose*8 + tmLastStationTight*16 + tm2DCompatibilityLoose*32 + tm2DCompatibilityTight*64; }
   
   
   
   void setNumberOfChambers(Int_t numberOfChambers) { numberOfChambers_ = numberOfChambers; }
   void setNumberOfMatches(Int_t numberOfMatches) { numberOfMatches_ = numberOfMatches; }
   void setNumberOfMatchedStations(Int_t numberOfMatchedStations) { numberOfMatchedStations_ = numberOfMatchedStations; }
   void setTimeDirection(Int_t timeDirection) { timeDirection_ = timeDirection; }
   
   
   // Set Muon energy 
   void setCaloEnergy(Float_t et_em, Float_t et_emS9, Float_t et_emS25, Float_t et_emMax, Float_t et_had, Float_t et_hadS9,  Float_t et_hadMax, Float_t et_ho, Float_t et_hoS9, Float_t caloCompatibility)
   {
      et_em_ = et_em;
      et_emS9_ = et_emS9;
      et_emS25_ = et_emS25;
      et_emMax_ = et_emMax;
      et_had_ = et_had;
      et_hadS9_ = et_hadS9;
      et_hadMax_ = et_hadMax;
      et_ho_ = et_ho;
      et_hoS9_ = et_hoS9;
      caloCompatibility_ = caloCompatibility;
   }
   
   // Set Muon PF isolation (cone DR=0.4)
   void setPfIsoR04(Float_t pfIsoChargedHadronPt04, Float_t pfIsoChargedParticlePt04, Float_t pfIsoNeutralHadronEt04, Float_t pfIsoPhotonEt04, Float_t pfIsoNeutralHadronEtHighThreshold04, Float_t pfIsoPhotonEtHighThreshold04, Float_t pfIsoPUPt04)
   {
      pfIsoChargedHadronPt04_ = pfIsoChargedHadronPt04;
      pfIsoChargedParticlePt04_ = pfIsoChargedParticlePt04;
      pfIsoNeutralHadronEt04_ = pfIsoNeutralHadronEt04;
      pfIsoPhotonEt04_ = pfIsoPhotonEt04;
      pfIsoNeutralHadronEtHighThreshold04_ = pfIsoNeutralHadronEtHighThreshold04;
      pfIsoPhotonEtHighThreshold04_ = pfIsoPhotonEtHighThreshold04;
      pfIsoPUPt04_ = pfIsoPUPt04;
   }
   
   // Set Muon detector isolation (cone DR=0.5)
   void setIsoR03(Float_t isoR03_emEt, Float_t isoR03_hadEt, Float_t isoR03_hoEt, Float_t isoR03_sumPt, Int_t isoR03_nTracks, Int_t isoR03_nJets)
   {
      isoR03_emEt_ = isoR03_emEt;
      isoR03_hadEt_ = isoR03_hadEt;
      isoR03_hoEt_ = isoR03_hoEt;
      isoR03_sumPt_ = isoR03_sumPt;
      isoR03_nTracks_ = isoR03_nTracks;
      isoR03_nJets_ = isoR03_nJets;
   }
   
   // Set Muon detector isolation (cone DR=0.5)
   void setIsoR05(Float_t isoR05_emEt, Float_t isoR05_hadEt, Float_t isoR05_hoEt, Float_t isoR05_sumPt, Int_t isoR05_nTracks, Int_t isoR05_nJets)
   {
      isoR05_emEt_ = isoR05_emEt;
      isoR05_hadEt_ = isoR05_hadEt;
      isoR05_hoEt_ = isoR05_hoEt;
      isoR05_sumPt_ = isoR05_sumPt;
      isoR05_nTracks_ = isoR05_nTracks;
      isoR05_nJets_ = isoR05_nJets;
   }
   
   
   // Set Track & Hits pattern 
   void setNumberOfValidPixelHitsInInnerTrack(Int_t numberOfValidPixelHitsInInnerTrack) { numberOfValidPixelHitsInInnerTrack_ = numberOfValidPixelHitsInInnerTrack; }
   void setNumberOfValidTrackerHitsInInnerTrack(Int_t numberOfValidTrackerHitsInInnerTrack) { numberOfValidTrackerHitsInInnerTrack_ = numberOfValidTrackerHitsInInnerTrack; }
   void setNumberOfValidMuonHitsInGlobalTrack(Int_t numberOfValidMuonHitsInGlobalTrack) { numberOfValidMuonHitsInGlobalTrack_ = numberOfValidMuonHitsInGlobalTrack; }
   void setPixelLayersWithMeasurementInInnerTrack(Int_t pixelLayersWithMeasurementInInnerTrack) { pixelLayersWithMeasurementInInnerTrack_ = pixelLayersWithMeasurementInInnerTrack; }
   void setStripLayersWithMeasurementInInnerTrack(Int_t stripLayersWithMeasurementInInnerTrack) { stripLayersWithMeasurementInInnerTrack_ = stripLayersWithMeasurementInInnerTrack; }
   
   void setNormalizedChi2InnerTrack(Float_t normalizedChi2InnerTrack) { normalizedChi2InnerTrack_ = normalizedChi2InnerTrack; }
   void setNormalizedChi2GlobalTrack(Float_t normalizedChi2GlobalTrack) { normalizedChi2GlobalTrack_ = normalizedChi2GlobalTrack; }
   
   void setInnerTrackDxy(Float_t innerTrackDxy) { innerTrackDxy_ = innerTrackDxy; }
   void setInnerTrackDz(Float_t innerTrackDz) { innerTrackDz_ = innerTrackDz; }
   
   void setBestTrackDxy(Float_t bestTrackDxy) { bestTrackDxy_ = bestTrackDxy; }
   void setBestTrackDz(Float_t bestTrackDz) { bestTrackDz_ = bestTrackDz; }
   
   void setIP3DSignificance(Float_t ip3DSignificance) { ip3DSignificance_ = ip3DSignificance; }
   
   void setXYZTInnerTrack(Double_t x, Double_t y, Double_t z, Double_t t) { innerTrack_.SetXYZT(x,y,z,t); }
   void setXYZTOuterTrack(Double_t x, Double_t y, Double_t z, Double_t t) { outerTrack_.SetXYZT(x,y,z,t); }
   void setXYZTGlobalTrack(Double_t x, Double_t y, Double_t z, Double_t t) { globalTrack_.SetXYZT(x,y,z,t); }
   void setXYZTPfTrack(Double_t x, Double_t y, Double_t z, Double_t t) { pfTrack_.SetXYZT(x,y,z,t); }
   
   void setPtErrorInnerTrack(Float_t ptErrorInnerTrack) { ptErrorInnerTrack_ = ptErrorInnerTrack; }
   void setEtaErrorInnerTrack(Float_t etaErrorInnerTrack) { etaErrorInnerTrack_ = etaErrorInnerTrack; }
   void setPhiErrorInnerTrack(Float_t phiErrorInnerTrack) { phiErrorInnerTrack_ = phiErrorInnerTrack; }

   
   friend std::ostream& operator<< (std::ostream& stream, const TRootMuon& muon) {
      stream << "TRootMuon - Charge=" << muon.charge() << " (Et,eta,phi)=("<< muon.Et() <<","<< muon.Eta() <<","<< muon.Phi() << ")  vertex(x,y,z)=("<< muon.vx() <<","<< muon.vy() <<","<< muon.vz() << ")"
      << "   Type(G,T,S,C,PF,RPC)=(" << muon.isGlobalMuon() << ","  << muon.isTrackerMuon() << ","  << muon.isStandAloneMuon() << ","  << muon.isCaloMuon()  << ","  << muon.isPFMuon()  << ","  << muon.isRPCMuon() << ") ";
      return stream;
   };
   
   void Print()
   {
      std::cout << "TRootMuon - Charge=" << this->charge() << " (Et,eta,phi)=("<< this->Et() <<","<< this->Eta() <<","<< this->Phi() << ")  vertex(x,y,z)=("<< this->vx() <<","<< this->vy() <<","<< this->vz() << ")"
         << "  Type(G,T,S,C,PF,RPC)=(" << this->isGlobalMuon() << ","  << this->isTrackerMuon() << ","  << this->isStandAloneMuon() << ","  << this->isCaloMuon()  << ","  << this->isPFMuon()  << ","  << this->isRPCMuon() << ") " << endl
         << "            TightID (perso)=" << this->isTightMuonPerso()<< "  Chi2=" << this->normalizedChi2GlobalTrack() << "  Muon hits=" << this->numberOfValidMuonHitsInGlobalTrack() << "  Matched stations=" << this->numberOfMatchedStations()
         << "  dxy=" << this->bestTrackDxy() << "  dz=" << this->bestTrackDz() << "  Pixel hits=" << this->numberOfValidPixelHitsInInnerTrack() << "  Tracker layers=" << this->trackerLayersWithMeasurementInInnerTrack() << endl
         << "            Nb of chambers=" << this->numberOfChambers() << "  Nb of matched chambers="  << this->numberOfMatches() 
         << "  ID=(" << this->idTrackerMuonArbitrated() << ","  << this->idAllArbitrated() << ","  << this->idGlobalMuonPromptTight() << ","  << this->idTMLastStationLoose()
         << ","  << this->idTMLastStationTight() << ","  << this->idTM2DCompatibilityLoose() << ","  << this->idTM2DCompatibilityTight() << ")" << "  Direction=" << this->timeDirection()
         << "  caloCompatibility="<<  this->caloCompatibility() << "  validity(energy,det-iso,pf-iso,quality)=(" << this->isEnergyValid() <<","<< this->isIsolationValid() <<","<< this->isPfIsolationValid() <<","<< this->isQualityValid() << ")" << endl
         << "            Et_em=" << this->et_em() << " Et_emS9=" << this->et_emS9() << " Et_emS25=" << this->et_emS25() << " Et_emMax=" << this->et_emMax() << "  Et_had=" << this->et_had() << " Et_hadS9=" << this->et_hadS9()  << " Et_hadMax=" << this->et_hadMax() << "  Et_ho=" << this->et_ho() << "  Et_hoS9=" << this->et_hoS9() << endl
         << "            det. isolation cone 0.3: Et_em=" << this->isoR03_emEt() << "  Et_had=" << this->isoR03_hadEt() <<"  Et_ho=" << this->isoR03_hoEt()  << "  nTracks=" << this->isoR03_nTracks() <<"  nJets=" << this->isoR03_nJets() << endl
         << "            det. isolation cone 0.5: Et_em=" << this->isoR05_emEt() << "  Et_had=" << this->isoR05_hadEt() <<"  Et_ho=" << this->isoR05_hoEt()  << "  nTracks=" << this->isoR05_nTracks() <<"  nJets=" << this->isoR05_nJets() << endl
         << "            PF Isolation cone 0.4  : ch.had=" << this->pfIsoChargedHadronPt04() << "  ch.part=" << this->pfIsoChargedParticlePt04() << "  neut.had=" << this->pfIsoNeutralHadronEt04()  << "  photons=" << this->pfIsoPhotonEt04()  << "  neut.had.high.thr.=" << this->pfIsoNeutralHadronEtHighThreshold04()  << "  phot.high.thr.=" << this->pfIsoPhotonEtHighThreshold04()  << "  PU=" << this->pfIsoPUPt04() << endl
         << "            IP 3D Significance=" << this->ip3DSignificance() << "  bestTrack: dxy=" << this->bestTrackDxy() << " , dz=" << this->bestTrackDz() << "  innerTrack: dxy=" << this->innerTrackDxy() << " , dz=" << this->innerTrackDz();
   };
   
   
   private:
      
      // Muon type (read from reco::Muon)
      Bool_t isGlobalMuon_;
      Bool_t isTrackerMuon_;
      Bool_t isStandAloneMuon_;
      Bool_t isCaloMuon_;
      Bool_t isPFMuon_;
      Bool_t isRPCMuon_;
      
      // Muon block validity (read from reco::Muon)
      Bool_t isEnergyValid_;
      Bool_t isIsolationValid_;
      Bool_t isPfIsolationValid_;
      Bool_t isQualityValid_;
      
      // Muon ID (read from reco::Muon)
      Int_t id_;        // MuonId coded in binary word id_
      // TrackerMuonArbitrated=0000001 , AllArbitrated=0000010 , GlobalMuonPromptTight=0000100 ,
      // TMLastStationLoose=0001000 , TMLastStationTight=0010000 , TM2DCompatibilityLoose=0100000 , TM2DCompatibilityTight=1000000
      
      // Variables from reco::Muon
      Int_t numberOfChambers_;        // number of chambers (include RPC rolls)
      Int_t numberOfMatches_;         // number of chambers with matched segments
      Int_t numberOfMatchedStations_; // number of stations with matched segments
      Int_t timeDirection_;           //  OutsideIn = -1, Undefined = 0, InsideOut = 1
      
      // Muon energy (read from reco::Muon)
      Float_t et_em_;                 // energy deposited in crossed ECAL crystals
      Float_t et_emS9_;               // energy deposited in 3x3 ECAL crystal matrix around crossed crystal
      Float_t et_emS25_;              // energy deposited in 5x5 ECAL crystal matrix around crossed crystal
      Float_t et_emMax_;              // maximal energy of ECAL crystal in the 5x5 shape
      Float_t et_had_;                // energy deposited in crossed HCAL tower (RecHits)
      Float_t et_hadS9_;              // energy deposited in 3x3 HCAL tower matrix around crossed tower (RecHits)
      Float_t et_hadMax_;             // maximal energy of HCAL tower in the 3x3 shape
      Float_t et_ho_;                 // energy deposited in crossed HO tower (RecHits)
      Float_t et_hoS9_;               // energy deposited in 3x3 HO tower matrix around crossed tower (RecHits)
      Float_t caloCompatibility_;     // Relative likelihood based on ECAL, HCAL, HO energy defined as L_muon/(L_muon+L_not_muon)
      
      // Muon PF isolation (read from reco::Muon)
      Float_t pfIsoChargedHadronPt04_;              // sum pt of charged Hadron 
      Float_t pfIsoChargedParticlePt04_;            // sum pt of charged Particles(inludes e/mu) 
      Float_t pfIsoNeutralHadronEt04_;              // sum Et of neutral hadrons
      Float_t pfIsoPhotonEt04_;                     // sum Et of PF photons
      Float_t pfIsoNeutralHadronEtHighThreshold04_; // sum Et of neutral hadrons with a higher threshold (1 GeV instead of 0.5 GeV) 
      Float_t pfIsoPhotonEtHighThreshold04_;        // sum Et of PF photons with a higher threshold (1 GeV instead of 0.5 GeV) 
      Float_t pfIsoPUPt04_;                         // sum pt of the charged particles in the cone of interest but with particles not originating from the primary vertex (for PU corrections) 
      
      // Muon detector isolation (read from reco::Muon)
      // Cone DR=0.3
      Float_t isoR03_emEt_;
      Float_t isoR03_hadEt_;
      Float_t isoR03_hoEt_;
      Float_t isoR03_sumPt_;
      Int_t isoR03_nTracks_;
      Int_t isoR03_nJets_;
      
      // Cone DR=0.5
      Float_t isoR05_emEt_;
      Float_t isoR05_hadEt_;
      Float_t isoR05_hoEt_;
      Float_t isoR05_sumPt_;
      Int_t isoR05_nTracks_;
      Int_t isoR05_nJets_;
      
      
      // Track & Hits pattern (TrackRef read from reco::Muon)
      Int_t numberOfValidPixelHitsInInnerTrack_;      // Number of valid pixel hits associated to inner track
      Int_t numberOfValidTrackerHitsInInnerTrack_;    // Number of valid tracker hits (pixel+strip) associated to inner track - More than 1 hit per layer (even mono) is possible due to modules overlap
      Int_t numberOfValidMuonHitsInGlobalTrack_;      // Number of valid muon hits associated to global track
      Int_t pixelLayersWithMeasurementInInnerTrack_;  // Number of pixel layers with at least one valid hit associated to inner track
      Int_t stripLayersWithMeasurementInInnerTrack_;  // Number of strip layers with at least one valid hit associated to inner track
      
      Float_t normalizedChi2InnerTrack_;     // chi-squared divided by n.d.o.f. of inner track
      Float_t normalizedChi2GlobalTrack_;    // chi-squared divided by n.d.o.f. of global track
      
      Float_t innerTrackDxy_;        // dxy wrt to primary vertex of inner track (i.e. the track used to compute muon momentum)
      Float_t innerTrackDz_;         //  dz wrt to primary vertex of inner track (i.e. the track used to compute muon momentum)
      
      Float_t bestTrackDxy_;        // dxy wrt to primary vertex of best track (i.e. the track used to compute muon momentum)
      Float_t bestTrackDz_;         //  dz wrt to primary vertex of best track (i.e. the track used to compute muon momentum)
      
      Float_t ip3DSignificance_;   // Significance of the impact parameter wrt to the selected primary vertex
      
      
      // Muon associated tracks
      TLorentzVector innerTrack_;  // Tracker only (TrackRef read from reco::Muon)
      TLorentzVector outerTrack_;  // Muon detector only (TrackRef read from reco::Muon)
      TLorentzVector globalTrack_; // Tracker + Muon detector (TrackRef read from reco::Muon)
      TLorentzVector pfTrack_;     // PF momentum (LorentzVector stored in reco::Muon)
      
      Float_t ptErrorInnerTrack_;
      Float_t etaErrorInnerTrack_;
      Float_t phiErrorInnerTrack_;
      
      
      ClassDef (TRootMuon,8);
      
   };
   
   #endif
   