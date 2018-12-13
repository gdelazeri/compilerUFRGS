#include <stdio.h>
#include "ast.h"

typedef struct func_list {
    AST* node;
    struct func_list* next;
} FUNC_LIST;

void semanticCheck(AST *node);
void setTypeIdentifiers(AST *node);
int foundSemanticError();
void checkUsage(AST *node);
void checkOperations(AST *node);
int checkPrintable(AST *node);
int checkExpression(AST *node);
int checkConditionalExpression(int type);
int checkArithmeticExpression(int type);
int checkLogicExpression(int type);
void addFunctionToList(AST *node);
int funcArgumentsCheck(AST *funcCall);
AST *findFunctionDeclaration(AST *funcCall);
