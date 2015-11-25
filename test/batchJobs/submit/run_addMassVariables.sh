#!/bin/bash

# monitor: squeue -u calpas
# cancel array: scancel array_jobId
# cancel all: scancel -u calpas

#SBATCH --mem 4000 # Memory request

#eval `scramv1 runtime -sh` 

directories=(hadhad muhad emu)
genOptions=(gen smeared)
pathToOutput=(/home/calpas/svfitMEM/CMSSW_7_4_15_patch1/src/TauAnalysis/SVfitPerformanceStudies/test/batchJobs/output)
pathToConfigFile=(/home/calpas/svfitMEM/CMSSW_7_4_15_patch1/src/TauAnalysis/SVfitPerformanceStudies/test/cfgTemplate)
samples=(SUSYGluGluToHToTauTauM300
)
#samples=(SUSYGluGluToHToTauTauM200
#       SUSYGluGluToHToTauTauM300
#       SUSYGluGluToHToTauTauM500
#       SUSYGluGluToHToTauTauM800
#       SUSYGluGluToHToTauTauM1200
#       SUSYGluGluToHToTauTauM1800
#       SUSYGluGluToHToTauTauM2600
#       GluGluHToTauTauM125
#       DYJetsToLLM50
#      ) 

# run addMassVariables for each config file in an array batch style
for dir in ${directories[*]}; do
  rm -rf $pathToOutput/$dir
  mkdir $pathToOutput/$dir

  for opt in ${genOptions[*]}; do
    mkdir $pathToOutput/$dir/$opt

    for sample in ${samples[*]}; do
      workDir=$pathToOutput/$dir/$opt/$sample
      mkdir $workDir 
      script="scriptTemplate/addMassVariables_${dir}_${opt}_${sample}"

      sbatch --array=0-2 --workdir=$workDir ${script}.sh

    done
  done
done

