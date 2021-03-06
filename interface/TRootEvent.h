#ifndef TRootEvent_h
#define TRootEvent_h

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <time.h>

#include "Rtypes.h"
#include "TObject.h"
#include "TVector3.h"
#include "TRef.h"

#include "../interface/TRootVertex.h"
#include "../interface/TRootBeamStatus.h"

#include <vector>
#include <algorithm>

using namespace std;

class TRootRun;

class TRootEvent : public TObject
{
   
public:
   
   TRootEvent() :
   nb_(0)
   ,eventId_(0)
   ,runId_(0)
   ,storeNumber_(0)
   ,luminosityBlock_(0)
   ,bunchCrossing_(0)
   ,orbitNumber_(0)
   ,collisionTime_(0)
   ,beamStatus_()
   ,totoAnaProcessingTime_(0)
   ,passGlobalL1_(false)
   ,physicsL1Accept_(0)
   ,technicalL1Accept_(0)
   ,trigHLT_(0)
   ,prescaleHLT_(0)
   ,hltAcceptNames_(0)
   ,csa07id_(-1)
   ,csa07weight_(-1.)
   ,csa07process_()
   ,nBasicClusters_()
   ,nSuperClusters_()
   ,primaryVertexIndex_(-1)
   ,primaryVertex_(0)
   ,processID_(-1)
   ,idParton1_(-1)
   ,xParton1_(-1.)
   ,xPDF1_(-1.)
   ,idParton2_(-1)
   ,xParton2_(-1.)
   ,xPDF2_(-1.)
   ,pdfScale_(-1.)
   ,eventScale_(-1.)
   ,ptHat_(-1.)
   ,weight_(-1.)
   ,pu_TrueNumInteractions_(0.)
   ,inTimePU_NumInteractions_(0)
   ,latePU_NumInteractions_(0)
   ,earlyPU_NumInteractions_(0)
   ,pu_z_(0)
   ,pu_bx_(0)
   ,pu_sumPt_lowPt_(0)
   ,pu_sumPt_highPt_(0)
   ,pu_nTrk_lowPt_(0)
   ,pu_nTrk_highPt_(0)
   ,run_(0)
   ,rho_(0)
   {;}
   
   ~TRootEvent() {;}
   
   // Collision infos
   UInt_t nb() const { return nb_; }
   UInt_t eventId() const { return eventId_; }
   UInt_t runId() const { return runId_; }
   UInt_t storeNumber() const { return storeNumber_; }
   UInt_t luminosityBlock() const { return luminosityBlock_; }
   Int_t bunchCrossing() const { return bunchCrossing_; }
   Int_t orbitNumber() const { return orbitNumber_; }
   unsigned long long collisionTimeStamp() const { return collisionTime_; }
   Double_t collisionTime() const
   {
      Double_t mytime = Double_t(collisionTime_>>32) + Double_t(collisionTime_&0xffffffff)*1.e-6;
      return mytime;
   }
   unsigned long  microsecondCollisionTime() const { return (collisionTime_&0xffffffff); }
   char *asciiCollisionTime() const;
   TRootBeamStatus beamStatus() const { return beamStatus_; }
   UInt_t totoAnaProcessingTime() const { return totoAnaProcessingTime_; }
   
   // L1 Trigger decision
   Bool_t passGlobalL1() const { return passGlobalL1_; }
   unsigned int nPhysicsL1Paths() const { return physicsL1Accept_.size(); }
   unsigned int nTechnicalL1Paths() const { return technicalL1Accept_.size(); }
   std::vector<Bool_t> physicsL1Accept() const { return physicsL1Accept_; }
   std::vector<Bool_t> technicalL1Accept() const { return technicalL1Accept_; }
   Bool_t physicsL1Accept(unsigned int i) const
   {
      if (i<physicsL1Accept_.size())
      {
         return physicsL1Accept_.at(i);
      }
      else
      {
         cout << "Physics L1 path " << i << " not found" << endl;
         return false;
      }
   }
   Bool_t technicalL1Accept(unsigned int i) const
   {
      if (i<technicalL1Accept_.size())
      {
         return technicalL1Accept_.at(i);
      }
      else
      {
         cout << "Technical L1 path " << i << " not found" << endl;
         return false;
      }
   }
   
   // HLT decision & prescale
   std::vector<std::string> hltAcceptNames() const { return hltAcceptNames_; }
   std::string hltAcceptNamesAt(unsigned int i) const { return hltAcceptNames_.at(i); }
   Bool_t passGlobalHLT() const { return ( hltAcceptNames_.size() == 0 ? false : true); }
   Bool_t hltAccept(std::string name) { return ( std::find(hltAcceptNames_.begin(), hltAcceptNames_.end(), name) != hltAcceptNames_.end() ); }
   
   void printHltAcceptNames()
   {
      std::cout << "HLT paths triggered for Run " << this->runId() <<" Event "<< this->eventId() <<":\n";
      for (unsigned int i=0; i!=hltAcceptNames_.size(); ++i)
         std::cout << "   " << hltAcceptNames_.at(i) << std::endl;
   }
   
   unsigned int nHLTPaths() const { return trigHLT_.size(); }
   std::vector<Bool_t> trigHLT() const { return trigHLT_; }
   Bool_t trigHLT(unsigned int i) const
   {
      if (i<trigHLT_.size())
      {
         return trigHLT_.at(i);
      }
      else
      {
         cout << "HLT path " << i << " not found" << endl;
         return false;
      }
   }
   
   std::vector<UInt_t> prescaleHLT() const { return prescaleHLT_; }
   UInt_t prescaleHLT(unsigned int i) const
   {
      if (i<prescaleHLT_.size())
      {
         return prescaleHLT_.at(i);
      }
      else
      {
         cout << "HLT path " << i << " not found" << endl;
         return false;
      }
   }
   
   // CSA07 Process Id and Event Weight
   Int_t csa07id() const { return csa07id_; }
   Float_t csa07weight() const { return csa07weight_; }
   TString csa07process() const { return csa07process_; }
   
   // Nb of BasicClusters of a given type
   Int_t nBasicClusters(Int_t type)
   {
      map<Int_t,Int_t>::iterator it=nBasicClusters_.find(type);
      return ( it ==nBasicClusters_.end() ? 0 : (*it).second );
   }
   
   // Nb of SuperClusters of a given type
   Int_t nSuperClusters(Int_t type)
   {
      map<Int_t,Int_t>::iterator it=nSuperClusters_.find(type);
      return ( it ==nSuperClusters_.end() ? 0 : (*it).second );
   }
   
   
   // Selected Primary Vertex
   Int_t primaryVertexIndex() const { return primaryVertexIndex_; }
   TRootVertex* primaryVertex() const
   {
      if ( primaryVertex_==0)
      {
         cout << "   ********** Error in TRootEvent::primaryVertex() - No primary vertex selected **********" << endl;
         return 0;
      }
      else
      {
         return (TRootVertex*) primaryVertex_.GetObject();
      }
   }
   
   
   // PDF infos
   // Signal Process ID
   Int_t processID() const { return processID_; }
   // flavour first incoming parton
   Int_t idParton1() const { return idParton1_; }
   // energy fraction carried by first incoming parton
   Float_t xParton1() const { return xParton1_; }
   Float_t xPDF1() const { return xPDF1_; }
   // flavour first incoming parton
   Int_t idParton2() const { return idParton2_; }
   // energy fraction carried by first incoming parton
   Float_t xParton2() const { return xParton2_; }
   Float_t xPDF2() const { return xPDF2_; }
   // PDF Scale
   Float_t pdfScale() const { return pdfScale_; }
   // Event scale (= Q scale for PYTHIA - PARI[23] )
   Float_t eventScale() const { return eventScale_; }
   //  GenEventInfoProduct::binningValues().at(0) - For PYTHIA, it is pt_hat, i.e. PARI[17]
   // see GeneratorInterface/Pythia6Interface/plugins/Pythia6Hadronizer.cc
   Float_t ptHat() const { return ptHat_; }
   // Event weight
   Float_t weight() const { return weight_; }

   
   // True Number of pileup
   Float_t  pu_TrueNumInteractions() const { return pu_TrueNumInteractions_; }
   
   // Number of pileup
   Int_t  pu_NumInteractions() const { return (inTimePU_NumInteractions_ + earlyPU_NumInteractions_ + latePU_NumInteractions_); }
   
   // Number of in-time pileup
   Int_t  inTimePU_NumInteractions() const { return inTimePU_NumInteractions_; }
   
   // Number of late pileup (BX==+1)
   Int_t  latePU_NumInteractions() const { return latePU_NumInteractions_; }
   
   // Number of early pileup (BX==-1)
   Int_t  earlyPU_NumInteractions() const { return earlyPU_NumInteractions_; }
   
   // Number of out-of-time pileup
   Int_t  outOfTimePU_NumInteractions() const { return (earlyPU_NumInteractions_ + latePU_NumInteractions_); }
   
   // Number of pileup in acceptance
   Int_t pu_NumInteractions_inAcceptance() const
   {
      return Int_t(pu_bx_.size());
   }
   
   // Number of in-time pileup in acceptance
    Int_t inTimePU_NumInteractions_inAcceptance() const
   {
      Int_t npu = 0;
      for(unsigned int i=0; i<pu_bx_.size(); ++i)
         if( pu_bx_.at(i)==0 ) npu++;
      return npu;
   }
   
   // Number of late pileup in acceptance
   Int_t latePU_NumInteractions_inAcceptance() const
   {
      Int_t npu = 0;
      for(unsigned int i=0; i<pu_bx_.size(); ++i)
         if( pu_bx_.at(i)>0 ) npu++;
         return npu;
   }
   
   // Number of early pileup in acceptance
   Int_t earlyPU_NumInteractions_inAcceptance() const
   {
      Int_t npu = 0;
      for(unsigned int i=0; i<pu_bx_.size(); ++i)
         if( pu_bx_.at(i)<0 ) npu++;
         return npu;
   }
   
   // Number of out-of-time pileup in acceptance
   Int_t outOfTimePU_NumInteractions_inAcceptance() const
   {
      Int_t npu = 0;
      for(unsigned int i=0; i<pu_bx_.size(); ++i)
         if( pu_bx_.at(i)!=0 ) npu++;
         return npu;
   }
   
   
   // z of the PU vertices
   std::vector<Float_t> pu_z() const { return pu_z_; }
   Float_t pu_z(unsigned int i) const
   {
      if (i<pu_z_.size()) return pu_z_.at(i);
      cout << "Pileup number " << i << " not found" << endl;
      return -999999.;
   }
   
   // BX of the PU vertices
   std::vector<Int_t> pu_bx() const { return pu_bx_; }
   Int_t pu_bx(unsigned int i) const
   {
      if (i<pu_bx_.size()) return pu_bx_.at(i);
      cout << "Pileup number " << i << " not found" << endl;
      return -1;
   }
   
   // Sum of the pt of the track attached to the PU vertex (low pt threshold)
   std::vector<Float_t> pu_sumPt_lowPt() const { return pu_sumPt_lowPt_; }
   Float_t pu_sumPt_lowPtu_bx(unsigned int i) const
   {
      if (i<pu_sumPt_lowPt_.size()) return pu_sumPt_lowPt_.at(i);
      cout << "Pileup number " << i << " not found" << endl;
      return -1.;
   }
   
   // Sum of the pt of the track attached to the PU vertex (high pt threshold)
   std::vector<Float_t> pu_sumPt_highPt() const { return pu_sumPt_highPt_; }
   Float_t pu_sumPt_highPt(unsigned int i) const
   {
      if (i<pu_sumPt_highPt_.size()) return pu_sumPt_highPt_.at(i);
      cout << "Pileup number " << i << " not found" << endl;
      return -1.;
   }
   
   // Track multiplicity of the PU vertex (low pt threshold)
   std::vector<Int_t> pu_nTrk_lowPt() const { return pu_nTrk_lowPt_; }
   Int_t pu_nTrk_lowPt(unsigned int i) const
   {
      if (i<pu_nTrk_lowPt_.size()) return pu_nTrk_lowPt_.at(i);
      cout << "Pileup number " << i << " not found" << endl;
      return -1;
   }
   
   // Track multiplicity of the PU vertex (high pt threshold)
   std::vector<Int_t> pu_nTrk_highPt() const { return pu_nTrk_highPt_; }
   Int_t pu_nTrk_highPt(unsigned int i) const
   {
      if (i<pu_nTrk_highPt_.size()) return pu_nTrk_highPt_.at(i);
      cout << "Pileup number " << i << " not found" << endl;
      return -1;
   }
   
   
   
   // Associated TRootRun stocked in runTree
   TRootRun* run() const { return (TRootRun*) run_.GetObject(); }

   // rho of the event for Pile-Up energy estimation 
   Float_t rho() const { return rho_; } 
   
   
   void setNb(UInt_t nb) { nb_ = nb; }
   void setEventId(UInt_t eventId) { eventId_ = eventId; }
   void setRunId(UInt_t runId) { runId_ = runId; }
   void setStoreNumber(UInt_t storeNumber) { storeNumber_ = storeNumber; }
   void setLuminosityBlock(UInt_t luminosityBlock) { luminosityBlock_ = luminosityBlock; }
   void setBunchCrossing(Int_t bunchCrossing) { bunchCrossing_ = bunchCrossing; }
   void setOrbitNumber(Int_t orbitNumber) { orbitNumber_ = orbitNumber; }
   void setCollisionTime(unsigned long long collisionTime) { collisionTime_ = collisionTime; }
   void setBeamStatus(const TRootBeamStatus& beamStatus) { beamStatus_ = beamStatus; }
   void setTotoAnaProcessingTime(UInt_t totoAnaProcessingTime) { totoAnaProcessingTime_ = totoAnaProcessingTime; }
   void setGlobalL1(Bool_t passGlobalL1) { passGlobalL1_ = passGlobalL1; }
   void setPhysicsL1Accept(std::vector<Bool_t> physicsL1Accept)
   {
      physicsL1Accept_.resize(physicsL1Accept.size());
      for (unsigned int i=0; i!=physicsL1Accept.size(); ++i) physicsL1Accept_[i]=physicsL1Accept[i];
   }
   void setTechnicalL1Accept(std::vector<Bool_t> technicalL1Accept)
   {
      technicalL1Accept_.resize(technicalL1Accept.size());
      for (unsigned int i=0; i!=technicalL1Accept.size(); ++i) technicalL1Accept_[i]=technicalL1Accept[i];
   }
   
   void setHltAcceptNames(std::vector<std::string> hltAcceptNames)
   {
      hltAcceptNames_.resize(hltAcceptNames.size());
      for (unsigned int i=0; i!=hltAcceptNames.size(); ++i) hltAcceptNames_[i]=hltAcceptNames[i];
   }
   void setTrigHLT(std::vector<Bool_t> trigHLT)
   {
      trigHLT_.resize(trigHLT.size());
      for (unsigned int i=0; i!=trigHLT.size(); ++i) trigHLT_[i]=trigHLT[i];
   }
   void setPrescaleHLT(std::vector<UInt_t> prescaleHLT)
   {
      prescaleHLT_.resize(prescaleHLT.size());
      for (unsigned int i=0; i!=prescaleHLT.size(); ++i) prescaleHLT_[i]=prescaleHLT[i];
   }
   
   void setCsa07id(Int_t csa07id) { csa07id_=csa07id; }
   void setCsa07weight(Float_t csa07weight)  { csa07weight_=csa07weight; }
   void setCsa07process(TString csa07process)  { csa07process_=csa07process; }
   void setCsa07process(char* csa07process)  { csa07process_=csa07process; }
   
   void setNBasicClusters(Int_t type,Int_t nBC) { nBasicClusters_[type]=nBC; }
   void setNSuperClusters(Int_t type,Int_t nSC) { nSuperClusters_[type]=nSC; }
   
   void setPrimaryVertexIndex(Int_t primaryVertexIndex) { primaryVertexIndex_=primaryVertexIndex; }
   void setPrimaryVertex(TRootVertex* primaryVertex) { primaryVertex_ = primaryVertex; }
   
   void setProcessID(Int_t processID) { processID_=processID; }
   void setIdParton1(Int_t idParton1) { idParton1_=idParton1; }
   void setXParton1(Float_t xParton1) { xParton1_=xParton1; }
   void setXPDF1(Float_t xPDF1) { xPDF1_=xPDF1; }
   void setIdParton2(Int_t idParton2) { idParton2_=idParton2; }
   void setXParton2(Float_t xParton2) { xParton2_=xParton2; }
   void setXPDF2(Float_t xPDF2) { xPDF2_=xPDF2; }
   void setPdfScale(Float_t pdfScale) { pdfScale_=pdfScale; }
   void setEventScale(Float_t eventScale) { eventScale_=eventScale; }
   void setPtHat(Float_t ptHat) { ptHat_=ptHat; }
   void setWeight(Float_t weight) { weight_=weight; }
   
   void set_PU_TrueNumInteractions(Float_t pu_TrueNumInteractions) { pu_TrueNumInteractions_=pu_TrueNumInteractions; }
   void set_InTimePU_NumInteractions(Int_t inTimePU_NumInteractions) { inTimePU_NumInteractions_=inTimePU_NumInteractions; }
   void set_LatePU_NumInteractions(Int_t latePU_NumInteractions) { latePU_NumInteractions_=latePU_NumInteractions; }
   void set_EarlyPU_NumInteractions(Int_t earlyPU_NumInteractions) { earlyPU_NumInteractions_=earlyPU_NumInteractions; }
   void set_PU_z(std::vector<Float_t> pu_z) { pu_z_=pu_z; }
   void set_PU_bx(std::vector<Int_t> pu_bx) { pu_bx_=pu_bx; }
   void set_PU_sumPt_lowPt(std::vector<Float_t> pu_sumPt_lowPt) { pu_sumPt_lowPt_=pu_sumPt_lowPt; }
   void set_PU_sumPt_highPt(std::vector<Float_t> pu_sumPt_highPt) { pu_sumPt_highPt_=pu_sumPt_highPt; }
   void set_PU_nTrk_lowPt(std::vector<Int_t> pu_nTrk_lowPt) { pu_nTrk_lowPt_=pu_nTrk_lowPt; }
   void set_PU_nTrk_highPt(std::vector<Int_t> pu_nTrk_highPt) { pu_nTrk_highPt_=pu_nTrk_highPt; }
      
   void setRun(TObject* run) { run_=run; }
   void setRho(Float_t rho) { rho_=rho; }
   
   
   friend std::ostream& operator<< (std::ostream& stream, const TRootEvent& event) {
      stream << "Run " << event.runId() <<" Event "<< event.eventId() <<"  Luminosity block "<< event.luminosityBlock()
      <<"  Sequential Nb "<< event.nb() <<"  orbitNumber "<< event.orbitNumber() <<"  bunchCrossing "<< event.bunchCrossing()
      <<"  recorded on "<< event.asciiCollisionTime();
      return stream;
   };
   
   void Print()
   {
      std::cout << "Run " << this->runId() <<" Event "<< this->eventId() <<"  Luminosity block "<< this->luminosityBlock()
      <<"  Sequential Nb "<< this->nb() <<"  orbitNumber "<< this->orbitNumber() <<"  bunchCrossing "<< this->bunchCrossing()
      <<"  recorded on "<< this->asciiCollisionTime();
   };
   
   
private:
   
   UInt_t nb_;
   UInt_t eventId_;
   UInt_t runId_;
   UInt_t storeNumber_;
   UInt_t luminosityBlock_;
   Int_t bunchCrossing_;
   Int_t orbitNumber_;
   unsigned long long collisionTime_;
   TRootBeamStatus beamStatus_;
   UInt_t totoAnaProcessingTime_;
   
   // Trigger Infos
   Bool_t passGlobalL1_;
   std::vector<Bool_t> physicsL1Accept_;
   std::vector<Bool_t> technicalL1Accept_;
   std::vector<Bool_t> trigHLT_;
   std::vector<UInt_t> prescaleHLT_;
   
   std::vector<std::string> hltAcceptNames_; // keep only names of triggered HLT paths
   
   // CSA07 Process ID and Weight
   Int_t csa07id_;
   Float_t csa07weight_;
   TString csa07process_;
   
   map<Int_t,Int_t> nBasicClusters_;
   map<Int_t,Int_t> nSuperClusters_;
   
   // Selected Primary vertex (by VertexAnalyzer::SelectPrimary)
   Int_t primaryVertexIndex_; // Index in vertices TClonesArray of the selected primary vertex
   TRef primaryVertex_; // Reference to the TRootVertex of the selected primary vertex
   
   // GenEvent and PDF infos
   Int_t processID_;
   Int_t idParton1_;
   Float_t xParton1_;
   Float_t xPDF1_;
   Int_t idParton2_;
   Float_t xParton2_;
   Float_t xPDF2_;
   Float_t pdfScale_;
   Float_t eventScale_;
   Float_t ptHat_;
   Float_t weight_;
   
   // Pileup infos
   Float_t pu_TrueNumInteractions_;       // True Number of pileup
   Int_t inTimePU_NumInteractions_;       // Number of in-time (BX==0) pileup (total number of pileup even if outside detector acceptance)
   Int_t latePU_NumInteractions_;         // Number of late (BX==1) pileup (total number of pileup even if outside detector acceptance)
   Int_t earlyPU_NumInteractions_;        // Number of early (BX==-1) pileup (total number of pileup even if outside detector acceptance)
   std::vector<Float_t> pu_z_;            // z of the PU vertex
   std::vector<Int_t>   pu_bx_;           // Bunch Crossing Id of the PU vertex (in time <=> BX==0  ;  out of time <=> BX!=0)
   std::vector<Float_t> pu_sumPt_lowPt_;  // Sum of the pt of the track attached to the PU vertex (low pt threshold)
   std::vector<Float_t> pu_sumPt_highPt_; // Sum of the pt of the track attached to the PU vertex (high pt threshold)
   std::vector<Int_t>   pu_nTrk_lowPt_;   // Track multiplicity of the PU vertex (low pt threshold)
   std::vector<Int_t>   pu_nTrk_highPt_;  // Track multiplicity of the PU vertex (high pt threshold)
   
   
   TRef run_;  // reference to the TRootRun
   
   Float_t rho_; // rho of the event for Pile-Up energy estimation 
   
   ClassDef (TRootEvent,13);
   
};

#endif
