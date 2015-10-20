#include <stdio.h>

bool isSolve = false;
int * nums;
int * finalnum;
int * exp;
int * finalexpc;
int length;
//int count = 0;

void adder(int* a, int result, int n) {
	if(isSolve)
		return;
	if(n == 0) {
//		count++;
		if(result == 45) {
			isSolve = true;
			for(int i = 0; i < 5; i++) {
			printf("%d\n", nums[i]);
				if(i < 4)
					finalexpc[i] = exp[i];
				finalnum[i] = nums[i];
			}
		}
/*		else
			printf("result here: %d", result);*/
		return;
	}


for(int i = 0; i < n; i++) {
	printf("%d ",a[i]);
	int *b = new int[n - 1];
	int count = 0;
	for(int j = 0; j < n; j++){
		if(i == j)
			continue;
		b[count] = a[j];
		count++;
	}
	printf("\n");
	if(n == 5) {
		nums[0] = a[i];

		adder(b, a[i], n-1);
		delete [] b;
	}else {
	nums[length-n] = a[i];
	if(n < 5)
		exp[length-n - 1] = 0;
	adder(b, result + a[i], n-1);
	if(n < 5)
		exp[length - n - 1] = 1;
	adder(b, result - a[i], n-1);
	if(n < 5);
		exp[length - n - 1] = 2;
	adder(b, result * a[i], n-1);
	if(a[i] != 0 && (result % a[i] == 0)) {
		if(n < 5)
		exp[length-n - 1] = 3;
		adder(b, result / a[i], n-1);
	}
	delete []b;
}
}
/*
	for(int i = 0; i < n; i++) {
		int *b = new int[n-1];
		int count = 0;
		for(int j = 0; j < n; j++) {
			if(count == i)
				continue;
			b[count] = a[j];
			count++;
		}
		if(n == 5) {
		printf("here\n");
		//	result = a[i];
			nums[0] = a[i];
			adder(b, a[i], n-1);
			adder(b, a[i]*-1, n-1);
			delete[] b;
		}
		else {	
		nums[length-n] = a[i];
		exp[length-n-1] = 0;
		adder(b, result + a[i], n-1);
		exp[length-n-1] = 1;
		adder(b, result - a[i], n-1);
		exp[length-n-1] = 2;
		adder(b, result * a[i], n-1);
		if(a[i] != 0 && result % a[i] == 0 && result != 0) {
			exp[length-n-1] = 3;
			adder(b, result / a[i], n-1);
		}
		delete[] b;
		}
	}*/
}

int main() {
	int a[] = {1,2,2,9,1};
	nums = new int[5];
	exp = new int[5];
	finalexpc = new int[5];
	finalnum = new int[5];
	length = 5;
	adder(a, 0, 5 );
	if(isSolve){
		printf("solvable!\n");
		char *expc = new char[4];
		for(int i = 0; i < 4; i++) {
			switch(finalexpc[i]) {
			case 0: finalexpc[i] = '+';
				break;
			case 1: finalexpc[i] = '-';
				break;
			case 2: finalexpc[i] = '*';
				break;
			default: finalexpc[i] = '/';
				break;
			}
		}
		printf("(((%d %c %d) %c %d) %c %d) %c %d = 45\n", finalnum[0], finalexpc[0], finalnum[1], finalexpc[1], finalnum[2], finalexpc[2], finalnum[3], finalexpc[3], finalnum[4]);
	}
	else
		printf("Nah.\n");

//printf("count:%d\n", count);
}
