#ifndef TRootSignalEvent_h
#define TRootSignalEvent_h

#include <string>
#include <iostream>

#include "../interface/TRootParticle.h"

#include "Rtypes.h"
#include "TObjArray.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "TList.h"
#include "TCollection.h"

using namespace std;

class TCollection;

class TRootSignalEvent : public TObject
{

   public:
      TRootSignalEvent();
      ~TRootSignalEvent();

      Int_t nZ() const { return nZ_; }
      Int_t nMuplus() const { return nMuplus_; }
      Int_t nMuminus() const { return nMuminus_; }
      Int_t nFSR() const { return nFSR_; }
      Int_t nISR() const { return nISR_; }

      void addBosonZ(TRootParticle* part);
      void addMuplus(TRootParticle* part);
      void addMuminus(TRootParticle* part);
      void addFSR(TRootParticle* part);
      void addISR(TRootParticle* part);

      TRootParticle* bosonZ() { return bosonZ_;}
      TRootParticle* muplus() { return muplus_;}
      TRootParticle* muminus() { return muminus_;}
      TRootParticle* photonFSR(Int_t iFSR);
      TRootParticle* photonISR(Int_t iISR);

   private:

      Int_t nZ_;
      Int_t nMuplus_;
      Int_t nMuminus_;
      Int_t nFSR_;
      Int_t nISR_;
      TRootParticle* bosonZ_;
      TRootParticle* muplus_;
      TRootParticle* muminus_;
      TObjArray* photonFSR_;
      TObjArray* photonISR_;

      ClassDef (TRootSignalEvent,3);

};

#endif
