MAINPROG=listMajor
DIR=${PWD}
ASST=$(notdir ${DIR})
CC=gcc
CXX=g++
##
# Adjust settings for different compilers
#
ifeq ($(OS),Windows_NT)
#
# Flags for Windows compilers
CPPFLAGS=-g -std=c++14 -MMD -pthread -D_GLIBCXX_DEBUG -Wall
LFLAGS=
RM=del /q
EXE=.exe
else
#
# Flags for Linux & MacOS
CPPFLAGS=-g -std=c++14 -MMD -pthread -D_GLIBCXX_DEBUG -Wall
LFLAGSx=-fuse-ld=gold -pthread
RM=/bin/rm -rf
EXE=
endif
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
CFLAGS=-g
TARGET=$(MAINPROG)$(EXE)
CPPS=$(wildcard *.cpp)
MAINCPPS=$(filter-out unittest.cpp test%.cpp, $(CPPS))
TESTCPPS=$(filter-out $(MAINPROG).cpp, $(CPPS))
 
LINK=g++ $(CPPFLAGS)
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


MAINOBJS=$(MAINCPPS:%.cpp=%.o)
TESTOBJS=$(TESTCPPS:%.cpp=%.o)
DEPENDENCIES = $(CPPS:%.cpp=%.d)



%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -o $@ -c $*.cpp

# 
# Targets:
# 

all: $(TARGET) unittest$(EXE) 

$(TARGET): $(MAINOBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $^ $(LFLAGS)



clean:
	-/bin/rm -rf *.d *.o $(TARGET) unittest$(EXE) docs

documentation:
	-mkdir docs
	doxygen Doxyfile


unittest$(EXE): $(TESTOBJS)
	$(LINK) $(FLAGS) -o $@ $^ $(LFLAGS)


make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@

include make.dep
