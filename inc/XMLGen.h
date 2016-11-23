#pragma once

#include "StringUtil.h"
#include "VisitedPages.h"
#include "WordIndex.h"
#include "URL.h"
#include <fstream>
#include <string>
using namespace std;

/****************************************************
 * Class XMLGen:
 *      This class writes the XML to the output file.
 *
 * Greg Hart
 * 14 Feb 2012
 ***************************************************/
class XMLGen{
private:
	//Name of output file
	string fileName;
public:
	//Default constructor
	XMLGen();

	//File is the name of the file to write the XML to.
	XMLGen(string file);

	//I shouldn't have to explicitly delete anything.
	~XMLGen();

	//Generates the XML and prints it to a file named fileName. The XML
	//is all inside a website tag.  In this tag there are three divisions
	//start-url, Pages, and Index.
	void encodeToXML(URL start, VisitedPages* visited, WordIndex* index);

private:
	//Generates the Pages section of the XML file
	void printPages(ofstream& outFile, VisitedPages* visited);

	//Generates the Index section of the XML file
	void printIndex(ofstream& outFile, WordIndex* index);
};


