#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mpi.h"

int num_processes;

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

void dissemination_barrier()
{
	int my_id, my_dst, my_src;
	int tag = 1;
	
	int r_wait=0;
	MPI_Status mpi_result;
	MPI_Request req;
	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	int s_wait=my_id;
	printf("processor %d entered dissemination_barrier\n",my_id );
	int i=0;
	for(i;i<ceil(log2(num_processes));++i)
	{
		my_dst=(my_id+(int)pow(2,i));
		my_dst=mod(my_dst,num_processes);
		my_src=(my_id-(int)pow(2,i));
		my_src=mod(my_src,num_processes);
		printf("processor %d sending to processor %d in round %d\n",my_id,my_dst,i );
		MPI_Isend(&s_wait, 1, MPI_INT, my_dst, tag, MPI_COMM_WORLD, &req);
		printf("processor %d waiting to receive from processor %d in round %d\n",my_id,my_src,i );
		int rc=MPI_Recv(&r_wait, 1, MPI_INT, my_src, tag, MPI_COMM_WORLD, &mpi_result);
		if (rc != MPI_SUCCESS)
		{
			printf("receive failed %d\n",my_id );
			MPI_Finalize();
			exit(1);
		} 
		printf("processor %d received %d from processor %d in round %d\n",my_id,r_wait,my_src,i );
	}

	printf("processor %d leaving dissemination_barrier\n",my_id );
}

void tournament_barrier()
{
	int my_id, my_dst, my_src;
	int tag = 1;
	
	int r_wait=0;
	MPI_Status mpi_result;
	MPI_Request req;
	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	int s_wait=my_id;
	printf("processor %d entered tournament_barrier\n",my_id );
	int i=2;	

	for(i;i<=num_processes;i=i*2)
	{
		if(my_id % i==0)
		{
			my_src=my_id + i/2;
			int rc=MPI_Recv(&r_wait, 1, MPI_INT, my_src, tag, MPI_COMM_WORLD, &mpi_result);
			printf("processor %d received %d from processor %d in round %d\n",my_id,r_wait,my_src,i );
			if (rc != MPI_SUCCESS)
			{
				printf("receive failed %d\n",my_id );
				MPI_Finalize();
				exit(1);
			}	

		}
		else
		{
			my_dst= my_id - i/2;
			my_src=my_dst;
			printf("processor %d sending to processor %d in round %d\n",my_id,my_dst,i );
			MPI_Send(&s_wait, 1, MPI_INT, my_dst, tag, MPI_COMM_WORLD);
			int rc= MPI_Recv(&r_wait, 1, MPI_INT, my_src, tag, MPI_COMM_WORLD, &mpi_result);
			printf("processor %d received %d from processor %d in round %d\n",my_id,r_wait,my_src,i );
			if (rc != MPI_SUCCESS)
			{
				printf("receive failed %d\n",my_id );
				MPI_Finalize();
				exit(1);
			}
			break;
		}
	}

	i=num_processes;
	for(i;i>=2;i=i/2)
	{
		// printf("my id=%d\n",my_id );
		if(my_id % i ==0)
		{
			my_dst= my_id + i/2;
			printf("processor %d sending to processor %d in round %d\n",my_id,my_dst,i );
			MPI_Send(&s_wait, 1, MPI_INT, my_dst, tag, MPI_COMM_WORLD);
		}
	}
}