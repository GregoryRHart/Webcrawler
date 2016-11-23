#pragma once

#include <string>
#include "URL.h"
using namespace std;

/*******************************************************************
 * This file is used to store a list of URLs that represent the 
 * links found on a webpage.  It needs some clean up, but it is more
 * or less my linked list code.  Though I may create a linked list
 * template and avoid this class altogether.
 *
 * Greg Hart
 * 14 Feb 2012
 ******************************************************************/
//! URLNode implements a doubly-linked list node
class URLNode 
{
	friend class URLList;  //!< URLList can access private members of URLNode
public:

	URLNode():value(),prev(NULL),next(NULL){
	}

	//!  Constructor
	URLNode(const URL& v, URLNode * p, URLNode * n) :
		value(v), prev(p), next(n){
	}

	//! Copy Constructor 
	URLNode(const URLNode & other) : 
		value(other.value),prev(other.prev),next(other.next)
	{
	}

	//!  Read-only public methods for use by clients of the URLList class
	const URL& GetValue() const
	{
		return value;
	}


	URLNode * GetPrevious()const
				{
		return prev;
				}


	URLNode * GetNext()const
				{
		return next;
				}

	//! Assignment operator 
	URLNode & operator=(const URLNode & other)
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
	URL value;        //!< value stored in the node
	URLNode * prev;            //!< pointer to previous node in the list
	URLNode * next;            //!< pointer to next node in the list
};


//! URLList implements a doubly-linked list
class URLList
{
private:

	URLNode* head;
	int size;

public:

	//!  No-arg constructor.  Initializes an empty linked list
	URLList();

	//!  Copy constructor.  Makes a complete copy of its argument
	URLList(const URLList & other);

	//!  Destructor
	~URLList();

	//! Assignment operator.  Makes a complete copy of its argument
	//! @return A reference to oneself
	URLList& operator =(const URLList & other);

	//!  @return true if the list is empty, or false if the list is not empty
	bool IsEmpty() const;

	URLNode* GetFirst() const;

	URLNode* GetLast() const;	

	//!  Removes all values from the list
	void Clear();

	//!  @return the number of values in the list
	int GetSize() const;

	//!  @return a pointer to the first node in the list, or NULL if the list is empty
	URL getNext();

	URL Remove(URLNode* n);

	URL Find(const URL& v, URLNode * n = NULL) const;

	void add(const URL& url, URLNode* n = NULL);	

	void add(const string& url);	

private:
	void init(const URLList& other);

	void Free();
};

