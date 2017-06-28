import FWCore.ParameterSet.Config as cms

from DQMOffline.Trigger.JetMonitor_cfi import hltJetMETmonitoring



hltJet_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring = hltJetMETmonitoring.clone()
hltJet_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring.jetSrc = cms.InputTag("ak4CaloJets")
hltJet_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring.FolderName = cms.string('HLT/JetMET/HLT_CaloJet_HT400_DisplacedDijet40_DisplacedTrack/')
hltJet_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring.ptcut = cms.double(20)
hltJet_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring.histoPSet.jetPtThrPSet = cms.PSet(
    nbins = cms.int32(80),
    xmin  = cms.double(0),
    xmax  = cms.double(400),

)
hltJet_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT400_DisplacedDijet40_DisplacedTrack_v*")




hltJet_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring = hltJetMETmonitoring.clone()
hltJet_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring.jetSrc = cms.InputTag("ak4CaloJets")
hltJet_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring.FolderName = cms.string('HLT/JetMET/HLT_CaloJet_HT430_DisplacedDijet40_DisplacedTrack/')
hltJet_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring.ptcut = cms.double(20)
hltJet_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring.histoPSet.jetPtThrPSet = cms.PSet(
    nbins = cms.int32(80),
    xmin  = cms.double(0),
    xmax  = cms.double(400),

)
hltJet_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT430_DisplacedDijet40_DisplacedTrack_v*")




hltJet_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring = hltJetMETmonitoring.clone()
hltJet_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring.jetSrc = cms.InputTag("ak4CaloJets")
hltJet_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring.FolderName = cms.string('HLT/JetMET/HLT_CaloJet_HT430_DisplacedDijet60_DisplacedTrack/')
hltJet_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring.ptcut = cms.double(20)
hltJet_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring.histoPSet.jetPtThrPSet = cms.PSet(
    nbins = cms.int32(80),
    xmin  = cms.double(0),
    xmax  = cms.double(400),

)
hltJet_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT430_DisplacedDijet60_DisplacedTrack_v*")




hltJet_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring = hltJetMETmonitoring.clone()
hltJet_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring.jetSrc = cms.InputTag("ak4CaloJets")
hltJet_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring.FolderName = cms.string('HLT/JetMET/HLT_CaloJet_HT430_DisplacedDijet80_DisplacedTrack/')
hltJet_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring.ptcut = cms.double(20)
hltJet_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring.histoPSet.jetPtThrPSet = cms.PSet(
    nbins = cms.int32(80),
    xmin  = cms.double(0),
    xmax  = cms.double(400),

)
hltJet_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT430_DisplacedDijet80_DisplacedTrack_v*")




hltJet_HT550_DisplacedDijet60_Inclusive_Prommonitoring = hltJetMETmonitoring.clone()
hltJet_HT550_DisplacedDijet60_Inclusive_Prommonitoring.jetSrc = cms.InputTag("ak4CaloJets")
hltJet_HT550_DisplacedDijet60_Inclusive_Prommonitoring.FolderName = cms.string('HLT/JetMET/HLT_CaloJet_HT550_DisplacedDijet60_Inclusive/')
hltJet_HT550_DisplacedDijet60_Inclusive_Prommonitoring.ptcut = cms.double(20)
hltJet_HT550_DisplacedDijet60_Inclusive_Prommonitoring.histoPSet.jetPtThrPSet = cms.PSet(
    nbins = cms.int32(80),
    xmin  = cms.double(0),
    xmax  = cms.double(400),

)
hltJet_HT550_DisplacedDijet60_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT550_DisplacedDijet60_Inclusive_v*")




hltJet_HT550_DisplacedDijet80_Inclusive_Prommonitoring = hltJetMETmonitoring.clone()
hltJet_HT550_DisplacedDijet80_Inclusive_Prommonitoring.jetSrc = cms.InputTag("ak4CaloJets")
hltJet_HT550_DisplacedDijet80_Inclusive_Prommonitoring.FolderName = cms.string('HLT/JetMET/HLT_CaloJet_HT550_DisplacedDijet80_Inclusive/')
hltJet_HT550_DisplacedDijet80_Inclusive_Prommonitoring.ptcut = cms.double(20)
hltJet_HT550_DisplacedDijet80_Inclusive_Prommonitoring.histoPSet.jetPtThrPSet = cms.PSet(
    nbins = cms.int32(80),
    xmin  = cms.double(0),
    xmax  = cms.double(400),

)
hltJet_HT550_DisplacedDijet80_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT550_DisplacedDijet80_Inclusive_v*")




hltJet_HT650_DisplacedDijet60_Inclusive_Prommonitoring = hltJetMETmonitoring.clone()
hltJet_HT650_DisplacedDijet60_Inclusive_Prommonitoring.jetSrc = cms.InputTag("ak4CaloJets")
hltJet_HT650_DisplacedDijet60_Inclusive_Prommonitoring.FolderName = cms.string('HLT/JetMET/HLT_CaloJet_HT650_DisplacedDijet60_Inclusive/')
hltJet_HT650_DisplacedDijet60_Inclusive_Prommonitoring.ptcut = cms.double(20)
hltJet_HT650_DisplacedDijet60_Inclusive_Prommonitoring.histoPSet.jetPtThrPSet = cms.PSet(
    nbins = cms.int32(80),
    xmin  = cms.double(0),
    xmax  = cms.double(400),

)
hltJet_HT650_DisplacedDijet60_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT650_DisplacedDijet60_Inclusive_v*")




hltJet_HT650_DisplacedDijet80_Inclusive_Prommonitoring = hltJetMETmonitoring.clone()
hltJet_HT650_DisplacedDijet80_Inclusive_Prommonitoring.jetSrc = cms.InputTag("ak4CaloJets")
hltJet_HT650_DisplacedDijet80_Inclusive_Prommonitoring.FolderName = cms.string('HLT/JetMET/HLT_CaloJet_HT650_DisplacedDijet80_Inclusive/')
hltJet_HT650_DisplacedDijet80_Inclusive_Prommonitoring.ptcut = cms.double(20)
hltJet_HT650_DisplacedDijet80_Inclusive_Prommonitoring.histoPSet.jetPtThrPSet = cms.PSet(
    nbins = cms.int32(80),
    xmin  = cms.double(0),
    xmax  = cms.double(400),

)
hltJet_HT650_DisplacedDijet80_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT650_DisplacedDijet80_Inclusive_v*")




hltJet_HT750_DisplacedDijet80_Inclusive_Prommonitoring = hltJetMETmonitoring.clone()
hltJet_HT750_DisplacedDijet80_Inclusive_Prommonitoring.jetSrc = cms.InputTag("ak4CaloJets")
hltJet_HT750_DisplacedDijet80_Inclusive_Prommonitoring.FolderName = cms.string('HLT/JetMET/HLT_CaloJet_HT750_DisplacedDijet80_Inclusive/')
hltJet_HT750_DisplacedDijet80_Inclusive_Prommonitoring.ptcut = cms.double(20)
hltJet_HT750_DisplacedDijet80_Inclusive_Prommonitoring.histoPSet.jetPtThrPSet = cms.PSet(
    nbins = cms.int32(80),
    xmin  = cms.double(0),
    xmax  = cms.double(400),

)
hltJet_HT750_DisplacedDijet80_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT750_DisplacedDijet80_Inclusive_v*")

HLTDisplacedJetJetmonitoring = cms.Sequence(
  hltJet_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring
 +hltJet_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring
 +hltJet_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring
 +hltJet_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring
 +hltJet_HT550_DisplacedDijet60_Inclusive_Prommonitoring
 +hltJet_HT550_DisplacedDijet80_Inclusive_Prommonitoring
 +hltJet_HT650_DisplacedDijet60_Inclusive_Prommonitoring
 +hltJet_HT650_DisplacedDijet80_Inclusive_Prommonitoring
 +hltJet_HT750_DisplacedDijet80_Inclusive_Prommonitoring
)
