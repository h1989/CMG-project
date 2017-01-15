import FWCore.ParameterSet.Config as cms
process = cms.Process("Demo")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring('file:recoTracks.root'))
process.demo = cms.EDAnalyzer("DemoTrackAnalyzer", tracks = cms.untracked.InputTag("generalTracks"))
process.p = cms.Path(process.demo)


