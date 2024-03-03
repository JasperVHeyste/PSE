#ifndef UNTITLED_PRINTINGSYSTEM_H
#define UNTITLED_PRINTINGSYSTEM_H
#include <vector>
#include <string>

#include "Printer.h"
#include "Job.h"
#include "Queue.h"
#include "readXML.h"


class PrintingSystem {
private:
    std::vector<Printer*> printers;
    Queue jobs;

public:
    virtual ~PrintingSystem();

    void createPrinter(std::string name, int emissions, int speed);
    void createJob(int jobnumber, int pagecount, string username);

    void implementXML(const char* file);
};


#endif //UNTITLED_PRINTINGSYSTEM_H
