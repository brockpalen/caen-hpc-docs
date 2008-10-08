/*****
fftw-3  example
Brock Palen
brockp@umich.edu
http://www.umich.edu/~brockp/
http://cac.engin.umich.edu

take the DFT of  cos(2*PI*x/10)
To print results compile with -DDBUG
To change the size of the transform -DSAMPLE=1024 (512 default)

module load fftw/3.1.1-pgi
pgcc sinfft.c $FFTW_INC $FFTW_LINK -lfftw3

http://www.fftw.org/doc/One_002dDimensional-DFTs-of-Real-Data.html#One_002dDimensional-DFTs-of-Real-Data
*****/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <fftw3.h>

#ifndef M_PI
  #define M_PI 3.14159265
#endif
#ifndef SAMPLE
  #define SAMPLE 512
#endif

#define WHERESTR "[file %s, line %d]"
#define WHEREARG __FILE__,__LINE__

int main(void){
  fftw_complex *out;
  fftw_plan p;
  double *in, tmp=0;
  double add=0, mul=0, fma=0;
  in  = (double*) fftw_malloc(sizeof(double)*SAMPLE);
  out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*ceil(SAMPLE/2+1)); /* see note below */
  p   = fftw_plan_dft_r2c_1d(SAMPLE, in, out, FFTW_MEASURE);
  if(out == NULL || in == NULL){
    fprintf(stderr, WHERESTR " ERROR: %s\n", WHEREARG, strerror(errno));
  }

  int i=0;
  #pragma omp parallel
  #pragma omp for
  for (i=0; i<SAMPLE; i++){
    in[i]=cos(2.0*M_PI*(double)i/10);
  } /*end load */
  fftw_execute(p);

/* transforms of real data have sysmitry. Because of this fftw only computes half the transform (SAMPLE/2+1).
This is why 'out'  is only that large as well as only printing those values. */
#ifndef NDEBUG
  for (i=0; i<ceil(SAMPLE/2+1); i++){
    tmp = sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]);
    printf("%8.8f\n",tmp);
  } /* end print */
#endif

  fftw_flops(p, &add, &mul, &fma);
  printf("Plan for %d samples used: %f add's, %f multiplies, %f fused Multiply-Add\n"
          ,SAMPLE, add, mul, fma);

  fftw_destroy_plan(p);
  fftw_free(in);
  fftw_free(out);
  

return 0;
}
