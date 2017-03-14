#!/bin/bash
#SBATCH -N5
#SBATCH -n5
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=5000; a<=6000; a+=100 ))
do  
   echo $a
   srun dynMan $a $a
done
