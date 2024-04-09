#include <stdio.h>
#include <string.h>
#include "mpi.h"
#define maxMessageLength 1024

int main(int argc, char** argv) {
	int proId = 0, numPro = 0;
	double startTime;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &proId);
	MPI_Comm_size(MPI_COMM_WORLD, &numPro);
	startTime = MPI_Wtime();
	char sendBuffer[numPro][maxMessageLength];
	char recvBuffer[maxMessageLength];
	char gatherBuffer[numPro][maxMessageLength]; 
	if (proId == 0) {
        // Only the root initializes the send buffer
        for (int i = 0; i < numPro; i++)
            snprintf(sendBuffer[i], maxMessageLength, "Hi rank %d, I'm 廖洺玄 from Parallel Programming Design Course in 2024", i);
    }

	MPI_Scatter(sendBuffer, maxMessageLength, MPI_CHAR, recvBuffer, maxMessageLength, MPI_CHAR, 0, MPI_COMM_WORLD);
	if(proId != 0) {
		printf("[MPI_Wtime():%f] Rank %d got message from rank 0: '%s'\n", MPI_Wtime() - startTime ,proId, recvBuffer);
		snprintf(recvBuffer, maxMessageLength, "Rank %d received. Thank you!", proId);
	}

	MPI_Gather(recvBuffer, maxMessageLength, MPI_CHAR, gatherBuffer, maxMessageLength, MPI_CHAR, 0, MPI_COMM_WORLD);
	if(proId == 0) {
		for(int i=1;i<numPro;i++)
			printf("[MPI_Wtime():%f] Rank 0 got message from rank %d: '%s'\n", MPI_Wtime() - startTime, i, gatherBuffer[i]);
	}


	MPI_Finalize();
}
