
#include "webcrawler.h"

char word[2000];
int word_count;
char descrip[501];
int descrip_count;

void WebCrawler::onContentFound(char c) {
	if(!isascii(c))
		return;
	if(descrip_count < 500) {
		descrip[descrip_count] = c;
		descrip_count++;
	}
	if(c == ' ' || c == '\0') {
		if(word[0] == '\0')
			return;
		else {
			char *p = (char*)malloc(sizeof(char) * (word_count + 1));
			for(int i = 0; i < word_count; i++) {
				p[i] = word[i];
			}
			p[word_count] = '\0';
			
			struct URLRecordList *e = new URLRecordList;
			struct URLRecordList *t;
			e->_urlRecordIndex = _headURL;
			e->_next = NULL;
			if(_wordToURLRecordList->find(p, &t)) {
				int isExist = 0;
				while(t->_next != NULL) {
					if(t->_urlRecordIndex == _headURL) {
						isExist = 1;
						break;
					}
					t = t->_next;
				}
				if(!isExist)
					t->_next = e;
			}
			else
				_wordToURLRecordList->insertItem(p, e);
		}
		for(int i = 0; i < 2000; i++) {
			word[i] = '\0';
		}
		word_count = 0;
	}
	else {
		word[word_count] = c;
		word_count++;
	}
}

void WebCrawler::onAnchorFound(char *url) {
	for(int i = 0; i < strlen(url); i++) {
		if(!isascii(url[i]))
			return;
	}
	int n;
	if(strstr(url, "http://") == NULL)
		return;
	
	if(!_urlToUrlRecord->find(url, &n)) { // didn't find a same one
		if(_tailURL < _maxUrls) {
			(_urlArray + _tailURL)->_url = strdup(url);
			_tailURL++;
			_urlToUrlRecord->insertItem(url, _headURL);
		}
	}
}

WebCrawler::WebCrawler(int maxUrls, int nurlRoots, const char ** urlRoots) {
	_maxUrls = maxUrls;
	_urlArray = new URLRecord[_maxUrls];
	_urlToUrlRecord = new HashTableTemplate<int>;
	_wordToURLRecordList = new HashTableTemplate<URLRecordList *>;
	for(int i = 0; i < nurlRoots; i++) {
		(_urlArray+i)->_url = strdup(urlRoots[i]);
		_urlToUrlRecord->insertItem(urlRoots[i], i);
	}
	_headURL = 0;
	_tailURL = nurlRoots;
}

void WebCrawler::crawl() {
	while(_headURL < _tailURL) {
		int n;
		char *buff;
		buff = fetchHTML((_urlArray+_headURL)->_url, &n);
		if(buff == NULL) {
			_headURL++;
			continue;
		}
		for(int i = 0; i < 500; i++) {
			descrip[i] = '\0';
		}
		descrip_count = 0;
//		printf("now going to parse %s, number:%d\n\n\n\n\n\n", buff, n);
		parse(buff, n);
		(_urlArray+_headURL)->_description = strdup(descrip);
		_headURL++;
	}
}

void WebCrawler::writeURLFile(const char * urlFileName) {
	FILE *fd;
	fd = fopen(urlFileName, "w");
	for(int i = 0; i < _maxUrls; i++) {
		if(_urlArray[i]._url == NULL)
			break;
		if(_urlArray[i]._description == NULL)
			fprintf(fd,"%d %s\nNo Content-Type\n\n", i, _urlArray[i]._url);
		else
			fprintf(fd,"%d %s\n%s\n\n", i, _urlArray[i]._url, _urlArray[i]._description);
	}
	fclose(fd);
}

void WebCrawler::writeWordFile(const char *wordFileName) {
	FILE *fd;
	fd = fopen(wordFileName, "w");
	const char * key;
	URLRecordList *p;
	HashTableTemplateIterator<URLRecordList *> iterator(_wordToURLRecordList);
	while(iterator.next(key, p)) {
		fprintf(fd,"%s", key);
		int array[_maxUrls];
		for(int i = 0; i < _maxUrls; i++)
			array[i] = 0;
		while(p!=NULL) {
			array[p->_urlRecordIndex] = 1;
			p = p->_next;
		}
		for(int i = 0; i < _maxUrls; i++) {
			if(array[i] == 1){
				fprintf(fd, " %d", i);
			}
		}
		fprintf(fd, "\n");
	}
	fclose(fd);
}
int main(int argc, char ** argv) {
	int max_url = 1000;
	const char **url;
	int url_count;
	if(!strcmp(argv[1], "-u")) {
		max_url = atoi(argv[2]);
		url_count = argc - 3;
		url = (const char **)malloc(sizeof(char*) * (argc - 3));
		for(int i = 0; i <= argc - 3; i++) {
			url[i] = argv[i + 3];
		}
	}
	else {
		url_count = argc - 1;
		url = (const char **)malloc(sizeof(char*) * (argc - 1));
		for(int i = 0; i <= argc - 1; i++) {
			url[i] = argv[i+1];
		}
	}
	WebCrawler myWebCrawler(max_url, url_count, url);
	myWebCrawler.crawl();
	myWebCrawler.writeURLFile("url.txt");
	myWebCrawler.writeWordFile("word.txt");
	return 0;
}
