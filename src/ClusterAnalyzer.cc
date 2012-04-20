#include "../interface/ClusterAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

bool operator< (const TRootEcalRecHit & left, const TRootEcalRecHit & right) { return left.energy()<right.energy(); }
bool decrease(const TRootEcalRecHit & left, const TRootEcalRecHit & right) { return left.energy()>right.energy(); }

ClusterAnalyzer::ClusterAnalyzer(const edm::ParameterSet& config, const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity), iClus_(0), doRecHits_(true)
{
   dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
   reducedBarrelEcalRecHitCollection_ = producersNames.getParameter<edm::InputTag>("reducedBarrelEcalRecHitCollection");
   reducedEndcapEcalRecHitCollection_ = producersNames.getParameter<edm::InputTag>("reducedEndcapEcalRecHitCollection");
   keepClusterizedEcalRecHits_ = config.getUntrackedParameter<bool>("keepClusterizedEcalRecHits", false);
   allowMissingCollection_ = producersNames.getUntrackedParameter<bool>("allowMissingCollection", false);
   doCracksCorrection_ = config.getUntrackedParameter<bool>("doCracksCorrection", false);
}


ClusterAnalyzer::~ClusterAnalyzer()
{
}


bool ClusterAnalyzer::process(const edm::Event& iEvent, const edm::EventSetup& iSetup, TRootEvent* rootEvent, EcalClusterLazyTools* lazyTools, TClonesArray* rootClusters, const edm::InputTag& basicClusterProducer, const int clusterType)
{
   
   // get Ecal rechits
   if(verbosity_>1) cout << endl << "Loading egamma LazyTools..." << endl;
   const EcalRecHitCollection *reducedEBRecHits = 0;
   const EcalRecHitCollection *reducedEERecHits = 0;
   edm::Handle < EcalRecHitCollection > redEBRecHits;
   edm::Handle < EcalRecHitCollection > redEERecHits;
   try
   {
      iEvent.getByLabel(reducedBarrelEcalRecHitCollection_, redEBRecHits );
      reducedEBRecHits = redEBRecHits.product();
      iEvent.getByLabel(reducedEndcapEcalRecHitCollection_, redEERecHits ) ;
      reducedEERecHits = redEERecHits.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => reduced EcalRecHitCollections are missing #####" << endl;
         throw exception;
      }
      if(verbosity_>1) cout << endl << "   ===> No reduced EcalRecHitCollections, skip cluster rechits infos" << endl;
      doRecHits_ = false;
   }
   
   unsigned int nBasicClusters=0;
   
   edm::Handle<reco::BasicClusterCollection> basicClustersHandle;
   const reco::BasicClusterCollection *basicClusters = 0;
   try
   {
      iEvent.getByLabel(basicClusterProducer, basicClustersHandle);
      nBasicClusters = basicClustersHandle->size();
      basicClusters = basicClustersHandle.product();
   }
   catch (cms::Exception& exception)
   {
      if ( !allowMissingCollection_ )
      {
         if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => reco::BasicCluster collection is missing for Producer: " << basicClusterProducer << " #####" << endl;
         throw exception;
      }
      if(verbosity_>1) cout << endl << "   ===> No reco::BasicCluster collection for Producer: " << basicClusterProducer << " , skip basic clusters info" << endl;
      return false;
   }
   
   edm::ESHandle<EcalSeverityLevelAlgo> severityLevelAlgo;
   if (doRecHits_) iSetup.get<EcalSeverityLevelAlgoRcd>().get(severityLevelAlgo);
   
   // get the channel status from the DB
   //edm::ESHandle<EcalChannelStatus> chStatus;
   //iSetup.get<EcalChannelStatusRcd>().get(chStatus);
   //const EcalChannelStatus* channelStatus = 0;
   //if( chStatus.isValid() ) channelStatus = chStatus.product();
   
   if(verbosity_>1) cout << endl << "   Producer: " << basicClusterProducer << " - Number of BasicClusters (type " << clusterType << ") = " << nBasicClusters << std::endl;
   
   Int_t iClusType=0;
   
   edm::ESHandle<EcalClusterCrackCorrParameters> theParams;
   iSetup.get<EcalClusterCrackCorrParametersRcd>().get(theParams);
   const EcalClusterCrackCorrParameters *myParams = theParams.product();
   
   for( reco::BasicClusterCollection::const_iterator  aClus = basicClusters->begin(); aClus != basicClusters->end(); aClus++)
   {
      TRootCluster localClus( aClus->energy(), aClus->eta(), aClus->phi(), aClus->x(), aClus->y(), aClus->z(), clusterType);
      localClus.setTime( lazyTools->BasicClusterTime(*aClus, iEvent) );
      localClus.setE2x2( lazyTools->e2x2(*aClus) );
      localClus.setE3x3( lazyTools->e3x3(*aClus) );
      localClus.setE5x5( lazyTools->e5x5(*aClus) );
      localClus.setEmax( lazyTools->eMax(*aClus) );
      localClus.setE2nd( lazyTools->e2nd(*aClus) );
      localClus.setS4( lazyTools->eLeft(*aClus) + lazyTools->eRight(*aClus) + lazyTools->eTop(*aClus) + lazyTools->eBottom(*aClus) );
      localClus.setNxtals( (aClus->hitsAndFractions()).size() );
      if ( (aClus->hitsAndFractions()).size()>0 ) localClus.setUid( (aClus->hitsAndFractions()).at(0).first() );
      
      
      if(doCracksCorrection_)
      {
         
         //correction factor to be returned, and to be calculated in this present function:
         Double_t correction_factor=1.;
         Double_t fetacor=1.; //eta dependent part of the correction factor
         Double_t fphicor=1.; //phi dependent part of the correction factor
         
         
         
         //These ECAL barrel module and supermodule border corrections correct a photon energy for leakage outside a 5x5 crystal cluster. They  depend on the local position in the hit crystal. The hit crystal needs to be at the border of a barrel module. The local position coordinates, called later EtaCry and PhiCry in the code, are comprised between -0.5 and 0.5 and correspond to the distance between the photon supercluster position and the center of the hit crystal, expressed in number of  crystal widthes. The correction parameters (that should be filled in CalibCalorimetry/EcalTrivialCondModules/python/EcalTrivialCondRetriever_cfi.py) were calculated using simulaion and thus take into account the effect of the magnetic field. They  only apply to unconverted photons in the barrel, but a use for non brem electrons could be considered (not tested yet). For more details, cf the CMS internal note 2009-013 by S. Tourneur and C. Seez
         
         //Beware: The user should make sure it only uses this correction factor for unconverted photons (or not breming electrons)
         
         //const reco::CaloClusterPtr & seedbclus =  superCluster.seed();
         
         //If not barrel, return 1:
         //cout<<"TMath::Abs(aClus->eta()) = "<<TMath::Abs(aClus->eta())<<endl;
         if (TMath::Abs(aClus->eta()) >1.4442 ) 
         {
            correction_factor = 1.0;
            fetacor = 1.0;
            fphicor=1.0;
         }
         else{
            
            edm::ESHandle<CaloGeometry> pG;
            iSetup.get<CaloGeometryRecord>().get(pG); 
            
            
            const CaloSubdetectorGeometry* geom=pG->getSubdetectorGeometry(DetId::Ecal,EcalBarrel);//EcalBarrel = 1
            
            const math::XYZPoint position_ = aClus->position(); 
            double Theta = -position_.theta()+0.5*TMath::Pi();
            double Eta = position_.eta();
            double Phi = TVector2::Phi_mpi_pi(position_.phi());
            
            //Calculate expected depth of the maximum shower from energy (like in PositionCalc::Calculate_Location()):
            // The parameters X0 and T0 are hardcoded here because these values were used to calculate the corrections:
            const float X0 = 0.89; const float T0 = 7.4;
            double depth = X0 * (T0 + log(aClus->energy()));
            
            
            //search which crystal is closest to the cluster position and call it crystalseed:
            //std::vector<DetId> crystals_vector = aClus->getHitsByDetId();   //deprecated
            std::vector< std::pair<DetId, float> > crystals_vector = aClus->hitsAndFractions();
            float dphimin=999.;
            float detamin=999.;
            int ietaclosest = 0;
            int iphiclosest = 0;
            for (unsigned int icry=0; icry!=crystals_vector.size(); ++icry) {    
               EBDetId crystal(crystals_vector[icry].first);
               const CaloCellGeometry* cell=geom->getGeometry(crystal);
               GlobalPoint center_pos = (dynamic_cast<const TruncatedPyramid*>(cell))->getPosition(depth);
               double EtaCentr = center_pos.eta();
               double PhiCentr = TVector2::Phi_mpi_pi(center_pos.phi());
               if (TMath::Abs(EtaCentr-Eta) < detamin) {
                  detamin = TMath::Abs(EtaCentr-Eta); 
                  ietaclosest = crystal.ieta();
               }
               if (TMath::Abs(TVector2::Phi_mpi_pi(PhiCentr-Phi)) < dphimin) {
                  dphimin = TMath::Abs(TVector2::Phi_mpi_pi(PhiCentr-Phi)); 
                  iphiclosest = crystal.iphi();
               }
            }
            EBDetId crystalseed(ietaclosest, iphiclosest);
            
            // Get center cell position from shower depth
            const CaloCellGeometry* cell=geom->getGeometry(crystalseed);
            GlobalPoint center_pos = (dynamic_cast<const TruncatedPyramid*>(cell))->getPosition(depth);
            
            //if the seed crystal isn't neighbourgh of a supermodule border, don't apply the phi dependent crack corrections, but use the smaller phi dependent local containment correction instead.
            if (ietaclosest<0) iphiclosest = 361 - iphiclosest; //inversion of phi 3 degree tilt 
         int iphimod20 = iphiclosest%20;
         if ( iphimod20 >1 ) fphicor=1.;
         
         else{
            double PhiCentr = TVector2::Phi_mpi_pi(center_pos.phi());
            double PhiWidth = (TMath::Pi()/180.);
            double PhiCry = (TVector2::Phi_mpi_pi(Phi-PhiCentr))/PhiWidth;
            if (PhiCry>0.5) PhiCry=0.5;
            if (PhiCry<-0.5) PhiCry=-0.5;
            //flip to take into account ECAL barrel symmetries:
            if (ietaclosest<0) PhiCry *= -1.;
            
            //Fetching parameters of the polynomial (see  CMS IN-2009/013)
            double g[5];
            int offset = iphimod20==0 ? 
            10 //coefficients for one phi side of a SM
            : 15; //coefficients for the other side
            for (int k=0; k!=5; ++k) g[k] = (myParams->params())[k+offset];
            
            fphicor=0.;
            for (int k=0; k!=5; ++k) fphicor += g[k]*std::pow(PhiCry,k);
         }
         
         //if the seed crystal isn't neighbourgh of a module border, don't apply the eta dependent crack corrections, but use the smaller eta dependent local containment correction instead.
         int ietamod20 = ietaclosest%20;
         if (TMath::Abs(ietaclosest) <25 || (TMath::Abs(ietamod20)!=5 && TMath::Abs(ietamod20)!=6) ) fetacor = 1.;
         
         else
         {
            double ThetaCentr = -center_pos.theta()+0.5*TMath::Pi();
            double ThetaWidth = (TMath::Pi()/180.)*TMath::Cos(ThetaCentr);
            double EtaCry = (Theta-ThetaCentr)/ThetaWidth;    
            if (EtaCry>0.5) EtaCry=0.5;
            if (EtaCry<-0.5) EtaCry=-0.5;
            //flip to take into account ECAL barrel symmetries:
            if (ietaclosest<0) EtaCry *= -1.;
            
            //Fetching parameters of the polynomial (see  CMS IN-2009/013)
            double f[5];
            int offset = TMath::Abs(ietamod20)==5 ? 
            0 //coefficients for eta side of an intermodule gap closer to the interaction point
            : 5; //coefficients for the other eta side
            for (int k=0; k!=5; ++k) f[k] = (myParams->params())[k+offset];
            
            fetacor=0.;
            for (int k=0; k!=5; ++k) fetacor += f[k]*std::pow(EtaCry,k); 
         }
         
         correction_factor = 1./(fetacor*fphicor);
         }
         localClus.setcrackCorrectionEta(1./fetacor);
         localClus.setcrackCorrectionPhi(1./fphicor);
         localClus.setcrackCorrectionEtaPhi(correction_factor);
         
      }
      
      
      if (doRecHits_)
      {
         
         std::vector<TRootEcalRecHit> hits;
         
         for(std::vector<std::pair<DetId,float> >::const_iterator detIdPair = (aClus->hitsAndFractions()).begin(); detIdPair != (aClus->hitsAndFractions()).end(); ++detIdPair)
         {
            DetId detId = detIdPair->first;
            if (detId.det() != DetId::Ecal)
            {
               if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => DetId=" << detId.det() << " is not ECAL #####" << endl;
               continue;
            }
            
            if (detId.subdetId() == EcalBarrel)
            {
               EcalRecHitCollection::const_iterator hit = reducedEBRecHits->find(detId);
               if (hit == reducedEBRecHits->end()) continue;
               EBDetId ebDet = (EBDetId)(detId);
               
               int iflag;
               for (iflag=EcalRecHit::kUnknown; ; --iflag)
               {
                  if ((*hit).checkFlag(iflag)) break;
                  if (iflag==0) break;
               }
               
               TRootEcalRecHit localHit(
                  detId.subdetId()
                  ,iflag
                  ,(*hit).energy()
                  ,(*hit).time()
                  ,ebDet.ieta()
                  ,ebDet.iphi()
                  ,0
                  ,ebDet.ism()
                  ,ebDet.ic()
                  ,0
                  ,ebDet.hashedIndex()
                  ,(*hit).chi2()
                  ,(*hit).outOfTimeEnergy()
                  ,(*hit).outOfTimeChi2()
                  ,severityLevelAlgo->severityLevel(detId, *reducedEBRecHits)
               );
               hits.push_back(localHit);
            }
            else if (detId.subdetId() == EcalEndcap)
            {
               EcalRecHitCollection::const_iterator hit = reducedEERecHits->find(detId);
               if (hit == reducedEERecHits->end()) continue;
               EEDetId eeDet = (EEDetId)(detId);
               
               int iflag;
               for (iflag=EcalRecHit::kUnknown; ; --iflag)
               {
                  if ((*hit).checkFlag(iflag)) break;
                  if (iflag==0) break;
               }
               
               TRootEcalRecHit localHit(
                  detId.subdetId()
                  ,iflag
                  ,(*hit).energy()
                  ,(*hit).time()
                  ,eeDet.ix()
                  ,eeDet.iy()
                  ,eeDet.zside()
                  ,eeDet.isc()
                  ,eeDet.ic()
                  ,eeDet.iquadrant()
                  ,eeDet.hashedIndex()
                  ,(*hit).chi2()
                  ,(*hit).outOfTimeEnergy()
                  ,(*hit).outOfTimeChi2()
                  ,severityLevelAlgo->severityLevel(detId, *reducedEERecHits)
               );
               hits.push_back(localHit);
            }
            else
            {
               if(verbosity_>1) cout << endl << "  ##### ERROR IN  ClusterAnalyzer::process => SubDetId=" << detId.subdetId() << " is not EcalBarrel or EcalEndcap #####" << endl;
               continue;
            }
         }
         
         // FIXME - Implement ordering method in TRootEcalRecHit.h
         //std::sort(hits.begin(), hits.end());
         std::sort(hits.begin(), hits.end(), decrease);
         // if keepClusterizedEcalRecHits_=false, then keep only rechit associated to seed crystal
         if (! keepClusterizedEcalRecHits_ ) hits.resize(1);
         localClus.setHits(hits);
      }
      
      new( (*rootClusters)[iClus_] ) TRootCluster(localClus);
      if(verbosity_>3) cout << "   ["<< setw(3) << iClus_ << "] " << localClus << endl;
      
      iClus_++;
      iClusType++;
   }
   rootEvent->setNBasicClusters(clusterType,iClusType);
   return true;
}
