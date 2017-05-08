#!/bin/bash
#SBATCH -N1
#SBATCH -n4
#SBATCH --time=00:30:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
srun parMatrix $1 >> 16CoresTimed.txt




