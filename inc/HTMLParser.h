#pragma once

#include <ctype.h>
#include "URLInputStream.h"
#include "CS240Exception.h"
#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include "Page.h"
#include "StopWords.h"
using namespace std;

/*********************************************************
 * Class HTMLParser:
 *      This class has no members and static functions. It
 *      is used parse the HTML and pass the data to the 
 *      page where it is stored. The functions are static
 *      so the Parser never needs to be instanciated.
 *
 * Greg Hart
 * 14 Feb 2012
 ********************************************************/
class HTMLParser{
private:

public:
	//Default constuctor, I never plan on needing it but
	//it is here just in case.
	HTMLParser();

	//Deconstuctor, I never plan on needing it but
	//it is here just in case.
	~HTMLParser();

	//Parse downloads the html from the page and parses
	//through it to find the words and any interesting 
	//tags.
	static void parse(Page* page, StopWords* stopWords);

private:
	static void toHTMLStart(Page& page, HTMLTokenizer& tokenizer);

	static void parseHead(Page& page, HTMLTokenizer& tokenizer, StopWords& stopWords);

	static void parseBody(Page& page, HTMLTokenizer& tokenizer, StopWords& stopWords);

	static void toHTMLEnd(Page& page, HTMLTokenizer& tokenizer);

	static void parseTitle(Page& page, HTMLTokenizer& tokenizer, StopWords& stopWords);

	static void parseScript(HTMLTokenizer& tokenizer);

	static void parseHeader(Page& page, HTMLTokenizer& tokenizer, StopWords& stopWords);

	static void handleLink(Page& page, HTMLToken& current);

	static int countWS(string words);

	static string trimLen(string discrip);

	static void makeWord(Page& page, string words, StopWords& stopWords);

	static bool isWordChar(char cur);

};

