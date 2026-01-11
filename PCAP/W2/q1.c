#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char* argv[]){
    char word[1024];
    char buff[1024];
    int rank;
    int length;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if(rank==0){
        printf("enter the word\n");
        scanf("%s",word);
        int x=strlen(word);
        MPI_Ssend(&x, 1, MPI_INT, 1,0, MPI_COMM_WORLD);
        MPI_Ssend(word, strlen(word), MPI_CHAR, 1,0, MPI_COMM_WORLD);
        MPI_Recv(word, strlen(word), MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);

        printf("after toggle by other process, word received in root\n%s\n",word);
    }
    else{
        MPI_Recv(&length, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(buff, length, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

        for(int i=0;i<length;i++){
            if(buff[i]>='A' && buff[i]<='Z') buff[i]=tolower(buff[i]);
            else buff[i]=toupper(buff[i]);
        }

        MPI_Ssend(buff, length, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;

}