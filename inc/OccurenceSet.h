#pragma once

#include "Occurence.h"
#include "URL.h"
#include "BST.h"
using namespace std;

/**********************************************************************
 * Class OccurenceSet:
 *      This class stores a BST of Occurence.  Because a word may 
 *      appear on more then one webpage we want to be able to store
 *      more then one occurence for each word.  Thus a set of occurences
 *
 * Greg Hart
 * 14 Feb 2012
 *********************************************************************/
class OccurenceSet{
private:
	BST<Occurence> occurences;

public:
	//I don't know if I will need all three types of constructor,
	//but it seemed like a good to add them so that I will think
	//more about it later.
	OccurenceSet();

	OccurenceSet(URL url);

	OccurenceSet(Occurence occurence);

	~OccurenceSet();

	//I am not sure that I will need both versions of this function
	//but the code is more general to have them both.
	bool hasOccurence(Occurence o);

	//Returns a bool based on the present of an Occurence with the 
	//given URL.
	bool hasOccurence(URL url);

	//I am not sure that I will need both versions of this function
	//but the code is more general to have them both.
	void addOccurence(Occurence o);

	//Adds a new Occurence with the given URL and a count of 1.
	void addOccurence(URL url);

	//Returns an iterator for the BST so that all the occurences can
	//be accessed.
	BSTIter<Occurence>* getIter();
};


