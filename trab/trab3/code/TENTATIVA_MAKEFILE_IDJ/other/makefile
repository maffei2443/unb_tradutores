FLAGS = #-W-no-incompatible-pointer-types \
	#  -Wno-implicit-function-declaration 
	 

all: lexico.l grammar.y print.o
	bison -vd grammar.y
	flex lexico.l
	cc -o $(FLAGS) $@ grammar.tab.c lex.yy.c Array.c Colorfy.c \
		Common.h Prints.o grammar.tab.h -lfl
print.o:	Prints.h
	gcc -c Prints.c

run:
	./all

clean:
	rm -f *.o all 
