#include<mpi.h>
#include<stdio.h>
#include<math.h>

int main(int argc, char *argv[]){

	int x=2;
	int rank,res;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	res= pow(x,rank);
	
	if(rank%2==0){
		printf("Hello\n");
	}
	else printf("WORLD\n");
	
	printf(" Result is %d\n", res);
	
	MPI_Finalize();
	return 0;
}
