#ifndef UNTITLED_JOB_H
#define UNTITLED_JOB_H

#include <string>

class Job {
private:
    int jobnumber;
    int pagecount;
    std::string username;
public:
    Job(int jn, int pc, std::string un) : jobnumber(jn), pagecount(pc), username(un) {};
};


#endif //UNTITLED_JOB_H
