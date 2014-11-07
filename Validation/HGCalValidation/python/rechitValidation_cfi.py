import FWCore.ParameterSet.Config as cms

hgcalRecHitValidationEE = cms.EDAnalyzer('HGCalRecHitValidation',
                                         DetectorName = cms.string("HGCalEESensitive"),
                                         RecHitSource = cms.string("HGCEERecHits"),
                                         Verbosity     = cms.untracked.int32(0)
                                         )
