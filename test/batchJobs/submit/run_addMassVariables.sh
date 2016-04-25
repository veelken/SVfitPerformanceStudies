#!/bin/bash

# monitor: squeue -u calpas
# cancel array: scancel array_jobId
# cancel all: scancel -u calpas

#SBATCH --mem 4000 # Memory request

directories=(hadhad muhad emu)
genOptions=(gen smeared)
path=(/home/calpas/svfitMEM/CMSSW_8_0_0/src/TauAnalysis/SVfitPerformanceStudies/test/)
pathToOutput=(${path}batchJobs/output)
pathToConfigFile=(${path}cfgTemplate)

samples=(GluGluHToTauTauM125
         DYJetsToLLM50
        )

#samples=(SUSYGluGluToHToTauTauM200
#         SUSYGluGluToHToTauTauM300
#         SUSYGluGluToHToTauTauM500
#         SUSYGluGluToHToTauTauM800
#         SUSYGluGluToHToTauTauM1200
#         SUSYGluGluToHToTauTauM1800
#         SUSYGluGluToHToTauTauM2600
#         GluGluHToTauTauM125
#         DYJetsToLLM50
#        ) 


# run addMassVariables for each config file in an array batch style
for dir in ${directories[*]}; do
  for opt in ${genOptions[*]}; do
    for sample in ${samples[*]}; do
      workDir=$pathToOutput/$dir/$opt/$sample
      rm -rf $workDir
      mkdir -p $workDir 
      script="scriptTemplate/addMassVariables_${dir}_${opt}_${sample}"
      sbatch --array=0-1000 --workdir=$workDir --job-name=${dir}_${opt}_${sample} ${script}.sh
    done
  done
done

