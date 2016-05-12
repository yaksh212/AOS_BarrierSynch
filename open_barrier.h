#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int num_threads;
int count;
int init=0;
int *local_sense;
int global_sense;
int is_init_complete=0;
int c = 0,wait=0;


typedef struct thread_info{
   int tid;
   int loser_spin;
   int spin;
}thread_info;

thread_info *array;


void sense_barrier_init(int count_d){
	//count = omp_get_num_threads();
	//local_sense = (bool *)malloc(sizeof(bool)*count);
	//int i=0;
	/*for(i;i<count;i++){
		local_sense[i] = true;
	}*/
        count = count_d;
	printf("%d\n",count);
	global_sense = 1;
        local_sense = (int *)malloc(sizeof(int)*count);
        int i=0;
        for(i;i<count;++i){
		local_sense[i] = 1;
	}
}

void openMP_sense_barrier(){
  
  //if(!__synch_fetch_and_add(init,1)){
 /* if(!init){
  	sense_barrier_init();
	init = 1;
        is_init_complete = 1;
  }
 // while(!is_init_complete);
 */
  int my_id = omp_get_thread_num();  
  local_sense[my_id] = !local_sense[my_id];
  int my_sense = global_sense;
  #pragma omp atomic
  count--;
  if(count == 0){
  	count = omp_get_num_threads();
  	//global_sense = local_sense[my_id];
  	global_sense = !global_sense;
  }else{
//	printf("count = %d thread = %d my_sense = %d global_sense = %d\n",count,omp_get_thread_num(),my_sense,global_sense);  
//	while(local_sense[my_id] != global_sense);
        while(my_sense == global_sense);
    // printf("thread %d leaving barrier\n",omp_get_thread_num());
  }


}


void init_tournament_barrier(int num_threads){
 // int num_threads = omp_get_num_threads();
 array = malloc(sizeof( thread_info)*num_threads);
 int i=0;
 for(i;i<num_threads;i++){
  thread_info *node = (thread_info *)malloc(sizeof(thread_info));
  node->tid = i;
  node->loser_spin = 0;
  node->spin = 0;
  array[i] = *node;
  wait=0;
 }
}

void openmp_tournament_barrier(){
  int current_tid = omp_get_thread_num();
 // if(!init){

 //  printf("thread %d entered init\n",current_tid );
 //   init_tournament_barrier();
 //   init = 1;
 // } 
 
 int i=2;
// printf("thread %d entered barrier\n",current_tid );
 // printf("total threads=%d\n",omp_get_num_threads() );
 for(i;i<=omp_get_num_threads();i=i*2){
     
     if(current_tid % i == 0){
 	// printf("l1 - %d\n",current_tid);
        array[current_tid].loser_spin = 1;
        // printf("thread %d spinning in l1 on %d with array[current_tid+i/2].loser_spin=%d\n",current_tid,current_tid+i/2,array[current_tid+i/2].loser_spin );
        while(!(array[current_tid+i/2].loser_spin))
        {
      // printf("thread %d spinning in l1 on %d\n",current_tid,current_tid+i/2 );
        }
      }else{
        
       array[current_tid].loser_spin = 1;
 	      // printf("l2 - %d setting loser spin =%d\n",current_tid,array[current_tid].loser_spin);
       while(!array[current_tid].spin);
       array[current_tid].spin = 0;
       array[current_tid].loser_spin = 0;
 	// printf("l3 - %d\n",current_tid);
       break;
      }
}
// printf("should be zero %d\n",current_tid);
/*i=log2(omp_get_num_threads())-1; 
for(i;i>=0;--i){
  int pow2 = (int)pow(2,i);
  if(current_tid == 0){
   
      array[current_tid+pow2].spin = 1;
      array[current_tid+pow2].loser_spin = 0;
  #pragma omp atomic
     c++; 
  }else if(current_tid %2 !=0)
     continue;
 else{
    int pow21 = (int)pow(2,i-1);
    if(current_tid%pow2==0 && i-1>=0 && array[current_tid+pow21].spin !=1)
     {
       array[current_tid+pow21].spin = 1;
       array[current_tid+pow21].loser_spin = 0;
  #pragma omp atomic
       c++;
     }
  }  
 }
 // printf("%d\n",c);	
 // #pragma omp atomic
 // wait++;
 // printf("value of wait=%d\n",wait );
 // while(wait!=omp_get_num_threads());	
 //printf("thread %d leaving barrier\n",current_tid );
 // if(current_tid==0)
 // {
 //  wait=0;
 // }
 // wait=0;
*/
 

  i=omp_get_num_threads();
// printf("thread %d entered barrier\n",current_tid );
 // printf("total threads=%d\n",omp_get_num_threads() );
 for(i;i>=2;i=i/2){
     
     if(current_tid % i == 0){
 	// printf("l1 - %d\n",current_tid);
        array[current_tid+i/2].spin = 1;
        // printf("thread %d spinning in l1 on %d with array[current_tid+i/2].loser_spin=%d\n",current_tid,current_tid+i/2,array[current_tid+i/2].loser_spin );
        while((array[current_tid+i/2].spin))
        {
      // printf("thread %d spinning in l1 on %d\n",current_tid,current_tid+i/2 );
        }
      }
}
/* printf("should be zero %d\n",current_tid);
 for(i=1;i<omp_get_num_threads();i++){
   array[i].spin = 1;
 }*/

}

