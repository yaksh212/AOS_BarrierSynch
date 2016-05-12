﻿# AOS_BarrierSynch

Contributors : Yakshdeep Kaul, Satyajeet Gawas

Barrier Implementation

OpenMP Barrier Implementation - openmp_barrier.h

MPI Barrier Implementation – mpi_barrier.h

make all : to compile all test programs

Running programs

OpenMP barriers test

./openmp_test (barrier_type) (num_threads)

barrier_type : 0 – Centralized Barrier

1 – Tournament Barrier

num_threads – number of OpenMP threads

To run all configurations of OpenMP barriers, you can run the script

./run_omp.sh

MPI barriers test

./mpi_test (barrier_type)

barrier_type : 0 – Dissemination Barrier

1 – Tournament Barrier

2 – Default

To run all configurations of OpenMP barriers, you can run the script

./run*.sh

Where * = 2,4,8 for 2,4 and 8 nodes respectively

OpenMP and MPI barriers test

./omp_mpi (omp_barrier) (mpi_barrier) (num_threads)

omp_barrier : 0 – Centralized Barrier

1 – Tournament Barrier

mpi_barrier : 0 – Dissemination Barrier

1 – Tournament Barrier

2 - Default

num_threads – number of OpenMP threads

To run all combinations discussed in report

./run_comb.sh
