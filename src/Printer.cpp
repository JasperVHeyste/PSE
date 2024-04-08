#include "Printer.h"
#include <chrono>
#include <thread>
#include "Job.h"
#include <iostream>

using namespace std;
Printer::Printer(std::string n, int e, int s, std::string t, int c)  : name(n), emission(e), speed(s), type(t), cost(c) {
    ready = true;
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

bool Printer::work(ostream& outputstream) {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    /*for (int i = 0; i <= job->getPagecount(); i++) {
        std::cout << "Page printed: " << i << std::endl;
    }*/
    outputstream << "Printer " << "'" << name << "'" << " finished job:" << "\n    Number: "
         << job->getJobnumber() << "\n    Submitted by '" <<
         job->getUsername() << "'" << endl << "    " << job->getPagecount() << " pages" << endl;
    ready = true;
    job = nullptr;
    ENSURE(isReady(), "Printer must be ready after work is done");
    ENSURE(not hasJob(), "Printer cannot have an assigned job after work is done");
    return true;
}

bool Printer::isReady() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return ready;
}

bool Printer::hasJob() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return job != nullptr;
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

int Printer::getCost() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return cost;
}

std::string Printer::getType() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return type;
}

Job *Printer::getJob() const {
    REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    return job;
}



