#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstdlib>
#include <ctime>

#define MAX_SIZE 50

int* rng(int count);
int* rngs(int seed, int count);

#endif