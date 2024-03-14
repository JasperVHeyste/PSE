#ifndef UNTITLED_PRINTINGSYSTEM_H
#define UNTITLED_PRINTINGSYSTEM_H
#include <vector>
#include <string>

#include "Printer.h"
#include "Job.h"
#include "Queue.h"
#include "XMLprocessor.h"



class PrintingSystem {
private:
    int reportIndex = 0;
    std::vector<Printer*> printers;
    Queue jobs;
    PrintingSystem* initcheck;

public:
    PrintingSystem();
    virtual ~PrintingSystem();

    bool properlyInitialized();
    //ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");

    void createPrinter(std::string name, int emissions, int speed);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //ENSURE(newPrinter->properlyInitialized(), "Printer must be properly initialized");

    void createJob(int jobnumber, int pagecount, string username);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //ENSURE(newJob->properlyInitialized(), "Job must be properly initialized");

    void implementXML(const char* filename, XMLprocessor& xmlp);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //REQUIRE(properlyInitialized(), "XMLprocessor is not properly initialized");
    //REQUIRE(ftype == ".xml", "Inputfile has to be an xml file");

    void proccesJob();
    void assignJob();
    void automatedJob();

    // use case 2.1
    void simpleOutput();

    bool isQueueEmpty();
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //REQUIRE(jobs.properlyInitialized(), "Queue is not properly initialized");
};


#endif //UNTITLED_PRINTINGSYSTEM_H
