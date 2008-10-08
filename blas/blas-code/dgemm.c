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

Example Calling dgemm from C.

See:

http://www.netlib.org/blas/dgemm.f

For what all the options mean
******/

int main(int argc, char **argv){
  #ifdef _OPENMP
    printf("OpenMP Enabled\n");
    printf("Will use: %d threads of %d available\n",
            omp_get_num_procs(), omp_get_max_threads());
  #endif

int M;     /* Number of row of matrix op(A) */
int N;     /* Number of columns of matrix op(B) */
int K;     /* Number of columns of matrix op(A) and rows ob(B) */
int lda;   /* On entry, LDA specifies the first dimension of A as declared
              in the calling (sub) program. When  TRANSA = 'N' or 'n' then
              LDA must be at least  max( 1, m ), otherwise  LDA must be at
              least  max( 1, k ).  */
int ldb;   /* On entry, LDB specifies the first dimension of B as declared
              in the calling (sub) program. When  TRANSB = 'N' or 'n' then
              LDB must be at least  max( 1, k ), otherwise  LDB must be at
              least  max( 1, n ). */
int ldc;
double alpha, beta; 

M=N=K=3;
lda=ldb=ldc=3;
alpha=1.0;
beta=0.0;

/**  Allocate Memory for Arrays **/
double *a = (double *)malloc(lda*K*sizeof(double));
double *b = (double *)malloc(ldb*N*sizeof(double));
double *c = (double *)malloc(ldc*N*sizeof(double));

if(c==NULL || b==NULL || a==NULL){
   fprintf(stderr, WHERESTR " ERROR: %s\n", WHEREARG, strerror(errno));
   return -1;
}

a[0]=0.0;
a[1]=1.0;
a[2]=2.0;
a[3]=3.0;
a[4]=4.0;
a[5]=5.0;
a[6]=6.0;
a[7]=7.0;
a[8]=8.0;

b[0]=0.0;
b[1]=1.0;
b[2]=2.0;
b[3]=3.0;
b[4]=4.0;
b[5]=5.0;
b[6]=6.0;
b[7]=7.0;
b[8]=8.0;

#ifdef ACML
dgemm('T','T',M,N,K,alpha,a,lda,b,ldb,beta,c,ldc);
#elif defined(CBLAS) || defined(MKL) || defined(VECLIB)
cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
             M,N,K,alpha,a,lda,b,ldb,beta,c,ldc);
#endif

int i, j;
i=j=lda;
for(i=0;i<lda;i++){
   for(j=0;j<N;j++){
     printf(" %5.1f ", c[j+N*i]);
   }
   printf("\n");
}

free(a);
free(b);
free(c);
return 0;
}
