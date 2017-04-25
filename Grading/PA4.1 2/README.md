# PA4: Matrix Multiplication
by Aaron Dartt


## Building and Compiling

cd build

make

# to clean

make clean


## Running
This project is meant to be run with SBATCH for queuing and courtesy to the other users.
the .sh files may be found in this project's build directory which has a script directory.
The contents of this file includes specification requirements for this job in the queue.

There are 30 SBATCH scripts in the following format:

<inputSize>x<numberOfCores>.sh

This will be run by using:


cd build

sbatch <name>.sh

Since this is run by another program, `sbatch`, do not change the execution mode using `chmod` at all with them.

There is also a script generation program in the src/scriptGen directory. If you want to 
run all the sbatch scripts in the build/scripts dirctory then there is a bash script in the
build directory called walkAway.sh. This script will run each script five times and launch a
job each time the user no longer has a job in squeue.
