#include <iostream>
#include <fstream>
#include "PrintingSystem.h"
#include <string>

#include "ContractManager.h"

/**
 * Constructor for the printing system
 */
PrintingSystem::PrintingSystem(){
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");
}

/**
 * Check if the printingsystem is properly inialized by checking if the pointer assigned in the constructor points to itself
 * @return true if properly initialzed, false if not
 */
bool PrintingSystem::properlyInitialized() const{
    return initcheck == this;
}

/**
 * Create a new printer and put it in the vector with printers
 * @param name name of the printer
 * @param emissions emissions the printer emits (gram of C02 per page)
 * @param speed speed of the printer (pages per minute)
 * @param type type of the printer
 * @param cost cost of printing (eurocent per page)
 */
void PrintingSystem::createDevice(string name, int emissions, int speed, string type, int cost){
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    if (type == "bw"){
        Device* newDevice = new BWprinter(name, emissions, speed, cost);
        bwprinters.push_back(newDevice);
        ENSURE(newDevice->properlyInitialized(), "Device must be properly initialized");
        devices.push_back(newDevice);
    }
    else if (type == "color"){
        Device* newDevice = new Colorprinter(name, emissions, speed, cost);
        colorprinters.push_back(newDevice);
        ENSURE(newDevice->properlyInitialized(), "Device must be properly initialized");
        devices.push_back(newDevice);
    }
    else if (type == "scan"){
        Device* newDevice = new Scanner(name, emissions, speed, cost);
        scanners.push_back(newDevice);
        ENSURE(newDevice->properlyInitialized(), "Device must be properly initialized");
        devices.push_back(newDevice);
    }
}

/**
 * Create a new job and put it in the queue with jobs
 * @param jobnumber jobnumber
 * @param pagecount page count
 * @param username username
 * @param type type of job
 * @param compnumber the number of the CO2-compensation for this job
 */
void PrintingSystem::createJob(int jobnumber, int pagecount, string username, string type, int compnumber){
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    Job* newJob = new Job(jobnumber, pagecount, username, type);
    if (compensationmap.count(compnumber)){
        newJob->setCompensation(compensationmap[compnumber]);
    }
    ENSURE(newJob->properlyInitialized(), "Job must be properly initialized");
    jobs.enqueue(newJob);
}

/**
 * Create a new compensation in the compensation map
 * @param compnumber number of the compensation
 * @param name name of the compensation
 */
void PrintingSystem::createCompensation(int compnumber, std::string name) {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    int amountofcompensationsbefore = compensationmap.size();
    compensationmap[compnumber] = name;
    int amountofcompensationsafter = compensationmap.size();
    ENSURE(amountofcompensationsafter > amountofcompensationsbefore, "Compensation has not been successfully added");
}

/**
 * Assign one job from the queue to an available matching printer from the vector
 */
void PrintingSystem::assignSingleJob() {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    if (devices.size() == 0) {
        cout << "No printers to assign job\n";
    }
    bool assigned = false;
    if (!jobs.isEmpty()) {
        Job* job = jobs.getJob(0);
        for (auto p: devices) {
            if (p->getType() == job->getType()) {
                jobs.dequeue();
                p->setJob(job);
                assigned = true;
                break;
            }
        }
        if (not assigned){
            cout << "No printers available for job type: " << job->getType() << endl;
        }
    }
    else {
        cout << "All jobs ready" << endl;
    }
}

/**
 * Assign one job from the queue to an available matching printer from the vector
 */
void PrintingSystem::assignAllJobs(std::ostream& outputstream) {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    if (devices.size() == 0) {
        outputstream << "No printers to assign job" << endl;
    }
    if (isQueueEmpty()){
        outputstream << "All jobs ready" << endl;
    }

    while (not isQueueEmpty()) {
        Job *job = jobs.getJob(0);
        string jobType = job->getType();
        if (jobType == "scan" && scanners.size() != 0) {
            Device *minPagesPrinter = scanners[0];
            for (vector<Device *>::iterator scanit = scanners.begin(); scanit != scanners.end(); scanit++) {
                if ((*scanit)->getJobAmount() < minPagesPrinter->getJobAmount()) {
                    minPagesPrinter = *scanit;
                }
            }
            minPagesPrinter->setJob(job);
            jobs.dequeue();
        }
        else if (jobType == "bw" && bwprinters.size() != 0) {
            Device *minPagesPrinter = bwprinters[0];
            for (vector<Device *>::iterator bwit = bwprinters.begin(); bwit != bwprinters.end(); bwit++) {
                if ((*bwit)->getJobAmount() < minPagesPrinter->getJobAmount()) {
                    minPagesPrinter = *bwit;
                }
            }
            minPagesPrinter->setJob(job);
            jobs.dequeue();
        }
        else if (jobType == "color" && colorprinters.size() != 0) {
            Device* minPagesPrinter = colorprinters[0];
            for (vector<Device *>::iterator colorit = colorprinters.begin(); colorit != colorprinters.end(); colorit++) {
                if ((*colorit)->getJobAmount() < minPagesPrinter->getJobAmount()) {
                    minPagesPrinter = *colorit;
                }
            }
            minPagesPrinter->setJob(job);
            jobs.dequeue();
        }
        else {
            outputstream << "No printers available for job type: " << jobType << endl;
            jobs.dequeue();
        }
    }

    ENSURE(isQueueEmpty(), "There are still jobs left in the queue while all should have been assigned");
}

/**
 * Let the printers that have jobs assigned to them process those jobs
 * @param outputstream
 */
void PrintingSystem::proccesJob(std::ostream& outputstream, Device* printer) {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    if (printer != nullptr) {
        if (!printer->hasJob()) {
            totalemissions += printer->getJobEmissions();
            printer->work(outputstream);
        }
    }
    else {
        for (auto p: devices) {
            if (p->hasJob()) {
                totalemissions += p->getJobEmissions();
                p->work(outputstream);
            }
        }
    }
}

/**
 * Automatically let jobs be assigned and processed until the queue with jobs is empty
 * @param outputstream
 */
void PrintingSystem::automatedJob(std::ostream& outputstream) {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    assignAllJobs(outputstream);

    bool jobsleft = true;

    while (jobsleft){
        jobsleft = false;
        for (vector<Device*>::iterator it = devices.begin(); it != devices.end(); it++){
            if ((*it)->hasJob()){
                totalemissions += (*it)->getJobEmissions();
                (*it)->work(outputstream);
                if ((*it)->hasJob()){
                    jobsleft = true;
                }
            }
        }
    }
}

/**
 * Check if the queue with jobs is empty
 * @return true if the queue with jobs is empty, false if not
 */
bool PrintingSystem::isQueueEmpty() {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    return jobs.isEmpty();
}

/**
 * @return the total amount of CO2 emissions after all jobs are finished
 */
int PrintingSystem::getEmissions() {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    return totalemissions;
}

/**
 * @return the index of the current simple report
 */
int PrintingSystem::getReportIndex() const {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    return reportIndex;
}

/**
 * @return the index of the current advanced report
 */
int PrintingSystem::getAdvancedreportIndex() const {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    return advancedreportIndex;
}

/**
 * Set the simple report index
 * @param index the index it will be set to
 */
void PrintingSystem::setReportIndex(int index) {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    PrintingSystem::reportIndex = index;
}

/**
 * Set the advanced report index
 * @param index the index it will be set to
 */
void PrintingSystem::setAdvancedreportIndex(int index) {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    PrintingSystem::advancedreportIndex = index;
}

/**
 * @return the printers in the system
 */
const vector<Device *> &PrintingSystem::getDevices() const {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    return devices;
}

/**
 * @return the compensations in the system
 */
const map<int, std::string> &PrintingSystem::getCompensationmap() const {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    return compensationmap;
}
