#include<stdio.h>
#include<mpi.h>
#include<unistd.h>
#include<stdlib.h>
void ErrorHandler(int code)
{
	if(code!=MPI_SUCCESS)
	{
		char string[100];
		int n;
		
		
		MPI_Error_string(code,string,&n);
		printf("Error is hahaah: %s\n",string);
		
	}
	return;
}

int main(int argc, char * argv[])
{
	int err,size,rank,n,Mc;
	MPI_Init(&argc,&argv);
	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
	
	err=MPI_Comm_rank(Mc,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	
	
	int i,ans,fact,f;
	
	f=rank+1;
	MPI_Scan(&f,&fact,1,MPI_INT,MPI_PROD,MPI_COMM_WORLD);
	MPI_Scan(&fact,&ans,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	ErrorHandler(err);
	
	if(rank==size-1)
		printf("Result is %d\n",ans);
		
	MPI_Finalize();
	return 0;
}


