program fpi
use mpi
!include 'mpif.h'      !if USE mpi does not work on your system or F77
   implicit none
   
!!!!!!!!!!!!!!!!
!brockp@umich.edu
!mpif90 -o fpi fpi.f90
!
! integrate f(x) = 4/( 1 + x*x )
!
!Demonstrate:
!  MPI_Init()
!  MPI_Comm_size()
!  MPI_Comm_rank()
!  MPI_Bcast()
!  MPI_Reduce()
!!!!!!!!!!!!!!!!
   
   integer rank                     ! rank of process
   integer numprocs                 ! size of COMM_WORLD
   integer ierr                     ! error code
   double precision area            ! partial sum
   double precision total           ! total area
   double precision n               ! number of intervals
   double precision width           ! interval width
   double precision midpoint        ! midpoint of f(x)
   double precision x               ! loop counter

   ! call INIT, SIZE and RANK
   call MPI_INIT(ierr)
   call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
   call MPI_COMM_SIZE(MPI_COMM_WORLD, numprocs, ierr)

   if( rank .eq. 0) then
     write(*,*)"MPI_COMM_WORLD is ",numprocs," big!"
     write(*,*)"Number of intervals?:"
     read(*,*) n
   endif

! all ranks should continue from here
  call MPI_BCAST(      n, &  ! buffer to send/recv data 
                       1, &  ! amount of data to send
    MPI_DOUBLE_PRECISION, &  ! datatype
                       0, &  ! root to bcast from
          MPI_COMM_WORLD, &  ! Communicator
                    ierr)

! find local sums
   width = 1.0/n
   do x = rank, n, numprocs
      midpoint = (x + 0.5) * width
      area = area + 4.0 / (1.0 + midpoint*midpoint)
   enddo

   call MPI_REDUCE(     area,   &  ! send buffer
                       total,   &  ! recv buffer
                           1,   &  ! count to reduce
        MPI_DOUBLE_PRECISION,   &  ! datatype
                     MPI_SUM,   &  ! MPI_Op
                           0,   &  ! rank to recev result
              MPI_COMM_WORLD,   &  ! communicator
                        ierr)

   if(rank .eq. 0) then
      !normalize value
      total = total*width
      write(*,*)"Pi is: ",total
   endif 

   call MPI_FINALIZE(ierr)
end program fpi
