#!/bin/bash
#SBATCH -N2
#SBATCH -n9
#SBATCH --time=00:40:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
srun seqMatrix 300



