#!/bin/bash
#SBATCH -N3
#SBATCH -n12
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=400; a<=10000; a+=100 ))
do  
   echo $a
   srun dynMan $a $a
done
