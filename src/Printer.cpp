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
    ready = true;
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
    Printer::job = j;
    ready = false;
}

/**
 * If this printer has a job assigned to it, process that job
 * @param outputstream the outputstream where any messages about the progress are sent
 * @return true if the printer had a job, false if not
 */
bool Printer::work(ostream& outputstream) {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    /*for (int i = 0; i <= job->getPagecount(); i++) {
        std::cout << "Page printed: " << i << std::endl;
    }*/
    if (not hasJob()){
        return false;
    }

    outputstream << "Printer " << "'" << name << "'" << " finished job:" << "\n    Number: "
         << job->getJobnumber() << "\n    Submitted by '" <<
         job->getUsername() << "'" << endl << "    " << job->getPagecount() << " pages" << endl;
    if (job->hasCompensation()){
        outputstream << "Job " << job->getJobnumber() << " was made CO2 neutral with the support of " << job->getCompensation() << "." << endl;
    }
    ready = true;
    job = nullptr;
    ENSURE(isReady(), "Printer must be ready after work is done");
    ENSURE(not hasJob(), "Printer cannot have an assigned job after work is done");
    return true;
}

/**
 * @return ready
 */
bool Printer::isReady() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return ready;
}

/**
 * @return true if the printer has a job, false if not
 */
bool Printer::hasJob() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return job != nullptr;
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
    return job->getUsername();
}

/**
 * @return the jobnumber of the job the printer has assigned to it
 */
int Printer::getJobnumber() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    REQUIRE(hasJob(), "Printer does not have a job assigned to it");
    return job->getJobnumber();
}

/**
 * @return the pagecount of the job the printer has assigned to it
 */
int Printer::getPagecount() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    REQUIRE(hasJob(), "Printer does not have a job assigned to it");
    return job->getPagecount();
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
    return job;
}

int Printer::getJobEmissions() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    REQUIRE(hasJob(), "Printer does not have a job assigned to it");
    return emission*getPagecount();
}



