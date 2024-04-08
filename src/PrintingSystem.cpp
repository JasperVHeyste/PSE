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


PrintingSystem::~PrintingSystem() {}

void PrintingSystem::createPrinter(string name, int emissions, int speed, string type, int cost){
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    Printer* newPrinter = new Printer(name, emissions, speed, type, cost);
    ENSURE(newPrinter->properlyInitialized(), "Printer must be properly initialized");
    printers.push_back(newPrinter);
}

void PrintingSystem::createJob(int jobnumber, int pagecount, string username, string type){
    REQUIRE(properlyInitialized(), "Printingsystem is not properly initialized");
    Job* newJob = new Job(jobnumber, pagecount, username, type);
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
        string type = "unspecified";

        if (object["objecttype"] == "device"){
            string name = object["name"];
            int cost = -1;
            int emissions = stoi(object["emissions"]);
            int speed = stoi(object["speed"]);

            if (input[i].count("type")){
                type = object["type"];
            }

            createPrinter(name, emissions, speed, type, cost);
            //cout << "created printer with name " << name << endl;
        }

        if (object["objecttype"] == "job"){
            int jobnumber = stoi(object["jobNumber"]);
            int pagecount = stoi(object["pageCount"]);
            string username = object["userName"];

            if (input[i].count("type")){
                type = object["type"];
            }

            createJob(jobnumber, pagecount, username, type);
            //cout << "created job with jobnumber " << jobnumber << endl;
        }
    }
}

void PrintingSystem::assignJob() {
    if (printers.size() == 0) {
        cout << "No printers to assign job\n";
    }
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

void PrintingSystem::proccesJob(std::ostream& outputstream) {
    for (auto p: printers) {
        if (!p->isReady()) {
            p->work(outputstream);
        }
    }
}

void PrintingSystem::automatedJob(std::ostream& outputstream) {
    while(not isQueueEmpty()){
        assignJob();
        proccesJob(outputstream);
    }
}

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

bool PrintingSystem::isQueueEmpty() {
    return jobs.isEmpty();
}
