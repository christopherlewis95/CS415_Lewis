#!/bin/bash
#SBATCH -N1
#SBATCH -n8
#SBATCH --time=01:00:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=400; a<=30000; a+=100 ))
do  
   echo $a
   srun dynMan $a $a
done
