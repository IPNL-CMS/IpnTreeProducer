#ifndef TRootMCPhoton_h
#define TRootMCPhoton_h

#include <vector>

#include "../interface/TRootParticle.h"

using namespace std;

class TRootMCPhoton : public TRootParticle
{

   public:

      TRootMCPhoton() :
      TRootParticle()
      ,convVertex_()
      ,tracks_(0)
      , recoPhotonIndex_(-1)
      {;}

      TRootMCPhoton(const TRootMCPhoton& photon) :
      TRootParticle(photon)
      ,convVertex_(photon.convVertex_)
      ,tracks_(photon.tracks_)
      , recoPhotonIndex_(photon.recoPhotonIndex_)
      {;}

      TRootMCPhoton(Double_t px, Double_t py, Double_t pz, Double_t e) :
      TRootParticle(px,py,pz,e)
      ,convVertex_()
      ,tracks_(0)
      , recoPhotonIndex_(-1)
      {;}

      TRootMCPhoton(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
      ,convVertex_()
      ,tracks_(0)
      , recoPhotonIndex_(-1)
      {;}

      TRootMCPhoton(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
      TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
      ,convVertex_()
      ,tracks_(0)
      , recoPhotonIndex_(-1)
      {;}

      TRootMCPhoton(const TLorentzVector &momentum) :
      TRootParticle(momentum)
      ,convVertex_()
      ,tracks_(0)
      , recoPhotonIndex_(-1)
      {;}

      TRootMCPhoton(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
      TRootParticle(momentum, vertex, type, charge)
      ,convVertex_()
      ,tracks_(0)
      , recoPhotonIndex_(-1)
      {;}

      TRootMCPhoton(const TLorentzVector &momentum, const TVector3 &vertex,  const TVector3 &convVertex, Int_t type, Float_t charge) :
      TRootParticle(momentum, vertex, type, charge)
      ,convVertex_()
      ,tracks_(0)
      , recoPhotonIndex_(-1)
      {;}

      TRootMCPhoton(const TLorentzVector &momentum, const TVector3 &vertex,  const TVector3 &convVertex,  const std::vector<TLorentzVector> &tracks, Int_t type, Float_t charge) :
      TRootParticle(momentum, vertex, type, charge)
      ,convVertex_(convVertex)
      ,tracks_(tracks)
      , recoPhotonIndex_(-1)
      {;}


      ~TRootMCPhoton() {;}


      unsigned int nTracks() const  { return tracks_.size(); }

      Float_t convEoverP() const
      {
         Float_t ptot = -1.;
         if (tracks_.size()==2)
         {
            TLorentzVector pair =  tracks_.at(0) + tracks_.at(1);
            ptot = ( pair.P()>0 ? this->E() / pair.P() : -1. );
         }
         return ptot;
      }

      Float_t convMass() const
      {
         Float_t mass = -1.;
         if (tracks_.size()==2)
         {
            TLorentzVector pair =  tracks_.at(0) + tracks_.at(1);
            mass = pair.M();
         }
         return mass;
      }

      Float_t convDeltaCotanTheta() const
      {
         Float_t cotan = -999.;
         if (tracks_.size()==2)
         {
            if ( tan(tracks_.at(0).Theta()) != 0 && tan(tracks_.at(1).Theta()) != 0 ) cotan = 1./ tan(tracks_.at(0).Theta()) - 1./ tan(tracks_.at(1).Theta());
         }
         return cotan;
      }

      Float_t convPtOverEt() const
      {
         Float_t pe = -1.;
         if (tracks_.size()==2)
         {
            TLorentzVector pair =  tracks_.at(0) + tracks_.at(1);
            pe = pair.Pt() / this->Et();
         }
         return pe;
      }


      TVector3 convVertex() const  { return convVertex_;}
      Double_t conv_vx() const  { return convVertex_.x(); }
      Double_t conv_vy() const  { return convVertex_.y(); }
      Double_t conv_vz() const  { return convVertex_.z(); }

      std::vector<TLorentzVector> tracks() const  { return tracks_;}
      Int_t recoPhotonIndex() const  { return recoPhotonIndex_;}
      virtual TString typeName() const { return "TRootMCPhoton"; }

      void setConvVertex(TVector3 convVertex) { convVertex_=convVertex; }
      void setConvVertex(Double_t x, Double_t y, Double_t z) { convVertex_.SetXYZ(x, y ,z); }
      void setTracks(std::vector<TLorentzVector> tracks) { tracks_=tracks; }
      void setRecoPhotonIndex(Int_t recoPhotonIndex) { recoPhotonIndex_=recoPhotonIndex; }


      friend std::ostream& operator<< (std::ostream& stream, const TRootMCPhoton& photon) {
         stream << "Converted TRootMCPhoton  (Et,eta,phi)=("<< photon.Et() <<","<< photon.Eta() <<","<< photon.Phi() << ")"
         << " photon vertex=("<< photon.vx() <<","<< photon.vy() <<","<< photon.vz() << ")"
         << " conversion vertex=("<< photon.conv_vx() <<","<< photon.conv_vy() <<","<< photon.conv_vz() << ")";
         return stream;
      };


   private:

      TVector3 convVertex_;		// Position of the conversion vertex
      std::vector<TLorentzVector> tracks_; // Tracks from the conversion
      Int_t recoPhotonIndex_;		// Index of first conversion track (in tracks TCloneArray)

      ClassDef (TRootMCPhoton,1);

};

#endif
