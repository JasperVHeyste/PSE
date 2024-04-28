#ifndef UNTITLED_PRINTER_H
#define UNTITLED_PRINTER_H
#include <string>
#include <iostream>
#include <queue>

class Job;
class Printer {
private:
public:
    int getSpeed() const;

private:
    std::string name;
    int emission;
    int speed; // pages per minute
    std::string type;
    int cost;
    std::queue<Job*> jobs;
    Printer* initcheck;

public:
    Printer(std::string n, int e, int s, std::string t = "unspecified", int c = -1); //if cost is -1 it means cost should be ignored
    //ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");

    ~Printer() {};

    bool properlyInitialized() const;

    void setJob(Job* j);
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    //REQUIRE(j->properlyInitialized(), "Job is not properly initialized");

    bool work(std::ostream& outputstream = std::cout);
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    bool isReady() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    bool hasJob() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    const std::string &getName() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    int getEmission() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    const std::string &getUsername() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    //REQUIRE(hasJob(), "Printer does not have a job assigned to it");

    int getJobnumber() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    //REQUIRE(hasJob(), "Printer does not have a job assigned to it");

    int getPagecount() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    //REQUIRE(hasJob(), "Printer does not have a job assigned to it");

    int getCost() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    std::string getType() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    Job *getJob() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    int getJobEmissions() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    //REQUIRE(hasJob(), "Printer does not have a job assigned to it");

    int getJobAmount() const;

    const std::queue<Job *> &getJobs() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");
};


#endif //UNTITLED_PRINTER_H
