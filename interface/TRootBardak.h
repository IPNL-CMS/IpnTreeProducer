#ifndef TRootBardak_h
#define TRootBardak_h

// Class to stock any temporary variables not fitting into another TRootObject

#include <string>
#include <iostream>
#include <cmath>

#include "Rtypes.h"
#include "TObject.h"

#include "../interface/TRootTrack.h"

using namespace std;

class TRootBardak : public TObject
{
	
	public:
		
		TRootBardak() :
		tkEle1_()
		,tkEle2_()
		,nSiHitsEle1_(-1)
		,nSiHitsEle2_(-1)
		,nPxlHitsEle1_(-1)
		,nPxlHitsEle2_(-1)
		,d0SigEle1_(-1.)
		,d0SigEle2_(-1.)
		,normChi2Ele1_(-1.)
		,normChi2Ele2_(-1.)
      , indexTRootTrackOfElectron1_(-1)
      , indexTRootTrackOfElectron2_(-1)
      , indexOfAllTracksVertexContainingElectron1_(-1)
      , indexOfAllTracksVertexContainingElectron2_(-1)
      {;}
		
		~TRootBardak() {;}
		
		TRootTrack tkEle1() const { return tkEle1_; }
		TRootTrack tkEle2() const { return tkEle2_; }
		Int_t nSiHitsEle1() const { return nSiHitsEle1_; }
		Int_t nSiHitsEle2() const { return nSiHitsEle2_; }
		Int_t nPxlHitsEle1() const { return nPxlHitsEle1_; }
		Int_t nPxlHitsEle2() const { return nPxlHitsEle2_; }
		Float_t d0SigEle1() const { return d0SigEle1_; }
		Float_t d0SigEle2() const { return d0SigEle2_; }
		Float_t normChi2Ele1() const { return normChi2Ele1_; }
		Float_t normChi2Ele2() const { return normChi2Ele2_; }
		Int_t indexTRootTrackOfElectron1() const { return indexTRootTrackOfElectron1_; }
		Int_t indexTRootTrackOfElectron2() const { return indexTRootTrackOfElectron2_; }
		Int_t IndexOfTRootVertexContainingElectron1() const { return indexOfAllTracksVertexContainingElectron1_; }
		Int_t IndexOfTRootVertexContainingElectron2() const { return indexOfAllTracksVertexContainingElectron2_; }
		
		void setEle1(const TRootTrack &tk, Int_t nSiHits, Int_t nPxlHits, Float_t d0Sig, Float_t normChi2)
		{
			tkEle1_ = tk;
			nSiHitsEle1_ = nSiHits;
			nPxlHitsEle1_ = nPxlHits;
			d0SigEle1_ = d0Sig;
			normChi2Ele1_ = normChi2;
		}
		
		void setEle2(const TRootTrack &tk, Int_t nSiHits, Int_t nPxlHits, Float_t d0Sig, Float_t normChi2)
		{
			tkEle2_ = tk;
			nSiHitsEle2_ = nSiHits;
			nPxlHitsEle2_ = nPxlHits;
			d0SigEle2_ = d0Sig;
			normChi2Ele2_ = normChi2;
		}
      
      void setIndexTRootTrackOfElectron1(Int_t indexTRootTrackOfElectron1) { indexTRootTrackOfElectron1_ = indexTRootTrackOfElectron1; }
      void setIndexTRootTrackOfElectron2(Int_t indexTRootTrackOfElectron2) { indexTRootTrackOfElectron2_ = indexTRootTrackOfElectron2; }
      void setIndexOfTRootVertexContainingElectron1(Int_t indexOfAllTracksVertexContainingElectron1) { indexOfAllTracksVertexContainingElectron1_ = indexOfAllTracksVertexContainingElectron1; }
      void setIndexOfTRootVertexContainingElectron2(Int_t indexOfAllTracksVertexContainingElectron2) { indexOfAllTracksVertexContainingElectron2_ = indexOfAllTracksVertexContainingElectron2; }
		
		friend std::ostream& operator<< (std::ostream& stream, const TRootBardak& bardak) {
			stream << " TRootBardak - nSiHitsEle1="<< bardak.nSiHitsEle1();
			return stream;
		};
		
	private:
		
		TRootTrack tkEle1_;
		TRootTrack tkEle2_;
		Int_t nSiHitsEle1_;
		Int_t nSiHitsEle2_;
		Int_t nPxlHitsEle1_;
		Int_t nPxlHitsEle2_;
		Float_t d0SigEle1_;
		Float_t d0SigEle2_;
		Float_t normChi2Ele1_;
		Float_t normChi2Ele2_;
      Int_t indexTRootTrackOfElectron1_;
      Int_t indexTRootTrackOfElectron2_;
      Int_t indexOfAllTracksVertexContainingElectron1_;
      Int_t indexOfAllTracksVertexContainingElectron2_;
      
		ClassDef (TRootBardak,2);
		
};

#endif
