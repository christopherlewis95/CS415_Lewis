#!/bin/bash
#SBATCH -N1
#SBATCH -n1
#SBATCH --time=00:01:00
#SBATCH --mail-user=christopherlewis@nevada.unr.edu
a=0
while [ $a -lt 3000 ]
do
   echo $a
   srun seqMan $a $a
   a=expr $a + 100`
done