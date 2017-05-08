#!/bin/bash

BATCHFILES="../build"

for (( a=120; a<=1500000000; a+=120 ))
do

    TEST=$(squeue -o"%.18i %.9P %.20j %.20u %.8T %.10M %.9l %.6D %R")

    while [[ "$TEST" =~ "christopherlewis" ]]
    do
        sleep 1s
        TEST=$(squeue -o"%.18i %.9P %.20j %.20u %.8T %.10M %.9l %.6D %R")
    done

    echo $a
    sbatch par16Cores.sh $a
    squeue
    sleep 1s
done

