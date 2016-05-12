OMPFLAGS = -fopenmp
OMPLIBS = -lgomp

CC = gcc
CPPFLAGS = -g -Wall
LDFLAGS = -g -Wall
LDLIBS = $(OMPLIBS)

MPICC = /opt/openmpi-1.4.3-gcc44/bin/mpicc
MPICH = /usr/lib64/openmpi/1.4-gcc
CFLAGS = -I$(MPICH)/include

# all: hello_world communicate_world openmp_mpi
all: openmp_mpi

# hello_world: hello_world.o
# 	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

# communicate_world: communicate_world.o
# 	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

openmp_mpi: mp_mpi.o
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS) $(OMPLIBS)

openmp_mpi.o: mp_mpi.c
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $(OMPFLAGS) $^

clean:
	rm -f *.o openmp_mpi
	# rm -f *.o hello_world communicate_world openmp_mpi
