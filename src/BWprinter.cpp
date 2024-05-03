#include "BWprinter.h"

/**
 * If this device has a job assigned to it, process that job
 * @param outputstream the outputstream where any messages about the progress are sent
 * @return true if the device had a job, false if not
 */
bool BWprinter::work(ostream& outputstream) {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");

    int jobsbeforework = getJobAmount();

    if (not hasJob()){
        return false;
    }

    Job* currentjob = jobs.front();

    outputstream << "Printer " << "'" << name << "'" << " finished black-and-white job:" << "\n    Number: "
                 << currentjob->getJobnumber() << "\n    Submitted by '" <<
                 currentjob->getUsername() << "'" << endl << "    " << currentjob->getPagecount() << " pages" << endl;
    if (currentjob->hasCompensation()){
        outputstream << "Job " << currentjob->getJobnumber() << " was made CO2 neutral with the support of " << currentjob->getCompensation() << "." << endl;
    }
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