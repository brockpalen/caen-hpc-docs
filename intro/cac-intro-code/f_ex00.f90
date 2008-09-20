!****************************************************************
!  This is a simple hello world program. Each node prints out 
!  it's rank and the size of the current MPI run (Total number of
!  nodes).
!****************************************************************
      program hello

      use mpi
!     include "mpif.h"
      call MPI_INIT( ierr )
      call MPI_COMM_RANK( MPI_COMM_WORLD, myid, ierr )
      call MPI_COMM_SIZE( MPI_COMM_WORLD, numprocs, ierr )

      write (*,*) "Hello from ",myid
      write (*,*) "Numprocs is ",numprocs

      call MPI_FINALIZE(ierr)
      stop
      end




