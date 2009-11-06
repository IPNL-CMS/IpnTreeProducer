#ifndef TRootBeamSpot_h
#define TRootBeamSpot_h

#include <string>
#include <iostream>
#include <iomanip>

#include "Rtypes.h"
#include "TVector3.h"

using namespace std;

class TRootBeamSpot : public TVector3
{

   public:

      TRootBeamSpot() :
      TVector3(-999999.,-999999.,-999999.)
      ,error_(-1.,-1.,-1.)
      ,sigmaZ_(-1.)
      ,sigmaZError_(-1.)
      ,beamWidthX_(-1.)
      ,beamWidthXError_(-1.)
      ,beamWidthY_(-1.)
      ,beamWidthYError_(-1.)
      {;}

      TRootBeamSpot(const TRootBeamSpot& spot) :
      TVector3(spot)
      ,error_(spot.error_)
      ,sigmaZ_(spot.sigmaZ_)
      ,sigmaZError_(spot.sigmaZError_)
      ,beamWidthX_(spot.beamWidthX_)
      ,beamWidthXError_(spot.beamWidthXError_)
      ,beamWidthY_(spot.beamWidthY_)
      ,beamWidthYError_(spot.beamWidthYError_)
      {;}

      TRootBeamSpot(Double_t vx, Double_t vy, Double_t vz) :
      TVector3(vx,vy,vz)
      ,error_(-1.,-1.,-1.)
      ,sigmaZ_(-1.)
      ,sigmaZError_(-1.)
      ,beamWidthX_(-1.)
      ,beamWidthXError_(-1.)
      ,beamWidthY_(-1.)
      ,beamWidthYError_(-1.)
      {;}

      TRootBeamSpot(Double_t vx, Double_t vy, Double_t vz, Double_t evx, Double_t evy, Double_t evz) :
      TVector3(vx,vy,vz)
      ,error_(evx,evy,evz)
      ,sigmaZ_(-1.)
      ,sigmaZError_(-1.)
      ,beamWidthX_(-1.)
      ,beamWidthXError_(-1.)
      ,beamWidthY_(-1.)
      ,beamWidthYError_(-1.)
      {;}

      TRootBeamSpot(const TVector3 &vertex) :
      TVector3(vertex)
      ,error_(-1.,-1.,-1.)
      ,sigmaZ_(-1.)
      ,sigmaZError_(-1.)
      ,beamWidthX_(-1.)
      ,beamWidthXError_(-1.)
      ,beamWidthY_(-1.)
      ,beamWidthYError_(-1.)
      {;}

      TRootBeamSpot( const TVector3 &vertex, const TVector3 &vertex_error) :
      TVector3(vertex)
      ,error_(vertex_error)
      ,sigmaZ_(-1.)
      ,sigmaZError_(-1.)
      ,beamWidthX_(-1.)
      ,beamWidthXError_(-1.)
      ,beamWidthY_(-1.)
      ,beamWidthYError_(-1.)
      {;}

      TRootBeamSpot(Double_t vx, Double_t vy, Double_t vz, Double_t evx, Double_t evy, Double_t evz, Float_t sigmaZ, Float_t sigmaZError, Float_t beamWidthX, Float_t beamWidthXError, Float_t beamWidthY, Float_t beamWidthYError) :
      TVector3(vx,vy,vz)
      ,error_(evx,evy,evz)
      ,sigmaZ_(sigmaZ)
      ,sigmaZError_(sigmaZError)
      ,beamWidthX_(beamWidthX)
      ,beamWidthXError_(beamWidthXError)
      ,beamWidthY_(beamWidthY)
      ,beamWidthYError_(beamWidthYError)
      {;}

      ~TRootBeamSpot() {;}


      TVector3 error() const { return error_;}
      Double_t xError() const  { return error_.x(); }
      Double_t yError() const  { return error_.y(); }
      Double_t zError() const  { return error_.z(); }
      Float_t sigmaZ() const { return sigmaZ_;}
      Float_t sigmaZError() const { return sigmaZError_;}
      Float_t beamWidthX() const { return beamWidthX_;}
      Float_t beamWidthXError() const { return beamWidthXError_;}
      Float_t beamWidthY() const { return beamWidthY_;}
      Float_t beamWidthYError() const { return beamWidthYError_;}

      TString typeName() const { return "TRootBeamSpot"; }

      void setError(TVector3 error) { error_ = error; }
      void setXerror(Double_t xerr) { error_.SetX(xerr);  }
      void setYerror(Double_t yerr) { error_.SetY(yerr); }
      void setZerror(Double_t zerr) { error_.SetZ(zerr); }
      void setSigmaZ(Float_t sigmaZ) { sigmaZ_ = sigmaZ; }
      void setSigmaZError(Float_t sigmaZError) { sigmaZError_ = sigmaZError; }
      void setBeamWidthX(Float_t beamWidthX) { beamWidthX_ = beamWidthX; }
      void setBeamWidthXError(Float_t beamWidthXError) { beamWidthXError_ = beamWidthXError; }
      void setBeamWidthY(Float_t beamWidthY) { beamWidthY_ = beamWidthY; }
      void setBeamWidthYError(Float_t beamWidthYError) { beamWidthYError_ = beamWidthYError; }

      void fill(Double_t vx, Double_t vy, Double_t vz, Double_t evx, Double_t evy, Double_t evz, Float_t sigmaZ, Float_t sigmaZError, Float_t beamWidthX, Float_t beamWidthXError, Float_t beamWidthY, Float_t beamWidthYError)
      {
         this->SetXYZ(vx,vy,vz);
         error_.SetXYZ(evx,evy,evz);
         sigmaZ_ = sigmaZ;
         sigmaZError_ = sigmaZError;
         beamWidthX_ = beamWidthX;
         beamWidthXError_ = beamWidthXError;
         beamWidthY_ = beamWidthY;
         beamWidthYError_ = beamWidthYError;
      }

      void clear()
      {
         this->SetXYZ(-999999.,-999999.,-999999.);
         error_.SetXYZ(-1.,-1.,-1.);
         sigmaZ_ = -1.;
         sigmaZError_ = -1.;
         beamWidthX_ = -1.;
         beamWidthXError_ = -1.;
         beamWidthY_ = -1.;
         beamWidthYError_ = -1.;
      }

      friend std::ostream& operator<< (std::ostream& stream, const TRootBeamSpot& spot) {
         stream << "TRootBeamSpot - (x,y,z)=(" << spot.x() << ","<< spot.y() << ","<< spot.z() << ")"
         << "  error=(" << spot.xError() << ","<< spot.yError() << ","<< spot.zError() << ")"
         << "  sigmaZ=" << spot.sigmaZ() << " +- "<< spot.sigmaZError()
         << "  Beam width: sigmaX=" << spot.beamWidthX() << " +- "<< spot.beamWidthXError()
         << "  sigmaY=" << spot.beamWidthY() << " +- "<< spot.beamWidthYError();
         return stream;
      };


   private:

      TVector3 error_; // Error on (x,y,z) beam position
      Float_t sigmaZ_; // RMS bunch length
      Float_t sigmaZError_; // RMS bunch length error
      Float_t beamWidthX_; // Average beam width in x
      Float_t beamWidthXError_; // Error on average beam x width
      Float_t beamWidthY_; // Average beam width in y
      Float_t beamWidthYError_; // Error on average beam y width

      ClassDef (TRootBeamSpot,2);

};

#endif
