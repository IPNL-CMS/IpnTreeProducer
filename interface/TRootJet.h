#ifndef TRootJet_h
#define TRootJet_h

#include "../interface/TRootParticle.h"

using namespace std;

class TRootJet : public TRootParticle
{

   public:
      TRootJet() :
      TRootParticle()
      ,jetType_(0)
      ,nConstituents_(-9999)
      ,chargedMultiplicity_(-9999)
      ,n90_(-9999)
      ,n60_(-9999)
      ,jetArea_(-9999.)
      ,pileupEnergy_(-9999.)
      ,maxDistance_(-9999.)
      ,dR01EnergyFraction_(-9999.)
      ,dR02EnergyFraction_(-9999.)
      ,dR03EnergyFraction_(-9999.)
      ,dR04EnergyFraction_(-9999.)
      ,dR05EnergyFraction_(-9999.)
      ,ecalEnergyFraction_(-9999.)
      ,hcalEnergyFraction_(-9999.)
      ,CHF_(-9999.)
      ,NHF_(-9999.)
      ,CEF_(-9999.)
      ,NEF_(-9999.)
      ,chargedEnergyFraction_(-9999.)
      ,chargedBroadness_(-9999.)
      ,chargedBroadnessDR01_(-9999.)
      ,chargedBroadnessDR02_(-9999.)
      ,chargedBroadnessDR03_(-9999.)
      ,chargedBroadnessDR04_(-9999.)
      ,chargedBroadnessDR05_(-9999.)
      ,btag_trackCountingHighEff_(-9999.)
      ,btag_trackCountingHighPur_(-9999.)
      ,btag_jetProbability_(-9999.)  
      ,btag_soft_e_(-9999.)
      ,btag_soft_e_pt_(-9999.)
      ,btag_soft_e_ip_(-9999.)
      ,btag_soft_mu_(-9999.)
      ,btag_soft_mu_pt_(-9999.)
      ,btag_soft_mu_ip_(-9999.)    
      ,L0Correction_(-9999.)
      ,L1Correction_(-9999.)
      ,L2Correction_(-9999.)
      ,L3Correction_(-9999.)
      ,L4Correction_(-9999.)      
      ,L5gCorrection_(-9999.)
      ,L5udsCorrection_(-9999.)
      ,L5cCorrection_(-9999.)
      ,L5bCorrection_(-9999.)
      ,L6gCorrection_(-9999.)
      ,L6udsCorrection_(-9999.)
      ,L6cCorrection_(-9999.)
      ,L6bCorrection_(-9999.)
      ,L7gCorrection_(-9999.)
      ,L7udsCorrection_(-9999.)	
      ,L7cCorrection_(-9999.)
      ,L7bCorrection_(-9999.)
      ,sigmaEta_(-9999.)
      ,sigmaPhi_(-9999.)
      ,n90Hits_(-9999)
      ,restrictedEMF_(-9999.)
      ,fHPD_(-9999.)
      ,fRBX_(-9999.)
      ,genJetEnergy_(-9999.)
      ,genJetIndex_(-9999)
      ,genJet_(0)
      ,isTopJet_(false)
      {;}

      TRootJet(const TRootJet& jet) :
      TRootParticle(jet)
      ,jetType_(jet.jetType_)
      ,nConstituents_(jet.nConstituents_)
      ,chargedMultiplicity_(jet.chargedMultiplicity_)
      ,n90_(jet.n90_)
      ,n60_(jet.n60_)
      ,jetArea_(jet.jetArea_)
      ,pileupEnergy_(jet.pileupEnergy_)
      ,maxDistance_(jet.maxDistance_)
      ,dR01EnergyFraction_(jet.dR01EnergyFraction_)
      ,dR02EnergyFraction_(jet.dR02EnergyFraction_)
      ,dR03EnergyFraction_(jet.dR03EnergyFraction_)
      ,dR04EnergyFraction_(jet.dR04EnergyFraction_)
      ,dR05EnergyFraction_(jet.dR05EnergyFraction_)
      ,ecalEnergyFraction_(jet.ecalEnergyFraction_)
      ,hcalEnergyFraction_(jet.hcalEnergyFraction_)
      ,CHF_(jet.CHF_)
      ,NHF_(jet.NHF_)
      ,CEF_(jet.CEF_)
      ,NEF_(jet.NEF_)
      ,chargedEnergyFraction_(jet.chargedEnergyFraction_)
      ,chargedBroadness_(jet.chargedBroadness_)
      ,chargedBroadnessDR01_(jet.chargedBroadnessDR01_)
      ,chargedBroadnessDR02_(jet.chargedBroadnessDR02_)
      ,chargedBroadnessDR03_(jet.chargedBroadnessDR03_)
      ,chargedBroadnessDR04_(jet.chargedBroadnessDR04_)
      ,chargedBroadnessDR05_(jet.chargedBroadnessDR05_)
      ,btag_trackCountingHighEff_(jet.btag_trackCountingHighEff_)
      ,btag_trackCountingHighPur_(jet.btag_trackCountingHighPur_)
      ,btag_jetProbability_(jet.btag_jetProbability_)
      ,btag_soft_e_(jet.btag_soft_e_)
      ,btag_soft_e_pt_(jet.btag_soft_e_pt_)
      ,btag_soft_e_ip_(jet.btag_soft_e_ip_)
      ,btag_soft_mu_(jet.btag_soft_mu_)
      ,btag_soft_mu_pt_(jet.btag_soft_mu_pt_)
      ,btag_soft_mu_ip_(jet.btag_soft_mu_ip_)
      ,L0Correction_(jet.L0Correction_)
      ,L1Correction_(jet.L1Correction_)
      ,L2Correction_(jet.L2Correction_)
      ,L3Correction_(jet.L3Correction_)
      ,L4Correction_(jet.L4Correction_)
      ,L5gCorrection_(jet.L5gCorrection_)
      ,L5udsCorrection_(jet.L5udsCorrection_)
      ,L5cCorrection_(jet.L5cCorrection_)
      ,L5bCorrection_(jet.L5bCorrection_)
      ,L6gCorrection_(jet.L6gCorrection_)
      ,L6udsCorrection_(jet.L6udsCorrection_)
      ,L6cCorrection_(jet.L6cCorrection_)
      ,L6bCorrection_(jet.L6bCorrection_)
      ,L7gCorrection_(jet.L7gCorrection_)
      ,L7udsCorrection_(jet.L7udsCorrection_)	
      ,L7cCorrection_(jet.L7cCorrection_)
      ,L7bCorrection_(jet.L7bCorrection_)
      ,sigmaEta_(jet.sigmaEta_)
      ,sigmaPhi_(jet.sigmaPhi_)
      ,n90Hits_(jet.n90Hits_)
      ,restrictedEMF_(jet.restrictedEMF_)
      ,fHPD_(jet.fHPD_)
      ,fRBX_(jet.fRBX_)
      ,genJetEnergy_(jet.genJetEnergy_)
      ,genJetIndex_(jet.genJetIndex_)
      ,genJet_(jet.genJet_)
      ,isTopJet_(jet.isTopJet_)
      {;}

      TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
      TRootParticle(px,py,pz,e)
      ,jetType_(0)
      ,nConstituents_(-9999)
      ,chargedMultiplicity_(-9999)
      ,n90_(-9999)
      ,n60_(-9999)
      ,jetArea_(-9999.)
      ,pileupEnergy_(-9999.)
      ,maxDistance_(-9999.)
      ,dR01EnergyFraction_(-9999.)
      ,dR02EnergyFraction_(-9999.)
      ,dR03EnergyFraction_(-9999.)
      ,dR04EnergyFraction_(-9999.)
      ,dR05EnergyFraction_(-9999.)
      ,ecalEnergyFraction_(-9999.)
      ,hcalEnergyFraction_(-9999.)
      ,CHF_(-9999.)
      ,NHF_(-9999.)
      ,CEF_(-9999.)
      ,NEF_(-9999.)
      ,chargedEnergyFraction_(-9999.)
      ,chargedBroadness_(-9999.)
      ,chargedBroadnessDR01_(-9999.)
      ,chargedBroadnessDR02_(-9999.)
      ,chargedBroadnessDR03_(-9999.)
      ,chargedBroadnessDR04_(-9999.)
      ,chargedBroadnessDR05_(-9999.)
      ,btag_trackCountingHighEff_(-9999.)
      ,btag_trackCountingHighPur_(-9999.)
      ,btag_jetProbability_(-9999.)
      ,btag_soft_e_(-9999.)
      ,btag_soft_e_pt_(-9999.)
      ,btag_soft_e_ip_(-9999.)
      ,btag_soft_mu_(-9999.)
      ,btag_soft_mu_pt_(-9999.)
      ,btag_soft_mu_ip_(-9999.)
      ,L0Correction_(-9999.)
      ,L1Correction_(-9999.)
      ,L2Correction_(-9999.)
      ,L3Correction_(-9999.)
      ,L4Correction_(-9999.)
      ,L5gCorrection_(-9999.)
      ,L5udsCorrection_(-9999.)
      ,L5cCorrection_(-9999.)
      ,L5bCorrection_(-9999.)
      ,L6gCorrection_(-9999.)
      ,L6udsCorrection_(-9999.)
      ,L6cCorrection_(-9999.)
      ,L6bCorrection_(-9999.)
      ,L7gCorrection_(-9999.)
      ,L7udsCorrection_(-9999.)	
      ,L7cCorrection_(-9999.)
      ,L7bCorrection_(-9999.)
      ,sigmaEta_(-9999.)
      ,sigmaPhi_(-9999.)
      ,n90Hits_(-9999)
      ,restrictedEMF_(-9999.)
      ,fHPD_(-9999.)
      ,fRBX_(-9999.)
      ,genJetEnergy_(-9999.)
      ,genJetIndex_(-9999)
      ,genJet_(0)
      ,isTopJet_(false)
      {;}

      TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
      ,jetType_(0)
      ,nConstituents_(-9999)
      ,chargedMultiplicity_(-9999)
      ,n90_(-9999)
      ,n60_(-9999)
      ,jetArea_(-9999.)
      ,pileupEnergy_(-9999.)
      ,maxDistance_(-9999.)
      ,dR01EnergyFraction_(-9999.)
      ,dR02EnergyFraction_(-9999.)
      ,dR03EnergyFraction_(-9999.)
      ,dR04EnergyFraction_(-9999.)
      ,dR05EnergyFraction_(-9999.)
      ,ecalEnergyFraction_(-9999.)
      ,hcalEnergyFraction_(-9999.)
      ,CHF_(-9999.)
      ,NHF_(-9999.)
      ,CEF_(-9999.)
      ,NEF_(-9999.)
      ,chargedEnergyFraction_(-9999.)
      ,chargedBroadness_(-9999.)
      ,chargedBroadnessDR01_(-9999.)
      ,chargedBroadnessDR02_(-9999.)
      ,chargedBroadnessDR03_(-9999.)
      ,chargedBroadnessDR04_(-9999.)
      ,chargedBroadnessDR05_(-9999.)
      ,btag_trackCountingHighEff_(-9999.)
      ,btag_trackCountingHighPur_(-9999.)
      ,btag_jetProbability_(-9999.)
      ,btag_soft_e_(-9999.)
      ,btag_soft_e_pt_(-9999.)
      ,btag_soft_e_ip_(-9999.)
      ,btag_soft_mu_(-9999.)
      ,btag_soft_mu_pt_(-9999.)
      ,btag_soft_mu_ip_(-9999.)
      ,L0Correction_(-9999.)
      ,L1Correction_(-9999.)
      ,L2Correction_(-9999.)
      ,L3Correction_(-9999.)
      ,L4Correction_(-9999.)
      ,L5gCorrection_(-9999.)
      ,L5udsCorrection_(-9999.)
      ,L5cCorrection_(-9999.)
      ,L5bCorrection_(-9999.)
      ,L6gCorrection_(-9999.)
      ,L6udsCorrection_(-9999.)
      ,L6cCorrection_(-9999.)
      ,L6bCorrection_(-9999.)
      ,L7gCorrection_(-9999.)
      ,L7udsCorrection_(-9999.)	
      ,L7cCorrection_(-9999.)
      ,L7bCorrection_(-9999.)
      ,sigmaEta_(-9999.)
      ,sigmaPhi_(-9999.)
      ,n90Hits_(-9999)
      ,restrictedEMF_(-9999.)
      ,fHPD_(-9999.)
      ,fRBX_(-9999.)
      ,genJetEnergy_(-9999.)
      ,genJetIndex_(-9999)
      ,genJet_(0)
      ,isTopJet_(false)
      {;}

      TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
      ,jetType_(0)
      ,nConstituents_(-9999)
      ,chargedMultiplicity_(-9999)
      ,n90_(-9999)
      ,n60_(-9999)
      ,jetArea_(-9999.)
      ,pileupEnergy_(-9999.)
      ,maxDistance_(-9999.)
      ,dR01EnergyFraction_(-9999.)
      ,dR02EnergyFraction_(-9999.)
      ,dR03EnergyFraction_(-9999.)
      ,dR04EnergyFraction_(-9999.)
      ,dR05EnergyFraction_(-9999.)
      ,ecalEnergyFraction_(-9999.)
      ,hcalEnergyFraction_(-9999.)
      ,chargedEnergyFraction_(-9999.)
      ,chargedBroadness_(-9999.)
      ,chargedBroadnessDR01_(-9999.)
      ,chargedBroadnessDR02_(-9999.)
      ,chargedBroadnessDR03_(-9999.)
      ,chargedBroadnessDR04_(-9999.)
      ,chargedBroadnessDR05_(-9999.)
      ,btag_trackCountingHighEff_(-9999.)
      ,btag_trackCountingHighPur_(-9999.)
      ,btag_jetProbability_(-9999.)
      ,btag_soft_e_(-9999.)
      ,btag_soft_e_pt_(-9999.)
      ,btag_soft_e_ip_(-9999.)
      ,btag_soft_mu_(-9999.)
      ,btag_soft_mu_pt_(-9999.)
      ,btag_soft_mu_ip_(-9999.)
      ,L0Correction_(-9999.)
      ,L1Correction_(-9999.)
      ,L2Correction_(-9999.)
      ,L3Correction_(-9999.)
      ,L4Correction_(-9999.)
      ,L5gCorrection_(-9999.)
      ,L5udsCorrection_(-9999.)
      ,L5cCorrection_(-9999.)
      ,L5bCorrection_(-9999.)
      ,L6gCorrection_(-9999.)
      ,L6udsCorrection_(-9999.)
      ,L6cCorrection_(-9999.)
      ,L6bCorrection_(-9999.)
      ,L7gCorrection_(-9999.)
      ,L7udsCorrection_(-9999.)	
      ,L7cCorrection_(-9999.)
      ,L7bCorrection_(-9999.)
      ,sigmaEta_(-9999.)
      ,sigmaPhi_(-9999.)
      ,n90Hits_(-9999)
      ,restrictedEMF_(-9999.)
      ,fHPD_(-9999.)
      ,fRBX_(-9999.)
      ,genJetEnergy_(-9999.)
      ,genJetIndex_(-9999)
      ,genJet_(0)
      ,isTopJet_(false)
      {;}

      TRootJet(const TLorentzVector &momentum) :
      TRootParticle(momentum)
      ,jetType_(0)
      ,nConstituents_(-9999)
      ,chargedMultiplicity_(-9999)
      ,n90_(-9999)
      ,n60_(-9999)
      ,jetArea_(-9999.)
      ,pileupEnergy_(-9999.)
      ,maxDistance_(-9999.)
      ,dR01EnergyFraction_(-9999.)
      ,dR02EnergyFraction_(-9999.)
      ,dR03EnergyFraction_(-9999.)
      ,dR04EnergyFraction_(-9999.)
      ,dR05EnergyFraction_(-9999.)
      ,ecalEnergyFraction_(-9999.)
      ,hcalEnergyFraction_(-9999.)
      ,CHF_(-9999.)
      ,NHF_(-9999.)
      ,CEF_(-9999.)
      ,NEF_(-9999.)
      ,chargedEnergyFraction_(-9999.)
      ,chargedBroadness_(-9999.)
      ,chargedBroadnessDR01_(-9999.)
      ,chargedBroadnessDR02_(-9999.)
      ,chargedBroadnessDR03_(-9999.)
      ,chargedBroadnessDR04_(-9999.)
      ,chargedBroadnessDR05_(-9999.)
      ,btag_trackCountingHighEff_(-9999.)
      ,btag_trackCountingHighPur_(-9999.)
      ,btag_jetProbability_(-9999.)
      ,btag_soft_e_(-9999.)
      ,btag_soft_e_pt_(-9999.)
      ,btag_soft_e_ip_(-9999.)
      ,btag_soft_mu_(-9999.)
      ,btag_soft_mu_pt_(-9999.)
      ,btag_soft_mu_ip_(-9999.)
      ,L0Correction_(-9999.)
      ,L1Correction_(-9999.)
      ,L2Correction_(-9999.)
      ,L3Correction_(-9999.)
      ,L4Correction_(-9999.)
      ,L5gCorrection_(-9999.)
      ,L5udsCorrection_(-9999.)
      ,L5cCorrection_(-9999.)
      ,L5bCorrection_(-9999.)
      ,L6gCorrection_(-9999.)
      ,L6udsCorrection_(-9999.)
      ,L6cCorrection_(-9999.)
      ,L6bCorrection_(-9999.)
      ,L7gCorrection_(-9999.)
      ,L7udsCorrection_(-9999.)	
      ,L7cCorrection_(-9999.)
      ,L7bCorrection_(-9999.)
      ,sigmaEta_(-9999.)
      ,sigmaPhi_(-9999.)
      ,n90Hits_(-9999)
      ,restrictedEMF_(-9999.)
      ,fHPD_(-9999.)
      ,fRBX_(-9999.)
      ,genJetEnergy_(-9999.)
      ,genJetIndex_(-9999)
      ,genJet_(0)
      ,isTopJet_(false)
      {;}

      TRootJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
      TRootParticle(momentum, vertex, type, charge)
      ,jetType_(0)
      ,nConstituents_(-9999)
      ,chargedMultiplicity_(-9999)
      ,n90_(-9999)
      ,n60_(-9999)
      ,jetArea_(-9999.)
      ,pileupEnergy_(-9999.)
      ,maxDistance_(-9999.)
      ,dR01EnergyFraction_(-9999.)
      ,dR02EnergyFraction_(-9999.)
      ,dR03EnergyFraction_(-9999.)
      ,dR04EnergyFraction_(-9999.)
      ,dR05EnergyFraction_(-9999.)
      ,ecalEnergyFraction_(-9999.)
      ,hcalEnergyFraction_(-9999.)
      ,CHF_(-9999.)
      ,NHF_(-9999.)
      ,CEF_(-9999.)
      ,NEF_(-9999.)
      ,chargedEnergyFraction_(-9999.)
      ,chargedBroadness_(-9999.)
      ,chargedBroadnessDR01_(-9999.)
      ,chargedBroadnessDR02_(-9999.)
      ,chargedBroadnessDR03_(-9999.)
      ,chargedBroadnessDR04_(-9999.)
      ,chargedBroadnessDR05_(-9999.)
      ,btag_trackCountingHighEff_(-9999.)
      ,btag_trackCountingHighPur_(-9999.)
      ,btag_jetProbability_(-9999.)
      ,btag_soft_e_(-9999.)
      ,btag_soft_e_pt_(-9999.)
      ,btag_soft_e_ip_(-9999.)
      ,btag_soft_mu_(-9999.)
      ,btag_soft_mu_pt_(-9999.)
      ,btag_soft_mu_ip_(-9999.)
      ,L0Correction_(-9999.)
      ,L1Correction_(-9999.)
      ,L2Correction_(-9999.)
      ,L3Correction_(-9999.)
      ,L4Correction_(-9999.)
      ,L5gCorrection_(-9999.)
      ,L5udsCorrection_(-9999.)
      ,L5cCorrection_(-9999.)
      ,L5bCorrection_(-9999.)
      ,L6gCorrection_(-9999.)
      ,L6udsCorrection_(-9999.)
      ,L6cCorrection_(-9999.)
      ,L6bCorrection_(-9999.)
      ,L7gCorrection_(-9999.)
      ,L7udsCorrection_(-9999.)	
      ,L7cCorrection_(-9999.)
      ,L7bCorrection_(-9999.)
      ,sigmaEta_(-9999.)
      ,sigmaPhi_(-9999.)
      ,n90Hits_(-9999)
      ,restrictedEMF_(-9999.)
      ,fHPD_(-9999.)
      ,fRBX_(-9999.)
      ,genJetEnergy_(-9999.)
      ,genJetIndex_(-9999)
      ,genJet_(0)
      ,isTopJet_(false)
      {;}

      ~TRootJet() {;}


      Int_t jetType() const { return jetType_; }
      Int_t nConstituents() const { return nConstituents_; }
      Int_t chargedMultiplicity() const { return chargedMultiplicity_; }
      Int_t n90() const { return n90_; }
      Int_t n60() const { return n60_; }
      Float_t jetArea() const { return jetArea_; }
      Float_t pileupEnergy() const { return pileupEnergy_; }
      Float_t maxDistance() const { return maxDistance_; }
      Float_t dR01EnergyFraction() const { return dR01EnergyFraction_; }
      Float_t dR02EnergyFraction() const { return dR02EnergyFraction_; }
      Float_t dR03EnergyFraction() const { return dR03EnergyFraction_; }
      Float_t dR04EnergyFraction() const { return dR04EnergyFraction_; }
      Float_t dR05EnergyFraction() const { return dR05EnergyFraction_; }
      Float_t ecalEnergyFraction() const { return ecalEnergyFraction_; }
      Float_t hcalEnergyFraction() const { return hcalEnergyFraction_; }
      Float_t CHF() const { return CHF_; }
      Float_t NHF() const { return NHF_; }
      Float_t CEF() const { return CEF_; }
      Float_t NEF() const { return NEF_; }
      Float_t chargedEnergyFraction() const { return chargedEnergyFraction_; }
      Float_t chargedBroadness() const { return chargedBroadness_; }
      Float_t chargedBroadnessDR01() const { return chargedBroadnessDR01_; }
      Float_t chargedBroadnessDR02() const { return chargedBroadnessDR02_; }
      Float_t chargedBroadnessDR03() const { return chargedBroadnessDR03_; }
      Float_t chargedBroadnessDR04() const { return chargedBroadnessDR04_; }
      Float_t chargedBroadnessDR05() const { return chargedBroadnessDR05_; }
      Float_t btag_trackCountingHighEff() const { return btag_trackCountingHighEff_; }
      Float_t btag_trackCountingHighPur() const { return btag_trackCountingHighPur_; }
      Float_t btag_jetProbability() const { return btag_jetProbability_; }
      Float_t btag_soft_e() const { return btag_soft_e_; }
      Float_t btag_soft_e_pt() const { return btag_soft_e_pt_; }
      Float_t btag_soft_e_ip() const { return btag_soft_e_ip_; }
      Float_t btag_soft_mu() const { return btag_soft_mu_; }
      Float_t btag_soft_mu_pt() const { return btag_soft_mu_pt_; }
      Float_t btag_soft_mu_ip() const { return btag_soft_mu_ip_; }
		
      Float_t L0Correction() const { return L0Correction_; }
      Float_t L1Correction() const { return L1Correction_; }
      Float_t L2Correction() const { return L2Correction_; }
      Float_t L3Correction() const { return L3Correction_; }
      Float_t L4Correction() const { return L4Correction_; }
      
      Float_t L5gCorrection() const { return L5gCorrection_; }
      Float_t L5udsCorrection() const { return L5udsCorrection_; }
      Float_t L5cCorrection() const { return L5cCorrection_; }
      Float_t L5bCorrection() const { return L5bCorrection_; }
      
      Float_t L6gCorrection() const { return L6gCorrection_; }
      Float_t L6udsCorrection() const { return L6udsCorrection_; }
      Float_t L6cCorrection() const { return L6cCorrection_; }
      Float_t L6bCorrection() const { return L6bCorrection_; }
      
      Float_t L7gCorrection() const { return L7gCorrection_; }
      Float_t L7udsCorrection() const { return L7udsCorrection_; }
      Float_t L7cCorrection() const { return L7cCorrection_; }
      Float_t L7bCorrection() const { return L7bCorrection_; }
      
      Double_t sigmaEta() const { return sigmaEta_; } 
      Double_t sigmaPhi() const { return sigmaPhi_; } 
      Int_t n90Hits() const { return n90Hits_; }
      Double_t restrictedEMF() const {return restrictedEMF_;}
      Double_t fHPD() const {return fHPD_;}
      Double_t fRBX() const {return fRBX_;}
      
      Double_t genJetEnergy() const { return genJetEnergy_; }
      Int_t genJetIndex() const { return genJetIndex_; }
      TRootParticle* genParton() const { return genParticle(); }
      TRootParticle* genJet() const { return (TRootParticle*) genJet_.GetObject() ;}
      Bool_t isTopJet() const { return isTopJet_; }

      virtual TString typeName() const { return "TRootJet"; }


      void setJetType(Int_t jetType) { jetType_ = jetType; }
      void setNConstituents(Int_t nConstituents) { nConstituents_ = nConstituents; }
      void setChargedMultiplicity(Int_t chargedMultiplicity) { chargedMultiplicity_ = chargedMultiplicity; }
      void setN90(Int_t n90) { n90_ = n90; }
      void setN60(Int_t n60) { n60_ = n60; }
      void setJetArea(Float_t jetArea) { jetArea_ = jetArea; }
      void setPileupEnergy(Float_t pileupEnergy) { pileupEnergy_ = pileupEnergy; }
      void setMaxDistance(Float_t maxDistance) { maxDistance_ = maxDistance; }
      void setDR01EnergyFraction(Float_t dR01EnergyFraction) { dR01EnergyFraction_ = dR01EnergyFraction; }
      void setDR02EnergyFraction(Float_t dR02EnergyFraction) { dR02EnergyFraction_ = dR02EnergyFraction; }
      void setDR03EnergyFraction(Float_t dR03EnergyFraction) { dR03EnergyFraction_ = dR03EnergyFraction; }
      void setDR04EnergyFraction(Float_t dR04EnergyFraction) { dR04EnergyFraction_ = dR04EnergyFraction; }
      void setDR05EnergyFraction(Float_t dR05EnergyFraction) { dR05EnergyFraction_ = dR05EnergyFraction; }
      void setEcalEnergyFraction(Float_t ecalEnergyFraction) { ecalEnergyFraction_ = ecalEnergyFraction; }
      void setHcalEnergyFraction(Float_t hcalEnergyFraction) { hcalEnergyFraction_ = hcalEnergyFraction; }
      void setCHF(Float_t CHF) { CHF_ = CHF; }
      void setNHF(Float_t NHF) { NHF_ = NHF; }
      void setCEF(Float_t CEF) { CEF_ = CEF; }
      void setNEF(Float_t NEF) { NEF_ = NEF; }
      void setChargedEnergyFraction(Float_t chargedEnergyFraction) { chargedEnergyFraction_ = chargedEnergyFraction; }
      void setChargedBroadness(Float_t chargedBroadness) { chargedBroadness_ = chargedBroadness; }
      void setChargedBroadnessDR01(Float_t chargedBroadnessDR01) { chargedBroadnessDR01_ = chargedBroadnessDR01; }
      void setChargedBroadnessDR02(Float_t chargedBroadnessDR02) { chargedBroadnessDR02_ = chargedBroadnessDR02; }
      void setChargedBroadnessDR03(Float_t chargedBroadnessDR03) { chargedBroadnessDR03_ = chargedBroadnessDR03; }
      void setChargedBroadnessDR04(Float_t chargedBroadnessDR04) { chargedBroadnessDR04_ = chargedBroadnessDR04; }
      void setChargedBroadnessDR05(Float_t chargedBroadnessDR05) { chargedBroadnessDR05_ = chargedBroadnessDR05; }
      void setBtag_trackCountingHighEff(Float_t btag_trackCountingHighEff) { btag_trackCountingHighEff_ = btag_trackCountingHighEff; }
      void setBtag_trackCountingHighPur(Float_t btag_trackCountingHighPur) { btag_trackCountingHighPur_ = btag_trackCountingHighPur; }
      void setBtag_jetProbability(Float_t btag_jetProbability) { btag_jetProbability_ = btag_jetProbability; }
      void setBtag_soft_e(Float_t btag_soft_e) { btag_soft_e_ = btag_soft_e; }
      void setBtag_soft_e_pt(Float_t btag_soft_e_pt) { btag_soft_e_pt_ = btag_soft_e_pt; }
      void setBtag_soft_e_ip(Float_t btag_soft_e_ip) { btag_soft_e_ip_ = btag_soft_e_ip; }
      void setBtag_soft_mu(Float_t btag_soft_mu) { btag_soft_mu_ = btag_soft_mu; }
      void setBtag_soft_mu_pt(Float_t btag_soft_mu_pt) { btag_soft_mu_pt_ = btag_soft_mu_pt; }
      void setBtag_soft_mu_ip(Float_t btag_soft_mu_ip) { btag_soft_mu_ip_ = btag_soft_mu_ip; }
		
      void setL0Correction(Float_t L0Correction) { L0Correction_ = L0Correction; }
      void setL1Correction(Float_t L1Correction) { L1Correction_ = L1Correction; }
      void setL2Correction(Float_t L2Correction) { L2Correction_ = L2Correction; }
      void setL3Correction(Float_t L3Correction) { L3Correction_ = L3Correction; }
      void setL4Correction(Float_t L4Correction) { L4Correction_ = L4Correction; }
      
      void setL5gCorrection(Float_t L5gCorrection) { L5gCorrection_ = L5gCorrection; }
      void setL5udsCorrection(Float_t L5udsCorrection) { L5udsCorrection_ = L5udsCorrection; }
      void setL5cCorrection(Float_t L5cCorrection) { L5cCorrection_ = L5cCorrection; }
      void setL5bCorrection(Float_t L5bCorrection) { L5bCorrection_ = L5bCorrection; }
      
      void setL6gCorrection(Float_t L6gCorrection) { L6gCorrection_ = L6gCorrection; }
      void setL6udsCorrection(Float_t L6udsCorrection) { L6udsCorrection_ = L6udsCorrection; }
      void setL6cCorrection(Float_t L6cCorrection) { L6cCorrection_ = L6cCorrection; }
      void setL6bCorrection(Float_t L6bCorrection) { L6bCorrection_ = L6bCorrection; }
      
      void setL7gCorrection(Float_t L7gCorrection) { L7gCorrection_ = L7gCorrection; }
      void setL7udsCorrection(Float_t L7udsCorrection) { L7udsCorrection_ = L7udsCorrection; }
      void setL7cCorrection(Float_t L7cCorrection) { L7cCorrection_ = L7cCorrection; }
      void setL7bCorrection(Float_t L7bCorrection) { L7bCorrection_ = L7bCorrection; }
      
      void setSigmaEta(Double_t sigmaEta) { sigmaEta_ = sigmaEta; }
      void setSigmaPhi(Double_t sigmaPhi) { sigmaPhi_ = sigmaPhi; }
      void setN90Hits(Int_t n90Hits) { n90Hits_ = n90Hits; }
      void setRestrictedEMF(Double_t restrictedEMF) {restrictedEMF_ = restrictedEMF; } 
      void setFHPD(Double_t fHPD) {fHPD_ = fHPD; } 
      void setFRBX(Double_t fRBX) {fRBX_ = fRBX; }
		
      void setGenJetEnergy(Double_t genJetEnergy) { genJetEnergy_ = genJetEnergy; }
      void setGenJetIndex(Int_t genJetIndex) { genJetIndex_ = genJetIndex; }
      //void setGenParton(TObject* genParton) { genParton_ = genParton; }
      void setGenJet(TObject* genJet) { genJet_ = genJet; }
      void setIsTopJet(Bool_t isTopJet) { isTopJet_ = isTopJet; }

      friend std::ostream& operator<< (std::ostream& stream, const TRootJet& jet) {
         stream << "TRootJet - Charge=" << setw(2) << jet.charge() << " (Et,eta,phi)=("<< setw(10) << jet.Et() <<","<< setw(10) << jet.Eta() <<","<< setw(10) << jet.Phi() << ")"
         << " vertex(x,y,z)=("<< jet.vx() <<","<< jet.vy() <<","<< jet.vz() << ")";
         return stream;
      };


  private:

     // Variables from reco::Jet
     Int_t jetType_;                     // 0 = Unknown ; 1 = CaloJet ; 2 = PFJet
     Int_t nConstituents_;               // Number of constituents of the jet (calotowers for CaloJet / PFParticles for PFJet)
     Int_t chargedMultiplicity_;         // Number of tracks associated to the jet. Not available for reco::CaloJet
     Int_t n90_;                         // Number of constituents of the jet carrying 90% of tje jet energy
     Int_t n60_;                         // Number of constituents of the jet carrying 60% of tje jet energy
     Float_t jetArea_;                   // Jet area
     Float_t pileupEnergy_;              // Pileup energy contribution
     Float_t maxDistance_;               // Maximum distance from jet to constituent
     Float_t dR01EnergyFraction_;        // Fraction of the jet energy in a DeltaR=0.1 cone
     Float_t dR02EnergyFraction_;        // Fraction of the jet energy in a DeltaR=0.1 cone
     Float_t dR03EnergyFraction_;        // Fraction of the jet energy in a DeltaR=0.1 cone
     Float_t dR04EnergyFraction_;        // Fraction of the jet energy in a DeltaR=0.1 cone
     Float_t dR05EnergyFraction_;        // Fraction of the jet energy in a DeltaR=0.1 cone
     Float_t ecalEnergyFraction_;        // ECAL Energy Fraction
     Float_t hcalEnergyFraction_;        // HCAL Energy Fraction
     Float_t CHF_;        // charged hadronic Fraction
     Float_t NHF_;        // neutral hadronic Fraction
     Float_t CEF_;        // charged em Fraction
     Float_t NEF_;        // neutral em Fraction
     Float_t chargedEnergyFraction_;     // Charged Energy Fraction - Only available for reco::PFJet


     // Variables from pat::Jet
     Float_t chargedBroadness_;          // DR of the cone containing 75% of the jet charged energy
     Float_t chargedBroadnessDR01_;      // charged energy in a cone DR=0.1 / jet charged energy
     Float_t chargedBroadnessDR02_;      // charged energy in a cone DR=0.2 / jet charged energy
     Float_t chargedBroadnessDR03_;      // charged energy in a cone DR=0.3 / jet charged energy
     Float_t chargedBroadnessDR04_;      // charged energy in a cone DR=0.4 / jet charged energy
     Float_t chargedBroadnessDR05_;      // charged energy in a cone DR=0.5 / jet charged energy
     Float_t btag_trackCountingHighEff_; // b-tagging ; Track counting High Efficiency
     Float_t btag_trackCountingHighPur_; // b-tagging ; Track counting High Purity
     Float_t btag_jetProbability_;       // b-tagging ; Jet probability
     Float_t btag_soft_e_;
     Float_t btag_soft_e_pt_;
     Float_t btag_soft_e_ip_;
     Float_t btag_soft_mu_;
     Float_t btag_soft_mu_pt_;
     Float_t btag_soft_mu_ip_;
	  
     Float_t L0Correction_;               // correction factor for L0 level
     Float_t L1Correction_;		  // correction factor for L1 level
     Float_t L2Correction_;		  // correction factor for L2 level
     Float_t L3Correction_;		  // correction factor for L3 level
     Float_t L4Correction_;		  // correction factor for L4 level
     
     Float_t L5gCorrection_;		 // correction factor for L5g level
     Float_t L5udsCorrection_;		 // correction factor for L5uds level
     Float_t L5cCorrection_;		 // correction factor for L5c level
     Float_t L5bCorrection_;		 // correction factor for L5b level
     
     Float_t L6gCorrection_;		 // correction factor for L6g level
     Float_t L6udsCorrection_;		 // correction factor for L6uds level
     Float_t L6cCorrection_;		 // correction factor for L6c level
     Float_t L6bCorrection_;		 // correction factor for L6b level
     
     Float_t L7gCorrection_;		 // correction factor for L7g level
     Float_t L7udsCorrection_;		 // correction factor for L7uds level
     Float_t L7cCorrection_;		 // correction factor for L7c level
     Float_t L7bCorrection_;		 // correction factor for L7b level
     
     Double_t sigmaEta_;
     Double_t sigmaPhi_;
     Int_t n90Hits_;
     Double_t restrictedEMF_;
     Double_t fHPD_;
     Double_t fRBX_;
	  
     Double_t genJetEnergy_;             // energy of matched genJet
     Int_t genJetIndex_; 	              // index of matched genJet in genJets TCloneArray
     TRef genJet_;                       // reference to matched genJet (kept in genJets branch)

     Bool_t isTopJet_;                   // Is parton matched to the jet a decay product of the top quark ?

     ClassDef (TRootJet,4);
     };

     #endif
