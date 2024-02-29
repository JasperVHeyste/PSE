#ifndef UNTITLED_PRINTINGSYSTEM_H
#define UNTITLED_PRINTINGSYSTEM_H
#include <vector>
#include "Printer.h"


class PrintingSystem {
private:
    std::vector<Printer> printers;


public:
    virtual ~PrintingSystem();

};


#endif //UNTITLED_PRINTINGSYSTEM_H
