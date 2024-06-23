//
// Created by 32488 on 23/06/2024.
//

#include "Loggerr.h"

void Loggerr::logBWPprinter2(Job *currentjob, BWprinter *p, ostream &outputstream) {
    outputstream << "Printer " << "'" << p->getName() << "'" << " finished black-and-white job:" << "\n    Number: "
                 << currentjob->getJobnumber() << "\n    Submitted by '" <<
                 currentjob->getUsername() << "'" << endl << "    " << currentjob->getPagecount() << " pages" << endl;
    if (currentjob->hasCompensation()){
        outputstream << "Job " << currentjob->getJobnumber() << " was made CO2 neutral with the support of " << currentjob->getCompensation() << "." << endl;
    }
}

void Loggerr::logColorprinter(Job *currentjob, Colorprinter *p, ostream &outputstream) {
    outputstream << "Printer " << "'" << p->getName() << "'" << " finished color-printing job:" << "\n    Number: "
                 << currentjob->getJobnumber() << "\n    Submitted by '" <<
                 currentjob->getUsername() << "'" << endl << "    " << currentjob->getPagecount() << " pages" << endl;
    if (currentjob->hasCompensation()){
        outputstream << "Job " << currentjob->getJobnumber() << " was made CO2 neutral with the support of " << currentjob->getCompensation() << "." << endl;
    }
}

void Loggerr::logScanner(Job *currentjob, Scanner *s, ostream &outputstream) {
    outputstream << "Printer " << "'" << s->getName() << "'" << " finished scanning job:" << "\n    Number: "
                 << currentjob->getJobnumber() << "\n    Submitted by '" <<
                 currentjob->getUsername() << "'" << endl << "    " << currentjob->getPagecount() << " pages" << endl;
    if (currentjob->hasCompensation()){
        outputstream << "Job " << currentjob->getJobnumber() << " was made CO2 neutral with the support of " << currentjob->getCompensation() << "." << endl;
    }
}
