#include "Printer.h"
#include <chrono>
#include <thread>
#include "Job.h"
#include <iostream>

using namespace std;
Printer::Printer(std::string n, int e, int s)  : name(n), emission(e), speed(s), ready(true) {
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");
}

bool Printer::properlyInitialized() const {
    return initcheck == this;
}

void Printer::setJob(Job *j) {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    REQUIRE(j->properlyInitialized(), "Job is not properly initialized");
    Printer::job = j;
    ready = false;
}

bool Printer::work() {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    /*for (int i = 0; i <= job->getPagecount(); i++) {
        std::cout << "Page printed: " << i << std::endl;
    }*/
    std::cout << "Printer " << "'" << name << "'" << " finished job:" << "\n    Number: "
         << job->getJobnumber() << "\n    Submitted by '" <<
         job->getUsername() << "'" << endl << "    " << job->getPagecount() << " pages" << endl;
    ready = true;
    job = nullptr;
    ENSURE(isReady(), "Printer must be ready after work is done");
    ENSURE(getJob() == nullptr, "Printer cannot have an assigned job after work is done");
    return true;
}

bool Printer::isReady() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return ready;
}

const std::string &Printer::getName() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return name;
}

int Printer::getEmission() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return emission;
}

const std::string &Printer::getUsername() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return job->getUsername();
}

int Printer::getJobnumber() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return job->getJobnumber();
}

int Printer::getPagecount() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return job->getPagecount();
}

Job *Printer::getJob() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return job;
}



