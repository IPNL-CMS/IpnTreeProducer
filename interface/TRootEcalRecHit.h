#ifndef TRootEcalRecHit_h
#define TRootEcalRecHit_h

#include <iostream>

#include "Rtypes.h"
#include "TObject.h"

using namespace std;

class TRootEcalRecHit : public TObject
{
   
   public:
      
      // FIXME - Flags should be synchronized with /DataFormats/EcalRecHit/interface/EcalRecHit.h
      enum Flags
      {
         kGood=0,                   // channel ok, the energy and time measurement are reliable
         kPoorReco,                 // the energy is available from the UncalibRecHit, but approximate (bad shape, large chi2)
         kOutOfTime,                // the energy is available from the UncalibRecHit (sync reco), but the event is out of time
         kFaultyHardware,           // The energy is available from the UncalibRecHit, channel is faulty at some hardware level (e.g. noisy)
         kNoisy,                    // the channel is very noisy
         kPoorCalib,                // the energy is available from the UncalibRecHit, but the calibration of the channel is poor
         kSaturated,                // saturated channel (recovery not tried)
         kLeadingEdgeRecovered,     // saturated channel: energy estimated from the leading edge before saturation
         kNeighboursRecovered,      // saturated/isolated dead: energy estimated from neighbours
         kTowerRecovered,           // channel in TT with no data link, info retrieved from Trigger Primitive
         kDead,                     // channel is dead and any recovery fails
         kKilled,                   // MC only flag: the channel is killed in the real detector
         kTPSaturated,              // the channel is in a region with saturated TP
         kL1SpikeFlag,              // the channel is in a region with TP with sFGVB = 0
         kWeird,                    // the signal is believed to originate from an anomalous deposit (spike) 
         kDiWeird,                  // the signal is anomalous, and neighbors another anomalous signal  
         kUnknown                   // to ease the interface with functions returning flags. 
      };
      
      // FIXME - Severity Levels should be synchronized with /RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h
      enum EcalSeverityLevel
      {
         kSeverityGood=0,
         kSeverityProblematic,
         kSeverityRecovered,
         kSeverityTime,
         kSeverityWeird,
         kSeverityBad
      };
      
      TRootEcalRecHit() :
         detector_(-999)
         ,recoFlag_(-999)
         ,energy_(-999.)
         ,time_(-999.)
         ,position1_(-999)
         ,position2_(-999)
         ,position3_(-999)
         ,ism_(-999)
         ,ic_(-999)
         ,iquadrant_(-999)
         ,hashedIndex_(-999)
         ,outOfTimeEnergy_(-999.)
         ,outOfTimeChi2_(-999.)
         ,severity_(-999)
         {;}
      
      TRootEcalRecHit(const TRootEcalRecHit& hit) :
         detector_(hit.detector_)
         ,recoFlag_(hit.recoFlag_)
         ,energy_(hit.energy_)
         ,time_(hit.time_)
         ,position1_(hit.position1_)
         ,position2_(hit.position2_)
         ,position3_(hit.position3_)
         ,ism_(hit.ism_)
         ,ic_(hit.ic_)
         ,iquadrant_(hit.iquadrant_)
         ,hashedIndex_(hit.hashedIndex_)
         ,chi2_(hit.chi2_)
         ,outOfTimeEnergy_(hit.outOfTimeEnergy_)
         ,outOfTimeChi2_(hit.outOfTimeChi2_)
         ,severity_(hit.severity_)
         {;}
      
      TRootEcalRecHit(Int_t detector, Int_t recoFlag, Float_t energy, Float_t time, Int_t position1, Int_t position2, Int_t position3, Int_t ism, Int_t ic, Int_t iquadrant, Int_t hashedIndex, Float_t chi2, Float_t outOfTimeEnergy, Float_t outOfTimeChi2, Int_t severity) :
         detector_(detector)
         ,recoFlag_(recoFlag)
         ,energy_(energy)
         ,time_(time)
         ,position1_(position1)
         ,position2_(position2)
         ,position3_(position3)
         ,ism_(ism)
         ,ic_(ic)
         ,iquadrant_(iquadrant)
         ,hashedIndex_(hashedIndex)
         ,chi2_(chi2)
         ,outOfTimeEnergy_(outOfTimeEnergy)
         ,outOfTimeChi2_(outOfTimeChi2)
         ,severity_(severity)
         {;}
      
      ~TRootEcalRecHit() {;}
      
      
      Int_t detector() const { return detector_; }
      Int_t recoFlag() const { return recoFlag_; }
      Float_t energy() const { return energy_; }
      Float_t time() const { return time_; }
      Int_t position1() const { return position1_; }
      Int_t position2() const { return position2_; }
      Int_t position3() const { return position3_; }
      Int_t ism() const { return ism_; }
      Int_t ic() const { return ic_; }
      Int_t iquadrant() const { return iquadrant_; }
      Int_t hashedIndex() const { return hashedIndex_; }
      //Bool_t isEB() const { return ( int((det_%100)/10)==1 ? true : false ); }
      //Bool_t isEE() const { return ( int((det_%100)/10)==2 ? true : false ); }
      Float_t chi2() const { return chi2_; }
      Float_t outOfTimeEnergy() const { return outOfTimeEnergy_; }
      Float_t outOfTimeChi2() const { return outOfTimeChi2_; }
      Int_t severity() const { return severity_; }
      
      void setDetector(Int_t detector) { detector_ = detector; }
      void setRecoFlag(Int_t recoFlag) { recoFlag_ = recoFlag; }
      void setEnergy(Float_t energy) { energy_ = energy; }
      void setTime(Float_t time) { time_ = time; }
      void setPosition1(Int_t position1) { position1_ = position1; }
      void setPosition2(Int_t position2) { position2_ = position2; }
      void setPosition3(Int_t position3) { position3_ = position3; }
      void setIsm(Int_t ism) { ism_ = ism; }
      void setIC(Int_t ic) { ic_ = ic; }
      void setIquadrant(Int_t iquadrant) { iquadrant_ = iquadrant; }
      void setHashedIndex(Int_t hashedIndex) { hashedIndex_ = hashedIndex; }
      void setChi2(Float_t chi2) { chi2_ = chi2; }
      void setOutOfTimeEnergy(Float_t outOfTimeEnergy) { outOfTimeEnergy_ = outOfTimeEnergy; }
      void setOutOfTimeChi2(Float_t outOfTimeChi2) { outOfTimeChi2_ = outOfTimeChi2; }
      void setSeverity(Int_t severity) { severity_ = severity; }
      
      //bool operator< (const TRootEcalRecHit & rhs) { return energy_<rhs.energy_; }
      
      friend std::ostream& operator<< (std::ostream& stream, const TRootEcalRecHit& hit)
      {
         if (hit.detector()==1)
            stream << "TRootEcalRecHit - Det=" << hit.detector() << " Flag=" << hit.recoFlag()  << " Severity=" << hit.severity() << " energy=" << hit.energy()
            << " time=" << hit.time() << " ieta=" << hit.position1() << " iphi=" << hit.position2()
            << " ism=" << hit.ism() << " ic=" << hit.ic() << " hashedIndex=" << hit.hashedIndex()
            << " chi2=" << hit.chi2() << " outOfTimeEnergy=" << hit.outOfTimeEnergy() << " outOfTimeChi2=" << hit.outOfTimeChi2();
         else if (hit.detector()==2)
            stream << "TRootEcalRecHit - Det=" << hit.detector() << " Flag=" << hit.recoFlag()  << " Severity=" << hit.severity()  << " energy=" << hit.energy()
            << " time=" << hit.time() << " ix=" << hit.position1() << " iy=" << hit.position2() << " iz=" << hit.position3()
            << " isc=" << hit.ism() << " ic=" << hit.ic() << " iquadrant=" << hit.iquadrant() << " hashedIndex=" << hit.hashedIndex()
            << " chi2=" << hit.chi2() << " outOfTimeEnergy=" << hit.outOfTimeEnergy() << " outOfTimeChi2=" << hit.outOfTimeChi2();
         else
            stream << "TRootEcalRecHit - Det=" << hit.detector() << " Flag=" << hit.recoFlag()  << " Severity=" << hit.severity()  << " energy=" << hit.energy()
            << " time=" << hit.time() << " position1=" << hit.position1() << " position2=" << hit.position2() << " position3=" << hit.position3()
            << " ism=" << hit.ism() << " ic=" << hit.ic() << " iquadrant=" << hit.iquadrant() << " hashedIndex=" << hit.hashedIndex()
            << " chi2=" << hit.chi2() << " outOfTimeEnergy=" << hit.outOfTimeEnergy() << " outOfTimeChi2=" << hit.outOfTimeChi2();
         return stream;
      };
      
      void Print()
      {
         if (detector_==1)
            std::cout << "TRootEcalRecHit - Det=" << this->detector() << " Flag=" << this->recoFlag()  << " Severity=" << this->severity()  << " energy=" << this->energy()
            << " time=" << this->time() << " ieta=" << this->position1() << " iphi=" << this->position2()
            << " ism=" << this->ism() << " ic=" << this->ic() << " hashedIndex=" << this->hashedIndex()
            << " chi2=" << this->chi2() << " outOfTimeEnergy=" << this->outOfTimeEnergy() << " outOfTimeChi2=" << this->outOfTimeChi2();
         else if (detector_==2)
            std::cout << "TRootEcalRecHit - Det=" << this->detector() << " Flag=" << this->recoFlag()  << " Severity=" << this->severity()   << " energy=" << this->energy()
            << " time=" << this->time() << " ix=" << this->position1() << " iy=" << this->position2() << " iz=" << this->position3()
            << " isc=" << this->ism() << " ic=" << this->ic() << " iquadrant=" << this->iquadrant() << " hashedIndex=" << this->hashedIndex()
            << " chi2=" << this->chi2() << " outOfTimeEnergy=" << this->outOfTimeEnergy() << " outOfTimeChi2=" << this->outOfTimeChi2();
         else
            std::cout << "TRootEcalRecHit - Det=" << this->detector() << " Flag=" << this->recoFlag()  << " Severity=" << this->severity()   << " energy=" << this->energy()
            << " time=" << this->time() << " position1=" << this->position1() << " position2=" << this->position2() << " position3=" << this->position3()
            << " ism=" << this->ism() << " ic=" << this->ic() << " iquadrant=" << this->iquadrant() << " hashedIndex=" << this->hashedIndex()
            << " chi2=" << this->chi2() << " outOfTimeEnergy=" << this->outOfTimeEnergy() << " outOfTimeChi2=" << this->outOfTimeChi2();
      };
      
         
   protected:
      
      Int_t detector_;          // detector containing the rechit
      Int_t recoFlag_;          // rechit reco quality flag
      Float_t energy_;          // rechit energy
      Float_t time_;            // rechit time
      Int_t position1_;         // ieta or ix of the rechit
      Int_t position2_;         // iphi or iy of the rechit
      Int_t position3_;         // iz of the EE rechit
      Int_t ism_;               // EB SM id or EE SC id
      Int_t ic_;                // crystal number inside EB SM or EE SC
      Int_t iquadrant_;         // EE SC quadrant id
      Int_t hashedIndex_;       // compact index for arrays
      Float_t chi2_;            // chi2 of the pulse shape fit
      Float_t outOfTimeEnergy_; // energy of out-of-time events as estimated by allowing the event to be out of synch with respect to the clock
      Float_t outOfTimeChi2_;   // chi2 of the pulse shape fit allowing the event to be out of synch
      Int_t severity_;          // severity levels 
      
      ClassDef (TRootEcalRecHit,5);
      
};


#endif
