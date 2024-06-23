#include "BWprinter.h"
#include "Loggerr.h"

/**
 * If this device has a job assigned to it, process that job
 * @param outputstream the outputstream where any messages about the progress are sent
 * @return true if the device had a job, false if not
 */
bool BWprinter::work(ostream& outputstream) {
    Loggerr l;
    REQUIRE(properlyInitialized(), "Device is not properly initialized");

    int jobsbeforework = getJobAmount();

    if (not hasJob()){
        return false;
    }

    Job* currentjob = jobs.front();

    l.logBWPprinter2(currentjob, this, outputstream);

    jobs.pop();

    ENSURE(getJobAmount() < jobsbeforework, "Job has not successfully been processed");
    return true;
}

/**
 * @return the type of this device, being "bw"
 */
string BWprinter::getType() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return "bw";
}
