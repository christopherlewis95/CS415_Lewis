#!/bin/bash
#SBATCH -n 2
#SBATCH --time=00:01:00
#SBATCH -J One_box
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
#SBATCH --mail-type=END

echo "runOne"
srun One_box oneBoxPing.txt 10

