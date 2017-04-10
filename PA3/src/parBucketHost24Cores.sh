#!/bin/bash
#SBATCH -N4
#SBATCH -n24
#SBATCH --time=01:00:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=10000000; a<=1500000000; a+=10000000 ))
do  
    srun parBucket $a twentyfourCores.txt
done

