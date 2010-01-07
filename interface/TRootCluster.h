#ifndef TRootCluster_h
#define TRootCluster_h

/************************************************************************************************************************************
Cluster Type: ijk
i = algo =>  1=Island , 2=Hybrid, 3=multi5x5, 4=IslandWeight
j = detector => 1=ECAL Barrel , 2=ECAL Endcap
k = corrections => 0=nopreshower / uncorrected  ,  1=no preshower / standard CMSSW corections
2=preshower / standard CMSSW corections  ,  3= preshower / uncorrected

BasicClusters
110 => Island Barrel BasicClusters
120 => Island Endcap BasicClusters
210 => hybrid Barrel BasicClusters
310 => multi5x5 Barrel BasicClusters
320 => multi5x5 Endcap BasicClusters

SuperClusters
110 => Island Barrel SuperClusters
120 => Island Endcap SuperClusters
121 => Corrected Island Endcap SuperClusters (standard CMSSW corrections)
122 => Corrected Island Endcap SuperClusters with Preshower (standard CMSSW corrections)
210 => Hybrid Barrel SuperClusters
211 => Corrected Hybrid Barrel SuperClusters (standard CMSSW corrections)
320 => Multi5x5 Endcap SuperClusters
322 => Corrected Multi5x5 Endcap SuperClusters with Preshower (standard CMSSW corrections)
323 => Multi5x5 Endcap SuperClusters with Preshower

Shapes variables (e3x3, e5x5, eMax, e2nd) are not modified by CMSSW energy corrections
Shapes variables for SuperClusters correspond to shapes variables of the seed BasicCluster

************************************************************************************************************************************/

#include <string>
#include <iostream>

#include "Rtypes.h"
#include "TVector3.h"
#include "TMath.h"
#include "TRef.h"

using namespace std;

class TRootCluster : public TVector3
{
	
	public:
		
		enum Flags
		{
			kGood                  // channel ok, the energy and time measurement are reliable
			,kPoorReco             // the energy is available from the UncalibRecHit, but approximate (bad shape, large chi2)
			,kOutOfTime            // the energy is available from the UncalibRecHit (sync reco), but the event is out of time
			,kFaultyHardware       // The energy is available from the UncalibRecHit, channel is faulty at some hardware level (e.g. noisy)
			,kPoorCalib            // the energy is available from the UncalibRecHit, but the calibration of the channel is poor
			,kSaturated            // saturated channel (recovery not tried)
			,kLeadingEdgeRecovered // saturated channel: energy estimated from the leading edge before saturation
			,kNeighboursRecovered  // saturated/isolated dead: energy estimated from neighbours
			,kTowerRecovered       // channel in TT with no data link, info retrieved from Trigger Primitive
			,kDead                 // channel is dead and any recovery fails
		};
		

		TRootCluster() :
		TVector3()
		,position_(-999999.,-999999.,-999999.)
		,det_(-1)
		,e2x2_(-1.)
		,e3x3_(-1.)
		,e5x5_(-1.)
		,eMax_(-1.)
		,e2nd_(-1.)
		,nXtals_(-1)
		,uid_(0)
		,hitsDetector_(0)
		,hitsFlag_(0)
		,hitsEnergy_(0)
		,hitsTime_(0)
		,hitsPosition1_(0)
		,hitsPosition2_(0)
		{;}
		
		TRootCluster(const TRootCluster& cluster) :
		TVector3(cluster)
		,position_(cluster.position_)
		,det_(cluster.det_)
		,e2x2_(cluster.e2x2_)
		,e3x3_(cluster.e3x3_)
		,e5x5_(cluster.e5x5_)
		,eMax_(cluster.eMax_)
		,e2nd_(cluster.e2nd_)
		,nXtals_(cluster.nXtals_)
		,uid_(cluster.uid_)
		,hitsDetector_(cluster.hitsDetector_)
		,hitsFlag_(cluster.hitsFlag_)
		,hitsEnergy_(cluster.hitsEnergy_)
		,hitsTime_(cluster.hitsTime_)
		,hitsPosition1_(cluster.hitsPosition1_)
		,hitsPosition2_(cluster.hitsPosition2_)
		{;}

		TRootCluster(Double_t energy, Double_t eta, Double_t phi) :
		position_(-999999.,-999999.,-999999.)
		,det_(-1)
		,e2x2_(-1.)
		,e3x3_(-1.)
		,e5x5_(-1.)
		,eMax_(-1.)
		,e2nd_(-1.)
		,nXtals_(-1)
		,uid_(0)
		,hitsDetector_(0)
		,hitsFlag_(0)
		,hitsEnergy_(0)
		,hitsTime_(0)
		,hitsPosition1_(0)
		,hitsPosition2_(0)
		{
			this->SetPtEtaPhi(energy*TMath::Sin(2.0*TMath::ATan(TMath::Exp(-eta))), eta, phi);
		}
		
		TRootCluster(Double_t energy, Double_t eta, Double_t phi, Double_t x, Double_t y, Double_t z) :
		position_(x,y,z)
		,det_(-1)
		,e2x2_(-1.)
		,e3x3_(-1.)
		,e5x5_(-1.)
		,eMax_(-1.)
		,e2nd_(-1.)
		,nXtals_(-1)
		,uid_(0)
		,hitsDetector_(0)
		,hitsFlag_(0)
		,hitsEnergy_(0)
		,hitsTime_(0)
		,hitsPosition1_(0)
		,hitsPosition2_(0)
		{
			this->SetPtEtaPhi(energy*TMath::Sin(2.0*TMath::ATan(TMath::Exp(-eta))), eta, phi);
		}
		
		TRootCluster(Double_t energy, Double_t eta, Double_t phi, Double_t x, Double_t y, Double_t z, Int_t det) :
		position_(x,y,z)
		,det_(det)
		,e2x2_(-1.)
		,e3x3_(-1.)
		,e5x5_(-1.)
		,eMax_(-1.)
		,e2nd_(-1.)
		,nXtals_(-1)
		,uid_(0)
		,hitsDetector_(0)
		,hitsFlag_(0)
		,hitsEnergy_(0)
		,hitsTime_(0)
		,hitsPosition1_(0)
		,hitsPosition2_(0)
		{
			this->SetPtEtaPhi(energy*TMath::Sin(2.0*TMath::ATan(TMath::Exp(-eta))), eta, phi);
		}
		
		TRootCluster(const TVector3 &momentum) :
		TVector3(momentum)
		,position_(-999999.,-999999.,-999999.)
		,det_(-1)
		,e2x2_(-1.)
		,e3x3_(-1.)
		,e5x5_(-1.)
		,eMax_(-1.)
		,e2nd_(-1.)
		,nXtals_(-1)
		,uid_(0)
		,hitsDetector_(0)
		,hitsFlag_(0)
		,hitsEnergy_(0)
		,hitsTime_(0)
		,hitsPosition1_(0)
		,hitsPosition2_(0)
		{;}
		
		
		TRootCluster(const TVector3 &momentum, const TVector3 &position, Int_t det) :
		TVector3(momentum)
		,position_(position)
		,det_(det)
		,e2x2_(-1.)
		,e3x3_(-1.)
		,e5x5_(-1.)
		,eMax_(-1.)
		,e2nd_(-1.)
		,nXtals_(-1)
		,uid_(0)
		,hitsDetector_(0)
		,hitsFlag_(0)
		,hitsEnergy_(0)
		,hitsTime_(0)
		,hitsPosition1_(0)
		,hitsPosition2_(0)
		{;}
		
		~TRootCluster() {;}
		
		
		Double_t calX() const { return position_.x(); }
		Double_t calY() const { return position_.y(); }
		Double_t calZ() const { return position_.z(); }
		Int_t det() const { return det_; }
		Int_t type() const { return det_; }
		Double_t e2x2() const { return e2x2_; }
		Double_t e3x3() const { return e3x3_; }
		Double_t e5x5() const { return e5x5_; }
		Double_t eMax() const { return eMax_; }
		Double_t e2nd() const { return e2nd_; }
		Int_t nXtals() const { return nXtals_; }
		UInt_t uid() const { return uid_; }
		std::vector<int> hitsDetector() const { return hitsDetector_; }
		std::vector<int> hitsFlag() const { return hitsFlag_; }
		std::vector<float> hitsEnergy() const { return hitsEnergy_; }
		std::vector<float> hitsTime() const { return hitsTime_; }
		std::vector<int> hitsPosition1() const { return hitsPosition1_; }
		std::vector<int> hitsPosition2() const { return hitsPosition2_; }
		Int_t seedDetector() const { return ( (hitsDetector_.size()>0) ? hitsDetector_.at(0) : -1 ); }
		Int_t seedFlag() const { return ( (hitsFlag_.size()>0) ? hitsFlag_.at(0) : -1 ); }
		Float_t seedTime() const { return ( (hitsTime_.size()>0) ? hitsTime_.at(0) : -999999. ); }
		Float_t seedEnergy() const { return ( (hitsEnergy_.size()>0) ? hitsEnergy_.at(0) : -999999. ); }
		Int_t seedPosition1() const { return ( (hitsPosition1_.size()>0) ? hitsPosition1_.at(0) : 0 ); }
		Int_t seedPosition2() const { return ( (hitsPosition2_.size()>0) ? hitsPosition2_.at(0) : 0 ); }
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
		void setType(Int_t det) { det_ = det; }
		void setE2x2(Double_t e2x2) { e2x2_ = e2x2; }
		void setE3x3(Double_t e3x3) { e3x3_ = e3x3; }
		void setE5x5(Double_t e5x5) { e5x5_ = e5x5; }
		void setEmax(Double_t eMax) { eMax_ = eMax; }
		void setE2nd(Double_t e2nd) { e2nd_ = e2nd; }
		void setNxtals(Int_t nXtals) { nXtals_ = nXtals; }
		void setUid(UInt_t uid) { uid_ = uid; }
		void setHitsDetector(std::vector<int> hitsDetector) { hitsDetector_ = hitsDetector; }
		void setHitsFlag(std::vector<int> hitsFlag) { hitsFlag_ = hitsFlag; }
		void setHitsEnergy(std::vector<float> hitsEnergy) { hitsEnergy_ = hitsEnergy; }
		void setHitsTime(std::vector<float> hitsTime) { hitsTime_ = hitsTime; }
		void setHitsPosition1(std::vector<int> hitsPosition1) { hitsPosition1_ = hitsPosition1; }
		void setHitsPosition2(std::vector<int> hitsPosition2) { hitsPosition2_ = hitsPosition2; }
		
		
		friend std::ostream& operator<< (std::ostream& stream, const TRootCluster& clus)
		{
			stream << "TRootCluster - Type=" << clus.det() << "  (E,Et,eta,phi)=(" << clus.Mag() <<"," << clus.Pt() <<"," << clus.Eta() <<"," << clus.Phi() << ")"
			<< " Calo position (x,y,z)=(" << clus.calX() << "," << clus.calY() << "," << clus.calZ() << ")"
			<< " e3x3=" << clus.e3x3() << " e5x5=" << clus.e5x5() << " eMax=" << clus.eMax()<< " e2nd=" << clus.e2nd() << " nXtals=" << clus.nXtals() << " t_max(Pulse)=" << clus.seedTime();
			return stream;
		};
		
		void Print()
		{
			std::cout << "TRootCluster - Type=" << this->det() << "  (E,Et,eta,phi)=(" << this->Mag() <<"," << this->Pt() <<"," << this->Eta() <<"," << this->Phi() << ")"
			<< " Calo position (x,y,z)=(" << this->calX() << "," << this->calY() << "," << this->calZ() << ")"
			<< " e3x3=" << this->e3x3() << " e5x5=" << this->e5x5() << " eMax=" << this->eMax()<< " e2nd=" << this->e2nd() << " nXtals=" << this->nXtals() << " t_max(Pulse)=" << this->seedTime();
		};
		
		
	protected:
		
		TVector3 position_; // Cluster position 
		Int_t det_;         // Cluster type: algo/detector/corrections (see above)
		Double_t e2x2_;     // 2x2 xtals energy sum
		Double_t e3x3_;     // 3x3 xtals energy sum
		Double_t e5x5_;     // 5x5 xtals energy sum
		Double_t eMax_;     // Max xtal energy
		Double_t e2nd_;     // Energy of the 2nd highest energy xtal
		Int_t nXtals_;      // Number of xtals in the Basic Cluster
		UInt_t uid_;        // Unique Identifier
		
		std::vector<int> hitsDetector_;  // detector containing the rechit
		std::vector<int> hitsFlag_;      // rechit reco quality flag
		std::vector<float> hitsEnergy_;  // rechit energy
		std::vector<float> hitsTime_;    // rechit time
		std::vector<int> hitsPosition1_; // ieta or ix of the rechit
		std::vector<int> hitsPosition2_; // iphi or iy of the rechit
		
		ClassDef (TRootCluster,4);
		
};

#endif
