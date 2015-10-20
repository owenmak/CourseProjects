#include<stdio.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<string.h>
//#include"Heap.h"
using namespace std;
int main() {
	string s = "12345   ";
	string d = s;
	s = "WWWWWWWWWWWWWWWWW";
	cout << d << endl;
	printf("%d\n", atoi(s.c_str()));
/*	Heap h(20);

	h.insert(5);

	h.insert(10);

	h.insert(3);

	h.insert(99);
	
	for(int i = 0; i < 4; i++)
		printf("%d\t", h.removeMin());*/
	char a[] = "Joey";
	char b[] = "Rachael";
	int c = strcmp(a,b);
	if(c > 0)
		printf("bigger"); 
	else if(c < 0)
		printf("smaller");
	else
		printf("The same");
/*	haha* h;
	h = new haha[4];
	for(int i = 0; i < 4; i++) {
		h[i].num = i;
	}
	haha* m;
	m = new haha[8];
	for(int i = 0; i < 4; i++) {
		m[i] = h[i];
	}*/
}
