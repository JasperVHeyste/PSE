#include <iostream>
#include <fstream>
#include "PrintingSystem.h"
#include <string>

//#include "DesignByContract.h"
#include "DesignByContract_windows.h"

PrintingSystem::PrintingSystem(){
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");
}

bool PrintingSystem::properlyInitialized() {
    return initcheck == this;
}


PrintingSystem::~PrintingSystem() {

}

void PrintingSystem::createPrinter(string name, int emissions, int speed){
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    Printer* newPrinter = new Printer(name, emissions, speed);
    ENSURE(newPrinter->properlyInitialized(), "Printer must be properly initialized");
    printers.push_back(newPrinter);
}

void PrintingSystem::createJob(int jobnumber, int pagecount, string username){
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    Job* newJob = new Job(jobnumber, pagecount, username);
    ENSURE(newJob->properlyInitialized(), "Job must be properly initialized");
    jobs.enqueue(newJob);
}

void PrintingSystem::implementXML(const char* filename, XMLprocessor& xmlp) {
    string fname = filename;
    string ftype;
    for (unsigned int i = fname.length()-4; i < fname.length(); i++){
        ftype += fname[i];
    }
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    REQUIRE(properlyInitialized(), "XMLprocessor is not properly initialized");
    REQUIRE(ftype == ".xml", "Inputfile has to be an xml file");

    vector<map<string,string>> input = xmlp.readXML(filename);

    for (unsigned int i = 0; i < input.size(); i++){
        map<string, string> object = input[i];

        if (object["type"] == "device"){
            string name = object["name"];
            int emissions = stoi(object["emissions"]);
            int speed = stoi(object["speed"]);

            createPrinter(name, emissions, speed);
            //cout << "created printer with name " << name << endl;
        }

        if (object["type"] == "job"){
            int jobnumber = stoi(object["jobNumber"]);
            int pagecount = stoi(object["pageCount"]);
            string username = object["userName"];

            createJob(jobnumber, pagecount, username);
            //cout << "created job with jobnumber " << jobnumber << endl;
        }
    }
}
void PrintingSystem::assignJob() {
    if (!jobs.isEmpty()) {
        for (auto p: printers) {
            if (!jobs.isEmpty()) {
                if (p->isReady()) {
                    Job *job = jobs.dequeue();
                    p->setJob(job);
                }
            }

        }
    }
    else {
        cout << "All jobs ready" << endl;
    }
}

void PrintingSystem::proccesJob() {
    for (auto p: printers) {
        if (!p->isReady()) {
            p->work();
        }
    }
}

void PrintingSystem::automatedJob() {
    while(not isQueueEmpty()){
        assignJob();
        proccesJob();
    }
}

void PrintingSystem::simpleOutput() {
    ofstream outputFile("status_report.txt" + to_string(reportIndex));
    reportIndex += 1;
    if (!outputFile.is_open()) {
        cout << "Can not open status_report." << endl;
        return;
    }

    if (printers.empty()){
        cout << "No printers present in Printingsystem" << endl;
    }

    // printers
    for (auto& p: printers){
        outputFile << "NEW-Printer (" << p->getName() << ": " << p->getEmission() << "g/page):\n";

        if (p->isReady()) {
            if (p->getJob() == nullptr) {
                outputFile << "printer has no job\n";
            }
        }
        if (!p->isReady()){
            outputFile << "     * Current:\n";
            outputFile << "[#" << p->getJobnumber() << "|" << p->getUsername() << "]\n";
        }
        // queue
        outputFile << "     * Queue:\n";
        if (jobs.isEmpty()){
            outputFile << "         No current jobs in queue.\n";
        }else{
            QueueNode* temp = jobs.head;
            for (int i = 0; i < jobs.getSize(); i++){
                Job* current = temp->item;
                outputFile << "         [#" << std::to_string(current->getJobnumber()) << "|" << current->getUsername() << "]\n";
                temp = temp->next;
            }
        }
    }


    outputFile.close();

}
