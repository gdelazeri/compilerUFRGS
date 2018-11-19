#ifndef TAC_H
#define TAC_H

#include "hash.h"
#include "ast.h"

typedef struct tac_node {
    int type;

    HASH_NODE* res;
    HASH_NODE* arg1;
    HASH_NODE* arg2;

    struct tac_node* prev;
    struct tac_node* next;
} TAC;


#define TAC_ADD 1
#define TAC_SUB 2
#define TAC_MUL 3
#define TAC_DIV 4
#define TAC_LT 5
#define TAC_GT 6
#define TAC_LE 7 
#define TAC_GE 8
#define TAC_EQ 9 
#define TAC_NOT 10
#define TAC_AND 11
#define TAC_OR 12

#define TAC_BEGINFUN 13
#define TAC_ENDFUN 14
#define TAC_CALL 15
#define TAC_ARG 16

#define TAC_IFZ 17
#define TAC_JUMP 18
#define TAC_MOVE 19

#define TAC_RET 20
#define TAC_PRINT 21   
#define TAC_READ 22

#define TAC_TEMP 23
#define TAC_LABEL 24
#define TAC_SYMBOL 25

#define TAC_PARAM 26
#define TAC_VECTOR 27
#define TAC_VECTOR_DECLARATION 28

#define TAC_FUN_CALL 29
#define TAC_MOVE_IND 30
#define TAC_GLOBAL_SCALAR 31
#define TAC_GLOBAL_VECTOR 32

TAC* TACCreate(int type, HASH_NODE* res, HASH_NODE* arg1, HASH_NODE* arg2);
TAC* TACJoin(TAC *tac1, TAC *tac2);
TAC* TACReverseList(TAC *list);
void TACPrint(TAC *tac);
void TACPrintList(TAC *list);
char* typeString(int type);
TAC* TACGenerate(AST *node);
TAC* TACGenerateBinOp(int type, TAC* op1, TAC* op2);
TAC* TACGenerateUnaOp(int type, TAC* op1);
TAC* TACGenerateReadVector(HASH_NODE* symbol, TAC* code[]);
TAC* TACGenerateLocalAssig(HASH_NODE* symbol, TAC* code[], int type);
TAC* TACGenerateFuncDefinition(HASH_NODE* symbol, TAC* code[]);
TAC* TACGenerateParameter(HASH_NODE* symbol, TAC* code[]);
TAC* TACGenerateIf(TAC* code[]);
TAC* TACGenerateIfElse(TAC* code[]);
TAC* TACGenerateWhile(TAC* code[]);
TAC* TACGenerateRead(HASH_NODE* symbol);
TAC* TACGenerateFunCall(HASH_NODE* symbol, TAC* code[]);
TAC* TACGenerateReturn(TAC* code[]);
TAC* TACGenerateArgument(TAC* code[]);
TAC* TACGeneratePrint(TAC* code[]);
TAC* TACGenerateGlobalAssig(HASH_NODE* symbol, TAC* code[], int type);

#endif