CC=g++
CFLAGS= -Wall -std=gnu99 -g -fopenmp
LIBS=src/matrix.c
TUNE= -O2

all: gen mpi

gen:
		g++ $(TUNE) -o bin/gen src/gen.cpp

mpi:
		mpicc $(TUNE) $(CFLAGS) -o bin/matrixPar $(LIBS) src/matrixPar.c
