#!/bin/bash

srun -N1 -n1 bin/gen 1000 matA.txt
srun -N1 -n1 bin/gen 1000 matB.txt
#SBATCH -N 1
#SBATCH -n 4
#SBATCH --time=00:05:00

srun bin/matrixPar matA.txt matB.txt



