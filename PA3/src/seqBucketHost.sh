#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100; a<=1000; a+=100 ))
do  
    srun seqBucket $a seqBucketSortMax100.txt   
done


