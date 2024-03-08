#include <iostream>
#include "PrintingSystem.h"
#include "tinyxml.h"

int main() {
    TiXmlDocument doc;
    XMLprocessor xmlp = XMLprocessor();
    PrintingSystem s = PrintingSystem();
    s.implementXML("PDFinput.xml", xmlp);
    s.automatedJob();
//    s.manualJob();
//    s.manualJob();
//    s.manualJob();
}
