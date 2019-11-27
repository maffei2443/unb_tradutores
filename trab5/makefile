FLAGS = -DSILENT -g
BFLAGS = -vdg
all: Tree.o lexico.l new_grammar.y Prints.o Prints.c Colorfy.o Array.o code_gen.o SemanticChecker.c
	bison $(BFLAGS) new_grammar.y
	flex lexico.l
	gcc $(FLAGS) -c SemanticChecker.c
	# gcc $(FLAGS) -c code_gen.c
	gcc $(FLAGS) -o $@ lex.yy.c new_grammar.tab.c Tree.o Prints.o Colorfy.o Array.o SemanticChecker.c code_gen.o

lexico: lexico.l print.o new_grammar.y 
	bison $(BFLAGS) new_grammar.y
	flex lexico.l
	cc $(FLAGS) -o $@ new_grammar.tab.c lex.yy.c Array.c \
		Colorfy.c  Prints.o



tree: Tree.o simTree.c
	gcc $(FLAGS) -o $@ simTree.c Tree.o

Tree.o: Tree.h Tree.c code_gen.h
	gcc $(FLAGS) -c Tree.c

Prints.o:	Prints.h Prints.c
	gcc $(FLAGS) -c Prints.c

Colorfy.o: Colorfy.h Colorfy.c
	gcc $(FLAGS) -c Colorfy.c

Array.o: Array.h Array.c
	gcc $(FLAGS) -c Array.c

code_gen.o: code_gen.h code_gen.c Array.o
	gcc $(FLAGS) -c code_gen.c

clean:
	rm *.o all
	rm lex.yy.c
	rm new_grammar.tab.* new_grammar.output new_grammar.dot