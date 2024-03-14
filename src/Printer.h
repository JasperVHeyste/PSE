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
    //int pagecount;
    bool ready = true;
    Printer* initcheck;
    Job* job = nullptr;
public:
    Printer(std::string n, int e, int s);

    bool properlyInitialized();

    bool work();


    bool isReady() const;

    const std::string &getName() const;

    int getEmission() const;

    const std::string &getUsername() const;

    int getJobnumber() const;

    int getPagecount() const;

    void setJob(Job *job);

    Job *getJob() const;
};


#endif //UNTITLED_PRINTER_H
