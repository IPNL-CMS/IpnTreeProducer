#ifndef ZeeVertexAnalyzer_h
#define ZeeVertexAnalyzer_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"

#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "RecoVertex/PrimaryVertexProducer/interface/PrimaryVertexProducerAlgorithm.h"

#include "../interface/TRootTrack.h"
#include "../interface/TRootVertex.h"
#include "../interface/TRootBardak.h"

#include "TClonesArray.h"

class ZeeVertexAnalyzer
{
	
	public:
		ZeeVertexAnalyzer(const edm::ParameterSet& iConfig, const edm::ParameterSet& producersNames, int verbosity);
		~ZeeVertexAnalyzer();
		void setVerbosity(int verbosity) {verbosity_ = verbosity; };
		bool getVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup, TClonesArray* rootVertices, TRootBardak* rootBardak);
		
	private:
		int verbosity_;
		edm::ParameterSet config_;
		edm::InputTag primaryVertexProducer_;
		edm::InputTag beamSpotProducer_;
		edm::InputTag trackProducer_;
		edm::InputTag electronProducer_;
		bool allowMissingCollection_;
		
};

#endif
