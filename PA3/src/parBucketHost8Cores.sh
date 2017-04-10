#!/bin/bash
#SBATCH -N1
#SBATCH -n4
#SBATCH --time=00:20:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100000; a<=1500000000; a+=100000 ))
do  
    srun parBucket $a eightCores.txt
done

