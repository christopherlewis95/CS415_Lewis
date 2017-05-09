# PA4: Matrix Multiplication

# Dependencies, Building, and Running

## Dependency Instructions
These projects depend on the MPI Library and SLIURM Running environment preinstalled in [h1.cse.unr.edu](h1.cse.unr.edu).  There are no instructions included on how to install these suites on your personal machines.
If you are using a Windows machine, you may SSH into your respective UNR accounts through [PuTTY] (http://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).

You may enter h1 off campus by first logging into your account through ubuntu.cse.unr.edu.  (Please note that keystrokes will be a tiny bit slower, but it's still manageable).
```bash
ssh username@ubuntu.cse.unr.edu
ssh username@h1.cse.unr.edu
```

## Compilation Options
There is only one option for this project and it is to use a makefile. Use the makefile provided in PA4/

# Running
You may simple run the program with a few commands from the PA4 home directory.
```bash
$ mkdir build (if not made)
$ cp makefile build/
$ cp src/par<#Cores>Matrix.sh build/ (Number of cores is 4, 9, or 16)
$ cp src/parMatrixIO.sh build/
$ cp runAll.sh build/ 
$ cd build
$ make
$ vim runAll.sh
   Change: sbatch <Script of your choice>.sh $a
   press escape
   type - :w
   type - :x
$ ./runAll

```
