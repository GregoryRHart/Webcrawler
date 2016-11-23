#include "VisitedPages.h"
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
// Constructors and destructor
VisitedPages::VisitedPages():pages(){
}

VisitedPages::VisitedPages(Page page):pages(){
	pages.add(page);
}

VisitedPages::~VisitedPages(){
}

//Checks if page has already been visited. I imange that only
//the pointer verious will get used in the end.
bool VisitedPages::hasPage(Page page) const{
	BSTNode<Page>* temp = pages.Find(page);
	return temp != NULL;
}

bool VisitedPages::hasPage(Page* page) const{
	return hasPage(*page);
}

Page& VisitedPages::add(Page page){
	return pages.add(page);

}

//Returns a BST iterator for looking through all the pages visited.
BSTIter<Page>* VisitedPages::getIter(){
	return pages.getIter();
}


