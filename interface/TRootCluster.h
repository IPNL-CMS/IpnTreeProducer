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
   ,eSeed_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,eTop_(-1.)
   ,eBottom_(-1.)
   ,eLeft_(-1.)
   ,eRight_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,sigmaIetaIeta_(-1.)
   ,sigmaIphiIphi_(-1.)
   ,sigmaIetaIphi_(-1.)
   ,seedXtalIeta_(-1)
   ,seedXtalIphi_(-1)
   ,deltaEtaFromXtalCenter_(-1.)
   ,deltaPhiFromXtalCenter_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,seedIndex_(999999)
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
   ,eSeed_(cluster.eSeed_)
   ,eMax_(cluster.eMax_)
   ,e2nd_(cluster.e2nd_)
   ,eTop_(cluster.eTop_)
   ,eBottom_(cluster.eBottom_)
   ,eLeft_(cluster.eLeft_)
   ,eRight_(cluster.eRight_)
   ,s4_(cluster.s4_)
   ,esRatio_(cluster.esRatio_)
   ,sigmaIetaIeta_(cluster.sigmaIetaIeta_)
   ,sigmaIphiIphi_(cluster.sigmaIphiIphi_)
   ,sigmaIetaIphi_(cluster.sigmaIetaIphi_)
   ,seedXtalIeta_(cluster.seedXtalIeta_)
   ,seedXtalIphi_(cluster.seedXtalIphi_)
   ,deltaEtaFromXtalCenter_(cluster.deltaEtaFromXtalCenter_)
   ,deltaPhiFromXtalCenter_(cluster.deltaPhiFromXtalCenter_)
   ,crackCorrectionEta_(cluster.crackCorrectionEta_)
   ,crackCorrectionPhi_(cluster.crackCorrectionPhi_)
   ,crackCorrectionEtaPhi_(cluster.crackCorrectionEtaPhi_)
   ,nXtals_(cluster.nXtals_)
   ,uid_(cluster.uid_)
   ,seedIndex_(cluster.seedIndex_)
   ,hits_(cluster.hits_)
   {;}
   
   TRootCluster(Float_t energy, Float_t eta, Float_t phi) :
   position_(-999999.,-999999.,-999999.)
   ,det_(-1)
   ,time_(-999999.)
   ,e2x2_(-1.)
   ,e3x3_(-1.)
   ,e5x5_(-1.)
   ,eSeed_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,eTop_(-1.)
   ,eBottom_(-1.)
   ,eLeft_(-1.)
   ,eRight_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,sigmaIetaIeta_(-1.)
   ,sigmaIphiIphi_(-1.)
   ,sigmaIetaIphi_(-1.)
   ,seedXtalIeta_(-1)
   ,seedXtalIphi_(-1)
   ,deltaEtaFromXtalCenter_(-1.)
   ,deltaPhiFromXtalCenter_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,seedIndex_(999999)
   ,hits_()
   {
      this->SetPtEtaPhi(energy*TMath::Sin(2.0*TMath::ATan(TMath::Exp(-eta))), eta, phi);
   }
   
   TRootCluster(Float_t energy, Float_t eta, Float_t phi, Float_t x, Float_t y, Float_t z) :
   position_(x,y,z)
   ,det_(-1)
   ,time_(-999999.)
   ,e2x2_(-1.)
   ,e3x3_(-1.)
   ,e5x5_(-1.)
   ,eSeed_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,eTop_(-1.)
   ,eBottom_(-1.)
   ,eLeft_(-1.)
   ,eRight_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,sigmaIetaIeta_(-1.)
   ,sigmaIphiIphi_(-1.)
   ,sigmaIetaIphi_(-1.)
   ,seedXtalIeta_(-1)
   ,seedXtalIphi_(-1)
   ,deltaEtaFromXtalCenter_(-1.)
   ,deltaPhiFromXtalCenter_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,seedIndex_(999999)
   ,hits_()
   {
      this->SetPtEtaPhi(energy*TMath::Sin(2.0*TMath::ATan(TMath::Exp(-eta))), eta, phi);
   }
   
   TRootCluster(Float_t energy, Float_t eta, Float_t phi, Float_t x, Float_t y, Float_t z, Int_t det) :
   position_(x,y,z)
   ,det_(det)
   ,time_(-999999.)
   ,e2x2_(-1.)
   ,e3x3_(-1.)
   ,e5x5_(-1.)
   ,eSeed_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,eTop_(-1.)
   ,eBottom_(-1.)
   ,eLeft_(-1.)
   ,eRight_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,sigmaIetaIeta_(-1.)
   ,sigmaIphiIphi_(-1.)
   ,sigmaIetaIphi_(-1.)
   ,seedXtalIeta_(-1)
   ,seedXtalIphi_(-1)
   ,deltaEtaFromXtalCenter_(-1.)
   ,deltaPhiFromXtalCenter_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,seedIndex_(999999)
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
   ,eSeed_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,eTop_(-1.)
   ,eBottom_(-1.)
   ,eLeft_(-1.)
   ,eRight_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,sigmaIetaIeta_(-1.)
   ,sigmaIphiIphi_(-1.)
   ,sigmaIetaIphi_(-1.)
   ,seedXtalIeta_(-1)
   ,seedXtalIphi_(-1)
   ,deltaEtaFromXtalCenter_(-1.)
   ,deltaPhiFromXtalCenter_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,seedIndex_(999999)
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
   ,eSeed_(-1.)
   ,eMax_(-1.)
   ,e2nd_(-1.)
   ,eTop_(-1.)
   ,eBottom_(-1.)
   ,eLeft_(-1.)
   ,eRight_(-1.)
   ,s4_(-1.)
   ,esRatio_(-1.)
   ,sigmaIetaIeta_(-1.)
   ,sigmaIphiIphi_(-1.)
   ,sigmaIetaIphi_(-1.)
   ,seedXtalIeta_(-1)
   ,seedXtalIphi_(-1)
   ,deltaEtaFromXtalCenter_(-1.)
   ,deltaPhiFromXtalCenter_(-1.)
   ,crackCorrectionEta_(-1.)
   ,crackCorrectionPhi_(-1.)
   ,crackCorrectionEtaPhi_(-1.)
   ,nXtals_(-1)
   ,uid_(0)
   ,seedIndex_(999999)
   ,hits_()
   {;}
   
   ~TRootCluster() {;}
   
   
   Float_t calX() const { return position_.x(); }
   Float_t calY() const { return position_.y(); }
   Float_t calZ() const { return position_.z(); }
   Int_t det() const { return det_; }
   Float_t time() const { return time_; }
   Int_t type() const { return det_; }
   Float_t e2x2() const { return e2x2_; }
   Float_t e3x3() const { return e3x3_; }
   Float_t e5x5() const { return e5x5_; }
   Float_t eSeed() const { return eSeed_; }
   Float_t eMax() const { return eMax_; }
   Float_t e2nd() const { return e2nd_; }
   Float_t eTop() const { return eTop_; }
   Float_t eBottom() const { return eBottom_; }
   Float_t eLeft() const { return eLeft_; }
   Float_t eRight() const { return eRight_; }
   Float_t s4() const { return s4_; }
   Float_t esRatio() const { return esRatio_; }
   Float_t sigmaIetaIeta() const { return sigmaIetaIeta_; }
   Float_t sigmaIphiIphi() const { return sigmaIphiIphi_; }
   Float_t sigmaIetaIphi() const { return sigmaIetaIphi_; }
   Int_t seedXtalIeta() const { return seedXtalIeta_; }
   Int_t seedXtalIphi() const { return seedXtalIphi_; }
   Float_t deltaEtaFromXtalCenter() const { return deltaEtaFromXtalCenter_; }
   Float_t deltaPhiFromXtalCenter() const { return deltaPhiFromXtalCenter_; }
   Float_t crackCorrectionEta() const { return crackCorrectionEta_; }
   Float_t crackCorrectionPhi() const { return crackCorrectionPhi_; }
   Float_t crackCorrectionEtaPhi() const { return crackCorrectionEtaPhi_; }
   Int_t nXtals() const { return nXtals_; }
   UInt_t uid() const { return uid_; }
   UInt_t nRecHits() const { return hits_.size(); }
   UInt_t seedIndex() const { return seedIndex_; }
   std::vector<TRootEcalRecHit> hits() const { return hits_; }
   TRootEcalRecHit* hitAt(unsigned int i) { return ( (i<hits_.size()) ? &(hits_.at(i)) : 0 ); }
   TRootEcalRecHit* seedHit() { return ( (seedIndex_<hits_.size()) ? &(hits_.at(seedIndex_)) : 0 ); }
   Int_t seedDetector() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).detector() : -1 ); }
   Int_t seedRecoFlag() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).recoFlag() : -1 ); }
   Float_t seedEnergy() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).energy() : -1. ); }
   Float_t seedTime() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).time() : -1. ); }
   Int_t seedPosition1() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).position1() : -999 ); }
   Int_t seedPosition2() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).position2() : -999 ); }
   Float_t seedChi2() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).chi2() : -1. ); }
   Float_t seedOutOfTimeEnergy() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).outOfTimeEnergy() : -1. ); }
   Float_t seedOutOfTimeChi2() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).outOfTimeChi2() : -1. ); }
   Int_t seedSeverity() const { return ( (seedIndex_<hits_.size()) ? hits_.at(seedIndex_).severity() : -1 ); }
   TString typeName() const {
      if ( det_==110 ) return "Island Barrel BC";
      else if ( det_==120 ) return "Island Endcap BC";
      else if ( det_==210 ) return "Hybrid Barrel BC";
      else if ( det_==320 ) return "Multi5x5 Endcap BC";
      else return "Unknown type SC";
   }
   Bool_t isEB() const { return ( int((det_%100)/10)==1 ? true : false ); }
   Bool_t isEE() const { return ( int((det_%100)/10)==2 ? true : false ); }
   
   void setCalX(Float_t x) { position_.SetX(x); }
   void setCalY(Float_t y) { position_.SetY(y); }
   void setCalZ(Float_t z) { position_.SetZ(z); }
   void setDet(Int_t det) { det_ = det; }
   void setTime(Float_t time) { time_ = time; }
   void setType(Int_t det) { det_ = det; }
   void setE2x2(Float_t e2x2) { e2x2_ = e2x2; }
   void setE3x3(Float_t e3x3) { e3x3_ = e3x3; }
   void setE5x5(Float_t e5x5) { e5x5_ = e5x5; }
   void Essed(Float_t eSeed) { eSeed_ = eSeed; }
   void setEmax(Float_t eMax) { eMax_ = eMax; }
   void setE2nd(Float_t e2nd) { e2nd_ = e2nd; }
   void setEtop(Float_t eTop) { eTop_ = eTop; }
   void setEbottom(Float_t eBottom) { eBottom_ = eBottom; }
   void setEleft(Float_t eLeft) { eLeft_ = eLeft; }
   void setEright(Float_t eRight) { eRight_ = eRight; }
   void setS4(Float_t s4) { s4_ = s4; }
   void setESratio(Float_t esRatio) { esRatio_ = esRatio; }
   void setSigmaIetaIeta(Float_t sigmaIetaIeta) { sigmaIetaIeta_ = sigmaIetaIeta; }
   void setSigmaIphiIphi(Float_t sigmaIphiIphi) { sigmaIphiIphi_ = sigmaIphiIphi; }
   void setSigmaIetaIphi(Float_t sigmaIetaIphi) { sigmaIetaIphi_ = sigmaIetaIphi; }
   void setSeedXtalIeta(Int_t seedXtalIeta) { seedXtalIeta_ = seedXtalIeta; }
   void setSeedXtalIphi(Int_t seedXtalIphi) { seedXtalIphi_ = seedXtalIphi; }
   void setDeltaEtaFromXtalCenter(Float_t deltaEtaFromXtalCenter) { deltaEtaFromXtalCenter_ = deltaEtaFromXtalCenter; }
   void setDeltaPhiFromXtalCenter(Float_t deltaPhiFromXtalCenter) { deltaPhiFromXtalCenter_ = deltaPhiFromXtalCenter; }
   void setCrackCorrectionEta(Float_t crackCorrectionEta) { crackCorrectionEta_ = crackCorrectionEta; }
   void setCrackCorrectionPhi(Float_t crackCorrectionPhi) { crackCorrectionPhi_ = crackCorrectionPhi; }
   void setCrackCorrectionEtaPhi(Float_t crackCorrectionEtaPhi) { crackCorrectionEtaPhi_ = crackCorrectionEtaPhi; }
   void setNxtals(Int_t nXtals) { nXtals_ = nXtals; }
   void setUid(UInt_t uid) { uid_ = uid; }
   void setSeedIndex(UInt_t seedIndex) { seedIndex_ = seedIndex; }
   void setHits(std::vector<TRootEcalRecHit> hits) { hits_ = hits; }
   
   
   friend std::ostream& operator<< (std::ostream& stream, const TRootCluster& clus)
   {
      stream << "TRootCluster - Type=" << clus.det() << "  (E,Et,eta,phi)=(" << clus.Mag() <<"," << clus.Pt() <<"," << clus.Eta() <<"," << clus.Phi() << ")"
      << " Calo position (x,y,z)=(" << clus.calX() << "," << clus.calY() << "," << clus.calZ() << ")" << " time=" << clus.time()
      << " e3x3=" << clus.e3x3() << " e5x5=" << clus.e5x5() << " eSeed=" << clus.eSeed()  << " eMax=" << clus.eMax() << " e2nd=" << clus.e2nd() << " s4=" << clus.s4() << " nXtals=" << clus.nXtals();
      return stream;
   };
   
   void Print()
   {
      std::cout << "TRootCluster - Type=" << this->det() << "  (E,Et,eta,phi)=(" << this->Mag() <<"," << this->Pt() <<"," << this->Eta() <<"," << this->Phi() << ")" << " Calo position (x,y,z)=(" << this->calX() << "," << this->calY() << "," << this->calZ() << ")" << endl
      << "            time=" << this->time() << " e2x2=" << this->e2x2() << " e3x3=" << this->e3x3() << " e5x5=" << this->e5x5() << " eSeed=" << this->eSeed()  << " eMax=" << this->eMax() << " e2nd=" << this->e2nd() << " eTop=" << this->eTop() << " eBottom=" << this->eBottom() << " eLeft=" << this->eLeft() << " eRight=" << this->eRight() << endl
      << "            s4=" << this->s4() << " esRatio=" << this->esRatio() << " sigmaIetaIeta=" << this->sigmaIetaIeta() << " sigmaIphiIphi=" << this->sigmaIphiIphi() << " sigmaIetaIphi=" << this->sigmaIetaIphi() << endl
      << "            seedXtalIeta=" << this->seedXtalIeta() << " seedXtalIphi=" << this->seedXtalIphi() << " deltaEtaFromXtalCenter=" << this->deltaEtaFromXtalCenter() << " deltaPhiFromXtalCenter=" << this->deltaPhiFromXtalCenter() << endl
      << "            crackCorrectionEta=" << this->crackCorrectionEta()<< " crackCorrectionPhi=" << this->crackCorrectionPhi()<< " crackCorrectionEtaPhi=" << this->crackCorrectionEtaPhi() << " nXtals=" << this->nXtals() << " seedIndex=" << this->seedIndex();
   };
   
   
protected:
   
   TVector3 position_; // Cluster position 
   Int_t det_;         // Cluster type: algo/detector/corrections (see above)
   Float_t time_;      // error-weighted average of time from rechits constituents of basic cluster 
   Float_t e2x2_;      // 2x2 xtals energy sum
   Float_t e3x3_;      // 3x3 xtals energy sum
   Float_t e5x5_;      // 5x5 xtals energy sum
   Float_t eSeed_;     // Energy of the seed xtal
   Float_t eMax_;      // Max xtal energy
   Float_t e2nd_;      // Energy of the 2nd highest energy xtal in the cluster (different fron David Petyt "E2" which is the 2nd highest energy xtal surrounding the seed xtal (i.e. in the 3x3 matrix))
   Float_t eTop_;
   Float_t eBottom_;
   Float_t eLeft_;
   Float_t eRight_;
   Float_t s4_;        // Energy in swiss cross
   Float_t esRatio_;   // Ratio E3/E21 of energy in ES planes
   Float_t sigmaIetaIeta_;
   Float_t sigmaIphiIphi_;
   Float_t sigmaIetaIphi_;
   Int_t seedXtalIeta_; // iphi of the seed xtal (EB only)
   Int_t seedXtalIphi_; // iphi of the seed xtal (EB only)
   Float_t deltaEtaFromXtalCenter_;  // local coordinates with respect to closest crystal center at nominal shower depth (EB only)
   Float_t deltaPhiFromXtalCenter_;  // local coordinates with respect to closest crystal center at nominal shower depth (EB only)
   Float_t crackCorrectionEta_;    //Corrected cracks eta energy 
   Float_t crackCorrectionPhi_;    //Corrected cracks phi energy
   Float_t crackCorrectionEtaPhi_; //Corrected cracks eta phi energy
   Int_t nXtals_; // Number of xtals in the Basic Cluster
   UInt_t uid_;   // Unique Identifier
   
   UInt_t seedIndex_; // position of the seed crystal in the hits_ vector
   std::vector<TRootEcalRecHit> hits_;  // associated Ecal rechits
   
   ClassDef (TRootCluster,10);
   
};


#endif
