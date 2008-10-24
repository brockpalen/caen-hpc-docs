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
#elif VECLIB  /* Apple blas lib provides CBLAS type functions */
  #include <vecLib/vecLib.h>
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
int timeelapsed=0;
int total=0;
unsigned int mflops=0;
unsigned int order=0;
unsigned int dim=50, dimmax=10000, diminc=10;
int counter=0;

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
   printf("%8d ", dim);
   #if defined (BLAS1) || defined (BLAS2)
   /** allocate arrays needed for blas 1/2**/
   double *x = (double *)malloc(dim*sizeof(double));
   double *y = (double *)malloc(dim*sizeof(double));

   if(y==NULL || x==NULL){
      fprintf(stderr, WHERESTR " ERROR: %s\n", WHEREARG, strerror(errno));
      return -1;
   }

   for(counter=0;counter<dim;counter++){
      x[counter]=y[counter]=counter;
   } /* end for */
   #endif /* blas 1/2 arrays */

   #ifdef BLAS1
   /* blas 1 */
   gettimeofday( &tv1, NULL);
   #ifdef ACML
   total=ddot(dim, x, 1, y, 1);
   #elif defined (VECLIB) || defined (CBLAS) || defined (MKL)
    total=cblas_ddot(dim, x, 1, y, 1);
   #endif

   gettimeofday( &tv2, NULL);
   timeelapsed = tv2.tv_sec*1000000+tv2.tv_usec;
   timeelapsed-= tv1.tv_sec*1000000+tv1.tv_usec;
   order=dim*2;
   mflops=order/timeelapsed;
   printf(" %10d", mflops);

   gettimeofday( &tv1, NULL);
   total=0;
   for(counter=0; counter<dim; counter++){
      total+=x[counter]*y[counter];
   }  /* end for */
   gettimeofday( &tv2, NULL);
   timeelapsed = tv2.tv_sec*1000000+tv2.tv_usec;
   timeelapsed-= tv1.tv_sec*1000000+tv1.tv_usec;
   mflops=order/timeelapsed;
   printf(" %10d", mflops);
   
   #endif  /* blas1 */

   /* blas 2 */
   #if defined (BLAS2) || defined (BLAS3)
   double *A = (double *)malloc(dim*dim*sizeof(double));
   if(A==NULL){
      fprintf(stderr, WHERESTR " ERROR: %s\n", WHEREARG, strerror(errno));
      return -1;
   }
   #endif
   #ifdef BLAS2
   for(counter=0;counter<dim*dim;counter++){
      A[counter]=counter;
   } /* end for */

   gettimeofday( &tv1, NULL);
   #ifdef ACML
   dgemv('T', dim, dim, 1, A, dim, x, 1, 0, y, 1);
   #elif defined (VECLIB) || defined (CBLAS) || defined (MKL)
   cblas_dgemv(CblasRowMajor, CblasNoTrans, dim, dim, 1, A, dim, x, 1, 0, y, 1);
   #endif

   gettimeofday( &tv2, NULL);
   timeelapsed = tv2.tv_sec*1000000+tv2.tv_usec;
   timeelapsed-= tv1.tv_sec*1000000+tv1.tv_usec;
   order=dim*dim*2;
   mflops=order/timeelapsed;
   printf(" %10d", mflops);

   unsigned int counter2=0;
   for(counter=0; counter<dim; counter++) y[counter]=0;
   
   gettimeofday( &tv1, NULL);
   for(counter=0; counter<dim; counter++){
      for(counter2=0; counter2<dim; counter2++){
      y[counter]+=A[counter2+(counter*dim)]*x[counter2];
      }
   } /* end for */
   gettimeofday( &tv2, NULL);
   timeelapsed = tv2.tv_sec*1000000+tv2.tv_usec;
   timeelapsed-= tv1.tv_sec*1000000+tv1.tv_usec;
   order=dim*dim*2;
   mflops=order/timeelapsed;
   printf(" %10d", mflops);
   
   #endif  /* blas2 */

   #ifdef BLAS3
   
   double *B = (double *)malloc(dim*dim*sizeof(double));
   double *C = (double *)malloc(dim*dim*sizeof(double));
   if(B==NULL || C==NULL){
      fprintf(stderr, WHERESTR " ERROR: %s\n", WHEREARG, strerror(errno));
      return -1;
   }
   for(counter=0;counter<dim*dim;counter++){
      A[counter]=B[counter]=counter;
   } /* end for */

   gettimeofday( &tv1, NULL);
   #ifdef ACML
   dgemm('T', 'T', dim, dim, dim, 1, A, dim, B, dim, 0, C, dim);
   #elif defined (VECLIB) || defined (CBLAS) || defined (MKL)
   cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
               dim, dim, dim, 1, A, dim, B, dim, 0, C, dim);
   #endif

   gettimeofday( &tv2, NULL);
   timeelapsed = tv2.tv_sec*1000000+tv2.tv_usec;
   timeelapsed-= tv1.tv_sec*1000000+tv1.tv_usec;
   order=dim*dim*dim*2;
   mflops=(dim*dim)/(timeelapsed/dim/2);
   printf(" %10d", mflops);


   /* zero result matrix */
   for(counter=0; counter<dim*dim; counter++){

   }  /* end for */

   int j, k;
   gettimeofday( &tv1, NULL);
   for(counter=0; counter<dim; counter++){
      for(j=0; j<dim; j++){
          for(k=0; k<dim; k++){
             C[counter+j*dim]+=A[counter+k*dim]*B[k+j*dim];
          }
      }
   } /* end for */
   gettimeofday( &tv2, NULL);
   timeelapsed = tv2.tv_sec*1000000+tv2.tv_usec;
   timeelapsed-= tv1.tv_sec*1000000+tv1.tv_usec;
   mflops=(dim*dim)/(timeelapsed/dim/2);
   printf(" %10d", mflops);

   #endif /* blas3 */  
 
   /* free blas 1 arrays */
   #if defined (BLAS1) || defined (BLAS2)
   free(x);
   free(y);
   #endif

   /* free blas 2/3 Matrix */
   #if defined (BLAS2) || defined (BLAS3)
   free(A);
   #endif
   
   /* free blas 3 only Matrix's */
   #ifdef BLAS3
   free(B);
   free(C);
   #endif

   /* endline needed to fpretty output */
   printf("\n");
   fflush(stdout);
} /* end for */
return 0;
}

