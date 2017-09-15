import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.hltHighLevel_cfi
hltHT425 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHT425.TriggerResultsTag = cms.InputTag( "TriggerResults", "", "HLT" )
hltHT425.HLTPaths = cms.vstring(
    "HLT_HT425_v*", 
)
hltHT425.throw = False
hltHT425.andOr = True

EXODisplacedJetSkimSequence = cms.Sequence(
    hltHT425
)
