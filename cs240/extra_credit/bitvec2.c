#include<stdio.h>
#include<stdlib.h>

unsigned char compare[] = {128, 64, 32, 16, 8, 4, 2, 1};

typedef struct bitvec {
	unsigned char* bit;
	short size;
} Bitvector;

Bitvector* bv_make(short size) {
	Bitvector *bv = (Bitvector*)malloc(sizeof(Bitvector));
	bv->size = size / 8 + 1;
	bv->bit = (char*)calloc(size/8 + 1, sizeof(char));
}

short bv_get(int index, Bitvector *bv) {
	int i = index / 8; // index for char
	int r = index % 8; // reminder
	printf("Now comparing: %d and %d\n",bv->bit[i],compare[r]);
	return((bv->bit[i] & compare[r]) != 0);
}

void bv_set(int index, Bitvector *bv) {
	int i = index / 8;
	int r = index % 8;
	printf("right now setting it into: %d\n", bv->bit[i] | compare[r]);
	bv->bit[i] =(bv->bit[i] | compare[r]);
}

void bv_free(Bitvector *bv) {
	free(bv->bit);
	free(bv);
}

void bv_print(Bitvector *bv) {
	for(int i = 0; i < bv->size; i++) {
		printf("%d\t", bv->bit[i]);
	}
	printf("\n");
}

int main() {
	Bitvector *bv = bv_make(15);
	bv_print(bv);
	bv_set(3, bv);
	bv_set(3, bv);
	printf("getting!\n");
	printf("%d\n",bv_get(1, bv));
	printf("%d\n",bv_get(3, bv));
	bv_print(bv);
}
