#include "Printer.h"
#include <chrono>
#include <thread>
#include "Job.h"

Printer::Printer(std::string n, int e, int s)  : name(n), emission(e), speed(s), ready(true) {
    initcheck = this;
}

bool Printer::properlyInitialized() {
    return initcheck == this;
}

bool Printer::work(Job *job) {
    ready = false;
    double printingTime = job->getPagecount() / speed;
    std::this_thread::sleep_for(std::chrono::minutes(static_cast<int>(printingTime)));
    ready = true;

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
    return username;
}

int Printer::getJobnumber() const {
    return jobnumber;
}

int Printer::getPagecount() const {
    return pagecount;
}
