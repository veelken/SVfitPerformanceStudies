#!/bin/bash

# create cfg files
cd /home/lucia/SVfitPerformanceStudies/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/cfgTemplate
./makeCfg.sh

# make script for jobs
cd /home/lucia/SVfitPerformanceStudies/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/batchJobs/submit/scriptTemplate/ 
./makeScript.sh

# create out dir and send jobs
# better run separatly for DY and 125 because they are too big
cd /home/lucia/SVfitPerformanceStudies/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/batchJobs/submit/ 
./run_addMassVariables.sh

# once the jogs finish, add the root file
#cd /ntuples/
#./addRootFile.sh

