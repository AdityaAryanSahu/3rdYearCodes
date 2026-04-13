#include<stdio.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char* argv[]){
	int rank, size;
	
	int fsum;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	char str[1024], res[1024];
	
	char ch;

	if(rank == 0){
			printf("enter string of length %d\n", size);
			scanf("%s", str);
	}
	MPI_Scatter(&str, 1, MPI_CHAR, &ch, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

	char buf[rank+2];
	for(int i=0;i<rank+1;i++)
		buf[i]=ch;
	buf[rank+1]='\0';


	MPI_Send(buf, rank+2, MPI_CHAR, 0, rank, MPI_COMM_WORLD);

	if(rank==0){
		res[0]=str[0];
		int len=1;
		for(int i=1;i<size;i++){
		MPI_Recv(&res[len], i+2, MPI_CHAR, i,i,MPI_COMM_WORLD, &status );
		len=len+i+1;
	}
	res[len+1]='\0';
	printf("%s\n", res);

	}
}