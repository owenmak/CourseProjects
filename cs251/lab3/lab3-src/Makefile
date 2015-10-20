
all:  webcrawler

/*gethttp: gethttp.cpp openhttp.cpp SimpleHTMLParser.cpp
	g++ -o gethttp -g gethttp.cpp openhttp.cpp SimpleHTMLParser.cpp */

webcrawler: webcrawler.cpp openhttp.cpp SimpleHTMLParser.cpp HashTableTemplate.h
	g++ -g -o webcrawler webcrawler.cpp openhttp.cpp SimpleHTMLParser.cpp HashTableTemplate.h

clean:
	rm -f *.o webcrawler core url.txt word.txt
