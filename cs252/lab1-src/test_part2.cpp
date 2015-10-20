#include <stdio.h>
#include <stdlib.h>

extern int etext, edata, end;

void print_segment_locations();
void report(const char *var, const char *section);
void report_results();

int a = 5; 
int b; 
static int c; 

class class1 { 
  static int m1; 
}; 

int main() { 
  print_segment_locations();
  int d;
  static int e = 0;
  static int f = 1;
  int array[10];
  char *ptr1 = new char[100];
  char *ptr2 = (char *)malloc(10 * sizeof(char));
  report_results();
  return 0;
}

#define MEM_UNKNOWN "unknown"
#define MEM_STACK "stack"
#define MEM_HEAP "heap"
#define MEM_DATA "data"
#define MEM_BSS "bss"
#define MEM_TEXT "text"

void report_results() {
  report("a", MEM_DATA);
  report("b", MEM_BSS);
  report("c", MEM_BSS);
  report("m1", MEM_BSS);
  report("d", MEM_STACK);
  report("e", MEM_BSS);
  report("f", MEM_DATA);
  report("array", MEM_STACK);
  report("ptr1", MEM_HEAP);
  report("ptr2", MEM_HEAP);

}

void report(const char *var, const char *section) {
  printf("%s: %s\n", var, section);
}


void print_segment_locations() {
  printf("End address of text is %10p\n", &etext);
  printf("End address of edata is %10p\n", &edata);
  printf("BSS address is %10p\n", &end);
}
