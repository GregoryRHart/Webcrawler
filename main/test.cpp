#include <iostream>
#include <string>
#include "test.h"
using namespace std;

bool BSTTest(ostream& os);
bool BSTString(ostream& os);
bool BSTURL(ostream& os);
bool URLListTest(ostream& os);
bool OccurenceTest(ostream& os);
bool OccurenceSetTest(ostream& os);
bool PairTest(ostream& os);
bool WordIndexTest(ostream& os);
bool StopWordsTest(ostream& os);
bool PageQueueTest(ostream& os);

int main(int argc, char* argv[]){
	bool success = true; 

	cout << "Running tests" << endl;

	cout << "\tTesting URL" << endl;
	success = URL::Test(cout) && success;

	cout << "\tTesting BST" << endl;
	success = BSTTest(cout) && success;

	cout << "\tTesting URLList" << endl;
	success = URLListTest(cout) && success;

	cout << "\tTesting Occurence" << endl;
	success = OccurenceTest(cout) && success;

	cout << "\tTesting OccurenceSet" << endl;
	success = OccurenceSetTest(cout) && success;

	cout << "\tTesting Pair" << endl;
	success = PairTest(cout) && success;

	cout << "\tTesting WordIndex" << endl;
	success = WordIndexTest(cout) && success;

	cout << "\tTesting StopWords" << endl;
	success = StopWordsTest(cout) && success;

	cout << "\tTesting PageQueue" << endl;
	success = PageQueueTest(cout) && success;

	cout << "All tests complete" << endl;
	if (success) {
		cout << "Tests Succeeded!" << endl;
	}
	else {
		cout << "Tests Failed!" << endl;
	}

	return 0;
}

bool PageQueueTest(ostream& os){
	bool success = true;

	URLList list;
	URL url[10];
	url[1]  = "http://www.google.com";
	url[2]  = "http://WWW.google.com/mail";
	url[3]  = "http://www.google.com/voice";
	url[4]  = "http://www.google.com/maps";
	url[5]  = "http://www.cnn.com/finance/headlines/today.html";
	url[6]  = "http://www.netflix.com";
	url[7]  = "file:///work/research/thesis.lyx";
	url[8]  = "file:///I/am/tired";
	url[9]  = "http://www.wiktionary.com";
	url[0]  = "http://www.google.com/labs/collections";
	Page start(url[1]);
	Page temp(url[0]);
	VisitedPages visited(temp);
	PageQueue queue(start, &visited); 

	list.add(url[0]);
	list.add(url[1]);
	list.add(url[2]);
	list.add(url[3]);
	list.add(url[4]);
	list.add(url[5]);
	list.add(url[6]);
	list.add(url[7]);
	list.add(url[8]);
	list.add(url[9]);

	queue.add(list);
	TEST(queue.GetSize() == 4);
	Page* cur = queue.dequeue();
	TEST(*cur == url[1]);
	cur = queue.dequeue();
	TEST(*cur == url[4]);
	cur = queue.dequeue();
	TEST(*cur == url[3]);
	cur = queue.dequeue();
	TEST(*cur == url[2]);
	TEST(queue.IsEmpty());
	return success;
}

bool StopWordsTest(ostream& os){
	bool success = true;

	StopWords stop("stopword.txt");
	TEST(stop.hasWord("a"));
	TEST(stop.hasWord("c"));
	TEST(stop.hasWord("E"));
	TEST(stop.hasWord("g"));
	TEST(stop.hasWord("I"));
	TEST(stop.hasWord("k"));
	TEST(stop.hasWord("M"));
	TEST(stop.hasWord("o"));
	TEST(stop.hasWord("Q"));
	TEST(stop.hasWord("s"));
	TEST(stop.hasWord("U"));
	TEST(stop.hasWord("x"));
	TEST(stop.hasWord("z"));
	TEST(stop.hasWord("wentworth"));
	TEST(!stop.hasWord("thee"));
	TEST(!stop.hasWord("zerba"));
	TEST(!stop.hasWord("aardvark"));
	TEST(stop.hasWord("IE"));
	TEST(!stop.hasWord("mike"));

	return success;
}

bool WordIndexTest(ostream& os){
	bool success = true;

	WordIndex index;
	TEST(!index.hasWord("apple"));

	OccurenceSet os1;
	OccurenceSet os2;
	URL url = "http://www.google.com";
	Occurence o1(url,1);
	url = "http://www.cnn.com";
	Occurence o2(url);
	url = "http://www.byu.edu";
	Occurence o3(url);
	url = "http://www.wikipedia.com";
	Occurence o4(url);
	url = "http://www.nerdparadise.com";
	Occurence o5(url);
	url = "http://www.google.com";
	Occurence o6(url,1);

	os1.addOccurence(o1);
	os1.addOccurence(o2);
	os2.addOccurence(o3);
	os2.addOccurence(o4);
	os2.addOccurence(o5);

	Pair pair1("apple",os1);
	Pair pair2("apple",os2);
	Pair pair3("bat",os1);

	index.add(pair1);
	BSTIter<Pair>* Piter = index.getIter();
	Pair temp = Piter->getNext();
	BSTIter<Occurence>* Oiter = temp.getOccurences().getIter();
	Occurence occur = Oiter->getNext();
	TEST(temp.getWord() == "apple");
	TEST(occur == o1);
	occur = Oiter->getNext();
	TEST(occur == o2);
	TEST(!Oiter->hasNext());
	delete Oiter;
	delete Piter;

	index.add(pair2);
	Piter = index.getIter();
	temp = Piter->getNext();
	TEST(!Piter->hasNext());
	Oiter = temp.getOccurences().getIter();
	occur = Oiter->getNext();
	TEST(occur == o1);
	occur = Oiter->getNext();
	TEST(occur == o4);
	occur = Oiter->getNext();
	TEST(occur == o5);
	occur = Oiter->getNext();
	TEST(occur == o2);
	occur = Oiter->getNext();
	TEST(occur == o3);
	TEST(!Oiter->hasNext());
	delete Oiter;
	delete Piter;

	index.add(pair3);
	Piter = index.getIter();
	temp = Piter->getNext();
	temp = Piter->getNext();
	TEST(index.hasWord("bat"));
	TEST(temp.getWord() == "bat");
	TEST(!Piter->hasNext());

	delete Piter;
	return success;
}

bool PairTest(ostream& os){
	bool success = true;

	Pair pair;
	OccurenceSet os1;
	OccurenceSet os2;
	URL url = "http://www.google.com";
	Occurence o1(url,1);
	url = "http://www.cnn.com";
	Occurence o2(url);
	url = "http://www.byu.edu";
	Occurence o3(url);
	url = "http://www.wikipedia.com";
	Occurence o4(url);
	url = "http://www.nerdparadise.com";
	Occurence o5(url);
	url = "http://www.google.com";
	Occurence o6(url,1);

	TEST(pair.getWord() == "");

	pair.add("word");

	TEST(pair.getWord() == "word");

	os1.addOccurence(o1);
	os1.addOccurence(o2);
	os2.addOccurence(o3);
	os2.addOccurence(o4);
	pair.add(os1);

	OccurenceSet temp = pair.getOccurences();
	BSTIter<Occurence>* iter = temp.getIter();
	TEST(iter->getNext() == o1);
	TEST(iter->getNext() == o2);
	delete iter;

	pair.add(os2);
	pair.add(o6);
	temp = pair.getOccurences();
	iter = temp.getIter();
	Occurence temp2 = iter->getNext();
	TEST(temp2 == o1);
	TEST(temp2.getCount() == 2);
	TEST(iter->getNext() == o4);
	TEST(iter->getNext() == o2);
	TEST(iter->getNext() == o3);
	delete iter;

	return success;
}

bool OccurenceSetTest(ostream& os){
	bool success = true;

	OccurenceSet occurences;
	URL url = "http://www.google.com";
	Occurence o1(url,1);
	url = "http://www.cnn.com";
	Occurence o2(url);
	url = "http://www.byu.edu";
	Occurence o3(url);
	url = "http://www.wikipedia.com";
	Occurence o4(url);
	url = "http://www.nerdparadise.com";
	Occurence o5(url);
	url = "http://www.google.com";
	Occurence o6(url,1);

	TEST(!occurences.hasOccurence(url));
	TEST(!occurences.hasOccurence(o1));
	occurences.addOccurence(o1);
	occurences.addOccurence(o2);
	occurences.addOccurence(o3);
	occurences.addOccurence(o4);
	occurences.addOccurence(o5);
	occurences.addOccurence(o6);
	occurences.addOccurence(url);
	TEST(occurences.hasOccurence(url));
	TEST(occurences.hasOccurence(o1));
	TEST(occurences.hasOccurence(o2));
	TEST(occurences.hasOccurence(o3));
	TEST(occurences.hasOccurence(o4));
	TEST(occurences.hasOccurence(o5));
	TEST(occurences.hasOccurence(o6));

	BSTIter<Occurence>* iter = occurences.getIter();
	Occurence temp = iter->getNext();
	delete iter;

	TEST(temp.getCount() == 3);
	TEST(temp.getURL() == url);


	return success;
}

bool OccurenceTest(ostream& os){
	bool success = true;

	Occurence empty;
	URL empURL;
	TEST(empty.getURL() == empURL);
	TEST(empty.getCount() == 0);

	URL google = "http://www.google.com";
	Occurence one(google);
	TEST(one.getURL() == google);
	TEST(one.getCount() == 1);
	one.incerment();
	TEST(one.getCount() == 2);
	one.incerment(4);
	TEST(one.getCount() == 6);

	Occurence two(google,2);
	TEST(two.getURL() == google);
	TEST(two.getCount() == 2);

	return success;
}

bool URLListTest(ostream& os){
	bool success = true;
	URLList list;
	URL url[10];
	url[1]  = "http://www.google.com";
	url[2]  = "http://www.wikipedia.com";
	url[3]  = "http://www.google.com/voice";
	url[4]  = "http://www.nerdparadise.com/thesite.html";
	url[5]  = "http://www.cnn.com/finance/headlines/today.html";
	url[6]  = "http://www.netflix.com";
	url[7]  = "file:///work/research/thesis.lyx";
	url[8]  = "file:///I/am/tired";
	url[9]  = "http://www.wiktionary.com";
	url[0]  = "http://www.google.com/labs/collections";
	string temp = "http://www.wikipedia.com";

	TEST(list.IsEmpty());
	TEST(list.GetFirst() == NULL);

	list.add(url[0]);
	list.add(url[1]);
	list.add(url[2]);
	TEST(list.GetSize() == 3);
	TEST(list.getNext() == url[2]);

	list.add(temp);
	TEST(list.GetFirst()->GetValue() == url[2]);
	TEST(list.GetLast()->GetValue() == url[0]);

	list.add(url[3]);
	list.add(url[4]);
	list.add(url[5]);
	list.add(url[6]);
	list.add(url[7]);
	list.add(url[8]);
	list.add(url[9]);

	URL empty();
	URL find = list.Find(url[9],list.GetFirst()->GetNext());
	TEST(list.Find(url[8]) == url[8]);
	TEST(empty == empty);    

	TEST(list.getNext() == url[9]);
	TEST(list.getNext() == url[8]);
	TEST(list.getNext() == url[7]);
	TEST(list.getNext() == url[6]);
	TEST(list.getNext() == url[5]);
	TEST(list.getNext() == url[4]);
	TEST(list.getNext() == url[3]);
	TEST(list.getNext() == url[2]);
	TEST(list.getNext() == url[1]);
	TEST(list.getNext() == url[0]);

	return success;
}

bool BSTTest(ostream& os){
	bool success = true;

	success = BSTString(os) && success;
	success = BSTURL(os) && success;   

	return success;
}

bool BSTString(ostream& os){
	bool success = true;

	os << "\t\tTesting BST with string " << endl;
	BST<string> tree;
	BSTNode<string>* n = tree.GetRoot();
	int size = tree.GetSize();
	TEST(n == NULL);
	TEST(size == 0);
	TEST(!tree.Find("a"));

	tree.add("b");
	tree.add("a");
	tree.add("c");
	n = tree.GetRoot();
	size = tree.GetSize();
	TEST(n->GetValue() == "b");
	TEST(n->GetLeft()->GetValue()  == "a");
	TEST(n->GetRight()->GetValue() == "c");
	TEST(size == 3);


	BSTIter<string>* iter = tree.getIter();
	TEST((iter->getNext()) == n->GetValue());
	TEST((iter->getNext()) == n->GetRight()->GetValue());
	TEST((iter->getNext()) == n->GetLeft()->GetValue());
	TEST(!iter->hasNext());

	tree.add("f");
	tree.add("e");
	tree.add("1");
	tree.add("2");
	tree.add("g");
	size = tree.GetSize();
	TEST(size == 8);
	BSTNode<string>* temp = tree.Find("f");
	TEST(temp->GetValue() == "f");
	temp = tree.Find("2");
	TEST(temp->GetValue() == "2");

	delete iter;
	iter = tree.getIter();
	TEST(iter->getNext() == "b");
	TEST(iter->getNext() == "c");
	TEST(iter->getNext() == "f");
	TEST(iter->getNext() == "g");
	TEST(iter->getNext() == "e");
	TEST(iter->getNext() == "a");
	TEST(iter->getNext() == "1");
	TEST(iter->getNext() == "2");
	TEST(!iter->hasNext());

	delete iter;

	return success;
}

bool BSTURL(ostream& os){
	bool success = true;

	os << "\t\tTesting BST with URL" << endl;
	BST<URL> tree;
	BSTNode<URL>* n = tree.GetRoot();
	int size = tree.GetSize();
	TEST(n == NULL);
	TEST(size == 0);

	URL url = "http://www.gmail.com";
	tree.add(url);
	url = "http://www.google.com/voice";
	tree.add(url);
	url = "file:///local/here.txt";
	tree.add(url);
	n = tree.GetRoot();
	size = tree.GetSize();
	TEST(n->GetValue() == "http://www.gmail.com");
	TEST(n->GetLeft()->GetValue()  == "file:///local/here.txt");
	TEST(n->GetRight()->GetValue() == "http://www.google.com/voice");
	TEST(size == 3);


	BSTIter<URL>* iter = tree.getIter();
	TEST((iter->getNext().getAbsoluteURL()) == n->GetValue().getAbsoluteURL());
	TEST((iter->getNext().getAbsoluteURL()) == n->GetRight()->GetValue().getAbsoluteURL());
	TEST((iter->getNext().getAbsoluteURL()) == n->GetLeft()->GetValue().getAbsoluteURL());
	TEST(!iter->hasNext());

	url = "http://www.nerdparadise.com";
	tree.add(url);
	url = "http://www.imdb.com/";
	tree.add(url);
	url = "file:///aardvark.txt";
	tree.add(url);
	url = "file:///games.exe";
	tree.add(url);
	url = "http://www.wikipedia.com";
	tree.add(url);
	size = tree.GetSize();
	TEST(size == 8);
	BSTNode<URL>* temp = tree.Find(url);
	TEST(temp->GetValue() == url);
	url = "http://www.hotmail.com";
	temp = tree.Find(url);
	TEST(temp == NULL);

	delete iter;
	iter = tree.getIter();
	TEST(iter->getNext() == "http://www.gmail.com");
	TEST(iter->getNext() == "http://www.google.com/voice");
	TEST(iter->getNext() == "http://www.nerdparadise.com");
	TEST(iter->getNext() == "http://www.wikipedia.com");
	TEST(iter->getNext() == "http://www.imdb.com/");
	TEST(iter->getNext() == "file:///local/here.txt");
	TEST(iter->getNext() == "file:///aardvark.txt");
	TEST(iter->getNext() == "file:///games.exe");
	TEST(!iter->hasNext());

	delete iter;

	return success;
}
