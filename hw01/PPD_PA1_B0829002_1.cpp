#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {

	int proId = 0;
	int numPro = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &proId);
	MPI_Comm_size(MPI_COMM_WORLD, &numPro);
	proId == 0 ? printf("Hello world!\n") : printf("I love IU and I'm the %d process.\n", proId);
	MPI_Finalize();


}
