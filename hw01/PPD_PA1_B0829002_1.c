#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char** argv) {
	int proId = 0, numPro = 0;
	double startTime;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &proId);
	MPI_Comm_size(MPI_COMM_WORLD, &numPro);
	startTime = MPI_Wtime();
	char buffer[1024][numPro];
	if(proId == 0) {
		// this section is for node manager
		for(int i=1;i<numPro;i++) {
			// request part
			sprintf(buffer[i], "Hi rank %d, I'm 廖洺玄 from Parallel Programming Design Course in 2024", i);
			MPI_Send(buffer[i], strlen(buffer[i]), MPI_BYTE, i, 0, MPI_COMM_WORLD);
			// get response part
			char response[1024];
			MPI_Recv(response, 1024, MPI_BYTE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("[MPI_Wtime():%f] Rank 0 got message from rank %d: '%s'\n", MPI_Wtime() - startTime, i, response);
		}
	} else {
		// this section is for execution of the node children
		// recieve part
		char data[1024] = {0};
		MPI_Recv(data, 1024, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("[MPI_Wtime():%f] Rank %d got message from rank 0: '%s'\n", MPI_Wtime() - startTime , proId, data);
		// response part
		sprintf(data, "Rank %d received. Thank you!", proId);
		MPI_Send(data, strlen(data), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
	}
	// free the buffer
	MPI_Finalize();
}
