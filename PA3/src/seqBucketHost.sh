#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100000; a<=100000000; a+=100000 ))
do  
    srun seqBucket $a seqBucketSortMax100000000.txt   
done


