/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
	#include <stdlib.h>
	#include <stdio.h>
    #include "ast.h"
    #include "semantic.h"

	int yylex();
	void yyerror(char *error);
	int getLineNumber();

    AST* astTree;
#line 15 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
		HASH_NODE *symbol;
        AST* ast;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 44 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_CHAR 257
#define KW_INT 258
#define KW_FLOAT 259
#define KW_IF 260
#define KW_THEN 261
#define KW_ELSE 262
#define KW_WHILE 263
#define KW_READ 264
#define KW_RETURN 265
#define KW_PRINT 266
#define OPERATOR_LE 267
#define OPERATOR_GE 268
#define OPERATOR_EQ 269
#define OPERATOR_OR 270
#define OPERATOR_AND 271
#define OPERATOR_NOT 272
#define TK_IDENTIFIER 273
#define LIT_INTEGER 274
#define LIT_FLOAT 275
#define LIT_CHAR 276
#define LIT_STRING 277
#define TOKEN_ERROR 278
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    3,    3,    4,    4,    5,
    5,    6,    7,    7,    8,    9,    9,   10,   11,   11,
   12,   12,   12,   12,   12,   12,   12,   13,   13,   14,
   14,   14,   15,   16,   16,   17,   17,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   19,   19,   20,   21,
   21,   22,   22,   22,   23,   23,   23,   24,
};
static const YYINT yylen[] = {                            2,
    1,    2,    0,    2,    1,    4,    1,    5,    7,    2,
    0,    6,    2,    0,    2,    3,    0,    3,    3,    0,
    1,    1,    2,    2,    2,    1,    0,    3,    6,    4,
    6,    3,    2,    1,    1,    3,    0,    1,    4,    1,
    1,    1,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    4,    2,    0,    1,    3,
    0,    1,    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
   62,   64,   63,    0,    1,    0,    0,    7,    5,    0,
    2,    4,   68,    0,    0,    0,    0,   67,   66,   65,
    6,    0,    0,    0,    0,    0,    0,    0,   13,   15,
    0,    0,   12,    0,    9,    0,    0,    0,    0,    0,
    0,   26,    0,    0,   21,   22,    0,   16,   10,   40,
   41,   42,    0,    0,    0,    0,   23,    0,   34,   24,
    0,    0,   18,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   32,    0,   33,   19,    0,    0,   55,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   51,   52,    0,    0,    0,    0,    0,    0,    0,   39,
   56,    0,   57,   36,    0,   31,    0,    0,   60,
};
static const YYINT yydgoto[] = {                          4,
    5,    6,    7,    8,   35,    9,   23,   24,   29,   42,
   43,   44,   45,   46,   60,   61,   85,   62,  105,  106,
  113,   10,   36,   55,
};
static const YYINT yysindex[] = {                      -197,
    0,    0,    0,    0,    0, -197,  -15,    0,    0, -226,
    0,    0,    0,   18, -209, -224, -197,    0,    0,    0,
    0,  -64,  -47,   10, -226,   13,  -51, -197,    0,    0,
 -209,  -95,    0,   10,    0, -209,  -77,  -77, -226,  -77,
  -86,    0,  -32,   16,    0,    0,  -45,    0,    0,    0,
    0,    0,  -77,   35,  -71,  -21,    0,   68,    0,    0,
   52,   68,    0,  -95,  -77,  -77,  -35,  -95,  -77,  -77,
  -77,  -77,  -77,  -77,  -77,  -77,  -77,  -77,  -77,  -77,
  -77,  -77,    0,  -86,    0,    0,   68,   41,    0, -164,
  -12,  -12,  -12,  -12,  -12,  -12,  -12,  -12,   -2,   -2,
    0,    0,   47,   68,    1,   56,   52,   45,  -95,    0,
    0,  -77,    0,    0,  -77,    0,   56,   68,    0,
};
static const YYINT yyrindex[] = {                       108,
    0,    0,    0,    0,    0,  108,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   19,    0,    0,    0,
    0,    0,    0,   23,    0,   55,    0,    0,    0,    0,
   64,  -40,    0,   23,    0,   64,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -42,  -55,    0,  -53,    0,    0,
  -50,    5,    0,  -40,    0,    0,    0,  -55,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   26,    0,    0,    0,    0,  -48,    0,    0,   70,
   60,   81,  311,  328,  345,  362,  385,  402,   -7,   14,
    0,    0,    0,  -29,    0,   29,  -50,    0,  -55,    0,
    0,    0,    0,    0,    0,    0,   29,  -46,    0,
};
static const YYINT yygindex[] = {                         0,
  126,    0,    0,    0,   97,    0,    0,  106,  101,  109,
   74,  -22,    0,    0,    0,   58,   32,  639,    0,   33,
   27,   15,  131,  369,
};
#define YYTABLESIZE 754
static const YYINT yytable[] = {                         38,
   38,   38,   38,   27,   38,   25,   79,   77,   37,   78,
   28,   80,   29,   53,   59,   65,   38,   38,   27,   38,
   79,   77,   53,   78,   75,   80,   76,   32,   82,   79,
   77,   25,   78,   83,   80,   49,   49,   49,   75,   79,
   76,   81,   25,   12,   80,   90,   13,   26,   35,   22,
   27,   49,   49,   28,   49,   38,   50,   50,   50,    1,
    2,    3,   89,   35,   18,   19,   20,   66,   59,   38,
   31,   32,   50,   50,   64,   50,   79,   77,   15,   78,
   38,   80,   79,   77,   20,   78,  116,   80,   79,   77,
   49,   78,   63,   80,   75,   84,   76,  109,  111,  112,
   75,   32,   76,   43,   49,  115,   75,    3,   76,   79,
   77,   50,   78,    8,   80,   49,   14,   17,   43,   43,
   17,   43,   11,   58,   44,   50,   61,   75,   30,   76,
   16,   11,   49,   34,   48,   33,   50,   86,  114,   44,
   44,  107,   44,  119,  117,   21,    0,    0,    0,    0,
    0,    0,  108,    0,    0,    0,    0,   43,  110,    0,
    0,    0,    0,    0,   37,    0,    0,   38,   39,   40,
   41,   43,    0,    0,    0,    0,    0,   13,   44,    0,
    0,    0,   43,    0,    0,    0,   13,   50,   51,   52,
   59,    0,   44,    0,    0,   13,   50,   51,   52,    0,
    0,    0,    0,   44,    0,    0,   27,    0,   25,    0,
    0,   37,    0,   28,    0,   29,    0,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   69,   70,   71,   72,   73,   74,    0,   37,    0,
    0,   38,   39,   40,   41,   69,   70,   71,   72,   73,
   74,   13,   49,   49,   49,   49,   49,   49,   49,   49,
   49,   49,   49,   49,   49,   49,   35,    0,    0,    0,
    0,    0,    0,   50,   50,   50,   50,   50,   50,   50,
   50,   50,   50,   50,   50,   50,   50,    0,    0,    0,
    0,    0,    0,    0,    0,   68,    0,    0,    0,    0,
    0,   69,   70,   71,   72,   73,   74,   69,   70,   71,
   72,   73,   74,   69,   70,   71,   72,   73,   74,   43,
   43,   43,   43,   43,   43,   43,   43,   43,   43,   43,
   43,   43,   43,    0,   69,   70,   71,   72,   73,   74,
   44,   44,   44,   44,   44,   44,   44,   44,   44,   44,
   44,   44,   44,   44,   45,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   45,
   45,   46,   45,    0,    0,    0,    0,    0,   14,    0,
    0,    0,    0,    0,    0,    0,   46,   46,   47,   46,
    0,    0,    0,   30,    0,    0,    0,    0,    0,    0,
   47,    0,    0,   47,   47,   48,   47,   57,   45,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   48,   48,   45,   48,   47,   46,    0,    0,   53,    0,
    0,    0,   47,   45,    0,    0,   47,    0,    0,   46,
    0,    0,   47,   53,   53,   54,   53,    0,    0,    0,
   46,    0,    0,    0,    0,    0,   47,    0,    0,   48,
   54,   54,    0,   54,    0,    0,    0,   47,    0,    0,
    0,    0,    0,   48,    0,    0,    0,   47,    0,    0,
    0,    0,   53,    0,   48,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   53,    0,    0,   54,
    0,    0,    0,    0,    0,    0,    0,   53,    0,    0,
    0,    0,    0,   54,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   54,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   45,   45,   45,   45,   45,   45,   45,   45,   45,   45,
   45,   45,   45,   45,    0,    0,    0,   46,   46,   46,
   46,   46,   46,   46,   46,   46,   46,   46,   46,   46,
   46,    0,    0,    0,   47,   47,   47,   47,   47,   47,
   47,   47,   47,   47,   47,   47,   47,   47,    0,    0,
    0,   48,   48,   48,   48,   48,   48,   48,   48,   48,
   48,   48,   48,   48,   48,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   53,   53,   53,   53,   53,   53,
   53,   53,   53,   53,   53,   53,   53,   53,    0,    0,
    0,   54,   54,   54,   54,   54,   54,   54,   54,   54,
   54,   54,   54,   54,   54,   54,   56,    0,   58,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   67,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   87,   88,    0,    0,   91,   92,   93,
   94,   95,   96,   97,   98,   99,  100,  101,  102,  103,
  104,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  104,    0,    0,  118,
};
static const YYINT yycheck[] = {                         42,
   43,   44,   45,   59,   47,   59,   42,   43,   59,   45,
   59,   47,   59,  100,   44,   61,   59,   60,   59,   62,
   42,   43,  100,   45,   60,   47,   62,  123,  100,   42,
   43,   17,   45,   56,   47,   43,   44,   45,   60,   42,
   62,  113,   28,   59,   47,   68,  273,  112,   44,  274,
   98,   59,   60,   44,   62,   98,   43,   44,   45,  257,
  258,  259,   98,   59,  274,  275,  276,  113,   98,  112,
   58,  123,   59,   60,   59,   62,   42,   43,   61,   45,
  123,   47,   42,   43,  125,   45,  109,   47,   42,   43,
   98,   45,  125,   47,   60,   44,   62,  262,   98,   44,
   60,  123,   62,   44,  112,   61,   60,    0,   62,   42,
   43,   98,   45,   59,   47,  123,   98,  100,   59,   60,
   98,   62,   59,   98,   44,  112,   98,   60,   59,   62,
  113,    6,   36,   28,   34,   27,  123,   64,  107,   59,
   60,   84,   62,  117,  112,   15,   -1,   -1,   -1,   -1,
   -1,   -1,  112,   -1,   -1,   -1,   -1,   98,  112,   -1,
   -1,   -1,   -1,   -1,  260,   -1,   -1,  263,  264,  265,
  266,  112,   -1,   -1,   -1,   -1,   -1,  273,   98,   -1,
   -1,   -1,  123,   -1,   -1,   -1,  273,  274,  275,  276,
  277,   -1,  112,   -1,   -1,  273,  274,  275,  276,   -1,
   -1,   -1,   -1,  123,   -1,   -1,  262,   -1,  262,   -1,
   -1,  262,   -1,  262,   -1,  262,   -1,  260,  261,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,  272,
  273,  267,  268,  269,  270,  271,  272,   -1,  260,   -1,
   -1,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  272,  273,  260,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  272,  273,  262,   -1,   -1,   -1,
   -1,   -1,   -1,  260,  261,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,  272,  273,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  261,   -1,   -1,   -1,   -1,
   -1,  267,  268,  269,  270,  271,  272,  267,  268,  269,
  270,  271,  272,  267,  268,  269,  270,  271,  272,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,   -1,  267,  268,  269,  270,  271,  272,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  272,  273,   44,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,
   60,   44,   62,   -1,   -1,   -1,   -1,   -1,   10,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   59,   60,   44,   62,
   -1,   -1,   -1,   25,   -1,   -1,   -1,   -1,   -1,   -1,
   32,   -1,   -1,   59,   60,   44,   62,   39,   98,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   59,   60,  112,   62,   56,   98,   -1,   -1,   44,   -1,
   -1,   -1,   64,  123,   -1,   -1,   68,   -1,   -1,  112,
   -1,   -1,   98,   59,   60,   44,   62,   -1,   -1,   -1,
  123,   -1,   -1,   -1,   -1,   -1,  112,   -1,   -1,   98,
   59,   60,   -1,   62,   -1,   -1,   -1,  123,   -1,   -1,
   -1,   -1,   -1,  112,   -1,   -1,   -1,  109,   -1,   -1,
   -1,   -1,   98,   -1,  123,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  112,   -1,   -1,   98,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,   -1,
   -1,   -1,   -1,  112,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  123,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  272,  273,   -1,   -1,   -1,  260,  261,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,  272,
  273,   -1,   -1,   -1,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,  272,  273,   -1,   -1,
   -1,  260,  261,  262,  263,  264,  265,  266,  267,  268,
  269,  270,  271,  272,  273,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,  272,  273,   -1,   -1,
   -1,  260,  261,  262,  263,  264,  265,  266,  267,  268,
  269,  270,  271,  272,  273,   37,   38,   -1,   40,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   53,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   65,   66,   -1,   -1,   69,   70,   71,
   72,   73,   74,   75,   76,   77,   78,   79,   80,   81,
   82,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  112,   -1,   -1,  115,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 278
#define YYUNDFTOKEN 305
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,0,0,0,0,"'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,"':'",
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,"'b'",0,"'d'",0,0,0,0,0,0,0,0,0,0,0,"'p'","'q'",0,0,0,0,0,0,0,0,0,
"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_CHAR","KW_INT","KW_FLOAT","KW_IF",
"KW_THEN","KW_ELSE","KW_WHILE","KW_READ","KW_RETURN","KW_PRINT","OPERATOR_LE",
"OPERATOR_GE","OPERATOR_EQ","OPERATOR_OR","OPERATOR_AND","OPERATOR_NOT",
"TK_IDENTIFIER","LIT_INTEGER","LIT_FLOAT","LIT_CHAR","LIT_STRING","TOKEN_ERROR",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : declarationList",
"declarationList : declaration declarationList",
"declarationList :",
"declaration : globalVar ';'",
"declaration : function",
"globalVar : type identifier '=' initValue",
"globalVar : vector",
"vector : type identifier 'q' LIT_INTEGER 'p'",
"vector : type identifier 'q' LIT_INTEGER 'p' ':' moreInitValue",
"moreInitValue : initValue moreInitValue",
"moreInitValue :",
"function : type identifier 'd' paramList 'b' block",
"paramList : param moreParam",
"paramList :",
"param : type identifier",
"moreParam : ',' param moreParam",
"moreParam :",
"block : '{' commandList '}'",
"commandList : command ';' commandList",
"commandList :",
"command : attribution",
"command : controlFlow",
"command : KW_READ identifier",
"command : KW_PRINT printables",
"command : KW_RETURN expression",
"command : block",
"command :",
"attribution : identifier '=' expression",
"attribution : identifier 'q' expression 'p' '=' expression",
"controlFlow : KW_IF expression KW_THEN command",
"controlFlow : KW_IF expression KW_THEN command KW_ELSE command",
"controlFlow : KW_WHILE expression command",
"printables : printable morePrintables",
"printable : LIT_STRING",
"printable : expression",
"morePrintables : ',' printable morePrintables",
"morePrintables :",
"expression : identifier",
"expression : identifier 'q' expression 'p'",
"expression : LIT_INTEGER",
"expression : LIT_FLOAT",
"expression : LIT_CHAR",
"expression : expression OPERATOR_LE expression",
"expression : expression OPERATOR_GE expression",
"expression : expression OPERATOR_EQ expression",
"expression : expression OPERATOR_OR expression",
"expression : expression OPERATOR_AND expression",
"expression : expression OPERATOR_NOT expression",
"expression : expression '+' expression",
"expression : expression '-' expression",
"expression : expression '*' expression",
"expression : expression '/' expression",
"expression : expression '<' expression",
"expression : expression '>' expression",
"expression : 'd' expression 'b'",
"expression : identifier 'd' argumentList 'b'",
"argumentList : argument moreArgument",
"argumentList :",
"argument : expression",
"moreArgument : ',' argument moreArgument",
"moreArgument :",
"type : KW_CHAR",
"type : KW_FLOAT",
"type : KW_INT",
"initValue : LIT_CHAR",
"initValue : LIT_FLOAT",
"initValue : LIT_INTEGER",
"identifier : TK_IDENTIFIER",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 201 "parser.y"

 /* Subroutines */

void yyerror(char *error){
    fprintf(stderr, "Error[Line %d]: %s\n", getLineNumber(), error);
    exit(3);
}
#line 466 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 58 "parser.y"
	{ astTree = ast_create(AST_PROGRAM, 0, yystack.l_mark[0].ast, 0, 0, 0); semanticCheck(yystack.l_mark[0].ast); }
break;
case 2:
#line 62 "parser.y"
	{ yyval.ast = ast_create(AST_DECLARATION_LIST, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 3:
#line 63 "parser.y"
	{ yyval.ast = 0; }
break;
case 4:
#line 67 "parser.y"
	{ yyval.ast = yystack.l_mark[-1].ast; }
break;
case 5:
#line 68 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 6:
#line 72 "parser.y"
	{ yyval.ast = ast_create(AST_GLOBAL_SCALAR, 0, yystack.l_mark[-3].ast, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0); }
break;
case 7:
#line 73 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 8:
#line 77 "parser.y"
	{ yyval.ast = ast_create(AST_GLOBAL_VECTOR, 0, yystack.l_mark[-4].ast, yystack.l_mark[-3].ast, ast_create(AST_SYMBOL, yystack.l_mark[-1].symbol, 0, 0, 0, 0), 0); }
break;
case 9:
#line 78 "parser.y"
	{ yyval.ast = ast_create(AST_GLOBAL_VECTOR, 0, yystack.l_mark[-6].ast, yystack.l_mark[-5].ast, ast_create(AST_SYMBOL, yystack.l_mark[-3].symbol, 0, 0, 0, 0), yystack.l_mark[0].ast); }
break;
case 10:
#line 82 "parser.y"
	{ yyval.ast = ast_create(AST_GLOBAL_VECTOR_VALUES, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 11:
#line 83 "parser.y"
	{ yyval.ast = 0; }
break;
case 12:
#line 87 "parser.y"
	{ yyval.ast = ast_create(AST_FUNCTION, 0, yystack.l_mark[-5].ast, yystack.l_mark[-4].ast, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 13:
#line 91 "parser.y"
	{ yyval.ast = ast_create(AST_FUNCTION_PARAMS, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 14:
#line 92 "parser.y"
	{ yyval.ast = 0; }
break;
case 15:
#line 96 "parser.y"
	{ yyval.ast = ast_create(AST_FUNCTION_PARAM, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 16:
#line 100 "parser.y"
	{ yyval.ast = ast_create(AST_FUNCTION_PARAMS, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 17:
#line 101 "parser.y"
	{ yyval.ast = 0; }
break;
case 18:
#line 105 "parser.y"
	{ yyval.ast = ast_create(AST_BLOCK, 0, yystack.l_mark[-1].ast, 0, 0, 0); }
break;
case 19:
#line 109 "parser.y"
	{ yyval.ast = ast_create(AST_COMMAND, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 20:
#line 110 "parser.y"
	{ yyval.ast = 0; }
break;
case 21:
#line 114 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 22:
#line 115 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 23:
#line 116 "parser.y"
	{ yyval.ast = ast_create(AST_READ, 0, yystack.l_mark[0].ast, 0, 0, 0); }
break;
case 24:
#line 117 "parser.y"
	{ yyval.ast = ast_create(AST_PRINT, 0, yystack.l_mark[0].ast, 0, 0, 0); }
break;
case 25:
#line 118 "parser.y"
	{ yyval.ast = ast_create(AST_RETURN, 0, yystack.l_mark[0].ast, 0, 0, 0); }
break;
case 26:
#line 119 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 27:
#line 120 "parser.y"
	{ yyval.ast = 0; }
break;
case 28:
#line 124 "parser.y"
	{ yyval.ast = ast_create(AST_LOCAL_SCALAR, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 29:
#line 125 "parser.y"
	{ yyval.ast = ast_create(AST_LOCAL_VECTOR, 0, yystack.l_mark[-5].ast, yystack.l_mark[-3].ast, yystack.l_mark[0].ast, 0); }
break;
case 30:
#line 129 "parser.y"
	{ yyval.ast = ast_create(AST_IF, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 31:
#line 130 "parser.y"
	{ yyval.ast = ast_create(AST_IF_ELSE, 0, yystack.l_mark[-4].ast, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0); }
break;
case 32:
#line 131 "parser.y"
	{ yyval.ast = ast_create(AST_WHILE, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 33:
#line 135 "parser.y"
	{ yyval.ast = ast_create(AST_PRINTABLES, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 34:
#line 139 "parser.y"
	{ yyval.ast = ast_create(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 35:
#line 140 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 36:
#line 144 "parser.y"
	{ yyval.ast = ast_create(AST_PRINTABLES, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 37:
#line 145 "parser.y"
	{ yyval.ast = 0; }
break;
case 38:
#line 149 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 39:
#line 150 "parser.y"
	{ yyval.ast = ast_create(AST_VECTOR, 0, yystack.l_mark[-3].ast, yystack.l_mark[-1].ast, 0, 0); }
break;
case 40:
#line 151 "parser.y"
	{ yyval.ast = ast_create(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 41:
#line 152 "parser.y"
	{ yyval.ast = ast_create(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 42:
#line 153 "parser.y"
	{ yyval.ast = ast_create(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 43:
#line 154 "parser.y"
	{ yyval.ast = ast_create(AST_LE, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 44:
#line 155 "parser.y"
	{ yyval.ast = ast_create(AST_GE, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 45:
#line 156 "parser.y"
	{ yyval.ast = ast_create(AST_EQ, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 46:
#line 157 "parser.y"
	{ yyval.ast = ast_create(AST_OR, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 47:
#line 158 "parser.y"
	{ yyval.ast = ast_create(AST_AND, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 48:
#line 159 "parser.y"
	{ yyval.ast = ast_create(AST_NOT, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 49:
#line 160 "parser.y"
	{ yyval.ast = ast_create(AST_ADD, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 50:
#line 161 "parser.y"
	{ yyval.ast = ast_create(AST_SUB, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 51:
#line 162 "parser.y"
	{ yyval.ast = ast_create(AST_MUL, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 52:
#line 163 "parser.y"
	{ yyval.ast = ast_create(AST_DIV, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 53:
#line 164 "parser.y"
	{ yyval.ast = ast_create(AST_LT, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 54:
#line 165 "parser.y"
	{ yyval.ast = ast_create(AST_GT, 0, yystack.l_mark[-2].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 55:
#line 166 "parser.y"
	{ yyval.ast = ast_create(AST_PARENTHESES, 0, yystack.l_mark[-1].ast, 0, 0, 0); }
break;
case 56:
#line 167 "parser.y"
	{ yyval.ast = ast_create(AST_FUNCTION_CALL, 0, yystack.l_mark[-3].ast, yystack.l_mark[-1].ast, 0, 0); }
break;
case 57:
#line 171 "parser.y"
	{ yyval.ast = ast_create(AST_FUNCTION_CALL_ARGS, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 58:
#line 172 "parser.y"
	{ yyval.ast = 0; }
break;
case 59:
#line 176 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 60:
#line 180 "parser.y"
	{ yyval.ast = ast_create(AST_FUNCTION_CALL_ARGS, 0, yystack.l_mark[-1].ast, yystack.l_mark[0].ast, 0, 0); }
break;
case 61:
#line 181 "parser.y"
	{ yyval.ast = 0; }
break;
case 62:
#line 185 "parser.y"
	{ yyval.ast = ast_create(AST_KW_CHAR, 0, 0, 0, 0, 0); }
break;
case 63:
#line 186 "parser.y"
	{ yyval.ast = ast_create(AST_KW_FLOAT, 0, 0, 0, 0, 0); }
break;
case 64:
#line 187 "parser.y"
	{ yyval.ast = ast_create(AST_KW_INT, 0, 0, 0, 0, 0); }
break;
case 65:
#line 191 "parser.y"
	{ yyval.ast = ast_create(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 66:
#line 192 "parser.y"
	{ yyval.ast = ast_create(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 67:
#line 193 "parser.y"
	{ yyval.ast = ast_create(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 68:
#line 197 "parser.y"
	{ yyval.ast = ast_create(AST_SYMBOL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
#line 940 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
