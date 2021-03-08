#include<stdio.h>
#include <mpi.h>
using namespace std;

void star(int* argc, char** argv);

int main(int* argc, char **argv) {
	star(argc, argv);
}
//TODO

//Реализуйте функцию star, которая создаёт N + 1 процессов(1 «центральный» и N «крайних»)
//и посылает сообщение центральному процессу, который посылает сообщение всем остальным процессам
//и дожидается от них ответа, после чего это повторяется(всего M раз).После того,
//как все события получены, все процессы заканчивают работу.

//Модифицировать программу, написанную на Л.Р.№1 так чтобы она работала на основе обобщенной передачи сообщений.
//Результаты работы сравнить(с результатами полученными в Л.Р.№2) и занести в отчет.


void star(int* argc, char** argv) {
	int ProcNum, ProcRank, RecvRank;
	int MainProcRank = 0;
	int M = 1;
	MPI_Status Status;
	int* valMain = nullptr;
	int valSlaves = 0;
	double t1, t2, dt;

	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

	if (ProcRank == MainProcRank)
		t1 = MPI_Wtime();

	valMain = new int[ProcNum];
	for (int i = 0; i < M; i++)
	{
		for (int i = 0; i < ProcNum; i++)
		{
			if (ProcRank == MainProcRank)
				valMain[i] = 1;
			else
				valMain[i] = 0;			
		}
	
		// send message for all
		MPI_Scatter(valMain, 1, MPI_INT, &valSlaves, 1, MPI_INT, 0, MPI_COMM_WORLD);

		//check recive from main
		if (ProcRank != MainProcRank && valSlaves == 1) {
			printf("Message from MainProc is received by %d process\n", ProcRank);
			// send message from all to main
			MPI_Gather(&valSlaves, 1, MPI_INT, valMain, 1, MPI_INT, 0, MPI_COMM_WORLD);
		}
			
		//check recive from all by main
		if (ProcRank == MainProcRank) {
			bool a = true;
			for (int i = 0; i < ProcNum; i++)
			{
				a = a && (valMain[i] == 1);
			}
			if(a)
				printf("Success\n");
			else
				printf("Error\n");
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