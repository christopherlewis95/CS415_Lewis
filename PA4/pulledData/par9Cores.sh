#!/bin/bash
#SBATCH -N2
#SBATCH -n9
#SBATCH --time=00:30:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
srun parMatrix $1 >> 9CoresTimed.txt




