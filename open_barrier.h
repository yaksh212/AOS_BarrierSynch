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

    int my_id = omp_get_thread_num();  
    local_sense[my_id] = !local_sense[my_id];
    int my_sense = global_sense;
      #pragma omp atomic
    count--;
    if(count == 0){
     count = omp_get_num_threads();
     global_sense = !global_sense;
   }else{
    while(my_sense == global_sense);
    }


  }


  void init_tournament_barrier(int num_threads){
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


    int i=2;
    for(i;i<=omp_get_num_threads();i=i*2){

     if(current_tid % i == 0){
      array[current_tid].loser_spin = 1;
      while(!(array[current_tid+i/2].loser_spin));

    }
    else{

     array[current_tid].loser_spin = 1;
     while(!array[current_tid].spin);
     array[current_tid].spin = 0;
     array[current_tid].loser_spin = 0;
     break;
   }
  }


  i=omp_get_num_threads();
  for(i;i>=2;i=i/2){

   if(current_tid % i == 0){
    array[current_tid+i/2].spin = 1;
    while((array[current_tid+i/2].spin));
      }
    }

  }

