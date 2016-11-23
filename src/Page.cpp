#include <string>
#include "URL.h"
#include "WordIndex.h"
#include "URLList.h"
#include "Page.h"
using namespace std;

/******************************************************************************
 * Class Page:
 *      Stores the needed information about a webpage: the URL, a discription,
 *      a list of links found on the page, and a word index of the page.
 *
 *****************************************************************************/
Page::Page():url(),discription(""),index(),disFlag(false),URLLinks(){
}

Page::Page(URL url):url(url),discription(""),index(),disFlag(false),URLLinks(){
}

Page::Page(string url):url(url),discription(""),index(),disFlag(false),URLLinks(){
}

Page::~Page(){}

Page Page::operator =(const Page& other){
	url = other.url;
	discription = other.discription;
	index = other.index;
	disFlag = other.disFlag;
	URLLinks = other.URLLinks;
	return *this;
}

//Pages will be stored in a BST so it is neseccary to overload the 
//comparator operators.
bool Page::operator ==(Page other){
	return getURL() == other.getURL();
}

bool Page::operator <(Page other){
	return getURL() < other.getURL();
}

bool Page::operator >(Page other){
	return getURL() > other.getURL();
}

//Checks the discription flag for deciding wether to use a header or
//the first hundred charators on the page for the discription.
bool Page::hasDiscrip(){
	return disFlag;
}

void Page::setDiscrip(string discrip){
	disFlag = true;
	discription = discrip;
}

//These three functions add information to the page as the HTML is parsed.
void Page::addWord(string word){
	index.add(word,url);
}

void Page::addLink(string url){
	if(!StringUtil::IsPrefix(url,"http") &&
			!StringUtil::IsPrefix(url,"file")){
		if(url[0] != '#'){
			string base = this->url.getAbsoluteURL();
			URL temp(base,url);
			addLink(temp);
		}
	} else {
		URL temp(url);
		addLink(temp);
	}
}

void Page::addLink(URL url){
	URLLinks.add(url);
}

//These four functions return information about the page.
WordIndex& Page::getIndex(){
	return index;
}

URLList& Page::getLinks(){
	return URLLinks;
}

URL Page::getURL() const{
	return url;
}

string Page::getDiscrip(){
	return discription;
}

ostream& operator <<(ostream& os, const Page page){
	os << page.getURL();
	return os;
}

