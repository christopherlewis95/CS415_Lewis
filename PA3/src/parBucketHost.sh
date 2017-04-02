#!/bin/bash
#SBATCH -N1
#SBATCH -n8
#SBATCH --time=01:00:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
srun parBucket

