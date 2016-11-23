#pragma once

#include "Page.h"
#include "BST.h"
using namespace std;

/************************************************************
 * Class VisitedPages:
 *      This class keeps track of the URLs that have already
 *      been added to the queque so we don't revisit them
 *      and particularly stops infinite loops.
 *
 * Greg Hart
 * 14 Feb 2012
 ***********************************************************/
class VisitedPages{
private:
	BST<Page> pages;

public:
	// Constructors and destructor
	VisitedPages();

	VisitedPages(Page page);

	~VisitedPages();

	//Checks if page has already been visited. I imange that only
	//the pointer verious will get used in the end.
	bool hasPage(Page page) const;

	bool hasPage(Page* page) const;

	Page& add(Page page);

	//Returns a BST iterator for looking through all the pages visited.
	BSTIter<Page>* getIter();
};


