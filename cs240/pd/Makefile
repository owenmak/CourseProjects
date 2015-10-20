all: dt.c rf.c pd_main.c tree.c confmatrix.c cargs.c *.a
	gcc -std=c99 -g -o pd pd_main.c cargs.c rf.c dtEdited.c tree.c confmatrix.c *.a -m32 -lm
