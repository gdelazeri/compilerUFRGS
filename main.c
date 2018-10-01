#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
extern AST* astTree;

//lex.yy.h
extern FILE *yyin;
int yyparse();


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
    yyparse();

    ast_decompile(fopen(argv[2],"w"), astTree);

    fprintf(stderr, "Parser Complete!");
    printf("\n");

    exit(0);
}