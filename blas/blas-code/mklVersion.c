#include <stdio.h>
#include <stdlib.h>
#include <mkl.h>

int main(void){
  MKLVersion pVersion;
  MKLGetVersion(&pVersion);
  printf("mkl version: %d.%d.%d\n"
                       ,pVersion.MajorVersion
                       ,pVersion.MinorVersion
                       ,pVersion.BuildNumber);

  printf("Build: %s\n", pVersion.Build);
  printf("Detected CPU %s\n", pVersion.Processor);

return 0;
}
