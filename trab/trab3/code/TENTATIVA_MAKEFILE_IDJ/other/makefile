print.o:	Prints.h
	gcc -c Prints.c

all: lexico.l grammar.y print.o
	bison -d grammar.y
	flex lexico.l
	cc -o $@ grammar.tab.c lex.yy.c Array.c Colorfy.c \
		Common.h Prints.o grammar.tab.h -lfl

clean:
	rm all
