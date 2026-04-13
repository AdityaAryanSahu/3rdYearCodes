 #include<mpi.h>
#include<stdio.h>
#include<math.h>

int main(int argc, char *argv[]){

	int x=2, y=10;
	int rank,res;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	switch(rank % 4){
	
		case 0:res=x+y;break;
		case 1: res=x-y; break;
		case 2: res=x*y; break;
		case 3: res= y/x; break;
	}
	printf("result by rank %d : %d\n", rank, res);
	
	MPI_Finalize();
	return 0;
}
