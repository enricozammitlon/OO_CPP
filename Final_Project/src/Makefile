#Makefile for "Battle Ship" C++ application
#Created by Enrico Zammit Lonardelli 2/4/2020

CC      := g++
IDIR =../include
CCFLAGS :=-g -Wall -I$(IDIR)
LDFLAGS :=
ODIR := ../build


TARGET:= battleship
TARGETS := $(patsubst %,$(ODIR)/%,$(TARGET))
OBJ    := battle.o board.o piece.o rules.o coordinates.o vessel.o player.o screen_manager.o notification_manager.o geometry.o game.o market.o
OBJS := $(patsubst %,$(ODIR)/%,$(OBJ))
DEP   := board.h coordinates.h piece.h player.h rules.h screen_manager.h sloop.h vessel.h notification_manager.h geometry.h game.h market.h
DEPS := $(patsubst %,$(IDIR)/%,$(DEP))

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJS)

$(OBJS): $(ODIR)/%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGETS): % : $(OBJS)
	$(CC) -o $@ $(LIBS) $^ $(CCFLAGS) $(LDFLAGS)