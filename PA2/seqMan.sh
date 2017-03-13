#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:01:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
for (( a=600; c<=3000; c+=100SS ))
do  
   echo $a
   srun seqMan $a $a
done
 
