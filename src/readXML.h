#ifndef PROJECT_READXML_H
#define PROJECT_READXML_H
#include "tinyxml.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

bool stringIsPositiveInteger(std::string s);
vector<map<string, string>> readXML(const char* filename, std::ostream& outputstream = cout);

#endif //PROJECT_READXML_H
