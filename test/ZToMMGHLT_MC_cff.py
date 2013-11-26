import FWCore.ParameterSet.Config as cms

### HLT filter
import copy
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
ZToMMGHltFilter = copy.deepcopy(hltHighLevel)
ZToMMGHltFilter.throw = cms.bool(False)
ZToMMGHltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
ZToMMGHltFilter.HLTPaths = ["*Mu*"]

ZToMMGHLTFilterSequence = cms.Sequence(
    ZToMMGHltFilter
    )

