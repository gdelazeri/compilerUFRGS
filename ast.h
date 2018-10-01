#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#define MAX_SONS 4

#define AST_PROGRAM 1
#define AST_DECLARATION_LIST 2
#define AST_GLOBAL_SCALAR 3
#define AST_GLOBAL_VECTOR 4
#define AST_GLOBAL_VECTOR_VALUES 5
#define AST_FUNCTION 6
#define AST_FUNCTION_PARAMS 7
#define AST_FUNCTION_PARAM 8
#define AST_BLOCK 9
#define AST_COMMAND 10
#define AST_READ 11
#define AST_PRINT 12
#define AST_RETURN 13
#define AST_LOCAL_SCALAR 14
#define AST_LOCAL_VECTOR 15
#define AST_IF 16
#define AST_IF_ELSE 17
#define AST_WHILE 18
#define AST_PRINTABLES 19
#define AST_SYMBOL 20
#define AST_VECTOR 21
#define AST_LE 22
#define AST_GE 23
#define AST_EQ 24
#define AST_OR 25
#define AST_AND 26
#define AST_NOT 27
#define AST_ADD 28
#define AST_SUB 29
#define AST_MUL 30
#define AST_DIV 31
#define AST_LT 32
#define AST_GT 33
#define AST_PARENTHESES 34
#define AST_FUNCTION_CALL 35
#define AST_FUNCTION_CALL_ARGS 36
#define AST_KW_CHAR 37
#define AST_KW_FLOAT 38
#define AST_KW_INT 39

typedef struct ast_node {
    int type;
    HASH_NODE *symbol;
    struct ast_node *son[MAX_SONS];
} AST;

AST *ast_create(int type, HASH_NODE *symbol, AST *s0, AST *s1, AST *s2, AST *s3);
void ast_print(AST *node, int level);
void ast_decompile(FILE* file, AST *node);