#pragma once

#include <string>
#include "URL.h"
#include "WordIndex.h"
#include "URLList.h"
using namespace std;

/******************************************************************************
 * Class Page:
 *      Stores the needed information about a webpage: the URL, a discription,
 *      a list of links found on the page, and a word index of the page.
 *
 *****************************************************************************/
class Page{
private:
	URL url;
	string discription;
	WordIndex index;
	bool disFlag;
	URLList URLLinks;

public:
	Page();

	Page(URL url);

	Page(string url);

	~Page();

	//Pages will be stored in a BST so it is neseccary to overload the 
	//comparator operators.
	Page operator =(const Page& other);

	bool operator ==(Page other);

	bool operator <(Page other);

	bool operator >(Page other);

	//Checks the discription flag for deciding wether to use a header or
	//the first hundred charators on the page for the discription.
	bool hasDiscrip();

	void setDiscrip(string discrip);

	//These two functions add information to the page as the HTML is parsed.
	void addWord(string word);

	void addLink(string url);

	void addLink(URL url);

	//These four functions return information about the page.
	WordIndex& getIndex();

	URLList& getLinks();

	URL getURL() const;

	string getDiscrip();
};

ostream& operator <<(ostream& os, const Page page);

