# PA3 Bucket Sort

# REPORT IS UNDER PA2/PA2Report.pdf
# Dependencies, Building, and Running

## Dependency Instructions
These projects depend on the MPI Library and SLIURM Running environment preinstalled in [h1.cse.unr.edu](h1.cse.unr.edu).  There are no instructions included on how to install these suites on your personal machines.
If you are using a Windows machine, you may SSH into your respective UNR accounts through [PuTTY] (http://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).

You may enter h1 off campus by first logging into your account through ubuntu.cse.unr.edu.  (Please note that keystrokes will be a tiny bit slower, but it's still manageable).
```bash
ssh username@ubuntu.cse.unr.edu
ssh username@h1.cse.unr.edu
```

## Building and Running
You may simple run the build with a few commands.
```bash
(Make sure you are under CS415_Lewis/PA3)
mkdir build
cp makefile src/*.sh build/
cd build

make
sbatch <scriptName>.sh
make clean
```
# Your results will be in shortly ;)