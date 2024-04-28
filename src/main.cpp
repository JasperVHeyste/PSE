#include <iostream>
#include "PrintingSystem.h"
#include "tinyxml.h"
#include "Output.h" 

int main() {
    TiXmlDocument doc;
    XMLprocessor xmlp = XMLprocessor();
    PrintingSystem s = PrintingSystem();
    xmlp.implementXML("PDFinput.xml", s);
    Output o;

    o.simpleOutput(&s);
    o.advancedOutput(&s);
    s.automatedJob();
    o.simpleOutput(&s);
    o.advancedOutput(&s);

    cout << "Total CO2 emissions: " << s.getEmissions() << " gram." << endl;

    /*while(not s.isQueueEmpty()){
        s.simpleOutput();
        s.assignJob();
        s.simpleOutput();
        s.proccesJob();
        s.simpleOutput();
    }*/
}
