#include <iostream>

#include "PrintingSystem.h"

PrintingSystem::~PrintingSystem() {

}

void PrintingSystem::createPrinter(string name, int emissions, int speed){
    Printer* newPrinter = new Printer(name, emissions, speed);
    printers.push_back(newPrinter);
}

void PrintingSystem::createJob(int jobnumber, int pagecount, string username){
    Job* newJob = new Job(jobnumber, pagecount, username);
    jobs.enqueue(newJob);
}

void PrintingSystem::implementXML(const char* file) {
    vector<map<string,string>> input = readXML(file);

    for (unsigned int i = 0; i < input.size(); i++){
        map<string, string> object = input[i];

        if (object["type"] == "device"){
            string name = object["name"];
            int emissions = stoi(object["emissions"]);
            int speed = stoi(object["speed"]);

            createPrinter(name, emissions, speed);
            cout << "created printer with name " << name << endl;
        }

        if (object["type"] == "job"){
            int jobnumber = stoi(object["jobnumber"]);
            int pagecount = stoi(object["pagecount"]);
            string username = object["username"];

            createJob(jobnumber, pagecount, username);
            cout << "created job with jobnumber " << jobnumber << endl;
        }
    }
}