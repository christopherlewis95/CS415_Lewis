#!/bin/bash

# running
echo "Running Parallel"
#SBATCH -N1
#SBATCH -n4
#SBATCH --time=00:15:00
#SBATCH --mail-user=ryanecheveria@gmail.com
#SBATCH --mail-type=ALL

srun parallelMatrix $1

