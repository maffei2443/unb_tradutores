FLAGS = -DSILENT -g
BFLAGS = -vdg
all: Tree.o lex.yy.o new_grammar.tab.o Prints.o Prints.c \
	Colorfy.o Array.o code_gen.o SemanticChecker.o	Common.o Stack.o	
	gcc $(FLAGS) -o $@ lex.yy.o new_grammar.tab.o Tree.o Prints.o Colorfy.o \
		Array.o SemanticChecker.o code_gen.o Common.o Stack.o

# lexico: lexico.l print.o new_grammar.y 
# 	bison $(BFLAGS) new_grammar.y
# 	flex lexico.l
# 	cc $(FLAGS) -o $@ new_grammar.tab.c lex.yy.c Array.c \
# 		Colorfy.c  Prints.o

lex.yy.o: lexico.l new_grammar.tab.o
	flex lexico.l
	gcc -c lex.yy.c

new_grammar.tab.o: new_grammar.y Common.o Common.h
	bison $(BFLAGS) new_grammar.y
	gcc -c new_grammar.tab.c Common.h

SemanticChecker.tab.o: SemanticChecker.c SemanticChecker.h new_grammar.tab.h Common.o
	gcc $(FLAGS) -c SemanticChecker.c Common.h


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

code_gen.o: code_gen.h code_gen.c Array.o Common.o
	gcc $(FLAGS) -c code_gen.c Common.o

Common.o: Common.h Common.c 
	gcc $(FLAGS) -c Common.c

Stack.o: Stack.h Stack.c
	gcc $(FLAGS) -c Stack.c

clean:
	rm *.o all
	rm lex.yy.c
	rm new_grammar.tab.* new_grammar.output new_grammar.dot