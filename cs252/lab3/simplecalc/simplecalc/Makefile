# Makefile for simplecalc

cc=gcc

CFLAGS= -g
LEX=lex
YACC=yacc

all: calc

lex.yy.o: simplecalc.l y.tab.h
	$(LEX) simplecalc.l
	$(CC) -c lex.yy.c

y.tab.o: simplecalc.y
	$(YACC) -d simplecalc.y
	$(CC) -c y.tab.c

calc: y.tab.o lex.yy.o
	$(CC) -o calc lex.yy.o y.tab.o -lfl

clean:
	rm -f lex.yy.c y.tab.c y.tab.h calc *.o

