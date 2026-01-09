#include<stdio.h>
#include<stdlib.h>
#define size 1024
int main(){
    FILE *input, *output;
    char input_file[size], output_file[size];
    scanf("%s%s", input_file, output_file);
    input = fopen(input_file, "r");
    output = fopen(output_file, "w+");
    if(input==NULL || output == NULL){}
    else{

    char c = fgetc(input);
    while(c!=EOF){
        if(c==' '){
            fputc(c,output);
            while(c==' ') c=fgetc(input);
        }
        else{
            fputc(c,output);
            c=fgetc(input);
        }

    }
    fclose(input);
    fclose(output);
}
    return 0;


}