%{
#include <stdio.h>
#include "tokens.h"
#include "hash.h"

int running = 1;
int lineNumber = 1;

int isRunning();
void initMe();
int getLineNumber();

%}

%x COMMENT

%%

 /* Reserved words */ 
"char"						{ return KW_CHAR; }
"int"						{ return KW_INT; }						
"float"						{ return KW_FLOAT; }
"if"						{ return KW_IF; }
"then"						{ return KW_THEN; }
"else"						{ return KW_ELSE; }
"while"						{ return KW_WHILE; }
"or"						{ return OPERATOR_OR; }
"and"						{ return OPERATOR_AND; }
"not"						{ return OPERATOR_NOT; }
"read"						{ return KW_READ; }
"print"						{ return KW_PRINT; }
"return"					{ return KW_RETURN; }

 /* Special characters */
[-,;:dbqp{}+*/<>=!&$#]    { return (int)yytext[0]; }

 /* Composed operators */
"<="						{ return OPERATOR_LE; }
">="						{ return OPERATOR_GE; }
"=="						{ return OPERATOR_EQ; }

 /* Identifier */ 
[ace-or-zA-Z_0-9]*[ace-or-zA-Z_]+[ace-or-zA-Z_0-9]*	{ hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }

 /* Literals */
[0-9]*						{ hashInsert(LIT_INTEGER, yytext); return LIT_INTEGER; }
[0-9]+"."[0-9]+				{ hashInsert(LIT_FLOAT, yytext); return LIT_FLOAT; }
\'[^']\'					{ hashInsert(LIT_CHAR, yytext); return LIT_CHAR; }
\"[^"]*\"                   { hashInsert(LIT_STRING, yytext); return LIT_STRING; }

 /* One line comment and multiple lines comment */
"//".*                      { }
"/*"                        { BEGIN(COMMENT); }
<COMMENT>.
<COMMENT>"\n"               { lineNumber++; }
<COMMENT>"*/"               { BEGIN(INITIAL); }

 /* New line */
"\n"						{ lineNumber++; }

 /* Space and tab */
[ \t]					    { }

.							{ return TOKEN_ERROR; }

%%

int yywrap() {
	running = 0;
	return 1;
}

int isRunning() {
	return running;
}

int getLineNumber() {
	return lineNumber;
}

void initMe() {
	hashInit();
}