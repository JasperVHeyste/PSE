#include <iostream>
#include "PrintingSystem.h"
#include "tinyxml.h"

int main() {
    TiXmlDocument doc;
    PrintingSystem s = PrintingSystem();
    s.implementXML("testinput1.xml");
}
