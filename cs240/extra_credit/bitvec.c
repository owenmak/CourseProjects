#include <stdio.h>
#include <stdlib.h>

typedef struct bitvec {
	short *bit;
	short size;
} Bitvector;

Bitvector* bv_make(short size) {
	Bitvector *bv = (Bitvector*)(malloc)(sizeof(Bitvector));
	bv->bit = (short*)calloc(size,sizeof(short));
	bv->size = size;
	return bv;
}

void bv_free(Bitvector *bv) {
	free(bv->bit);
	free(bv);
}

short bv_get(int i, Bitvector *bv) {
	return bv->bit[i];
}

void bv_set(int index, Bitvector *bv) {
	bv->bit[index] = 1;
}

void print(Bitvector *bv) {
	for(int i = 0; i < bv->size; i++) {
		printf("%d", bv->bit[i]);
	}
	printf("\n");
}

int main() {
	Bitvector *bv = bv_make(7);
	bv_set(3, bv);
	printf("value:%d\n", bv_get(2, bv));
	print(bv);
	bv_free(bv);
}
