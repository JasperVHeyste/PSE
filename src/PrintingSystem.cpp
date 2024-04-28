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
bool PrintingSystem::properlyInitialized() {
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
void PrintingSystem::createPrinter(string name, int emissions, int speed, string type, int cost){
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    Printer* newPrinter = new Printer(name, emissions, speed, type, cost);
    ENSURE(newPrinter->properlyInitialized(), "Printer must be properly initialized");
    printers.push_back(newPrinter);
    if (type == "bw"){
        bwprinters.push_back(newPrinter);
    }
    else if (type == "color"){
        colorprinters.push_back(newPrinter);
    }
    else if (type == "scan"){
        scanners.push_back(newPrinter);
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
    compensationmap[compnumber] = name;
}

/**
 * Assign one job from the queue to an available matching printer from the vector
 */
void PrintingSystem::assignSingleJob() {
    if (printers.size() == 0) {
        cout << "No printers to assign job\n";
    }
    bool assigned = false;
    if (!jobs.isEmpty()) {
        Job* job = jobs.getJob(0);
        for (auto p: printers) {
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
    if (printers.size() == 0) {
        outputstream << "No printers to assign job" << endl;
    }
    if (isQueueEmpty()){
        outputstream << "All jobs ready" << endl;
    }

    while (not isQueueEmpty()) {
        Job *job = jobs.getJob(0);
        string jobType = job->getType();
        if (jobType == "scan" && scanners.size() != 0) {
            Printer *minPagesPrinter = scanners[0];
            for (vector<Printer *>::iterator scanit = scanners.begin(); scanit != scanners.end(); scanit++) {
                if ((*scanit)->getJobAmount() < minPagesPrinter->getJobAmount()) {
                    minPagesPrinter = *scanit;
                }
            }
            minPagesPrinter->setJob(job);
            jobs.dequeue();
        }
        else if (jobType == "bw" && bwprinters.size() != 0) {
            Printer *minPagesPrinter = bwprinters[0];
            for (vector<Printer *>::iterator bwit = bwprinters.begin(); bwit != bwprinters.end(); bwit++) {
                if ((*bwit)->getJobAmount() < minPagesPrinter->getJobAmount()) {
                    minPagesPrinter = *bwit;
                }
            }
            minPagesPrinter->setJob(job);
            jobs.dequeue();
        }
        else if (jobType == "color" && colorprinters.size() != 0) {
            Printer* minPagesPrinter = colorprinters[0];
            for (vector<Printer *>::iterator colorit = colorprinters.begin(); colorit != colorprinters.end(); colorit++) {
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
}

/**
 * Let the printers that have jobs assigned to them process those jobs
 * @param outputstream
 */
void PrintingSystem::proccesJob(std::ostream& outputstream, Printer* printer) {
    if (printer != nullptr) {
        if (!printer->hasJob()) {
            totalemissions += printer->getJobEmissions();
            printer->work(outputstream);
        }
    }
    else {
        for (auto p: printers) {
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
    assignAllJobs(outputstream);

    bool jobsleft = true;

    while (jobsleft){
        jobsleft = false;
        for (vector<Printer*>::iterator it = printers.begin(); it != printers.end(); it++){
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
 * Write a status report to a textfile
 */
void PrintingSystem::simpleOutput() {
    ofstream outputFile("status_report" + to_string(reportIndex) + ".txt");
    reportIndex += 1;
    if (!outputFile.is_open()) {
        cout << "Can not open status_report." << endl;
        return;
    }

    if (printers.empty()){
        outputFile << "No printers present in Printingsystem\n" << endl;
    }

    // printers
    for (auto& p: printers){
        outputFile << "NEW-Printer (" << p->getName() << ": " << p->getEmission() << "g/page):\n";


        if (p->hasJob()){
            outputFile << "     * Current:\n";
            outputFile << "[#" << p->getJobnumber() << "|" << p->getUsername() << "]\n";
        }
        else {
            outputFile << "printer has no job\n";
        }
        // queue
        outputFile << "     * Queue:\n";
        if (jobs.isEmpty()){
            outputFile << "         No current jobs in queue.\n";
        }else{
            QueueNode* temp = jobs.getHead();
            for (int i = 0; i < jobs.getSize(); i++){
                Job* current = temp->item;
                outputFile << "         [#" << std::to_string(current->getJobnumber()) << "|" << current->getUsername() << "]\n";
                temp = temp->next;
            }
        }
    }

    outputFile.close();
}

/**
 * Check if the queue with jobs is empty
 * @return true if the queue with jobs is empty, false if not
 */
bool PrintingSystem::isQueueEmpty() {
    return jobs.isEmpty();
}

/**
 * @return the total amount of CO2 emissions after all jobs are finished
 */
int PrintingSystem::getEmissions() {
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    return totalemissions;
}
