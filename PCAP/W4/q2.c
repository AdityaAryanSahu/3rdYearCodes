#include<stdio.h>
#include<mpi.h>

int search(int buf[], int val){
	int count=0;
	for(int i=0;i<3;i++) if(buf[i]== val) count++;

	return count;
 } 

int main(int argc, char* argv[]){
	int rank, size;
	
	int fsum;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int array[3][3];
	int buf[3];
	int val;

	if(rank == 0){
		printf("enter 3x3 array:\n");
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				scanf("%d", &array[i][j]);

		printf("enter val to be searched:\n");	

		scanf("%d", &val);
	}
	MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	MPI_Scatter(array, 3, MPI_INT, buf, 3, MPI_INT, 0, MPI_COMM_WORLD );

	int count = search(buf, val);

	MPI_Reduce(&count, &fsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


	if(rank == 0){
		printf("final count: %d\n", fsum);
	}

}