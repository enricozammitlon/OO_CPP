#Makefile for "Battle Ship" C++ application
#Created by Enrico Zammit Lonardelli 2/4/2020

IDIR =../include
CXX=g++
CPPFLAGS=-I$(IDIR) -Wall -g
BUILD = ${BUILDPATH}
OBJS = battle.o board.o piece.o rules.o coordinates.o vessel.o player.o

battleship : $(OBJS)
	$(CXX) $(CPPFLAGS) -o battleship $(OBJS);mv -t $(BUILD) battleship $(OBJS)
battle.o :
	$(CXX) $(CPPFLAGS) -c battle.cpp
board.o : $(IDIR)/board.h
	$(CXX) $(CPPFLAGS) -c board.cpp
piece.o : $(IDIR)/piece.h
	$(CXX) $(CPPFLAGS) -c piece.cpp
rules.o : $(IDIR)/rules.h
	$(CXX) $(CPPFLAGS) -c rules.cpp
coordinates.o : $(IDIR)/coordinates.h
	$(CXX) $(CPPFLAGS) -c coordinates.cpp
vessel.o : $(IDIR)/vessel.h
	$(CXX) $(CPPFLAGS) -c vessel.cpp
player.o : $(IDIR)/player.h
	$(CXX) $(CPPFLAGS) -c player.cpp

clean:
	rm -f core battleship $(OBJS)