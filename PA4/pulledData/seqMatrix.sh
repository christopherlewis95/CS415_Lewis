#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:50:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=120; a<=5000; a+=120 ))
do  
    srun seqMatrix $a seqMatrixTimed.txt 
done


