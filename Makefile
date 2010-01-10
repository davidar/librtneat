CXX := c++
CFLAGS := -O3 -g -Wall

OBJS := \
    neat.o \
    network.o \
    nnode.o \
    link.o \
    trait.o \
    gene.o \
    genome.o \
    innovation.o \
    organism.o \
    species.o \
    population.o

.PHONY: all clean

all: librtneat.a

librtneat.a: ${OBJS}
	ar rc $@ $^
	ranlib $@

.cpp.o:
	$(CXX) ${CFLAGS} -c $<

neat.o: neat.cpp neat.h
network.o: network.cpp network.h neat.h neat.o
nnode.o: nnode.cpp nnode.h
link.o: link.cpp link.h
trait.o: trait.cpp trait.h
gene.o: gene.cpp gene.h
genome.o: genome.cpp genome.h
innovation.o: innovation.cpp innovation.h
organism.o: organism.cpp organism.h
species.o: species.cpp species.h organism.h
population.o: population.cpp population.h organism.h
experiments.o: experiments.cpp experiments.h network.h species.h cartpole.h
neatmain.o: neatmain.cpp neatmain.h neat.h population.h

clean:
	rm -f ${OBJS} librtneat.a
