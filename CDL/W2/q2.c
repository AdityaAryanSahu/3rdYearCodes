#include<stdlib.h>
#include<stdio.h>
#define size 1024
int main(){
    FILE *inp,*out;
    char inpf[size], outf[size];
    printf("enter the input file and output file\n");
    scanf("%s%s", inpf, outf);
    inp = fopen(inpf, "r");
    out = fopen(outf, "w");
    char c = fgetc(inp);
    while(c!=EOF){
        if(c == '#'){
            while(c!='\n') c=fgetc(inp);
        }
        else{
            fputc(c, out);
            c=fgetc(inp);
        }
    }
    fclose(inp);
    fclose(out);
    return 0;


}