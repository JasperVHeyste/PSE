#include <iostream>
#include "PrintingSystem.h"
#include "tinyxml.h"

int main() {
    TiXmlDocument doc;
    XMLprocessor xmlp = XMLprocessor();
    PrintingSystem s = PrintingSystem();
    s.implementXML("PDFinput.xml", xmlp);

    s.automatedJob();

    /*while(not s.isQueueEmpty()){
        s.simpleOutput();
        s.assignJob();
        s.simpleOutput();
        s.proccesJob();
        s.simpleOutput();
    }*/
}
