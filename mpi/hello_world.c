#include <stdio.h>
#include "mpi.h"
#include "mpi_barrier.h"
#include "pthread.h"
#include <time.h>

int count=0;
int main(int argc, char **argv)
{
  // int my_id, num_processes;
  // pthread_mutex_t g_num_prod_lock;
  int b_option  =  atoi(argv[1]); 
  MPI_Init(&argc,&argv);
  int i;
  // int number = rand() % 10000 + 1;
   int my_rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  // while(number)
  // {
  // 	number-=number;
  // }
  // dissemination_barrier();
   for (i = 1; i <= 10; ++i)
   {
   // printf("second\n");
    // pthread_mutex_lock(&g_num_prod_lock);
    count += 1;
    // pthread_mutex_unlock(&g_num_prod_lock);
  }
 
  printf("count before second=%d\n",count);
  // MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
  
  // double start = (double)clock();
  double t1, t2; 
  t1 = MPI_Wtime(); 
 for(i=0;i<10000;i++){
  // printf("%d\n",i );
  switch (b_option){
        case 0:  dissemination_barrier(); break;
        case 1:  tournament_barrier(); break;
        case 2:  MPI_Barrier(MPI_COMM_WORLD);
   }
  }
  t2 = MPI_Wtime(); 
  printf( "Elapsed time is %f\n", t2 - t1 ); 
  // double end = (double)clock();
  // printf("my rank = %d  time taken = %f\n",my_rank,(end-start));
  // tournament_barrier();
   for (i = 1; i <= 10000; ++i)
   {
   // printf("second\n");
    // pthread_mutex_lock(&g_num_prod_lock);
    count -= 1;
    // pthread_mutex_unlock(&g_num_prod_lock);
  }
  printf("count=%d\n",count);
  // printf("Hello World from processes %d of %d\n", my_id, num_processes);
  // while(1);
  MPI_Finalize();
  return 0;
}

