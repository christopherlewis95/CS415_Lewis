#!/bin/bash
#SBATCH -N2
#SBATCH -n10
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=10; a<=50; a+=10 ))
do  
    srun parBucket $a
done

