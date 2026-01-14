#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>

int findNoVow(char str[]){
    int count=0;
    for(int i=0;i<strlen(str);i++){
    	str[i]=tolower(str[i]);
        if(str[i]!='a' && str[i]!='e' && str[i]!='i' &&str[i]!='o' &&str[i]!='u') count++;
        }
    return count;
}

int main(int argc, char* argv[]){
    int rank,size;
    int x, chunk;
    char word[1024];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int buff[size];
    MPI_Status status;

    if(rank==0){
        int ch;
        do{
        printf("enter the string\n");
        scanf("%s", word);
        chunk= strlen(word)/size;
        ch=strlen(word)%size;
        if(ch) printf("enter string such that its length divisible by %d\n",size);
         }while(ch!=0);
    }
     MPI_Bcast(&chunk,1, MPI_INT, 0, MPI_COMM_WORLD);
     char temp[chunk+1];
    MPI_Scatter(word, chunk, MPI_CHAR, temp, chunk, MPI_CHAR, 0,MPI_COMM_WORLD);
    temp[chunk]='\0';
    printf("string received by rank %d: %s\n", rank, temp);
    x= findNoVow(temp);
    MPI_Gather(&x, 1, MPI_INT, buff, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0){
    sleep(0.5);
        int sum=0;
        for(int i=0;i<size;i++) sum+=buff[i];

        printf("final non vowel count in string %s: %d\n", word, sum);
    }
    MPI_Finalize();
    return 0;

}
