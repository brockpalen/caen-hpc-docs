#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>

#ifdef ACML
  #include <acml.h>
#elif MKL
  #include <mkl_cblas.h>
#elif CBLAS
  #include <cblas.h>
#else
  #error "No BLAS lib defined Options: ACML, MKL, CLBAS"
#endif


#ifdef _OPENMP
  #include <omp.h>
#endif
#define WHERESTR "[file %s, line %d]"
#define WHEREARG __FILE__,__LINE__

/******
Brock Palen 
brockp@umich.edu

Code runs BLAS 1 2 and 3 to compare performance
******/

struct timeval tv1, tv2;
struct timezone tz;
 double timeelapsed=0;
unsigned int numops=0;
unsigned int order=0;
unsigned int dim=100, dimmax=1000, diminc=100;

int main(int argc, char **argv){

  #ifdef _OPENMP
    printf("OpenMP Enabled\n");
    printf("Will use: %d threads of %d available\n",
            omp_get_num_procs(), omp_get_max_threads());
  #endif

/****
Blas 1
DDOT(N, X, INCX, Y, INCY)

N      Dimention of Vector X
X      Vector 
INCX   Incrment Vector X
Y      Vector
INCY   Increment Vector Y
 
Blas 2
DGEMV(TRANS, M, N, ALPHA, A, LDA, X, INCX, BETA, Y, INCY)

TRANS  Transpose A or not
M      Rows of A
N      Columns of A
ALPHA  Scaler to Multiply A by
A      Matrix  A(LDA, N)
LDA    First dimension of A.  max(1, M)
X      Array dimension at least (1+(n-1)*abs(INCX)) when TRANS=N
       (1+(m-1)*abs(INCX)) Otherwise
INCX   Increments for the elements of X
BEATA  Scaller to multipy Y by
Y      Array dimension at least (1+(m-1)abs(INCY)) when TRANS=N
       (1+(n-1)*ABS(INCY)) otherwise.
       Y is overwriteen with the results
INCY   Increments for the elements of Y
*****/

for(dim; dim<=dimmax; dim+=diminc){
   /** allocate arrays needed for blas 1/2**/
   double *x = (double *)malloc(dim*sizeof(double));
   double *y = (double *)malloc(dim*sizeof(double));

   if(y==NULL || x==NULL){
      fprintf(stderr, WHERESTR " ERROR: %s\n", WHEREARG, strerror(errno));
      return -1;
   }

   int counter=0;
   for(counter=0;counter<dim;counter++){
      x[counter]=y[counter]=counter;
   } /* end for */

   /* blas 1 */
   gettimeofday( &tv1, &tz);
   #ifdef ACML
   ddot(dim, x, 1, y, 1);
   #endif /*  ACML */

   gettimeofday( &tv2, &tz);
   timeelapsed = (tv2.tv_usec-tv1.tv_usec);
   printf("%4d %4d", dim, timeelapsed);
   /* free blas 1 arrays */
   free(x);
   free(y);

   /* endline needed to fpretty output */
   printf("\n");
} /* end for */
return 0;
}

