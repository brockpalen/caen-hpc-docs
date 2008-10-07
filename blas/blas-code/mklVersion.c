#include <stdio.h>
#include <stdlib.h>
#include <mkl.h>
#ifdef _OPENMP
  #include <omp.h>
#endif

int main(void){
  MKLVersion pVersion;
  MKLGetVersion(&pVersion);
  printf("mkl version: %d.%d.%d\n"
                       ,pVersion.MajorVersion
                       ,pVersion.MinorVersion
                       ,pVersion.BuildNumber);

  printf("Build: %s\n", pVersion.Build);
  printf("Detected CPU %s\n", pVersion.Processor);

  #ifdef _OPENMP
   printf("\nOpenMP Enabled OMP_NUM_THREADS=%d CPU's of %d CPU's Total\n\n",
           omp_get_max_threads(),
           omp_get_num_procs());
  #endif  /* OpenMP check */

return 0;
}
