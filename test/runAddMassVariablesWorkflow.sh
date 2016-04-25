#!/bin/bash

# create cfg files
cd /home/calpas/svfitMEM/CMSSW_8_0_0/src/TauAnalysis/SVfitPerformanceStudies/test/cfgTemplate
./makeCfg.sh

# make script for jobs
cd /home/calpas/svfitMEM/CMSSW_8_0_0/src/TauAnalysis/SVfitPerformanceStudies/test/batchJobs/submit/scriptTemplate/
./makeScript.sh

# create out dir and send jobs
# better run separatly for DY and 125 because they are too big
cd /home/calpas/svfitMEM/CMSSW_8_0_0/src/TauAnalysis/SVfitPerformanceStudies/test/batchJobs/submit/
./run_addMassVariables.sh

# once the jogs finish, add the root file
./addRootFile.sh

