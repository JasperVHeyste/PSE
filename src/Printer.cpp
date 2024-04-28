#include "Printer.h"
#include <chrono>
#include <thread>
#include "Job.h"
#include <iostream>

using namespace std;
/**
 * Constructor for a printer
 * @param n name of the printer
 * @param e emissions the printer emits (gram of C02 per page)
 * @param s speed of the printer (pages per minute)
 * @param t type of the printer
 * @param c cost of printing (eurocent per page)
 */
Printer::Printer(std::string n, int e, int s, std::string t, int c)  : name(n), emission(e), speed(s), type(t), cost(c) {
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");
}

/**
 * Check if the printer is properly inialized by checking if the pointer assigned in the constructor points to itself
 * @return true if properly initialzed, false if not
 */
bool Printer::properlyInitialized() const {
    return initcheck == this;
}

/**
 * Assign a job to the printer
 * @param j the job that needs to be assigned to this printer
 */
void Printer::setJob(Job *j) {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    REQUIRE(j->properlyInitialized(), "Job is not properly initialized");
    jobs.push(j);
}

/**
 * If this printer has a job assigned to it, process that job
 * @param outputstream the outputstream where any messages about the progress are sent
 * @return true if the printer had a job, false if not
 */
bool Printer::work(ostream& outputstream) {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    if (not hasJob()){
        return false;
    }
    string typestring = getType();
    if (getType() == "bw") {
        typestring = " black and white printing";
    }
    else if (getType() == "color") {
        typestring = " color-printing";
    }
    else if (getType() == "scan") {
        typestring = " scanning";
    }

    Job* currentjob = jobs.front();
    outputstream << "Printer " << "'" << name << "'" << " finished" << typestring << " job:" << "\n    Number: "
                 << currentjob->getJobnumber() << "\n    Submitted by '" <<
                 currentjob->getUsername() << "'" << endl << "    " << currentjob->getPagecount() << " pages" << endl;
    if (currentjob->hasCompensation()){
        outputstream << "Job " << currentjob->getJobnumber() << " was made CO2 neutral with the support of " << currentjob->getCompensation() << "." << endl;
    }
    jobs.pop();
    return true;
}

/**
 * @return true if the printer has a job, false if not
 */
bool Printer::hasJob() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return not jobs.empty();
}

/**
 * @return the name of the printer
 */
const std::string &Printer::getName() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return name;
}

/**
 * @return the emissions of the printer
 */
int Printer::getEmission() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return emission;
}

/**
 * @return the username of the person using the printer
 */
const std::string &Printer::getUsername() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    REQUIRE(hasJob(), "Printer does not have a job assigned to it");
    return jobs.front()->getUsername();
}

/**
 * @return the jobnumber of the job the printer has assigned to it
 */
int Printer::getJobnumber() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    REQUIRE(hasJob(), "Printer does not have a job assigned to it");
    return jobs.front()->getJobnumber();
}

/**
 * @return the pagecount of the job the printer has assigned to it
 */
int Printer::getPagecount() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    REQUIRE(hasJob(), "Printer does not have a job assigned to it");
    return jobs.front()->getPagecount();
}

/**
 * @return the amount it costs to use this printer
 */
int Printer::getCost() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return cost;
}

/**
 * @return the type of the printer
 */
std::string Printer::getType() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return type;
}

/**
 * @return the job the printer has assigned to it
 */
Job *Printer::getJob() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return jobs.front();
}

/**
 * @return the emissions the printer emits during the job it handles currently
 */
int Printer::getJobEmissions() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    REQUIRE(hasJob(), "Printer does not have a job assigned to it");
    return emission*getPagecount();
}

/**
 * @return the amount of jobs left in the queue of the printer
 */
int Printer::getJobAmount() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return jobs.size();
}

/**
 * @return the queue with jobs
 */
const queue<Job*>& Printer::getJobs() const {
    return jobs;
}

/**
 * @return the speed of the printer
 */
int Printer::getSpeed() const {
    return speed;
}


