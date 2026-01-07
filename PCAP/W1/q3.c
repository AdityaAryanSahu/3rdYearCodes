#include<mpi.h>
#include<stdio.h>
#include<string.h>


	
int main(int argc, char *argv[]){

	char str[]= "ADITYA";
	int rank,res;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank>=strlen(str)) { printf("error as rank greater than the string length\n"); exit(0);}
	
	if(str[rank]>='A' && str[rank]<='Z') str[rank]+=32;
	else str[rank]-=32;
	
	printf("toggle by rank %d is %s\n", rank,str);
	
	MPI_Finalize();
	return 0;
}
