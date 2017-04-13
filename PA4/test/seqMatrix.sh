#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:40:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100; a<=2700; a+=100 ))
do  
    srun seqMatrix $a seqMatrixTimed.txt 
done


