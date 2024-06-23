#include "Colorprinter.h"
#include "Logger.h"

/**
 * If this device has a job assigned to it, process that job
 * @param outputstream the outputstream where any messages about the progress are sent
 * @return true if the device had a job, false if not
 */
bool Colorprinter::work(ostream& outputstream) {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    Logger l;
    int jobsbeforework = getJobAmount();

    if (not hasJob()){
        return false;
    }

    Job* currentjob = jobs.front();

    l.logColorprinter(currentjob, this, outputstream);
    jobs.pop();

    ENSURE(getJobAmount() < jobsbeforework, "Job has not successfully been processed");
    return true;
}

/**
 * @return the type of this device, being "color"
 */
string Colorprinter::getType() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return "color";
}
