#include "../interface/PhotonIsolator.h"

PhotonIsolator::PhotonIsolator(edm::ParameterSet * config, edm::ParameterSet * producersNames):config_(config), producersNames_(producersNames)
{
   verbosity_ = (*config_).getUntrackedParameter<int>("verbosity", 0);
   basicClustersIsolation_BarrelBC_type_ = (*config_).getParameter<int>("basicClustersIsolation_BarrelBC_type");
   basicClustersIsolation_EndcapBC_type_ = (*config_).getParameter<int>("basicClustersIsolation_EndcapBC_type");
   basicClustersIsolation_DRmax_ = (*config_).getParameter<double>("basicClustersIsolation_DRmax");
   basicClustersIsolation_ClusterEt_threshold_ = (*config_).getParameter<double>("basicClustersIsolation_ClusterEt_threshold");
   basicClustersDoubleConeIsolation_BarrelBC_type_ = (*config_).getParameter<int>("basicClustersDoubleConeIsolation_BarrelBC_type");
   basicClustersDoubleConeIsolation_EndcapBC_type_ = (*config_).getParameter<int>("basicClustersDoubleConeIsolation_EndcapBC_type");
   basicClustersDoubleConeIsolation_DRmin_ = (*config_).getParameter<double>("basicClustersDoubleConeIsolation_DRmin");
   basicClustersDoubleConeIsolation_DRmax_ = (*config_).getParameter<double>("basicClustersDoubleConeIsolation_DRmax");
   basicClustersDoubleConeIsolation_ClusterEt_threshold_ = (*config_).getParameter<double>("basicClustersDoubleConeIsolation_ClusterEt_threshold");
   hcalRecHitIsolation_DRmax_ = (*config_).getParameter<double>("hcalRecHitIsolation_DRmax");
   hcalRecHitIsolation_HitEt_threshold_ = (*config_).getParameter<double>("hcalRecHitIsolation_HitEt_threshold");
   trackerIsolation_DRmax_ = (*config_).getParameter<double>("trackerIsolation_DRmax");
   trackerIsolation_pt_threshold_ = (*config_).getParameter<double>("trackerIsolation_pt_threshold");
   trackerNiceTracksIsolationD0_ = (*config_).getParameter<double>("trackerNiceTracksIsolationD0");
   trackerIsolation_pixelLayers_threshold_ = (*config_).getParameter<int>("trackerIsolation_pixelLayers_threshold");
   trackerNiceTracksIsolationLIP_ = (*config_).getParameter<double>("trackerNiceTracksIsolationLIP");
   trackerNiceTracksIsolationTrackThreshold_ = (*config_).getParameter<double>("trackerNiceTracksIsolationTrackThreshold");
   trackerNiceTracksIsolationdROuterRadius_ = (*config_).getParameter<double>("trackerNiceTracksIsolationdROuterRadius");
   trackerNiceTracksIsolationdRInnerRadius_ = (*config_).getParameter<double>("trackerNiceTracksIsolationdRInnerRadius");
   trackerNiceTracksIsolationTrackEtaSlice_ = (*config_).getParameter<double>("trackerNiceTracksIsolationTrackEtaSlice");

   allowMissingCollection_ = (*producersNames_).getUntrackedParameter<bool>("allowMissingCollection", false);
}


PhotonIsolator::~PhotonIsolator()
{
}


float PhotonIsolator::deltaR(float phi1, float phi2, float eta1, float eta2)
{
   float dphi=deltaPhi(phi1,phi2);
   float deta=fabs(eta1-eta2);
   float dr = sqrt(dphi*dphi+ deta*deta);
   return dr;
}


float PhotonIsolator::deltaPhi(float phi1, float phi2)
{
   float dphi;
   if(phi1<0) phi1+=TWOPI;
   if(phi2<0) phi2+=TWOPI;
   dphi=fabs(phi1-phi2);
   if(dphi>TWOPI) dphi-=TWOPI;
   if(dphi>PI) dphi=TWOPI-dphi;
   return dphi;
}


bool PhotonIsolator::loadHcalRecHits(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   // Get HB/HE rechits
   try
   {
      edm::InputTag hbheRecHitProducer = producersNames_->getParameter<edm::InputTag>("hbheRecHitProducer");
      edm::Handle<HBHERecHitCollection> hbheHandle;
      iEvent.getByLabel(hbheRecHitProducer, hbheHandle);
      hbheHits_ = hbheHandle.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  PhotonIsolator::LoadHcalRecHits => No HBHERecHitCollection #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No HBHERecHitCollection, skip HCAL rechits isolation" << endl;
      return false;
   }
   
   // Get HO rechits
   try
   {
      edm::InputTag hoRecHitProducer = producersNames_->getParameter<edm::InputTag>("hoRecHitProducer");
      edm::Handle<HORecHitCollection> hoHandle;
      iEvent.getByLabel(hoRecHitProducer, hoHandle);
      hoHits_ = hoHandle.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  PhotonIsolator::LoadHcalRecHits => No HORecHitCollection #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No HORecHitCollection, skip HCAL rechits isolation" << endl;
      return false;
   }
   
   // Get HF rechits
   try
   {
      edm::InputTag hfRecHitProducer = producersNames_->getParameter<edm::InputTag>("hfRecHitProducer");
      edm::Handle<HFRecHitCollection> hfHandle;
      iEvent.getByLabel(hfRecHitProducer, hfHandle);
      hfHits_ = hfHandle.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  PhotonIsolator::LoadHcalRecHits => No HFRecHitCollection #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No HFRecHitCollection, skip HCAL rechits isolation" << endl;
      return false;
   }
   
   // Get Calo Geometry
   try
   {
      edm::ESHandle<CaloGeometry> geomHandle;
      (iSetup.get<CaloGeometryRecord>()).get(geomHandle);
      geometry_ = geomHandle.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  PhotonIsolator::LoadHcalRecHits => No CaloGeometryRecord #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No CaloGeometryRecord, skip HCAL rechits isolation" << endl;
      return false;
   }
   
   return true;
}


Double_t PhotonIsolator::basicClustersIsolation(TRootPhoton* photon, TClonesArray* superClusters, TClonesArray* basicClusters)
{
   Double_t sumEt = 0.;
   Int_t isc_barrel = photon->scIndexOfType(basicClustersIsolation_BarrelBC_type_);
   Int_t isc_endcap = photon->scIndexOfType(basicClustersIsolation_EndcapBC_type_);
   Int_t isc = max(isc_barrel,isc_endcap);
   
	if(isc==-1)
	{
		if(verbosity_>1) cout << "  ##### ERROR IN  PhotonIsolator::BasicClustersIsolation => no supercluster associated to the photon #####" << endl;
		return -1.;
	}
   
   TRootSuperCluster* photonSC =  (TRootSuperCluster*) superClusters->At(isc);
   //cout << "Associated SC[" << isc << "]" << endl;;
   
   TRootCluster* localBC;
   for (int ibc=0; ibc<basicClusters->GetEntriesFast(); ibc++)
   {
      localBC = (TRootCluster*) basicClusters->At(ibc);
      //cout << "localBC[" << ibc << "] type=" << localBC->type() << endl;
      if( localBC->type()==basicClustersIsolation_BarrelBC_type_ || localBC->type()==basicClustersIsolation_EndcapBC_type_ )
      {
         if( localBC->Pt()>basicClustersIsolation_ClusterEt_threshold_  )
         {
            // No vertex correction for BC, so used uncorrected SC position for isolation
            //Double_t dR = deltaR( photon->Phi(), localBC->Phi(), photon->Eta(), localBC->Eta() );
            Double_t dR = deltaR( photonSC->Phi(), localBC->Phi(), photonSC->Eta(), localBC->Eta() );
            //cout << "localBC DeltaR=" << dR << endl;
            if( dR<basicClustersIsolation_DRmax_ )
            {
               bool inSuperCluster = false;
               for (unsigned int isub=0; isub<photonSC->subBasicClusterIndexVector().size(); isub++)
               {
                  // Veto Basic Clusters belonging to photon supercluster
                  if ( ibc==photonSC->subBasicClusterIndexVector().at(isub) )
                  {
                     inSuperCluster = true;
                     //break; //FIXME - Add break
                  }
               }
               //if (inSuperCluster) cout << "localBC in photonSC" << endl;
               //if (!inSuperCluster) cout << "localBC not in photonSC" << endl;
               if (!inSuperCluster) sumEt+=localBC->Pt();
               //cout << "sumEt=" << sumEt << endl;
            }
         }
      }
   }
   return sumEt;
}


Double_t PhotonIsolator::basicClustersDoubleConeIsolation(TRootPhoton* photon, TClonesArray* superClusters, TClonesArray* basicClusters)
{
   Int_t isc_barrel = photon->scIndexOfType(basicClustersDoubleConeIsolation_BarrelBC_type_);
   Int_t isc_endcap = photon->scIndexOfType(basicClustersDoubleConeIsolation_EndcapBC_type_);
   Int_t isc = max(isc_barrel,isc_endcap);
   
   if(isc==-1) { cout << "  ##### ERROR IN  PhotonIsolator::BasicClustersDoubleConeIsolation => no supercluster associated to the photon #####" << endl; return -1.;}
   
   TRootSuperCluster* photonSC =  (TRootSuperCluster*) superClusters->At(isc);
   
   Double_t sumEt = 0.;
   TRootCluster* localBC;
   for (int ibc=0; ibc<basicClusters->GetEntriesFast(); ibc++)
   {
      localBC = (TRootCluster*) basicClusters->At(ibc);
      if( localBC->type()==basicClustersDoubleConeIsolation_BarrelBC_type_ || localBC->type()==basicClustersDoubleConeIsolation_EndcapBC_type_ )
      {
         if( localBC->Pt()>basicClustersDoubleConeIsolation_ClusterEt_threshold_ )
         {
            // No vertex correction for BC, so used uncorrected SC position for isolation
            //Double_t dR = deltaR( photon->Phi(), localBC->Phi(), photon->Eta(), localBC->Eta() );
            Double_t dR = deltaR( photonSC->Phi(), localBC->Phi(), photonSC->Eta(), localBC->Eta() );
            if( dR<basicClustersDoubleConeIsolation_DRmax_ && dR>basicClustersDoubleConeIsolation_DRmin_ )
            {
               sumEt+=localBC->Pt();
            }
         }
      }
   }
   return sumEt;
}


Double_t PhotonIsolator::hcalRecHitIsolation(TRootPhoton* photon)
{
   Double_t sumEt=0.;
   
   // No vertex correction for recHits, so used uncorrected photon position
   //double phi=photon->Phi();
   //double eta=photon->Eta();
   double phi=photon->caloPosition().Phi();
   double eta=photon->caloPosition().Eta();
   
   for(HBHERecHitCollection::const_iterator hbheItr = hbheHits_->begin(); hbheItr != hbheHits_->end(); hbheItr++)
   {
      double HcalHit_energy=hbheItr->energy();
      double HcalHit_eta=geometry_->getPosition(hbheItr->id()).eta();
      double HcalHit_phi=geometry_->getPosition(hbheItr->id()).phi();
      float HcalHit_pth=HcalHit_energy*sin(2*atan(exp(-HcalHit_eta)));
      
      if(HcalHit_pth>hcalRecHitIsolation_HitEt_threshold_)
      {
         float newDelta=deltaR(HcalHit_phi,phi,HcalHit_eta,eta);
         if(newDelta<hcalRecHitIsolation_DRmax_) sumEt+=HcalHit_pth;
      }
   }
   
   
   for(HFRecHitCollection::const_iterator hfItr = hfHits_->begin(); hfItr != hfHits_->end(); hfItr++)
   {
      double HcalHit_energy=hfItr->energy();
      double HcalHit_eta=geometry_->getPosition(hfItr->id()).eta();
      double HcalHit_phi=geometry_->getPosition(hfItr->id()).phi();
      float HcalHit_pth=HcalHit_energy*sin(2*atan(exp(-HcalHit_eta)));
      
      if(HcalHit_pth>hcalRecHitIsolation_HitEt_threshold_)
      {
         float newDelta=deltaR(HcalHit_phi,phi,HcalHit_eta,eta);
         if(newDelta<hcalRecHitIsolation_DRmax_) sumEt+=HcalHit_pth;
      }
   }
   
   
   for(HORecHitCollection::const_iterator hoItr = hoHits_->begin(); hoItr != hoHits_->end(); hoItr++)
   {
      double HcalHit_energy=hoItr->energy();
      double HcalHit_eta=geometry_->getPosition(hoItr->id()).eta();
      double HcalHit_phi=geometry_->getPosition(hoItr->id()).phi();
      float HcalHit_pth=HcalHit_energy*sin(2*atan(exp(-HcalHit_eta)));
      if(HcalHit_pth>hcalRecHitIsolation_HitEt_threshold_)
      {
         float newDelta=deltaR(HcalHit_phi,phi,HcalHit_eta,eta);
         if(newDelta<hcalRecHitIsolation_DRmax_) sumEt+=HcalHit_pth;
      }
   }
   
   return sumEt;
}


Double_t PhotonIsolator::trackerIsolation(TRootPhoton* photon, TClonesArray* tracks, Int_t &nTracks)
{
   // FIXME - If photon not vertex corrected then correct it
   Double_t sumPt = 0.;
   nTracks = 0;
   TRootTrack* localTrack;
   for (int itk=0; itk<tracks->GetEntriesFast(); itk++)
   {
      localTrack = (TRootTrack*) tracks->At(itk);
      if( localTrack->Pt() > trackerIsolation_pt_threshold_ && localTrack->pixelLayersWithMeasurement() >= trackerIsolation_pixelLayers_threshold_ )
      {
         Double_t dR = deltaR( photon->Phi(), localTrack->Phi(), photon->Eta(), localTrack->Eta() );
         if( dR<trackerIsolation_DRmax_ )
         {
            sumPt+=localTrack->Pt();
            nTracks++;
         }
      }
   }
   return sumPt;
}


Int_t PhotonIsolator::nNiceTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, const edm::ParameterSet& producersNames, TRootPhoton* photon)
{
   edm::ESHandle<TrackerGeometry> trackerGeomHandle;
   edm::ESHandle<MagneticField> magFieldHandle;
   iSetup.get<TrackerDigiGeometryRecord>().get( trackerGeomHandle );
   iSetup.get<IdealMagneticFieldRecord>().get( magFieldHandle );
   const TrackerGeometry* trackerGeom = trackerGeomHandle.product();
   const MagneticField* magField = magFieldHandle.product();
   
   trackProducer_ = producersNames.getParameter<edm::InputTag>("trackProducer");
   edm::Handle<reco::TrackCollection> recoTracks;
   try
   {
      iEvent.getByLabel(trackProducer_, recoTracks);
      int nTracks = recoTracks->size();
      if(verbosity_>1) std::cout << "   Number of tracks = " << nTracks << "   Label: " << trackProducer_.label() << "   Instance: " << trackProducer_.instance() << std::endl;
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         cout << "  ##### ERROR IN  TrackAnalyzer::process => Track collection is missing #####"<<endl;
         throw exception;
      }
      if(verbosity_>1) cout <<  "   ===> No Track collection, skip track info" << endl;
      return false;
   }
   
   reco::BeamSpot vertexBeamSpot;
   beamSpotProducer_ = producersNames.getParameter<edm::InputTag>("beamSpotProducer");
   edm::Handle<reco::BeamSpot> recoBeamSpotHandle;
   iEvent.getByLabel(beamSpotProducer_,recoBeamSpotHandle);
   vertexBeamSpot = *recoBeamSpotHandle;
   math::XYZPoint theBeamSpot(vertexBeamSpot.x0(),vertexBeamSpot.y0(),vertexBeamSpot.z0());
   int nNiceTracks = 0;
   
   //loop over tracks
   for(reco::TrackCollection::const_iterator trItr = recoTracks->begin(); trItr != recoTracks->end(); ++trItr)
   {
      // check if the track has a pixel seed
      bool isFirstPixelHit = trItr->hitPattern().hasValidHitInFirstPixelBarrel();
      if (isFirstPixelHit == false) continue;
      
      // first check if the track pass the dzCut
      double dzCut = fabs( (*trItr).vz() - photon->vz() );
      if (dzCut > trackerNiceTracksIsolationLIP_) continue;
      
      // check if the pt of the track is higher than the threshold
      double this_pt  = (*trItr).pt();
      if (this_pt < trackerNiceTracksIsolationTrackThreshold_ ) continue;
      
      // only consider tracks from the main vertex
      if (fabs( (*trItr).dxy(theBeamSpot) ) > trackerNiceTracksIsolationD0_ ) continue;
      
      // check if the extrapolation of the track is in the cone
      math::XYZPoint ipt;
      bool gotImp = PhotonIsolator::getTrackImpactPosition(&(*trItr), trackerGeom, magField, ipt);
      math::XYZVector tmpTrackMomentumAtVtx = (*trItr).momentum () ;
      double drMatch = deltaR(ipt.Phi(), photon->Phi(),ipt.Eta(), photon->Eta());
      if (!( (drMatch<trackerNiceTracksIsolationdROuterRadius_))) continue;
      
      double dr = deltaR(photon->Phi(),tmpTrackMomentumAtVtx.Phi(),photon->Eta(),tmpTrackMomentumAtVtx.Eta());
      double deta = (*trItr).eta() - photon->Eta() ;
      if ( (dr<trackerNiceTracksIsolationdROuterRadius_)&&(dr>=trackerNiceTracksIsolationdRInnerRadius_)&&(fabs(deta)>trackerNiceTracksIsolationTrackEtaSlice_))
      {
         nNiceTracks++;
      }
   }
   return nNiceTracks;
}


bool PhotonIsolator::getTrackImpactPosition(const reco::Track* tk_ref, const TrackerGeometry* trackerGeom, const MagneticField* magField, math::XYZPoint& ew) const
{
  PropagatorWithMaterial propag( alongMomentum, 0.000511, magField );
  TrajectoryStateTransform transformer;
  ReferenceCountingPointer<Surface> ecalWall( new  BoundCylinder( GlobalPoint(0.,0.,0.), TkRotation<float>(), SimpleCylinderBounds( 129, 129, -320.5, 320.5 ) ) );
  const float epsilon = 0.001;
  Surface::RotationType rot; // unit rotation matrix
  const float barrelRadius = 129.f;
  const float barrelHalfLength = 270.9f;
  const float endcapRadius = 171.1f;
  const float endcapZ = 320.5f;
  ReferenceCountingPointer<BoundCylinder> theBarrel_(new BoundCylinder( Surface::PositionType(0,0,0), rot,SimpleCylinderBounds( barrelRadius-epsilon, barrelRadius+epsilon, -barrelHalfLength, barrelHalfLength)));
  ReferenceCountingPointer<BoundDisk> theNegativeEtaEndcap_( new BoundDisk( Surface::PositionType( 0, 0, -endcapZ), rot, SimpleDiskBounds( 0, endcapRadius, -epsilon, epsilon)));
  ReferenceCountingPointer<BoundDisk> thePositiveEtaEndcap_( new BoundDisk( Surface::PositionType( 0, 0, endcapZ), rot, SimpleDiskBounds( 0, endcapRadius, -epsilon, epsilon)));

  const TrajectoryStateOnSurface myTSOS = transformer.outerStateOnSurface(*tk_ref, *trackerGeom, magField);
  TrajectoryStateOnSurface  stateAtECAL;
  stateAtECAL = propag.propagate(myTSOS, *theBarrel_);
  if (!stateAtECAL.isValid() || ( stateAtECAL.isValid() && fabs(stateAtECAL.globalPosition().eta() ) >1.479 )  )
  {
    //endcap propagator
    if (myTSOS.globalPosition().eta() > 0.) stateAtECAL = propag.propagate(myTSOS, *thePositiveEtaEndcap_);
    else stateAtECAL = propag.propagate(myTSOS, *theNegativeEtaEndcap_);
  }
  
  if (stateAtECAL.isValid())
  {
    ew = stateAtECAL.globalPosition();
    return true;
  }
  else
    return false;
}

