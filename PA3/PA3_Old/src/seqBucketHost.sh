#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=100000; a<=10000000; a+=100000 ))
do  
    g++ randNumGen.cpp -o randGen
    g++ seqBucketSort.cpp -o seqBuck
    ./randGen $a
    ./seqBuck $a
    rm randGen
    rm seqBuck   
done


