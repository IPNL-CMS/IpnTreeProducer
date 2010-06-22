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

using namespace std;

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
      ,passGlobalHLT_(false)
      ,trigHLT_(0)
      ,csa07id_(-1)
      ,csa07weight_(-1.)
      ,csa07process_()
      ,nBasicClusters_()
      ,nSuperClusters_()
      ,primaryVertexIndex_(-1)
      ,primaryVertex_(0)
      ,idParton1_(-1)
      ,xParton1_(-1.)
      ,idParton2_(-1)
      ,xParton2_(-1.)
      ,factorizationScale_(-1.)
      ,eventScale_(-1.)
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
         if (0<=i && i<physicsL1Accept_.size())
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
         if (0<=i && i<technicalL1Accept_.size())
         {
            return technicalL1Accept_.at(i);
         }
         else
         {
            cout << "Technical L1 path " << i << " not found" << endl;
            return false;
         }
      }
      
      // HLT decision
      Bool_t passGlobalHLT() const { return passGlobalHLT_; }
      unsigned int nHLTPaths() const { return trigHLT_.size(); }
      std::vector<Bool_t> trigHLT() const { return trigHLT_; }
      Bool_t trigHLT(unsigned int i) const
      {
         if (0<=i && i<trigHLT_.size())
         {
            return trigHLT_.at(i);
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
      // flavour first incoming parton
      Int_t idParton1() const { return idParton1_; }
      // energy fraction carried by first incoming parton
      Float_t xParton1() const { return xParton1_; }
      // flavour first incoming parton
      Int_t idParton2() const { return idParton2_; }
      // energy fraction carried by first incoming parton
      Float_t xParton2() const { return xParton2_; }
      // Factorization Scale Q
      Float_t factorizationScale() const { return factorizationScale_; }
      // Event scale (pt_hat for PYTHIA)
      Float_t eventScale() const { return eventScale_; }
      
      
      
      void setNb(UInt_t nb) { nb_ = nb; }
      void setEventId(UInt_t eventId) { eventId_ = eventId; }
      void setRunId(UInt_t runId) { runId_ = runId; }
      void setStoreNumber(UInt_t storeNumber) { storeNumber_ = storeNumber; }
      void setLuminosityBlock(UInt_t luminosityBlock) { luminosityBlock_ = luminosityBlock; }
      void setBunchCrossing(Int_t bunchCrossing) { bunchCrossing_ = bunchCrossing; }
      void setOrbitNumber(Int_t orbitNumber) { orbitNumber_ = orbitNumber; }
      void setCollisionTime(unsigned long long collisionTime) { collisionTime_ = collisionTime; }
      void setBeamStatus(TRootBeamStatus beamStatus) { beamStatus_ = beamStatus; }
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
      
      void setGlobalHLT(Bool_t passGlobalHLT) { passGlobalHLT_ = passGlobalHLT; }
      void setTrigHLT(std::vector<Bool_t> trigHLT)
      {
         trigHLT_.resize(trigHLT.size());
         for (unsigned int i=0; i!=trigHLT.size(); ++i) trigHLT_[i]=trigHLT[i];
      }
      
      void setCsa07id(Int_t csa07id) { csa07id_=csa07id; }
      void setCsa07weight(Float_t csa07weight)  { csa07weight_=csa07weight; }
      void setCsa07process(TString csa07process)  { csa07process_=csa07process; }
      void setCsa07process(char* csa07process)  { csa07process_=csa07process; }
      
      void setNBasicClusters(Int_t type,Int_t nBC) { nBasicClusters_[type]=nBC; }
      void setNSuperClusters(Int_t type,Int_t nSC) { nSuperClusters_[type]=nSC; }
      
      void setPrimaryVertexIndex(Int_t primaryVertexIndex) { primaryVertexIndex_=primaryVertexIndex; }
      void setPrimaryVertex(TRootVertex* primaryVertex) { primaryVertex_ = primaryVertex; }
      
      void setIdParton1(Int_t idParton1) { idParton1_=idParton1; }
      void setXParton1(Float_t xParton1) { xParton1_=xParton1; }
      void setIdParton2(Int_t idParton2) { idParton2_=idParton2; }
      void setXParton2(Float_t xParton2) { xParton2_=xParton2; }
      void setFactorizationScale(Float_t factorizationScale) { factorizationScale_=factorizationScale; }
      void setEventScale(Float_t eventScale) { eventScale_=eventScale; }
      
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
      Bool_t passGlobalHLT_;
      std::vector<Bool_t> trigHLT_;
      
      // CSA07 Process ID and Weight
      Int_t csa07id_;
      Float_t csa07weight_;
      TString csa07process_;
      
      map<Int_t,Int_t> nBasicClusters_;
      map<Int_t,Int_t> nSuperClusters_;
      
      // Selected Primary vertex (by VertexAnalyzer::SelectPrimary)
      Int_t primaryVertexIndex_; // Index in vertices TClonesArray of the selected primary vertex
      TRef primaryVertex_; // Reference to the TRootVertex of the selected primary vertex
      
      // PDF infos
      Int_t idParton1_;
      Float_t xParton1_;
      Int_t idParton2_;
      Float_t xParton2_;
      Float_t factorizationScale_;
      Float_t eventScale_;
      
      ClassDef (TRootEvent,6);
      
};

#endif
