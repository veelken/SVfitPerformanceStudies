import FWCore.ParameterSet.Config as cms

process = cms.Process("produceSVfitStudyNtuple")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.Geometry.GeometryDB_cff")
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
##process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = cms.string('MCRUN2_74_V9')

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring( 
         'file:/hdfs/cms/store/mc/RunIIFall15MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/BACD287C-77BA-E511-8AFF-0025905B85E8.root'  
        #'file:/hdfs/cms/store/mc/RunIIFall15MiniAODv2/SUSYGluGluToHToTauTau_M-1500_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/50000/2669A374-C2B8-E511-8FC7-0025907B4FB6.root'                             
        #'/store/user/veelken/CMSSW_7_4_x/skims/mssmHtautau3200_RECO_1_1_ONE.root'
    ),
    ##eventsToProcess = cms.untracked.VEventRange(
    ##    '1:8:1309'
    ##)      
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
)

process.ntupleProductionSequence = cms.Sequence()

#--------------------------------------------------------------------------------
# print-out of generator level information
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printGenParticleList = cms.EDAnalyzer("ParticleListDrawer",
    src = cms.InputTag('prunedGenParticles'),
    maxEventsToPrint = cms.untracked.int32(10)
)
##process.ntupleProductionSequence += process.printGenParticleList

##process.dumpGenTaus = cms.EDAnalyzer("DumpGenTaus",
##    src = cms.InputTag('genParticles'),
##    maxEventsToPrint = cms.untracked.int32(10)
##)
##process.ntupleProductionSequence += process.dumpGenTaus
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# produce collection of tauGenJets
process.genParticlesFromZorHiggsDecays = cms.EDProducer("GenParticlePruner",
    src = cms.InputTag('prunedGenParticles'),
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
# produce genMET and genHadronicRecoil collections
process.genMEtFromTauDecays = cms.EDProducer("GenMEtFromTauDecaysProducer",
    src = cms.InputTag('tauGenJetsWithNu'),
    verbosity = cms.int32(0)
)
process.ntupleProductionSequence += process.genMEtFromTauDecays

process.genHadRecoil = cms.EDProducer("GenHadRecoilProducer",
    srcGenParticles = cms.InputTag('prunedGenParticles'),
    srcGenElectrons = cms.InputTag('tauGenJetsSelectorElectron'),
    srcGenMuons = cms.InputTag('tauGenJetsSelectorMuon'),
    srcGenHadTaus = cms.InputTag('tauGenJetsSelectorAllHadrons'), 
    verbosity = cms.int32(0)
)
process.ntupleProductionSequence += process.genHadRecoil
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# produce collections of smeared hadronic taus, smeared MET and smeared hadronic recoil
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
    verbosity = cms.int32(0)
)
process.ntupleProductionSequence += process.smearedMEt

process.smearedHadRecoil = cms.EDProducer("SmearedHadRecoilProducer",
    src = cms.InputTag('genHadRecoil'),
    sigmaPx = cms.double(10.),
    sigmaPy = cms.double(10.),
    sigmaPz = cms.double(-1.),
    sigmaMass = cms.double(-1.),                                      
    verbosity = cms.int32(0)
)
process.ntupleProductionSequence += process.smearedHadRecoil
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# produce Ntuple
process.ntupleProducer = cms.EDAnalyzer("SVfitStudyNtupleProducer",
    srcGenTauLeptons = cms.InputTag('tauGenJetsWithNu'),                                         
    srcGenElectrons = cms.InputTag('tauGenJetsSelectorElectron'),
    srcGenMuons = cms.InputTag('tauGenJetsSelectorMuon'),
    srcGenHadTaus = cms.InputTag('tauGenJetsSelectorAllHadrons'),
    srcGenMET = cms.InputTag('genMEtFromTauDecays'),
    srcGenHadRecoil = cms.InputTag('genHadRecoil'),     
    srcGenParticles = cms.InputTag('prunedGenParticles'),
    srcGenJets = cms.InputTag('slimmedGenJets'),
    minJetPt = cms.double(20.),
    maxJetAbsEta = cms.double(5.),

    srcSmearedHadTaus = cms.InputTag('smearedHadTaus'),
    srcSmearedMET = cms.InputTag('smearedMEt'),
    srcSmearedHadRecoil = cms.InputTag('smearedHadRecoil'),                                    

    evtWeights = cms.PSet(),

    verbosity = cms.int32(0)
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




