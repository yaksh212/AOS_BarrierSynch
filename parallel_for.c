#include <omp.h>
#include <stdio.h>
#include "open_barrier.h"

int main(int argc, char **argv)
{
  int i,n,x = 0;
  int nthreads=16;
  init_tournament_barrier(nthreads);
  sense_barrier_init(nthreads);
 int b_opt = atoi(argv[1]); 
#pragma omp parallel for shared(x) private(i,n) num_threads(nthreads)
 for(n=0;n<16;n++){ 
 //printf("entered first loop by %d\n",n); 
 for (i = 1; i <= 100; ++i)
   {
   // printf("second\n");
    #pragma omp atomic
    x += 1;
  }
  //printf("entering barrier\n");
 int j;

 double start = omp_get_wtime();
 for(j=0;j<10000;j++){

 printf("j=%d\n",j);
 switch(b_opt){
  case 0: openMP_sense_barrier();break;
  case 1: openmp_tournament_barrier();break;
 }
 //  #pragma omp barrier
}
 double end = omp_get_wtime();
 printf("time taken = %f\n",end-start);
 printf("sum(1 - %d) = %d\n", i - 1, x);

 /* for (i = 1; i <= 10000; ++i)
   {
  //  printf("1-second\n");
    #pragma omp atomic
    x -= 1;
  }*/
}

 // printf("sum(1 - %d) = %d\n", i - 1, x);
  return 0;
}

