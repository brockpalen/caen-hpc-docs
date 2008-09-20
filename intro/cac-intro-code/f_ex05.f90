! This program shows how to use MPI_Scatter and MPI_Gather
! Each processor gets different data from the root processor
! by way of mpi_scatter.  The data is summed and then sent back
! to the root processor using MPI_Gather.  The root processor
! then prints the global sum. 
module global
	integer numnodes,myid,mpi_err
end module
subroutine init
    use mpi
    use global
    implicit none
! do the mpi init stuff
    call MPI_INIT( mpi_err )
    call MPI_COMM_SIZE( MPI_COMM_WORLD, numnodes, mpi_err )
    call MPI_Comm_rank(MPI_COMM_WORLD, myid, mpi_err)
end subroutine init

program test1
	use mpi
	use global
	implicit none
	integer, allocatable :: myray(:),send_ray(:),back_ray(:)
	integer count
	integer size,mysize,i,k,j,total
	integer, parameter :: root=0
	call init
! each processor will get count elements from the root
	count=4
	allocate(myray(count))
! create the data to be sent on the root
	if(myid == root)then
	    size=count*numnodes	
		allocate(send_ray(0:size-1))
		allocate(back_ray(0:numnodes-1))
		do i=0,size-1
			send_ray(i)=i
		enddo
	endif
! send different data to each processor 
	call MPI_Scatter(	send_ray, count,  MPI_INTEGER, &
						myray,    count,  MPI_INTEGER, &
	                 	root,                      &
	                 	MPI_COMM_WORLD,mpi_err)
	                
! each processor does a local sum
	total=sum(myray)
	write(*,*)"myid= ",myid," total= ",total
! send the local sums back to the root
	call MPI_Gather(	total,    1,  MPI_INTEGER, &
						back_ray, 1,  MPI_INTEGER, &
	                 	root,                  &
	                 	MPI_COMM_WORLD,mpi_err)
! the root prints the global sum
	if(myid == root)then
	  write(*,*)"results from all processors= ",sum(back_ray)
	endif
	
	call mpi_finalize(mpi_err)
end program
