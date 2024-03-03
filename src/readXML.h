#ifndef PROJECT_READXML_H
#define PROJECT_READXML_H
#include "tinyxml.h"
#include <vector>
#include <map>
#include <string>
using namespace std;

vector<map<string, string>> readXML(const char* filename);

#endif //PROJECT_READXML_H
