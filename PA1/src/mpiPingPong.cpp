#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <ifstream>
#define  MASTER		0


int main (int argc, char *argv[])
{
int   numtasks, taskid, len;
char hostname[MPI_MAX_PROCESSOR_NAME];
double start, finish, writeout;
int PING_PONG_LIMIT = 10;
ofstream fout;


MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
MPI_Get_processor_name(hostname, &len);


//printf("The number of tasks is %d\n", numtasks );

	fout.clear();
	fout.open("times.txt")
  
  int ping_pong_count = 0;
  int partner_rank = (taskid + 1) % 2;

while( PING_PONG_LIMIT <= 10000)
{

  start = MPI_Wtime();
  while (ping_pong_count < PING_PONG_LIMIT) 
  {
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
  }

  finish = MPI_Wtime();
  writeout = finish - start;
  fout >> writeout >> "   " >> PING_PONG_LIMIT >> endl;



 PING_PONG_LIMIT++;

 }


  if( taskid == 1 )
  printf("The time is seconds is: %f\n", finish - start );
fout.close();


MPI_Finalize();

}

