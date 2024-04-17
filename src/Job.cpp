#include "Job.h"

/**
 * Constructor for a job
 * @param jn jobnumber
 * @param pc page count
 * @param un username
 * @param t type of job
 */
Job::Job(int jn, int pc, std::string un, std::string t) : jobnumber(jn), pagecount(pc), username(un), type(t) {
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");
}

/**
 * Check if the job is properly inialized by checking if the pointer assigned in the constructor points to itself
 * @return true if properly initialzed, false if not
 */
bool Job::properlyInitialized() const{
    return initcheck == this;
}

/**
 * @return jobnumber
 */
int Job::getJobnumber() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return jobnumber;
}

/**
 * @return pagecount
 */
int Job::getPagecount() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return pagecount;
}

/**
 * @return username
 */
const std::string& Job::getUsername() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return username;
}

/**
 * @return type
 */
const std::string& Job::getType() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    return type;
}