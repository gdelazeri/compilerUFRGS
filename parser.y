%{
	#include <stdlib.h>
	#include <stdio.h>
    #include "ast.h"
    #include "semantic.h"

	int yylex();
	void yyerror(char *error);
	int getLineNumber();

    AST* astTree;
%}


%union {
		HASH_NODE *symbol;
        AST* ast;
}

/* Language Tokens */
%token KW_CHAR       
%token KW_INT        
%token KW_FLOAT    
%token KW_IF         
%token KW_THEN       
%token KW_ELSE       
%token KW_WHILE      
%token KW_READ       
%token KW_RETURN     
%token KW_PRINT     
%token OPERATOR_LE   
%token OPERATOR_GE  
%token OPERATOR_EQ  
%token OPERATOR_OR   
%token OPERATOR_AND  
%token OPERATOR_NOT  
%token <symbol> TK_IDENTIFIER 
%token <symbol> LIT_INTEGER   
%token <symbol> LIT_FLOAT     
%token <symbol> LIT_CHAR      
%token <symbol> LIT_STRING    
%token TOKEN_ERROR  

%type <ast> program declarationList declaration globalVar vector moreInitValue function paramList param moreParam block commandList command attribution controlFlow printables printable morePrintables expression argumentList argument moreArgument type initValue identifier

%start program

%right KW_THEN KW_ELSE
%left OPERATOR_NOT
%left OPERATOR_AND OPERATOR_OR
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ
%left '+' '-'
%left '*' '/'

%%

/* Language Rules */

program: 
    declarationList { astTree = ast_create(AST_PROGRAM, 0, $1, 0, 0, 0); semanticCheck($1); }
;

declarationList: 
    declaration declarationList { $$ = ast_create(AST_DECLARATION_LIST, 0, $1, $2, 0, 0); $$->line = getLineNumber(); }
    | /* Empty */ { $$ = 0; }
;

declaration:
    globalVar ';' { $$ = $1; }
    | function { $$ = $1; }
;

globalVar:
    type identifier '=' initValue { $$ = ast_create(AST_GLOBAL_SCALAR, 0, $1, $2, $4, 0); $$->line = getLineNumber(); }
    | vector { $$ = $1; }
;

vector:
    type identifier 'q' LIT_INTEGER 'p'  { $$ = ast_create(AST_GLOBAL_VECTOR, 0, $1, $2, ast_create(AST_SYMBOL, $4, 0, 0, 0, 0), 0); $$->line = getLineNumber(); }
   | type identifier 'q' LIT_INTEGER 'p' ':' moreInitValue { $$ = ast_create(AST_GLOBAL_VECTOR, 0, $1, $2, ast_create(AST_SYMBOL, $4, 0, 0, 0, 0), $7); $$->line = getLineNumber(); }
;

moreInitValue:
    initValue moreInitValue { $$ = ast_create(AST_GLOBAL_VECTOR_VALUES, 0, $1, $2, 0, 0); }
    | /* Empty */ { $$ = 0; }
;

function:
    type identifier 'd' paramList 'b' block { $$ = ast_create(AST_FUNCTION, 0, $1, $2, $4, $6); $$->line = getLineNumber(); }
;

paramList:
    param moreParam { $$ = ast_create(AST_FUNCTION_PARAMS, 0, $1, $2, 0, 0); }
    | /* Empty */ { $$ = 0; }
;

param:
   type identifier { $$ = ast_create(AST_FUNCTION_PARAM, 0, $1, $2, 0, 0); $$->line = getLineNumber(); }
;

moreParam:
    ',' param moreParam { $$ = ast_create(AST_FUNCTION_PARAMS, 0, $2, $3, 0, 0); }
    | /* Empty */ { $$ = 0; }
;

block:
    '{' commandList '}' { $$ = ast_create(AST_BLOCK, 0, $2, 0, 0, 0); }
;

commandList:
    command ';' commandList { $$ = ast_create(AST_COMMAND, 0, $1, $3, 0, 0); }
    | /* Empty */ { $$ = 0; }
;

command:
    attribution { $$ = $1; }
    | controlFlow { $$ = $1; }
    | KW_READ identifier { $$ = ast_create(AST_READ, 0, $2, 0, 0, 0); $$->line = getLineNumber();}
    | KW_PRINT printables { $$ = ast_create(AST_PRINT, 0, $2, 0, 0, 0); $$->line = getLineNumber();}
    | KW_RETURN expression { $$ = ast_create(AST_RETURN, 0, $2, 0, 0, 0); $$->line = getLineNumber();}
    | block { $$ = $1; }
    | /* Empty */ { $$ = 0; }
;

attribution:
    identifier '=' expression { $$ = ast_create(AST_LOCAL_SCALAR, 0, $1, $3, 0, 0); $$->line = getLineNumber(); }
    | identifier 'q' expression 'p' '=' expression { $$ = ast_create(AST_LOCAL_VECTOR, 0, $1, $3, $6, 0); $$->line = getLineNumber(); }
;

controlFlow:
    KW_IF expression KW_THEN command { $$ = ast_create(AST_IF, 0, $2, $4, 0, 0); $$->line = getLineNumber(); }
    | KW_IF expression KW_THEN command KW_ELSE command { $$ = ast_create(AST_IF_ELSE, 0, $2, $4, $6, 0); $$->line = getLineNumber(); }
    | KW_WHILE expression command { $$ = ast_create(AST_WHILE, 0, $2, $3, 0, 0); $$->line = getLineNumber(); }
;

printables:
    printable morePrintables { $$ = ast_create(AST_PRINTABLES, 0, $1, $2, 0, 0); }
;

printable:
    LIT_STRING { $$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); $$->line = getLineNumber(); }
    | expression { $$ = $1; }
;

morePrintables:
    ',' printable morePrintables { $$ = ast_create(AST_PRINTABLES, 0, $2, $3, 0, 0); }
    | /* Empty */ { $$ = 0; }
;

expression:
    identifier { $$ = $1; }
    | identifier 'q' expression 'p' { $$ = ast_create(AST_VECTOR, 0, $1, $3, 0, 0); $$->line = getLineNumber(); }
    | LIT_INTEGER { $$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); $$->line = getLineNumber(); }
    | LIT_FLOAT { $$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); $$->line = getLineNumber(); }
    | LIT_CHAR { $$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); $$->line = getLineNumber(); }
    | expression OPERATOR_LE expression { $$ = ast_create(AST_LE, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | expression OPERATOR_GE expression { $$ = ast_create(AST_GE, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | expression OPERATOR_EQ expression { $$ = ast_create(AST_EQ, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | expression OPERATOR_OR expression { $$ = ast_create(AST_OR, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | expression OPERATOR_AND expression { $$ = ast_create(AST_AND, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | OPERATOR_NOT expression { $$ = ast_create(AST_NOT, 0, $2, 0, 0, 0); $$->line = getLineNumber();}
    | expression '+' expression { $$ = ast_create(AST_ADD, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | expression '-' expression { $$ = ast_create(AST_SUB, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | expression '*' expression { $$ = ast_create(AST_MUL, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | expression '/' expression { $$ = ast_create(AST_DIV, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | expression '<' expression { $$ = ast_create(AST_LT, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | expression '>' expression { $$ = ast_create(AST_GT, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
    | 'd' expression 'b' { $$ = ast_create(AST_PARENTHESES, 0, $2, 0, 0, 0); $$->line = getLineNumber();}
    | identifier 'd' argumentList 'b' { $$ = ast_create(AST_FUNCTION_CALL, 0, $1, $3, 0, 0); $$->line = getLineNumber();}
;

argumentList:
    argument moreArgument { $$ = ast_create(AST_FUNCTION_CALL_ARGS, 0, $1, $2, 0, 0); }
    | /* Empty */ { $$ = 0; }
;

argument:
   expression { $$ = $1; }
; 

moreArgument:
    ',' argument moreArgument { $$ = ast_create(AST_FUNCTION_CALL_ARGS, 0, $2, $3, 0, 0); }
    | /* Empty */ { $$ = 0; }
;

type: 
    KW_CHAR { $$ = ast_create(AST_KW_CHAR, 0, 0, 0, 0, 0); $$->line = getLineNumber();}
    | KW_FLOAT { $$ = ast_create(AST_KW_FLOAT, 0, 0, 0, 0, 0); $$->line = getLineNumber();}
    | KW_INT { $$ = ast_create(AST_KW_INT, 0, 0, 0, 0, 0); $$->line = getLineNumber();}
;

initValue:
    LIT_CHAR { $$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); $$->line = getLineNumber();}
    | LIT_FLOAT { $$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); $$->line = getLineNumber();}
    | LIT_INTEGER { $$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); $$->line = getLineNumber();}
;

identifier:
    TK_IDENTIFIER { $$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); $$->line = getLineNumber();}
;

%%

 /* Subroutines */

void yyerror(char *error){
    fprintf(stderr, "Error[Line %d]: %s\n", getLineNumber(), error);
    exit(3);
}