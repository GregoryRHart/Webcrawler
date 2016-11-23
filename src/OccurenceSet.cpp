#include "OccurenceSet.h"
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
//I don't know if I will need all three types of constructor,
//but it seemed like a good to add them so that I will think
//more about it later.
OccurenceSet::OccurenceSet(){
}

OccurenceSet::OccurenceSet(URL url){
	Occurence temp(url);
	occurences.add(temp);
}

OccurenceSet::OccurenceSet(Occurence occurence){
	occurences.add(occurence);
}

OccurenceSet::~OccurenceSet(){
}

//I am not sure that I will need both versions of this function
//but the code is more general to have them both.
bool OccurenceSet::hasOccurence(Occurence o){
	return !(occurences.Find(o) == NULL);
}

//Returns a bool based on the present of an Occurence with the 
//given URL.
bool OccurenceSet::hasOccurence(URL url){
	Occurence temp(url);
	return !(occurences.Find(temp) == NULL);
}

//I am not sure that I will need both versions of this function
//but the code is more general to have them both.
void OccurenceSet::addOccurence(Occurence o){
	BSTNode<Occurence>* temp = occurences.Find(o);
	if(temp != NULL){
		const Occurence* occur = &(temp->GetValue()); 
		occur->count += o.getCount();
	} else{
		occurences.add(o);
	}
}

//Adds a new Occurence with the given URL and a count of 1.
void OccurenceSet::addOccurence(URL url){
	Occurence temp(url);
	addOccurence(temp);
}

//Returns an iterator for the BST so that all the occurences can
//be accessed.
BSTIter<Occurence>* OccurenceSet::getIter(){
	return occurences.getIter();
}


