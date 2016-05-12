#include <stdio.h>
#include "mpi.h"
#include "mpi_barrier.h"
#include "pthread.h"

int count=0;
int main(int argc, char **argv)
{
  // int my_id, num_processes;
  // pthread_mutex_t g_num_prod_lock;
  MPI_Init(&argc, &argv);
  int i;
  // int number = rand() % 10000 + 1;
  // while(number)
  // {
  // 	number-=number;
  // }
  // dissemination_barrier();
   for (i = 1; i <= 10000; ++i)
   {
   // printf("second\n");
    // pthread_mutex_lock(&g_num_prod_lock);
    count += 1;
    // pthread_mutex_unlock(&g_num_prod_lock);
  }
  printf("count before second=%d\n",count);
  // MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
  // MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  // dissemination_barrier();
  tournament_barrier();
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

