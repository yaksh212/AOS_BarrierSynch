#include <stdio.h>
#include <omp.h>
#include "mpi.h"
#include "mpi_barrier.h"
#include "open_barrier.h"

#define NUM_THREADS 4

int main(int argc, char **argv)
{
  int my_id, num_processes, thread_num, num_threads;
  int b_opt1 = atoi(argv[1]); 
  int b_opt2 = atoi(argv[2]);
  init_tournament_barrier(NUM_THREADS);
  sense_barrier_init(NUM_THREADS);
  MPI_Init(&argc, &argv);
  int j;
  MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  omp_set_num_threads(NUM_THREADS);
  // printf("o1=%d o2=%d\n",b_opt1,b_opt2 );
  #pragma omp parallel private(j,thread_num,num_threads) 
	{ 
		double start,end,average;
		thread_num = omp_get_thread_num();
		num_threads = omp_get_num_threads();
		
		for(j=0;j<10000;j++)
		{
			// printf("j=%d\n",j);
			switch(b_opt1)
			{
				case 0:start =omp_get_wtime(); openMP_sense_barrier();end = omp_get_wtime();break;
				case 1:start = omp_get_wtime(); openmp_tournament_barrier();end = omp_get_wtime();break;
			}
			
			average+=(end-start);
			//  #pragma omp barrier
		}
		
		
		printf("average time taken by thread %d of proc %d= %f\n",thread_num,my_id,average/10000);

	}

	double t1, t2; 
	double mpi_avg=0;
	int i;
	for(i=0;i<10000;i++)
	{
		// printf("%d\n",i );
		switch (b_opt2)
		{
			case 0:  t1 = MPI_Wtime(); dissemination_barrier();t2 = MPI_Wtime(); break;
			case 1:  t1 = MPI_Wtime(); tournament_barrier();t2 = MPI_Wtime(); break;
			case 2:  t1 = MPI_Wtime(); MPI_Barrier(MPI_COMM_WORLD);t2 = MPI_Wtime();
		}
		mpi_avg+=(t2-t1);
	}
	 
	printf( "Avg Elapsed time in barrier by proc %d= %f\n", my_id,mpi_avg/10000); 
	//printf("total average for all threads=\n", );

// #pragma omp parallel private(thread_num, num_threads)
//   {
//     num_threads = omp_get_num_threads();
//     thread_num = omp_get_thread_num();

//     printf("Hello World from thread %d:%d of %d procs and %d threads.\n",
//         my_id, thread_num, num_processes, num_threads);
//   } // implied barrier

  MPI_Finalize();
  return 0;
}
