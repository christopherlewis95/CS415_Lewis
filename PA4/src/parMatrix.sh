#!/bin/bash
#SBATCH -N2
#SBATCH -n9
#SBATCH --time=00:01:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
srun parMatrix 300



