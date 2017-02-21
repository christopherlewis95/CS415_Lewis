#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER		0
#define  PING_PONG_LIMIT 10

int main (int argc, char *argv[])
{
int   numtasks, taskid, len;
char hostname[MPI_MAX_PROCESSOR_NAME];
double start1, finish1, start2, finish2, time1, time2;

MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
MPI_Get_processor_name(hostname, &len);


//printf("The number of tasks is %d\n", numtasks );

  
  int ping_pong_count = 0;
  int partner_rank = (taskid + 1) % 2;

  if( taskid == 0)
  start1 = MPI_Wtime();

  if( taskid == 1 )
  start2 = MPI_Wtime();

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
  if( taskid == 0)
  finish1 = MPI_Wtime();

  if( taskid == 1 )
  finish2 = MPI_Wtime();


  if( taskid == 0 )
  time1 = finish1 - start1;
  
  else if( taskid == 1)

  time2 = finish2 - start2;

MPI_Finalize();

	printf("Final time is %f\n", (time1 + time2)/2 );

return 0;

}

