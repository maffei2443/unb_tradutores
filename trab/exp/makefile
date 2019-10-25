all: Tree.o lexico.l
	bison -vd grammar.y
	flex lexico.l
	gcc -g -o main lex.yy.c grammar.tab.c Tree.o

sim: Tree.o
	gcc -g -o sim simTree.c Tree.o

Tree.o: Tree.h
	gcc -c Tree.c
