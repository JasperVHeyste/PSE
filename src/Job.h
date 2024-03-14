#ifndef UNTITLED_JOB_H
#define UNTITLED_JOB_H

#include <string>

class Job {
private:
    int jobnumber;
    int pagecount;
    std::string username;
    Job* initcheck;

public:
    Job(int jn, int pc, std::string un);

    bool properlyInitialized();

    int getPagecount() const {
        return pagecount;
    }

    int getJobnumber() const {
        return jobnumber;
    }

    const std::string &getUsername() const {
        return username;
    }
};


#endif //UNTITLED_JOB_H
