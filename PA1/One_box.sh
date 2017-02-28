#!/bin/bash
#SBATCH -n 2
#SBATCH -t 0-1:30
#SBATCH -J One_box
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
#SBATCH --mail-type=END


echo "runOne"
srun ./One_box

