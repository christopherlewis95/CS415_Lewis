#!/bin/bash
#SBATCH -N2
#SBATCH -n10
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
file=10Cores.txt
for (( a=10; a<=100; a+=10 ))
do  
    srun parBucket $a $file
done

