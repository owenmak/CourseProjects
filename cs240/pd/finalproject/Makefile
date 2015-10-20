all: dt.c rf.c pd_main.c tree.c confmatrix.c cargs.c *.a
	gcc -std=c99 -g -o rf pd_main.c cargs.c rf.c dt.c tree.c confmatrix.c *.a -m32 -lm
