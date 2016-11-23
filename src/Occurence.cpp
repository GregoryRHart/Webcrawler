#include "Occurence.h"
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
//I don't know if I will need all three types
//of constructors, but I can see them all being
//used.
Occurence::Occurence():url(),count(0){
}

Occurence::Occurence(URL& url):url(url),count(1){
}

Occurence::Occurence(URL& url, int count):url(url),count(count){
}

Occurence::~Occurence(){
}

//Occurences will be stored in a BST so the comparator
//operators need to be overloaded.
bool Occurence::operator ==(const Occurence* other){
	return url == other->url;
}

bool Occurence::operator <(const Occurence* other){
	return url < other->url;
}

bool Occurence::operator >(const Occurence* other){
	return url > other->url;
}

bool Occurence::operator ==(const Occurence& other){
	return url == other.url;
}

bool Occurence::operator <(const Occurence& other){
	return url < other.url;
}

bool Occurence::operator >(const Occurence& other){
	return url > other.url;
}

void Occurence::incerment(int increase){
	count += increase;
}

URL Occurence::getURL() const{
	return url;
}

int Occurence::getCount() const{
	return count;
}


