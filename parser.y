%{
	#include <stdlib.h>
	#include <stdio.h>
    #include "hash.h"

	int yylex();
	void yyerror(char *error);
	int getLineNumber();
%}


%union {
		HASH_NODE *symbol;
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

/* TODO: Add left rules */

%start program

%%

/* Language Rules */

program: 
    declarationList 
;

declarationList: 
    declaration declarationList
    | /* Empty */
;

declaration:
    globalVar ';'
    | function
;

globalVar:
    type TK_IDENTIFIER '=' initValue
    | vector
;

vector:
    type TK_IDENTIFIER 'q' LIT_INTEGER 'p'  
    | type TK_IDENTIFIER 'q' LIT_INTEGER 'p' ':' initValue moreInitValue
;

moreInitValue:
    initValue moreInitValue
    | /* Empty */
;

function:
    type TK_IDENTIFIER 'd' paramList 'b' block
;

paramList:
    param moreParam
    | /* Empty */
;

param:
   type TK_IDENTIFIER
;

moreParam:
    ',' param moreParam
    | /* Empty */
;

block:
    '{' commandList '}'
;

commandList:
    command ';' commandList
    | /* Empty */
;

command:
    attribution
    | controlFlow
    | KW_READ TK_IDENTIFIER
    | KW_PRINT printables
    | KW_RETURN expression
    | block
    | /* Empty */
;

attribution:
    TK_IDENTIFIER '=' expression
    | TK_IDENTIFIER 'q' expression 'p' '=' expression
;

controlFlow:
    KW_IF expression KW_THEN command
    | KW_IF expression KW_THEN command KW_ELSE command
    | KW_WHILE expression command
;

printables:
    printable morePrintables
;

printable:
    LIT_STRING
    | expression
;

morePrintables:
    ',' printable morePrintables
    | /* Empty */
;

expression:
    TK_IDENTIFIER
    | TK_IDENTIFIER 'q' expression 'p'
    | LIT_INTEGER
    | LIT_FLOAT
    | LIT_CHAR
    | expression OPERATOR_LE expression
    | expression OPERATOR_GE expression
    | expression OPERATOR_EQ expression
    | expression OPERATOR_OR expression
    | expression OPERATOR_AND expression
    | expression OPERATOR_NOT expression
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '<' expression
    | expression '>' expression
    | 'd' expression 'b'
    | TK_IDENTIFIER 'd' argumentList 'b'
;

argumentList:
    argument moreArgument
    | /* Empty */
;

argument:
   expression
; 

moreArgument:
    ',' argument moreArgument
    | /* Empty */
;

type: 
    KW_CHAR
    | KW_FLOAT
    | KW_INT
;

initValue:
    LIT_CHAR
    | LIT_FLOAT
    | LIT_INTEGER
;

%%

 /* Subroutines */

void yyerror(char *error){
    fprintf(stderr, "Error[Line %d]: %s\n", getLineNumber(), error);
    exit(3);
}