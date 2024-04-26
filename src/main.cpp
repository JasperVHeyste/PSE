#include <iostream>
#include "PrintingSystem.h"
#include "tinyxml.h"

int main() {
    TiXmlDocument doc;
    XMLprocessor xmlp = XMLprocessor();
    PrintingSystem s = PrintingSystem();
    xmlp.implementXML("PDFinput.xml", s);

    s.simpleOutput();
    s.automatedJob();
    s.simpleOutput();

    cout << "Total CO2 emissions: " << s.getEmissions() << " gram." << endl;

    /*while(not s.isQueueEmpty()){
        s.simpleOutput();
        s.assignJob();
        s.simpleOutput();
        s.proccesJob();
        s.simpleOutput();
    }*/
}
