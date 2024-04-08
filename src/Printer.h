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
    std::string type;
    int cost;

    bool ready = true;
    Job* job = nullptr;
    Printer* initcheck;
public:
    Printer(std::string n, int e, int s, std::string t = "unspecified", int c = -1); //if cost is -1 it means cost should be ignored
    //ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");

    bool properlyInitialized() const;

    void setJob(Job* j);
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    //REQUIRE(j->properlyInitialized(), "Job is not properly initialized");

    bool work(std::ostream& outputstream = std::cout);
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");
    //ENSURE(isReady(), "Printer must be ready after work is done");
    //ENSURE(not hasJob(), "Printer cannot have an assigned job after work is done");

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

    int getJobnumber() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    int getPagecount() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    int getCost() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    std::string getType() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");

    Job *getJob() const;
    //REQUIRE(properlyInitialized(), "Printer is not properly initialized");
};


#endif //UNTITLED_PRINTER_H
