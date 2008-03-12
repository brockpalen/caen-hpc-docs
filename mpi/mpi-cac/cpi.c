#include <stdio.h>
#include <stdlib.h>

#ifndef OPT
   #include "mpi.h"
#else
   #include <optmpi.h>
#endif

/******
brockp@umich.edu
mpicc -o cpi cpi.c

Integrate between:  0..1

f(x)=4/(1 + x*x)

Demonstrate:
  MPI_Init()
  MPI_Comm_size()
  MPI_Comm_rank()
  MPI_Bcast()
  MPI_Reduce()
******/

int main(int argc, char **argv){

  int rank;          /* rank of process */
  int numprocs;      /* size of COMM_WORLD */
  double area = 0.0; /* partal sum */
  double total= 0.0; /* total sum */
  double n = 0.0;    /* number of intervals */
  double width;      /* interval width */
  double midpoint;   /* midpoint of f(x) */
  int x;             /* needed counter */

  /* call Init, size, and rank */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){
    printf("Started with %d ranks\n",numprocs);
    printf("Number of intervals?: \n");
    scanf("%lf",&n);

  } /* all ranks need to be included now */
 
  MPI_Bcast(    &n,  /* buffer to send/recv in/out of */
                 1,  /* number of values to bcast */
       MPI_DOUBLE,  /* type to send */
                 0,  /* root to bcast from */
    MPI_COMM_WORLD); /* communicator */

   /* find local sums */
  width = 1.0/n;
  for (x = rank; x < n; x += numprocs){
      midpoint = ((double)x + 0.5) * width;
      area += 4.0 / (1.0 + midpoint*midpoint);
  } /* end for */

  /* use MPI_Reduce() to get the sum of the local sums */

  MPI_Reduce( &area,   /* send buff */
             &total,   /* recv buff */
                  1,   /* number to reduce */
         MPI_DOUBLE,   /* datatype */
            MPI_SUM,   /* MPI_Op */
                  0,   /* rank to get result */
    MPI_COMM_WORLD);   /* communicator */

  if(rank == 0){
    /* normalize */
    total *= width;
    printf("Pi is: %20.20lf\n", total);
  }

/* always call at end */
MPI_Finalize();

return 0;
}
