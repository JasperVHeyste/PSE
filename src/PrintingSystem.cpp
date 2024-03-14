#include <iostream>
#include <fstream>
#include "PrintingSystem.h"
#include <string>

#include "DesignByContract.h"
//#include "DesignByContract_windows.h"

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

void PrintingSystem::manualJob() {
    if (jobs.size != 0) {
        for (auto p : printers) {
            if (p->isReady()) {
                Job *job = jobs.dequeue();
                p->work(job);
                cout << "Printer " << "'" << p->getName() << "'" << " finished job:" << "\n    Number: " << job->getJobnumber() << "\n    Submitted by '" <<
                     job->getUsername() << "'" << endl << "    " <<job->getPagecount() << " pages" << endl;
            }
        }
    }
    else {
        cout << "All jobs ready" << endl;
    }
}

void PrintingSystem::automatedJob() {
    while (!jobs.isEmpty()) {
        for (auto p : printers) {
            if (p->isReady()) {
                Job *job = jobs.dequeue();
                p->work(job);
                cout << "Printer " << "'" << p->getName() << "'" << " finished job:" << "\n    Number: " << job->getJobnumber() << "\n    Submitted by '" <<
                     job->getUsername() << "'" << endl << "    " <<job->getPagecount() << " pages" << endl;
            }
        }
    }

}

void PrintingSystem::simpleOutput() {
    ofstream outputFile("status_report.txt");
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
            outputFile << "* Current:\n";
            outputFile << "[#" << std::to_string(p->getJobnumber()) << "|" << p->getUsername() << "]\n";
        }
        if (!p->isReady()){
            outputFile << "Not ready.\n";
        }
    }

    // queue
    outputFile << "Queue:\n";
    if (jobs.isEmpty()){
        outputFile << "No current jobs in queue.";
    }else{
        QueueNode* temp = jobs.head;
        for (int i = 0; i < jobs.getSize(); i++){
            Job* current = temp->item;
            outputFile << "[#" << std::to_string(current->getJobnumber()) << "|" << current->getUsername() << "]\n";
            temp = temp->next;
        }
    }
    outputFile.close();

}
