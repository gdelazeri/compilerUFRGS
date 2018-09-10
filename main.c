#include <stdio.h>
#include <stdlib.h>

//lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;


int isRunning(void);
void initMe(void);
int getLineNumber();

int main(int argc, char** argv)
{
    int token = 0;
    if(argc < 2) {
        fprintf(stderr, "Erro, falta 1 argumento! Indique o nome do arquivo a ser lido");
        exit(0);
    }

    FILE* file = fopen(argv[1],"r");
    if(file == NULL) {
        fprintf(stderr, "Erro, ao ler arquivo!");
        exit(1);
    } else {
        yyin = file;
    }

    initMe();
    while (isRunning())
    {
        token = yylex();
        if(!isRunning()) {
            break;
        }
       fprintf(stderr," Na linha %d temos o lexema \" %s \" que representa o token %d\n", getLineNumber(), yytext, token);
    }
    printf("\n");
    return 1;
}