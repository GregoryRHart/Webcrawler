#include <cstdlib>
#include <iostream>
#include <string>
#include "URL.h"
#include "Page.h"
#include "StopWords.h"
#include "HTMLParser.h"
#include "VisitedPages.h"
#include "PageQueue.h"
#include "WordIndex.h"
#include "XMLGen.h"
using namespace std;

int main(int argc, char* argv[]){

	if(argc != 4){
		cout << "Incorrect input" << endl;
		cout << "Usage: crawler <start-url> <output-file> <stopword-file>" << endl;
		return -1;
	}

	URL startURL = argv[1];
	string outputFile = argv[2];
	StopWords stopWords(argv[3]);
	Page start(startURL);
	Page* current = &start;
	VisitedPages visitedPages;
	PageQueue pageQueue(start, &visitedPages);
	WordIndex wordIndex;
	XMLGen XMLgen(outputFile);

	try{
		while(!pageQueue.IsEmpty()){
			current = pageQueue.dequeue();
			HTMLParser::parse(current, &stopWords);
			pageQueue.add(current->getLinks());
			wordIndex.add(current->getIndex()); 
		}
		XMLgen.encodeToXML(startURL, &visitedPages, &wordIndex);
	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
	}

	return 0;
}
