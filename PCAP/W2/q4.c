#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char* argv[]){
    int rank,size;
    int x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if(rank==0){
        printf("enter the number\n");
        scanf("%d",&x);
        MPI_Send(&x, 1, MPI_INT, 1,1, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
        printf("final x value in root: %d\n", x);
       
    }
    else{
        MPI_Recv(&x, 1, MPI_INT, rank-1, rank, MPI_COMM_WORLD, &status);
        printf("x value received by rank %d: %d\n", rank, x);
        x++;
        if(rank == size-1)
        MPI_Send(&x, 1, MPI_INT, 0,0, MPI_COMM_WORLD);
        else MPI_Send(&x, 1, MPI_INT, rank+1,rank+1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;

}