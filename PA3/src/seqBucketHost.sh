#!/bin/bash
for (( a=100; a<=10000; a+=100 ))
do  
    g++ randNumGen.cpp -o randGen
    g++ seqBucketSort.cpp -o seqBuck
    ./randGen $a
    ./seqBuck
    rm randGen
    rm seqBuck   
done


