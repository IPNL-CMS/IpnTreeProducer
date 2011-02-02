#ifndef TRootTau_h
#define TRootTau_h

#include "../interface/TRootParticle.h"

using namespace std;

class TRootTau : public TRootParticle
{
   
   public:
      
      TRootTau() :
      TRootParticle()
      {;}
      
      TRootTau(const TRootTau& tau) :
      TRootParticle(tau)
      {;}
      
      TRootTau(Double_t px, Double_t py, Double_t pz, Double_t e) :
      TRootParticle(px,py,pz,e)
      {;}
      
      TRootTau(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
      {;}
      
      TRootTau(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
      {;}
      
      TRootTau(const TLorentzVector &momentum) :
      TRootParticle(momentum)
      {;}
      
      TRootTau(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
      TRootParticle(momentum, vertex, type, charge)
      {;}
      
      ~TRootTau() {;}
      
      //TObject* genTau() const { return genTau_.GetObject() ;}
      virtual TString typeName() const { return "TRootTau"; }
      
      friend std::ostream& operator<< (std::ostream& stream, const TRootTau& tau) {
 	stream << "TRootTau - Charge=" << tau.charge() << " (Et,eta,phi)=("<< tau.Et() <<","<< tau.Eta() <<","<< tau.Phi() << ")  vertex(x,y,z)=("<< tau.vx() <<","<< tau.vy() <<","<< tau.vz() << ")";
	return stream;
      };
      
      void Print()
      {
	std::cout << "TRootTau - Charge=" << this->charge() << " (Et,eta,phi)=("<< this->Et() <<","<< this->Eta() <<","<< this->Phi() << ")  vertex(x,y,z)=("<< this->vx() <<","<< this->vy() <<","<< this->vz() << ")";
      };
      
      
   private:
      
      // Variables from reco::Tau
      
      ClassDef (TRootTau,1);
      
};

#endif
