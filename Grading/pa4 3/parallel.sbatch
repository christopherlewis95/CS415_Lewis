#!/bin/bash

#SBATCH -N 2
#SBATCH --time=00:10:00
#SBATCH --mem=8192MB
#SBATCH --output=../log/parallel.csv

BIN_PATH=../bin

if [[ ! -f ${BIN_PATH}/matrix_parallel ]]; then
  echo "error: binary not found"
  exit 1
fi


sizes=(100 484 1024 1444 1936 2500 3136)
printf "4 cores,"
for size in ${sizes[@]}; do
  srun -n 4 ${BIN_PATH}/matrix_parallel ${size} ${size}
  printf ","
done
echo ""

sizes=(81 576 1296 1521 2025 2601 2916)
printf "9 cores,"
for size in ${sizes[@]}; do
  srun -n 9 ${BIN_PATH}/matrix_parallel ${size} ${size}
  printf ","
done
echo ""

exit 0

