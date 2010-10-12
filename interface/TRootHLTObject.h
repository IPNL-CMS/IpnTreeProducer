#ifndef TRootHLTObject_h
#define TRootHLTObject_h

#include <string>
#include <iostream>
#include <iomanip>

#include "../interface/TRootParticle.h"

using namespace std;

class TRootHLTObject : public TRootParticle
{
   public:

      TRootHLTObject():
      TRootParticle()
      ,hltPath_("hltPath_name")
      ,hltFilter_("hltFilter_name")
      ,hltAlgo_("hltAlgo_name")
      {;}

      TRootHLTObject(TString hltPath, TString hltFilter, TString hltAlgo, Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge ):
      TRootParticle( px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge )
      ,hltPath_(hltPath)
      ,hltFilter_(hltFilter)
      ,hltAlgo_(hltAlgo)
      {;}

      TRootHLTObject(const TRootHLTObject & hltObject):
      TRootParticle(hltObject)
      ,hltPath_(hltObject.hltPath_)
      ,hltFilter_(hltObject.hltFilter_)
      ,hltAlgo_(hltObject.hltAlgo_)
      {;}

      ~TRootHLTObject(){;}


      TString hltPath()   const { return hltPath_; }
      TString hltFilter() const { return hltFilter_; }
      TString hltAlgo()   const { return hltAlgo_; }

      virtual TString typeName() const { return "TRootHLTObject"; }

      void setHLTPath(TString hltPath)  { hltPath_ = hltPath; }
      void setHLTFilter(TString hltFilter){ hltFilter_ = hltFilter; }
      void setHLTAlgo(TString hltAlgo)  { hltAlgo_ = hltAlgo; }

      friend std::ostream& operator<< (std::ostream& stream , const TRootHLTObject& hltObject)
      {
         stream << "Name="       <<hltObject.hltPath()
         << " Charge="        <<hltObject.charge()
         << " (Et,eta,phi)=(" <<setw(10)<<hltObject.Et()<< ","<<setw(10)<<hltObject.Eta()<<","<<setw(10)<<hltObject.Phi()<<")"
         << " vertex(x,y,z)=("<<hltObject.vx() <<","<< hltObject.vy() <<","<< hltObject.vz() << ")";
         return stream;
      };

   protected:

      TString hltPath_;
      TString hltFilter_;
      TString hltAlgo_;

      ClassDef (TRootHLTObject,1);
};

#endif
