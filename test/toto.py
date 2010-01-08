import FWCore.ParameterSet.Config as cms

process = cms.Process("TotoAna")

# Keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.MessageLogger = cms.Service("MessageLogger",
#	cout = cms.untracked.PSet(
#		default = cms.untracked.PSet(
#			limit = cms.untracked.int32(100)
#		),
#		threshold = cms.untracked.string('INFO')
#   ),
#	destinations = cms.untracked.vstring('cout')
#)

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

# Needed for GlobalPositionRcd
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR09_P_V8::All'

# Global geometry
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')

# Transient Track Builder
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

# Geometry needed for clustering and calo shapes variables
# process.load("RecoEcal.EgammaClusterProducers.geometryForClustering_cff")

# ES cluster for pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.preshowerClusterShape_cfi")

# pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.piZeroDiscriminators_cfi")

# Needed to re-run Photon Id
process.load("RecoEgamma.PhotonIdentification.photonId_cff")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(3)
)


process.source = cms.Source("PoolSource",

# RECO
fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/cms/store/caf/user/meridian/MinimumBias/BeamCommissioning09_EGMSkim_v4/972c4a0f8dedfb0d9feb42e7e718d588/EGMFirstCollisionSkim_124027_15.root')
# fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_3_2_5__RelValZTT__GEN-SIM-RECO__STARTUP31X_V4-v1__0011__1820860F-828E-DE11-A33B-000423D99CEE.root')
#	fileNames = cms.untracked.vstring(
#   'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValH130GGgluonfusion__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__104E25AC-CC78-DE11-AE55-001D09F2447F.root'
#   ,'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValH130GGgluonfusion__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__748489A8-CC78-DE11-991C-000423D99896.root'
#   ,'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValH130GGgluonfusion__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__BA7034AD-CC78-DE11-96E0-001D09F251E0.root'
#   ,'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValH130GGgluonfusion__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__CEA857A2-CC78-DE11-8073-000423D98EA8.root'
#   ,'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValH130GGgluonfusion__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__FC6C2AF4-E278-DE11-B2D1-001D09F23A07.root'
#   )
#   fileNames = cms.untracked.vstring(
#   'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValZEE__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__30A1F4B9-DB78-DE11-8F74-001D09F253C0.root'
#   ,'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValZEE__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__56BA18F5-E278-DE11-8038-001D09F26509.root'
#   ,'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValZEE__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__A0CE6C32-DA78-DE11-96E3-001D09F2532F.root'
#   ,'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValZEE__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__DC0B8126-DB78-DE11-8962-001D09F25109.root'
#   ,'file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValZMM__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__360B09AE-CC78-DE11-8933-001D09F254CE.root'
#   )
#   fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValTTbar__GEN-SIM-RECO__STARTUP31X_V2-v1__0006__0CC00E3B-5A78-DE11-A2AB-000423D94A04.root')
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_3_1_2__RelValZMM__GEN-SIM-RECO__STARTUP31X_V2-v1__0007__360B09AE-CC78-DE11-8933-001D09F254CE.root')
#  fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_2_1__Summer08__H120_gg__GEN-SIM-RECO__IDEAL_V11_redigi_v2__0009__F8176F88-7124-DE11-BE7A-00151796C0E0.root')
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_2_1__QCDpt170__Summer08_IDEAL_V11_redigi_v1__GEN-SIM-RECO__0010115D-6FE7-DD11-AFDC-0019B9E7CD05.root')
#  fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_1_10__RelValH130GGgluonfusion__GEN-SIM-DIGI-RAW-HLTDEBUG-RECO__STARTUP_V7_v1__0001__00616C72-FA9A-DD11-A526-00304867902E.root')
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_1_8__Summer08__H120_gg__GEN-SIM-RECO__IDEAL_V9_v1__0000__FE60393A-76E6-DD11-BDF1-001D0964474D.root')
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_1_8__Summer08__H120_gg__GEN-SIM-RECO__IDEAL_V9_v1__0000__FAE31F8E-6CE6-DD11-A953-0015C5EC47A2.root')
# fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_1_7__RelValTTbar__GEN-SIM-RECO__IDEAL_V9_v2__0002__56B92AB9-8B7E-DD11-A821-000423D6AF24.root')
# AOD
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_1_7__Summer08__QCDDiJetPt380to470__AODSIM__IDEAL_V9_AODSIM_v1__0000__F630AA5F-EBA4-DD11-BABD-001D0967D71F.root')
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_1_7__Summer08__TTJets-madgraph__AODSIM__IDEAL_V9_AODSIM_v1__0004__000BCB88-49AF-DD11-A760-00E081791887.root')
# PAT + some RECO Collections
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_1_10__Summer08__TTJets-madgraph__IDEAL_V9__PATLayer1_OutputFromAOD_full_113.root')
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_2_3__PATLayer1_Output.fromRECOinputCSA08test2_full.root')
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_2_X__Farida__InclusiveMuPt15_IN2P3__PATL1_InclusiveMuPt15_Sum08_1.root')
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_2_X__Farida__Hgg__PATL1_test.root')
# Only PAT Collections
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_2_1_10__TQAFLayer1_Output.fromAOD2110_IDEAL_full_0__PATOnly.root')
# fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_3_2_2_PATONLY_PatLayer1_RelValTTbar_STARTUP31X_V2_GEN-SIM-RECO.root')
# fileNames = cms.untracked.vstring('file:/sps/cms/ytschudi/These/CMSSW_3_2_5/src/SUSY/PATTuple/test/PATFiles/PatLayer1_RelValTTbar_STARTUP31X_V2_GEN-SIM-RECO.root')
# Salvatore PAT tuple
#	fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_3_3_1_Salvatore_PATtuple_01.root')
# Salvatore Input RECO
# fileNames = cms.untracked.vstring('/store/mc/Summer09/TTbar/GEN-SIM-RECO/MC_31X_V3-v1/0025/48AC6C31-AA88-DE11-B02C-0030487C6F54.root')
# fileNames = cms.untracked.vstring('file:/sps/cms/morgan/data/CMSSW_3_1_2__TTbar__GEN-SIM-RECO__MC_31X_V3-v1__0025__48AC6C31-AA88-DE11-B02C-0030487C6F54.root')
)

process.analysis = cms.EDAnalyzer("TotoAnalyzer",
	myConfig = cms.PSet(

		# Data type of the PoolSource ( RECO / PAT )
		dataType = cms.untracked.string("RECO"),   # use reco::Objects
		#dataType = cms.untracked.string("PAT"),    # use pat::Objects

		# Verbosite
		# 		0 = muet
 		# 		1 = No evts tous les 10 ou 100 evts
		# 		2 = Indique fonctions executees et nb d'objets reconstruprocess.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
 		# 		3 = Liste objets de haut niveau (electrons, muons, photons...)
 		# 		4 = Liste tous les objets (haut niveau, clusters....)
		# 		5 = Debug
 		verbosity = cms.untracked.int32(4),

		# name of output root file
		RootFileName = cms.untracked.string('Test.root'),

		# DATASET Infos  (will be written in runTree for bookeeping)
		xsection = cms.untracked.double(0.674770994),
		description = cms.untracked.string('Le dataset pourri a Roberto'),

		# What is written to rootuple		    
		doL1 = cms.untracked.bool(True),
		doHLT = cms.untracked.bool(True),
		doMC = cms.untracked.bool(True),
		doPDFInfo = cms.untracked.bool(True),
		doSignalMuMuGamma = cms.untracked.bool(False),  # not tested in 2.X.X or 3.X.X
		doSignalTopTop = cms.untracked.bool(True),
#		signalGenerator = cms.untracked.string('PYTHIA'),
#		signalGenerator = cms.untracked.string('COMPHEP'),
#		signalGenerator = cms.untracked.string('ALPGEN'),
		signalGenerator = cms.untracked.string('MADGRAPH'),
		doPhotonConversionMC = cms.untracked.bool(True),

		doPhotonMC = cms.untracked.bool(True),
		doElectronMC = cms.untracked.bool(True),
		doMuonMC = cms.untracked.bool(True),
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
		doPhoton = cms.untracked.bool(True),
		doCluster = cms.untracked.bool(True),
		keepClusterizedEcalRecHits = cms.untracked.bool(True),
		doMET = cms.untracked.bool(True),
		doBardak = cms.untracked.bool(True),
		
		doPhotonVertexCorrection = cms.untracked.bool(False),
		doPhotonIsolation = cms.untracked.bool(True),
		doPhotonConversion = cms.untracked.bool(True),
		conversionLikelihoodWeightsFile = cms.untracked.string('RecoEgamma/EgammaTools/data/TMVAnalysis_Likelihood.weights.txt'),

		# Draw MC particle tree
		drawMCTree = cms.untracked.bool(False),
		mcTreePrintP4 = cms.untracked.bool(True),
		mcTreePrintPtEtaPhi = cms.untracked.bool(False),
		mcTreePrintVertex = cms.untracked.bool(False),
		mcTreePrintStatus = cms.untracked.bool(True),
		mcTreePrintIndex = cms.untracked.bool(True),
		mcTreeStatus = cms.untracked.vint32( 1,2,3 ),	# accepted status codes

		# MC particles acceptance cuts
		photonMC_etaMax = cms.double(3.0),
		photonMC_ptMin = cms.double(2.0),
		electronMC_etaMax = cms.double(3.0),
		electronMC_ptMin = cms.double(2.0),
		muonMC_etaMax = cms.double(3.0),
		muonMC_ptMin = cms.double(0.0),
		jetMC_etaMax = cms.double(10.0),
		jetMC_ptMin = cms.double(0.0),

		# Photon isolation
		basicClustersIsolation_BarrelBC_type = cms.int32(210),                  # Type of Clusters used for isolation in barrel (see TRootCluster.h for type definition)
		basicClustersIsolation_EndcapBC_type = cms.int32(320),                  # Type of Clusters used for isolation in endcap (see TRootCluster.h for type definition)
		basicClustersIsolation_DRmax = cms.double(0.3),                         # size of the DR cone around photon - Et of BC in this cone are added
		basicClustersIsolation_ClusterEt_threshold = cms.double(0.0),           # Et threshold for BC added in DR cone
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

		# Parametrization of the Primary Vertex re-Reconstruction (used for Zee events)
		verbose = cms.untracked.bool(False),
		algorithm = cms.string('AdaptiveVertexFitter'),
		useBeamConstraint = cms.bool(True),
		
		PVSelParameters = cms.PSet(
			maxDistanceToBeam = cms.double(0.05), ## 200 / 500 microns if useBeamConstraint = true / false
			minVertexFitProb = cms.double(0.01) ## 1% vertex fit probability
		),
			
		TkFilterParameters = cms.PSet(
			maxNormalizedChi2 = cms.double(5.0),
			minSiliconHits = cms.int32(7), ## hits > 7
			maxD0Significance = cms.double(10.0), ## keep most primary tracks
			minPt = cms.double(0.0), ## better for softish events
			minPixelHits = cms.int32(1) ## hits > 2
		),

		VtxFinderParameters = cms.PSet(
		ptCut = cms.double(0.0),
		vtxFitProbCut = cms.double(0.01), ## 1% vertex fit probability
		trackCompatibilityToSVcut = cms.double(0.01), ## 1%
		trackCompatibilityToPVcut = cms.double(0.05), ## 5%
		maxNbOfVertices = cms.int32(0) ## search all vertices in each cluster
		),

		TkClusParameters = cms.PSet(
			zSeparation = cms.double(0.1) ## 1 mm max separation betw. clusters
		),
		
   ),

	producersNamesRECO = cms.PSet(
		dataType = cms.untracked.string("RECO"),
		allowMissingCollection = cms.untracked.bool(True),
		l1Producer = cms.InputTag("gtDigis"),
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		genParticlesProducer = cms.InputTag("genParticles"),
		genJetsProducer = cms.InputTag("iterativeCone5GenJets"),
		genMETsProducer = cms.InputTag("genMetCalo"),
		#genMETsProducer = cms.InputTag("genMetTrue"),
		beamSpotProducer = cms.InputTag("offlineBeamSpot"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVerticesWithBS"),
		trackProducer = cms.InputTag("generalTracks"),
		jetProducer = cms.InputTag("ak5CaloJets"),
		muonProducer = cms.InputTag("muons"),
		electronProducer = cms.InputTag("gsfElectrons"),
		photonProducer = cms.InputTag("photons"),
		metProducer = cms.InputTag("met"),
		barrelEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
		endcapEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
		reducedBarrelEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
		reducedEndcapEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
		hbheRecHitProducer = cms.InputTag("hbhereco"),
		hoRecHitProducer = cms.InputTag("horeco"),
		hfRecHitProducer = cms.InputTag("hfreco")
	),

	producersNamesPAT = cms.PSet(
		dataType = cms.untracked.string("PAT"),
		allowMissingCollection = cms.untracked.bool(True),
		patEncapsulation = cms.untracked.bool(False),
		l1Producer = cms.InputTag("gtDigis"),
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		genParticlesProducer = cms.InputTag("genParticles"),
		genJetsProducer = cms.InputTag("iterativeCone5GenJets"),
		genMETsProducer = cms.InputTag("genMet"),
		beamSpotProducer = cms.InputTag("offlineBeamSpot"),
		#primaryVertexProducer = cms.InputTag("offlinePrimaryVerticesWithBS"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		trackProducer = cms.InputTag("generalTracks"),
		jetProducer = cms.InputTag("selectedLayer1Jets"),
		muonProducer = cms.InputTag("selectedLayer1Muons"),
		electronProducer = cms.InputTag("selectedLayer1Electrons"),
		photonProducer = cms.InputTag("selectedLayer1Photons"),
		metProducer = cms.InputTag("selectedLayer1METs"),
		barrelEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
		endcapEcalRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
		reducedBarrelEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
		reducedEndcapEcalRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
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

#process.p = cms.Path(process.preshowerClusterShape*process.piZeroDiscriminators*process.analysis)
#process.p = cms.Path(process.photonIDSequence*process.analysis)
process.p = cms.Path(process.analysis)

