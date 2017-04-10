#!/bin/bash
#SBATCH -N1
#SBATCH -n4
#SBATCH --time=00:30:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=10000000; a<=1500000000; a+=10000000 ))
do  
    srun parBucket $a fourCores.txt
done

