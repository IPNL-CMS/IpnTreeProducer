#ifndef PhotonIsolator_h
#define PhotonIsolator_h

#include <memory>
#include <string>
#include <iostream>
#include <map>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
//#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
//#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
//#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "TrackingTools/GeomPropagators/interface/AnalyticalPropagator.h"
#include "TrackingTools/MaterialEffects/interface/PropagatorWithMaterial.h"
#include "DataFormats/TrajectoryState/interface/PTrajectoryStateOnDet.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "DataFormats/GeometrySurface/interface/BoundCylinder.h"
#include "DataFormats/GeometrySurface/interface/BoundDisk.h"
#include "DataFormats/GeometrySurface/interface/SimpleCylinderBounds.h"
#include "DataFormats/GeometrySurface/interface/SimpleDiskBounds.h"

#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"

#include "../interface/TRootPhoton.h"
#include "../interface/TRootSuperCluster.h"
#include "../interface/TRootCluster.h"
#include "../interface/TRootTrack.h"

#include "TClonesArray.h"

#define PI 3.141592654
#define TWOPI 6.283185308


class PhotonIsolator{
   
public:
   
   PhotonIsolator(edm::ParameterSet * config, edm::ParameterSet * producersNames);
   ~PhotonIsolator();
   
   float deltaPhi(float phi1, float phi2);
   float deltaR(float phi1, float phi2, float eta1, float eta2);
   void setVerbosity(int verbosity) {verbosity_ = verbosity; };
   bool loadHcalRecHits(const edm::Event& iEvent, const edm::EventSetup& iSetup);
   Double_t basicClustersIsolation(TRootPhoton* photon, TClonesArray* superClusters, TClonesArray* basicClusters);
   Double_t basicClustersDoubleConeIsolation(TRootPhoton* photon, TClonesArray* superClusters, TClonesArray* basicClusters);
   Double_t hcalRecHitIsolation(TRootPhoton* photon);
   Double_t trackerIsolation(TRootPhoton* photon, TClonesArray* tracks, Int_t &nTracks);
   Int_t nNiceTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, const edm::ParameterSet& producersNames, TRootPhoton* photon);
   bool getTrackImpactPosition(const reco::Track* tk_ref, const TrackerGeometry* trackerGeom, const MagneticField* magField, math::XYZPoint& ew) const;
   
private:
   
   edm::ParameterSet * config_;
   edm::ParameterSet * producersNames_;
   edm::InputTag  trackProducer_;
   edm::InputTag beamSpotProducer_;
   int verbosity_;
   int basicClustersIsolation_BarrelSC_type_;
   int basicClustersIsolation_EndcapSC_type_;
   int basicClustersIsolation_BarrelBC_type_;
   int basicClustersIsolation_EndcapBC_type_;
   double basicClustersIsolation_DRmax_;
   double basicClustersIsolation_ClusterEt_threshold_;
   int basicClustersDoubleConeIsolation_BarrelSC_type_;
   int basicClustersDoubleConeIsolation_EndcapSC_type_;
   int basicClustersDoubleConeIsolation_BarrelBC_type_;
   int basicClustersDoubleConeIsolation_EndcapBC_type_;
   double basicClustersDoubleConeIsolation_DRmin_;
   double basicClustersDoubleConeIsolation_DRmax_;
   double basicClustersDoubleConeIsolation_ClusterEt_threshold_;
   double trackerNiceTracksIsolationLIP_;
   double trackerNiceTracksIsolationD0_;
   double trackerNiceTracksIsolationTrackThreshold_;
   double trackerNiceTracksIsolationdROuterRadius_;
   double trackerNiceTracksIsolationdRInnerRadius_;
   double trackerNiceTracksIsolationTrackEtaSlice_;
   double hcalRecHitIsolation_DRmax_;
   double hcalRecHitIsolation_HitEt_threshold_;
   double trackerIsolation_DRmax_;
   double trackerIsolation_pt_threshold_;
   int trackerIsolation_pixelLayers_threshold_;
   bool allowMissingCollection_;
   
   const HBHERecHitCollection* hbheHits_;
   const HORecHitCollection* hoHits_;
   const HFRecHitCollection* hfHits_;
   const CaloGeometry* geometry_;
   
};

#endif
