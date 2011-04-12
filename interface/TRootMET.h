#ifndef TRootMET_h
#define TRootMET_h

#include "../interface/TRootParticle.h"

using namespace std;

class TRootMET : public TRootParticle
{
   
public:
   
   TRootMET() :
   TRootParticle()
   ,maxEtInEmTowers_(0.)
   ,maxEtInHadTowers_(0.)
   ,hadEtInHO_(0.)
   ,hadEtInHB_(0.)
   ,hadEtInHF_(0.)
   ,hadEtInHE_(0.)
   ,emEtInEB_(0.)
   ,emEtInEE_(0.)
   ,emEtInHF_(0.)
   ,etFractionHadronic_(0.)
   ,etFractionEm_(0.)
   ,metSignificance_(0.)
   ,caloMETInpHF_(0.)
   ,caloMETInmHF_(0.)
   ,caloSETInpHF_(0.)
   ,caloSETInmHF_(0.)
   ,caloMETPhiInpHF_(0.)
   ,caloMETPhiInmHF_(0.)
   ,uncorrectedPhiALL_(-9999.)
   ,uncorrectedPtALL_(-1.)
   ,corExALL_(-9999.)
   ,corEyALL_(-9999.)
   ,corSumEtALL_(-9999.)
   ,uncorrectedPhiJES_(-9999.)
   ,uncorrectedPtJES_(-1.)
   ,corExJES_(-9999.)
   ,corEyJES_(-9999.)
   ,corSumEtJES_(-9999.)
   ,uncorrectedPhiMUON_(-9999.)
   ,uncorrectedPtMUON_(-1.)
   ,corExMUON_(-9999.)
   ,corEyMUON_(-9999.)
   ,corSumEtMUON_(-9999.)
   ,neutralHadEtFraction_(0.)
   ,neutralHadEt_ (0.)
   ,chargedHadEtFraction_(0.)
   ,chargedHadEt_(0.)
   ,neutralEMEtFraction_(0.)
   ,neutralEMEt_ (0.)
   ,chargedEMEtFraction_(0.)
   ,chargedEMEt_(0.)
   ,muonEtFraction_(0.)
   ,muonEt_(0.)
   ,type6EtFraction_(0.)
   ,type6Et_(0.)
   ,type7EtFraction_(0.)
   ,type7Et_(0.)
   ,sumEt_(0.)
   {;}
   
   TRootMET(const TRootMET& met) :
   TRootParticle(met)
   ,maxEtInEmTowers_(met.maxEtInEmTowers_)
   ,maxEtInHadTowers_(met.maxEtInHadTowers_)
   ,hadEtInHO_(met.hadEtInHO_)
   ,hadEtInHB_(met.hadEtInHB_)
   ,hadEtInHF_(met.hadEtInHF_)
   ,hadEtInHE_(met.hadEtInHE_)
   ,emEtInEB_(met.emEtInEB_)
   ,emEtInEE_(met.emEtInEE_)
   ,emEtInHF_(met.emEtInHF_)
   ,etFractionHadronic_(met.etFractionHadronic_)
   ,etFractionEm_(met.etFractionEm_)
   ,metSignificance_(met.metSignificance_)
   ,caloMETInpHF_(met.caloMETInpHF_)
   ,caloMETInmHF_(met.caloMETInmHF_)
   ,caloSETInpHF_(met.caloSETInpHF_)
   ,caloSETInmHF_(met.caloSETInmHF_)
   ,caloMETPhiInpHF_(met.caloMETPhiInpHF_)
   ,caloMETPhiInmHF_(met.caloMETPhiInmHF_)
   ,uncorrectedPhiALL_(met.uncorrectedPhiALL_)
   ,uncorrectedPtALL_(met.uncorrectedPtALL_)
   ,corExALL_(met.corExALL_)
   ,corEyALL_(met.corEyALL_)
   ,corSumEtALL_(met.corSumEtALL_)
   ,uncorrectedPhiJES_(met.uncorrectedPhiJES_)
   ,uncorrectedPtJES_(met.uncorrectedPtJES_)
   ,corExJES_(met.corExJES_)
   ,corEyJES_(met.corEyJES_)
   ,corSumEtJES_(met.corSumEtJES_)
   ,uncorrectedPhiMUON_(met.uncorrectedPhiMUON_)
   ,uncorrectedPtMUON_(met.uncorrectedPtMUON_)
   ,corExMUON_(met.corExMUON_)
   ,corEyMUON_(met.corEyMUON_)
   ,corSumEtMUON_(met.corSumEtMUON_)
   ,neutralHadEtFraction_(met.neutralHadEtFraction_)
   ,neutralHadEt_ (met.neutralHadEt_)
   ,chargedHadEtFraction_(met.chargedHadEtFraction_)
   ,chargedHadEt_(met.chargedHadEt_)
   ,neutralEMEtFraction_(met.neutralEMEtFraction_)
   ,neutralEMEt_(met.neutralEMEt_)
   ,chargedEMEtFraction_(met.chargedEMEtFraction_)
   ,chargedEMEt_(met.chargedEMEt_)
   ,muonEtFraction_(met.muonEtFraction_)
   ,muonEt_(met.muonEt_)
   ,type6EtFraction_(met.type6EtFraction_)
   ,type6Et_(met.type6Et_)
   ,type7EtFraction_(met.type7EtFraction_)
   ,type7Et_(met.type7Et_)
   ,sumEt_(met.sumEt_)
   {;}
   
   TRootMET(Double_t px, Double_t py, Double_t pz, Double_t e) :
   TRootParticle(px,py,pz,e)
   ,maxEtInEmTowers_(0.)
   ,maxEtInHadTowers_(0.)
   ,hadEtInHO_(0.)
   ,hadEtInHB_(0.)
   ,hadEtInHF_(0.)
   ,hadEtInHE_(0.)
   ,emEtInEB_(0.)
   ,emEtInEE_(0.)
   ,emEtInHF_(0.)
   ,etFractionHadronic_(0.)
   ,etFractionEm_(0.)
   ,metSignificance_(0.)
   ,caloMETInpHF_(0.)
   ,caloMETInmHF_(0.)
   ,caloSETInpHF_(0.)
   ,caloSETInmHF_(0.)
   ,caloMETPhiInpHF_(0.)
   ,caloMETPhiInmHF_(0.)
   ,uncorrectedPhiALL_(-9999.)
   ,uncorrectedPtALL_(-1.)
   ,corExALL_(-9999.)
   ,corEyALL_(-9999.)
   ,corSumEtALL_(-9999.)
   ,uncorrectedPhiJES_(-9999.)
   ,uncorrectedPtJES_(-1.)
   ,corExJES_(-9999.)
   ,corEyJES_(-9999.)
   ,corSumEtJES_(-9999.)
   ,uncorrectedPhiMUON_(-9999.)
   ,uncorrectedPtMUON_(-1.)
   ,corExMUON_(-9999.)
   ,corEyMUON_(-9999.)
   ,corSumEtMUON_(-9999.)
   ,neutralHadEtFraction_(0.)
   ,neutralHadEt_ (0.)
   ,chargedHadEtFraction_(0.)
   ,chargedHadEt_(0.)
   ,neutralEMEtFraction_(0.)
   ,neutralEMEt_ (0.)
   ,chargedEMEtFraction_(0.)
   ,chargedEMEt_(0.)
   ,muonEtFraction_(0.)
   ,muonEt_(0.)
   ,type6EtFraction_(0.)
   ,type6Et_(0.)
   ,type7EtFraction_(0.)
   ,type7Et_(0.)
   ,sumEt_(0.)
   {;}
   
   TRootMET(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
   ,maxEtInEmTowers_(0.)
   ,maxEtInHadTowers_(0.)
   ,hadEtInHO_(0.)
   ,hadEtInHB_(0.)
   ,hadEtInHF_(0.)
   ,hadEtInHE_(0.)
   ,emEtInEB_(0.)
   ,emEtInEE_(0.)
   ,emEtInHF_(0.)
   ,etFractionHadronic_(0.)
   ,etFractionEm_(0.)
   ,metSignificance_(0.)
   ,caloMETInpHF_(0.)
   ,caloMETInmHF_(0.)
   ,caloSETInpHF_(0.)
   ,caloSETInmHF_(0.)
   ,caloMETPhiInpHF_(0.)
   ,caloMETPhiInmHF_(0.)
   ,uncorrectedPhiALL_(-9999.)
   ,uncorrectedPtALL_(-1.)
   ,corExALL_(-9999.)
   ,corEyALL_(-9999.)
   ,corSumEtALL_(-9999.)
   ,uncorrectedPhiJES_(-9999.)
   ,uncorrectedPtJES_(-1.)
   ,corExJES_(-9999.)
   ,corEyJES_(-9999.)
   ,corSumEtJES_(-9999.)
   ,uncorrectedPhiMUON_(-9999.)
   ,uncorrectedPtMUON_(-1.)
   ,corExMUON_(-9999.)
   ,corEyMUON_(-9999.)
   ,corSumEtMUON_(-9999.)
   ,neutralHadEtFraction_(0.)
   ,neutralHadEt_ (0.)
   ,chargedHadEtFraction_(0.)
   ,chargedHadEt_(0.)
   ,neutralEMEtFraction_(0.)
   ,neutralEMEt_ (0.)
   ,chargedEMEtFraction_(0.)
   ,chargedEMEt_(0.)
   ,muonEtFraction_(0.)
   ,muonEt_(0.)
   ,type6EtFraction_(0.)
   ,type6Et_(0.)
   ,type7EtFraction_(0.)
   ,type7Et_(0.)
   ,sumEt_(0.)
   {;}
   
   TRootMET(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
   ,maxEtInEmTowers_(0.)
   ,maxEtInHadTowers_(0.)
   ,hadEtInHO_(0.)
   ,hadEtInHB_(0.)
   ,hadEtInHF_(0.)
   ,hadEtInHE_(0.)
   ,emEtInEB_(0.)
   ,emEtInEE_(0.)
   ,emEtInHF_(0.)
   ,etFractionHadronic_(0.)
   ,etFractionEm_(0.)
   ,metSignificance_(0.)
   ,caloMETInpHF_(0.)
   ,caloMETInmHF_(0.)
   ,caloSETInpHF_(0.)
   ,caloSETInmHF_(0.)
   ,caloMETPhiInpHF_(0.)
   ,caloMETPhiInmHF_(0.)
   ,uncorrectedPhiALL_(-9999.)
   ,uncorrectedPtALL_(-1.)
   ,corExALL_(-9999.)
   ,corEyALL_(-9999.)
   ,corSumEtALL_(-9999.)
   ,uncorrectedPhiJES_(-9999.)
   ,uncorrectedPtJES_(-1.)
   ,corExJES_(-9999.)
   ,corEyJES_(-9999.)
   ,corSumEtJES_(-9999.)
   ,uncorrectedPhiMUON_(-9999.)
   ,uncorrectedPtMUON_(-1.)
   ,corExMUON_(-9999.)
   ,corEyMUON_(-9999.)
   ,corSumEtMUON_(-9999.)
   ,neutralHadEtFraction_(0.)
   ,neutralHadEt_ (0.)
   ,chargedHadEtFraction_(0.)
   ,chargedHadEt_(0.)
   ,neutralEMEtFraction_(0.)
   ,neutralEMEt_ (0.)
   ,chargedEMEtFraction_(0.)
   ,chargedEMEt_(0.)
   ,muonEtFraction_(0.)
   ,muonEt_(0.)
   ,type6EtFraction_(0.)
   ,type6Et_(0.)
   ,type7EtFraction_(0.)
   ,type7Et_(0.)
   ,sumEt_(0.)
   {;}
   
   TRootMET(const TLorentzVector &momentum) :
   TRootParticle(momentum)
   ,maxEtInEmTowers_(0.)
   ,maxEtInHadTowers_(0.)
   ,hadEtInHO_(0.)
   ,hadEtInHB_(0.)
   ,hadEtInHF_(0.)
   ,hadEtInHE_(0.)
   ,emEtInEB_(0.)
   ,emEtInEE_(0.)
   ,emEtInHF_(0.)
   ,etFractionHadronic_(0.)
   ,etFractionEm_(0.)
   ,metSignificance_(0.)
   ,caloMETInpHF_(0.)
   ,caloMETInmHF_(0.)
   ,caloSETInpHF_(0.)
   ,caloSETInmHF_(0.)
   ,caloMETPhiInpHF_(0.)
   ,caloMETPhiInmHF_(0.)
   ,uncorrectedPhiALL_(-9999.)
   ,uncorrectedPtALL_(-1.)
   ,corExALL_(-9999.)
   ,corEyALL_(-9999.)
   ,corSumEtALL_(-9999.)
   ,uncorrectedPhiJES_(-9999.)
   ,uncorrectedPtJES_(-1.)
   ,corExJES_(-9999.)
   ,corEyJES_(-9999.)
   ,corSumEtJES_(-9999.)
   ,uncorrectedPhiMUON_(-9999.)
   ,uncorrectedPtMUON_(-1.)
   ,corExMUON_(-9999.)
   ,corEyMUON_(-9999.)
   ,corSumEtMUON_(-9999.)
   ,neutralHadEtFraction_(0.)
   ,neutralHadEt_ (0.)
   ,chargedHadEtFraction_(0.)
   ,chargedHadEt_(0.)
   ,neutralEMEtFraction_(0.)
   ,neutralEMEt_ (0.)
   ,chargedEMEtFraction_(0.)
   ,chargedEMEt_(0.)
   ,muonEtFraction_(0.)
   ,muonEt_(0.)
   ,type6EtFraction_(0.)
   ,type6Et_(0.)
   ,type7EtFraction_(0.)
   ,type7Et_(0.)
   ,sumEt_(0.)
   {;}
   
   TRootMET(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
   TRootParticle(momentum, vertex, type, charge)
   ,maxEtInEmTowers_(0.)
   ,maxEtInHadTowers_(0.)
   ,hadEtInHO_(0.)
   ,hadEtInHB_(0.)
   ,hadEtInHF_(0.)
   ,hadEtInHE_(0.)
   ,emEtInEB_(0.)
   ,emEtInEE_(0.)
   ,emEtInHF_(0.)
   ,etFractionHadronic_(0.)
   ,etFractionEm_(0.)
   ,metSignificance_(0.)
   ,caloMETInpHF_(0.)
   ,caloMETInmHF_(0.)
   ,caloSETInpHF_(0.)
   ,caloSETInmHF_(0.)
   ,caloMETPhiInpHF_(0.)
   ,caloMETPhiInmHF_(0.)
   ,uncorrectedPhiALL_(-9999.)
   ,uncorrectedPtALL_(-1.)
   ,corExALL_(-9999.)
   ,corEyALL_(-9999.)
   ,corSumEtALL_(-9999.)
   ,uncorrectedPhiJES_(-9999.)
   ,uncorrectedPtJES_(-1.)
   ,corExJES_(-9999.)
   ,corEyJES_(-9999.)
   ,corSumEtJES_(-9999.)
   ,uncorrectedPhiMUON_(-9999.)
   ,uncorrectedPtMUON_(-1.)
   ,corExMUON_(-9999.)
   ,corEyMUON_(-9999.)
   ,corSumEtMUON_(-9999.)
   ,neutralHadEtFraction_(0.)
   ,neutralHadEt_ (0.)
   ,chargedHadEtFraction_(0.)
   ,chargedHadEt_(0.)
   ,neutralEMEtFraction_(0.)
   ,neutralEMEt_ (0.)
   ,chargedEMEtFraction_(0.)
   ,chargedEMEt_(0.)
   ,muonEtFraction_(0.)
   ,muonEt_(0.)
   ,type6EtFraction_(0.)
   ,type6Et_(0.)
   ,type7EtFraction_(0.)
   ,type7Et_(0.)
   ,sumEt_(0.)
   {;}
   
   ~TRootMET() {;}
   
   Float_t maxEtInEmTowers() const { return maxEtInEmTowers_; }
   Float_t maxEtInHadTowers() const { return maxEtInHadTowers_; }
   Float_t hadEtInHO() const { return hadEtInHO_; }
   Float_t hadEtInHB() const { return hadEtInHB_; }
   Float_t hadEtInHF() const { return hadEtInHF_; }
   Float_t hadEtInHE() const { return hadEtInHE_; }
   Float_t emEtInEB() const { return emEtInEB_; }
   Float_t emEtInEE() const { return emEtInEE_; }
   Float_t emEtInHF() const { return emEtInHF_; }
   Float_t etFractionHadronic() const { return etFractionHadronic_; }
   Float_t etFractionEm() const { return etFractionEm_; }
   Float_t metSignificance() const { return metSignificance_; }
   Float_t caloMETInpHF() const { return caloMETInpHF_; }
   Float_t caloMETInmHF() const { return caloMETInmHF_; }
   Float_t caloSETInpHF() const { return caloSETInpHF_; }
   Float_t caloSETInmHF() const { return caloSETInmHF_; }
   Float_t caloMETPhiInpHF() const { return caloMETPhiInpHF_; }
   Float_t caloMETPhiInmHF() const { return caloMETPhiInmHF_; }
   Float_t uncorrectedPhiALL() const {return uncorrectedPhiALL_; }
   Float_t uncorrectedPtALL()const {return uncorrectedPtALL_; }
   Float_t corExALL()const {return corExALL_; }
   Float_t corEyALL()const {return corEyALL_; }
   Float_t corSumEtALL()const {return corSumEtALL_; }
   Float_t uncorrectedPhiJES() const {return uncorrectedPhiJES_; }
   Float_t uncorrectedPtJES()const {return uncorrectedPtJES_; }
   Float_t corExJES()const {return corExJES_; }
   Float_t corEyJES()const {return corEyJES_; }
   Float_t corSumEtJES()const {return corSumEtJES_; }
   Float_t uncorrectedPhiMUON() const {return uncorrectedPhiMUON_; }
   Float_t uncorrectedPtMUON()const {return uncorrectedPtMUON_; }
   Float_t corExMUON()const {return corExMUON_; }
   Float_t corEyMUON()const {return corEyMUON_; }
   Float_t corSumEtMUON()const {return corSumEtMUON_; }
   Float_t neutralHadEtFraction() const {return neutralHadEtFraction_; }
   Float_t neutralHadEt() const {return neutralHadEt_; }
   Float_t chargedHadEtFraction() const {return chargedHadEtFraction_; }
   Float_t chargedHadEt() const {return chargedHadEt_; }
   Float_t neutralEMEtFraction() const {return neutralEMEtFraction_; }
   Float_t neutralEMEt() const {return neutralEMEt_; }
   Float_t chargedEMEtFraction() const {return chargedEMEtFraction_; }
   Float_t chargedEMEt() const {return chargedEMEt_; }
   Float_t muonEtFraction() const {return muonEtFraction_; }
   Float_t muonEt() const {return muonEt_; }
   Float_t type6EtFraction() {return type6EtFraction_; }
   Float_t type6Et() {return type6Et_; }
   Float_t type7EtFraction() {return type7EtFraction_; }
   Float_t type7Et() {return type7Et_; }
   Float_t sumEt() const {return sumEt_; }
   //TObject* genMET() const { return genMET_.GetObject(); }
   virtual TString typeName() const { return "TRootMET"; }
   
   
   void setMaxEtInEmTowers(Float_t maxEtInEmTowers) { maxEtInEmTowers_ = maxEtInEmTowers; }
   void setMaxEtInHadTowers(Float_t maxEtInHadTowers) { maxEtInHadTowers_ = maxEtInHadTowers; }
   void setHadEtInHO(Float_t hadEtInHO) { hadEtInHO_ = hadEtInHO; }
   void setHadEtInHB(Float_t hadEtInHB) { hadEtInHB_ = hadEtInHB; }
   void setHadEtInHF(Float_t hadEtInHF) { hadEtInHF_ = hadEtInHF; }
   void setHadEtInHE(Float_t hadEtInHE) { hadEtInHE_ = hadEtInHE; }
   void setEmEtInEB(Float_t emEtInEB) { emEtInEB_ = emEtInEB; }
   void setEmEtInEE(Float_t emEtInEE) { emEtInEE_ = emEtInEE; }
   void setEmEtInHF(Float_t emEtInHF) { emEtInHF_ = emEtInHF; }
   void setEtFractionHadronic(Float_t etFractionHadronic) { etFractionHadronic_ = etFractionHadronic; }
   void setEtFractionEm(Float_t etFractionEm) { etFractionEm_ = etFractionEm; }
   void setMETSignificance(Float_t metSignificance) { metSignificance_ = metSignificance; }
   void setCaloMETInpHF(Float_t caloMETInpHF) { caloMETInpHF_ = caloMETInpHF; }
   void setCaloMETInmHF(Float_t caloMETInmHF) { caloMETInmHF_ = caloMETInmHF; }
   void setCaloSETInpHF(Float_t caloSETInpHF) { caloSETInpHF_ = caloSETInpHF; }
   void setCaloSETInmHF(Float_t caloSETInmHF) { caloSETInmHF_ = caloSETInmHF; }
   void setCaloMETPhiInpHF(Float_t caloMETPhiInpHF) { caloMETPhiInpHF_ = caloMETPhiInpHF; }
   void setCaloMETPhiInmHF(Float_t caloMETPhiInmHF) { caloMETPhiInmHF_ = caloMETPhiInmHF; }
   
   void setCaloMETFraction(
      Float_t maxEtInEmTowers
      ,Float_t maxEtInHadTowers
      ,Float_t hadEtInHO
      ,Float_t hadEtInHB
      ,Float_t hadEtInHF
      ,Float_t hadEtInHE
      ,Float_t emEtInEB
      ,Float_t emEtInEE
      ,Float_t emEtInHF
      ,Float_t etFractionHadronic
      ,Float_t etFractionEm
      ,Float_t metSignificance
      ,Float_t caloMETInpHF
      ,Float_t caloMETInmHF
      ,Float_t caloSETInpHF
      ,Float_t caloSETInmHF
      ,Float_t caloMETPhiInpHF
      ,Float_t caloMETPhiInmHF
   )
   {
      maxEtInEmTowers_ = maxEtInEmTowers;
      maxEtInEmTowers_ = maxEtInEmTowers;
      maxEtInHadTowers_ = maxEtInHadTowers;
      hadEtInHO_ = hadEtInHO;
      hadEtInHB_ = hadEtInHB;
      hadEtInHF_ = hadEtInHF;
      hadEtInHE_ = hadEtInHE;
      emEtInEB_ = emEtInEB;
      emEtInEE_ = emEtInEE;
      emEtInHF_ = emEtInHF;
      etFractionHadronic_ = etFractionHadronic;
      etFractionEm_ = etFractionEm;
      metSignificance_ = metSignificance;
      caloMETInpHF_ = caloMETInpHF;
      caloMETInmHF_ = caloMETInmHF;
      caloSETInpHF_ = caloSETInpHF;
      caloSETInmHF_ = caloSETInmHF;
      caloMETPhiInpHF_ = caloMETPhiInpHF;
      caloMETPhiInmHF_ = caloMETPhiInmHF;
   }
   
   void setUncorrectedPhiALL(Float_t uncorrectedPhiALL) { uncorrectedPhiALL_ = uncorrectedPhiALL;}
   void setUncorrectedPtALL(Float_t uncorrectedPtALL) { uncorrectedPtALL_ = uncorrectedPtALL;}
   void setCorExALL(Float_t corExALL) { corExALL_ = corExALL;}
   void setCorEyALL(Float_t corEyALL) { corEyALL_ = corEyALL;}
   void setCorSumEtALL(Float_t corSumEtALL) { corSumEtALL_ = corSumEtALL;}
   void setUncorrectedPhiJES(Float_t uncorrectedPhiJES) { uncorrectedPhiJES_ = uncorrectedPhiJES;}
   void setUncorrectedPtJES(Float_t uncorrectedPtJES) { uncorrectedPtJES_ = uncorrectedPtJES;}
   void setCorExJES(Float_t corExJES) { corExJES_ = corExJES;}
   void setCorEyJES(Float_t corEyJES) { corEyJES_ = corEyJES;}
   void setCorSumEtJES(Float_t corSumEtJES) { corSumEtJES_ = corSumEtJES;}
   void setUncorrectedPhiMUON(Float_t uncorrectedPhiMUON) { uncorrectedPhiMUON_ = uncorrectedPhiMUON;}
   void setUncorrectedPtMUON(Float_t uncorrectedPtMUON) { uncorrectedPtMUON_ = uncorrectedPtMUON;}
   void setCorExMUON(Float_t corExMUON) { corExMUON_ = corExMUON;}
   void setCorEyMUON(Float_t corEyMUON) { corEyMUON_ = corEyMUON;}
   void setCorSumEtMUON(Float_t corSumEtMUON) { corSumEtMUON_ = corSumEtMUON;}
   //void setGenMET(TObject* genMET) { genMET_ = genMET; }
   
   void setHadronicEtFraction(
      Float_t neutralHadEtFraction
      ,Float_t neutralHadEt
      ,Float_t chargedHadEtFraction
      ,Float_t chargedHadEt
   )
   {
      neutralHadEtFraction_ = neutralHadEtFraction;
      neutralHadEt_         = neutralHadEt;
      chargedHadEtFraction_ = chargedHadEtFraction;
      chargedHadEt_         = chargedHadEt;
   }
   
   void setEMEtFraction(
      Float_t neutralEMEtFraction
      ,Float_t neutralEMEt
      ,Float_t chargedEMEtFraction
      ,Float_t chargedEMEt
   )
   {
      neutralEMEtFraction_ = neutralEMEtFraction;
      neutralEMEt_         = neutralEMEt;
      chargedEMEtFraction_ = chargedEMEtFraction;
      chargedEMEt_         = chargedEMEt;
   }
   
   void setMuonstFraction(
      Float_t muonEtFraction
      ,Float_t muonEt
   )
   {
      muonEtFraction_ = muonEtFraction;
      muonEt_         = muonEt;
   }
   
   void setTypesFraction(
      Float_t type6EtFraction,
      Float_t type6Et,
      Float_t type7EtFraction,
      Float_t type7Et
   )
   {
      type6EtFraction_ = type6EtFraction;
      type6Et_         = type6Et;
      type7EtFraction_ = type7EtFraction;
      type7Et_         = type7Et;
   }
   
   void setSumEt(Float_t sumEt) { sumEt_ = sumEt; }
   
   friend std::ostream& operator<< (std::ostream& stream, const TRootMET& met) {
      stream << "TRootMET  (Pt,Px,Py,Phi,SumEt)=("<< met.Pt() <<","<< met.Px() <<","<< met.Py()  <<","<< met.Phi() << "," << met.sumEt() << ")"
         << "  hadEt in (HO,HB,HF,HE)=("<< met.hadEtInHO() <<","<< met.hadEtInHB() <<","<< met.hadEtInHF() <<","<< met.hadEtInHE() << ")"
         << "  emEt in (EB,EF,HF)=("<< met.emEtInEB() <<","<< met.emEtInEE() <<","<< met.emEtInHF() << ")";
      return stream;
   };
   
   
   private:
      
      Float_t maxEtInEmTowers_;    // Maximum ET in EM towers
      Float_t maxEtInHadTowers_;   // Maximum ET in HCAL towers
      Float_t hadEtInHO_;          // Hadronic ET fraction in HO
      Float_t hadEtInHB_;          // Hadronic ET in HB
      Float_t hadEtInHF_;          // Hadronic ET in HF
      Float_t hadEtInHE_;          // Hadronic ET in HE
      Float_t emEtInEB_;           // Em ET in EB
      Float_t emEtInEE_;           // Em ET in EE
      Float_t emEtInHF_;           // Em ET in HF
      Float_t etFractionHadronic_; // Hadronic ET fraction
      Float_t etFractionEm_;       // Em ET fraction
      Float_t metSignificance_;    // Em ET fraction
      Float_t caloMETInpHF_;       // CaloMET in HF+
      Float_t caloMETInmHF_;       // CaloMET in HF-
      Float_t caloSETInpHF_;       // CaloSET in HF+
      Float_t caloSETInmHF_;       // CaloSET in HF-
      Float_t caloMETPhiInpHF_;    // CaloMET-phi in HF+
      Float_t caloMETPhiInmHF_;    // CaloMET-phi in HF-
      Float_t uncorrectedPhiALL_;
      Float_t uncorrectedPtALL_;
      Float_t corExALL_;
      Float_t corEyALL_;
      Float_t corSumEtALL_;
      Float_t uncorrectedPhiJES_;
      Float_t uncorrectedPtJES_;
      Float_t corExJES_;
      Float_t corEyJES_;
      Float_t corSumEtJES_;
      Float_t uncorrectedPhiMUON_;
      Float_t uncorrectedPtMUON_;
      Float_t corExMUON_;
      Float_t corEyMUON_;
      Float_t corSumEtMUON_;
      
      Float_t neutralHadEtFraction_;
      Float_t neutralHadEt_;
      Float_t chargedHadEtFraction_;
      Float_t chargedHadEt_;
      Float_t neutralEMEtFraction_;
      Float_t neutralEMEt_;
      Float_t chargedEMEtFraction_;
      Float_t chargedEMEt_;
      Float_t muonEtFraction_;
      Float_t muonEt_;
      Float_t type6EtFraction_;
      Float_t type6Et_;
      Float_t type7EtFraction_;
      Float_t type7Et_;
      
      Float_t sumEt_;
      
      ClassDef (TRootMET,3);
      
   };
   
   #endif
   