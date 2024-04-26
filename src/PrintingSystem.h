#ifndef UNTITLED_PRINTINGSYSTEM_H
#define UNTITLED_PRINTINGSYSTEM_H
#include <vector>
#include <string>
#include <algorithm>
#include "Printer.h"
#include "Job.h"
#include "Queue.h"
#include "XMLprocessor.h"



class PrintingSystem {
private:
    int reportIndex = 0;
    int totalemissions = 0;
    std::vector<Printer*> printers;
    std::vector<Printer*> scanners;
    std::vector<Printer*> bwprinters;
    std::vector<Printer*> colorprinters;
    Queue jobs;
    std::map<int,std::string> compensationmap;
    PrintingSystem* initcheck;

public:
    PrintingSystem();
    virtual ~PrintingSystem() {};

    bool properlyInitialized();
    //ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");

    void createPrinter(std::string name, int emissions, int speed, string type, int cost);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //ENSURE(newPrinter->properlyInitialized(), "Printer must be properly initialized");

    void createJob(int jobnumber, int pagecount, string username, string type, int compensation);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //ENSURE(newJob->properlyInitialized(), "Job must be properly initialized");

    void implementXML(const char* filename, XMLprocessor& xmlp);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //REQUIRE(properlyInitialized(), "XMLprocessor is not properly initialized");
    //REQUIRE(ftype == ".xml", "Inputfile has to be an xml file");

    void proccesJob(std::ostream& outputstream = std::cout, Printer* printer = nullptr);

    void assignSingleJob();
    void assignAllJobs();

    void automatedJob(std::ostream& outputstream = std::cout);

    // use case 2.1
    void simpleOutput();

    bool isQueueEmpty();
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //REQUIRE(jobs.properlyInitialized(), "Queue is not properly initialized");

    int getEmissions();
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
};


#endif //UNTITLED_PRINTINGSYSTEM_H
