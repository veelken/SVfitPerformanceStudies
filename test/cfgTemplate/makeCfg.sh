#!/bin/bash

directories=(hadhad muhad emu)
genOptions=(gen smeared)
pathToFiles=(/hdfs/local/calpas/files)

files=(GluGluHToTauTauM125
       DYJetsToLLM50
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

maxEventsHight=3000
maxEventsLow=100

# create a config file for each decay/sample/jobID for gen and smeared in separate directories
for dir in ${directories[*]}; do
  for opt in ${genOptions[*]}; do
    for file in ${files[*]}; do
      myDir=$dir/$opt/$file
      rm -rf $myDir 
      mkdir -p $myDir 

      for job in {0..1000}; do 
        if [ $file = 'DYJetsToLLM50' ] || [ $file = 'GluGluHToTauTauM125' ]; then
          sed "s+PATH_TO_FILE+$pathToFiles+g;s+FILE+$file+g;s+MAX_EVENTS+$maxEventsHight+g;s+JOB_ID+$job+g" template_addMassVariables_${dir}_${opt}_cfg.py> ${dir}/${opt}/${file}/addMassVariables_${job}_cfg.py 
        else
          sed "s+PATH_TO_FILE+$pathToFiles+g;s+FILE+$file+g;s+MAX_EVENTS+$maxEventsLow+g;s+JOB_ID+$job+g" template_addMassVariables_${dir}_${opt}_cfg.py> ${dir}/${opt}/${file}/addMassVariables_${job}_cfg.py 
        fi
      done

    done  
  done  
done


