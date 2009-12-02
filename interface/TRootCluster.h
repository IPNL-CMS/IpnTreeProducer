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
		,seedTime_(-999999.)
		,uid_(0)
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
		,seedTime_(cluster.seedTime_)
		,uid_(cluster.uid_)
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
		,seedTime_(-999999.)
		,uid_(0)
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
		,seedTime_(-999999.)
		,uid_(0)
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
		,seedTime_(-999999.)
		,uid_(0)
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
		,seedTime_(-999999.)
		,uid_(0)
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
		,seedTime_(-999999.)
		,uid_(0)
		{;}
		
		~TRootCluster() {;}
		
		
		Double_t calX() const  { return position_.x(); }
		Double_t calY() const  { return position_.y(); }
		Double_t calZ() const  { return position_.z(); }
		Int_t det() const  { return det_; }
		Int_t type() const  { return det_; }
		Double_t e2x2() const   { return e2x2_; }
		Double_t e3x3() const   { return e3x3_; }
		Double_t e5x5() const   { return e5x5_; }
		Double_t eMax() const   { return eMax_; }
		Double_t e2nd() const   { return e2nd_; }
		Int_t nXtals() const   { return nXtals_; }
		Double_t seedTime() const   { return seedTime_; }
		UInt_t uid() const   { return uid_; }
		TString typeName() const {
			if ( det_==110 ) return "Island Barrel BC";
			else if ( det_==120 ) return "Island Endcap BC";
			else if ( det_==210 ) return "Hybrid Barrel BC";
			else if ( det_==320 ) return "Multi5x5 Endcap BC";
			else return "Unknown type SC";
		}
		
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
		void setSeedTime(Float_t seedTime) { seedTime_ = seedTime; }
		void setUid(UInt_t uid) { uid_ = uid; }
		
		
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
		
		TVector3 position_;
		Int_t det_;
		Double_t e2x2_;
		Double_t e3x3_;
		Double_t e5x5_;
		Double_t eMax_;
		Double_t e2nd_;
		Int_t nXtals_;
		Float_t seedTime_;
		UInt_t uid_;
		
		ClassDef (TRootCluster,3);
		
};

#endif
