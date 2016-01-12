#!/bin/bash

maxEvents=4
directories=(hadhad muhad emu)
genOptions=(gen smeared)
##pathToFiles=(/home/calpas/svfitMEM/CMSSW_7_4_15_patch1/src/TauAnalysis/SVfitPerformanceStudies/test/files)
pathToFiles=($CMSSW_BASE/src/TauAnalysis/SVfitPerformanceStudies/test/files)
files=(SUSYGluGluToHToTauTauM300
)
#files=(SUSYGluGluToHToTauTauM200
#       SUSYGluGluToHToTauTauM300
#       SUSYGluGluToHToTauTauM500
#       SUSYGluGluToHToTauTauM800
#       SUSYGluGluToHToTauTauM1200
#       SUSYGluGluToHToTauTauM1800
#       SUSYGluGluToHToTauTauM2600
#       GluGluHToTauTauM125
#       DYJetsToLLM50
#      ) 

# create a config file for each decay/sample/jobID for gen and smeared in separate directories
for dir in ${directories[*]}; do
  rm -rf $dir
  mkdir $dir
  for opt in ${genOptions[*]}; do
    mkdir $dir/$opt
    for file in ${files[*]}; do
      mkdir $dir/$opt/$file # the directory the retrived the jobs
      for job in {0..200}; do # number of batch job to send
        sed "s+PATH_TO_FILE+$pathToFiles+g;s+FILE+$file+g;s+MAX_EVENTS+$maxEvents+g;s+JOB_ID+$job+g" template_addMassVariables_${dir}_${opt}_cfg.py> ${dir}/${opt}/${file}/addMassVariables_${job}_cfg.py 
      done
    done  
  done  
done

