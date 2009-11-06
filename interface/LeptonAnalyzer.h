#ifndef LeptonAnalyzer_h
#define LeptonAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/IPTools/interface/IPTools.h"

#include "FWCore/Framework/interface/EventSetupRecordImplementation.h"

#include "../interface/TRootEvent.h"
#include "../interface/TRootBeamSpot.h"


class LeptonAnalyzer
{

   public:
      LeptonAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
      ~LeptonAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      void initIPCalculator(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent, TRootBeamSpot* rootBeamSpot);
      float ip3DSignificance(const reco::TransientTrack& track);

   protected:
      int verbosity_;
      bool allowMissingCollection_;
      bool initOK_;
      std::string dataType_ ;
      bool doPrimaryVertex_;
      bool doBeamSpot_;
      edm::InputTag vertexProducer_;
      bool dummyVertex_;
      edm::ESHandle<TransientTrackBuilder> trackBuilder_;
      const reco::Vertex* primaryVertex_;
      const GlobalPoint* vertexPoint_;

};

#endif
