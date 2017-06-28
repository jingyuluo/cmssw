import FWCore.ParameterSet.Config as cms

from DQM.TrackingMonitorClient.TrackingEffFromHitPatternClientConfig_cff import trackingEffFromHitPattern

trackingEffFromHitPatternHLT = trackingEffFromHitPattern.clone()
trackingEffFromHitPatternHLT.subDirs = cms.untracked.vstring(
   "HLT/Tracking/pixelTracks/HitEffFromHitPattern*",
   "HLT/Tracking/iter0HP/HitEffFromHitPattern*",
   "HLT/Tracking/iter2Merged/HitEffFromHitPattern*"
)

# Sequence
trackingMonitorClientHLT = cms.Sequence(
    trackingEffFromHitPatternHLT
)


#iter4 Monitoring
trackingForIter4EffFromHitPatternHLT = trackingEffFromHitPattern.clone()
trackingForIter4EffFromHitPatternHLT.subDirs = cms.untracked.vstring(
   "HLT/Tracking/iter4Merged/HitEffFromHitPattern*"
) 

trackingIter4MonitorClientHLT = cms.Sequence(
    trackingForIter4EffFromHitPatternHLT
)

# EGM tracking
trackingForElectronsEffFromHitPatternHLT = trackingEffFromHitPattern.clone()
trackingForElectronsEffFromHitPatternHLT.subDirs = cms.untracked.vstring(
   "HLT/EG/Tracking/GSF/HitEffFromHitPattern*",
   "HLT/EG/Tracking/pixelTracks/HitEffFromHitPattern*",
   "HLT/EG/Tracking/iter0HP/HitEffFromHitPattern*",
   "HLT/EG/Tracking/iter2Merged/HitEffFromHitPattern*"
)

# Sequence
trackingForElectronsMonitorClientHLT = cms.Sequence(
    trackingForElectronsEffFromHitPatternHLT
)
