Target  = do.exe

Objects = SVfitMEM.o 

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)

#CXXLIBS    = -L$(CMSSW_RELEASE_BASE)/lib/$(SCRAM_ARCH) -lPhysicsToolsUtilities 
CXXFLAGS   = -std=c++0x -I$(CMSSW_RELEASE_BASE)/src/

all:$(Target)

do.exe: main.cc $(Objects)
	g++ -o $@ main.cc $(Objects) $(ROOTFLAGS) $(ROOTLIBS) $(CXXFLAGS) #$(CXXLIBS)

SVfitMEM.o: SVfitMEM.C SVfitMEM.h
	g++ -o $@ SVfitMEM.C -c $(ROOTFLAGS) $(CXXFLAGS)
        
clean:
	rm -f do.exe SVfitMEM.o

info:
	@echo SCRAM_ARCH = $(SCRAM_ARCH)
	@echo CMSSW_RELEASE_BASE = $(CMSSW_RELEASE_BASE)
