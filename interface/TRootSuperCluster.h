#ifndef TRootSuperCluster_h
#define TRootSuperCluster_h

/************************************************************************************************************************************
SuperCluster Type: ijk
i = algo =>  1=Island , 2=Hybrid, 3=multi5x5
j = detector => 1=ECAL Barrel , 2=ECAL Endcap
k = corrections => 0=nopreshower / uncorrected  ,  1=no preshower / standard CMSSW corections
2=preshower / standard CMSSW corections  ,  3= preshower / uncorrected

110 => Island Barrel SuperClusters
120 => Island Endcap SuperClusters
121 => Corrected Island Endcap SuperClusters (standard CMSSW corrections)
122 => Corrected Island Endcap SuperClusters with Preshower (standard CMSSW corrections)
210 => Hybrid Barrel SuperClusters
211 => Corrected Hybrid Barrel SuperClusters (standard CMSSW corrections)
320 => Multi5x5 Endcap SuperClusters
322 => Corrected Multi5x5 Endcap SuperClusters with Preshower (standard CMSSW corrections)
323 => Multi5x5 Endcap SuperClusters with Preshower

************************************************************************************************************************************/

#include <string>
#include <iostream>
#include <vector>

#include "Rtypes.h"

#include "../interface/TRootCluster.h"

using namespace std;

class TRootPhoton;
class TRootElectron;

class TRootSuperCluster : public TRootCluster
{
   
   public:
      
      TRootSuperCluster() :
      TRootCluster()
      ,rawEnergy_(-1.)
      ,crackCorrectionEta_(-1.)
      ,crackCorrectionPhi_(-1.)
      ,crackCorrectionEtaPhi_(-1.)
      ,preshowerEnergy_(-1.)
      ,etaWidth_(-1.)
      ,phiWidth_(-1.)
      ,hoe1_(-1.)
      ,hoe2_(-1.)
      ,nBasicClusters_(-1)
      ,subBasicClusterUIDVector_()
      ,subBasicClusterIndexVector_()
      ,seedBasicClusterVectorIndex_(-1)
      ,subBasicClusterRefVector_()
      ,seedBasicCluster_(0)
      ,photonIndex_(-1)
      ,photon_(0)
      ,electronIndex_(-1)
      ,electron_(0)
      {;}
      
      TRootSuperCluster(const TRootSuperCluster& cluster) :
      TRootCluster(cluster)
      ,rawEnergy_(cluster.rawEnergy_)
      ,crackCorrectionEta_(cluster.crackCorrectionEta_)
      ,crackCorrectionPhi_(cluster.crackCorrectionPhi_)
      ,crackCorrectionEtaPhi_(cluster.crackCorrectionEtaPhi_)
      ,preshowerEnergy_(cluster.preshowerEnergy_)
      ,etaWidth_(cluster.etaWidth_)
      ,phiWidth_(cluster.phiWidth_)
      ,hoe1_(cluster.hoe1_)
      ,hoe2_(cluster.hoe2_)
      ,nBasicClusters_(cluster.nBasicClusters_)
      ,subBasicClusterUIDVector_(cluster.subBasicClusterUIDVector_)
      ,subBasicClusterIndexVector_(cluster.subBasicClusterIndexVector_)
      ,seedBasicClusterVectorIndex_(cluster.seedBasicClusterVectorIndex_)
      ,subBasicClusterRefVector_(cluster.subBasicClusterRefVector_)
      ,seedBasicCluster_(cluster.seedBasicCluster_)
      ,photonIndex_(cluster.photonIndex_)
      ,photon_(cluster.photon_)
      ,electronIndex_(cluster.electronIndex_)
      ,electron_(cluster.photon_)
      {;}
      
      TRootSuperCluster(Double_t energy, Double_t eta, Double_t phi) :
      TRootCluster(energy, eta, phi)
      ,rawEnergy_(-1.)
      ,crackCorrectionEta_(-1.)
      ,crackCorrectionPhi_(-1.)
      ,crackCorrectionEtaPhi_(-1.)      
      ,preshowerEnergy_(-1.)
      ,etaWidth_(-1.)
      ,phiWidth_(-1.)
      ,hoe1_(-1.)
      ,hoe2_(-1.)
      ,nBasicClusters_(-1)
      ,subBasicClusterUIDVector_()
      ,subBasicClusterIndexVector_()
      ,seedBasicClusterVectorIndex_(-1)
      ,subBasicClusterRefVector_()
      ,seedBasicCluster_(0)
      ,photonIndex_(-1)
      ,photon_(0)
      ,electronIndex_(-1)
      ,electron_(0)
      {;}
      
      TRootSuperCluster(Double_t energy, Double_t eta, Double_t phi, Double_t x, Double_t y, Double_t z) :
      TRootCluster(energy, eta, phi, x, y, z)
      ,rawEnergy_(-1.)
      ,crackCorrectionEta_(-1.)
      ,crackCorrectionPhi_(-1.)
      ,crackCorrectionEtaPhi_(-1.)
      ,preshowerEnergy_(-1.)
      ,etaWidth_(-1.)
      ,phiWidth_(-1.)
      ,hoe1_(-1.)
      ,hoe2_(-1.)
      ,nBasicClusters_(-1)
      ,subBasicClusterUIDVector_()
      ,subBasicClusterIndexVector_()
      ,seedBasicClusterVectorIndex_(-1)
      ,subBasicClusterRefVector_()
      ,seedBasicCluster_(0)
      ,photonIndex_(-1)
      ,photon_(0)
      ,electronIndex_(-1)
      ,electron_(0)
      {;}
      
      TRootSuperCluster(Double_t energy, Double_t eta, Double_t phi, Double_t x, Double_t y, Double_t z, Int_t det) :
      TRootCluster(energy, eta, phi, x, y, z, det)
      ,rawEnergy_(-1.)
      ,crackCorrectionEta_(-1.)
      ,crackCorrectionPhi_(-1.)
      ,crackCorrectionEtaPhi_(-1.)
      ,preshowerEnergy_(-1.)
      ,etaWidth_(-1.)
      ,phiWidth_(-1.)
      ,hoe1_(-1.)
      ,hoe2_(-1.)
      ,nBasicClusters_(-1)
      ,subBasicClusterUIDVector_()
      ,subBasicClusterIndexVector_()
      ,seedBasicClusterVectorIndex_(-1)
      ,subBasicClusterRefVector_()
      ,seedBasicCluster_(0)
      ,photonIndex_(-1)
      ,photon_(0)
      ,electronIndex_(-1)
      ,electron_(0)
      {;}
      
      ~TRootSuperCluster() {;}
      
      // ECAL Raw Energy
      Float_t rawEnergy() const   { return rawEnergy_; }

      // ECAL Raw Energy Corrected Cracks
      Float_t crackCorrectionEta() const   { return crackCorrectionEta_; }
      Float_t crackCorrectionPhi() const   { return crackCorrectionPhi_; }
      Float_t crackCorrectionEtaPhi() const   { return crackCorrectionEtaPhi_; }

      // Preshower Energy
      Float_t preshowerEnergy() const   { return preshowerEnergy_; }
      
      // etaWidth
      Float_t etaWidth() const   { return etaWidth_; }
      
      // phiWidth
      Float_t phiWidth() const   { return phiWidth_; }
      
      // Energy in first layer of HCAL tower behind SC over SC energy
      Float_t hoe1() const   { return hoe1_; }
      
      // Energy in second layer of HCAL tower behind SC over SC energy
      Float_t hoe2() const   { return hoe2_; }
      
      // Number of  Basic Cluster constituents
      Int_t nBasicClusters() const   { return nBasicClusters_; }
      
      // UIDs of the Basic Cluster constituents
      std::vector<UInt_t> subBasicClusterUIDVector() const { return subBasicClusterUIDVector_; }
      
      // Indexes in TCloneArray ("BasicClusters" branch) of the Basic Cluster constituents
      std::vector<Int_t> subBasicClusterIndexVector() const { return subBasicClusterIndexVector_; }
      
      // Index in TCloneArray ("BasicClusters" branch) of the seed Basic Cluster
      Int_t seedBasicClusterIndex() const
      {
         if( Int_t(subBasicClusterIndexVector_.size())>seedBasicClusterVectorIndex_)
         {
            return subBasicClusterIndexVector_.at(seedBasicClusterVectorIndex_);
         }
         else
         {
            cout << "No seed BasicCluster in this SuperCluster...." << endl;
            return -1;
         }
      }
      
      // Get the ith Basic Cluster constituent stocked in subBasicClusterRefVector_
      TRootCluster* subBasicClusterAt(UInt_t index) const
      {
         if ( index>=subBasicClusterRefVector_.size())
         {
            return 0;
         }
         else
         {
            return (TRootCluster*) subBasicClusterRefVector_.at(index).GetObject();
         }
      }
      
      // Get the vector containing the references to Basic Cluster constituent
      std::vector<TRef> subBasicClusterRefVector() const { return subBasicClusterRefVector_; }
      
      // Get the seed Basic Cluster
      TRootCluster* seedBasicCluster() const  { return (TRootCluster*) seedBasicCluster_.GetObject();}
      
      // Index in TCloneArray ("Photons" branch) of the possible associated photon
      Int_t photonIndex() const   { return photonIndex_; }
      
      // Get possible associated photon
      TRootPhoton* photon() const  { return (TRootPhoton*) photon_.GetObject();}
      
      // Index in TCloneArray ("Electrons" branch) of the possible associated electron
      Int_t electronIndex() const   { return electronIndex_; }
      
      // Get possible associated electron
      TRootElectron* electron() const  { return (TRootElectron*) electron_.GetObject();}
      
      // is associated to a photon ?
      Bool_t isPhoton() const { return ( photon_.GetObject() == 0 ? false : true); }
      
      // is associated to an electron ?
      Bool_t isElectron() const { return ( electron_.GetObject() == 0 ? false : true); }
      
      // Name of the clustering algorithm
      TString typeName() const
      {
         if ( det_==110 ) return "Island Barrel SC";
         else if ( det_==120 ) return "Island Endcap SC";
         else if ( det_==121 ) return "Corrected Island Endcap SC";
         else if ( det_==122 ) return "Corrected Island Endcap with Preshower SC";
         else if ( det_==210 ) return "Hybrid Barrel SC";
         else if ( det_==211 ) return "Corrected Hybrid Barrel SC";
         else if ( det_==320 ) return "Multi5x5 Endcap SC";
         else if ( det_==322 ) return "Corrected Multi5x5 Endcap with Preshower SC";
         else if ( det_==323 ) return "Multi5x5 Endcap with Preshower SC";
         else return "Unknown type SC";
      }
      
      void setRawEnergy(Float_t rawEnergy) { rawEnergy_ = rawEnergy; }
      void setcrackCorrectionEta(Float_t crackCorrectionEta) { crackCorrectionEta_ = crackCorrectionEta; }
      void setcrackCorrectionPhi(Float_t crackCorrectionPhi) { crackCorrectionPhi_ = crackCorrectionPhi; }
      void setcrackCorrectionEtaPhi(Float_t crackCorrectionEtaPhi) { crackCorrectionEtaPhi_ = crackCorrectionEtaPhi; }
      void setPreshowerEnergy(Float_t preshowerEnergy) { preshowerEnergy_ = preshowerEnergy; }
      void setEtaWidth(Float_t etaWidth) { etaWidth_ = etaWidth; }
      void setPhiWidth(Float_t phiWidth) { phiWidth_ = phiWidth; }
      void setHoe1(Float_t hoe1) { hoe1_ = hoe1; }
      void setHoe2(Float_t hoe2) { hoe2_ = hoe2; }
      void setNBasicClusters(Int_t nBasicClusters) { nBasicClusters_ = nBasicClusters; }
      void addSubBasicClusterUID(UInt_t uid) { subBasicClusterUIDVector_.push_back(uid); }
      void clearSubBasicClusterUID() { subBasicClusterUIDVector_.clear(); }
      void addSubBasicClusterIndex(Int_t idx) { subBasicClusterIndexVector_.push_back(idx); }
      void clearSubBasicClusterIndex() { subBasicClusterIndexVector_.clear(); }
      void setSeedBasicClusterVectorIndex(Int_t  seedBasicClusterVectorIndex) { seedBasicClusterVectorIndex_ = seedBasicClusterVectorIndex; }
      void addSubBasicCluster(TObject* subBasicCluster) { subBasicClusterRefVector_.push_back(subBasicCluster); }
      void clearSubBasicCluster() { subBasicClusterRefVector_.clear(); }
      void setSeedBasicCluster(TObject* seedBasicCluster) { seedBasicCluster_ = seedBasicCluster; }
      void setPhotonIndex(Int_t photonIndex) { photonIndex_ = photonIndex; }
      void setPhoton(TObject* photon) { photon_ = photon; }
      void setElectronIndex(Int_t electronIndex) { electronIndex_ = electronIndex; }
      void setElectron(TObject* electron) { electron_ = electron; }
      
      
      friend std::ostream& operator<< (std::ostream& stream, const TRootSuperCluster& clus)
      {
         stream << "TRootSuperCluster - Type=" << clus.det_ << "  (E,Et,eta,phi)=(" << clus.Mag() <<"," << clus.Pt() <<"," << clus.Eta() <<"," << clus.Phi() << ")"
         << " Calo position (x,y,z)=(" << clus.calX() << "," << clus.calY() << "," << clus.calZ() << ")" << " time=" << clus.time()
         << " nBC=" << clus.nBasicClusters() << " e3x3=" << clus.e3x3() << " e5x5=" << clus.e5x5() << " eMax=" << clus.eMax()<< " e2nd=" << clus.e2nd()
         << " hoe1=" << clus.hoe1() << " hoe2=" << clus.hoe2() << " nXtals=" << clus.nXtals() << " E_presh=" << clus.preshowerEnergy() << " E_raw=" << clus.rawEnergy()
         << " E_raw_CorrectedCracksEta=" << clus.crackCorrectionEta() * clus.Mag() << " E_raw_CorrectedCracksPhi=" << clus.crackCorrectionPhi() * clus.Mag()
         << " E_raw_CorrectedCracksEtaPhi=" << clus.crackCorrectionEtaPhi() * clus.Mag();
         return stream;
      };
      
      void Print()
      {
         std::cout << "TRootSuperCluster - Type=" << this->det() << "  (E,Et,eta,phi)=(" << this->Mag() <<"," << this->Pt() <<"," << this->Eta() <<"," << this->Phi() << ")" << " Calo position (x,y,z)=(" << this->calX() << "," << this->calY() << "," << this->calZ() << ")" << endl
         << "            E_presh=" << this->preshowerEnergy() << " E_raw=" << this->rawEnergy() << " E_raw_CorrectedCracksEta="<<this->crackCorrectionEta() * this->Mag() << " E_raw_CorrectedCracksPhi="<<this->crackCorrectionPhi() * this->Mag() << " E_raw_CorrectedCracksEtaPhi="<<this->crackCorrectionEtaPhi() * this->Mag() << endl
         << "            time=" << this->time() << " e2x2=" << this->e2x2() << " e3x3=" << this->e3x3() << " e5x5=" << this->e5x5() << " eMax=" << this->eMax() << " e2nd=" << this->e2nd() << " eTop=" << this->eTop() << " eBottom=" << this->eBottom() << " eLeft=" << this->eLeft() << " eRight=" << this->eRight() << endl
         << "            s4=" << this->s4() << " esRatio=" << this->esRatio() << " etaWidth=" << this->etaWidth() << " phiWidth=" << this->phiWidth() << " sigmaIetaIeta=" << this->sigmaIetaIeta() << " sigmaIphiIphi=" << this->sigmaIphiIphi() << " sigmaIetaIphi=" << this->sigmaIetaIphi() << endl
         << "            seedXtalIeta=" << this->seedXtalIeta() << " seedXtalIphi=" << this->seedXtalIphi() << " deltaEtaFromXtalCenter=" << this->deltaEtaFromXtalCenter() << " deltaPhiFromXtalCenter=" << this->deltaPhiFromXtalCenter() << endl
         << "            crackCorrectionEta=" << this->crackCorrectionEta()<< " crackCorrectionPhi=" << this->crackCorrectionPhi()<< " crackCorrectionEtaPhi=" << this->crackCorrectionEtaPhi()<< " nXtals=" << this->nXtals() << " nBC=" << this->nBasicClusters();
         
      };
      
      
   protected:
      
      Float_t rawEnergy_;
      Float_t crackCorrectionEta_;
      Float_t crackCorrectionPhi_;
      Float_t crackCorrectionEtaPhi_;
      Float_t preshowerEnergy_;
      Float_t etaWidth_;
      Float_t phiWidth_;
      Float_t hoe1_;
      Float_t hoe2_;
      Int_t nBasicClusters_;
      std::vector<UInt_t> subBasicClusterUIDVector_;
      std::vector<Int_t> subBasicClusterIndexVector_;
      Int_t seedBasicClusterVectorIndex_; // position in subBasicClusterIndexVector_ and subBasicClusterRefVector_ of the seedBasicCluster
      std::vector<TRef> subBasicClusterRefVector_;
      TRef seedBasicCluster_;
      Int_t photonIndex_;
      TRef photon_;
      Int_t electronIndex_;
      TRef electron_;
      
      ClassDef (TRootSuperCluster,10);
      
};

#endif
