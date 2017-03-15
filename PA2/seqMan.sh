#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:50:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=400; a<=30000; a+=100 ))
do  
   echo $a
   srun seqMan $a $a
done
 
