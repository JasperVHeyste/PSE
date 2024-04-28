//
// Created by Jens on 27/04/2024.
//

#include "Output.h"
#include <fstream>
#include <set>

void Output::simpleOutput(PrintingSystem* system) {
    set<Printer*> allPrinters;
    int index = system->getReportIndex();
    ofstream outputFile("status_report" + to_string(index) + ".txt");
    index += 1;
    system->setReportIndex(index);
    if (!outputFile.is_open()) {
        cout << "Can not open status_report." << endl;
        return;
    }
    outputFile << "# === [System Status] === #\n" << endl;

    // printers
    outputFile << "--== Devices ==--" << endl;
    if (system->getPrinters().empty()){
        outputFile << "No devices present in Printingsystem\n" << endl;
    }else {
        if (system->getPrinters().empty()){
            outputFile << "No printers present in system.\n";
        }else {
            for (auto p: system->getPrinters()) {
                outputFile << p->getName() << ": \n";
                outputFile << "* Type: " << p->getType() << "\n";
                outputFile << "* CO2: " << p->getEmission() << "g/page\n";
                outputFile << "* " << p->getSpeed() << "pages / minute\n";
                outputFile << "* " << p->getCost() << "cents / page\n";
                allPrinters.insert(p);
                outputFile << "\n";
            }
        }
    }
    // jobs
    outputFile << "--== Jobs ==--";
    for (auto p: allPrinters) {
        queue<Job*> jobs = p->getJobs();
        if (!jobs.empty()){
            queue<Job*> jobsCopy = jobs;
            int size = jobsCopy.size();
            int place = 0;
            while (!jobsCopy.empty()) {
                place += 1;
                Job* current = jobsCopy.front();
                jobsCopy.pop();

                outputFile << "\n[Job #" << std::to_string(current->getJobnumber()) << "]\n";
                outputFile << "* Owner: " << current->getUsername() << "\n";
                outputFile << "* Device: " << p->getName() << "\n";
                outputFile << "* Status: " << to_string(place) << "/" << to_string(size) << "\n";
                outputFile << "* Total pages: " << current->getPagecount() << " pages\n";
                int totalC02 = p->getEmission() * current->getPagecount();
                outputFile << "* Total C02: " << to_string(totalC02) << "g C02\n";
                int totalCost = p->getCost() * current->getPagecount();
                outputFile << "* Total cost: " << to_string(totalCost) << "cents\n";
                if (current->hasCompensation()) {
                    outputFile << "* Compensation: " << current->getCompensation() << "\n";
                }
            }
        }else{
            outputFile << "\n" << p->getName() << "Doesnt have any jobs assigned.\n";
        }
    }

    // compensations
    outputFile << "\n--== Co2 Compensation initiatives ==--";
    for (const auto& c : system->getCompensationmap()) {
        outputFile <<"\n";
        outputFile << c.second << " [*" << c.first << "]\n";
    }

    outputFile << "# ======================= #\n";
    outputFile.close();
}

void Output::advancedOutput(PrintingSystem* system) {
    int index = system->getAdvancedreportIndex();
    ofstream outputFile("advanced_status_report" + to_string(index) + ".txt");
    index += 1;
    system->setAdvancedreportIndex(index);
    if (!outputFile.is_open()) {
        cout << "Can not open status_report." << endl;
        return;
    }

    outputFile << "-=Queue=-\n";

    vector<Printer*> printers = system->getPrinters();
    if (printers.empty()){
        outputFile << "No printers present in printingsystem\n";
    }else {
        for (auto p: system->getPrinters()) {
            outputFile << "*" << p->getName() << "\n";
            queue<Job *> jobs = p->getJobs();
            queue<Job *> copyjobs = jobs;
            if (!p->hasJob()){
                outputFile << "Is not processing a job | ";
            }else {
                outputFile <<"[" << p->getJob()->getJobnumber() << "] | ";
            }
            if (copyjobs.empty()){
                outputFile << "No jobs assigned.\n\n";
            }else {
                while (!copyjobs.empty()) {
                    Job* current = copyjobs.front();
                    copyjobs.pop();
                    outputFile << "[" << current->getJobnumber() << "] ";
                }
                outputFile << "\n\n";
            }
        }
    }
    outputFile.close();
}
