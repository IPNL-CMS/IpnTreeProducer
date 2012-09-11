#ifndef PhotonAnalyzer_h
#define PhotonAnalyzer_h

// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"

#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
//#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEgamma/EgammaTools/interface/EGEnergyCorrector.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"

#include "DataFormats/VertexReco/interface/Vertex.h" 	
#include "DataFormats/VertexReco/interface/VertexFwd.h"

//#include "DataFormats/EgammaCandidates/interface/PhotonID.h"
//#include "DataFormats/EgammaCandidates/interface/PhotonIDFwd.h"
//#include "DataFormats/EgammaCandidates/interface/PhotonIDAssociation.h"

#include "DataFormats/EgammaCandidates/interface/PhotonPi0DiscriminatorAssociation.h"

//#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"

#include "../interface/TRootEvent.h"
#include "../interface/TRootPhoton.h"
#include "../interface/TRootTrack.h"

#include "TClonesArray.h"


class PhotonAnalyzer
{
   
   public:
      PhotonAnalyzer(const edm::InputTag& photonProducer, const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
      ~PhotonAnalyzer();
      void setVerbosity(int verbosity) {verbosity_ = verbosity; };
      bool process(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent, TClonesArray* rootPhotons, TClonesArray* conversionTracks, EcalClusterLazyTools* lazyTools, EGEnergyCorrector* egEnergyRegression);
      //bool process(const edm::Event& iEvent, TRootEvent* rootEvent, TClonesArray* rootPhotons, TClonesArray* conversionTracks, EcalClusterLazyTools* lazyTools);
      
   private:
      int verbosity_;
      int iconvtrack_;
      std::string dataType_ ;
      edm::InputTag photonProducer_;
      edm::InputTag primaryVertexProducer_;
      edm::InputTag reducedBarrelEcalRecHitCollection_;
      edm::InputTag reducedEndcapEcalRecHitCollection_;
      bool doPhotonEnergyRegression_;
      bool doPhotonConversion_;
      bool doVertexCorrection_;
      bool useMC_;
      bool allowMissingCollection_;
      
};

#endif
