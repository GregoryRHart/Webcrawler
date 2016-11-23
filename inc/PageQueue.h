#pragma once

#include <iostream>
#include "Page.h"
#include "VisitedPages.h"
#include "URLList.h"
#include "URL.h"
using namespace std;

/******************************************************************************
 * This file has two classes LLNode is used in the creation of the queque.
 * PageQueue is implaments the queque and the functionality of PageQueue.
 * I have will probably turn my linked list code into a template and simplify 
 * this file
 *
 * Greg Hart
 * 14 Feb 2012
 *****************************************************************************/

//! LLNode implements a doubly-linked list node
class LLNode 
{
	friend class PageQueue;  //!< PageQueue can access private members of LLNode
public:

	//!  Constructor
	LLNode(Page* v, LLNode * p, LLNode * n) :
		value(v), prev(p), next(n){
	}

	//! Copy Constructor 
	LLNode(const LLNode & other) : 
		value(other.value),prev(other.prev),next(other.next)
	{
	}

	//!  Read-only public methods for use by clients of the PageQueue class
	const Page& GetValue() const{
		return *value;
	}


	LLNode * GetPrevious()const
				{
		return prev;
				}


	LLNode * GetNext()const
				{
		return next;
				}

	//! Assignment operator 
	LLNode & operator=(const LLNode & other)
	{
		if(this!=&other)
		{
			value=other.value;
			prev=other.prev;
			next=other.next;
		}
		return *this;
	}

private:
	Page* value;        //!< value stored in the node
	LLNode* prev;            //!< pointer to previous node in the list
	LLNode * next;            //!< pointer to next node in the list
};


//! PageQueue implements a doubly-linked list
//I probabaly don't need all the functions in this class I kept most of them
//however since they are already implamented.
class PageQueue
{
private:
	LLNode* head;
	//This is used in determining valid URLs.
	VisitedPages* visited;
	int size;
	//This is also used in determing valid URLs.
	URL startURL;

public:

	//!  No-arg constructor.  Initializes an empty linked list
	PageQueue();

	//Starts the queque with a page and the list of visited pages.
	PageQueue(Page& page, VisitedPages* visited);

	//!  Copy constructor.  Makes a complete copy of its argument
	PageQueue(const PageQueue& other);


	//!  Destructor
	~PageQueue();

	//! Assignment operator.  Makes a complete copy of its argument
	//! @return A reference to oneself
	PageQueue& operator =(const PageQueue& other);

	//!  @return true if the list is empty, or false if the list is not empty
	bool IsEmpty() const;

	//!  Removes all values from the list
	void Clear();

	//!  @return the number of values in the list
	int GetSize() const;

	//Removes and returns the next page in the queque.	
	Page* dequeue();

	//Adds a page to the queque
	void add(Page* page);

	//I don't know if I need both versions of the function, but this
	//also adds a page to the queque.
	void add(URLList urls);

	void print();

	void rprint();
private:
	//When a new URL or Page is added to the queque this checks
	//the URL before adding the page.  I will probably add three
	//seperate function, one for get criteria for a valid URL.
	bool validURL(URL url);

	bool inScope(URL url);

	bool wasVisited(URL url);

	bool isHTML(URL url);

	void Free();

	void init(const PageQueue& other);
};


