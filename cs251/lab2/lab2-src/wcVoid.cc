//
// CS251 Program that prints the occurrences of the words of a file
// This program is incomplete. 
//


#include <stdio.h>
#include "HashTableVoid.h"

#define MAXWORD 1024

struct WordCount {
  const char * word;
  int count;
};

void usage()
{
  fprintf(stderr, "Usage: wcVoid file\n");
}

int main(int argc, char **argv) {
  if (argc <2) {
    usage();
    exit(1);
  }
  
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file %s\n", argv[1]);
    perror("fopen");
    exit(1);
  }

  HashTableVoid table;

  int ch;
  char word[MAXWORD];
  int count = 0;
  printf("Reading file %s...\n\n", argv[1]);
  printf("WORDS\n", argv[1]);
  printf("-----------------------\n", argv[1]);
  while (1) {

    // Keep reading to skip spaces
    ch = fgetc(f);    
    while (ch > 0 && (ch==' '|| ch=='\t' || ch== '\n')) {
      // Skip spaces
      ch = fgetc(f);
    }

    if (ch <=0) {
      break;
    }
    
    // Found a word. Keep reading to parse word
    int i = 0;
    while (ch > 0 && ch!=' '&& ch!='\t' && ch!= '\n') {
      word[i]=ch;
      i++;
      ch = fgetc(f);
    }

    // print word
    word[i]=0;
    printf("%d:%s\n", count, word);

    // Add word to table
    WordCount * wc;
    bool found = table.find(word, (void**) &wc);
    if (!found) {
      // Add to table
      wc = new WordCount();
      wc->word = strdup(word);
      wc->count = 0;
      table.insertItem(word, (void*)wc);
    }
    wc->count++;
    
    count++;
    
  }

  printf("\nHISTOGRAM\n", argv[1]);
  printf("-----------------------\n", argv[1]);
  HashTableVoidIterator iterator(&table);
  WordCount * wc;
  void * wcp;
  const char * key;
  while (iterator.next(key, wcp)) {
    wc = (WordCount *)wcp;
    printf("%-20s %d\n", wc->word, wc->count);
  }
  
  fclose(f);
  
}


