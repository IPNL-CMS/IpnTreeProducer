#ifndef TRootCluster_h
#define TRootCluster_h

/************************************************************************************************************************************
 * Cluster Type: ijk
 * i = algo =>  1=Island , 2=Hybrid, 3=multi5x5, 4=IslandWeight
 * j = detector => 1=ECAL Barrel , 2=ECAL Endcap
 * k = corrections => 0=nopreshower / uncorrected  ,  1=no preshower / standard CMSSW corections
 * 2=preshower / standard CMSSW corections  ,  3= preshower / uncorrected
 * 
 * BasicClusters
 * 110 => Island Barrel BasicClusters
 * 120 => Island Endcap BasicClusters
 * 210 => hybrid Barrel BasicClusters
 * 310 => multi5x5 Barrel BasicClusters
 * 320 => multi5x5 Endcap BasicClusters
 * 
 * SuperClusters
 * 110 => Island Barrel SuperClusters
 * 120 => Island Endcap SuperClusters
 * 121 => Corrected Island Endcap SuperClusters (standard CMSSW corrections)
 * 122 => Corrected Island Endcap SuperClusters with Preshower (standard CMSSW corrections)
 * 210 => Hybrid Barrel SuperClusters
 * 211 => Corrected Hybrid Barrel SuperClusters (standard CMSSW corrections)
 * 320 => Multi5x5 Endcap SuperClusters
 * 322 => Corrected Multi5x5 Endcap SuperClusters with Preshower (standard CMSSW corrections)
 * 323 => Multi5x5 Endcap SuperClusters with Preshower
 * 
 * Shapes variables (e3x3, e5x5, eMax, e2nd) are not modified by CMSSW energy corrections
 * Shapes variables for SuperClusters correspond to shapes variables of the seed BasicCluster
 * 
 ************************************************************************************************************************************/

#include <string>
#include <iostream>

#include "Rtypes.h"
#include "TVector3.h"
#include "TMath.h"
#include "TRef.h"

#include "../interface/TRootEcalRecHit.h"

using namespace std;

class TRootCluster : public TVector3
{
   
public:
   
   TRootCluster() :
   TVector3()
   ,position_(-999999.,-999999.,-999999.)
   ,det_(-1)
   ,time_(-999999.)
   ,e2x2_(-1.)
   ,e3x3_(-1.)
   ,e5x5_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,hits_()
   {;}
   
   TRootCluster(const TRootCluster& cluster) :
   TVector3(cluster)
   ,position_(cluster.position_)
   ,det_(cluster.det_)
   ,time_(cluster.time_)
   ,e2x2_(cluster.e2x2_)
   ,e3x3_(cluster.e3x3_)
   ,e5x5_(cluster.e5x5_)
   ,eMax_(cluster.eMax_)
   ,e2nd_(cluster.e2nd_)
   ,s4_(cluster.s4_)
   ,esRatio_(cluster.esRatio_)
   ,crackCorrectionEta_(cluster.crackCorrectionEta_)
   ,crackCorrectionPhi_(cluster.crackCorrectionPhi_)
   ,crackCorrectionEtaPhi_(cluster.crackCorrectionEtaPhi_)
   ,nXtals_(cluster.nXtals_)
   ,uid_(cluster.uid_)
   ,hits_(cluster.hits_)
   {;}
   
   TRootCluster(Double_t energy, Double_t eta, Double_t phi) :
   position_(-999999.,-999999.,-999999.)
   ,det_(-1)
   ,time_(-999999.)
   ,e2x2_(-1.)
   ,e3x3_(-1.)
   ,e5x5_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,hits_()
   {
      this->SetPtEtaPhi(energy*TMath::Sin(2.0*TMath::ATan(TMath::Exp(-eta))), eta, phi);
   }
   
   TRootCluster(Double_t energy, Double_t eta, Double_t phi, Double_t x, Double_t y, Double_t z) :
   position_(x,y,z)
   ,det_(-1)
   ,time_(-999999.)
   ,e2x2_(-1.)
   ,e3x3_(-1.)
   ,e5x5_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,hits_()
   {
      this->SetPtEtaPhi(energy*TMath::Sin(2.0*TMath::ATan(TMath::Exp(-eta))), eta, phi);
   }
   
   TRootCluster(Double_t energy, Double_t eta, Double_t phi, Double_t x, Double_t y, Double_t z, Int_t det) :
   position_(x,y,z)
   ,det_(det)
   ,time_(-999999.)
   ,e2x2_(-1.)
   ,e3x3_(-1.)
   ,e5x5_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,hits_()
   {
      this->SetPtEtaPhi(energy*TMath::Sin(2.0*TMath::ATan(TMath::Exp(-eta))), eta, phi);
   }
   
   TRootCluster(const TVector3 &momentum) :
   TVector3(momentum)
   ,position_(-999999.,-999999.,-999999.)
   ,det_(-1)
   ,time_(-999999.)
   ,e2x2_(-1.)
   ,e3x3_(-1.)
   ,e5x5_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,hits_()
   {;}
   
   
   TRootCluster(const TVector3 &momentum, const TVector3 &position, Int_t det) :
   TVector3(momentum)
   ,position_(position)
   ,det_(det)
   ,time_(-999999.)
   ,e2x2_(-1.)
   ,e3x3_(-1.)
   ,e5x5_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,hits_()
   {;}
   
   ~TRootCluster() {;}
   
   
   Double_t calX() const { return position_.x(); }
   Double_t calY() const { return position_.y(); }
   Double_t calZ() const { return position_.z(); }
   Int_t det() const { return det_; }
   Float_t time() const { return time_; }
   Int_t type() const { return det_; }
   Double_t e2x2() const { return e2x2_; }
   Double_t e3x3() const { return e3x3_; }
   Double_t e5x5() const { return e5x5_; }
   Double_t eMax() const { return eMax_; }
   Double_t e2nd() const { return e2nd_; }
   Double_t s4() const { return s4_; }
   Float_t esRatio() const { return esRatio_; }
   Double_t crackCorrectionEta() const { return crackCorrectionEta_; }
   Double_t crackCorrectionPhi() const { return crackCorrectionPhi_; }
   Double_t crackCorrectionEtaPhi() const { return crackCorrectionEtaPhi_; }
   Int_t nXtals() const { return nXtals_; }
   UInt_t uid() const { return uid_; }
   UInt_t nRecHits() const { return hits_.size(); }
   std::vector<TRootEcalRecHit> hits() const { return hits_; }
   TRootEcalRecHit* hitAt(unsigned int i) { return ( (i<hits_.size()) ? &(hits_.at(i)) : 0 ); }
   TRootEcalRecHit* seedHit() { return ( (0<hits_.size()) ? &(hits_.at(0)) : 0 ); }
   Int_t seedDetector() const { return ( (0<hits_.size()) ? hits_.at(0).detector() : -1. ); }
   Int_t seedRecoFlag() const { return ( (0<hits_.size()) ? hits_.at(0).recoFlag() : -1. ); }
   Float_t seedEnergy() const { return ( (0<hits_.size()) ? hits_.at(0).energy() : -1. ); }
   Float_t seedTime() const { return ( (0<hits_.size()) ? hits_.at(0).time() : -1. ); }
   Int_t seedPosition1() const { return ( (0<hits_.size()) ? hits_.at(0).position1() : -1. ); }
   Int_t seedPosition2() const { return ( (0<hits_.size()) ? hits_.at(0).position2() : -1. ); }
   Float_t seedChi2() const { return ( (0<hits_.size()) ? hits_.at(0).chi2() : -1. ); }
   Float_t seedOutOfTimeEnergy() const { return ( (0<hits_.size()) ? hits_.at(0).outOfTimeEnergy() : -1. ); }
   Float_t seedOutOfTimeChi2() const { return ( (0<hits_.size()) ? hits_.at(0).outOfTimeChi2() : -1. ); }
   Int_t seedSeverity() const { return ( (0<hits_.size()) ? hits_.at(0).severity() : -1. ); }
   TString typeName() const {
      if ( det_==110 ) return "Island Barrel BC";
      else if ( det_==120 ) return "Island Endcap BC";
      else if ( det_==210 ) return "Hybrid Barrel BC";
      else if ( det_==320 ) return "Multi5x5 Endcap BC";
      else return "Unknown type SC";
   }
   Bool_t isEB() const { return ( int((det_%100)/10)==1 ? true : false ); }
   Bool_t isEE() const { return ( int((det_%100)/10)==2 ? true : false ); }
   
   void setCalX(Double_t x) { position_.SetX(x); }
   void setCalY(Double_t y) { position_.SetY(y); }
   void setCalZ(Double_t z) { position_.SetZ(z); }
   void setDet(Int_t det) { det_ = det; }
   void setTime(Double_t time) { time_ = time; }
   void setType(Int_t det) { det_ = det; }
   void setE2x2(Double_t e2x2) { e2x2_ = e2x2; }
   void setE3x3(Double_t e3x3) { e3x3_ = e3x3; }
   void setE5x5(Double_t e5x5) { e5x5_ = e5x5; }
   void setEmax(Double_t eMax) { eMax_ = eMax; }
   void setE2nd(Double_t e2nd) { e2nd_ = e2nd; }
   void setS4(Double_t s4) { s4_ = s4; }
   void setESratio(Float_t esRatio) { esRatio_ = esRatio; }
   void setcrackCorrectionEta(Double_t crackCorrectionEta) { crackCorrectionEta_ = crackCorrectionEta; }
   void setcrackCorrectionPhi(Double_t crackCorrectionPhi) { crackCorrectionPhi_ = crackCorrectionPhi; }
   void setcrackCorrectionEtaPhi(Double_t crackCorrectionEtaPhi) { crackCorrectionEtaPhi_ = crackCorrectionEtaPhi; }
   void setNxtals(Int_t nXtals) { nXtals_ = nXtals; }
   void setUid(UInt_t uid) { uid_ = uid; }
   void setHits(std::vector<TRootEcalRecHit> hits) { hits_ = hits; }
   
   
   friend std::ostream& operator<< (std::ostream& stream, const TRootCluster& clus)
   {
      stream << "TRootCluster - Type=" << clus.det() << "  (E,Et,eta,phi)=(" << clus.Mag() <<"," << clus.Pt() <<"," << clus.Eta() <<"," << clus.Phi() << ")"
      << " Calo position (x,y,z)=(" << clus.calX() << "," << clus.calY() << "," << clus.calZ() << ")" << " time=" << clus.time()
      << " e3x3=" << clus.e3x3() << " e5x5=" << clus.e5x5() << " eMax=" << clus.eMax() << " e2nd=" << clus.e2nd() << " s4=" << clus.s4() << " nXtals=" << clus.nXtals();
      return stream;
   };
   
   void Print()
   {
      std::cout << "TRootCluster - Type=" << this->det() << "  (E,Et,eta,phi)=(" << this->Mag() <<"," << this->Pt() <<"," << this->Eta() <<"," << this->Phi() << ")"
      << " Calo position (x,y,z)=(" << this->calX() << "," << this->calY() << "," << this->calZ() << ")" << " time=" << this->time()
      << " e3x3=" << this->e3x3() << " e5x5=" << this->e5x5() << " eMax=" << this->eMax() << " e2nd=" << this->e2nd() << " s4=" << this->s4() << " nXtals=" << this->nXtals();
   };
   
   
protected:
   
   TVector3 position_; // Cluster position 
   Int_t det_;         // Cluster type: algo/detector/corrections (see above)
   Float_t time_;      // error-weighted average of time from rechits constituents of basic cluster 
   Double_t e2x2_;     // 2x2 xtals energy sum
   Double_t e3x3_;     // 3x3 xtals energy sum
   Double_t e5x5_;     // 5x5 xtals energy sum
   Double_t eMax_;     // Max xtal energy
   Double_t e2nd_;     // Energy of the 2nd highest energy xtal
   Double_t s4_;       // Energy in swiss cross
   Float_t esRatio_;   // Ratio E3/E21 of energy in ES planes
   Double_t crackCorrectionEta_; //Corrected cracks eta energy 
   Double_t crackCorrectionPhi_; //Corrected cracks phi energy
   Double_t crackCorrectionEtaPhi_; //Corrected cracks eta phi energy
   Int_t nXtals_;      // Number of xtals in the Basic Cluster
   UInt_t uid_;        // Unique Identifier
   
   std::vector<TRootEcalRecHit> hits_;  // associated Ecal rechits
   
   ClassDef (TRootCluster,9);
   
};


#endif
