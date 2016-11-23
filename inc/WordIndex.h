#pragma once

#include "BST.h"
#include "Pair.h"
#include "StopWords.h"
#include <string>
#include "OccurenceSet.h"
#include "Occurence.h"
using namespace std;

/*********************************************************
 * Class WordIndex:
 *      This class stores an index (map) of all the words
 *      seen in the crawl with the occurences (the urls 
 *      at which the were found an the number of times on
 *      that page)
 *
 * Greg Hart
 * 14 Feb 2012
 ********************************************************/
class WordIndex{
private:
	//BST of word, occurences pairs
	BST<Pair> wordMap;

public:
	//Constructors and destructor
	WordIndex();

	~WordIndex();

	//Returns BST iterator to go through all the words.
	BSTIter<Pair>* getIter(); 

	WordIndex operator =(const WordIndex& other);

	//Checks if word is in the index.
	bool hasWord(string word) const;

	//adds the word to the index
	void add(string word);

	//adds the word to the index or increments the count.
	void add(string word, URL url);

	void add(Pair pair);

	//adds an whole index of words to the exist index.
	void add(WordIndex& index);   
};


