#include "StopWords.h"
using namespace std;

/**************************************************************************
 * Class StopWords:
 *      This class reads in the stop words file and stores it in an array
 *      list for quick searches.
 *
 *  Greg Hart
 *  14 Feb 2012
 *************************************************************************/
//Constructors and destructors
StopWords::StopWords():size(0),max(1024){
	words = new string[1024];
}

StopWords::StopWords(char* fileName):size(0),max(1024){
	words = new string[1024];
	readFile(fileName);
}

StopWords::~StopWords(){
	//    for(int i=0; i<size; i++){
	//        delete words[i];
	//    }
	delete [] words;
}

// Preforms a binary search for word on the array.
bool StopWords::hasWord(string word){
	StringUtil::ToLower(word);
	return find(0,size,word);
}

//Using to increase the array size when it fills.  It will only be called
//by the constructor unless I add an add method.
void StopWords::grow(){
	max *= 2;
	string* temp = new string[max];
	for(int i = 0; i<size;i++){
		temp[i] = words[i];
	}
	delete [] words;
	words = temp;

}

//Handles the reading in of the words from the file.
void StopWords::readFile(char* fileName){
	ifstream file;
	file.open(fileName);

	if (!file.is_open()) {
		cout << "Unable to open file: " << fileName << endl;
		return;
	}

	char curWord[1024];
	while (file.getline(curWord, sizeof(curWord))){
		string* Word = new string(curWord);
		StringUtil::ToLower(*(Word));
		if(*Word != ""){
			if(size >= max){
				grow();
			}
			words[size] = *Word;
			size++;
		}
		delete Word;
	}
	file.close();
}

bool StopWords::find(int start, int end, string word){
	while(start < end){
		int mid = (end+start)/2;
		if(word.compare((words[mid])) == 0){
			return true;
		} else if(word.compare((words[mid])) < 0){
			end = mid;
		} else if(word.compare((words[mid])) > 0){
			start = mid+1;
		}
	}
	return false;
}     

void StopWords::print(){
	for(int i=0; i<size; i++){
		cout << words[i] << endl;
	}
}

