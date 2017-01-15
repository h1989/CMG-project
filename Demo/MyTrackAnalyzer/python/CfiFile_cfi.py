import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('MyTrackAnalyzer'
     ,tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
)
