#include <stdio.h>
#include <stdlib.h>

#ifndef OPT
   #include "mpi.h"
#else
   #include <optmpi.h>
#endif

/******
brockp@umich.edu
mpicc -o cdeadlock deadlock.c

Demonstrate:
  Deadlocks,
  MPI_Recv() must have a matching MPI_Send()
  
******/

int main(int argc, char **argv){

  int rank;          /* rank of process */
  int numprocs;      /* size of COMM_WORLD */
  int tag=10;        /* expected tag */
  int message;       /* Recv'd message */
  MPI_Status status; /* status of recv */

  /* call Init, size, and rank */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int source = rank-1; /* source process */
  int dest   = rank+1; /* process target */
  double *buffer;      /* Send buffer */
  buffer  = (double *) malloc(sizeof(double)*SIZE);
  
  /* fill buffer */
  int i;
  for (i=0; i<SIZE; i++){
     buffer[i]=i*0.0001;
  } /* end for */

  /* zero gets from last process
     rank numprocs-1 -> 0
     last process sends to 0 */
  if(rank == 0){ /* root process only */
    printf("%i doubles will be sent\n",SIZE);
    source = numprocs-1;
  } /* end if */
  if(rank == numprocs-1){
    dest = 0;
  } /* end if */

  /* communicate */
  MPI_Send(buffer, SIZE, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  MPI_Recv(buffer, SIZE, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status);

  printf("%i rank finished\n",rank);

 free(buffer);   /* always free memory */
/* always call at end */
MPI_Finalize();

return 0;
}
