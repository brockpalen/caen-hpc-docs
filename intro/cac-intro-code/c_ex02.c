#include <stdio.h>
#include "mpi.h"
#include <math.h>
 
/************************************************************
! Program shows how to use probe and get_count to find the size
! of an incomming message
************************************************************/

int main(argc,argv)
int argc;
char *argv[];
{
    int myid, numprocs;
    MPI_Status status;
    int i,mytag,ierr,icount;
 
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
 

/* print out my rank and this run's PE size*/
    printf("Hello from %d\n",myid);
    printf("Numprocs is %d\n",numprocs);
    mytag=123;
    i=0;
    icount=0;
    if(myid == 0) {
    	i=100;
    	icount=1;
    	ierr=MPI_Send(&i,icount,MPI_INT,1,mytag,MPI_COMM_WORLD);
    }
    if(myid == 1){
    	ierr=MPI_Probe(0,mytag,MPI_COMM_WORLD,&status);
    	ierr=MPI_Get_count(&status,MPI_INT,&icount);
    	printf("getting %d\n",icount);
   	ierr = MPI_Recv(&i,icount,MPI_INT,0,mytag,MPI_COMM_WORLD,&status);
    	printf("i= %d\n",i);
    }
    MPI_Finalize();
}

