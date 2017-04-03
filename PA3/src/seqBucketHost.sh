#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100; a<=10000000; a+=10000 ))
do  
    srun seqBuck $a seqBucketSort.txt   
done


