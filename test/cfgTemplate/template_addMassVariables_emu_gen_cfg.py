import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('PATH_TO_FILE/FILE.root'),
    maxEvents = cms.int32(MAX_EVENTS),
    skipEvents = cms.uint32(MAX_EVENTS*JOB_ID),
    outputEvery = cms.uint32(1)
)

process.addMassVariables = cms.PSet(

    inputTreeName = cms.string('ntupleProducer/SVfitStudyNtupleProducer'),
    outputTreeName = cms.string('ntupleProducer/emu_gen/SVfitStudyNtupleProducer'),

    leg1BranchName = cms.string("genElectron1"),
    leg1minPt = cms.double(10.),
    leg1maxAbsEta = cms.double(2.5),

    leg2BranchName = cms.string("genMuon1"),
    leg2minPt = cms.double(10.),
    leg2maxAbsEta = cms.double(2.5),

    metBranchName = cms.string("genMEt"),
  
    svFitMEM = cms.PSet(
        sqrtS = cms.double(13.e+3), # 13 TeV
        apply_xSection_times_AccCorr = cms.string("xSection"), # "none", "xSection" or "xSection_times_Acc"
        inputFileName_xSection_times_AccCorr = cms.string('TauAnalysis/SVfitMEM/data/svFitMEM_xSection_and_AccCorr_13TeV_fitted.root'),
        graphName_xSection = cms.string('graph_Xsection_woAcc_13TeV_leplep_vamp_fitted'),
        graphName_Acc = cms.string('graph_Acc_13TeV_leplep_vamp'),
        minAcc = cms.double(1.e-2),
        addLogM_powers = cms.vdouble(0., 5.),
        inputFileName_hadTauTF = cms.string('TauAnalysis/SVfitMEM/data/hadTauTF_toyMC.root'),
        graphName_hadTauTF = cms.string('fit'),
        intMode = cms.string('vamp'),
        maxObjFunctionCalls = cms.uint32(20000),
        verbosity = cms.int32(0)
    ),

    keepAllBranches = cms.bool(True),

    verbosity = cms.int32(1),
    
    outputFileName = cms.string('svFitStudyNtuple_emu_gen_JOB_ID.root')
)