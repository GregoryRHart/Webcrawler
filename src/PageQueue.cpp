#include "PageQueue.h"
#include <iostream>
using namespace std;

//!  No-arg constructor.  Initializes an empty linked list
PageQueue::PageQueue():visited(NULL),size(0),startURL(){
	Page empty;
	head = new LLNode(&empty,NULL,NULL);	
}

//! constructor with a starting page and a set of visited pages.
PageQueue::PageQueue(Page& page, VisitedPages* visited):visited(visited),size(0),startURL(){
	string temp = page.getURL().getAbsoluteURL();
	int idx = temp.find_last_of("/");
	temp = temp.substr(0,idx);
	startURL = temp;
	Page empty;
	head = new LLNode(&empty,NULL,NULL);
	add(&page);	
}

//!  Copy constructor.  Makes a complete copy of its argument
PageQueue::PageQueue(const PageQueue & other){
	Page empty;
	head = new LLNode(&empty,NULL,NULL);
	init(other);
	size = other.size;
	visited = other.visited;
	startURL = other.startURL;
}

//!  Destructor
PageQueue::~PageQueue(){
	Free();
	delete head;
}	

//! Assignment operator.  Makes a complete copy of its argument
//! @return A reference to oneself
PageQueue& PageQueue::operator =(const PageQueue & other){
	if(&other != this){
		Free();
		init(other);
		size = other.size;
		visited = other.visited;
		startURL = other.startURL;
	}
	return *this;
}	

void PageQueue::print(){
	LLNode* cur = head->next;
	cout << "printing queue" << endl;
	while(cur != NULL){
		cout << *(cur->value) << endl;
		cur = cur->next;
	}
}

void PageQueue::rprint(){
	LLNode* cur = head->prev;
	while(cur != NULL){
		cout << *(cur->value) << endl;
		cur = cur->prev;
	}   
}

//!  @return true if the list is empty, or false if the list is not empty
bool PageQueue::IsEmpty() const{
	return size == 0;
}

//!  Removes all values from the list
void PageQueue::Clear(){
	Free();
	size = 0;
}

//!  @return the number of values in the list
int PageQueue::GetSize() const{
	return size;
}

void PageQueue::add(URLList urls){
	URL empty;
	URL temp = urls.getNext();
	while(!(temp == empty)){
		Page* page = new Page(temp);
		add(page);
		temp = urls.getNext();
		delete page;
	}
}

void PageQueue::add(Page* page){
	if(validURL(page->getURL())){           
		Page& temp = visited->add(*page);
		LLNode* newNode = new LLNode(&temp,NULL,NULL);
		if(IsEmpty()){
			head->next = newNode;
			head->prev = newNode;
		} else {
			newNode->next = head->next;
			head->next = newNode;
			if(newNode->next != NULL){
				newNode->next->prev = newNode;
			} 
		}
		size++;
	}
}

Page* PageQueue::dequeue() {
	if(IsEmpty()){          
		return NULL;
	}
	LLNode* temp = head->prev;
	Page* page = temp->value;
	if(head->next != head->prev){
		temp->prev->next = NULL;
		head->prev = temp->prev;     
	} else {
		head->next = NULL;
		head->prev = NULL;
	}
	size--; 

	delete temp;
	return page;
}

bool PageQueue::validURL(URL url){
	return inScope(url) && isHTML(url) && !wasVisited(url);
}

bool PageQueue::inScope(URL url){
	return StringUtil::IsPrefix(url.getAbsoluteURL(),startURL.getAbsoluteURL());
}

bool PageQueue::wasVisited(URL url){
	Page page(url);
	return visited->hasPage(page);
}

bool PageQueue::isHTML(URL url){
	string address = url.getAbsoluteURL();
	if(StringUtil::IsSuffix(address,"/")){
		return true;
	}
	string suffix = address;
	int idx = suffix.find_last_of("/");
	suffix = suffix.substr(idx);
	if(suffix.find_first_of(".") > suffix.size()){
		return true;
	}
	int size = 10;
	string suffixes[] = {".html", ".htm", ".shtml", ".cgi",
			".jsp", ".asp", ".aspx", ".php", ".pl", ".cfm"};
	idx = address.find_first_of("?");
	address = address.substr(0,idx);
	for(int i=0; i<size; i++){
		if(StringUtil::IsSuffix(address, suffixes[i])){
			return true;
		}
	}
	return false;
}

void PageQueue::Free(){
	LLNode* cur = head->next;
	while(cur != NULL){
		head->next = cur->next;
		delete cur;
		cur = head->next;
	}
	head->next = NULL;
	head->prev = NULL;
	size = 0;
}

void PageQueue::init(const PageQueue& other){
	LLNode* hisCur = other.head;
	LLNode* myCur  = head;
	while(hisCur->next != NULL){
		LLNode* temp = new LLNode(*(hisCur->next));
		myCur->next = temp;
		if(myCur != head){ 
			myCur->next->prev = myCur;
		}
		hisCur = hisCur->next;
		myCur = myCur->next;
	}
	head->prev = myCur;
}


