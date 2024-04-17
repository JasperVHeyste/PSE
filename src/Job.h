#ifndef UNTITLED_JOB_H
#define UNTITLED_JOB_H

#include "ContractManager.h"
#include <string>

class Job {
private:
    int jobnumber;
    int pagecount;
    std::string username;
    std::string type;

    Job* initcheck;

public:
    Job(int jn, int pc, std::string un, std::string t = "unspecified");
    //ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state")

    ~Job() {};

    bool properlyInitialized() const;

    int getJobnumber() const;
    //REQUIRE(properlyInitialized(), "Job is not properly initialized")

    int getPagecount() const;
    //REQUIRE(properlyInitialized(), "Job is not properly initialized")

    const std::string& getUsername() const;
    //REQUIRE(properlyInitialized(), "Job is not properly initialized")

    const std::string& getType() const;
    //REQUIRE(properlyInitialized(), "Job is not properly initialized")
};


#endif //UNTITLED_JOB_H
