#ifndef PROJECT_XMLPROCESSOR_H
#define PROJECT_XMLPROCESSOR_H
#include "tinyxml.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

class XMLprocessor {
private:
   vector<int> previousjobnumbers;
   XMLprocessor* initializecheck;
public:
    XMLprocessor();

    bool properlyinitialized();
    //ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");

    vector<map<string, string>> readXML(const char* filename, ostream& outputstream = cout);
    //REQUIRE(properlyinitialized(), "XMLprocessor is not properly initialized");
    //REQUIRE(ftype == ".xml", "Inputfile has to be an xml file");

    bool checkStringIsPositiveInt(string s);
    //REQUIRE(properlyinitialized(), "XMLprocessor is not properly initialized");
};




#endif //PROJECT_XMLPROCESSOR_H
