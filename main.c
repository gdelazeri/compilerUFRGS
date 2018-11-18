#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "semantic.h"
#include "tac.h"
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
    if(argc < 3) {
        fprintf(stderr, "Missing arguments.\n");
        fprintf(stderr, "Usage: ./etapa5 input.txt output.txt\n");
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
    fprintf(stderr, "Syntax check finished successfully!\n");

    if (foundSemanticError() == 1)
    {
        fprintf(stderr, "Semantic ERROR(s) found: unable to compile\n");
        exit(4);
    }
    fprintf(stderr, "Semantic check finished successfully!\n");
    
    TAC* tac = TACGenerate(astTree);
    TAC* rev = TACReverseList(tac);
    TACPrintList(rev);

    fprintf(stderr, "Parser Complete!");
    printf("\n");

    exit(0);
}