## What's included
Included is all of the files required to compile and run the program. The makefile included will handle all of the compilation for you.
Folders with hidden .keep files are also inside the zip to ensure that the code can build correctly and log appropriately using the included batch file.

## Building/Compiling
All of the necessary shared object files and executables can be created using the makefile provided. To do so, simply type:
```
$ cd build
$ make
```
This will create all of the necessary files in the **bin** folder. Conversely, to delete all of the compiled files, type:
```
$ cd build
$ make clean
```

## Running
The program takes two command line arguments in order to run (the size of matrix a, and the size of matrix b). 
A batch file has been provided that runs tests using 4 cores and 9 cores. This does assume that the machine has slurm installed.
More tests can be written as long as the number of cores and the size of the matrices are perfect squares. The size must also be divisible by the number of cores as well.

## Results
The program itself will only print out the time taken to stdout if no errors were encountered. The provided batch file will record the timing results in the **log** directory.
