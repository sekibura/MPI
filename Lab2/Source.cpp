#include<stdio.h>
#include <mpi.h>
using namespace std;

void star(int* argc, char** argv);

int main(int* argc, char **argv) {
	star(argc, argv);
}
//tasks:

//���������� ������� star, ������� ������ N + 1 ���������(1 ������������ � N ���������)
//� �������� ��������� ������������ ��������, ������� �������� ��������� ���� ��������� ���������
//� ���������� �� ��� ������, ����� ���� ��� �����������(����� M ���).����� ����,
//��� ��� ������� ��������, ��� �������� ����������� ������.

//�������������� ���������, ���������� �� �.�.�1,
//��� ����� ��� �������� �� ������ ������������ �������� ���������.
//���������� ������ �������� � ������� � �����.

void star(int* argc, char** argv) {
	int ProcNum, ProcRank, RecvRank;
	int MainProcRank = 0;
	int TotalSum = 0;
	int M = 1;
	int val = 1;

	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

	for (int i = 0; i < M; i++)
	{
	
		val = 1;
		MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Reduce(&val, &TotalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
		if(ProcRank == MainProcRank)
			printf("\n Answers from process = %3d\n", TotalSum-1);


	
	}
	
	MPI_Finalize();
}