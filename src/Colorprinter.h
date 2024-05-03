#ifndef PROJECT_COLORPRINTER_H
#define PROJECT_COLORPRINTER_H

#include "ContractManager.h"
#include "Device.h"
#include "Job.h"
using namespace std;

class Colorprinter : public Device{
public:
    Colorprinter(std::string n, int e, int s, int c) : Device(n, e, s, c) {};

    virtual bool work(std::ostream& outputstream = std::cout);
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
    //ENSURE(getJobAmount() < jobsbeforework, "Job has not successfully been processed");

    virtual std::string getType() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
};


#endif
