#ifndef UNTITLED_PRINTER_H
#define UNTITLED_PRINTER_H
#include <string>
#include <iostream>
#include <queue>

class Job;
class Device {
protected:
    std::string name;
    int emission;
    int speed; // pages per minute
    int cost;
    std::queue<Job*> jobs;
    Device* initcheck;

public:
    Device(std::string n, int e, int s, int c = -1); //if cost is -1 it means cost should be ignored
    //ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");

    ~Device() {};

    bool properlyInitialized() const;

    void setJob(Job* j);
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
    //REQUIRE(j->properlyInitialized(), "Job is not properly initialized");
    //ENSURE(hasJob(), "Device does not have a job assigned to it");

    virtual bool work(std::ostream& outputstream = std::cout);
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
    //ENSURE(getJobAmount() < jobsbeforework, "Job has not successfully been processed");

    bool hasJob() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");

    const std::string& getName() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");

    int getEmission() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");

    const std::string& getUsername() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
    //REQUIRE(hasJob(), "Device does not have a job assigned to it");

    int getJobnumber() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
    //REQUIRE(hasJob(), "Device does not have a job assigned to it");

    int getPagecount() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
    //REQUIRE(hasJob(), "Device does not have a job assigned to it");

    int getCost() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");

    virtual std::string getType() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");

    Job* getJob() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
    //REQUIRE(hasJob(), "Device does not have a job assigned to it");

    int getJobEmissions() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
    //REQUIRE(hasJob(), "Device does not have a job assigned to it");

    int getJobAmount() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");

    const std::queue<Job *>& getJobs() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");

    int getSpeed() const;
    //REQUIRE(properlyInitialized(), "Device is not properly initialized");
};


#endif
