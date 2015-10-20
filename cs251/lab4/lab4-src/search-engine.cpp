#include <time.h>
#include <string.h>
#include "search-engine.h"
#include <stdlib.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#define BILLION 1E9
using namespace std;
int TypeIndex;
SearchEngine::SearchEngine( int port, DictionaryType dictionaryType):
  MiniHTTPD(port)
{
	if(dictionaryType == ArrayDictionaryType){
		_wordToURLList = new ArrayDictionary();
		TypeIndex = 0;
	}
	else if(dictionaryType == HashDictionaryType) {
		_wordToURLList = new HashDictionary();
		TypeIndex = 1;
	}
	else if(dictionaryType == AVLDictionaryType) {
		_wordToURLList = new AVLDictionary();
		TypeIndex = 2;
	}
	else{
		_wordToURLList = new BinarySearchDictionary();
		TypeIndex = 3;
	}

	_URLCount = 0;
	ifstream infile;
	infile.open("word.txt");
	char c;
	string s;
	while(!infile.eof()) {
	    getline(infile, s);
	    if(s.length() == 0)
	        continue;
	    int word_count = 0;
	    for(int i = 0; i < s.length(); i++) {
    	    if(s[i] == ' ')  // getting the word.
	            break;
   	    	word_count++;
   		}
		char *word;
		word = (char*)malloc(sizeof(char) * (word_count + 1));
   		for(int i = 0; i < word_count; i++) {
        	word[i] = s[i];
    	}
    	word[word_count] = '\0';
    	char* record;
		record = strdup(s.substr(word_count + 1).c_str()); //storing all the rest as a string.
//    	printf("from searchengine: %s\n",word);
//    	cout << record << endl;
//    	printf("\n");
//		if(!strcmp(word, "rail"))
//			cout << record;

		_wordToURLList->addRecord((const char*)word, (void*) record);
	}
	infile.close();
	infile.open("url.txt"); //pre-run to check for the nums;
	int num =0;
	while(!infile.eof()) {
		getline(infile, s);
		//printf("%c\n",s[0]);
//		cout << s << endl;
		if(s[0] >= '0' && s[0] <= '9')
			num++;
	}
//	printf("HAHA %d\n",num);
	infile.close();
	infile.open("url.txt");
	p = new URLRecord[num];
	_URLCount = num;
//	printf("HEYHEY _URL COUNT IS: %d\n", _URLCount);
	while(!infile.eof()) {
    	getline(infile, s);
	    if(s.length() == 0)
   	    	continue;
    	int word_count = 0;
    	for(int i = 0; i < s.length(); i++) {
        	if(s[i] == ' ')
            	break;
        	word_count++;
    	}
    	int index = atoi(s.substr(0,word_count).c_str());
//    	printf("the index is: %d\n", index);
//    	printf("%s\n",s.substr(word_count+1).c_str()); // THIS IS THE WEBPAGE
		p[index]._url = strdup(s.substr(word_count + 1).c_str());
    	getline(infile, s);
		p[index]._description = strdup(s.c_str());
//    	cout << s << endl;
//    	cout << endl;
	}
	infile.close();
//	for(int i = 0; i < num; i++) {
//		printf("%s\n",p[i]._url);
//	}
	printf("%d",num);
  // Create dictionary of the indicated type

  // Populate dictionary and sort it if necessary
}

void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
  struct timespec Start, End;
  clock_gettime(CLOCK_REALTIME, &Start);
  if (strcmp(documentRequested, "/")==0) {
    // Send initial form
    fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
    fprintf(fout, "<CENTER><H1><em>Boiler Search</em></H1>\n");
    fprintf(fout, "<H2>\n");
    fprintf(fout, "<FORM ACTION=\"search\">\n");
    fprintf(fout, "Search:\n");
    fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
    fprintf(fout, "</H2>\n");
    fprintf(fout, "</FORM></CENTER>\n");
    return;
  }

  // TODO: The words to search in "documentRequested" are in the form
  // /search?word=a+b+c
  //
  // You need to separate the words before search
  // Search the words in the dictionary and find the URLs that
  // are common for al the words. Then print the URLs and descriptions
  // in HTML. Make the output look nicer.
//	printf("%s\n", documentRequested);
	int word_num = 0;
	char **words;
	if(strcmp(documentRequested,"/search?word=")) {
		word_num = 1;
		for(int i = 0; i < strlen(documentRequested); i++) {
			if(documentRequested[i] == '+')
				word_num++;
		}
		words = (char**)malloc(sizeof(char*) * word_num);
		int word_start;
		for(int i = 0; i < strlen(documentRequested); i++) {
			if(documentRequested[i] == '=') {
				word_start = i;
				break;
			}
		}
		char buff[strlen(documentRequested)];
		for(int i = 0; i < strlen(documentRequested); i++) {
			buff[i] = '\0';
		}
		int buff_count = 0;
		int word_count = 0;
		for(int i = word_start + 1; i < strlen(documentRequested); i++) {
			if(documentRequested[i] == '+') {
				words[word_count] = strdup(buff);
				for(int i = 0; i < strlen(documentRequested); i++)
						buff[i] = '\0';
				buff_count = 0;
				word_count++;
			}
			else {
				buff[buff_count] = documentRequested[i];
				buff_count++;
			}
		}
		words[word_count] = strdup(buff);
/*		for(int i = 0; i < word_num; i++) {
			printf("%d:%s\n",i, words[i]);
		}*/
	}
	char* url_index[word_num];
	for(int i = 0; i < word_num; i++) {
		if(_wordToURLList->findRecord(words[i]) != NULL) {
//			printf("trying to find: %s\n", words[i]);
//			printf("found data: %s\n",(const char*) _wordToURLList->findRecord(words[i]));
			url_index[i] = strdup((char*)_wordToURLList->findRecord(words[i]));
		}
		else
			url_index[i] = NULL;
	}
	int url_count[_URLCount];
	for(int i = 0; i < _URLCount; i++)
		url_count[i] = 0;
	for(int i = 0; i < word_num; i++) {
		char buf[20];
		for(int j = 0; j <20; j++) {
			buf[j] = '\0';
		}
		char c;
		int count = 0;
//		printf("The data passed: %s\n", url_index[i]);
		for(int j = 0; j < strlen(url_index[i]); j++) {
			c = url_index[i][j];
			if((j == strlen(url_index[i]) - 1) && count != 0) {
				buf[count] = c;
				url_count[atoi(buf)]++;
				for(int k = 0; k < 20; k++) {
					buf[k] = '\0';
				}
				count = 0;
			}
			else if(c == ' ' ) {
//				printf("Now putting %s into %d\n", buf, atoi(buf));
				url_count[atoi(buf)]++;
				for(int k = 0; k < 20; k++) {
					buf[k] = '\0';
				}
				count = 0;
			}
			else {
				buf[count] = c;
				count++;
			}
		}
	} // storing all the indexs into an array.
//	printf("HEYHEYHEY HERE WE GO%d\n", _URLCount);
	int nurls = 0;
	for(int i = 0; i < _URLCount; i++) {
		if(url_count[i] == word_num) {
			nurls++;
		}
	}
//	printf("nurls: %d", nurls);
	int nurl_count = 0;
	char* urls[nurls];
	char* description[nurls];
	for(int i = 0; i < _URLCount; i++) {
		if(url_count[i] == word_num) {
			urls[nurl_count] = p[i]._url;
			description[nurl_count] = p[i]._description;
			nurl_count++;
		}
	}
	clock_gettime(CLOCK_REALTIME, &End);
  // Here the URLs printed are hardwired
  /*
  const int nurls=2;

  const char * words = "data structures";

  const char * urls[] = {
    "http://www.cs.purdue.edu",
    "http://www.cs.purdue.edu/homes/cs251"
  };
  
  const char * description[] = {
    "Computer Science Department. Purdue University.",
    "CS251 Data Structures"
  };*/
/*  fprintf( stderr, "Search for words: \"");
  for(int i = 0; i < word_num; i++)
	fprintf( stderr, "%s\"", words[i]);*/

  fprintf( fout, "<TITLE>Search Results</TITLE>\r\n");
  fprintf( fout, "<H1> <Center><em>Boiler Search</em></H1>\n");
  fprintf( fout, "<H2> Search Results for \"");
  for(int i = 0; i < word_num; i++)
	  fprintf( fout, "%s ", words[i]);
  fprintf( fout, "\"");
  fprintf( fout, "\t with ");
  switch(TypeIndex) {
  case 0:
  	fprintf( fout, "Array Dictionary\n");
  	break;
  case 1:
  	fprintf( fout, "Hash Dictionary\n");
  	break;
  case 2:
  	fprintf( fout, "AVL Dictionary\n");
  	break;
  case 3:
  	fprintf( fout, "Binary Search Dictionary\n");
  	break;
  }
  double accum = ( End.tv_sec - Start.tv_sec )  + ( End.tv_nsec - Start.tv_nsec )  / BILLION;
  fprintf( fout, ".\tTime spent on this search: %lf", accum );
  fprintf( fout, "</center></H2>\n");

  for ( int i = 0; i < nurls; i++ ) {
    fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, urls[i], urls[i] );
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
  }

  // Add search form at the end
  fprintf(fout, "<HR><H2>\n");
  fprintf(fout, "<FORM ACTION=\"search\">\n");
  fprintf(fout, "Search:\n");
  fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
  fprintf(fout, "</H2>\n");
  fprintf(fout, "</FORM>\n");
}

void
printUsage()
{
  const char * usage =
    "Usage: search-engine port (array | hash | avl | bsearch)\n"
    "  It starts a search engine at this port using the\n"
    "  data structure indicated. Port has to be larger than 1024.\n";

  fprintf(stderr, "%s", usage);
}

int main(int argc, char ** argv)
{
  if (argc < 3) {
    printUsage();
    return 1;
  }

  // Get port
  int port;
  sscanf( argv[1], "%d", &port);

  // Get DictionaryType
  const char * dictType = argv[2];
  DictionaryType dictionaryType;
  if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = HashDictionaryType;
  }
  else if (!strcmp(dictType, "avl")) {
    dictionaryType = AVLDictionaryType;
  }
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
  }
  else {
    printUsage();
    return 0;
  }
  
  SearchEngine httpd(port, dictionaryType);
  
  httpd.run();

  return 0;
}
