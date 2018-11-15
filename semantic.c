#include "semantic.h"
#include <string.h>

struct fun_node *list = 0;
int semanticError = 0;

int foundSemanticError() {
    return semanticError;
}

void semanticCheck(AST *node) {
    setTypeIdentifiers(node);
    int undeclaredError = checkUndeclared();

    if (undeclaredError == 1) semanticError = 1;
    checkUsage(node);
    checkOperations(node);
}


void setTypeIdentifiers(AST *node) {
    int i;

    if (!node) 
        return;

    if (node->type == AST_GLOBAL_SCALAR)
    {
        if (node->son[1]->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: identifier %s already declared. Line: %d \n", node->son[1]->symbol->text, node->line);
            semanticError = 1;
        }
        else {
            if (node->son[0]->type == AST_KW_CHAR)
                node->son[1]->symbol->dataType = DATATYPE_INTEGER;
            if (node->son[0]->type == AST_KW_FLOAT)
                node->son[1]->symbol->dataType = DATATYPE_FLOAT;
            if (node->son[0]->type == AST_KW_INT) 
                node->son[1]->symbol->dataType = DATATYPE_INTEGER;
            node->son[1]->symbol->type = TYPE_SCALAR;
        }
    }
    else if (node->type == AST_GLOBAL_VECTOR) {
        if (node->son[1]->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: identifier %s already declared. Line: %d \n", node->son[1]->symbol->text, node->line);
            semanticError = 1;
        }
        else {
            if (node->son[0]->type == AST_KW_CHAR)
                node->son[1]->symbol->dataType = DATATYPE_INTEGER;
            if (node->son[0]->type == AST_KW_FLOAT)
                node->son[1]->symbol->dataType = DATATYPE_FLOAT;
            if (node->son[0]->type == AST_KW_INT) 
                node->son[1]->symbol->dataType = DATATYPE_INTEGER;
            node->son[1]->symbol->type = TYPE_VECTOR;
        }
    }
    else if (node->type == AST_FUNCTION) {
        if (node->son[1]->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: identifier %s already declared. Line: %d \n", node->son[1]->symbol->text, node->line);
            semanticError = 1;
        }
        else {
            if (node->son[0]->type == AST_KW_CHAR)
                node->son[1]->symbol->dataType = DATATYPE_INTEGER;
            if (node->son[0]->type == AST_KW_FLOAT)
                node->son[1]->symbol->dataType = DATATYPE_FLOAT;
            if (node->son[0]->type == AST_KW_INT) 
                node->son[1]->symbol->dataType = DATATYPE_INTEGER;
            node->son[1]->symbol->type = TYPE_FUNCTION;
            //node->numberArgs = countSons(node->son[2]);
            //list = funlist_insert(node->son[1]->symbol->text, node->numberArgs, node->son[2], list);
        }
    }
    else if (node->type == AST_FUNCTION_PARAM) {
        if (node->son[1]->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "Semantic ERROR: identifier %s already declared. Line: %d \n", node->son[1]->symbol->text, node->line);
            semanticError = 1;
        }
        else {
            if (node->son[0]->type == AST_KW_CHAR)
                node->son[1]->symbol->dataType = DATATYPE_INTEGER;
            if (node->son[0]->type == AST_KW_FLOAT)
                node->son[1]->symbol->dataType = DATATYPE_FLOAT;
            if (node->son[0]->type == AST_KW_INT) 
                node->son[1]->symbol->dataType = DATATYPE_INTEGER;
            node->son[1]->symbol->type = TYPE_SCALAR;
        }
    }
    else if (node->type == AST_SYMBOL) {
        if (node->symbol->type == SYMBOL_LIT_CHAR)
            node->symbol->dataType = DATATYPE_INTEGER;
        if (node->symbol->type == SYMBOL_LIT_FLOAT)
            node->symbol->dataType = DATATYPE_FLOAT;
        if (node->symbol->type == SYMBOL_LIT_INTEGER)
            node->symbol->dataType = DATATYPE_INTEGER;
    }

    for (i = 0; i < MAX_SONS; ++i)
        setTypeIdentifiers(node->son[i]);
}


void checkUsage(AST *node) {
    int i;

    if (!node) 
        return;

    if (node->type == AST_LOCAL_SCALAR) {
        if (node->son[0]->symbol->type != TYPE_SCALAR) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a scalar. Line %d \n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }
    else if (node->type == AST_LOCAL_VECTOR) {
        if (node->son[0]->symbol->type != TYPE_VECTOR) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a vector. Line %d \n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }
    else if (node->type == AST_FUNCTION_CALL) {
        if (node->son[0]->symbol->type != TYPE_FUNCTION) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a function. Line %d \n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }  
    else if (node->type == AST_VECTOR) {
        if (node->son[0]->symbol->type != TYPE_VECTOR) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a vector. Line %d\n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }
    else if (node->type == AST_READ) {
        if (node->son[0]->symbol->type != TYPE_SCALAR) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a scalar. Line %d\n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }

    for (i = 0; i < MAX_SONS; ++i)
        checkUsage(node->son[i]);
}

// devem ser verificados onde forem usados, em expressões aritméticas, relacionais, lógicas, ou para índices de vetores;
void checkOperations(AST *node)  {
    if (!node) 
        return;

    // verificar se ambos os lados são do mesmo tipo. Mas como saber o tipo?
    if (node->type == AST_LE || node->type == AST_GE || node->type == AST_EQ || node->type == AST_LT || node->type == AST_GT) {

    } else if (node->type == AST_AND || node->type == AST_AND) {

    } else if (node->type == AST_NOT) {

    } else if (node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV) {

    }
    for (int i = 0; i < MAX_SONS; ++i)
        checkOperations(node->son[i]);
}