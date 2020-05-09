#Makefile for "Battle Ship" C++ application
#Created by Enrico Zammit Lonardelli 2/4/2020

CC      := g++
IDIR =../include
CCFLAGS :=-g -Wall -I$(IDIR) -std=c++17 -lstdc++fs
LDFLAGS :=
ODIR := ../build


TARGET:= battleship
TARGETS := $(patsubst %,$(ODIR)/%,$(TARGET))
OBJ    := battle.o board.o coordinates.o vessel.o player.o screen_manager.o notification_manager.o geometry.o game.o market_manager.o authentication.o highscore_manager.o human.o npc.o
OBJS := $(patsubst %,$(ODIR)/%,$(OBJ))
DEP   := board.h coordinates.h piece.h player.h screen_manager.h vessel.h notification_manager.h geometry.h game.h market_manager.h authentication.h highscore_manager.h human.h npc.h submarine.h destroyer.h raft.h cruiser.h carrier.h
DEPS := $(patsubst %,$(IDIR)/%,$(DEP))

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJS)

$(OBJS): $(ODIR)/%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGETS): % : $(OBJS)
	$(CC) -o $@ $(LIBS) $^ $(CCFLAGS) $(LDFLAGS)