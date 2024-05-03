#include "Device.h"
#include <chrono>
#include <thread>
#include "Job.h"
#include <iostream>

using namespace std;
/**
 * Constructor for a device
 * @param n name of the device
 * @param e emissions the device emits (gram of C02 per page)
 * @param s speed of the device (pages per minute)
 * @param t type of the device
 * @param c cost of device (eurocent per page)
 */
Device::Device(std::string n, int e, int s, int c)  : name(n), emission(e), speed(s), cost(c) {
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");
}

/**
 * Check if the device is properly inialized by checking if the pointer assigned in the constructor points to itself
 * @return true if properly initialzed, false if not
 */
bool Device::properlyInitialized() const {
    return initcheck == this;
}

/**
 * Assign a job to the device
 * @param j the job that needs to be assigned to this device
 */
void Device::setJob(Job *j) {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    REQUIRE(j->properlyInitialized(), "Job is not properly initialized");
    jobs.push(j);
    ENSURE(hasJob(), "Device does not have a job assigned to it");
}

/**
 * If this device has a job assigned to it, process that job
 * @param outputstream the outputstream where any messages about the progress are sent
 * @return true if the device had a job, false if not
 */
bool Device::work(ostream& outputstream) {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return false;
}

/**
 * @return true if the device has a job, false if not
 */
bool Device::hasJob() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return not jobs.empty();
}

/**
 * @return the name of the device
 */
const std::string &Device::getName() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return name;
}

/**
 * @return the emissions of the device
 */
int Device::getEmission() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return emission;
}

/**
 * @return the username of the person using the device
 */
const std::string &Device::getUsername() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    REQUIRE(hasJob(), "Device does not have a job assigned to it");
    return jobs.front()->getUsername();
}

/**
 * @return the jobnumber of the job the device has assigned to it
 */
int Device::getJobnumber() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    REQUIRE(hasJob(), "Device does not have a job assigned to it");
    return jobs.front()->getJobnumber();
}

/**
 * @return the pagecount of the job the device has assigned to it
 */
int Device::getPagecount() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    REQUIRE(hasJob(), "Device does not have a job assigned to it");
    return jobs.front()->getPagecount();
}

/**
 * @return the amount it costs to use this device
 */
int Device::getCost() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return cost;
}

/**
 * @return the job the device has assigned to it
 */
Job *Device::getJob() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    REQUIRE(hasJob(), "Device does not have a job assigned to it");
    return jobs.front();
}

/**
 * @return the emissions the device emits during the job it handles currently
 */
int Device::getJobEmissions() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    REQUIRE(hasJob(), "Device does not have a job assigned to it");
    return emission*getPagecount();
}

/**
 * @return the amount of jobs left in the queue of the device
 */
int Device::getJobAmount() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return jobs.size();
}

/**
 * @return the queue with jobs
 */
const queue<Job*>& Device::getJobs() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return jobs;
}

/**
 * @return the speed of the device
 */
int Device::getSpeed() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return speed;
}

string Device::getType() const {
    REQUIRE(properlyInitialized(), "Device is not properly initialized");
    return "Printer has no type";
}


