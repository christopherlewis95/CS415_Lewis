#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=01:00:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
srun seqBucket

