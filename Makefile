#
# UFRGS - Compiladores B - Marcelo Johann - 2018/2 - Etapa 5
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa5: y.tab.o lex.yy.o main.o hash.o ast.o semantic.o tac.o
	gcc -o etapa5 lex.yy.o main.o hash.o ast.o semantic.o tac.o y.tab.o
main.o: main.c
	gcc -c main.c
tac.o: tac.c
	gcc -c tac.c
semantic.o: semantic.c
	gcc -c semantic.c
ast.o: ast.c
	gcc -c ast.c
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l 
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc -d parser.y
clean:
	rm *.o lex.yy.c lex.yy.h y.tab.c y.tab.h etapa5