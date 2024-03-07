#include <iostream>
#include "PrintingSystem.h"
#include "tinyxml.h"

int main() {
    TiXmlDocument doc;
    PrintingSystem s = PrintingSystem();
    s.implementXML("PDFinput.xml");
    s.automatedJob();
//    s.manualJob();
//    s.manualJob();
//    s.manualJob();
}
