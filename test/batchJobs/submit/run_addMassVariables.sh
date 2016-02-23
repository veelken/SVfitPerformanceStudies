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

#samples=(GluGluHToTauTauM125)

samples=(SUSYGluGluToHToTauTauM200
         SUSYGluGluToHToTauTauM300
         SUSYGluGluToHToTauTauM500
         SUSYGluGluToHToTauTauM800
         SUSYGluGluToHToTauTauM1200
         SUSYGluGluToHToTauTauM1800
         SUSYGluGluToHToTauTauM2600
         GluGluHToTauTauM125
         DYJetsToLLM50
        ) 

#rm -rf $pathToOutput
mkdir -p $pathToOutput/$dir

# run addMassVariables for each config file in an array batch style
for dir in ${directories[*]}; do
  rm -rf $pathToOutput/$dir
  mkdir -p $pathToOutput/$dir

  for opt in ${genOptions[*]}; do
    mkdir -p $pathToOutput/$dir/$opt

    for sample in ${samples[*]}; do
      workDir=$pathToOutput/$dir/$opt/$sample
      mkdir -p $workDir 
      script="scriptTemplate/addMassVariables_${dir}_${opt}_${sample}"

      if [ $sample = 'DYJetsToLLM50' ]; then
        sbatch --array=0-1000 --workdir=$workDir --job-name=${dir}_${opt}_${sample} ${script}.sh
      else
        sbatch --array=0-500 --workdir=$workDir --job-name=${dir}_${opt}_${sample} ${script}.sh
      fi

    done
  done
done

