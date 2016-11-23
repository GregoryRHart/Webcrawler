#pragma once

#include "OccurenceSet.h"
#include "Occurence.h"
#include <string>
using namespace std;

/******************************************************************************
 * Class Pair:
 *      This class stores a word and it corresponding OccurenceSet.  It was 
 *      written to make the map for WordIndex easier.
 *
 *  Greg Hart
 *  14 Feb 2012
 *****************************************************************************/
class Pair{
private:
	string word;
	mutable OccurenceSet occurences;
public:
	// I don't know if I will need all three constructors, but I can easily
	// see me using all three.
	Pair();

	Pair(string word);

	Pair(string word,Occurence& occurence);

	Pair(string word, OccurenceSet& occurences);

	// Pairs are stored in a BST so the need the comparator operators.
	bool operator ==(const Pair& other) const;

	bool operator <(const Pair& other) const;

	bool operator >(const Pair& other) const;

	// These two functions returns the member values.
	string getWord() const;

	OccurenceSet& getOccurences();

	//These two functions add to the member values.  I don't know if I will
	//need the add(word) but if the default constructor is used it will be
	//neseccary.
	void add(string word);

	void add(OccurenceSet occurences) const;

	void add(Occurence occurence);
};

