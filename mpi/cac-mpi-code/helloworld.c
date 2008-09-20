#include <stdio.h>
#include <stdlib.h>

#ifndef OPT
   #include "mpi.h"
#else
   #include <optmpi.h>
#endif

/******
brockp@umich.edu
mpicc -o chello helloworld.c

Demonstrate:
  MPI_Init()
  MPI_Comm_size()
  MPI_Comm_rank()
  MPI_Send()
  MPI_Recv()
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

  if(rank != 0){
    MPI_Recv(&message,    /*buffer for message */
                    1,    /*MAX count to recv */
              MPI_INT,    /*type to recv */
                    0,    /*recv from 0 only */
                  tag,    /*tag of messgae */
       MPI_COMM_WORLD,    /*communicator to use */
              &status);   /*status object */
    printf("Hello from process %d!\n",rank);
  }
  else{
    /* rank 0 ONLY executes this */
    printf("MPI_COMM_WORLD is %d processes big!\n", numprocs);
    int x; 
    for(x=1; x<numprocs; x++){
       MPI_Send(&x,          /*send x to process x */
                 1,          /*number to send */
           MPI_INT,          /*type to send */
                 x,          /*rank to send to */
               tag,          /*tag for message */
     MPI_COMM_WORLD);        /*communicator to use */
    } 
  } /* end else */

  
/* always call at end */
MPI_Finalize();

return 0;
}
