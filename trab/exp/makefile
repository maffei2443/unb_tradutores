FLAGS = -DSILENT -g
BFLAGS = -vdg
simple: Tree.o simple_lexico.l simple_grammar.y
	gcc -c Tree.c
	bison $(BFLAGS) simple_grammar.y
	flex simple_lexico.l
	gcc $(FLAGS) -o $@ lex.yy.c simple_grammar.tab.c Tree.o

lexico: lexico.l print.o new_grammar.y
	bison $(BFLAGS) new_grammar.y
	flex lexico.l
	cc $(FLAGS) -o $@ new_grammar.tab.c lex.yy.c Array.c \
		Colorfy.c Common.h Prints.o


all: Tree.o lexico.l new_grammar.y Prints.o Prints.c Colorfy.o Array.o
	gcc -c Tree.c
	gcc -c Prints.c
	bison $(BFLAGS) new_grammar.y
	flex lexico.l
	gcc $(FLAGS) -o $@ lex.yy.c new_grammar.tab.c Tree.o Prints.o Colorfy.o Array.o Common.h

tree: Tree.o simTree.c
	gcc $(FLAGS) -o $@ simTree.c Tree.o

Tree.o: Tree.h Tree.c
	gcc -c Tree.c

Prints.o:	Prints.h Prints.c
	gcc -c Prints.c

Colorfy.o: Colorfy.h Colorfy.c
	gcc -c Colorfy.c

Array.o: Array.h Array.c
	gcc -c Array.c