import FWCore.ParameterSet.Config as cms

process = cms.Process("produceSVfitStudyNtuple")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.Geometry.GeometryDB_cff")
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
##process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = cms.string('MCRUN2_74_V9')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(                                
        '/store/user/veelken/CMSSW_7_4_x/skims/mssmHtautau3200_RECO_1_1_ONE.root'
    ),
    ##eventsToProcess = cms.untracked.VEventRange(
    ##    '1:8:1309'
    ##)      
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.ntupleProductionSequence = cms.Sequence()

#--------------------------------------------------------------------------------
# print-out of generator level information
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printGenParticleList = cms.EDAnalyzer("ParticleListDrawer",
    src = cms.InputTag('genParticles'),
    maxEventsToPrint = cms.untracked.int32(10)
)
process.ntupleProductionSequence += process.printGenParticleList

process.dumpGenTaus = cms.EDAnalyzer("DumpGenTaus",
    src = cms.InputTag('genParticles'),
    maxEventsToPrint = cms.untracked.int32(10)
)
process.ntupleProductionSequence += process.dumpGenTaus
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# produce collection of tauGenJets
process.genParticlesFromZorHiggsDecays = cms.EDProducer("GenParticlePruner",
    src = cms.InputTag('genParticles'),
    select = cms.vstring(
        "drop  *  ", # this is the default
        "keep++ pdgId = {Z0}",
        "keep++ pdgId = {A0}",
        "keep++ pdgId = {H0}",
        "keep++ pdgId = {h0}"
    )
)
process.ntupleProductionSequence += process.genParticlesFromZorHiggsDecays

process.load("PhysicsTools.JetMCAlgos.TauGenJets_cfi")
process.tauGenJets.GenParticles =  cms.InputTag('genParticlesFromZorHiggsDecays')
process.ntupleProductionSequence += process.tauGenJets

process.tauGenJetsWithNu = process.tauGenJets.clone(
    includeNeutrinos = cms.bool(True)
)
process.ntupleProductionSequence += process.tauGenJetsWithNu

process.load("PhysicsTools.JetMCAlgos.TauGenJetsDecayModeSelectorAllHadrons_cfi")
process.tauGenJetsSelectorAllHadrons.select = cms.vstring(
    "oneProng0Pi0", 
    "oneProng1Pi0", 
    "oneProng2Pi0", 
    "oneProngOther",
    "threeProng0Pi0", 
    "threeProng1Pi0", 
    "threeProngOther", 
    "rare"
)
process.ntupleProductionSequence += process.tauGenJetsSelectorAllHadrons

process.tauGenJetsSelectorAllHadronsWithNu = process.tauGenJetsSelectorAllHadrons.clone(
    src = cms.InputTag('tauGenJetsWithNu')
)
process.ntupleProductionSequence += process.tauGenJetsSelectorAllHadronsWithNu

process.tauGenJetsSelectorElectron = process.tauGenJetsSelectorAllHadrons.clone(
    select = cms.vstring('electron')
)
process.ntupleProductionSequence += process.tauGenJetsSelectorElectron

process.tauGenJetsSelectorElectronWithNu = process.tauGenJetsSelectorElectron.clone(
    src = cms.InputTag('tauGenJetsWithNu')
)
process.ntupleProductionSequence += process.tauGenJetsSelectorElectronWithNu

process.tauGenJetsSelectorMuon = process.tauGenJetsSelectorAllHadrons.clone(
    select = cms.vstring('muon')
)
process.ntupleProductionSequence += process.tauGenJetsSelectorMuon

process.tauGenJetsSelectorMuonWithNu = process.tauGenJetsSelectorMuon.clone(
    src = cms.InputTag('tauGenJetsWithNu')
)
process.ntupleProductionSequence += process.tauGenJetsSelectorMuonWithNu
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# produce genMET collection 
process.genMEtFromTauDecays = cms.EDProducer("GenMEtFromTauDecaysProducer",
    src = cms.InputTag('tauGenJetsWithNu'),
    verbosity = cms.int32(2)
)
process.ntupleProductionSequence += process.genMEtFromTauDecays
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# produce collections of smeared hadronic taus and smeared MET
process.smearedHadTaus = cms.EDProducer("SmearedGenHadTauProducer",
    src = cms.InputTag('tauGenJetsSelectorAllHadrons'),
    inputFileName = cms.string("TauAnalysis/SVfitPerformanceStudies/data/hadTauSmearingCDF_toyMC.root"),
    graphName = cms.string("rCDF")
)
process.ntupleProductionSequence += process.smearedHadTaus

process.smearedMEt = cms.EDProducer("SmearedMEtProducer",
    src = cms.InputTag('genMEtFromTauDecays'),
    sigmaX = cms.double(10.),
    sigmaY = cms.double(10.),
    verbosity = cms.int32(2)
)
process.ntupleProductionSequence += process.smearedMEt
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# produce Ntuple
process.ntupleProducer = cms.EDAnalyzer("SVfitStudyNtupleProducer",
    srcGenTauLeptons = cms.InputTag('tauGenJetsWithNu'),                                         
    srcGenElectrons = cms.InputTag('tauGenJetsSelectorElectron'),
    srcGenMuons = cms.InputTag('tauGenJetsSelectorMuon'),
    srcGenHadTaus = cms.InputTag('tauGenJetsSelectorAllHadrons'),
    srcGenMET = cms.InputTag('genMEtFromTauDecays'),

    srcSmearedHadTaus = cms.InputTag('smearedHadTaus'),
    srcSmearedMET = cms.InputTag('smearedMEt'),

    evtWeights = cms.PSet(),

    verbosity = cms.int32(2)
)
process.ntupleProductionSequence += process.ntupleProducer

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("svFitStudyNtuple.root")
)
#--------------------------------------------------------------------------------

process.p = cms.Path(process.ntupleProductionSequence)

##process.printEventContent = cms.EDAnalyzer("EventContentAnalyzer")
##process.printFirstEventContentPath = cms.Path( process.printEventContent)
##process.schedule = cms.Schedule(process.printFirstEventContentPath, process.p)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

##processDumpFile = open('produceSVfitStudyNtuple.dump', 'w')
##print >> processDumpFile, process.dumpPython()




