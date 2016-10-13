#!/usr/bin/env python
import os,re,sys
import commands
import subprocess
import fileinput
import math, time
import array

print 'START CREATING cfgs...'


channels = ["muhad","emu","hadhad"]
options  = ["gen","smeared"]

samples=["ZprimeTauTauM2500" 
         #"DYJetsToLLM50_ext"              #1
         #"VBFHToTauTauM125"             #2
         #"GluGluHToTauTauM125"        #3
         #"SUSYGluGluToHToTauTauM90",   #4
         #"SUSYGluGluToHToTauTauM200",  #5
         #"SUSYGluGluToHToTauTauM300",  #6
         #"SUSYGluGluToHToTauTauM500",  #7
         #"SUSYGluGluToHToTauTauM800",  #8
         #"SUSYGluGluToHToTauTauM1200", #9
         #"SUSYGluGluToHToTauTauM1800", #10
         #"SUSYGluGluToHToTauTauM2600"  #11
        ]

#event_selection = ["0Jets","1JetBoosted","1JetNotBoosted","2Jets"]
event_selection = ["inclusive"]
nsamples  = len(samples)
         
#os.system("mkdir -p submit_jobs")

for ich in channels:
   #os.system("mkdir -p submit_jobs/"+ich)
   print " CHANNEL ::: "+ich 
   for iopt in options:
      #os.system("mkdir -p submit_jobs/"+ich+"/"+iopt)
      print " OPTION ::: "+iopt
      for i in range(0,nsamples):

         #nsplit = vnsplit[i]

         os.system("mkdir -p submit_jobs/"+ich+"/"+iopt+"/"+samples[i])
         startdir = ich+"/"+iopt+"/"+samples[i] 
         nfiles = len(next(os.walk(startdir))[2]) #dir is your directory path as string
         print nfiles
         print " SAMPLE ::: "+samples[i]
         if(samples[i].find('Zprime')==-1):
            nfiles = nfiles/5
            for isel in event_selection:
               os.system("mkdir -p submit_jobs/"+ich+"/"+iopt+"/"+samples[i]+"/"+isel)
               for j in range(0,nfiles):
                  scriptToLaunch = open("submit_jobs/"+ich+"/"+iopt+"/"+samples[i]+"/"+isel+"/script_to_launch_"+isel+"_"+str(j)+".sh", 'w')
                  scriptToLaunch.write("#!/bin/bash\n\n")
                  scriptToLaunch.write("pwd\n")
                  scriptToLaunch.write("export SCRAM_ARCH=slc6_amd64_gcc493\n")
	          scriptToLaunch.write("export BUILD_ARCH=slc6_amd64_gcc493\n")
                  scriptToLaunch.write("export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch\n")
                  scriptToLaunch.write("source /home/lucia/setup_cms.sh\n")
                  scriptToLaunch.write("cd /home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/\n")
                  scriptToLaunch.write("pwd\n")
	          scriptToLaunch.write("cmsenv\n")
                  scriptToLaunch.write("cd -\n")
	          scriptToLaunch.write("pwd\n")
                  scriptToLaunch.write("mkdir -p /scratch/lucia/"+ich+"\n")
	          scriptToLaunch.write("mkdir -p /scratch/lucia/"+ich+"/"+iopt+"\n")
	          scriptToLaunch.write("mkdir -p /scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/"+isel+"\n")
                  scriptToLaunch.write("cp /home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/submitBatchJobs/"+ich+"/"+iopt+"/"+samples[i]+"/addMassVariables_"+isel+"_"+str(j)+"_cfg.py /scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/"+isel+"/.\n")
	          scriptToLaunch.write("cp /hdfs/local/lucia/files/"+samples[i]+".root /scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/"+isel+"/.\n")
                  scriptToLaunch.write("cd /scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/"+isel+"\n")
                  scriptToLaunch.write("ls -l\n")
                  scriptToLaunch.write("addMassVariables addMassVariables_"+isel+"_"+str(j)+"_cfg.py\n")
	          scriptToLaunch.write("ls -l\n")
                  scriptToLaunch.write("pwd\n")
                  scriptToLaunch.write("mv svFitStudyNtuple_"+ich+"_"+iopt+"_"+str(j)+".root /hdfs/local/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/"+isel+"/\n")
		  scriptToLaunch.write("mv *"+str(j)+".out /hdfs/local/lucia/logs_"+ich+"/"+iopt+"/"+samples[i]+"/"+isel+"\n")
		  scriptToLaunch.write("mv *"+str(j)+".err /hdfs/local/lucia/logs_"+ich+"/"+iopt+"/"+samples[i]+"/"+isel+"/\n")
         else:
            os.system("mkdir -p submit_jobs/"+ich+"/"+iopt+"/"+samples[i]+"/inclusive")
            for j in range(0,nfiles):
               scriptToLaunch = open("submit_jobs/"+ich+"/"+iopt+"/"+samples[i]+"/inclusive/script_to_launch_inclusive_"+str(j)+".sh", 'w')
               scriptToLaunch.write("#!/bin/bash\n\n")
               scriptToLaunch.write("pwd\n")
               scriptToLaunch.write("export SCRAM_ARCH=slc6_amd64_gcc493\n")
	       scriptToLaunch.write("export BUILD_ARCH=slc6_amd64_gcc493\n")
               scriptToLaunch.write("export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch\n")
               scriptToLaunch.write("source /home/lucia/setup_cms.sh\n")
               scriptToLaunch.write("cd /home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/\n")
               scriptToLaunch.write("pwd\n")
	       scriptToLaunch.write("cmsenv\n")
               scriptToLaunch.write("cd -\n")
	       scriptToLaunch.write("pwd\n")
               scriptToLaunch.write("mkdir -p /scratch/lucia/"+ich+"\n")
	       scriptToLaunch.write("mkdir -p /scratch/lucia/"+ich+"/"+iopt+"\n")
	       scriptToLaunch.write("mkdir -p /scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/inclusive\n")
               scriptToLaunch.write("cp /home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/submitBatchJobs/"+ich+"/"+iopt+"/"+samples[i]+"/addMassVariables_inclusive_"+str(j)+"_cfg.py /scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/inclusive/.\n")
	       scriptToLaunch.write("cp /hdfs/local/lucia/files/"+samples[i]+".root /scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/inclusive/.\n")
               scriptToLaunch.write("cd /scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/inclusive\n")
               scriptToLaunch.write("ls -l\n")
               scriptToLaunch.write("addMassVariables addMassVariables_inclusive_"+str(j)+"_cfg.py\n")
	       scriptToLaunch.write("ls -l\n")
               scriptToLaunch.write("pwd\n")
               scriptToLaunch.write("mv svFitStudyNtuple_"+ich+"_"+iopt+"_"+str(j)+".root /hdfs/local/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/inclusive/\n")
               scriptToLaunch.write("mv *"+str(j)+".out /hdfs/local/lucia/logs_"+ich+"/"+iopt+"/"+samples[i]+"/inclusive/\n")
               scriptToLaunch.write("mv *"+str(j)+".err /hdfs/local/lucia/logs_"+ich+"/"+iopt+"/"+samples[i]+"/inclusive/\n")
  

