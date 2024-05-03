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

    bool properlyInitialized() const;
    //ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");

    void createPrinter(std::string name, int emissions, int speed, string type, int cost);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //ENSURE(newPrinter->properlyInitialized(), "Printer must be properly initialized");

    void createJob(int jobnumber, int pagecount, string username, string type, int compensation);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //ENSURE(newJob->properlyInitialized(), "Job must be properly initialized");

    void createCompensation(int compnumber, string name);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //ENSURE(amountofcompensationsafter > amountofcompensationsbefore, "Compensation has not been successfully added");

    void proccesJob(std::ostream& outputstream = std::cout, Printer* printer = nullptr);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");

    void assignSingleJob();
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");

    void assignAllJobs(std::ostream& outputstream = std::cout);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //ENSURE(isQueueEmpty(), "There are still jobs left in the queue while all should have been assigned");

    void automatedJob(std::ostream& outputstream = std::cout);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");

    bool isQueueEmpty();
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    //REQUIRE(jobs.properlyInitialized(), "Queue is not properly initialized");

    int getEmissions();
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    
    int getReportIndex() const;
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");

    int getAdvancedreportIndex() const;
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");

    void setReportIndex(int reportIndex);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");

    void setAdvancedreportIndex(int advancedreportIndex);
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");

    const vector<Printer *> &getPrinters() const;
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");

    const map<int, std::string> &getCompensationmap() const;
    //REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
};


#endif //UNTITLED_PRINTINGSYSTEM_H
