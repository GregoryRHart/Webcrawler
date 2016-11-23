//The implamentation of HTMLParser.h
#include "HTMLParser.h"

HTMLParser::HTMLParser(){
}

HTMLParser::~HTMLParser(){
}

void HTMLParser::parse(Page* page, StopWords* stopWords){
	string url = page->getURL().getAbsoluteURL();
	URLInputStream* stream = NULL;
	try{
		stream = new URLInputStream(url);

		HTMLTokenizer tokenizer(stream);

		toHTMLStart(*page, tokenizer);

		parseHead(*page, tokenizer, *stopWords);

		parseBody(*page, tokenizer, *stopWords);

		toHTMLEnd(*page, tokenizer);

	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
		delete stream;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
		delete stream;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
		delete stream;
	}
	delete stream;
}

void HTMLParser::toHTMLStart(Page& page, HTMLTokenizer& tokenizer){

	//I am assuming that GetValue() will returns the tag values in all lowercase
	//if not I can add ToLower() from the StringUtils. 
	HTMLToken current("",COMMENT);
	try{
		current = tokenizer.GetNextToken();
		string value = current.GetValue(); 
		StringUtil::ToLower(value);
		while(current.GetType() != END && value.compare("html") != 0){
			current = tokenizer.GetNextToken();   
			value =current.GetValue();
			StringUtil::ToLower(value);
		}
	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
	}
}

void HTMLParser::parseHead(Page& page, HTMLTokenizer& tokenizer, StopWords& stopWords){

	HTMLToken current("",COMMENT);
	try{
		current = tokenizer.GetNextToken();
		string value = current.GetValue();
		StringUtil::ToLower(value); 
		while(current.GetType() != END && value.compare("body") != 0){
			if(value.compare("a") == 0){
				handleLink(page, current);
			} else if(value.compare("title") == 0){
				parseTitle(page, tokenizer, stopWords);
			}
			current = tokenizer.GetNextToken();
			value = current.GetValue();
			StringUtil::ToLower(value);
		}
	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
	}
}

void HTMLParser::parseBody(Page& page, HTMLTokenizer& tokenizer, StopWords& stopWords){
	HTMLToken current("",COMMENT);
	string discrip = "";
	int whiteSpace = 0;
	try{
		current = tokenizer.GetNextToken();
		HTMLTokenType type = current.GetType();
		string value = current.GetValue();
		StringUtil::ToLower(value); 
		while(current.GetType() != END && value.compare("body") != 0){
			if(value.compare("a") == 0){
				handleLink(page, current);
			} else if(type == TEXT){
				string temp = current.GetValue();
				makeWord(page, temp, stopWords);
				if(discrip.size()-whiteSpace < 100){
					whiteSpace += countWS(temp);
					discrip += temp;
				}
			} else if(value.compare("script") == 0){
				parseScript(tokenizer);
			} else if(discrip.compare("") != 0 && value[0] == 'h'
					&& isdigit(value[1])){
				parseHeader(page, tokenizer, stopWords);
			}
			current = tokenizer.GetNextToken();
			type = current.GetType();
			value = current.GetValue();
			StringUtil::ToLower(value);
		}
	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
	}

	if(!page.hasDiscrip()){
		discrip = trimLen(discrip);
		page.setDiscrip(discrip);
	}
}

void HTMLParser::toHTMLEnd(Page& page, HTMLTokenizer& tokenizer){

	HTMLToken current("",COMMENT);
	try{
		current = tokenizer.GetNextToken();
		string value = current.GetValue(); 
		StringUtil::ToLower(value);
		while(current.GetType() != END && value.compare("html") != 0){  
			if(value.compare("a") == 0){
				handleLink(page, current);
			}
			current = tokenizer.GetNextToken();   
			value =current.GetValue();
			StringUtil::ToLower(value);
		}
	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
	}
}

void HTMLParser::parseTitle(Page& page, HTMLTokenizer& tokenizer, StopWords& stopWords){

	HTMLToken current("",COMMENT);
	string discrip = "";
	try{
		current = tokenizer.GetNextToken();
		HTMLTokenType type = current.GetType();
		string value = current.GetValue();
		StringUtil::ToLower(value); 
		while(current.GetType() != END && value.compare("title") != 0){
			if(value.compare("a") == 0){
				handleLink(page, current);
			} else if(type == TEXT){
				discrip += current.GetValue();
				makeWord(page, current.GetValue(), stopWords);
			} else if(value.compare("script") == 0){
				parseScript(tokenizer);
			}
			current = tokenizer.GetNextToken();
			type = current.GetType();
			value = current.GetValue();
			StringUtil::ToLower(value);
		}
	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
	}

	if(!page.hasDiscrip() && discrip.compare("") != 0){
		page.setDiscrip(discrip);
	}
}

void HTMLParser::parseScript(HTMLTokenizer& tokenizer){

	HTMLToken current("",COMMENT);
	try{
		current = tokenizer.GetNextToken();
		string value = current.GetValue(); 
		StringUtil::ToLower(value);
		while(current.GetType() != END && value.compare("script") != 0){
			current = tokenizer.GetNextToken();   
		    value = current.GetValue();
		    StringUtil::ToLower(value);
        }
	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
	}
}

void HTMLParser::parseHeader(Page& page, HTMLTokenizer& tokenizer, StopWords& stopWords){

	HTMLToken current("",COMMENT);
	string discrip = "";
	try{
		current = tokenizer.GetNextToken();
		HTMLTokenType type = current.GetType();
		string value = current.GetValue();
		StringUtil::ToLower(value); 
		while(current.GetType() != END && !(value[0] == 'h' && isdigit(value[1]))){
			if(value.compare("a") == 0){
				handleLink(page, current);
			} else if(type == TEXT){
				discrip += current.GetValue();
				makeWord(page, current.GetValue(), stopWords);
			} else if(value.compare("script") == 0){
				parseScript(tokenizer);
			}
			current = tokenizer.GetNextToken();
			type = current.GetType();
			value = current.GetValue();
			StringUtil::ToLower(value);
		}
	}
	catch(exception &e){
		cout << "Exception Occured: " << e.what() << endl;
	}
	catch(CS240Exception &e){
		cout << "Exception Occured: " << e.GetMessage() << endl;
	}
	catch(...){
		cout << "Unknown Exception Occured"  << endl;
	}

	if(!page.hasDiscrip()){
		page.setDiscrip(discrip);
	}
}

void HTMLParser::handleLink(Page& page, HTMLToken& current){
	string url = current.GetAttribute("HREF");
	if(url.compare("") != 0){
		page.addLink(url);
	}
}

int HTMLParser::countWS(string words){
	int len = words.size();
	int count = 0;
	for(int i=0; i<len; i++){
		if(isspace(words[i])){
			count ++;
		}
	}
	return count;
}

string HTMLParser::trimLen(string discrip){
	int count = 0;
	int len = discrip.size();
	for(int i=0; i<len; i++){
		if(!isspace(discrip[i])){
			count++;
			if(count >= 100){
				return discrip.substr(0,i+1);
			}
		}
	}
	return discrip;
}

void HTMLParser::makeWord(Page& page, string words, StopWords& stopWords){
	StringUtil::ToLower(words);
	string temp;
	int len = words.size();
	int i = 0;
	while(i<len){
		if(!isWordChar(words[i]) || i == len-1){
			if(i == len-1){
				if(isWordChar(words[i])){
					temp = words; 
				} else {
					temp = words.substr(0,i);
				}
				i++;
			} else {
				temp = words.substr(0,i);
				words = words.substr(i+1);
				i = 0;
				len = words.size();
			}
			if(temp.compare("") != 0 && isalpha(temp[0]) && !stopWords.hasWord(temp)){
				page.addWord(temp);
			}
		} else {
			i++;
		}
	}
}

bool HTMLParser::isWordChar(char cur){
	return isalnum(cur) || cur == '_' || cur == '-';
}
