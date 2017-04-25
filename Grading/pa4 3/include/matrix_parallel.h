#ifndef MATRIX_PARALLEL_H
#define MATRIX_PARALLEL_H

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mpi.h>

#include "cmath_extra.h"
#include "matrix.h"
#include "timer.h"

#define PROG_NAME "matrix_parallel"

bool is_perfect_square(int num);

#endif // MATRIX_SEQUENTIAL_H