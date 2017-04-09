#!/bin/bash
#SBATCH -N1
#SBATCH -n2
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=10; a<=50; a+=10 ))
do  
    srun parBucket $a
done

