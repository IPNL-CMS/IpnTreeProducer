import FWCore.ParameterSet.Config as cms

process = cms.Process("TotoAna")

# Keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger = cms.Service("MessageLogger",
#  cout = cms.untracked.PSet(
#     default = cms.untracked.PSet(
#        limit = cms.untracked.int32(100)
#     ),
#     threshold = cms.untracked.string('INFO')
#   ),
#  destinations = cms.untracked.vstring('cout')
#)

process.options = cms.untracked.PSet(
wantSummary = cms.untracked.bool(True)
)

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

# Needed for GlobalPositionRcd
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = cms.string('FT_R_53_V6::All')
#process.GlobalTag.globaltag = cms.string('START53_V11::All')


# Global geometry
#process.load("Configuration.Geometry.GeometryAll_cff")
process.load("Configuration.Geometry.GeometryDB_cff")
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')

# Transient Track Builder
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

# Geometry needed for clustering and calo shapes variables
# process.load("RecoEcal.EgammaClusterProducers.geometryForClustering_cff")

# ES cluster for pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.preshowerClusterShape_cfi")

# pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.piZeroDiscriminators_cfi")

# RAW / DIGI / RECO Standard sequences
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.EventContent.EventContent_cff')


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

#process.maxLuminosityBlocks = cms.untracked.PSet(
#   input = cms.untracked.int32(2)
#)

process.source = cms.Source("PoolSource",

# AOD
#fileNames = cms.untracked.vstring('file:/tmp/lethuill/CMSSW_5_1_2_patch1__RECO_5_0_0_v1_DYToMuMu.root')
#fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/l/lethuill/data/AOD/CMSSW_5_1_2_patch1__RECO_5_0_0_v1_DYToMuMu.root')
# RECO
fileNames = cms.untracked.vstring('/store/relval/CMSSW_5_3_4_cand1/RelValH130GGgluonfusion/GEN-SIM-RECO/PU_START53_V10-v1/0003/0C17628B-41F7-E111-BFAB-003048D2BE12.root')
#fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/cms/store/relval/CMSSW_4_2_2/RelValH130GGgluonfusion/GEN-SIM-RECO/START42_V11-v1/0014/3603E96A-966D-E011-B380-003048678FFA.root')
#fileNames = cms.untracked.vstring('/store/data/Run2010B/Electron/RAW-RECO/v2/000/147/114/AAB9337B-0ED0-DF11-9B73-0030486790B0.root')
#fileNames = cms.untracked.vstring(
#'rfio:/castor/cern.ch/cms/store/data/Run2010A/EG/RECO/v4/000/144/114/C2497931-2CB4-DF11-A92C-003048F1183E.root'
#,'rfio:/castor/cern.ch/cms/store/data/Run2010A/EG/RECO/v4/000/143/192/40927555-35AB-DF11-B264-0030487C7E18.root'
#)
#,skipEvents=cms.untracked.uint32(26015)
#,firstRun = cms.untracked.uint32(144114),
#,firstLumi   = cms.untracked.uintt32(5),
#,firstEvent = cms.untracked.uint32(135841750)
#eventsToProcess = cms.untracked.VEventRange('144114:135841760-144114:135841771','143192:24655772,-143192:24655772,'),
)

process.totoana = cms.EDAnalyzer("TotoAnalyzer",
   myConfig = cms.PSet(

      # Data type of the PoolSource ( RECO / PAT )
      dataType = cms.untracked.string("RECO"),   # use reco::Objects
      #dataType = cms.untracked.string("PAT"),    # use pat::Objects

      # Verbosite
      #     0 = muet
      #     1 = No evts tous les 10 ou 100 evts
      #     2 = Indique fonctions executees et nb d'objets reconstruits
      #     3 = Liste objets de haut niveau (electrons, muons, photons...)
      #     4 = Liste tous les objets (haut niveau, clusters....)
      #     5 = Debug
      verbosity = cms.untracked.int32(3),

      # name of output root file
      RootFileName = cms.untracked.string('Test.root'),

      # DATASET Infos  (will be written in runTree for bookeeping)
      xsection = cms.untracked.double(0.674770994),
      description = cms.untracked.string('Le dataset pourri a Roberto'),

      # What is written to rootuple
      doLHCInfo = cms.untracked.bool(True),
      doL1 = cms.untracked.bool(True),
      doHLT = cms.untracked.bool(True),
      doHLTObject = cms.untracked.bool(False),
      doMC = cms.untracked.bool(True),
      doPDFInfo = cms.untracked.bool(True),
      doSignalMuMuGamma = cms.untracked.bool(False),  # not tested in 2.X.X or 3.X.X
      doSignalTopTop = cms.untracked.bool(False),
#     signalGenerator = cms.untracked.string('PYTHIA'),
#     signalGenerator = cms.untracked.string('COMPHEP'),
#     signalGenerator = cms.untracked.string('ALPGEN'),
      signalGenerator = cms.untracked.string('MADGRAPH'),
      doPhotonConversionMC = cms.untracked.bool(True),
      doElectronMCTruth = cms.untracked.bool(False),

      doPhotonMC = cms.untracked.bool(True),
      doElectronMC = cms.untracked.bool(True),
      doMuonMC = cms.untracked.bool(True),
      doTauMC = cms.untracked.bool(False),
      doOtherStablePartsMC = cms.untracked.bool(False),
      doJetMC = cms.untracked.bool(True),
      doMETMC = cms.untracked.bool(True),
      doUnstablePartsMC = cms.untracked.bool(True),

      doBeamSpot = cms.untracked.bool(True),
      doPrimaryVertex = cms.untracked.bool(True),
      doZeePrimaryVertex = cms.untracked.bool(False),
      doTrack = cms.untracked.bool(True),
      doJet = cms.untracked.bool(True),
      doMuon = cms.untracked.bool(True),
      doElectron = cms.untracked.bool(True),
      doTau = cms.untracked.bool(True),
      doPhoton = cms.untracked.bool(True),
      doPhotonEnergyRegression = cms.untracked.bool(True),
      photonEnergyRegressionFile = cms.untracked.string('/afs/cern.ch/user/b/bendavid/cmspublic/regweights52xV3/gbrv3ph_52x.root'),
      doCluster = cms.untracked.bool(True),
      doCracksCorrection = cms.untracked.bool(True),
      keepClusterizedEcalRecHits = cms.untracked.bool(True),
      keepAllEcalRecHits = cms.untracked.bool(False),
      doMET = cms.untracked.bool(True),
      doBardak = cms.untracked.bool(True),
      doRho = cms.untracked.bool(True),

      doPhotonVertexCorrection = cms.untracked.bool(False),
      doPhotonIsolation = cms.untracked.bool(True),
      doPhotonConversion = cms.untracked.bool(True),

      # Draw MC particle tree
      drawMCTree = cms.untracked.bool(False),
      mcTreePrintP4 = cms.untracked.bool(True),
      mcTreePrintPtEtaPhi = cms.untracked.bool(False),
      mcTreePrintVertex = cms.untracked.bool(False),
      mcTreePrintStatus = cms.untracked.bool(True),
      mcTreePrintIndex = cms.untracked.bool(True),
      mcTreeStatus = cms.untracked.vint32( 1,2,3 ),   # accepted status codes

      # MC particles acceptance cuts
      photonMC_etaMax = cms.double(3.0),
      photonMC_ptMin = cms.double(2.0),
      electronMC_etaMax = cms.double(3.0),
      electronMC_ptMin = cms.double(2.0),
      muonMC_etaMax = cms.double(3.0),
      muonMC_ptMin = cms.double(0.0),
      otherStablePartMC_etaMax = cms.double(3.0),
      otherStablePartMC_ptMin = cms.double(2.0),
      jetMC_etaMax = cms.double(10.0),
      jetMC_ptMin = cms.double(0.0),

      # Photon isolation
      basicClustersIsolation_BarrelSC_type = cms.int32(211),                  # Type of SuperClusters used for isolation in barrel (see TRootCluster.h for type definition)
      basicClustersIsolation_EndcapSC_type = cms.int32(322),                  # Type of SuperClusters used for isolation in endcap (see TRootCluster.h for type definition)
      basicClustersIsolation_BarrelBC_type = cms.int32(210),                  # Type of Basic Clusters used for isolation in barrel (see TRootCluster.h for type definition)
      basicClustersIsolation_EndcapBC_type = cms.int32(320),                  # Type of Basic Clusters used for isolation in endcap (see TRootCluster.h for type definition)
      basicClustersIsolation_DRmax = cms.double(0.3),                         # size of the DR cone around photon - Et of BC in this cone are added
      basicClustersIsolation_ClusterEt_threshold = cms.double(0.0),           # Et threshold for BC added in DR cone
      basicClustersDoubleConeIsolation_BarrelSC_type = cms.int32(211),        # Type of SuperClusters used for isolation in barrel (see TRootCluster.h for type definition)
      basicClustersDoubleConeIsolation_EndcapSC_type = cms.int32(322),        # Type of SuperClusters used for isolation in endcap (see TRootCluster.h for type definition)
      basicClustersDoubleConeIsolation_BarrelBC_type = cms.int32(210),        # Type of Clusters used for isolation in barrel (see TRootCluster.h for type definition)
      basicClustersDoubleConeIsolation_EndcapBC_type = cms.int32(320),        # Type of Clusters used for isolation in endcap (see TRootCluster.h for type definition)
      basicClustersDoubleConeIsolation_DRmin = cms.double(0.05),              # size of the inner DR cone around photon - BC in this cone are rejected
      basicClustersDoubleConeIsolation_DRmax = cms.double(0.3),               # size of the outer DR cone around photon - Et of BC with DRmin < DR < DRmax are added
      basicClustersDoubleConeIsolation_ClusterEt_threshold = cms.double(0.0), # Et threshold for BC added in DR cone
      hcalRecHitIsolation_DRmax = cms.double(0.3),                            # size of the DR cone around photon - Et of HCAL rechits in this cone are added
      hcalRecHitIsolation_HitEt_threshold = cms.double(0.0),                  # Et threshold for HCAL rechits in DR cone
      trackerIsolation_DRmax = cms.double(0.3),                               # size of the DR cone around photon - pt of tracks in this cone are added
      trackerIsolation_pt_threshold = cms.double(0.0),                        # pt threshold for tracks added in DR cone
      trackerIsolation_pixelLayers_threshold = cms.int32(0),                  # minimum number of pixel layers with measurement required for tracks to be added in DR cone isolation
      doNiceTracksIsolation = cms.untracked.bool(False),                      # Nice tracks need reco::TrackExtra (not available in AOD)   
      trackerNiceTracksIsolationLIP = cms.double(0.2),                        # longitudianal impact parameter of the track (value in RECO = 0.2)
      trackerNiceTracksIsolationD0 = cms.double(0.1),                         # cut on the transverse impact of the track
      trackerNiceTracksIsolationTrackThreshold = cms.double(0.0),             # cut on the transverse energy of the track
      trackerNiceTracksIsolationdROuterRadius = cms.double(0.4),
      trackerNiceTracksIsolationdRInnerRadius = cms.double(0.04),
      trackerNiceTracksIsolationTrackEtaSlice = cms.double(0.015),

      # Parametrization of the Primary Vertex re-Reconstruction (used for Zee events)
      verbose = cms.untracked.bool(False),
      algorithm = cms.string('AdaptiveVertexFitter'),
      useBeamConstraint = cms.bool(True),
      beamSpotLabel = cms.InputTag("offlineBeamSpot"),
      minNdof  = cms.double(2.0),
      TrackLabel = cms.InputTag("generalTracks"), # label of tracks to be used
      
      PVSelParameters = cms.PSet(
         maxDistanceToBeam = cms.double(2), ## (in cm) 200 / 500 microns if useBeamConstraint = true / false
         #minVertexFitProb = cms.double(0.01) ## 1% vertex fit probability
      ),

      TkFilterParameters = cms.PSet(
         maxNormalizedChi2 = cms.double(20.0),
         minSiliconLayersWithHits = cms.int32(5), # >= 5
         minPixelLayersWithHits = cms.int32(2),   # >= 2
         maxD0Significance = cms.double(100.0),     # keep most primary tracks
         minPt = cms.double(0.0),                 # better for softish events
         trackQuality = cms.string("any")
      ),

      # clustering
      TkClusParameters = cms.PSet(
         algorithm   = cms.string('gap'),
         TkGapClusParameters = cms.PSet(
            zSeparation = cms.double(0.2) ## 2 mm max separation betw. clusters
         )
      )
      
   ),

   producersNamesRECO = cms.PSet(
      dataType = cms.untracked.string("RECO"),
      allowMissingCollection = cms.untracked.bool(True),
      l1Producer = cms.InputTag("gtDigis"),
      hltProducer = cms.InputTag("TriggerResults","","HLT"),
      hltEvent = cms.InputTag("patTriggerEvent","","HLT"),
      genParticlesProducer = cms.InputTag("genParticles"),
      genJetsProducer = cms.InputTag("antikt5GenJets"),
      genMETsProducer = cms.InputTag("genMetTrue"),
      beamSpotProducer = cms.InputTag("offlineBeamSpot"),
      primaryVertexProducer = cms.InputTag("offlinePrimaryVerticesWithBS"),
      trackProducer = cms.InputTag("generalTracks"),
      jetProducer = cms.VInputTag(
         cms.InputTag("ak5CaloJets"),
         cms.InputTag("kt4PFJets")
         ),
      srcRho = cms.InputTag('kt6PFJets','rho'),
      muonProducer = cms.VInputTag(cms.InputTag("muons")),
      electronProducer = cms.VInputTag(cms.InputTag("gsfElectrons")),
      tauProducer = cms.VInputTag(),
      photonProducer = cms.VInputTag(cms.InputTag("photons")),
      basicClusterProducerIndex = cms.vint32(210, 320),
      basicClusterProducer = cms.VInputTag(
         cms.InputTag("hybridSuperClusters","hybridBarrelBasicClusters"),
         # in 5.X.X
         cms.InputTag("multi5x5SuperClusters", "multi5x5EndcapBasicClusters")
         # in 4.X.X
         #cms.InputTag("multi5x5BasicClusters", "multi5x5EndcapBasicClusters")
         ),
      # RECO SC Collections
      superClusterProducerIndex = cms.vint32(210, 211, 320, 323, 322),
      superClusterProducer = cms.VInputTag(
         cms.InputTag("hybridSuperClusters",""),
         cms.InputTag("correctedHybridSuperClusters",""),
         cms.InputTag("multi5x5SuperClusters","multi5x5EndcapSuperClusters"),
         cms.InputTag("multi5x5SuperClustersWithPreshower",""),
         cms.InputTag("correctedMulti5x5SuperClustersWithPreshower","")
      ),
      # AOD SC Collections
      #superClusterProducerIndex = cms.vint32(211, 322),
      #superClusterProducer = cms.VInputTag(
         #cms.InputTag("correctedHybridSuperClusters",""),
         #cms.InputTag("correctedMulti5x5SuperClustersWithPreshower","")
      #),
      metProducer = cms.VInputTag(cms.InputTag("met")),
      barrelEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
      endcapEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
      reducedBarrelEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
      reducedEndcapEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
      caloTowerCollection = cms.InputTag("towerMaker"),
      hbheRecHitProducer = cms.InputTag("hbhereco"),
      hoRecHitProducer = cms.InputTag("horeco"),
      hfRecHitProducer = cms.InputTag("hfreco"),
      electronProducerForZeeVertex = cms.InputTag("gsfElectrons"),
      HLTfilterToSave = cms.vstring("hltL1NonIsoHLTNonIsoDoublePhotonEt17HEFilter")
   ),

   producersNamesPAT = cms.PSet(
      dataType = cms.untracked.string("PAT"),
      allowMissingCollection = cms.untracked.bool(True),
      patEncapsulation = cms.untracked.bool(False),
      l1Producer = cms.InputTag("gtDigis"),
      hltProducer = cms.InputTag("TriggerResults","","HLT"),
      hltEvent = cms.InputTag("patTriggerEvent","","PAT"),
      genParticlesProducer = cms.InputTag("genParticles"),
      genJetsProducer = cms.InputTag("antikt5GenJets"),
      genMETsProducer = cms.InputTag("genMetTrue"),
      beamSpotProducer = cms.InputTag("offlineBeamSpot"),
      #primaryVertexProducer = cms.InputTag("offlinePrimaryVerticesWithBS"),
      primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
      trackProducer = cms.InputTag("generalTracks"),
      jetProducer = cms.VInputTag(cms.InputTag("cleanPatJets")),
      srcRho = cms.InputTag('kt6PFJets','rho'),
      muonProducer = cms.VInputTag(cms.InputTag("cleanPatMuons")),
      electronProducer = cms.VInputTag(cms.InputTag("cleanPatElectrons")),
      tauProducer = cms.VInputTag(cms.InputTag("cleanPatTaus")),
      photonProducer = cms.VInputTag(cms.InputTag("cleanPatPhotons")),
      metProducer = cms.VInputTag(cms.InputTag("patMETs")),
      barrelEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
      endcapEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
      reducedBarrelEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
      reducedEndcapEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
      caloTowerCollection = cms.InputTag("towerMaker"),
      hbheRecHitProducer = cms.InputTag("hbhereco"),
      hoRecHitProducer = cms.InputTag("horeco"),
      hfRecHitProducer = cms.InputTag("hfreco")
   )
 )


##process.hltHighLevel = cms.EDFilter("HLTHighLevel",
##    HLTPaths = cms.vstring('HLT2PhotonRelaxed'),
##    andOr = cms.bool(True),
##    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
##)

process.primaryVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

process.noscraping = cms.EDFilter("FilterOutScraping",
  applyfilter = cms.untracked.bool(True),
  debugOn = cms.untracked.bool(False),
  numtrack = cms.untracked.uint32(10),
  thresh = cms.untracked.double(0.25)
)

process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'

#Jet producer for rho calculation 
#process.load('RecoJets.JetProducers.kt4PFJets_cfi')
#process.kt6PFJets = process.kt4PFJets.clone( rParam = 0.6, doRhoFastjet = True )
#process.kt6PFJets.Rho_EtaMax = cms.double(2.5)


# TotoAna standalone
process.p = cms.Path(process.totoana)

# rho Pileup estimator + TotoAna
#process.p = cms.Path(process.kt6PFJets+process.totoana)

# Photon reReco + TotoAna
#process.load("photonReReco")
#process.p = cms.Path(process.photons*process.photonIDSequence*process.totoana)

# Pi0disc + TotoAna
#process.p = cms.Path(process.preshowerClusterShape*process.piZeroDiscriminators*process.totoana)

# PrimaryVertexFilter + noscraping + hltPhysicsDeclared + TotoAna
#process.p = cms.Path(process.primaryVertexFilter+process.noscraping+process.hltPhysicsDeclared+process.totoana)
