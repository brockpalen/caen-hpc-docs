! Program shows how to use probe and get_count to find the size
! of an incomming message
      program hello

      use mpi 
      integer myid,numprocs
      integer status(MPI_STATUS_SIZE)
      integer mytag,i,icount,ierr
      call MPI_INIT( ierr )
      call MPI_COMM_RANK( MPI_COMM_WORLD, myid, ierr )
      call MPI_COMM_SIZE( MPI_COMM_WORLD, numprocs, ierr )

      write (*,*) "Hello from ",myid
      write (*,*) "Numprocs is ",numprocs
      mytag=123
      i=0
      icount=0
      if(myid .eq. 0)then
         i=100
         icount=1
         call MPI_SEND(i,icount,MPI_INTEGER,1,mytag,MPI_COMM_WORLD,ierr)
      endif
      if(myid .eq. 1)then
      	call mpi_probe(0,mytag,MPI_COMM_WORLD,status,ierr)
      	call mpi_get_count(status,MPI_INTEGER,icount,ierr)
      	write(*,*)"getting ", icount
      	call mpi_recv(i,icount,MPI_INTEGER,0,mytag,MPI_COMM_WORLD,&
         status,ierr)
      	write(*,*)"i=",i
      endif
      call mpi_finalize(ierr)
      stop
      end




