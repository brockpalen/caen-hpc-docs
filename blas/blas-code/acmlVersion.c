#include <stdio.h>
#include <stdlib.h>
#include <acml.h>
#ifdef _OPENMP
  #include <omp.h>
#endif

int main(void){
  int *major, *minor, *patch;
  /*acmlversion(major,minor,patch);*/
  acmlinfo();
  /*printf("acml version: %d.%d.%d\n",major, minor, patch);*/

  #ifdef _OPENMP
   printf("\nOpenMP Enabled OMP_NUM_THREADS=%d CPU's of %d CPU's Total\n\n",
           omp_get_max_threads(),
           omp_get_num_procs());
  #endif  /* OpenMP check */

return 0;
}
