#include<stdio.h>
#include <mpi.h>
using namespace std;

void star(int* argc, char** argv);

int main(int* argc, char **argv) {
	star(argc, argv);
}

//���������� ������� star, ������� ������ N + 1 ���������(1 ������������ � N ���������)
//� �������� ��������� ������������ ��������, ������� �������� ��������� ���� ��������� ���������
//� ���������� �� ��� ������, ����� ���� ��� �����������(����� M ���).����� ����,
//��� ��� ������� ��������, ��� �������� ����������� ������.

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