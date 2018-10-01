#include "ast.h"

AST *ast_create(int type, HASH_NODE *symbol, AST *son0, AST *son1, AST *son2, AST *son3) {
  AST *new;
  new = (AST *)calloc(1, sizeof(AST));
  
  new->type = type;
  new->symbol = symbol;
  new->son[0] = son0;
  new->son[1] = son1;
  new->son[2] = son2;
  new->son[3] = son3;

  return new;
}

void ast_print(AST *node, int level) {
  int i = 0;
  
  if (node) {    
    for (i = 0; i < level; ++i) {
      fprintf(stderr, ">");
    }
    
    fprintf(stderr, "AST(");

    switch (node->type) {
      case AST_PROGRAM:
        fprintf(stderr, "PROGRAM");
        break;
      case AST_DECLARATION_LIST:
        fprintf(stderr, "DECLARATION");
        break;
      case AST_GLOBAL_SCALAR:
        fprintf(stderr, "GLOBAL_SCALAR");
        break;
      case AST_GLOBAL_VECTOR:
        fprintf(stderr, "GLOBAL_VECTOR");
        break;
      case AST_GLOBAL_VECTOR_VALUES:
        fprintf(stderr, "GLOBAL_VECTOR_VALUES");
        break;
      case AST_FUNCTION:
        fprintf(stderr, "FUNCTION");
        break;
      case AST_FUNCTION_PARAMS:
        fprintf(stderr, "FUNCTION_PARAMS_LIST");
        break;
      case AST_FUNCTION_PARAM:
        fprintf(stderr, "FUNCTION_PARAM");
        break;
      case AST_BLOCK:
        fprintf(stderr, "BLOCK");
        break;
      case AST_COMMAND:
        fprintf(stderr, "COMMAND");
        break;
      case AST_READ:
        fprintf(stderr, "READ");
        break;
      case AST_PRINT:
        fprintf(stderr, "PRINT");
        break;
      case AST_RETURN:
        fprintf(stderr, "RETURN");
        break;
      case AST_LOCAL_SCALAR:
        fprintf(stderr, "LOCAL_SCALAR");
        break;
      case AST_LOCAL_VECTOR:
        fprintf(stderr, "LOCAL_VECTOR");
        break;
      case AST_IF:
        fprintf(stderr, "IF_THEN");
        break;
      case AST_IF_ELSE:
        fprintf(stderr, "IF_THEN_ELSE");
        break;
      case AST_WHILE:
        fprintf(stderr, "WHILE");
        break;
      case AST_PRINTABLES:
        fprintf(stderr, "PRINTABLE");
        break;
      case AST_SYMBOL:
        fprintf(stderr, "SYMBOL");
        break;
      case AST_VECTOR:
        fprintf(stderr, "VECTOR_EXPRESSION");
        break;
      case AST_LE:
        fprintf(stderr, "LE");
        break;
      case AST_GE:
        fprintf(stderr, "GE");
        break;
      case AST_EQ:
        fprintf(stderr, "EQ");
        break;
      case AST_OR:
        fprintf(stderr, "OR");
        break;
      case AST_AND:
        fprintf(stderr, "AND");
        break;
      case AST_NOT:
        fprintf(stderr, "NOT");
        break;
      case AST_ADD:
        fprintf(stderr, "ADD");
        break;
      case AST_SUB:
        fprintf(stderr, "SUB");
        break;
      case AST_MUL:
        fprintf(stderr, "MUL");
        break;
      case AST_DIV:
        fprintf(stderr, "DIV");
        break;
      case AST_LT:
        fprintf(stderr, "LT");
        break;
      case AST_GT:
        fprintf(stderr, "GT");
        break;
      case AST_PARENTHESES:
        fprintf(stderr, "PARENTHESES");
        break;
      case AST_FUNCTION_CALL:
        fprintf(stderr, "FUNCTION_CALL");
        break;
      case AST_FUNCTION_CALL_ARGS:
        fprintf(stderr, "FUNCTION_CALL_ARGS");
        break;
      case AST_KW_CHAR:
        fprintf(stderr, "KW_CHAR");
        break;
      case AST_KW_FLOAT:
        fprintf(stderr, "KW_FLOAT");
        break;
      case AST_KW_INT:
        fprintf(stderr, "KW_INT");
        break;
      default:
        fprintf(stderr, "UNKOWN WITH TOKEN %d", node-> type);
        break;
    }

    if (node->symbol) {
      fprintf(stderr, ",%s\n", node->symbol->text);
    } else {
      fprintf(stderr, "\n");
    }

    for (i = 0; i < MAX_SONS; ++i) {
      ast_print(node->son[i], level + 1);
    }
  }
}

void ast_decompile(FILE *file, AST *node) {
  char *buffer;
  int i = 0;

  if (node) {
    switch (node->type) {
      case AST_PROGRAM:
        for (i = 0; i < MAX_SONS; ++i) {
          ast_decompile(file, node->son[i]);
        }
        break;
      case AST_DECLARATION_LIST:
        for (i = 0; i < MAX_SONS; ++i) {
          ast_decompile(file, node->son[i]);
          fprintf(file, "\n");
        }
        break;
      case AST_GLOBAL_SCALAR:
        ast_decompile(file, node->son[0]);
        ast_decompile(file, node->son[1]);
        fprintf(file, " = ");
        ast_decompile(file, node->son[2]);
        fprintf(file, ";");
        break;
      case AST_GLOBAL_VECTOR:
        ast_decompile(file, node->son[0]);
        ast_decompile(file, node->son[1]);
        fprintf(file, " q ");
        ast_decompile(file, node->son[2]);
        fprintf(file, " p");
        if (node->son[3] != 0) {
          fprintf(file, ":");
          ast_decompile(file, node->son[3]);
        }
        fprintf(file, ";");
        break;
      case AST_GLOBAL_VECTOR_VALUES:
        fprintf(file, " ");
        ast_decompile(file, node->son[0]);
        ast_decompile(file, node->son[1]);
        break;
      case AST_FUNCTION:
        fprintf(file, "\n");
        ast_decompile(file, node->son[0]);
        ast_decompile(file, node->son[1]);
        fprintf(file, " d ");
        ast_decompile(file, node->son[2]);
        fprintf(file, " b ");
        fprintf(file, "\n");
        ast_decompile(file, node->son[3]);
        break;
      case AST_FUNCTION_PARAMS:
        fprintf(file, " ");
        ast_decompile(file, node->son[0]);

        if (node->son[1] != 0) {
          fprintf(file, ",");
          ast_decompile(file, node->son[1]);
        }    
        break;
      case AST_FUNCTION_PARAM:
        ast_decompile(file, node->son[0]);
        ast_decompile(file, node->son[1]);
        break;
      case AST_BLOCK:
        fprintf(file, "{\n");
        ast_decompile(file, node->son[0]);
        ast_decompile(file, node->son[1]);
        fprintf(file, "}");
        break;
      case AST_COMMAND:
        ast_decompile(file, node->son[0]);
        fprintf(file, ";\n");
        ast_decompile(file, node->son[1]);
        break;
      case AST_READ:
        fprintf(file, "read ");
        ast_decompile(file, node->son[0]);
        break;
      case AST_PRINT:
        fprintf(file, "print ");
        ast_decompile(file, node->son[0]);
        break;
      case AST_RETURN:
        fprintf(file, "return ");
        ast_decompile(file, node->son[0]);
        break;
      case AST_LOCAL_SCALAR:
        ast_decompile(file, node->son[0]);
        fprintf(file, " = ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_LOCAL_VECTOR:
        ast_decompile(file, node->son[0]);
        fprintf(file, " q ");
        ast_decompile(file, node->son[1]);
        fprintf(file, " p ");
        fprintf(file, "= ");
        ast_decompile(file, node->son[2]);
        break;
      case AST_IF:
        fprintf(file, "if ");
        ast_decompile(file, node->son[0]);
        fprintf(file, " then\n");
        ast_decompile(file, node->son[1]);
        break;
      case AST_IF_ELSE:
        fprintf(file, "if ");
        ast_decompile(file, node->son[0]);
        fprintf(file, " then\n");
        ast_decompile(file, node->son[1]);
        fprintf(file, "else\n");
        ast_decompile(file, node->son[2]);
        break;
      case AST_WHILE:
        fprintf(file, "while ");
        ast_decompile(file, node->son[0]);
        fprintf(file, "\n");
        ast_decompile(file, node->son[1]);
        break;
      case AST_PRINTABLES:
        ast_decompile(file, node->son[0]);
        if (node->son[1] != 0) {
          fprintf(file, ", ");
          ast_decompile(file, node->son[1]);
        }
        break;
      case AST_SYMBOL:
        fprintf(file, "%s", node->symbol->text);
        break;
      case AST_VECTOR:
        ast_decompile(file, node->son[0]);
        fprintf(file, " q ");
        ast_decompile(file, node->son[1]);
        fprintf(file, " p");
        break;
      case AST_LE:
        ast_decompile(file, node->son[0]);
        fprintf(file, " <= ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_GE:
        ast_decompile(file, node->son[0]);
        fprintf(file, " >= ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_EQ:
        ast_decompile(file, node->son[0]);
        fprintf(file, " == ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_OR:
        ast_decompile(file, node->son[0]);
        fprintf(file, " or ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_AND:
        ast_decompile(file, node->son[0]);
        fprintf(file, " and ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_NOT:
        ast_decompile(file, node->son[0]);
        fprintf(file, " not ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_ADD:
        ast_decompile(file, node->son[0]);
        fprintf(file, " + ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_SUB:
        ast_decompile(file, node->son[0]);
        fprintf(file, " - ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_MUL:
        ast_decompile(file, node->son[0]);
        fprintf(file, " * ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_DIV:
        ast_decompile(file, node->son[0]);
        fprintf(file, " / ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_LT:
        ast_decompile(file, node->son[0]);
        fprintf(file, " < ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_GT:
        ast_decompile(file, node->son[0]);
        fprintf(file, " > ");
        ast_decompile(file, node->son[1]);
        break;
      case AST_PARENTHESES:
        fprintf(file, "d ");
        ast_decompile(file, node->son[0]);
        fprintf(file, " b");
        break;
      case AST_FUNCTION_CALL:
        ast_decompile(file, node->son[0]);
        fprintf(file, " d ");
        ast_decompile(file, node->son[1]);
        fprintf(file, " b");
        break;
      case AST_FUNCTION_CALL_ARGS:
        ast_decompile(file, node->son[0]);
        if (node->son[1] != 0) {
          fprintf(file, ", ");
          ast_decompile(file, node->son[1]);
        }
        break;
      case AST_KW_CHAR:
        fprintf(file, "char ");
        break;
      case AST_KW_FLOAT:
        fprintf(file, "float ");
        break;
      case AST_KW_INT:
        fprintf(file, "int ");
        break;
      default:
        break;
    } 
  }
}