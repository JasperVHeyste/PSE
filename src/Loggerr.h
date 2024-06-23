//
// Created by 32488 on 23/06/2024.
//

#ifndef PSE_LOGGERR_H
#define PSE_LOGGERR_H
#include "PrintingSystem.h"
#include <iostream>

class Loggerr {
public:
    void logBWPprinter2(Job* currentjob, BWprinter* p, ostream& outputstream);
    void logColorprinter(Job* currentjob, Colorprinter* p, ostream& outputstream);
    void logScanner(Job* currentjob, Scanner* s, ostream& outputstream);
};


#endif //PSE_LOGGERR_H
