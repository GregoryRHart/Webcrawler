#pragma once

#include <string>
#include <iostream>
#include "StringUtil.h"
using namespace std;

/**************************************************************************
 * Class URL:
 *      This class stores a URL.  It brakes it up in parts quick reference.
 *      It has a lot more function then I will probable use, but I could
 *      see them being needful if this code was used for more then just this
 *      project
 *
 * Greg Hart
 * 14 Feb 2012
 **************************************************************************/

class URL{
private:
	//The two possible schemes (I haven't seen https mentioned anywhere).
	static const string HTTP;
	static const string FILE;
	//The length of the two possible schemes.
	static const int schLen = 7;
	//The protocal, network location, and the rest of the address.
	string scheme;
	string netLoc;
	string path;

public:
	// I probably don't need all of these constructors, but they seemed
	// like good ones to have.
	URL();

	URL(char* url);

	URL(string url);

	URL(char* base, char* rel);       

	URL(string base, string rel);       

	URL(const URL& other);

	~URL();

	//Get the whole URL or the various parts you may be interested in.
	string getAbsoluteURL() const;

	string getScheme() const;

	string getNetLoc() const;

	string getPath() const;

	URL operator =(const URL& other);

	//The page comparators will depend on the URL comparators.
	bool operator <(const URL& other) const;

	bool operator >(const URL& other) const;

	bool operator ==(const URL& other) const;

	URL operator =(string url);

	URL operator =(const char* url);

	//ToString will be used to over load the insertion operator.  I
	//think I forgot to add this to all the classes that need it.
	string toString() const;

	//Checks if a url is relative or absolute;
	static bool isRelative(char* url);

	static bool isRelative(string url);

	static bool Test(ostream& os);
private:
	//This two probably won't be used in this specific project.
	void free();

	URL& copy(const URL& other);        

	//Parsing the URL into it parts, called by the constructors.
	void parse(string url);

	//Resolves relative URLs. Is called by the constructor, but I could
	//see the need of noncostructor function that needs this as well.
	string resolve(string base, string rel);

	int parentDirs(string& rel);

	void addSlash(string& base);

	static bool TestHTTP(ostream& os);

	static bool TestFILE(ostream& os);

};

ostream& operator <<(ostream& os, const URL url);

