#include "Job.h"

Job::Job(int jn, int pc, std::string un) : jobnumber(jn), pagecount(pc), username(un) {
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");
}

bool Job::properlyInitialized() const{
    return initcheck == this;
}

int Job::getJobnumber() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return jobnumber;
}

int Job::getPagecount() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return pagecount;
}

const std::string& Job::getUsername() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return username;
}