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
    int array[size];
    int buffer[1024];
    MPI_Status status;

    if(rank==0){
        printf("enter the array\n");
        for(int i=0;i<size;i++) scanf("%d",&array[i]);

        int bufsize = (size - 1) * (sizeof(int) + MPI_BSEND_OVERHEAD);
        void *buffer = malloc(bufsize);
        MPI_Buffer_attach(buffer, bufsize);

        for(int i=1;i<size;i++){
        MPI_Bsend(&array[i], 1, MPI_INT, i,i, MPI_COMM_WORLD);
        }
        void *oldbuf;
        int oldsize;
        MPI_Buffer_detach(&oldbuf, &oldsize);
        free(oldbuf);

        printf("computation in root: %d\n", (array[0]*array[0]));
       
    }
    else{
        MPI_Recv(&x, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        if(rank%2==0) x*=x;
        else x=x*x*x;
        printf("computation by rank %d: %d\n", rank, x);
    }
    MPI_Finalize();
    return 0;

}