import FWCore.ParameterSet.Config as cms


ZToMMGMuonsCountFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("muons"),
    minNumber = cms.uint32(2)
    )

ZToMMGLooseMuons = cms.EDFilter("MuonViewRefSelector",
    src = cms.InputTag("muons"),
    cut = cms.string("""
        pt > 10 &
        isGlobalMuon &
				isTrackerMuon &
        abs(innerTrack().dxy) < 2.0
        """),
    filter = cms.bool(True)
    )

ZToMMGLooseMuonsCountFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("ZToMMGLooseMuons"),
    minNumber = cms.uint32(2)
    )

ZToMMGTightMuons = ZToMMGLooseMuons.clone(
    src = "ZToMMGLooseMuons",
    cut = "pt > 20"
    )

ZToMMGTightMuonsCountFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("ZToMMGTightMuons"),
    minNumber = cms.uint32(1)
    )

ZToMMGDimuons = cms.EDProducer("CandViewShallowClonePtrCombiner",
    decay = cms.string("ZToMMGTightMuons ZToMMGLooseMuons"),
    checkCharge = cms.bool(False),
    cut = cms.string("30 < mass")
    )

ZToMMGDimuonsFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("ZToMMGDimuons"),
    minNumber = cms.uint32(1)
    )


ZToMMGMuonsFilterSequence = cms.Sequence(
    ZToMMGMuonsCountFilter
		*
		ZToMMGLooseMuons
		*
		ZToMMGLooseMuonsCountFilter
#    (ZToMMGLooseMuons + ZToMMGLooseMuonsCountFilter)
		*
    ZToMMGTightMuons
		*
		ZToMMGTightMuonsCountFilter
		*
		ZToMMGDimuons
		*
		ZToMMGDimuonsFilter
#    ZToMMGDimuons *
#    ZToMMGDimuonsFilter
    )

