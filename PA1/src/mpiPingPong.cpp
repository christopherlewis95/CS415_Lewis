#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER		0
#define  PING_PONG_LIMIT 10

int main (int argc, char *argv[])
{
int   numtasks, taskid, len;
char hostname[MPI_MAX_PROCESSOR_NAME];

MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
MPI_Get_processor_name(hostname, &len);



  int ping_pong_count = 0;
  int partner_rank = (taskid + 1) % 2;
  while (ping_pong_count < PING_PONG_LIMIT) 
  {
    if (taskid == ping_pong_count % 2) 
    {
      // Increment the ping pong count before you send it
      ping_pong_count++;
      MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
      printf("Proccesor %d sent and incremented ping_pong_count %d to processor %d\n",
             taskid, ping_pong_count, partner_rank);
    } 
    else 
    {
      MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      printf("processor %d received ping_pong_count %d from processor %d\n",
             taskid, ping_pong_count, partner_rank);
    }
  }

MPI_Finalize();

}

