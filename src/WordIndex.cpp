#include "WordIndex.h"
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
//Constructors and destructor
WordIndex::WordIndex():wordMap(){
}

WordIndex::~WordIndex(){
}

//Returns BST iterator to go through all the words.
BSTIter<Pair>* WordIndex::getIter(){
	return wordMap.getIter();
} 

WordIndex WordIndex::operator =(const WordIndex& other){
	wordMap = other.wordMap;
	return *this;
}

//Checks if word is in the index.
bool WordIndex::hasWord(string word) const{
	Pair temp(word);
	BSTNode<Pair>* node = wordMap.Find(temp);
	return node != NULL;
}

//adds the word to the index
void WordIndex::add(string word){
	Pair temp(word);
	wordMap.add(temp);
}

void WordIndex::add(Pair pair){
	BSTNode<Pair>* temp = wordMap.Find(pair);
	if(temp != NULL){
		WordIndex index;
		index.add(pair);
		add(index);
	} else {
		wordMap.add(pair);
	}
}

//adds the word to the index or increments the count.
void WordIndex::add(string word, URL url){
	Occurence tempO(url);
	Pair temp(word,tempO);
	add(temp);
}

//adds an whole index of words to the exist index.
void WordIndex::add(WordIndex& index){
	BSTIter<Pair>* iter = index.getIter();
	while(iter->hasNext()){ 
		Pair other = iter->getNext();
		BSTNode<Pair>* temp = wordMap.Find(other);
		if(temp != NULL){
			const Pair* pair = &(temp->GetValue()); 
			pair->add(other.getOccurences());
		} else{
			wordMap.add(other);
		}
	}
	delete iter;
}   



