#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char* argv[]){
    int rank,size;
    int x, chunk;
    char word1[1024], word2[1024], finalW[1024];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);;
    MPI_Status status;

    if(rank==0){
        int ch;
        do{
        printf("enter the strings of same length\n");
        scanf("%s%s", word1, word2);
        chunk= strlen(word1)/size;
        ch=strlen(word1)%size;
        if(ch) printf("enter strings such that its length divisible by %d and equal length\n",size);
         }while(ch!=0 || (strlen(word1)!=strlen(word2)));
        
    }
     MPI_Bcast(&chunk,1, MPI_INT, 0, MPI_COMM_WORLD);
     char temp1[chunk+1], temp2[chunk+1], final[chunk*2+1];
    MPI_Scatter(word1, chunk, MPI_CHAR, temp1, chunk, MPI_CHAR, 0,MPI_COMM_WORLD);
    MPI_Scatter(word2, chunk, MPI_CHAR, temp2, chunk, MPI_CHAR, 0,MPI_COMM_WORLD);
    temp1[chunk]='\0';
    temp2[chunk]='\0';
    printf("string received by rank %d: %s and %s\n", rank, temp1, temp2);
    int j=0,k=0;
    for(int i=0;i<chunk*2;i++){ 
        if(i%2==0) final[i]=temp1[j++];
        else final[i]=temp2[k++];
    }
    final[chunk*2]='\0';
    printf("string former by rank %d: %s \n", rank, final);
    MPI_Gather(&final, chunk*2, MPI_CHAR, finalW, chunk*2, MPI_CHAR, 0, MPI_COMM_WORLD);
    if(rank==0){
        finalW[2*chunk*size]='\0';
        printf("final string in root: %s\n", finalW);
    }
    MPI_Finalize();
    return 0;

}