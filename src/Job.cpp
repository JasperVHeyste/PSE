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
 * Assign a CO2 compensation to this job
 * @param comp the name of the compensation
 */
void Job::setCompensation(std::string comp) {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    compensation = comp;
    hascomp = true;
    ENSURE(hasCompensation(), "Compensation was not correctly assigned");
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

/**
 * @return compensation
 */
const std::string Job::getCompensation() const {
    REQUIRE(properlyInitialized(), "Job is not properly initialized");
    REQUIRE(hasCompensation(), "Job does not have a compensation assigned to it");
    return compensation;
}

/**
 * @return true if this job has a compensation, false if not
 */
bool Job::hasCompensation() const {
    return hascomp;
}

