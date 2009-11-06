#ifndef TrackAnalyzer_h
#define TrackAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"

#include "../interface/TRootTrack.h"

#include "TClonesArray.h"


class TrackAnalyzer
{

   public:
      TrackAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
      ~TrackAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      bool process(const edm::Event& iEvent, TClonesArray* rootTracks);

   private:
      int verbosity_;
      edm::InputTag trackProducer_;
      bool allowMissingCollection_;

};

#endif
