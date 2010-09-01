#ifndef TRootMuon_h
#define TRootMuon_h

#include "../interface/TRootParticle.h"

using namespace std;

class TRootMuon : public TRootParticle
{
   
   public:
      
      TRootMuon() :
      TRootParticle()
      ,numberOfChambers_(-1)
      ,numberOfMatches_(-1)
      ,et_em_(-9999.)
      ,et_emS9_(-9999.)
      ,et_had_(-9999.)
      ,et_hadS9_(-9999.)
      ,et_ho_(-9999.)
      ,et_hoS9_(-9999.)
      ,caloCompatibility_(-9999.)
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
      ,trackIso_(-9999)
      ,ecalIso_(-9999)
      ,hcalIso_(-9999)
      ,pfParticleIso_(-9999)
      ,pfChargedHadronIso_(-9999)
      ,pfNeutralHadronIso_(-9999)
      ,pfPhotonIso_(-9999)
      ,energyValid_(false)
      ,matchesValid_(false)
      ,isolationValid_(false)
      ,direction_(-9999)
      ,algo_(-9999)
      ,id_(-9999)
      ,numberOfValidPixelHits_(-1)
      ,numberOfValidTrackerHits_(-1)
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
      ,innerTrack_(0.,0.,0.,0.)
      ,outerTrack_(0.,0.,0.,0.)
      ,globalTrack_(0.,0.,0.,0.)
      ,ecalCandEnergy_(-9999.)
      ,hcalCandEnergy_(-9999.)
      {;}
      
      TRootMuon(const TRootMuon& muon) :
      TRootParticle(muon)
      ,numberOfChambers_(muon.numberOfChambers_)
      ,numberOfMatches_(muon.numberOfMatches_)
      ,et_em_(muon.et_em_)
      ,et_emS9_(muon.et_emS9_)
      ,et_had_(muon.et_had_)
      ,et_hadS9_(muon.et_hadS9_)
      ,et_ho_(muon.et_ho_)
      ,et_hoS9_(muon.et_hoS9_)
      ,caloCompatibility_(muon.caloCompatibility_)
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
      ,trackIso_(muon.trackIso_)
      ,ecalIso_(muon.ecalIso_)
      ,hcalIso_(muon.hcalIso_)
      ,pfParticleIso_(muon.pfParticleIso_)
      ,pfChargedHadronIso_(muon.pfChargedHadronIso_)
      ,pfNeutralHadronIso_(muon.pfNeutralHadronIso_)
      ,pfPhotonIso_(muon.pfPhotonIso_)
      ,energyValid_(muon.energyValid_)
      ,matchesValid_(muon.matchesValid_)
      ,isolationValid_(muon.isolationValid_)
      ,direction_(muon.direction_)
      ,algo_(muon.algo_)
      ,id_(muon.id_)
      ,numberOfValidPixelHits_(muon.numberOfValidPixelHits_)
      ,numberOfValidTrackerHits_(muon.numberOfValidTrackerHits_)
      ,pixelLayersWithMeasurement_(muon.pixelLayersWithMeasurement_)
      ,stripLayersWithMeasurement_(muon.stripLayersWithMeasurement_)
      ,d0_(muon.d0_)
      ,d0Error_(muon.d0Error_)
      ,dsz_(muon.dsz_)
      ,dszError_(muon.dszError_)
      ,dB_(muon.dB_)
      ,normalizedChi2_(muon.normalizedChi2_)
      ,ptError_(muon.ptError_)
      ,etaError_(muon.etaError_)
      ,phiError_(muon.phiError_)
      ,ip3DSignificance_(muon.ip3DSignificance_)
      ,innerTrack_(muon.innerTrack_)
      ,outerTrack_(muon.outerTrack_)
      ,globalTrack_(muon.globalTrack_)
      ,ecalCandEnergy_(muon.ecalCandEnergy_)
      ,hcalCandEnergy_(muon.hcalCandEnergy_)
      {;}
      
      TRootMuon(Double_t px, Double_t py, Double_t pz, Double_t e) :
      TRootParticle(px,py,pz,e)
      ,numberOfChambers_(-1)
      ,numberOfMatches_(-1)
      ,et_em_(-9999.)
      ,et_emS9_(-9999.)
      ,et_had_(-9999.)
      ,et_hadS9_(-9999.)
      ,et_ho_(-9999.)
      ,et_hoS9_(-9999.)
      ,caloCompatibility_(-9999.)
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
      ,trackIso_(-9999)
      ,ecalIso_(-9999)
      ,hcalIso_(-9999)
      ,pfParticleIso_(-9999)
      ,pfChargedHadronIso_(-9999)
      ,pfNeutralHadronIso_(-9999)
      ,pfPhotonIso_(-9999)
      ,energyValid_(false)
      ,matchesValid_(false)
      ,isolationValid_(false)
      ,direction_(-9999)
      ,algo_(-9999)
      ,id_(-9999)
      ,numberOfValidPixelHits_(-1)
      ,numberOfValidTrackerHits_(-1)
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
      ,innerTrack_(0.,0.,0.,0.)
      ,outerTrack_(0.,0.,0.,0.)
      ,globalTrack_(0.,0.,0.,0.)
      ,ecalCandEnergy_(-9999.)
      ,hcalCandEnergy_(-9999.)
      {;}
      
      TRootMuon(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
      ,numberOfChambers_(-1)
      ,numberOfMatches_(-1)
      ,et_em_(-9999.)
      ,et_emS9_(-9999.)
      ,et_had_(-9999.)
      ,et_hadS9_(-9999.)
      ,et_ho_(-9999.)
      ,et_hoS9_(-9999.)
      ,caloCompatibility_(-9999.)
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
      ,trackIso_(-9999)
      ,ecalIso_(-9999)
      ,hcalIso_(-9999)
      ,pfParticleIso_(-9999)
      ,pfChargedHadronIso_(-9999)
      ,pfNeutralHadronIso_(-9999)
      ,pfPhotonIso_(-9999)
      ,energyValid_(false)
      ,matchesValid_(false)
      ,isolationValid_(false)
      ,direction_(-9999)
      ,algo_(-9999)
      ,id_(-9999)
      ,numberOfValidPixelHits_(-1)
      ,numberOfValidTrackerHits_(-1)
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
      ,innerTrack_(0.,0.,0.,0.)
      ,outerTrack_(0.,0.,0.,0.)
      ,globalTrack_(0.,0.,0.,0.)
      ,ecalCandEnergy_(-9999.)
      ,hcalCandEnergy_(-9999.)
      {;}
      
      TRootMuon(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
      ,numberOfChambers_(-1)
      ,numberOfMatches_(-1)
      ,et_em_(-9999.)
      ,et_emS9_(-9999.)
      ,et_had_(-9999.)
      ,et_hadS9_(-9999.)
      ,et_ho_(-9999.)
      ,et_hoS9_(-9999.)
      ,caloCompatibility_(-9999.)
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
      ,trackIso_(-9999)
      ,ecalIso_(-9999)
      ,hcalIso_(-9999)
      ,pfParticleIso_(-9999)
      ,pfChargedHadronIso_(-9999)
      ,pfNeutralHadronIso_(-9999)
      ,pfPhotonIso_(-9999)
      ,energyValid_(false)
      ,matchesValid_(false)
      ,isolationValid_(false)
      ,direction_(-9999)
      ,algo_(-9999)
      ,id_(-9999)
      ,numberOfValidPixelHits_(-1)
      ,numberOfValidTrackerHits_(-1)
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
      ,innerTrack_(0.,0.,0.,0.)
      ,outerTrack_(0.,0.,0.,0.)
      ,globalTrack_(0.,0.,0.,0.)
      ,ecalCandEnergy_(-9999.)
      ,hcalCandEnergy_(-9999.)
      {;}
      
      TRootMuon(const TLorentzVector &momentum) :
      TRootParticle(momentum)
      ,numberOfChambers_(-1)
      ,numberOfMatches_(-1)
      ,et_em_(-9999.)
      ,et_emS9_(-9999.)
      ,et_had_(-9999.)
      ,et_hadS9_(-9999.)
      ,et_ho_(-9999.)
      ,et_hoS9_(-9999.)
      ,caloCompatibility_(-9999.)
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
      ,trackIso_(-9999)
      ,ecalIso_(-9999)
      ,hcalIso_(-9999)
      ,pfParticleIso_(-9999)
      ,pfChargedHadronIso_(-9999)
      ,pfNeutralHadronIso_(-9999)
      ,pfPhotonIso_(-9999)
      ,energyValid_(false)
      ,matchesValid_(false)
      ,isolationValid_(false)
      ,direction_(-9999)
      ,algo_(-9999)
      ,id_(-9999)
      ,numberOfValidPixelHits_(-1)
      ,numberOfValidTrackerHits_(-1)
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
      ,innerTrack_(0.,0.,0.,0.)
      ,outerTrack_(0.,0.,0.,0.)
      ,globalTrack_(0.,0.,0.,0.)
      ,ecalCandEnergy_(-9999.)
      ,hcalCandEnergy_(-9999.)
      {;}
      
      TRootMuon(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
      TRootParticle(momentum, vertex, type, charge)
      ,numberOfChambers_(-1)
      ,numberOfMatches_(-1)
      ,et_em_(-9999.)
      ,et_emS9_(-9999.)
      ,et_had_(-9999.)
      ,et_hadS9_(-9999.)
      ,et_ho_(-9999.)
      ,et_hoS9_(-9999.)
      ,caloCompatibility_(-9999.)
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
      ,trackIso_(-9999)
      ,ecalIso_(-9999)
      ,hcalIso_(-9999)
      ,pfParticleIso_(-9999)
      ,pfChargedHadronIso_(-9999)
      ,pfNeutralHadronIso_(-9999)
      ,pfPhotonIso_(-9999)
      ,energyValid_(false)
      ,matchesValid_(false)
      ,isolationValid_(false)
      ,direction_(-9999)
      ,algo_(-9999)
      ,id_(-9999)
      ,numberOfValidPixelHits_(-1)
      ,numberOfValidTrackerHits_(-1)
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
      ,innerTrack_(0.,0.,0.,0.)
      ,outerTrack_(0.,0.,0.,0.)
      ,globalTrack_(0.,0.,0.,0.)
      ,ecalCandEnergy_(-9999.)
      ,hcalCandEnergy_(-9999.)
      {;}
      
      ~TRootMuon() {;}
      
      
      Int_t numberOfChambers() const { return numberOfChambers_;}
      Int_t numberOfMatches() const { return numberOfMatches_;}
      Float_t et_em() const { return et_em_;}
      Float_t et_emS9() const { return et_emS9_;}
      Float_t et_had() const { return et_had_;}
      Float_t et_hadS9() const { return et_hadS9_;}
      Float_t et_ho() const { return et_ho_;}
      Float_t et_hoS9() const { return et_hoS9_;}
      Float_t caloCompatibility() const { return caloCompatibility_;}
      
      Float_t isoR03_emEt() const { return isoR03_emEt_;}
      Float_t isoR03_hadEt() const { return isoR03_hadEt_;}
      Float_t isoR03_hoEt() const { return isoR03_hoEt_;}
      Float_t isoR03_sumPt() const { return isoR03_sumPt_;}
      Int_t isoR03_nTracks() const { return isoR03_nTracks_;}
      Int_t isoR03_nJets() const { return isoR03_nJets_;}
      
      Float_t isoR05_emEt() const { return isoR05_emEt_;}
      Float_t isoR05_hadEt() const { return isoR05_hadEt_;}
      Float_t isoR05_hoEt() const { return isoR05_hoEt_;}
      Float_t isoR05_sumPt() const { return isoR05_sumPt_;}
      Int_t isoR05_nTracks() const { return isoR05_nTracks_;}
      Int_t isoR05_nJets() const { return isoR05_nJets_;}
      
      Float_t trackIso() const {return trackIso_;}
      Float_t ecalIso() const {return ecalIso_;}
      Float_t hcalIso() const {return hcalIso_;}
      
      Float_t pfParticleIso() const {return pfParticleIso_;}
      Float_t pfChargedHadronIso() const {return pfChargedHadronIso_;}
      Float_t pfNeutralHadronIso() const {return pfNeutralHadronIso_;}
      Float_t pfPhotonIso() const {return pfPhotonIso_;}
      
      Bool_t energyValid() const { return energyValid_;}
      Bool_t matchesValid() const { return matchesValid_;}
      Bool_t isolationValid() const { return isolationValid_;}
      
      Int_t direction() const { return direction_;}
      Int_t algo() const { return algo_;}
      
      Bool_t isGlobalMuon() const { return algo_ & 2; }
      Bool_t isTrackerMuon() const { return algo_ & 4; }
      Bool_t isStandAloneMuon() const { return algo_ & 8; }
      Bool_t isCaloMuon() const { return algo_ & 16; }
      
      Int_t id() const { return id_;}
      Bool_t idTrackerMuonArbitrated() const { return id_ & 1; }
      Bool_t idAllArbitrated() const { return id_ & 2; }
      Bool_t idGlobalMuonPromptTight() const { return id_ & 4; }
      Bool_t idTMLastStationLoose() const { return id_ & 8; }
      Bool_t idTMLastStationTight() const { return id_ & 16; }
      Bool_t idTM2DCompatibilityLoose() const { return id_ & 32; }
      Bool_t idTM2DCompatibilityTight() const { return id_ & 64; }
      
      Int_t numberOfValidPixelHits() const { return numberOfValidPixelHits_; }
      Int_t numberOfValidTrackerHits() const { return numberOfValidTrackerHits_; }
      Int_t pixelLayersWithMeasurement() const { return pixelLayersWithMeasurement_; }
      Int_t stripLayersWithMeasurement() const { return stripLayersWithMeasurement_; }
      Float_t d0() const { return d0_ ;}
      Float_t d0Error() const { return d0Error_ ;}
      Float_t dsz() const { return dsz_ ;}
      Float_t dszError() const { return dszError_ ;}
      Float_t dB() const { return dB_ ;}
      Float_t normalizedChi2() const { return normalizedChi2_ ;}
      Float_t ptError() const { return ptError_ ;}
      Float_t etaError() const { return etaError_ ;}
      Float_t phiError() const { return phiError_ ;}
      Float_t ip3DSignificance() const { return ip3DSignificance_ ;}
      
      TLorentzVector innerTrack() const { return innerTrack_; }
      TLorentzVector outerTrack() const { return outerTrack_; }
      TLorentzVector globalTrack() const { return globalTrack_; }
      
      Float_t ecalCandEnergy() const { return ecalCandEnergy_; }
      Float_t hcalCandEnergy() const { return hcalCandEnergy_; }
      
      //TObject* genMuon() const { return genMuon_.GetObject() ;}
      virtual TString typeName() const { return "TRootMuon"; }
      
      
      void setNumberOfChambers(Int_t numberOfChambers) { numberOfChambers_ = numberOfChambers; }
      void setNumberOfMatches(Int_t numberOfMatches) { numberOfMatches_ = numberOfMatches; }
      void setCaloEnergy(Float_t et_em, Float_t et_emS9, Float_t et_had, Float_t et_hadS9, Float_t et_ho, Float_t et_hoS9, Float_t caloCompatibility)
      {
         et_em_ = et_em;
         et_emS9_ = et_emS9;
         et_had_ = et_had;
         et_hadS9_ = et_hadS9;
         et_ho_ = et_ho;
         et_hoS9_ = et_hoS9;
         caloCompatibility_ = caloCompatibility;
      }
      
      void setIsoR03(Float_t isoR03_emEt, Float_t isoR03_hadEt, Float_t isoR03_hoEt, Float_t isoR03_sumPt, Int_t isoR03_nTracks, Int_t isoR03_nJets)
      {
         isoR03_emEt_ = isoR03_emEt;
         isoR03_hadEt_ = isoR03_hadEt;
         isoR03_hoEt_ = isoR03_hoEt;
         isoR03_sumPt_ = isoR03_sumPt;
         isoR03_nTracks_ = isoR03_nTracks;
         isoR03_nJets_ = isoR03_nJets;
      }
      
      void setIsoR05(Float_t isoR05_emEt, Float_t isoR05_hadEt, Float_t isoR05_hoEt, Float_t isoR05_sumPt, Int_t isoR05_nTracks, Int_t isoR05_nJets)
      {
         isoR05_emEt_ = isoR05_emEt;
         isoR05_hadEt_ = isoR05_hadEt;
         isoR05_hoEt_ = isoR05_hoEt;
         isoR05_sumPt_ = isoR05_sumPt;
         isoR05_nTracks_ = isoR05_nTracks;
         isoR05_nJets_ = isoR05_nJets;
      }
      
      void setTrackIso(Float_t trackIso) { trackIso_ = trackIso; }
      void setEcalIso(Float_t ecalIso) { ecalIso_ = ecalIso; }
      void setHcalIso(Float_t hcalIso) { hcalIso_ = hcalIso; }
      
      void setPFParticleIso(Float_t iso) { pfParticleIso_=iso; }
      void setPFChargedHadronIso(Float_t iso) { pfChargedHadronIso_=iso; }
      void setPFNeutralHadronIso(Float_t iso) { pfNeutralHadronIso_=iso; }
      void setPFPhotonIso(Float_t iso) { pfPhotonIso_=iso; }
      
      void setValidity(Bool_t energyValid, Bool_t matchesValid, Bool_t isolationValid)
      {
         energyValid_ = energyValid;
         matchesValid_ = matchesValid;
         isolationValid_ = isolationValid;
      }
      
      void setDirection(Int_t direction) { direction_ = direction; }
      void setAlgo(Int_t algo) { algo_ = algo; }
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
      
      void setNumberOfValidPixelHits(Int_t numberOfValidPixelHits) { numberOfValidPixelHits_ = numberOfValidPixelHits; }
      void setNumberOfValidTrackerHits(Int_t numberOfValidTrackerHits) { numberOfValidTrackerHits_ = numberOfValidTrackerHits; }
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
      
      void setXYZTInnerTrack(Double_t x, Double_t y, Double_t z, Double_t t) { innerTrack_.SetXYZT(x,y,z,t); }
      void setXYZTOuterTrack(Double_t x, Double_t y, Double_t z, Double_t t) { outerTrack_.SetXYZT(x,y,z,t); }
      void setXYZTGlobalTrack(Double_t x, Double_t y, Double_t z, Double_t t) { globalTrack_.SetXYZT(x,y,z,t); }
      
      void setEcalCandEnergy(Float_t ecalCandEnergy) { ecalCandEnergy_ = ecalCandEnergy; }
      void setHcalCandEnergy(Float_t hcalCandEnergy) { hcalCandEnergy_ = hcalCandEnergy;}
      
      friend std::ostream& operator<< (std::ostream& stream, const TRootMuon& muon) {
         stream << "TRootMuon - Charge=" << muon.charge() << " (Et,eta,phi)=("<< muon.Et() <<","<< muon.Eta() <<","<< muon.Phi() << ")  vertex(x,y,z)=("<< muon.vx() <<","<< muon.vy() <<","<< muon.vz() << ")"
         << "   Type(G,T,S,C)=(" << muon.isGlobalMuon() << ","  << muon.isTrackerMuon() << ","  << muon.isStandAloneMuon() << ","  << muon.isCaloMuon() << ") ";
         return stream;
      };
      
      void Print()
      {
         std::cout << "TRootMuon - Charge=" << this->charge() << " (Et,eta,phi)=("<< this->Et() <<","<< this->Eta() <<","<< this->Phi() << ")  vertex(x,y,z)=("<< this->vx() <<","<< this->vy() <<","<< this->vz() << ")"
         << "  Type(G,T,S,C)=(" << this->isGlobalMuon() << ","  << this->isTrackerMuon() << ","  << this->isStandAloneMuon() << ","  << this->isCaloMuon() << ") " << endl
         << "            Nb of chambers=" << this->numberOfChambers() << "  Nb of matched chambers="  << this->numberOfMatches()
         << "  ID=(" << this->idTrackerMuonArbitrated() << ","  << this->idAllArbitrated() << ","  << this->idGlobalMuonPromptTight() << ","  << this->idTMLastStationLoose()
         << ","  << this->idTMLastStationTight() << ","  << this->idTM2DCompatibilityLoose() << ","  << this->idTM2DCompatibilityTight() << ")" << "  Direction=" << this->direction_
         << "  caloCompatibility="<<  this->caloCompatibility_ << "  validity(energy,matches,isolation)=(" << this->energyValid_ <<","<< this->matchesValid_ <<","<< this->isolationValid_ << ")" << endl
         << "            Et_em=" << this->et_em_ << " Et_emS9=" << this->et_emS9_ << "  Et_had=" << this->et_had_ << " Et_hadS9=" << this->et_hadS9_ << "  Et_ho=" << this->et_ho_ << "  Et_hoS9=" << this->et_hoS9_ << endl
         << "            isolation cone 0.3: Et_em=" << this->isoR03_emEt_ << "  Et_had=" << this->isoR03_hadEt_ <<"  Et_ho=" << this->isoR03_hoEt_  << "  nTracks=" << this->isoR03_nTracks_ <<"  nJets=" << this->isoR03_nJets_ << endl
         << "            isolation cone 0.5: Et_em=" << this->isoR05_emEt_ << "  Et_had=" << this->isoR05_hadEt_ <<"  Et_ho=" << this->isoR05_hoEt_  << "  nTracks=" << this->isoR05_nTracks_ <<"  nJets=" << this->isoR05_nJets_ << endl
         << "            pat default isolation: Et_em=" << this->ecalIso_ << "  Et_had=" << this->hcalIso_ << "  Pt_trk=" << this->trackIso_ << endl
         << "            PF Isolation : particleIso=" << this->pfParticleIso_ << "  chargedHadronIso=" << this->pfChargedHadronIso_ << "  NeutralHadronIso=" << this->pfNeutralHadronIso_ << endl
         << "            d0=" << this->d0_ << " +- " << this->d0Error_ << "  dsz=" << this->dsz_ << " +- " << this->dszError_ << "  dB=" << this->dB_ << "   IP 3D Significance=" << this->ip3DSignificance_;
      };
      
      
   private:
      
      // Variables from reco::Muon
      Int_t numberOfChambers_;      // number of chambers
      Int_t numberOfMatches_;       // number of chambers with matched segments
      Float_t et_em_;             // energy deposited in crossed ECAL crystals
      Float_t et_emS9_;           // energy deposited in 3x3 ECAL crystal matrix around crossed crystal
      Float_t et_had_;            // energy deposited in crossed HCAL tower (RecHits)
      Float_t et_hadS9_;          // energy deposited in 3x3 HCAL tower matrix around crossed tower (RecHits)
      Float_t et_ho_;             // energy deposited in crossed HO tower (RecHits)
      Float_t et_hoS9_;           // energy deposited in 3x3 HO tower matrix around crossed tower (RecHits)
      Float_t caloCompatibility_; // Relative likelihood based on ECAL, HCAL, HO energy defined as L_muon/(L_muon+L_not_muon)
      
      // Muon isolation encapsulated in reco::Muon
      // http://cmslxr.fnal.gov/lxr/source/RecoMuon/MuonIsolationProducers/doc/MuonIsolationProducers.doc
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
      
      // Added by Stephane 23/04/2010 -- correct pat Isolation
      Float_t trackIso_; // returns the value of the summed track pt in a cone of deltaR<0.3
      Float_t ecalIso_; // returns the value of the summed Et of all recHits in the ecal in a cone of deltaR<0.3
      Float_t hcalIso_; // returns the value of the summed Et of all recHits in the hcal in a cone of deltaR<0.4
      
      // Added by Stephane 23/04/2010 -- pat Isolation for PFlow muons
      Float_t pfParticleIso_; // isolation calculated with all the PFCandidates
      Float_t pfChargedHadronIso_; // isolation calculated with only the charged hadron PFCandidates
      Float_t pfNeutralHadronIso_; // isolation calculated with only the neutral hadron PFCandidates
      Float_t pfPhotonIso_; // Returns the isolation calculated with only the gamma PFCandidates
      
      Bool_t energyValid_;
      Bool_t matchesValid_;
      Bool_t isolationValid_;
      
      Int_t direction_; //  OutsideIn = -1, Undefined = 0, InsideOut = 1
      Int_t algo_;      //  binary => GlobalMuon=00010 , TrackerMuon=00100 , StandAloneMuon=01000 , CaloMuon=10000
      Int_t id_;        // MuonId coded in binary word id_ ==> TrackerMuonArbitrated=0000001 , AllArbitrated=0000010 , GlobalMuonPromptTight=0000100 ,
      // TMLastStationLoose=0001000 , TMLastStationTight=0010000 , TM2DCompatibilityLoose=0100000 , TM2DCompatibilityTight=1000000
      
      
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
      
      Int_t numberOfValidPixelHits_;     // Number of valid pixel hits
      Int_t numberOfValidTrackerHits_;   // Number of valid tracker hits (pixel+strip) - More than 1 hit per layer (even mono) is possible due to modules overlap
      Int_t pixelLayersWithMeasurement_; // Number of pixel layers with at least one valid hit
      Int_t stripLayersWithMeasurement_; // Number of strip layers with at least one valid hit
      
      Float_t d0_;                 // d0=-dxy
      Float_t d0Error_;            // error on d0_
      Float_t dsz_;                // dsz parameter
      Float_t dszError_;           // error on dsz_
      Float_t dB_;                 // distance to beamline
      Float_t normalizedChi2_;     // chi-squared divided by n.d.o.f. of track fit
      
      Float_t ptError_;            // needed ?  ptError()
      Float_t etaError_;           // needed ?  etaError()
      Float_t phiError_;           // needed ?  phiError()
      
      Float_t ip3DSignificance_;   // Significance of the impact parameter wrt to the selected primary vertex
      
      TLorentzVector innerTrack_;  // Tracker only
      TLorentzVector outerTrack_;  // Muon detector only
      TLorentzVector globalTrack_; // Tracker + Muon detector
      
      // Variables from pat::Muons
      Float_t ecalCandEnergy_;     // energy within the cone of DR=0.07 in the ECAL (CandEnergy of the ecalIsoDeposit)
      Float_t hcalCandEnergy_;     // energy within the cone of DR=1.0 in the HCAL (CandEnergy of the hcalIsoDeposit)
      
      
      ClassDef (TRootMuon,7);
      
};

#endif
