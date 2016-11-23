#include "URL.h"
#include "UnitTest.h"
#include <assert.h>
using namespace std;

/******************************************************************************
 * Class URL:
 *      This class stores a URL.  It brakes it up in parts for quick reference.
 *      It has a lot more function then I will probable use, but I could
 *      see them being needful if this code was used for more then just this
 *      project.
 *
 * Greg Hart
 * 14 Feb 2012
 *****************************************************************************/

const string URL::HTTP = "http://";
const string URL::FILE = "file://";

// I probably don't need all of these constructors, but they seemed
// like good ones to have.
URL::URL():scheme(""),netLoc(""),path(""){
}

URL::URL(char* url){
	string surl = url;
	parse(surl);
}

URL::URL(string url){
	parse(url);
}

URL::URL(char* base, char* rel){
	string sbase = base;
	string srel  = rel;
	string url = resolve(sbase, srel);
	parse(url);
}       

URL::URL(string base, string rel){
	string url = resolve(base, rel);
	parse(url);
}       

URL::URL(const URL& other){
	if(&other != this){
		free();
		copy(other);
	}
}

URL::~URL(){
	free();
}

//Get the whole URL or the various parts you may be interested in.
string URL::getAbsoluteURL() const{
	string url = scheme;
	url += netLoc;
	url += path;
	return url;
}

string URL::getScheme() const{
	return scheme;
}

string URL::getNetLoc() const{
	return netLoc;
}

string URL::getPath() const{
	return path;
}

URL URL::operator =(const URL& other){
	scheme = other.scheme;
	netLoc = other.netLoc;
	path = other.path;
	return *this;
}

// The page comparators will depend on the URL comparators.
bool URL::operator <(const URL& other) const{
	return getAbsoluteURL() < other.getAbsoluteURL();
}

bool URL::operator >(const URL& other) const{
	return getAbsoluteURL() > other.getAbsoluteURL();
}

bool URL::operator ==(const URL& other) const{
	return getAbsoluteURL() == other.getAbsoluteURL();

}

URL URL::operator =(const char* url){
	parse(url);
	return *this;
}

URL URL::operator =(string url){
	parse(url);
	return *this;
}

// ToString will be used to over load the insertion operator.  I
// think I forgot to add this to all the classes that need it.
string URL::toString() const{
	return getAbsoluteURL();
}

bool URL::isRelative(string url){
	string urlLower = StringUtil::ToLowerCopy(url);
	if(StringUtil::IsPrefix(urlLower, HTTP) ||
			StringUtil::IsPrefix(urlLower, FILE)){
		return false;
	}
	return true;
}

bool URL::isRelative(char* url){
	string surl = url;
	return isRelative(surl);
} 

//This two probably won't be used in this specific project.
void URL::free(){
	scheme = "";
	netLoc = "";
	path   = "";
}

URL& URL::copy(const URL& other){
	scheme = other.scheme;
	netLoc = other.netLoc;
	path   = other.path;
	return *this;
}        

//Parsing the URL into it parts, called by the constructors.
void URL::parse(string url){
	assert(url != "");
	addSlash(url);
	scheme = url.substr(0,schLen);
	StringUtil::ToLower(scheme);
	url = url.substr(schLen);
	if(url[1] == '/'){
		netLoc = "";
	} else {
		int end = url.find_first_of('/');
		netLoc = url.substr(0,end);
		StringUtil::ToLower(netLoc);
		url = url.substr(end);
	}
	int pound = url.find_first_of('#');
	path = url.substr(0,pound);
}

//Resolves relative URLs. Is called by the constructor, but I could
//see the need of noncostructor function that needs this as well.
string URL::resolve(string base, string rel){
	assert(base != "");
	assert(rel  != "");
	int idx = 0;
	string temp;
	addSlash(base);

	switch (rel[0]){
	case '/':
		rel = rel.substr(1);
		temp = base.substr(schLen);
		idx = temp.find_first_of('/') + 1;
		base = base.substr(0,idx+schLen);
		break;
	case '.':
		int dirs = parentDirs(rel);
		for( ; dirs > 0; dirs--){
			int idx = base.find_last_of('/');
			base = base.substr(0,idx-1);
		}
		break;
	}

	if(rel[0] != '#'){
		idx = base.find_last_of('/');
		if(idx < ((int)base.size() - 1)){
			base = base.substr(0,idx);
		}
	}
	if(base[base.size()-1] != '/'){
		base += '/';
	}

	base += rel;
	return base;
}

void URL::addSlash(string& base){
	if(base[0] == 'h'){
		string temp = base.substr(schLen);
		int per = temp.find_first_of('.');
		int slash = temp.find_last_of('/');
		if(per > slash){
			base += "/";
		}
	} else if(base.size() < schLen+1){
		base += "/";
	}
}

int URL::parentDirs(string& rel){
	int count = 0;
	while(rel[0] == '.'){
		if(rel[1] == '.'){
			count++;
			rel = rel.substr(3);
		} else {
			rel = rel.substr(2);
		}
	}
	return count;
}

ostream& operator <<(ostream& os, const URL url){
	os << url.toString();
	return os;
}

bool URL::Test(ostream& os){
	bool success = true;


	URL temp;
	TEST(temp.getAbsoluteURL() == "");
	TEST(temp.getScheme()      == "");
	TEST(temp.getNetLoc()      == "");
	TEST(temp.getPath()        == "");

	os << "\t\tTesting http urls" << endl;
	success = TestHTTP(os) && success;
	os << "\t\tTesting file urls" << endl;
	success = TestFILE(os) && success;
	return success;
}

bool URL::TestHTTP(ostream& os){
	bool success = true;

	string url = "http://www.cnn.com/news/financial/index.html";
	{
		URL temp(url);
		TEST(temp.getAbsoluteURL() == url);
		TEST(temp.getScheme()      == HTTP);
		TEST(temp.getNetLoc()      == "www.cnn.com");
		TEST(temp.getPath()        == "/news/financial/index.html");
	}

	url = "http://www.cnn.com/news/financial/index.html#HEADLINES";
	{
		URL temp(url);
		TEST(temp.getAbsoluteURL() == "http://www.cnn.com/news/financial/index.html");
		TEST(temp.getScheme()      == HTTP);
		TEST(temp.getNetLoc()      == "www.cnn.com");
		TEST(temp.getPath()        == "/news/financial/index.html");
	}

	url = "http://www.cnn.com/";
	{
		URL temp(url);
		TEST(temp.getAbsoluteURL() == url);
		TEST(temp.getScheme()      == HTTP);
		TEST(temp.getNetLoc()      == "www.cnn.com");
		TEST(temp.getPath()        == "/");
	}

	url = "http://www.cnn.com";
	{
		URL temp(url);
		TEST(temp.getAbsoluteURL() == (url + "/"));
		TEST(temp.getScheme()      == HTTP);
		TEST(temp.getNetLoc()      == "www.cnn.com");
		TEST(temp.getPath()        == "/");
	}

	string base = "http://www.cnn.com/news/financial/index.html";
	string rel  = "./images/nasdaq.jpg";
	url = "http://www.cnn.com/news/financial/images/nasdaq.jpg";
	{
		URL temp(base,rel);
		TEST(temp.getAbsoluteURL() == url);
		TEST(temp.getScheme()      == HTTP);
		TEST(temp.getNetLoc()      == "www.cnn.com");
		TEST(temp.getPath()        == "/news/financial/images/nasdaq.jpg");
	}

	base = "http://www.cnn.com";
	rel  = "/images/nasdaq.jpg";
	url  = "http://www.cnn.com/images/nasdaq.jpg";
	{
		URL temp(base,rel);
		TEST(temp.getAbsoluteURL() == url);
		TEST(temp.getScheme()      == HTTP);
		TEST(temp.getNetLoc()      == "www.cnn.com");
		TEST(temp.getPath()        == rel);
	}

	base = "http://www.cnn.com/news/financial/folder/another/again/still/index.html";
	rel = "./../.././././.././././.././../images/nasdaq.jpg";
	url = "http://www.cnn.com/news/images/nasdaq.jpg";
	{
		URL temp(base,rel);
		TEST(temp.getAbsoluteURL() == url);
		TEST(temp.getScheme()      == HTTP);
		TEST(temp.getNetLoc()      == "www.cnn.com");
		TEST(temp.getPath()        == "/news/images/nasdaq.jpg");
	}

	return success;
}

bool URL::TestFILE(ostream& os){
	bool success = true;

	string url = "file:///news/financial/folder/another/again/still/index.html";
	{
		URL temp(url);
		TEST(temp.getAbsoluteURL() == url);
		TEST(temp.getScheme()      == FILE);
		TEST(temp.getNetLoc()      == "");
		TEST(temp.getPath()        == "/news/financial/folder/another/again/still/index.html");
	}

	url = "FILE:///news/financial/";
	{
		URL temp(url);
		TEST(temp.getAbsoluteURL() == "file:///news/financial/");
		TEST(temp.getScheme()      == FILE);
		TEST(temp.getNetLoc()      == "");
		TEST(temp.getPath()        == "/news/financial/");
	}

	url = "file://";
	{
		URL temp(url);
		TEST(temp.getAbsoluteURL() == (url + "/"));
		TEST(temp.getScheme()      == FILE);
		TEST(temp.getNetLoc()      == "");
		TEST(temp.getPath()        == "/");
	}

	string base = "file:///news/financial/index.html";
	string rel  = "./images/nasdaq.jpg";
	url = "file:///news/financial/images/nasdaq.jpg";
	{
		URL temp(base,rel);
		TEST(temp.getAbsoluteURL() == url);
		TEST(temp.getScheme()      == FILE);
		TEST(temp.getNetLoc()      == "");
		TEST(temp.getPath()        == "/news/financial/images/nasdaq.jpg");
	}

	base = "file://";
	rel  = "/images/nasdaq.jpg";
	url  = "file:///images/nasdaq.jpg";
	{
		URL temp(base,rel);
		TEST(temp.getAbsoluteURL() == url);
		TEST(temp.getScheme()      == FILE);
		TEST(temp.getNetLoc()      == "");
		TEST(temp.getPath()        == rel);
	}

	base = "file:///news/financial/folder/another/again/still/index.html";
	rel = "./../.././././.././././.././../images/nasdaq.jpg";
	url = "file:///news/images/nasdaq.jpg";
	{
		URL temp(base,rel);
		TEST(temp.getAbsoluteURL() == url);
		TEST(temp.getScheme()      == FILE);
		TEST(temp.getNetLoc()      == "");
		TEST(temp.getPath()        == "/news/images/nasdaq.jpg");
	}

	return success;
}
