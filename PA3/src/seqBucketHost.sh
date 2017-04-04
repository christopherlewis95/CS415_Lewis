#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=10; a<=100; a+=10 ))
do  
    srun seqBucket $a seqBucketSortMax100.txt   
done


