#!/bin/bash
#SBATCH -N1
#SBATCH -n4
#SBATCH --time=00:01:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
srun parMatrix 12



