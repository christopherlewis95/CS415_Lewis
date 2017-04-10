#!/bin/bash
#SBATCH -N1
#SBATCH -n2
#SBATCH --time=00:30:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100; a<=1500; a+=100 ))
do  
    srun parBucket $a 2Cores.txt
done

