#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=01:00:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100000000; a<=1500000000; a+=100000000 ))
do  
    srun seqBucket $a seqBucketSortTimed.txt 
done


