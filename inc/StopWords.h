#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include "StringUtil.h"
using namespace std;

/**************************************************************************
 * Class StopWords:
 *      This class reads in the stop words file and stores it in an array
 *      list for quick searches.
 *
 *  Greg Hart
 *  14 Feb 2012
 *************************************************************************/
class StopWords{
private:
	//The array its max size and the size of the used portion of the array
	string* words;
	int size;
	int max;
public:
	//Constructors and destructors
	StopWords();

	StopWords(char* fileName);

	~StopWords();

	// Preforms a binary search for word on the array.
	bool hasWord(string word);

	void print();
private:
	//Using to increase the array size when it fills.  It will only be called
	//by the constructor unless I add an add method.
	void grow();

	//Handles the reading in of the words from the file.
	void readFile(char* fileName);

	bool find(int start, int end, string word);     
};


