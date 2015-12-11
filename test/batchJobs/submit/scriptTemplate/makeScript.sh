#!/bin/bash

directories=(hadhad muhad emu)
genOptions=(gen smeared)
##pathToCfg=(/home/calpas/svfitMEM/CMSSW_7_4_15_patch1/src/TauAnalysis/SVfitPerformanceStudies/test/cfgTemplate)
pathToCfg=($CMSSW_BASE/src/TauAnalysis/SVfitPerformanceStudies/test/cfgTemplate)
files=(SUSYGluGluToHToTauTauM300)
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

# create a config files 
for dir in ${directories[*]}; do
  for opt in ${genOptions[*]}; do
    for file in ${files[*]}; do
      CfgPath=${pathToCfg}/${dir}/${opt}/${file}
      script="addMassVariables_${dir}_${opt}_${file}"
      sed "s+PATH_TO_CONFIGFILE+$CfgPath+g" template_addMassVariables.sh > $script.sh 
      chmod u+x $script.sh
    done  
  done  
done


