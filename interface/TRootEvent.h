#ifndef TRootEvent_h
#define TRootEvent_h

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "Rtypes.h"
#include "TObject.h"
#include "TVector3.h"
#include "TRef.h"

#include "../interface/TRootVertex.h"

using namespace std;

class TRootEvent : public TObject
{

   public:

      TRootEvent() :
      nb_(0)
      ,eventId_(0)
      ,runId_(0)
		,luminosityBlock_(0)
		,bunchCrossing_(0)
		,orbitNumber_(0)
		,collisionTime_(0)
		,totoAnaProcessingTime_(0)
		,passGlobalL1_(false)
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
      {;}

      ~TRootEvent() {;}

      // Collision infos
      UInt_t nb() const { return nb_; }
      UInt_t eventId() const { return eventId_; }
      UInt_t runId() const { return runId_; }
		UInt_t luminosityBlock() const { return luminosityBlock_; }
		Int_t bunchCrossing() const { return bunchCrossing_; }
		Int_t orbitNumber() const { return orbitNumber_; }
		unsigned long long collisionTime() const { return collisionTime_; }
		UInt_t totoAnaProcessingTime() const { return totoAnaProcessingTime_; }
		
      // Trigger decision
      Int_t passGlobalL1() const { return passGlobalL1_; }
      Bool_t passGlobalHLT() const { return passGlobalHLT_; }
      unsigned int nHLTPaths() const { return trigHLT_.size(); }
      std::vector<Bool_t> trigHLT() const { return trigHLT_; }
      Bool_t trigHLT(unsigned int i) const
      {
         if (trigHLT_.size()>i)
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



      void setNb(UInt_t nb) { nb_ = nb; }
      void setEventId(UInt_t eventId) { eventId_ = eventId; }
      void setRunId(UInt_t runId) { runId_ = runId; }
		void setLuminosityBlock(UInt_t luminosityBlock) { luminosityBlock_ = luminosityBlock; }
		void setBunchCrossing(Int_t bunchCrossing) { bunchCrossing_ = bunchCrossing; }
		void setOrbitNumber(Int_t orbitNumber) { orbitNumber_ = orbitNumber; }
		void setCollisionTime(unsigned long long collisionTime) { collisionTime_ = collisionTime; }
		void setTotoAnaProcessingTime(UInt_t totoAnaProcessingTime) { totoAnaProcessingTime_ = totoAnaProcessingTime; }
		void setGlobalL1(Int_t passGlobalL1) { passGlobalL1_ = passGlobalL1; }
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

      friend std::ostream& operator<< (std::ostream& stream, const TRootEvent& event) {
      stream << "Run " << event.runId() <<" Event "<< event.eventId() <<"  Luminosity block "<< event.luminosityBlock()
		<<"  Sequential Nb "<< event.nb() <<"  bunchCrossing "<< event.bunchCrossing() <<"  orbitNumber "<< event.orbitNumber();
      return stream;
      };

		
   private:

      UInt_t nb_;
      UInt_t eventId_;
      UInt_t runId_;
		UInt_t luminosityBlock_;
		Int_t bunchCrossing_;
		Int_t orbitNumber_;
		unsigned long long collisionTime_;
		UInt_t totoAnaProcessingTime_;
		
      // Trigger Infos
      Bool_t passGlobalL1_;
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

      ClassDef (TRootEvent,3);

};

#endif
