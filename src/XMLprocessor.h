#ifndef PROJECT_XMLPROCESSOR_H
#define PROJECT_XMLPROCESSOR_H
#include "tinyxml.h"
#include "ContractManager.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

class XMLprocessor {
private:
   vector<int> previousjobnumbers;
   vector<int> previouscompnumbers;
   XMLprocessor* initcheck;
public:
    XMLprocessor();
    //ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");

    bool properlyInitialized() const;

    bool checkStringIsPositiveInt(string s) const;
    //REQUIRE(properlyInitialized(), "XMLprocessor is not properly initialized");

    vector<map<string, string>> readXML(const char* filename, ostream& outputstream = cout);
    //REQUIRE(properlyInitialized(), "XMLprocessor is not properly initialized");
    //REQUIRE(ftype == ".xml", "Inputfile has to be an xml file");
};




#endif //PROJECT_XMLPROCESSOR_H
