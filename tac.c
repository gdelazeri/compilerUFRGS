#include <stdio.h>
#include <stdlib.h>
#include "tac.h"


TAC* TACCreate(int type, HASH_NODE* res, HASH_NODE* arg1, HASH_NODE* arg2) {
    TAC* tac;

	if (!(tac = (TAC*) calloc(1, sizeof(TAC)))) {
		exit(1);
	}

    tac->type = type;
    tac->res = res;
    tac->arg1 = arg1;
    tac->arg2 = arg2;

    tac->prev = NULL;
    tac->next = NULL;

    return tac;
}

TAC* TACJoin(TAC *tac1, TAC *tac2) {
    if (!tac1) return tac2;
    if (!tac2) return tac1;

    TAC* aux;
    for (aux = tac2; aux->prev != NULL; aux = aux->prev) {}

    aux->prev = tac1;
    tac1->next = aux;
    return tac2;
}

TAC* TACReverseList(TAC *list)  {
    TAC* aux = list;

    if (!list) return NULL;

    while (aux->prev) 
        aux = aux->prev;
    
    return aux;
}

void TACPrint(TAC *tac) {
    if (!tac) return;
    if (tac->type == TAC_SYMBOL) return;
    fprintf(stderr, "(%s) %s | %s | %s\n",
        typeString(tac->type),
        tac->res? tac->res->text : "-",
        tac->arg1? tac->arg1->text : "-",
        tac->arg2? tac->arg2->text : "-");
}

void TACPrintList(TAC *list) {
    for (TAC* aux = list; aux != NULL; aux = aux->next)
        TACPrint(aux);
}


char* typeString(int type) {
    switch (type) {  
        case TAC_ADD:
            return "ADD";
        case TAC_SUB:
            return "SUB";
        case TAC_MUL:
            return "MUL";
        case TAC_DIV:
            return "DIV";
        case TAC_LT:
            return "LT";
        case TAC_GT:
            return "GT";
        case TAC_LE:
            return "LE";
        case TAC_GE:
            return "GE";
        case TAC_EQ:
            return "EQ";
        case TAC_NOT:
            return "NOT";
        case TAC_AND:
            return "AND";
        case TAC_OR:
            return "OR";
        case TAC_BEGINFUN:
            return "BEGIN_FUNC";
        case TAC_ENDFUN:
            return "END_FUNC";
        case TAC_CALL:
            return "CALL";
        case TAC_ARG:
            return "ARG";
        case TAC_IFZ:
            return "IFZ";
        case TAC_JUMP:
            return "JUMP";
        case TAC_MOVE:
            return "MOVE";
        case TAC_RET:
            return "RETURN";
        case TAC_PRINT:
            return "PRINT";
        case TAC_READ:
            return "READ";
        case TAC_LABEL:
            return "LABEL";
        case TAC_PARAM:
            return "PARAM";
        case TAC_VECTOR:
            return "VECTOR_READ";
        case TAC_GLOBAL_SCALAR:
            return "GLOBAL_SCALAR";
        case TAC_GLOBAL_VECTOR:
            return "GLOBAL_VECTOR";
        case TAC_MOVE_IND:
            return "MOVE_IND";
        case TAC_VECTOR_DECLARATION:
            return "VEC_DECL";
        case TAC_SYMBOL:
            return "SYMBOL";
        default:
            return "UNDEF";
    }
}

TAC* TACGenerate(AST *node) {
    if (!node)
        return NULL;

    TAC* code[MAX_SONS];

    for (int i = 0; i < MAX_SONS; ++i) {
        code[i] = TACGenerate(node->son[i]);
    }

    switch (node->type) {
        case AST_SYMBOL:
            return TACCreate(TAC_SYMBOL, node->symbol, NULL, NULL);

        // global assignments
        case AST_GLOBAL_SCALAR:
        case AST_GLOBAL_VECTOR:
            return TACGenerateGlobalAssig(node->son[1]->symbol, code, node->type);
        
        case AST_GLOBAL_VECTOR_VALUES:
            return TACGenerateGlobalAssig(NULL, code, node->type);
            
        // binary operations
        case AST_ADD:
            return TACGenerateBinOp(TAC_ADD, code[0], code[1]);
	    case AST_SUB:
            return TACGenerateBinOp(TAC_SUB, code[0], code[1]);
	    case AST_MUL:
            return TACGenerateBinOp(TAC_MUL, code[0], code[1]);
	    case AST_DIV:
            return TACGenerateBinOp(TAC_DIV, code[0], code[1]);
	    case AST_LT:
            return TACGenerateBinOp(TAC_LT, code[0], code[1]);
	    case AST_GT:
            return TACGenerateBinOp(TAC_GT, code[0], code[1]);
	    case AST_LE:
            return TACGenerateBinOp(TAC_LE, code[0], code[1]);
	    case AST_GE:
            return TACGenerateBinOp(TAC_GE, code[0], code[1]);
	    case AST_EQ:
            return TACGenerateBinOp(TAC_EQ, code[0], code[1]);
	    case AST_AND:
            return TACGenerateBinOp(TAC_AND, code[0], code[1]);
	    case AST_OR:
            return TACGenerateBinOp(TAC_OR, code[0], code[1]);
        
        // unary operations
        case AST_NOT:
            return TACGenerateUnaOp(TAC_NOT, code[0]);
        
        case AST_VECTOR:
            return TACGenerateReadVector(node->son[0]->symbol, code);

        // assignment
        case AST_LOCAL_SCALAR:
        case AST_LOCAL_VECTOR:
            return TACGenerateLocalAssig(node->son[0]->symbol, code, node->type);

        // function declaration and parameters
        case AST_FUNCTION:
            return TACGenerateFuncDefinition(node->son[1]->symbol, code);
        case AST_FUNCTION_PARAM:
           return TACGenerateParameter(node->son[1]->symbol, code);

        // control flow
        case AST_IF:
            return TACGenerateIf(code);
        case AST_IF_ELSE:
            return TACGenerateIfElse(code);
        case AST_WHILE:
            return TACGenerateWhile(code);
        
        // function calls
        case AST_READ:
            return TACGenerateRead(node->son[0]->symbol);
        case AST_FUNCTION_CALL:
            return TACGenerateFunCall(node->son[0]->symbol, code);
        case AST_FUNCTION_CALL_ARGS:
            return TACGenerateArgument(code);

        // prints
        case AST_PRINTABLES:
            return TACGeneratePrint(code);

        // return
        case AST_RETURN:
            return TACGenerateReturn(code);

        default:
            return TACJoin(TACJoin(TACJoin(code[0], code[1]), code[2]), code[3]);
    }

}

TAC* TACGenerateBinOp(int type, TAC* op1, TAC* op2) {
    HASH_NODE* temp = makeTemp();
    TAC* result = TACCreate(type, temp,
        op1? op1->res : NULL,
        op2? op2->res : NULL);

    return TACJoin(TACJoin(op1, op2), result);
}

TAC* TACGenerateUnaOp(int type, TAC* op1) {
    HASH_NODE* temp = makeTemp();
    TAC* result = TACCreate(type, temp,
        op1? op1->res : NULL,
        NULL);

    return TACJoin(op1, result);
}

TAC* TACGenerateReadVector(HASH_NODE* symbol, TAC* code[]) {
    HASH_NODE* temp = makeTemp();
    TAC* index = code[1];
    TAC* read = TACCreate(TAC_VECTOR, temp,
        symbol, index? index->res : NULL); 

    return TACJoin(index, read);
}

TAC* TACGenerateLocalAssig(HASH_NODE* symbol, TAC* code[], int type) {
    if (type == AST_LOCAL_SCALAR) {
        TAC* value = code[1];
        TAC* assignment = TACCreate(TAC_MOVE, symbol,
            value? value->res : NULL, NULL);

        return TACJoin(value, assignment);
    } else {
        TAC* index = code[1];
        TAC* value = code[2];
        TAC* assignment = TACCreate(TAC_MOVE_IND, symbol,
            index? index->res : NULL,
            value? value->res : NULL);

        return TACJoin(TACJoin(index, value), assignment);
    }
}

TAC* TACGenerateFuncDefinition(HASH_NODE* symbol, TAC* code[]) {
    TAC* start = TACCreate(TAC_BEGINFUN, symbol, NULL, NULL);
    TAC* end = TACCreate(TAC_ENDFUN, symbol, NULL, NULL);    
    TAC* type = code[0];
    TAC* params = code[2];
    TAC* body = code[3];

    return TACJoin(TACJoin(TACJoin(TACJoin(type, start), params), body), end);
}

TAC* TACGenerateParameter(HASH_NODE* symbol, TAC* code[]) {
    TAC* type = code[0];
    TAC* param = TACCreate(TAC_PARAM, symbol, NULL, NULL);

    return TACJoin(type, param);
}

TAC* TACGenerateIf(TAC* code[]) {   
    HASH_NODE* _jumpAddr = makeLabel();
    TAC* jumpAddr = TACCreate(TAC_LABEL, _jumpAddr, NULL, NULL);    

    TAC* condition = code[0];
    TAC* command = code[1];

    TAC* ifz = TACCreate(TAC_IFZ, _jumpAddr,
        condition? condition->res : NULL, NULL);

    return TACJoin(TACJoin(TACJoin(condition, ifz), command), jumpAddr);
}

TAC* TACGenerateIfElse(TAC* code[]) {
    HASH_NODE* _elseAddr = makeLabel();
    TAC* elseAddr = TACCreate(TAC_LABEL, _elseAddr, NULL, NULL);

    HASH_NODE* _continueAddr = makeLabel();
    TAC* continueAddr = TACCreate(TAC_LABEL, _continueAddr, NULL, NULL);

    TAC* condition = code[0];
    TAC* thenBlock = code[1];
    TAC* elseBlock = code[2];

    TAC* ifz = TACCreate(TAC_IFZ, _elseAddr,
        condition? condition->res : NULL, NULL);
    TAC* jump = TACCreate(TAC_JUMP, _continueAddr, NULL, NULL);

    return TACJoin(TACJoin(TACJoin(
        TACJoin(TACJoin(TACJoin(condition, ifz), thenBlock), 
        jump), elseAddr), elseBlock), continueAddr);
}

TAC* TACGenerateWhile(TAC* code[]) {
    TAC* condition = code[0];
    TAC* command = code[1];

    HASH_NODE* _whileStart = makeLabel();
    TAC* whileStart = TACCreate(TAC_LABEL, _whileStart, NULL, NULL);


    HASH_NODE* _whileEnd = makeLabel();
    TAC* whileEnd = TACCreate(TAC_LABEL, _whileEnd, NULL, NULL);

    TAC* ifz = TACCreate(TAC_IFZ, _whileEnd,
        condition? condition->res : NULL, NULL);
    TAC* jmpToStart = TACCreate(TAC_JUMP, _whileStart, NULL, NULL);

    return TACJoin(TACJoin(TACJoin(
        TACJoin(TACJoin(whileStart, condition), ifz), command), jmpToStart), whileEnd);
}

TAC* TACGenerateRead(HASH_NODE* symbol) {
    return TACCreate(TAC_READ, symbol, NULL, NULL);
}

TAC* TACGenerateFunCall(HASH_NODE* symbol, TAC* code[]) {
    TAC* args = code[1];
    
    HASH_NODE* result = makeTemp();
    TAC* call = TACCreate(TAC_CALL, result, symbol, NULL);

    return TACJoin(args, call);
}

TAC* TACGenerateReturn(TAC* code[]) {
    TAC* value = code[0];
    TAC* ret = TACCreate(TAC_RET, value? value->res : NULL, NULL, NULL);

    return TACJoin(value, ret);
}

TAC* TACGenerateArgument(TAC* code[]) {
    TAC* arg1 = code[0];
    TAC* arglist = code[1];
    TAC* argument = TACCreate(TAC_ARG, arg1? arg1->res : NULL, NULL, NULL);

    return TACJoin(TACJoin(arg1, argument), arglist);
}

TAC* TACGeneratePrint(TAC* code[]) {
    TAC* arg1 = code[0];
    TAC* arglist = code[1];
    TAC* argument = TACCreate(TAC_PRINT, arg1? arg1->res : NULL, NULL, NULL);

    return TACJoin(TACJoin(arg1, argument), arglist);
}

TAC* TACGenerateGlobalAssig(HASH_NODE* symbol, TAC* code[], int type) {
    if (type == AST_GLOBAL_SCALAR) {
        TAC* value = code[2];
        TAC* assignment = TACCreate(TAC_GLOBAL_SCALAR, symbol,
        value? value->res : NULL, NULL);

        return TACJoin(value, assignment);
    }
    else if (type == AST_GLOBAL_VECTOR) {
        TAC* index = code[2];
        TAC* assignment = TACCreate(TAC_GLOBAL_VECTOR, symbol,
            index? index->res : NULL, NULL);

        return TACJoin(TACJoin(index, assignment), code[3]);
    }
    else if (type == AST_GLOBAL_VECTOR_VALUES) {
        TAC* value = code[0];
        TAC* declaration = TACCreate(TAC_VECTOR_DECLARATION, value? value->res : NULL,
            NULL, NULL);
        
        return TACJoin(TACJoin(value, declaration), code[1]);
    }

}