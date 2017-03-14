#!/bin/bash
#SBATCH -N5
#SBATCH -n5
#SBATCH --time=00:05:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=400; a<=1800; a+=20 ))
do  
   echo $a
   srun dynMan $a $a
done
