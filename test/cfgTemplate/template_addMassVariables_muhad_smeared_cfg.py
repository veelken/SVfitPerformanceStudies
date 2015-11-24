import FWCore.ParameterSet.Config as cms

import os

process = cms.PSet()

process.fwliteInput = cms.PSet(
    fileNames = cms.vstring('/afs/cern.ch/user/v/veelken/scratch0/SVfitMEM_with_vamp/CMSSW_7_4_6/src/TauAnalysis/SVfitPerformanceStudies/test/svFitStudyNtuple.root'),
    
    maxEvents = cms.int32(1000),

    skipEvents = cms.uint32(1000*JOB_ID),
    
    outputEvery = cms.uint32(1)
)

process.addMassVariables = cms.PSet(

    inputTreeName = cms.string('ntupleProducer/SVfitStudyNtupleProducer'),
    outputTreeName = cms.string('ntupleProducer/muhad_smeared/SVfitStudyNtupleProducer'),

    leg1BranchName = cms.string("genMuon1"),
    leg1minPt = cms.double(15.),
    leg1maxAbsEta = cms.double(2.5),

    leg2BranchName = cms.string("smearedHadTau1"),
    leg2minPt = cms.double(20.),
    leg2maxAbsEta = cms.double(2.5),

    metBranchName = cms.string("smearedMEt"),
  
    svFitMEM = cms.PSet(
        sqrtS = cms.double(8.e+3), # 8 TeV
        apply_xSection_times_AccCorr = cms.string("xSection"), # "none", "xSection" or "xSection_times_Acc"
        inputFileName_xSection_times_AccCorr = cms.string('TauAnalysis/SVfitMEM/data/svFitMEM_xSection_and_AccCorr_13TeV_fitted.root'),
        graphName_xSection = cms.string('graph_Xsection_woAcc_13TeV_lephad_vamp_fitted'),
        graphName_Acc = cms.string('graph_Acc_13TeV_lephad_vamp'),
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
    
    outputFileName = cms.string('svFitStudyNtuple_muhad_smeared_jobIdJOB_ID.root')
)
