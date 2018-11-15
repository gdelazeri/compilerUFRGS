#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "semantic.h"
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
        exit(1);
    }

    FILE* file = fopen(argv[1],"r");
    if(file == NULL) {
        fprintf(stderr, "Erro, ao ler arquivo!");
        exit(2);
    } else {
        yyin = file;
    }

    initMe();
    yyparse();

    if (foundSemanticError() == 1)
    {
        fprintf(stderr, "Semantic ERROR(s) found: unable to compile\n");
        exit(4);
    }
    fprintf(stderr, "Semantic check finished successfully!\n");
    

    fprintf(stderr, "Parser Complete!");
    printf("\n");

    exit(0);
}