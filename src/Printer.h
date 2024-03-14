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
    Printer* initcheck;
public:
    Printer(std::string n, int e, int s);

    bool properlyInitialized();

    bool work(Job *job);

    bool isReady() const;

    const std::string &getName() const;

    int getEmission() const;

    const std::string &getUsername() const;

    int getJobnumber() const;

    int getPagecount() const;
};


#endif //UNTITLED_PRINTER_H
