#include "XMLGen.h"
#include <iostream>
#include <fstream>
using namespace std;

XMLGen::XMLGen(){
}

XMLGen::XMLGen(string file):fileName(file){
}

XMLGen::~XMLGen(){
}

void XMLGen::encodeToXML(URL start, VisitedPages* visited, WordIndex* index){
	ofstream outFile(fileName.c_str());
	if(!outFile.is_open()){
		cout << fileName << " failed to open." << endl;
		return;
	}

	outFile << "<website>" << endl;

	outFile << "<start-url>" << endl;
	string url = StringUtil::EncodeToXmlCopy(start.getAbsoluteURL());
	outFile << url << endl;
	outFile << "</start-url>" << endl;

	//Generates the Pages section of the XML
	printPages(outFile, visited);

	//Generates the Index section of the XML
	printIndex(outFile, index);    

	outFile << "</website>" << endl;

	outFile.close();
}

void XMLGen::printPages(ofstream& outFile, VisitedPages* visited){

	outFile << "<pages>" << endl;
	BSTIter<Page>* iter= visited->getIter();
	string url;
	string discription;
	while(iter->hasNext()){
		Page* temp = &(iter->getNext());
		outFile << "<page>" << endl;
		outFile << "<url>" << endl;
		url = StringUtil::EncodeToXmlCopy(temp->getURL().getAbsoluteURL());
		outFile << url << endl;
		outFile << "</url>" << endl;
		discription = StringUtil::EncodeToXmlCopy(temp->getDiscrip());
		outFile << "<description>" << discription
				<< "</description>" << endl;
		outFile << "</page>" << endl;
	}
	outFile << "</pages>" << endl;
	delete iter;
}

void XMLGen::printIndex(ofstream& outFile, WordIndex* index){

	outFile << "<index>" << endl;
	BSTIter<Pair>* Piter = index->getIter();
	string url;
	while(Piter->hasNext()){
		Pair* temp = &(Piter->getNext());
		outFile << "<word>" << endl;
		outFile << "<value>" << endl;
		outFile << temp->getWord() << endl;
		outFile << "</value>" << endl;
		BSTIter<Occurence>* Oiter = temp->getOccurences().getIter();
		while(Oiter->hasNext()){
			Occurence* occur = &(Oiter->getNext());
			outFile << "<occurrence>" << endl;
			outFile << "<url>" << endl;
			url = StringUtil::EncodeToXmlCopy(occur->getURL().getAbsoluteURL());
			outFile << url << endl;
			outFile << "</url>" << endl;
			outFile << "<count>" << occur->getCount()
                    		<< "</count>" << endl;
			outFile << "</occurrence>" << endl;
		}
		outFile << "</word>" << endl;
		delete Oiter;
	}
	outFile << "</index>" << endl;    
	delete Piter;
}
