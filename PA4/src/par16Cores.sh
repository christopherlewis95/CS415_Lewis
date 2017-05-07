#!/bin/bash
#SBATCH -N1
#SBATCH -n4
#SBATCH --time=00:30:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=120; a<=1500000000; a+=120 ))
do  
    srun parMatrix $a >> 16CoresTimed.txt
done



