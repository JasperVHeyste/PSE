#ifndef UNTITLED_PRINTER_H
#define UNTITLED_PRINTER_H
#include <string>
#include <iostream>
class Job;
class Printer {
private:
    std::string name;
    int emission;
    int speed; // pages per minute
    std::string username;
    int jobnumber;
    int pagecount;
    bool ready;
public:
    Printer(std::string n, int e, int s) : name(n), emission(e), speed(s), ready(true) {};

    bool work(Job *job);

    bool isReady() const;

    const std::string &getName() const;
};


#endif //UNTITLED_PRINTER_H
