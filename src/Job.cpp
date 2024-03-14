#include "Job.h"

Job::Job(int jn, int pc, std::string un) : jobnumber(jn), pagecount(pc), username(un) {
    initcheck = this;
}

bool Job::properlyInitialized() {
    return initcheck == this;
}