#!/usr/bin/env python
import os,re,sys
import commands
import subprocess
import fileinput
import math, time
import array

print 'START CREATING cfgs...'

channels        = ["emu","muhad","hadhad"]
options         = ["gen","smeared"]
event_selection = ["inclusive"]#,"0Jets","1JetBoosted","1JetNotBoosted","2Jets"]

samples=["ZprimeTauTauM2500"
         #"DYJetsToLLM50_ext"              #1
         #"VBFHToTauTauM125"            #2
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

################## N event EMU ##################
#nevents = [10000000,
#           1497868,                      #2
#           1498800                      #3
#         497150,                       #4
#         198194,                       #5
#         199657,                       #6
#         99551,                        #7
#         100000,                       #8  
#         100000,                       #9
#         99694,                        #10
#         99597                         #11
        #]

################## N event MUHAD ################
nevents=[149235 #zprime
         #4000000,                      #1 
         #260000                      #2
#         260000,                      #3
#         497150,                       #4
#         198194,                       #5
#         199657,                       #6
#         99551,                        #7
#         80000,                       #8  
#         80000,                       #9
#         80000,                        #10
#         80000                         #11
        ]
################## N event HADHAD ################
#nevents=[#50000000                      #1 
#         300000,                      #2
         #445000
#]                      #3
#         497150,                       #4
#         110000,                       #5
#         60000,                       #6
#         45000,                        #7
#         40000,                       #8  
#         40000,                       #9
#         40000,                        #10
#         40000                         #11
#        ]

#for emu still split VBF and GluGlu with 2500 events
vnsplit=[500]
#################################################



nsamples   = len(samples)
nchannels  = len(channels)
noptions   = len(options)

for ich in channels:
   print "channel %s " % ich
   for iopt in options:
      print "%s " % iopt
      for i in range(0,nsamples):   

         print "sample %s" % samples[i]
         cfgDir=ich+"/"+iopt+"/"+samples[i]
         #os.system("rm -rf "+cfgDir) 
         os.system("mkdir -p "+cfgDir) 
         
         nsplit = -999

	 nsplit = vnsplit[i]

         njobs = int(nevents[i]/nsplit) + 1
         for j in range(0,njobs):
            #if (samples[i]=="DYJetsToLLM50_ext" or samples[i]=="VBFHToTauTauM125" or samples[i]=="GluGluHToTauTauM125"):
            #   nselection = 5
            #else:
            nselection = 1
            for k in range(0,nselection):
               os.system("cp template_addMassVariables_"+ich+"_"+iopt+"_cfg.py "+ich+"/"+iopt+"/"+samples[i]+"/"+"addMassVariables_"+event_selection[k]+"_"+str(j)+"_cfg.py")
               with open(ich+"/"+iopt+"/"+samples[i]+"/"+"addMassVariables_"+event_selection[k]+"_"+str(j)+"_cfg.py",'r') as f:
                  text = f.read()
                  text = text.replace("FILE",samples[i])
                  text = text.replace("MAX_EVENTS",str(nsplit))
                  text = text.replace("JOB_ID",str(j))
                  text = text.replace("EVENT_SELECTION",event_selection[k])
               with open(ich+"/"+iopt+"/"+samples[i]+"/"+"addMassVariables_"+event_selection[k]+"_"+str(j)+"_cfg.py",'w') as f:
                  f.write(text)


