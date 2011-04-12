#ifndef TRootMCElectron_h
#define TRootMCElectron_h

#include <vector>

#include "../interface/TRootParticle.h"

using namespace std;

class TRootMCElectron : public TRootParticle
{
   
public:
   
   TRootMCElectron() :
   TRootParticle()
   ,bremPosition_()
   ,bremMomentum_()
   ,energyLoss_()
   {;}
   
   TRootMCElectron(const TRootMCElectron& electron) :
   TRootParticle(electron)
   ,bremPosition_(electron.bremPosition_)
   ,bremMomentum_(electron.bremMomentum_)
   ,energyLoss_(electron.energyLoss_)
   {;}
   
   TRootMCElectron(Double_t px, Double_t py, Double_t pz, Double_t e) :
   TRootParticle(px,py,pz,e)
   ,bremPosition_()
   ,bremMomentum_()
   ,energyLoss_()
   {;}
   
   TRootMCElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
   ,bremPosition_()
   ,bremMomentum_()
   ,energyLoss_()
   {;}
   
   TRootMCElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
   TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
   ,bremPosition_()
   ,bremMomentum_()
   ,energyLoss_()
   {;}
   
   TRootMCElectron(const TLorentzVector &momentum) :
   TRootParticle(momentum)
   ,bremPosition_()
   ,bremMomentum_()
   ,energyLoss_()
   {;}
   
   TRootMCElectron(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
   TRootParticle(momentum, vertex, type, charge)
   ,bremPosition_()
   ,bremMomentum_()
   ,energyLoss_()
   {;}
   
   TRootMCElectron(const TLorentzVector &momentum, const TVector3 &vertex,  const TVector3 &convVertex, Int_t type, Float_t charge) :
   TRootParticle(momentum, vertex, type, charge)
   ,bremPosition_()
   ,bremMomentum_()
   ,energyLoss_()
   {;}
   
   TRootMCElectron(const TLorentzVector &momentum, const TVector3 &vertex,  const TVector3 &convVertex,  const std::vector<TLorentzVector> &tracks, Int_t type, Float_t charge) :
   TRootParticle(momentum, vertex, type, charge)
   ,bremPosition_()
   ,bremMomentum_()
   ,energyLoss_()
   {;}
   
   
   ~TRootMCElectron() {;}
   
   
   std::vector<TVector3> bremPosition() const  { return bremPosition_;}
   std::vector<TLorentzVector> bremMomentum() const { return bremMomentum_;}
   std::vector<float> energyLoss() const { return energyLoss_;};
   
   void setBremPosition(std::vector<TVector3> bremPosition) {bremPosition_ = bremPosition;}
   void setBremMomentum(std::vector<TLorentzVector> bremMomentum) {bremMomentum_ = bremMomentum;}
   void setEnergyLoss(std::vector<float> energyLoss) { energyLoss_ = energyLoss;}
   
   
   virtual TString typeName() const { return "TRootMCElectron"; }
   
   
   private:
      
      std::vector<TVector3> bremPosition_;      // position of the brem vertex
      std::vector<TLorentzVector> bremMomentum_; // brem photon momentum
      std::vector<float>   energyLoss_;   // Energy loss by the brem
      
      ClassDef (TRootMCElectron,1);
      
   };
   
   #endif
   