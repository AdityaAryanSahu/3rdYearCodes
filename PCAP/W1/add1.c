#include<mpi.h>
#include<stdio.h>


int rev(int n){
	int sum=0;
	while(n>0){
	sum=sum*10+n%10;
	n/=10;
	
	}
	return sum;
}
int main(int argc, char *argv[]){

	int rank,res;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	int arr[]={18,523,301, 1234, 2, 14 ,108, 150, 1928};
	
	res=rev(arr[rank]);
	printf(" rank %d has the result %d\n", rank, res);
	
	
	MPI_Finalize();
	return 0;
}
