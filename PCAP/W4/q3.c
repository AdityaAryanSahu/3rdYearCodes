#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
	int rank, size;
	
	int fsum;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int array[4][4], res[4][4];
	int buf[4], buf2[4];
	int val;

	if(rank == 0){
		printf("enter 4x4 array:\n");
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				scanf("%d", &array[i][j]);
	}

	MPI_Scatter(array, 4, MPI_INT, buf, 4, MPI_INT, 0, MPI_COMM_WORLD );


	MPI_Scan(buf, buf2, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	for(int i=0;i<4;i++)
		printf("%d\t", buf2[i]);

	printf("\n");

	}


