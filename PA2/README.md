# PA1 PING PONG 

# REPORT IS UNDER PA1/PA1Report.pdf
# Dependencies, Building, and Running

## Dependency Instructions
These projects depend on the MPI Library and SLIURM Running environment preinstalled in [h1.cse.unr.edu](h1.cse.unr.edu).  There are no instructions included on how to install these suites on your personal machines.
If you are using a Windows machine, you may SSH into your respective UNR accounts through [PuTTY] (http://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).

You may enter h1 off campus by first logging into your account through ubuntu.cse.unr.edu.  (Please note that keystrokes will be a tiny bit slower, but it's still manageable).
```bash
ssh username@ubuntu.cse.unr.edu
ssh username@h1.cse.unr.edu
```

# MPI_Send and Recv
Below is what the code looks like during the MPI send and recieve process
```bash
    if (taskid == 0) 
    {
      // Increment the ping pong count before you send it
      ping_pong_count++;
      MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);

      //printf("Proccesor %d sent and incremented ping_pong_count %d to processor %d\n",
         //   taskid, ping_pong_count, partner_rank);
    } 
    else if (taskid == 1)
    {
      ping_pong_count++;
      MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
      MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      //printf("processor %d received ping_pong_count %d from processor %d\n",
        //     taskid, ping_pong_count, partner_rank);
    }
```

# Times
Times that are in recorded into a text file will look like they are below 
```bash
0.00293		10
0.001381	11
0.001718	12
0.0017		13
0.002004	14
0.00215		15
0.002293	16
.
...
.....
...
.
0.794225	9994
0.800384	9995
0.792501	9996
0.79594		9997
0.792921	9998
0.798525	9999
0.796232	10000
```

## Building and Running
To build this project you must use a bashscript as to thhis is what I intended this project to be ran by. <br>
You may simple run the build script with a few commands.
```bash
chmod +x buildscript.sh
./buildscript
```
<br>
<b>Running the script will perform a make clean on its own.</b>

