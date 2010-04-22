#ifndef TRootEcalRecHit_h
#define TRootEcalRecHit_h

#include "Rtypes.h"
#include "TObject.h"

using namespace std;

class TRootEcalRecHit : public TObject
{
	
	public:
		
		enum Flags
		{
			kGood=0,               // channel ok, the energy and time measurement are reliable
			kPoorReco,             // the energy is available from the UncalibRecHit, but approximate (bad shape, large chi2)
			kOutOfTime,            // the energy is available from the UncalibRecHit (sync reco), but the event is out of time
			kFaultyHardware,       // The energy is available from the UncalibRecHit, channel is faulty at some hardware level (e.g. noisy)
			kNoisy,                // the channel is very noisy
			kPoorCalib,            // the energy is available from the UncalibRecHit, but the calibration of the channel is poor
			kSaturated,            // saturated channel (recovery not tried)
			kLeadingEdgeRecovered, // saturated channel: energy estimated from the leading edge before saturation
			kNeighboursRecovered,  // saturated/isolated dead: energy estimated from neighbours
			kTowerRecovered,       // channel in TT with no data link, info retrieved from Trigger Primitive
			kFake,                 // the signal in the channel is a fake (e.g. a so-called spike)
			kFakeNeighbours,       // the signal in the channel is a fake and it is detected by looking at the neighbours
			kDead,                 // channel is dead and any recovery fails
			kKilled,               // MC only flag: the channel is killed in the real detector
			kUnknown               // to easy the interface with functions returning flags
		};
		
		TRootEcalRecHit() :
		detector_(0)
		,recoFlag_(0)
		,energy_(0)
		,time_(0)
		,position1_(0)
		,position2_(0)
		{;}
		
		TRootEcalRecHit(const TRootEcalRecHit& hit) :
		detector_(hit.detector_)
		,recoFlag_(hit.recoFlag_)
		,energy_(hit.energy_)
		,time_(hit.time_)
		,position1_(hit.position1_)
		,position2_(hit.position2_)
		{;}
		
		TRootEcalRecHit(Int_t detector, Int_t recoFlag, Float_t energy, Float_t time, Int_t position1, Int_t position2) :
		detector_(detector)
		,recoFlag_(recoFlag)
		,energy_(energy)
		,time_(time)
		,position1_(position1)
		,position2_(position2)
		{;}
				
		~TRootEcalRecHit() {;}
		
		
		Int_t detector() const { return detector_; }
		Int_t recoFlag() const { return recoFlag_; }
		Float_t energy() const { return energy_; }
		Float_t time() const { return time_; }
		Int_t position1() const { return position1_; }
		Int_t position2() const { return position2_; }
		//Bool_t isEB() const { return ( int((det_%100)/10)==1 ? true : false ); }
		//Bool_t isEE() const { return ( int((det_%100)/10)==2 ? true : false ); }
		
		void setDetector(Int_t detector) { detector_ = detector; }
		void setRecoFlag(Int_t recoFlag) { recoFlag_ = recoFlag; }
		void setEnergy(Float_t energy) { energy_ = energy; }
		void setTime(Float_t time) { time_ = time; }
		void setPosition1(Int_t position1) { position1_ = position1; }
		void setPosition2(Int_t position2) { position2_ = position2; }
		
		//bool operator< (const TRootEcalRecHit & rhs) { return energy_<rhs.energy_; }
		
		friend std::ostream& operator<< (std::ostream& stream, const TRootEcalRecHit& hit)
		{
			if (hit.detector()==1)
				stream << "TRootEcalRecHit - Det=" << hit.detector() << " Flag=" << hit.recoFlag() << " energy=" << hit.energy()
				<< " time=" << hit.time() << " ieta=" << hit.position1()<< " iphi=" << hit.position2();
			else if (hit.detector()==2)
				stream << "TRootEcalRecHit - Det=" << hit.detector() << " Flag=" << hit.recoFlag() << " energy=" << hit.energy()
				<< " time=" << hit.time() << " ix=" << hit.position1()<< " iy=" << hit.position2();
			else
				stream << "TRootEcalRecHit - Det=" << hit.detector() << " Flag=" << hit.recoFlag() << " energy=" << hit.energy()
				<< " time=" << hit.time() << " position1=" << hit.position1()<< " position2=" << hit.position2();
			return stream;
		};
		
		void Print()
		{
			if (detector_==1)
				std::cout << "TRootEcalRecHit - Det=" << this->detector() << " Flag=" << this->recoFlag() << " energy=" << this->energy()
				<< " time=" << this->time() << " ieta=" << this->position1()<< " iphi=" << this->position2();
			else if (detector_==2)
				std::cout << "TRootEcalRecHit - Det=" << this->detector() << " Flag=" << this->recoFlag() << " energy=" << this->energy()
				<< " time=" << this->time() << " ix=" << this->position1()<< " iy=" << this->position2();
			else
				std::cout << "TRootEcalRecHit - Det=" << this->detector() << " Flag=" << this->recoFlag() << " energy=" << this->energy()
				<< " time=" << this->time() << " position1=" << this->position1()<< " position2=" << this->position2();			
		};
		
		
	protected:
		
		Int_t detector_;  // detector containing the rechit
		Int_t recoFlag_;  // rechit reco quality flag
		Float_t energy_;  // rechit energy
		Float_t time_;    // rechit time
		Int_t position1_; // ieta or ix of the rechit
		Int_t position2_; // iphi or iy of the rechit
		
		ClassDef (TRootEcalRecHit,2);
		
};


#endif
