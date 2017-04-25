PA4 - Matrix Multiplication Parallel
To compile use make-- it will compile the generator and the multiplication files
	ex. make
To run sbatch build.sh-- it will generate 2 generically named arrays of size specified in the batch (you can change the '1000' to whatever you want).
	ex. sbatch build.sh
To test on different node configurations adjust the values in 'build.sh' to you liking.

The arrays generate in the home folder for easy access, but the executables go in the bin and the source files can be found in src

Known problems: I wasn't able to get cannons to work, so I tried just splitting the array up normally like we did with bucket etc. the times are really garbage though, essentially just sequential-- so I think every process is actually just doing the entire operation and gathering into the same location. I'd appreciate any help you can offer!