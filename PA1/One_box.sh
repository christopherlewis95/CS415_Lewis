#!/bin/bash
#SBATCH -n 2
#SBATCH --mem=2048MB
#SBATCH --time=00:30:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
#SBATCH --mail-type=ALL

srun src/mpiPingPong.cpp fileOne.txt

