#pragma once

#include "URL.h"
using namespace std;

/**********************************************
 * Class Occurence:
 * This class stores a URL and a count it was 
 * designed to be used inconjunction with a 
 * string.  The count indicates how many times
 * the word appears on the wedsite.
 *
 * Greg Hart
 * 14 Feb 2012
 *********************************************/
class Occurence{
	friend class OccurenceSet;

private:
	URL url;
	mutable int count;
public:
	//I don't know if I will need all three types
	//of constructors, but I can see them all being
	//used.
	Occurence();

	Occurence(URL& url);

	Occurence(URL& url, int count);

	~Occurence();

	//Occurences will be stored in a BST so the comparator
	//operators need to be overloaded.
	bool operator ==(const Occurence* other);

	bool operator <(const Occurence* other);

	bool operator >(const Occurence* other);

	bool operator ==(const Occurence& other);

	bool operator <(const Occurence& other);

	bool operator >(const Occurence& other);

	void incerment(int increase = 1);

	URL getURL() const;

	int getCount() const;
};


