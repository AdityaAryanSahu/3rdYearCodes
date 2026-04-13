#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int row = 1, col = 1;

typedef struct{
    int row, col;
    char lexeme[100];
    char type[100];
} token;

token getNextToken(FILE* fp){
    token tkn;
    char buf[100];

    while(1){
        char c = fgetc(fp);

        // EOF
        if(c == EOF){
            strcpy(tkn.type, "EOF");
            return tkn;
        }

        // skip whitespace
        if(isspace(c)){
            if(c == '\n'){ row++; col = 1; }
            else col++;
            continue;
        }

        tkn.row = row;
        tkn.col = col;

        // comments <!-- -->
        if(c == '<'){
            char d = fgetc(fp);

            if(d == '!'){
                char e = fgetc(fp);
                char f = fgetc(fp);

                if(e == '-' && f == '-'){
                    char p = fgetc(fp), q = fgetc(fp);

                    while(p != EOF){
                        if(p == '-' && q == '-'){
                            char r = fgetc(fp);
                            if(r == '>') break;
                            else{
                                p = q;
                                q = r;
                                continue;
                            }
                        }
                        p = q;
                        q = fgetc(fp);
                    }
                    continue;
                }
                else{
                    ungetc(f, fp);
                    ungetc(e, fp);
                    ungetc(d, fp);
                }
            }
            else{
                ungetc(d, fp);
            }

            tkn.lexeme[0] = '<';
            tkn.lexeme[1] = '\0';
            strcpy(tkn.type, "LT");
            col++;
            return tkn;
        }

        if(c == '>'){
            strcpy(tkn.lexeme, ">");
            strcpy(tkn.type, "GT");
            col++;
            return tkn;
        }

        if(c == '/'){
            strcpy(tkn.lexeme, "/");
            strcpy(tkn.type, "SLASH");
            col++;
            return tkn;
        }
        // attribute value "..."
            if(c == '"'){
                int i = 0;
                c = fgetc(fp);
                while(c != '"' && c != EOF){
                    buf[i++] = c;
                    c = fgetc(fp);
                }
                buf[i] = '\0';

                strcpy(tkn.lexeme, buf);
                strcpy(tkn.type, "STRING");
                return tkn;
            }

            // =
            if(c == '='){
                strcpy(tkn.lexeme, "=");
                strcpy(tkn.type, "EQ");
                return tkn;
            }
        // tag name
        if(isalpha(c)){
            int i = 0;
            while(isalnum(c)){
                buf[i++] = c;
                c = fgetc(fp);
            }
            buf[i] = '\0';
            ungetc(c, fp);

            strcpy(tkn.lexeme, buf);
            strcpy(tkn.type, "ID");
            col += strlen(buf);
            return tkn;
        }

        // TEXT (important: ignore spaces)
        if(c != '<' && !isspace(c)){
            int i = 0;
            while(c != EOF && c != '<' && c != '>' && !isspace(c)){
                buf[i++] = c;
                c = fgetc(fp);
            }
            buf[i] = '\0';
            ungetc(c, fp);

            strcpy(tkn.lexeme, buf);
            strcpy(tkn.type, "STRING");
            col += strlen(buf);
            return tkn;
        }
    }
}