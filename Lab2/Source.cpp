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
	double t1, t2, dt;

	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	if(ProcRank==MainProcRank)	
		t1 = MPI_Wtime();

	for (int i = 0; i < M; i++)
	{
	
		if (ProcRank != MainProcRank)
			val = 0;

		MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
		if (ProcRank != MainProcRank) {
			if (val == 1) {
				printf("\n Get msg from main process by %3d\n", ProcRank);
				
			}
			else {
				printf("\n DNT get msg from main process by %3d\n", ProcRank);
			}
		}
		MPI_Reduce(&val, &TotalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

		if ((ProcRank == MainProcRank) ) {
			if (TotalSum == 4) 
				printf("\nSuccess, all answers received \n");
			else
				printf("\Error\n");
			
		}
	}
	if (ProcRank == MainProcRank) 
	{
		t2 = MPI_Wtime();
		dt = t2 - t1;
		printf("\nTIME = %f\n", dt);
	}


	MPI_Finalize();


}