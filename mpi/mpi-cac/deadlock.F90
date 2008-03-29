program deadlock
use mpi
!include 'mpif.h'    !if USE mpi does not work or using F77
    implicit none


!!!!!!!!!!!!!!!!
!brockp@umich.edu
!mpif90 -o fhello helloworld.f90
!
!Demonstrate:
!  Deadlocks,
!  MPI_Recv() must have a matching MPI_Send()
!!!!!!!!!!!!!!!!

   integer rank                     ! rank of process
   integer numprocs                 ! size of COMM_WORLD
   integer tag                      ! tag
   integer ierr                     ! error code
   integer message                  ! Receved message
   integer status(MPI_STATUS_SIZE)  ! status of recv
   integer source                   ! source process
   integer dest                     ! process target
   double precision, dimension(SIZE) :: buffer  ! buffer
   integer x

   ! call INIT, SIZE and RANK
   call MPI_INIT(ierr)
   call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
   call MPI_COMM_SIZE(MPI_COMM_WORLD, numprocs, ierr)
   
   source = rank-1
   dest   = rank+1
   tag    = 10

   !fill buffer
   do x=1,SIZE
      buffer(x)=x+0.0001
   enddo

   if(rank .eq. 0) then
      write(*,*)SIZE," DOUBLES will be sent"
      source = numprocs-1
   endif
   if(rank .eq. numprocs-1) then
      dest = 0
   endif

!communicate
   call MPI_SEND(buffer, SIZE, MPI_DOUBLE_PRECISION, dest, tag, &
                 MPI_COMM_WORLD, ierr)
   call MPI_RECV(buffer, SIZE, MPI_DOUBLE_PRECISION, source, tag, &
                 MPI_COMM_WORLD, status, ierr)

   write(*,*)rank," rank finished"

   call MPI_FINALIZE(ierr)
end program deadlock
