#include "Printer.h"
#include <chrono>
#include <thread>
#include "Job.h"
#include <iostream>

using namespace std;
Printer::Printer(std::string n, int e, int s)  : name(n), emission(e), speed(s), ready(true) {
    initcheck = this;
}

bool Printer::properlyInitialized() {
    return initcheck == this;
}

bool Printer::work() {
    int pagina = job->getPagecount();
    for (int i = 0; i <= pagina; i++) {
        //std::cout << "Page printed: " << i << std::endl;
    }
    std::cout << "Printer " << "'" << name << "'" << " finished job:" << "\n    Number: "
         << job->getJobnumber() << "\n    Submitted by '" <<
         job->getUsername() << "'" << endl << "    " << job->getPagecount() << " pages" << endl;
    ready = true;
    job = nullptr;
    return true;
}

bool Printer::isReady() const {
    return ready;
}

const std::string &Printer::getName() const {
    return name;
}

int Printer::getEmission() const {
    return emission;
}

const std::string &Printer::getUsername() const {
    return job->getUsername();
}

int Printer::getJobnumber() const {
    return job->getJobnumber();
}

int Printer::getPagecount() const {
    return job->getPagecount();
}

void Printer::setJob(Job *j) {
    Printer::job = j;
    ready = false;
}

Job *Printer::getJob() const {
    return job;
}


