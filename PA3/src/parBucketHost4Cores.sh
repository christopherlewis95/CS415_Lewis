#!/bin/bash
#SBATCH -N1
#SBATCH -n2
#SBATCH --time=00:30:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=10000; a<=15000000; a+=10000 ))
do  
    srun parBucket $a 2Cores.txt
done

