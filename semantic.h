#include <stdio.h>
#include "ast.h"

void semanticCheck(AST *node);
void setTypeIdentifiers(AST *node);
int foundSemanticError();
void checkUsage(AST *node);
void checkOperations(AST *node);
