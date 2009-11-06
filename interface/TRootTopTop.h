#ifndef TRootTopTop_h
#define TRootTopTop_h

#include <string>
#include <iostream>

#include "Rtypes.h"
#include "TLorentzVector.h"
#include "TRef.h"

using namespace std;

class TRootTopTop : public TLorentzVector
{

   public:

      TRootTopTop() : TLorentzVector(), indexOne_(-1), indexTwo_(-1), motherOne_(0), motherTwo_(0), decayType_(0), njetTenGeV_(-1), njetFiftyGeV_(-1) {;}
      TRootTopTop(const TRootTopTop& particles) : TLorentzVector(particles), indexOne_(particles.indexOne_), indexTwo_(particles.indexTwo_), motherOne_(particles.motherOne_),motherTwo_(particles.motherTwo_), decayType_(particles.decayType_), njetTenGeV_(particles.njetTenGeV_),njetFiftyGeV_(particles.njetFiftyGeV_) {;}
      TRootTopTop(Float_t px, Float_t py, Float_t pz, Float_t e) : TLorentzVector(px,py,pz,e), indexOne_(-1), indexTwo_(-1), motherOne_(0), motherTwo_(0), decayType_(0), njetTenGeV_(-1), njetFiftyGeV_(-1) {;}
      TRootTopTop(const TLorentzVector &momentum) : TLorentzVector(momentum),indexOne_(-1), indexTwo_(-1), motherOne_(0), motherTwo_(0), decayType_(0),  njetTenGeV_(-1), njetFiftyGeV_(-1)  {;}
      TRootTopTop(const TLorentzVector &momentum, Int_t indexOne, Int_t indexTwo, Int_t motherOne, Int_t motherTwo, Int_t decayType, Int_t njetTenGeV, Int_t njetFiftyGeV) : TLorentzVector(momentum),indexOne_(indexOne), indexTwo_(indexTwo),motherOne_(motherOne), motherTwo_(motherTwo), decayType_(decayType), njetTenGeV_(njetTenGeV),njetFiftyGeV_(njetFiftyGeV)  {;}

      ~TRootTopTop() {;}

      Int_t indexOne() const {return indexOne_; }
      Int_t indexTwo() const {return indexTwo_; }
      Int_t motherOne() const {return motherOne_; }
      Int_t motherTwo() const {return motherTwo_; }
      Int_t decayType() const  { return decayType_; }
      Int_t njetTenGeV() const {return njetTenGeV_;}
      Int_t njetFiftyGeV() const {return njetFiftyGeV_;}

      void setIndexOne(Int_t indexOne) {indexOne_ = indexOne; }
      void setIndexTwo(Int_t indexTwo) {indexTwo_ = indexTwo; }
      void setMotherOne(Int_t motherOne) { motherOne_ = motherOne; }
      void setMotherTwo(Int_t motherTwo) { motherTwo_ = motherTwo; }
      void setdecayType(Int_t decayType) { decayType_ = decayType; }
      void setnjetTenGeV(Int_t njetTenGeV) {njetTenGeV_ = njetTenGeV; }
      void setnjetFiftyGeV(Int_t njetFiftyGeV) {njetFiftyGeV_ = njetFiftyGeV; }

   protected:

      Int_t indexOne_;
      Int_t indexTwo_;
      Int_t motherOne_;
      Int_t motherTwo_;
      Int_t decayType_;
      Int_t njetTenGeV_;
      Int_t njetFiftyGeV_;

      ClassDef (TRootTopTop,1);

};

#endif
