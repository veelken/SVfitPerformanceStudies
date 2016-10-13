#!/usr/bin/env python
import os,re,sys
import commands
import subprocess
import fileinput
import math, time
import array

print 'START CREATING cfgs...'
#*********************************************
#submitted all SUSY jobs for HadHad Gen
#*********************************************


#configuration to run again emu jobs to get the number for the table!!!

channels = ["emu"]
options  = ["smeared"]

samples=[#"ZprimeTauTauM2500"
         "DYJetsToLLM50_ext"             #1
         #"VBFHToTauTauM125"            #2
         #"GluGluHToTauTauM125"         #3
         #"SUSYGluGluToHToTauTauM90",    #4
         #"SUSYGluGluToHToTauTauM200",   #5
         #"SUSYGluGluToHToTauTauM300",   #6
         #"SUSYGluGluToHToTauTauM500",  #7
         #"SUSYGluGluToHToTauTauM800",  #8
         #"SUSYGluGluToHToTauTauM1200", #9
         #"SUSYGluGluToHToTauTauM1800", #10
         #"SUSYGluGluToHToTauTauM2600"  #11
        ]

event_selection = ["inclusive","0Jets","1JetBoosted","1JetNotBoosted","2Jets"]
maindir = "/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/submitBatchJobs/submit_jobs/"
nsamples  = len(samples)
for ich in channels:
   #os.system("mkdir -p /hdfs/local/lucia/logs_"+ich)
   for iopt in options:
      #os.system("mkdir -p /hdfs/local/lucia/logs_"+ich+"/"+iopt)
      for i in range(0,nsamples):
         #os.system("mkdir -p /hdfs/local/lucia/"+ich+"/"+iopt+"/"+samples[i])
         #os.system("mkdir -p /hdfs/local/lucia/logs_"+ich+"/"+iopt+"/"+samples[i])
         nsel = len(event_selection)
         for isel in range(0,nsel):
            #os.system("mkdir -p /hdfs/local/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/"+event_selection[isel])
            #os.system("mkdir -p /hdfs/local/lucia/logs_"+ich+"/"+iopt+"/"+samples[i]+"/"+event_selection[isel])
            startdir = maindir+ich+"/"+iopt+"/"+samples[i]+"/"+event_selection[isel]
            print startdir
            nfiles = 2402 #len(next(os.walk(startdir))[2]) #2402 is enough to process smth like 6 mio events
            for j in range(0,nfiles):
               os.chdir(startdir)
               os.system("sbatch --job-name="+ich+"_"+iopt+"_"+samples[i]+"_"+str(j)+" script_to_launch_"+event_selection[isel]+"_"+str(j)+".sh")
               #os.system("sbatch --job-name="+ich+"_"+iopt+"_"+samples[i]+"_"+str(j)+" --error=/scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/"+event_selection[isel]+"/job."+str(j)+".err --output=/scratch/lucia/"+ich+"/"+iopt+"/"+samples[i]+"/"+event_selection[isel]+"/job."+str(j)+".out script_to_launch_"+event_selection[isel]+"_"+str(j)+".sh")
               os.chdir("/home/lucia/SVfitPerformanceStudiesII/CMSSW_7_6_3/src/TauAnalysis/SVfitPerformanceStudies/test/submitBatchJobs")

#print "submitted %d jobs in total " %(count)
