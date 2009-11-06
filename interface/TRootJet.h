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
      ,bCorrection_(-9999.)
      ,cCorrection_(-9999.)
      ,udsCorrection_(-9999.)
      ,gCorrection_(-9999.)
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
      ,bCorrection_(jet.bCorrection_)
      ,cCorrection_(jet.cCorrection_)
      ,udsCorrection_(jet.udsCorrection_)
      ,gCorrection_(jet.gCorrection_)
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
      ,bCorrection_(-9999.)
      ,cCorrection_(-9999.)
      ,udsCorrection_(-9999.)
      ,gCorrection_(-9999.)
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
      ,bCorrection_(-9999.)
      ,cCorrection_(-9999.)
      ,udsCorrection_(-9999.)
      ,gCorrection_(-9999.)
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
      ,bCorrection_(-9999.)
      ,cCorrection_(-9999.)
      ,udsCorrection_(-9999.)
      ,gCorrection_(-9999.)
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
      ,bCorrection_(-9999.)
      ,cCorrection_(-9999.)
      ,udsCorrection_(-9999.)
      ,gCorrection_(-9999.)
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
      ,bCorrection_(-9999.)
      ,cCorrection_(-9999.)
      ,udsCorrection_(-9999.)
      ,gCorrection_(-9999.)
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
      Float_t bCorrection() const { return bCorrection_; }
      Float_t cCorrection() const { return cCorrection_; }
      Float_t udsCorrection() const { return udsCorrection_; }
      Float_t gCorrection() const { return gCorrection_; }
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
      void setBCorrection(Float_t bCorrection) { bCorrection_ = bCorrection; }
      void setCCorrection(Float_t cCorrection) { cCorrection_ = cCorrection; }
      void setUDSCorrection(Float_t udsCorrection) { udsCorrection_ = udsCorrection; }
      void setGCorrection(Float_t gCorrection) { gCorrection_ = gCorrection; }
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
     Float_t bCorrection_;               // correction factor for b hypothesis
     Float_t cCorrection_;               // correction factor for c hypothesis
     Float_t udsCorrection_;             // correction factor for uds hypothesis
     Float_t gCorrection_;               // correction factor for gluon hypothesis

     Double_t genJetEnergy_;             // energy of matched genJet
     Int_t genJetIndex_; 	              // index of matched genJet in genJets TCloneArray
     TRef genJet_;                       // reference to matched genJet (kept in genJets branch)

     Bool_t isTopJet_;                   // Is parton matched to the jet a decay product of the top quark ?

     ClassDef (TRootJet,2);
     };

     #endif
