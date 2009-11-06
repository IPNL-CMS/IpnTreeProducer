#ifndef VertexAnalyzer_h
#define VertexAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "../interface/TRootEvent.h"
#include "../interface/TRootBeamSpot.h"
#include "../interface/TRootVertex.h"

#include "TClonesArray.h"


class VertexAnalyzer
{

   public:
      VertexAnalyzer(const edm::ParameterSet& producersNames);
      VertexAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
      ~VertexAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      bool getBeamSpot(const edm::Event& iEvent, TRootBeamSpot* rootBeamSpot);
      bool getVertices(const edm::Event& iEvent, TClonesArray* rootVertices);
      void selectPrimary(TRootEvent* rootEvent, TClonesArray* rootVertices);

   private:
      int verbosity_;
      edm::InputTag primaryVertexProducer_;
      edm::InputTag beamSpotProducer_;
      bool allowMissingCollection_;

};

#endif
