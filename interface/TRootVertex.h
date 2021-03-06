#ifndef TRootVertex_h
#define TRootVertex_h

#include <string>
#include <iostream>
#include <iomanip>

#include "Rtypes.h"
#include "TVector3.h"
#include "TRef.h"

using namespace std;

class TRootTrack;

class TRootVertex : public TVector3
{
   
public:
   
   TRootVertex() :
   TVector3(-999999.,-999999.,-999999.)
   ,error_(-1.,-1.,-1.)
   ,algo_(-1)
   ,isValid_(false)
   ,isFake_(true)
   ,chi2_(-1.)
   ,ndof_(-1.)
   ,ntracks_(-1)
   ,higherTrackPt_(-1.)
   ,scalarSumPt_(-1.)
   ,vectorSumPt_(-1.)
   ,tracksIndices_()
   ,tracks_()
   ,recoIndex_(-1)
   {;}
   
   TRootVertex(const TRootVertex& vertex) :
   TVector3(vertex)
   ,error_(vertex.error_)
   ,algo_(vertex.algo_)
   ,isValid_(vertex.isValid_)
   ,isFake_(vertex.isFake_)
   ,chi2_(vertex.chi2_)
   ,ndof_(vertex.ndof_)
   ,ntracks_(vertex.ntracks_)
   ,higherTrackPt_(vertex.higherTrackPt_)
   ,scalarSumPt_(vertex.scalarSumPt_)
   ,vectorSumPt_(vertex.vectorSumPt_)
   ,tracksIndices_(vertex.tracksIndices_)
   ,tracks_(vertex.tracks_)
   ,recoIndex_(vertex.recoIndex_)
   {;}
   
   TRootVertex(Double_t vx, Double_t vy, Double_t vz) :
   TVector3(vx,vy,vz)
   ,error_(-1.,-1.,-1.)
   ,algo_(-1)
   ,isValid_(false)
   ,isFake_(true)
   ,chi2_(-1.)
   ,ndof_(-1.)
   ,ntracks_(-1)
   ,higherTrackPt_(-1.)
   ,scalarSumPt_(-1.)
   ,vectorSumPt_(-1.)
   ,tracksIndices_()
   ,tracks_()
   ,recoIndex_(-1)
   {;}
   
   TRootVertex(Double_t vx, Double_t vy, Double_t vz, Double_t evx, Double_t evy, Double_t evz) :
   TVector3(vx,vy,vz)
   ,error_(evx,evy,evz)
   ,algo_(-1)
   ,isValid_(false)
   ,isFake_(true)
   ,chi2_(-1.)
   ,ndof_(-1.)
   ,ntracks_(-1)
   ,higherTrackPt_(-1.)
   ,scalarSumPt_(-1.)
   ,vectorSumPt_(-1.)
   ,tracksIndices_()
   ,tracks_()
   ,recoIndex_(-1)
   {;}
   
   
   TRootVertex(const TVector3 &vertex) :
   TVector3(vertex)
   ,error_(-1.,-1.,-1.)
   ,algo_(-1)
   ,isValid_(false)
   ,isFake_(true)
   ,chi2_(-1.)
   ,ndof_(-1.)
   ,ntracks_(-1)
   ,higherTrackPt_(-1.)
   ,scalarSumPt_(-1.)
   ,vectorSumPt_(-1.)
   ,tracksIndices_()
   ,tracks_()
   ,recoIndex_(-1)
   {;}
   
   TRootVertex( const TVector3 &vertex, const TVector3 &vertex_error) :
   TVector3(vertex)
   ,error_(vertex_error)
   ,algo_(-1)
   ,isValid_(false)
   ,isFake_(true)
   ,chi2_(-1.)
   ,ndof_(-1.)
   ,ntracks_(-1)
   ,higherTrackPt_(-1.)
   ,scalarSumPt_(-1.)
   ,vectorSumPt_(-1.)
   ,tracksIndices_()
   ,tracks_()
   ,recoIndex_(-1)
   {;}
   
   ~TRootVertex() {;}
   
   
   TVector3 error() const { return error_;}
   Double_t xerr() const  { return error_.x(); }
   Double_t yerr() const  { return error_.y(); }
   Double_t zerr() const  { return error_.z(); }
   Int_t algo() const { return algo_;}
   TString algoName() const
   {
      if (algo_==0) return "RECO";
      else if (algo_==1) return "AllTracksFit";
      else if (algo_==2) return "NoEEFit";
      else if (algo_==3) return "OnlyEEFit";
      else if (algo_==4) return "AllTracksDzMean";
      else if (algo_==5) return "NoEEDzMean";
      else if (algo_==6) return "OnlyEEDzMean";
      else return "Unknown method of vertex reconstruction";
   }
   Bool_t isValid() const { return isValid_;}
   Bool_t isFake() const { return isFake_;}
   Float_t chi2() const { return chi2_;}
   Float_t ndof() const { return ndof_;}
   Float_t ntracks() const { return ntracks_;}
   Float_t higherTrackPt() const { return higherTrackPt_;}
   Float_t scalarSumPt() const { return scalarSumPt_;}
   Float_t vectorSumPt() const { return vectorSumPt_;}
   Int_t recoIndex() const { return recoIndex_;}

   // Number of associated TRootTracks
   Int_t nAssociatedTracks() const { return tracks_.size();}
   
   // Indexes in TCloneArray ("Tracks" branch) of the tracksconstituents
   std::vector<Int_t> tracksIndices() const { return tracksIndices_; }
   
   // Get index in TCloneArray ("Tracks" branch) of the ith track constituent
   Int_t trackIndexAt(UInt_t index) const
   {
      if ( index>=tracksIndices_.size())
      {
         std::cout << "*** ERROR in TRootVertex::trackIndexAt() :  index out of range ***" << std::endl;
         return -1;
      }
      else
      {
         return tracksIndices_.at(index);
      }
   }
   
   // Get the vector containing the references to tracks constituents
   std::vector<TRef> tracks() const { return tracks_; }
   
   // Get the ith track constituent
   TRootTrack* trackAt(UInt_t index) const
   {
      if ( index>=tracks_.size())
      {
         std::cout << "*** ERROR in TRootVertex::trackAt() :  index out of range ***" << std::endl;
         return 0;
      }
      else
      {
         return (TRootTrack*) tracks_.at(index).GetObject();
      }
   }
   
   TString typeName() const { return "TRootVertex"; }
   
   void setError(TVector3 error) { error_ = error; }
   void setXerr(Double_t xerr) { error_.SetX(xerr);  }
   void setYerr(Double_t yerr) { error_.SetY(yerr); }
   void setZerr(Double_t zerr) { error_.SetZ(zerr); }
   void setAlgo(Int_t algo) { algo_ = algo; }
   void setAlgoName(TString algoName)
   {
      if (algoName=="RECO") algo_=0;
          else if (algoName=="AllTracksFit") algo_=1;
          else if (algoName=="NoEEFit") algo_=2;
          else if (algoName=="OnlyEEFit") algo_=3;
          else if (algoName=="AllTracksDzMean") algo_=4;
          else if (algoName=="NoEEDzMean") algo_=5;
          else if (algoName=="OnlyEEDzMean") algo_=6;
          else std::cout <<  "***** TRootVertex::setAlgo(TString) => Unknown method of vertex reconstruction *****" << std::endl;
   }
   void setIsValid(Float_t isValid) { isValid_ = isValid; }
   void setIsFake(Float_t isFake) { isFake_ = isFake; }
   void setChi2(Float_t chi2) { chi2_ = chi2; }
   void setNdof(Float_t ndof) { ndof_ = ndof; }
   void setNtracks(Float_t ntracks) { ntracks_ = ntracks; }
   void setHigherTrackPt(Float_t higherTrackPt) { higherTrackPt_ = higherTrackPt; }
   void setScalarSumPt(Float_t scalarSumPt) { scalarSumPt_ = scalarSumPt; }
   void setVectorSumPt(Float_t vectorSumPt) { vectorSumPt_ = vectorSumPt; }
   void setTracksIndices(std::vector<Int_t> tracksIndices) { tracksIndices_ = tracksIndices; }
   void setTracks(std::vector<TRef> tracks) { tracks_ = tracks; }
   void setRecoIndex(Int_t recoIndex) { recoIndex_ = recoIndex; }
   
   friend std::ostream& operator<< (std::ostream& stream, const TRootVertex& vertex)
   {
         stream << "TRootVertex - algo=" << setw(10) << vertex.algoName() << " isValid=" << vertex.isValid() << " isFake="<< vertex.isFake() << " (x,y,z)=(" << setw(9) << vertex.x() <<","<< setw(9) << vertex.y() <<","<< setw(9) << vertex.z() << ")"
         << " error(dx,dy,dz)=("<< setw(11) << vertex.xerr() <<","<< setw(11) << vertex.yerr() <<","<< setw(11) << vertex.zerr() << ")"
         << "  chi2="<< setw(8) << vertex.chi2() <<"  ndof="<< setw(6) << vertex.ndof() <<"  nTracks="<< setw(4) << vertex.ntracks()
         << "  higherTrackPt="<< setw(7) << vertex.higherTrackPt() <<"  scalarSumPt="<< setw(7) << vertex.scalarSumPt() <<"  vectorSumPt="<< setw(7) << vertex.vectorSumPt();
         return stream;
      };
   
   private:
      
      TVector3 error_;
      Int_t algo_;
      Bool_t isValid_;
      Bool_t isFake_;
      Float_t chi2_;
      Float_t ndof_;
      Float_t ntracks_;
      Float_t higherTrackPt_;
      Float_t scalarSumPt_;
      Float_t vectorSumPt_;
      std::vector<Int_t> tracksIndices_;
      std::vector<TRef> tracks_;
      Int_t recoIndex_; // corresponding index in std::vector< reco::Vertex > collection
      
      ClassDef (TRootVertex,4);
      
   };
   
   #endif
   