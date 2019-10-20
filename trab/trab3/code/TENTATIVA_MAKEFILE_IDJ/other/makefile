FLAGS = 

all: lexico.l grammar.y print.o Function.h
	bison -vd grammar.y
	flex lexico.l
	cc -o $(FLAGS) $@ grammar.tab.c lex.yy.c Array.c Function.c Colorfy.c Common.h Prints.o

print.o:	Prints.h
	gcc -c Prints.c

Function.o:	Function.h
	gcc -c Function.c
run:
	./all
clean:
	rm -f *.o all 
