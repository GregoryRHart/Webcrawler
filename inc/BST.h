#pragma once

#include <assert.h>
#include <iostream>
using namespace std;

/****************************************************
 * This file has three classes in it.  They are all
 * centered around creating a binary search tree
 * All three are templates so that the tree and store
 * any object that have the comparator operators
 * overloaded
 *
 * Greg Hart
 * 14 Feb 2012
 ***************************************************/
template <typename T>
class BST;
template <typename T>
class BSTIter;

template <typename T>
//!  BSTNode implements a binary search tree node
class BSTNode 
{
	friend class BST<T>;   //!< BST can access private members of BSTNode
	friend class BSTIter<T>;

public:

	//!  Constructor
	BSTNode(const T& v) :
		value(v), left(NULL), right(NULL){
	}

	//! Copy Constructor
	BSTNode(const BSTNode & other) : 
		value(other.value),left(other.left),right(other.right){
	}

	//!  Read-only public methods for use by clients of the BST class
	const T& GetValue() const{
		return value;
	}

	BSTNode* GetLeft()const{
		return left;
	}


	BSTNode* GetRight()const{
		return right;
	}

	void setRight(BSTNode<T>* node){
		right = node;
	}

	void setLeft(BSTNode<T>* node){
		left = node;
	}

	//! Assignment operator 
	BSTNode & operator=(const BSTNode & other)
	{
		if(this!=&other)
		{
			value=other.value;
			left=other.left;
			right=other.right;
		}

		return *this;
	}

private:
	T value;  //!< value stored in the node
	BSTNode* left;     //!< pointer to the node's left child
	BSTNode* right;    //!< pointer to the node's right child
};

template <typename T>
// Is an iterator for the BST.
class BSTIter{
private:
	BSTNode<T*>* root;
	BSTNode<T*>* cur;
public:
	BSTIter(BSTNode<T>* newRoot){
		if(newRoot != NULL){
			root = new BSTNode<T*>(&(newRoot->value));
			cur = root;
			makeList(root,newRoot);
		} else {
			root = NULL;
			cur = NULL;
		}                
	}

	~BSTIter(){
		free();
	}

	bool hasNext(){
		return cur != NULL;
	}

	T& getNext(){
		BSTNode<T*>* temp = cur;
		cur = cur->GetRight();
		return *(temp->GetValue());
	}

	void clear(){
		free();
	}
private:
	void free(){
		while(root != NULL){
			cur = root;
			root = root->GetRight();
			delete cur;
		}
	}

	void makeList(BSTNode<T*>* list ,BSTNode<T>* tree){
		while(list->GetRight() != NULL){
			list = list->GetRight();
		}
		if(tree->GetRight() != NULL){
			list->setRight(new BSTNode<T*>(&(tree->right->value)));
			makeList(list->GetRight(), tree->right);
		}
		while(list->GetRight() != NULL){
			list = list->GetRight();
		}
		if(tree->left != NULL){
			list->setRight(new BSTNode<T*>(&(tree->left->value)));
			makeList(list->GetRight(),tree->left);
		}          
	}
};

template <typename T>
//!  BST implements a binary search tree
//I probably don't need all the functions in this class
//but since I had already implamented them no sense it
//getting rid of them.
//
//I need to fix the indentation and the BST:: it is not
//need.
class BST 
{
	friend class BSTIter<T>;

private:
	BSTNode<T>* root;
	int size;

public:
	//!  No-arg constructor.  Initializes an empty BST
	BST():root(NULL),size(0){
		return;
	}

	//!  Copy constructor.  Makes a complete copy of its argument
	BST(const BST& other):root(NULL),size(0){
		if(other.root != NULL){
			root = new BSTNode<T>(*(other.root)); 
			Init(other.root,root);
		}
		size = other.size;
	}	

	//!  Destructor
	~BST(){
		if(root != NULL){
			Free(root);
		}
	}

	//!  Assignment operator.  Makes a complete copy of its argument
	//!  @return Reference to oneself
	BST<T>& operator =(const BST & other){
		if(this != &other){
			if(root != NULL){
				Free(root);
				root = NULL;
			}   
			if(other.root != NULL){
				root = new BSTNode<T>(*(other.root));
				Init(other.root,root);
			}
			size = other.size;
		}
		return *this;
	}

	//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
	//!  @note This is useful for BST clients that need to traverse the tree.)
	BSTNode<T>* GetRoot()const{
		return root;
	}

	//!  @return true if the BST is empty, or false if the BST is not empty
	bool IsEmpty() const{
		return size == 0;	
	}

	//!  Removes all values from the BST
	void Clear(){
		if(root != NULL){
			Free(root);
			root = NULL;
		} 
		size = 0;
	}	

	//!  @return the number of values in the BST
	int GetSize() const{
		return size;
	}	

	//!  Inserts value v into the BST
	//!  
	//!  @param v The new value being inserted
	//!
	//!  @return a pointer to the newly inserted node, or NULL if v was already
	//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
	T& add(const T& v){
		if(root == NULL){
			root = new BSTNode<T>(v);
			size++;
			return root->value;
		} 
		BSTNode<T>* newNode = new BSTNode<T>(v);

		BSTNode<T>* inser = rInsert(root,newNode);
		if(inser != NULL){
			size++;
		}
		return inser->value;
	}	

	//!  Searches the tree for value v
	//!  
	//!  @param v The new value being searched for
	//!
	//!  @return a pointer to the node containing v, or NULL if v is not in the tree
	BSTNode<T>* Find(const T& v) const{
		if(root == NULL){
			return NULL;
		}
		return rFind(root, v);
	}	


	BSTIter<T>* getIter() const{
		BSTIter<T>* iter = new BSTIter<T>(root);
		return iter;
	}

private:	
	void Free(BSTNode<T>* cur){
		if(cur->left != NULL){
			Free(cur->left);
		}
		if(cur->right){
			Free(cur->right);
		}
		if(cur != NULL){
			delete cur;
		}
	}

	void Init(const BSTNode<T>* hisCur, BSTNode<T>* myCur){
		if(hisCur->left != NULL){
			myCur->left = new BSTNode<T>(*(hisCur->left));
			Init(hisCur->left,myCur->left);
		}
		if(hisCur->right != NULL){
			myCur->right = new BSTNode<T>(*(hisCur->right));
			Init(hisCur->right,myCur->right);
		}
	} 

	BSTNode<T>* rInsert(BSTNode<T>* cur, BSTNode<T>* newNode){
		if(cur->value == newNode->value){
			delete newNode;
			return NULL;      
		}

		if(cur->value < newNode->value){
			if(cur->right == NULL){
				cur->right = newNode;
				return newNode;
			} else {
				return rInsert(cur->right,newNode);
			}
		} else {
			if(cur->left == NULL){
				cur->left = newNode;
				return newNode;
			} else {
				return rInsert(cur->left,newNode);
			}   
		}
	}

	BSTNode<T>* rFind(BSTNode<T>* cur, const T& v) const{
		if(cur->value == v){
			return cur;
		}
		if(cur->value < v){
			if(cur->right != NULL){
				return rFind(cur->right,v);
			} 
		} else {
			if(cur->left != NULL){
				return rFind(cur->left,v);
			} 
		}
		return NULL;
	}
};



