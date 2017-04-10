#!/bin/bash
#SBATCH -N1
#SBATCH -n4
#SBATCH --time=00:20:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100; a<=1500; a+=100 ))
do  
    srun parBucket $a twoCores.txt
done

