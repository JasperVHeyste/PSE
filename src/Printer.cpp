#include "Printer.h"
#include <chrono>
#include <thread>
#include "Job.h"
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
