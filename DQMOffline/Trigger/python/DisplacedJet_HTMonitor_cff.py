import FWCore.ParameterSet.Config as cms

from DQMOffline.Trigger.HTMonitor_cfi import hltHTmonitoring

hltHT_HT425_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT425_Prommonitoring.FolderName = cms.string('HLT/HT/HT_425/')
hltHT_HT425_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT425_v*")
hltHT_HT425_Prommonitoring.jetSelection_HT = cms.string("pt > 40 && eta <5.0")

hltHT_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring.FolderName = cms.string('HLT/HT/HLT_HT400_DisplacedDijet40_DisplacedTrack/')
hltHT_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT400_DisplacedDijet40_DisplacedTrack_v*")
hltHT_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring.jetSelection = cms.string("pt>40 && eta<2.0 && n90>=3 && emEnergyFraction>0.01 && emEnergyFraction<0.99")
hltHT_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring.jetSelection_HT  = cms.string("pt > 40 && eta < 5.0")


hltHT_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring.FolderName = cms.string('HLT/HT/HLT_HT430_DisplacedDijet40_DisplacedTrack/')
hltHT_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT430_DisplacedDijet40_DisplacedTrack_v*")
hltHT_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring.jetSelection = cms.string("pt>40 && eta<2.0 && n90>=3 && emEnergyFraction>0.01 && emEnergyFraction<0.99")
hltHT_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring.jetSelection_HT  = cms.string("pt > 40 && eta < 5.0")


hltHT_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring.FolderName = cms.string('HLT/HT/HLT_HT430_DisplacedDijet60_DisplacedTrack/')
hltHT_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT430_DisplacedDijet60_DisplacedTrack_v*")
hltHT_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring.jetSelection = cms.string("pt>60 && eta<2.0 && n90>=3 && emEnergyFraction>0.01 && emEnergyFraction<0.99")
hltHT_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring.jetSelection_HT  = cms.string("pt > 40 && eta < 5.0")


hltHT_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring.FolderName = cms.string('HLT/HT/HLT_HT430_DisplacedDijet80_DisplacedTrack/')
hltHT_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT430_DisplacedDijet80_DisplacedTrack_v*")
hltHT_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring.jetSelection = cms.string("pt>80 && eta<2.0 && n90>=3 && emEnergyFraction>0.01 && emEnergyFraction<0.99")
hltHT_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring.jetSelection_HT  = cms.string("pt > 40 && eta < 5.0")



hltHT_HT550_DisplacedDijet60_Inclusive_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT550_DisplacedDijet60_Inclusive_Prommonitoring.FolderName = cms.string('HLT/HT/HLT_HT550_DisplacedDijet60_Inclusive/')
hltHT_HT550_DisplacedDijet60_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT550_DisplacedDijet60_Inclusive_v*")
hltHT_HT550_DisplacedDijet60_Inclusive_Prommonitoring.jetSelection = cms.string("pt>60 && eta<2.0 && n90>=3 && emEnergyFraction>0.01 && emEnergyFraction<0.99")
hltHT_HT550_DisplacedDijet60_Inclusive_Prommonitoring.jetSelection_HT  = cms.string("pt > 40 && eta < 5.0")


hltHT_HT550_DisplacedDijet80_Inclusive_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT550_DisplacedDijet80_Inclusive_Prommonitoring.FolderName = cms.string('HLT/HT/HLT_HT550_DisplacedDijet80_Inclusive/')
hltHT_HT550_DisplacedDijet80_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT550_DisplacedDijet80_Inclusive_v*")
hltHT_HT550_DisplacedDijet80_Inclusive_Prommonitoring.jetSelection = cms.string("pt>80 && eta<2.0 && n90>=3 && emEnergyFraction>0.01 && emEnergyFraction<0.99")
hltHT_HT550_DisplacedDijet80_Inclusive_Prommonitoring.jetSelection_HT  = cms.string("pt > 40 && eta < 5.0")



hltHT_HT650_DisplacedDijet60_Inclusive_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT650_DisplacedDijet60_Inclusive_Prommonitoring.FolderName = cms.string('HLT/HT/HLT_HT650_DisplacedDijet60_Inclusive/')
hltHT_HT650_DisplacedDijet60_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT650_DisplacedDijet60_Inclusive_v*")
hltHT_HT650_DisplacedDijet60_Inclusive_Prommonitoring.jetSelection = cms.string("pt>60 && eta<2.0 && n90>=3 && emEnergyFraction>0.01 && emEnergyFraction<0.99")
hltHT_HT650_DisplacedDijet60_Inclusive_Prommonitoring.jetSelection_HT  = cms.string("pt > 40 && eta < 5.0")


hltHT_HT650_DisplacedDijet80_Inclusive_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT650_DisplacedDijet80_Inclusive_Prommonitoring.FolderName = cms.string('HLT/HT/HLT_HT650_DisplacedDijet80_Inclusive/')
hltHT_HT650_DisplacedDijet80_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT650_DisplacedDijet80_Inclusive_v*")
hltHT_HT650_DisplacedDijet80_Inclusive_Prommonitoring.jetSelection = cms.string("pt>80 && eta<2.0 && n90>=3 && emEnergyFraction>0.01 && emEnergyFraction<0.99")
hltHT_HT650_DisplacedDijet80_Inclusive_Prommonitoring.jetSelection_HT  = cms.string("pt > 40 && eta < 5.0")


hltHT_HT750_DisplacedDijet80_Inclusive_Prommonitoring = hltHTmonitoring.clone()
hltHT_HT750_DisplacedDijet80_Inclusive_Prommonitoring.FolderName = cms.string('HLT/HT/HLT_HT750_DisplacedDijet80_Inclusive/')
hltHT_HT750_DisplacedDijet80_Inclusive_Prommonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_HT750_DisplacedDijet80_Inclusive_v*")
hltHT_HT750_DisplacedDijet80_Inclusive_Prommonitoring.jetSelection = cms.string("pt>80 && eta<2.0 && n90>=3 && emEnergyFraction>0.01 && emEnergyFraction<0.99")
hltHT_HT750_DisplacedDijet80_Inclusive_Prommonitoring.jetSelection_HT  = cms.string("pt > 40 && eta < 5.0")

exoHLTDisplacedJetHTmonitoring = cms.Sequence(
 hltHT_HT425_Prommonitoring
+hltHT_HT400_DisplacedDijet40_DisplacedTrack_Prommonitoring
+hltHT_HT430_DisplacedDijet40_DisplacedTrack_Prommonitoring
+hltHT_HT430_DisplacedDijet60_DisplacedTrack_Prommonitoring
+hltHT_HT430_DisplacedDijet80_DisplacedTrack_Prommonitoring
+hltHT_HT550_DisplacedDijet60_Inclusive_Prommonitoring
+hltHT_HT550_DisplacedDijet80_Inclusive_Prommonitoring
+hltHT_HT650_DisplacedDijet60_Inclusive_Prommonitoring
+hltHT_HT650_DisplacedDijet80_Inclusive_Prommonitoring
+hltHT_HT750_DisplacedDijet80_Inclusive_Prommonitoring   
)
