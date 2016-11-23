#include "URLList.h"
#include <iostream>
using namespace std;

//!  No-arg constructor.  Initializes an empty linked list
URLList::URLList():size(0){
	head = new URLNode();	
}

//!  Copy constructor.  Makes a complete copy of its argument
URLList::URLList(const URLList & other){
	head = new URLNode();
	init(other);
	size = other.size;
}

//!  Destructor
URLList::~URLList(){
	Free();
	delete head;
}	

//! Assignment operator.  Makes a complete copy of its argument
//! @return A reference to oneself
URLList& URLList::operator =(const URLList & other){
	if(&other != this){
		Free();
		init(other);
		size = other.size;
	}
	return *this;
}	

/*  void URLList::print(){
  URLNode* cur = head->next;
    while(cur != NULL){
      cout << cur->value << endl;
      cur = cur->next;
    }
  }

  void URLList::rprint(){
  URLNode* cur = head->prev;
    while(cur != NULL){
      cout << cur->value << endl;
      cur = cur->prev;
    }
  }
 */
//!  @return true if the list is empty, or false if the list is not empty
bool URLList::IsEmpty() const{
	return size == 0;
}

//!  Removes all values from the list
void URLList::Clear(){
	Free();
	size == 0;
}

//!  @return the number of values in the list
int URLList::GetSize() const{
	return size;
}

//!  @return a pointer to the first node in the list, or NULL if the list is empty
URLNode * URLList::GetFirst() const{
	return head->GetNext();
}

//!  @returns a pointer to the last node in the list, or NULL if the list is empty
URLNode * URLList::GetLast()const{
	return head->GetPrevious();
}

//!  Inserts value v into the list after node n
//!  
//!  @param v The new value being inserted
//!  @param n A node that is already in the list after which the new node should 
//!      be inserted.
//!      If n is NULL, the new node should be inserted at the beginning of the list.
//!
//!  @return a pointer to the newly inserted node
void URLList::add(const URL& v, URLNode* n){
	URLNode* newNode = new URLNode(v,NULL,NULL);
	if(IsEmpty()){
		head->next = newNode;
		head->prev = newNode;
	} else {
		if(n == NULL){
			newNode->next = head->next;
			head->next = newNode;
			if(newNode->next != NULL){
				newNode->next->prev = newNode;
			} 
		}else{
			newNode->prev = n;
			newNode->next = n->next;
			n->next = newNode;
			if(newNode->next != NULL){
				newNode->next->prev = newNode;
			}
			if(newNode->prev == head){
				newNode->prev = NULL;
			}
			if(newNode->next == NULL){
				head->prev = newNode;
			}
		}
	}        
	size++;
}	

void URLList::add(const string& v){
	URL url(v);
	add(url);
}

//! Searches for the first occurrence of value v that appears in the list 
//!   after node n
//!   
//!  @param v The value being searched for
//!  @param n The node in the list after which the search should begin.
//!      If n is NULL, the list should be searched from the beginning.
//!
//!  @return a pointer to the node containing v, or NULL if v is not found
URL URLList::Find(const URL& v, URLNode* n) const{
	URLNode* cur;
	if(n == NULL){
		cur = head;
	} else {
		cur = n->next;
	}
	while(cur != NULL){
		if(cur->value == v){
			return cur->GetValue();
		}
		cur = cur->next;
	}
	URL temp;
	return temp;
}	

//!  Removes node n from the list
//!  
//!  @param n The node being removed from the list
URL URLList::Remove(URLNode * n){
	URLNode* cur = n;
	URL url;
	if(cur == head->next && cur != NULL){
		if(cur->next != NULL){
			cur->next->prev = NULL;
		}
		head->next = cur->next;
	} else if(cur == head->prev && cur != NULL){
		cur->prev->next = NULL;
		head->prev = cur->prev;
	} else if(cur != NULL){
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
	}
	if(cur != NULL){
		url = cur->GetValue();
		delete cur;
		size--;
	}
	if(IsEmpty()){
		head->next = NULL;
		head->prev = NULL;
	}
	return url;
}

void URLList::Free(){
	URLNode* cur = head->next;
	while(cur != NULL){
		head->next = cur->next;
		delete cur;
		cur = head->next;
	}
	head->next = NULL;
	head->prev = NULL;
	size = 0;
}

void URLList::init(const URLList& other){
	URLNode* hisCur = other.head;
	URLNode* myCur  = head;
	while(hisCur->next != NULL){
		URLNode* temp = new URLNode(*(hisCur->next));
		myCur->next = temp;
		if(myCur != head){ 
			myCur->next->prev = myCur;
		}
		hisCur = hisCur->next;
		myCur = myCur->next;
	}
	head->prev = myCur;
}

URL URLList::getNext(){
	return Remove(head->next); 
}
