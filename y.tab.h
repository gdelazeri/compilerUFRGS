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
extern YYSTYPE yylval;
