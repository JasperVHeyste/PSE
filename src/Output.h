#ifndef PSE_MAIN_OUTPUT_H
#define PSE_MAIN_OUTPUT_H
#include "PrintingSystem.h"

class Output {
private:
    Output* initcheck;
public:
    Output();
    //ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");

    bool properlyInitialized();

    void simpleOutput(PrintingSystem* system);
    //REQUIRE(properlyInitialized(), "Output is not properly initialized");
    void advancedOutput(PrintingSystem* system);
    //REQUIRE(properlyInitialized(), "Output is not properly initialized");
};


#endif //PSE_MAIN_OUTPUT_H
