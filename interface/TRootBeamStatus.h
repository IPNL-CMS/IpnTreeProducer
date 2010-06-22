#ifndef TRootBeamStatus_h
#define TRootBeamStatus_h

#include <string>
#include <iostream>
#include "TObject.h"

using namespace std;

class TRootBeamStatus : public TObject
{
   
   public:
      
      TRootBeamStatus() :
      bstMasterStatus_(0)
      ,lhcFillNumber_(0)
      ,turnCountNumber_(0)
      ,beamMode_(0)
      ,beamMomentum_(0)
      ,totalIntensityBeam1_(0)
      ,totalIntensityBeam2_(0)
      {;}
      
      TRootBeamStatus(const TRootBeamStatus& beamStatus) :
      bstMasterStatus_(beamStatus.bstMasterStatus_)
      ,lhcFillNumber_(beamStatus.lhcFillNumber_)
      ,turnCountNumber_(beamStatus.turnCountNumber_)
      ,beamMode_(beamStatus.beamMode_)
      ,beamMomentum_(beamStatus.beamMomentum_)
      ,totalIntensityBeam1_(beamStatus.totalIntensityBeam1_)
      ,totalIntensityBeam2_(beamStatus.totalIntensityBeam2_)
      {;}
      
      ~TRootBeamStatus() {;}
      
      UShort_t bstMasterStatus() const { return bstMasterStatus_; }
      UInt_t lhcFillNumber() const { return lhcFillNumber_; }
      UInt_t turnCountNumber() const { return turnCountNumber_; }
      UShort_t beamMode() const { return beamMode_; }
      UShort_t beamMomentum() const { return beamMomentum_; }
      UInt_t totalIntensityBeam1() const { return totalIntensityBeam1_; }
      UInt_t totalIntensityBeam2() const { return totalIntensityBeam2_; }
      
      void setBstMasterStatus(UInt_t bstMasterStatus) { bstMasterStatus_ = bstMasterStatus; }
      void setLhcFillNumber_(UInt_t lhcFillNumber) { lhcFillNumber_ = lhcFillNumber; }
      void setTurnCountNumber(UInt_t turnCountNumber) { turnCountNumber_ = turnCountNumber; }
      void setBeamMode(UInt_t beamMode) { beamMode_ = beamMode; }
      void setBeamMomentum(UInt_t beamMomentum) { beamMomentum_ = beamMomentum; }
      void setTotalIntensityBeam1(UInt_t totalIntensityBeam1) { totalIntensityBeam1_ = totalIntensityBeam1; }
      void setTotalIntensityBeam2(UInt_t totalIntensityBeam2) { totalIntensityBeam2_ = totalIntensityBeam2; }
      
   private:
      
      UShort_t bstMasterStatus_;   // BST Master Status, updated on each turn
      UInt_t lhcFillNumber_;       // LHC Fill Number, updated at a rate of 1Hz
      UInt_t turnCountNumber_;     // Turn count numbers, 0 .. 4294967294 (106 hours - reset on first injection), updated on each turn
      UShort_t beamMode_;          // Beam mode (RAMP, STABLE, etc), updated at a rate of 1Hz
      UShort_t beamMomentum_;      // Beam Momentum (beam 1 = beam 2), 2 bytes in GeV/c, updated at a rate of 1Hz
      UInt_t totalIntensityBeam1_; // Total Intensity beam 1, measured in Integer × 10E10 charges, updated at a rate of 1Hz
      UInt_t totalIntensityBeam2_; // Total Intensity beam 2, measured in Integer × 10E10 charges, updated at a rate of 1Hz
      
      ClassDef (TRootBeamStatus,1);
      
};

#endif
