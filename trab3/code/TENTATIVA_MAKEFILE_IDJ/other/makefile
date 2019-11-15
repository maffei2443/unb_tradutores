FLAGS = -DSILENT -g

all: lexico.l grammar.y print.o Function.h
	bison -vd --graph grammar.y
	flex lexico.l
	cc $(FLAGS) -o $@ grammar.tab.c lex.yy.c Array.c Function.c ShowTree.c Colorfy.c Common.h Prints.o

print.o:	Prints.h
	gcc -c Prints.c

Function.o:	Function.h
	gcc -c Function.c

ShowTree.o: ShowTree.h
	gcc -c ShowTree

run:
	./all
clean:
	rm -f *.o all 
