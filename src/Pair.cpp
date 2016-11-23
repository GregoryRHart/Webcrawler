#include "Pair.h"
using namespace std;

/******************************************************************************
 * Class Pair:
 *      This class stores a word and it corresponding OccurenceSet.  It was 
 *      written to make the map for WordIndex easier.
 *
 *  Greg Hart
 *  14 Feb 2012
 *****************************************************************************/
// I don't know if I will need all three constructors, but I can easily
// see me using all three.
Pair::Pair():word(""),occurences(){
}

Pair::Pair(string word):word(word),occurences(){
}

Pair::Pair(string word,Occurence& occurence):word(word),occurences(occurence){

}

Pair::Pair(string word, OccurenceSet& occurences):word(word),occurences(occurences){
}

// Pairs are stored in a BST so the need the comparator operators.
bool Pair::operator ==(const Pair& other) const{
	return word == other.word;
}

bool Pair::operator <(const Pair& other) const{
	return word < other.word;
}

bool Pair::operator >(const Pair& other) const{
	return word > other.word;
}

// These two functions returns the member values.
string Pair::getWord() const{
	return word;
}

OccurenceSet& Pair::getOccurences(){
	return occurences;
}

//These two functions add to the member values.  I don't know if I will
//need the add(word) but if the default constructor is used it will be
//neseccary.
void Pair::add(string word){
	this->word = word;
}

void Pair::add(OccurenceSet occurences) const{
	BSTIter<Occurence>* iter = occurences.getIter();
	while(iter->hasNext()){
		this->occurences.addOccurence(iter->getNext());
	}
	delete iter;
}

void Pair::add(Occurence occurence){
	occurences.addOccurence(occurence);
}


