program dgemm_example
!!!!!!!!!!!!!!!!
!Brock Palen
!brockp@umich.edu
!
!Example Callding DGEMM from Fortran
!See:
!
!http://www.netlib.org/blas/dgemm.f
!!!!!!!!!!!!!!!!
#define WHERESTR "[file %s, line %d]"
#define WHEREARG __FILE__,__LINE__

#ifdef _OPENMP
  use omp_lib
#endif
implicit none
EXTERNAL DGEMM
INTEGER I, J
DOUBLE PRECISION, ALLOCATABLE :: a(:,:)
DOUBLE PRECISION, ALLOCATABLE :: b(:,:)
DOUBLE PRECISION, ALLOCATABLE :: c(:,:)
INTEGER M    ! Number of rows of matrix op(a)
INTEGER N    ! Number of columns of matrix op(b)
INTEGER K    ! Number of columns of matrix op(a) and rows op(b)
INTEGER lda  ! n entry, LDA specifies the first dimension of A as declared
             ! in the calling (sub) program. When  TRANSA = 'N' or 'n' then
             ! LDA must be at least  max( 1, m ), otherwise  LDA must be at
             ! least  max( 1, k ).  
INTEGER ldb  ! On entry, LDB specifies the first dimension of B as declared
             ! in the calling (sub) program. When  TRANSB = 'N' or 'n' then
             ! LDB must be at least  max( 1, k ), otherwise  LDB must be at
             ! least  max( 1, n ). 
INTEGER ldc  ! On entry, LDC specifies the first dimension of C as declared
             ! in  the  calling  (sub)  program.   LDC  must  be  at  least
             ! max( 1, m ).
DOUBLE PRECISION alpha, beta

#define WHERESTR "[file %s, line %d]"
#define WHEREARG __FILE__,__LINE__

#ifdef _OPENMP
 write(*,*)"Will use: ", omp_get_num_procs(), " of ", &
            omp_get_max_threads(), " available"
#endif
M=3
N=M
K=M
lda=M
ldb=M
ldc=M
alpha=1.0
beta=0.0

! allocate arrays
ALLOCATE(a(lda,K), b(ldb,N), c(ldc,N))

a=RESHAPE((/ 0.0, 1.0, 2.0, &
             3.0, 4.0, 5.0, &
             6.0, 7.0, 8.0  /), &
             (/lda,K/))
b=RESHAPE((/ 0.0, 1.0, 2.0, &
             3.0, 4.0, 5.0, &
             6.0, 7.0, 8.0  /), &
             (/ldb,N/))

CALL DGEMM('N','N',M,N,K,alpha,a,lda,b,ldb,beta,c,ldc)

DO I = LBOUND(c,1), UBOUND(c,1)
    WRITE(*,*) (c(I,J), J=LBOUND(c,2), UBOUND(c,2))
END DO
end program dgemm_example
