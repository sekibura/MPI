#include<stdio.h>
#include <mpi.h>
using namespace std;

void star(int* argc, char** argv);

int main(int* argc, char **argv) {
	star(argc, argv);
}

//Реализуйте функцию star, которая создаёт N + 1 процессов(1 «центральный» и N «крайних»)
//и посылает сообщение центральному процессу, который посылает сообщение всем остальным процессам
//и дожидается от них ответа, после чего это повторяется(всего M раз).После того,
//как все события получены, все процессы заканчивают работу.

void star(int* argc, char** argv) {
	int ProcNum, ProcRank, RecvRank;
	int MainProcRank = 0;
	int M = 1;
	MPI_Status Status;

	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

	for (int i = 0; i < M; i++)
	{

		if (ProcRank == MainProcRank) {
			for (int i = 1; i < ProcNum; i++)
				MPI_Send(&ProcRank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

			for (int i = 1; i < ProcNum; i++) {
				MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				printf("\nAnswer from process %d to %d process \n", RecvRank, ProcRank);
			}
		}
		else
		{
			MPI_Recv(&RecvRank, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			printf("\nMessage received from process %d to %d process \n", RecvRank, ProcRank);
			MPI_Send(&ProcRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
}