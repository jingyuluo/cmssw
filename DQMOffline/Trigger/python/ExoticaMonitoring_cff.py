import FWCore.ParameterSet.Config as cms

from DQMOffline.Trigger.METMonitor_cff import *
from DQMOffline.Trigger.NoBPTXMonitor_cff import *
from DQMOffline.Trigger.HTMonitor_cff import *
from DQMOffline.Trigger.DisplacedJet_Monitor_cff import *

exoticaMonitorHLT = cms.Sequence(
    exoHLTMETmonitoring
    + exoHLTNoBPTXmonitoring
    + exoHLTHTmonitoring
    + exoHLTDisplacedJetmonitoring
)
