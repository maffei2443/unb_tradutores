# IDIR=../include
# ODIR=../obj
# CC=gcc
# CFLAGS=-I.

# Array.o:
# 	$(CC) Array.c -c 

# SymTable.o: 
# 	$(CC) SymTable.c -c

# main.c: Array.o SymTable.o 
# 	$(CC) main.c -o run Array.o SymTable.o

# .PHONY: clean

# clean:
# 	rm *.o

IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -g

ODIR=../obj

LIBS=-lfl

_DEPS = Array.h SymTable.h Colorfy.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Array.o SymTable.o Colorfy.o lex.yy.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# main: $(OBJ)
# 	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
lexico: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 