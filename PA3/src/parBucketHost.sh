#!/bin/bash
#SBATCH -N1
#SBATCH -n8
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100; a<=1000; a+=100 ))
do  
    srun parBucket $a
done

