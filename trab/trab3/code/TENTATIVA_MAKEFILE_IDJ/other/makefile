all: lexico.l grammar.y
	bison -d grammar.y
	flex lexico.l
	cc -o $@ grammar.tab.c lex.yy.c Array.c Colorfy.c -lfl