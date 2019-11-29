FLAGS = -DSILENT -g
BFLAGS = -vdg
all: Tree.o lexico.l new_grammar.y Prints.o Prints.c Colorfy.o Array.o SemanticChecker.c
	bison $(BFLAGS) new_grammar.y
	flex lexico.l
	gcc -c SemanticChecker.c
	gcc $(FLAGS) -o $@ lex.yy.c new_grammar.tab.c Tree.o Prints.o Colorfy.o Array.o SemanticChecker.o

lexico: lexico.l print.o new_grammar.y 
	bison $(BFLAGS) new_grammar.y
	flex lexico.l
	cc $(FLAGS) -o $@ new_grammar.tab.c lex.yy.c Array.c \
		Colorfy.c  Prints.o



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

SemanticChecker.o: SemanticChecker.c SemanticChecker.h new_grammar.tab.h		
	bison $(BFLAGS) new_grammar.y
	gcc -c SemanticChecker.c

clean:
	rm *.o all
	rm lex.yy.c
	rm new_grammar.tab.* new_grammar.output new_grammar.dot