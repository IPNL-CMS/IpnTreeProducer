#ifndef TRootMCParticle_h
#define TRootMCParticle_h

#include "../interface/TRootParticle.h"

using namespace std;

class TRootMCParticle : public TRootParticle
{

   public:

      TRootMCParticle() :
      TRootParticle()
      ,status_(0)
      ,nDau_(0)
      ,motherType_(0)
      ,grannyType_(0)
      ,oldgrannyType_(0)
      ,dauOneId_(0)
      ,dauTwoId_(0)
      ,dauThreeId_(0)
      ,dauFourId_(0)
      ,indexInList_(-1)
      {;}

      TRootMCParticle(const TRootMCParticle& particle) :
      TRootParticle(particle)
      ,status_(particle.status_)
      ,nDau_(particle.nDau_)
      ,motherType_(particle.motherType_)
      ,grannyType_(particle.grannyType_)
      ,oldgrannyType_(particle.oldgrannyType_)
      ,dauOneId_(particle.dauOneId_)
      ,dauTwoId_(particle.dauTwoId_)
      ,dauThreeId_(particle.dauThreeId_)
      ,dauFourId_(particle.dauFourId_)
      ,indexInList_(particle.indexInList_)
      {;}

      TRootMCParticle(Double_t px, Double_t py, Double_t pz, Double_t e) :
      TRootParticle(px,py,pz,e)
      ,status_(0)
      ,nDau_(0)
      ,motherType_(0)
      ,grannyType_(0)
      ,oldgrannyType_(0)
      ,dauOneId_(0)
      ,dauTwoId_(0)
      ,dauThreeId_(0)
      ,dauFourId_(0)
      ,indexInList_(-1)
      {;}

      TRootMCParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
      ,status_(0)
      ,nDau_(0)
      ,motherType_(0)
      ,grannyType_(0)
      ,oldgrannyType_(0)
      ,dauOneId_(0)
      ,dauTwoId_(0)
      ,dauThreeId_(0)
      ,dauFourId_(0)
      ,indexInList_(-1)
      {;}

      TRootMCParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z,Int_t type, Float_t charge) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
      ,status_(0)
      ,nDau_(0)
      ,motherType_(0)
      ,grannyType_(0)
      ,oldgrannyType_(0)
      ,dauOneId_(0)
      ,dauTwoId_(0)
      ,dauThreeId_(0)
      ,dauFourId_(0)
      ,indexInList_(-1)
      {;}

      TRootMCParticle(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z,Int_t type, Float_t charge, Int_t status, Int_t nDau, Int_t motherType, Int_t grannyType, Int_t oldgrannyType, Int_t dauOneId, Int_t dauTwoId, Int_t dauThreeId, Int_t dauFourId, Int_t indexInList) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
      ,status_(status)
      ,nDau_(nDau)
      ,motherType_(motherType)
      ,grannyType_(grannyType)
      ,oldgrannyType_(oldgrannyType)
      ,dauOneId_(dauOneId)
      ,dauTwoId_(dauTwoId)
      ,dauThreeId_(dauThreeId)
      ,dauFourId_(dauFourId)
      ,indexInList_(indexInList)
      {;}

      TRootMCParticle(const TLorentzVector &momentum) :
      TRootParticle(momentum)
      ,status_(0)
      ,nDau_(0)
      ,motherType_(0)
      ,grannyType_(0)
      ,oldgrannyType_(0)
      ,dauOneId_(0)
      ,dauTwoId_(0)
      ,dauThreeId_(0)
      ,dauFourId_(0)
      ,indexInList_(-1)
      {;}

      TRootMCParticle(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
      TRootParticle(momentum, vertex, type, charge)
      ,status_(0)
      ,nDau_(0)
      ,motherType_(0)
      ,grannyType_(0)
      ,oldgrannyType_(0)
      ,dauOneId_(0)
      ,dauTwoId_(0)
      ,dauThreeId_(0)
      ,dauFourId_(0)
      ,indexInList_(-1)
      {;}

	TRootMCParticle(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge, Int_t status, Int_t nDau, Int_t motherType, Int_t grannyType, Int_t oldgrannyType, Int_t dauOneId, Int_t dauTwoId, Int_t dauThreeId, Int_t dauFourId, Int_t indexInList) :
      TRootParticle(momentum, vertex, type, charge)
      ,status_(status)
      ,nDau_(nDau)
      ,motherType_(motherType)
      ,grannyType_(grannyType)
      ,oldgrannyType_(oldgrannyType)
      ,dauOneId_(dauOneId)
      ,dauTwoId_(dauTwoId)
      ,dauThreeId_(dauThreeId)
      ,dauFourId_(dauFourId)
      ,indexInList_(indexInList)
      {;}

      ~TRootMCParticle() {;}


      Int_t status() const {return status_; }
      Int_t nDau() const {return nDau_; }
      Int_t motherType() const {return motherType_; }
      Int_t grannyType() const {return grannyType_; }
      Int_t oldgrannyType() const {return oldgrannyType_; }
      Int_t dauOneId() const {return dauOneId_;}
      Int_t dauTwoId() const {return dauTwoId_;}
      Int_t dauThreeId() const {return dauThreeId_;}
      Int_t dauFourId() const {return dauFourId_;}
      Int_t indexInList() const {return indexInList_; }
      virtual TString typeName() const { return "TRootMCParticle"; }


      void setStatus(Int_t status) { status_ = status; }
      void setnDau(Int_t nDau) { nDau_ = nDau; }
      void setMotherType(Int_t motherType) { motherType_ = motherType; }
      void setGrannyType(Int_t grannyType) { grannyType_ = grannyType; }
      void setoldGrannyType(Int_t oldgrannyType) { oldgrannyType_ = oldgrannyType; }
      void setDauOneId (Int_t dauOneId) { dauOneId_ = dauOneId; }
      void setDauTwoId (Int_t dauTwoId) { dauTwoId_ = dauTwoId; }
      void setDauThreeId (Int_t dauThreeId) { dauThreeId_ = dauThreeId; }
      void setDauFourId (Int_t dauFourId) { dauFourId_ = dauFourId; }
      void setIndexInList(Int_t indexInList) {indexInList_ = indexInList; }


      friend std::ostream& operator<< (std::ostream& stream, const TRootMCParticle& part) {
         stream << "Type=" << part.type_ << "  Charge=" << part.charge_ << "  Status=" << part.status_ << "  number of daughters=" <<
         part.nDau_ << "  mother ID=" << part.motherType_ << "  granny ID=" << part.grannyType_ << "  oldgranny ID=" << part.oldgrannyType_ << " index in the MC list=" << part.indexInList_ << " (Et,eta,phi)=("<< part.Et() <<","<< part.Eta() <<","<< part.Phi() << ")"
         << " vertex(x,y,z)=("<< part.vx() <<","<< part.vy() <<","<< part.vz() << ")";
         return stream;
      };


   protected:

      Int_t status_;
      Int_t nDau_;
      Int_t motherType_;
      Int_t grannyType_;
      Int_t oldgrannyType_;
      Int_t dauOneId_;
      Int_t dauTwoId_;
      Int_t dauThreeId_;
      Int_t dauFourId_;
      Int_t indexInList_;

      ClassDef (TRootMCParticle,1);

};

#endif
