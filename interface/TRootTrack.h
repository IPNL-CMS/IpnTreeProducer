#ifndef TRootTrack_h
#define TRootTrack_h

#include "../interface/TRootParticle.h"

using namespace std;

class TRootVertex;

class TRootTrack : public TRootParticle
{
	
public:
	
	TRootTrack() :
		TRootParticle()
		,pixelLayersWithMeasurement_(-1)
		,stripLayersWithMeasurement_(-1)
		,chi2_(-1.)
		,d0_(-99999.)
		,d0Error_(-99999.)
		,dz_(-99999.)
		,dzError_(-99999.)
      ,primaryVertexIndex_(-1)
      ,primaryVertex_()
      {;}

	TRootTrack(const TRootTrack& track) :
		TRootParticle(track)
		,pixelLayersWithMeasurement_(track.pixelLayersWithMeasurement_)
		,stripLayersWithMeasurement_(track.stripLayersWithMeasurement_)
		,chi2_(track.chi2_)
		,d0_(track.d0_)
		,d0Error_(track.d0Error_)
		,dz_(track.dz_)
		,dzError_(track.dzError_)
      ,primaryVertexIndex_(track.primaryVertexIndex_)
      ,primaryVertex_(track.primaryVertex_)
      {;}
	
	TRootTrack(Double_t px, Double_t py, Double_t pz, Double_t e) :
		TRootParticle(px,py,pz,e)
		,pixelLayersWithMeasurement_(-1)
		,stripLayersWithMeasurement_(-1)
		,chi2_(-1.)
		,d0_(-99999.)
		,d0Error_(-99999.)
		,dz_(-99999.)
		,dzError_(-99999.)
      ,primaryVertexIndex_(-1)
      ,primaryVertex_()
      {;}
	
	TRootTrack(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
		,pixelLayersWithMeasurement_(-1)
		,stripLayersWithMeasurement_(-1)
		,chi2_(-1.)
		,d0_(-99999.)
		,d0Error_(-99999.)
		,dz_(-99999.)
		,dzError_(-99999.)
      ,primaryVertexIndex_(-1)
      ,primaryVertex_()
      {;}
	
	TRootTrack(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
		,pixelLayersWithMeasurement_(-1)
		,stripLayersWithMeasurement_(-1)
		,chi2_(-1.)
		,d0_(-99999.)
		,d0Error_(-99999.)
		,dz_(-99999.)
		,dzError_(-99999.)
      ,primaryVertexIndex_(-1)
      ,primaryVertex_()
      {;}
	
	TRootTrack(const TLorentzVector &momentum) :
		TRootParticle(momentum)
		,pixelLayersWithMeasurement_(-1)
		,stripLayersWithMeasurement_(-1)
		,chi2_(-1.)
		,d0_(-99999.)
		,d0Error_(-99999.)
		,dz_(-99999.)
		,dzError_(-99999.)
      ,primaryVertexIndex_(-1)
      ,primaryVertex_()
      {;}
	
	TRootTrack(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
		TRootParticle(momentum, vertex, type, charge)
		,pixelLayersWithMeasurement_(-1)
		,stripLayersWithMeasurement_(-1)
		,chi2_(-1.)
		,d0_(-99999.)
		,d0Error_(-99999.)
		,dz_(-99999.)
		,dzError_(-99999.)
      ,primaryVertexIndex_(-1)
      ,primaryVertex_()
      {;}

	TRootTrack(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge,
		Int_t pixelLayersWithMeasurement, Int_t stripLayersWithMeasurement, Float_t chi2, Float_t d0, Float_t d0Error, Float_t dz, Float_t dzError) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
		,pixelLayersWithMeasurement_(pixelLayersWithMeasurement)
		,stripLayersWithMeasurement_(stripLayersWithMeasurement)
		,chi2_(chi2)
		,d0_(d0)
		,d0Error_(d0Error)
		,dz_(dz)
		,dzError_(dzError)
      ,primaryVertexIndex_(-1)
      ,primaryVertex_()
      {;}

	~TRootTrack() {;}
		
	Int_t pixelLayersWithMeasurement() const { return pixelLayersWithMeasurement_; }
	Int_t stripLayersWithMeasurement() const { return stripLayersWithMeasurement_; }
	Float_t chi2() const { return chi2_; }
	Float_t d0() const { return d0_; }
	Float_t d0Error() const { return d0Error_; }
	Float_t dz() const { return dz_; }
	Float_t dzError() const { return dzError_; }
	Int_t primaryVertexIndex() const { return primaryVertexIndex_; }
	TRootVertex* primaryVertex() const
	{
      if (primaryVertexIndex_<0) return 0;
      else return (TRootVertex*) primaryVertex_.GetObject();
   }
	virtual TString typeName() const { return "TRootTrack"; }

	void setPixelLayersWithMeasurement(Int_t pixelLayersWithMeasurement) { pixelLayersWithMeasurement_ = pixelLayersWithMeasurement; }
	void setStripLayersWithMeasurement(Int_t stripLayersWithMeasurement) { stripLayersWithMeasurement_ = stripLayersWithMeasurement; }
	void setChi2(Float_t chi2) { chi2_ = chi2; }
	void setD0(Float_t d0) { d0_ = d0; }
	void setD0Error(Float_t d0Error) { d0Error_ = d0Error; }
	void setDz(Float_t dz) { dz_ = dz; }
	void setDzError(Float_t dzError) { dzError_ = dzError; }
	void setPrimaryVertexIndex(Int_t primaryVertexIndex) { primaryVertexIndex_ = primaryVertexIndex; }
	void setPrimaryVertex(TObject* primaryVertex) { primaryVertex_ = primaryVertex; }
	
	friend std::ostream& operator<< (std::ostream& stream, const TRootTrack& track) {
		stream << "TRootTrack - Charge=" << setw(2) << track.charge() << " (Et,eta,phi)=("<< setw(10) << track.Et() <<","<< setw(10) << track.Eta() <<","<< setw(10) << track.Phi() << ")"
      << " vertex(x,y,z)=("<< setw(12) << track.vx() <<","<< setw(12) << track.vy() <<","<< setw(12) << track.vz() << ")";
		return stream;
	};

   void Print()
   {
      std::cout << "TRootTrack - Charge=" << setw(2) << this->charge() << " (Et,eta,phi)=("<< setw(10) << this->Et() <<","<< setw(10) << this->Eta() <<","<< setw(10) << this->Phi() << ")"
      << " vertex(x,y,z)=("<< setw(12) << this->vx() <<","<< setw(12) << this->vy() <<","<< setw(12) << this->vz() << ")" << std::endl
      << "            chi2="<< setw(8) << this->chi2() <<"  nPixelLayers="<< setw(2) << this->pixelLayersWithMeasurement() <<"  nStripLayers="<< setw(3) << this->stripLayersWithMeasurement()
      << "  d0="<< setw(12) << this->d0() <<" +- "<< setw(12) << this->d0Error() <<"  dz="<< setw(10) << this->dz() << " +- " << setw(10) << this->dzError();
      if (this->primaryVertexIndex()<0) std::cout << "  no vertex" << std::endl;
      else std::cout << "  TRootVertex[" << this->primaryVertexIndex() << "]" << std::endl;
   };
			
private:
		
	Int_t pixelLayersWithMeasurement_; // Number of pixel layers with at least one valid hit
	Int_t stripLayersWithMeasurement_; // Number of strip layers with at least one valid hit
	Float_t chi2_;
	Float_t d0_;
	Float_t d0Error_;
	Float_t dz_;
	Float_t dzError_;
   Int_t primaryVertexIndex_; // Index in TCloneArray of TRootVertex containing this track
   TRef primaryVertex_;// Reference to TRootVertex containing this track
   
	ClassDef (TRootTrack,3);
   
};

#endif
