#include "semantic.h"
#include <string.h>

FUNC_LIST *func_list = NULL;
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
    if (!node) 
        return;

    // se o tipo é uma inicialização global de variável escalar, primeiramente checa-se se o filho[1] (que é o identificador)
    // contem tipo diferente de SYMBOL_IDENTIFIER. Se sim, quer dizer que esse processo já foi feito para uma variável
    // com este mesmo nome e estamos em um caso de dupla declaração. Se não, seta-se o tipo e o dataType desse 
    // indentificador de acordo com o tipo do filho[0] (que representa a palavra reservada de tipo -> int, char ou float).
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
    // se o tipo é uma inicialização global de variável vetor.
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
    // se o tipo é uma inicialização de variável função.
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
            addFunctionToList(node);
        }
    }
    // se o tipo é uma inicialização de variável de parâmetro de função, dentro da inicialização da mesma.
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
    // se o tipo é um símbolo, seta-se o seu dataType de acordo com seu tipo.
    else if (node->type == AST_SYMBOL) {
        if (node->symbol->type == SYMBOL_LIT_CHAR)
            node->symbol->dataType = DATATYPE_INTEGER;
        if (node->symbol->type == SYMBOL_LIT_FLOAT)
            node->symbol->dataType = DATATYPE_FLOAT;
        if (node->symbol->type == SYMBOL_LIT_INTEGER)
            node->symbol->dataType = DATATYPE_INTEGER;
    }

    // percorre todos os filhos.
    for (int i = 0; i < MAX_SONS; ++i)
        setTypeIdentifiers(node->son[i]);
}


void checkUsage(AST *node) {
    if (!node) 
        return;

    // se o tipo é uma atribuição local de variável escalar, verifica se o filho[0] (identificador) é do tipo escalar.
    if (node->type == AST_LOCAL_SCALAR) {
        if (node->son[0]->symbol->type != TYPE_SCALAR) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a scalar. Line %d \n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }
    // se o tipo é uma atribuição local de variável vetor, verifica se o filho[0] (identificador) é do tipo vetor.
    else if (node->type == AST_LOCAL_VECTOR) {
        if (node->son[0]->symbol->type != TYPE_VECTOR) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a vector. Line %d \n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }
    // se o tipo é uma chamada de variável função, verifica se o filho[0] (identificador) é do tipo função.
    else if (node->type == AST_FUNCTION_CALL) {
        if (node->son[0]->symbol->type != TYPE_FUNCTION) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a function. Line %d \n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }
    // se o tipo é um acesso à vetor (vetor[number]), verifica se o filho[0] (identificador) é do tipo vetor.  
    else if (node->type == AST_VECTOR) {
        if (node->son[0]->symbol->type != TYPE_VECTOR) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a vector. Line %d\n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }
    // se o tipo é um leitura, verifica se o filho[0] (identificador) é do tipo escalar.
    else if (node->type == AST_READ) {
        if (node->son[0]->symbol->type != TYPE_SCALAR) {
            fprintf(stderr, "Semantic ERROR: identifier %s must be a scalar. Line %d\n", node->son[0]->symbol->text, node->line);
            semanticError = 1;
        }
    }
    // se o tipo é de print, verifica-se se o filho[0] é um 'printable' (ou expressão ou literal string).
    else if (node->type == AST_PRINT) {
        if (!checkPrintable(node->son[0])) {
            fprintf(stderr, "Semantic ERROR: print expects a String or an expression. Line %d\n", node->line);
            semanticError = 1;
        }
    }
    // percorre todos os filhos.
    for (int i = 0; i < MAX_SONS; ++i)
        checkUsage(node->son[i]);
}

void checkOperations(AST *node)  {
    if (!node) 
        return;
    
    // percorre todos os filhos.
    for (int i = 0; i < MAX_SONS; ++i)
        checkOperations(node->son[i]);
    
    // seta os node->datatypes.
    if (node->type == AST_KW_CHAR || node->type == AST_KW_INT) {
        node->dataType = DATATYPE_INTEGER;
    }
    else if (node->type == AST_KW_FLOAT) {
        node->dataType = DATATYPE_FLOAT;
    }
    else if (node->type == AST_SYMBOL) {
        node->dataType = node->symbol->dataType;
        fprintf(stderr, "ACHEI UM SYMBOL\n");
        fprintf(stderr, "Ident: %s\n", node->symbol->text);
        fprintf(stderr, "DataType: %d\n", node->dataType);
        
    }
    else if (node->type == AST_VECTOR || node->type == AST_FUNCTION_CALL) {
        node->dataType = node->son[0]->dataType;

        if (node->type == AST_FUNCTION_CALL) {
            funcArgumentsCheck(node);
        }
    }
    else if (node->type == AST_GLOBAL_VECTOR_VALUES) {
        node->dataType = node->son[0]->dataType;
        fprintf(stderr, "OLHA EU AQUI %d\n", node->dataType);
        if (node->son[1]) {
            if (node->dataType != node->son[1]->dataType) {
                node->dataType = DATATYPE_UNDEFINED;
            }            
        }
    }
    else if (node->type == AST_GLOBAL_SCALAR) {
        if (node->son[1]->dataType != node->son[2]->dataType) {
            fprintf(stderr, "Semantic ERROR: incompatible types. Line %d\n", node->line);
            semanticError = 1;
        } 
    }
    else if (node->type == AST_GLOBAL_VECTOR) {
        if (node->son[3] != NULL) {
            if (node->son[1]->dataType != node->son[3]->dataType) {
                fprintf(stderr, "VALOR DO IDENT %d\n", node->son[1]->dataType);
                fprintf(stderr, "VALOR DOS VALORES %d\n", node->son[3]->dataType);
                semanticError = 1;
            }
        }
    }
    else if (checkConditionalExpression(node->type)) {
        if (node->type == AST_EQ) {
            if (node->son[0]->dataType != node->son[1]->dataType) {
                fprintf(stderr, "Semantic ERROR: expected operators with same type. Line %d\n", node->line);
                semanticError = 1;
                node->dataType = DATATYPE_UNDEFINED;
                return;
            }
        }
        else {
            if (node->son[0]->dataType != node->son[1]->dataType) {
                fprintf(stderr, "Semantic ERROR: expected operators with same type. Line %d\n", node->line);
                semanticError = 1;
                node->dataType = DATATYPE_UNDEFINED;
                return;
            }
            if (node->son[0]->dataType == DATATYPE_BOOL) {
                fprintf(stderr, "Semantic ERROR: unexpected boolean operator. Line %d\n", node->line);
                semanticError = 1;
                node->dataType = DATATYPE_UNDEFINED;
                return;
            }
        }
        node->dataType = DATATYPE_BOOL;
    }
    else if (checkLogicExpression(node->type)) {
        if (node->type == AST_NOT) {
           if (node->son[0]->dataType != DATATYPE_BOOL) {
                fprintf(stderr, "Semantic ERROR: expected boolean operator. Line %d\n", node->line);
                semanticError = 1;
                node->dataType = DATATYPE_UNDEFINED;
                return;
            }
        }
        else {
            if (node->son[0]->dataType != DATATYPE_BOOL || node->son[1]->dataType != DATATYPE_BOOL) {
                fprintf(stderr, "Semantic ERROR: expected boolean operator. Line %d\n", node->line);
                semanticError = 1;
                node->dataType = DATATYPE_UNDEFINED;
                return;
            }
        }
        node->dataType = DATATYPE_BOOL;
    }
    else if (checkArithmeticExpression(node->type)) {
        if (node->son[0]->dataType != node->son[1]->dataType) {
            fprintf(stderr, "Semantic ERROR: expected operators with same type. Line %d\n", node->line);
            semanticError = 1;
            node->dataType = DATATYPE_UNDEFINED;
            return;
        }
        if (node->son[0]->dataType == DATATYPE_BOOL) {
            fprintf(stderr, "Semantic ERROR: unexpected boolean operator. Line %d\n", node->line);
            semanticError = 1;
            node->dataType = DATATYPE_UNDEFINED;
            return;
        }
        node->dataType = node->son[0]->dataType;
    }
    else if (node->type == AST_PARENTHESES) {
        node->dataType = node->son[0]->dataType;
    }
    else if (node->type == AST_LOCAL_SCALAR) {
        if (node->son[0]->dataType != node->son[1]->dataType) {
            fprintf(stderr, "Semantic ERROR: imcompatible types. Line %d\n", node->line);
            semanticError = 1;
            node->dataType = DATATYPE_UNDEFINED;
            return;
        }
    }
    else if (node->type == AST_LOCAL_VECTOR) {
        if (node->son[1]->dataType != DATATYPE_INTEGER) {
            fprintf(stderr, "Semantic ERROR: array index must be an integer. Line %d\n", node->line);
            semanticError = 1;
            node->dataType = DATATYPE_UNDEFINED;
            return;
        }
        if (node->son[0]->dataType != node->son[2]->dataType) {
            fprintf(stderr, "Semantic ERROR: imcompatible types. Line %d\n", node->line);
            semanticError = 1;
            node->dataType = DATATYPE_UNDEFINED;
            return;
        }
    }
    else if (node->type == AST_IF || node->type == AST_IF_ELSE || node->type == AST_WHILE) {
        if (node->son[0]->dataType != DATATYPE_BOOL) {
            fprintf(stderr, "Semantic ERROR: conditional expression must be boolean. Line %d\n", node->line);
            semanticError = 1;
            node->dataType = DATATYPE_UNDEFINED;
            return;
        }
    }
    else if (node->type == AST_RETURN) {
        if (node->son[0]->dataType == DATATYPE_BOOL) {
            fprintf(stderr, "Semantic ERROR: return type must not be boolean. Line %d\n", node->line);
            semanticError = 1;
            node->dataType = DATATYPE_UNDEFINED;
            return;
        }
    }
}

// Funções auxiliares
int checkPrintable(AST *node) {
    if (!node) return 1;
    if (!checkExpression(node->son[0])) {
        if (node->son[0]->type != AST_SYMBOL) return 0;
    }
    return checkPrintable(node->son[1]);
}

int checkExpression(AST *node) {
    if (node->type == AST_VECTOR || node->type == AST_PARENTHESES || node->type == AST_FUNCTION_CALL || checkArithmeticExpression(node->type) || checkLogicExpression(node->type) || checkConditionalExpression(node->type)) return 1;
    if (node->type == AST_SYMBOL) {
        if (node->symbol->type == SYMBOL_LIT_STRING) return 0;
        return 1;
    }
    return 0;
}

int checkConditionalExpression(int type) {
    if (type == AST_LE || type == AST_GE || type == AST_EQ || type== AST_LT || type == AST_GT) return 1;
    return 0;
}

int checkArithmeticExpression(int type) {
    if (type == AST_ADD || type == AST_SUB || type == AST_MUL || type== AST_DIV) return 1;
    return 0;
}

int checkLogicExpression(int type) {
    if (type == AST_OR || type == AST_AND || type == AST_NOT) return 1;
    return 0;
}

void addFunctionToList(AST *node) {
    FUNC_LIST* newFunc;

	if (!(newFunc = (FUNC_LIST*) calloc(1, sizeof(FUNC_LIST)))) {
		exit(1);
	}

    newFunc->next = func_list;
    newFunc->node = node;

    func_list = newFunc;
}

int funcArgumentsCheck(AST *funcCall) {
    AST *funcDeclaration;
    if (!(funcDeclaration = findFunctionDeclaration(funcCall))) {
        fprintf(stderr, "Semantic ERROR: identifier %s undeclared. Line: %d \n", funcCall->son[0]->symbol->text, funcCall->line);
        semanticError = 1;
        return 0;
    }

    AST *parameters = funcDeclaration->son[1];
    AST *arguments = funcCall->son[1];

    while (parameters && arguments) {
        if (parameters->son[0]->dataType != arguments->son[0]->dataType) {
            fprintf(stderr, "Semantic ERROR: argument type mismatch. Line %d\n", funcCall->line);
            semanticError = 1;
            return 0;
        }
        parameters = parameters->son[1];
        arguments = arguments->son[1];
    }

    if (parameters) {
        fprintf(stderr, "Semantic ERROR: missing arguments for function call. Line %d\n", funcCall->line);
        semanticError = 1;
        return 0;
    } else if (arguments) {
        fprintf(stderr, "Semantic ERROR: too many arguments on function call. Line %d\n", funcCall->line);
        semanticError = 1;
        return 0;
    }

    return 1;
}

AST *findFunctionDeclaration(AST *funcCall) {
    for (FUNC_LIST* curr = func_list; curr != NULL; curr = curr->next) {
        if (curr->node->son[1]->symbol->text == funcCall->son[0]->symbol->text)
            return curr->node;
    }
    return NULL;
}