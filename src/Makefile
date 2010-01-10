INCLUDE_DIR := ../include/NEAT
CXX := c++
CFLAGS := -O3 -g -Wall -I${INCLUDE_DIR}

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

all: ../librtneat.a

../librtneat.a: ${OBJS}
	ar rc $@ $^
	ranlib $@

.cpp.o:
	$(CXX) ${CFLAGS} -c $<

neat.o: ${INCLUDE_DIR}/neat.h
network.o: ${INCLUDE_DIR}/network.h ${INCLUDE_DIR}/neat.h
nnode.o: ${INCLUDE_DIR}/nnode.h
link.o: ${INCLUDE_DIR}/link.h
trait.o: ${INCLUDE_DIR}/trait.h
gene.o: ${INCLUDE_DIR}/gene.h
genome.o: ${INCLUDE_DIR}/genome.h
innovation.o: ${INCLUDE_DIR}/innovation.h
organism.o: ${INCLUDE_DIR}/organism.h
species.o: ${INCLUDE_DIR}/species.h ${INCLUDE_DIR}/organism.h
population.o: ${INCLUDE_DIR}/population.h ${INCLUDE_DIR}/organism.h

clean:
	rm -f ${OBJS} ../librtneat.a
