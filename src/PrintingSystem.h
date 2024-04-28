#ifndef UNTITLED_PRINTINGSYSTEM_H
#define UNTITLED_PRINTINGSYSTEM_H
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "Printer.h"
#include "Job.h"
#include "Queue.h"
#include "XMLprocessor.h"



class PrintingSystem {
private:
    int reportIndex = 0;
    int advancedreportIndex = 0;
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

    void createCompensation(int compnumber, string name);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");

    void proccesJob(std::ostream& outputstream = std::cout, Printer* printer = nullptr);

    void assignSingleJob();
    void assignAllJobs(std::ostream& outputstream = std::cout);

    void automatedJob(std::ostream& outputstream = std::cout);

    bool isQueueEmpty();
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //REQUIRE(jobs.properlyInitialized(), "Queue is not properly initialized");

    int getEmissions();
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    
    int getReportIndex() const;

    int getAdvancedreportIndex() const;

    void setReportIndex(int reportIndex);

    void setAdvancedreportIndex(int advancedreportIndex);

    const vector<Printer *> &getPrinters() const;

    const map<int, std::string> &getCompensationmap() const;


};


#endif //UNTITLED_PRINTINGSYSTEM_H
