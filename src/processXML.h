#ifndef PROJECT_PROCESSXML_H
#define PROJECT_PROCESSXML_H

class Printer;
class Job;

class processXML {
public:
    Printer* createPrinter();
    Job* createJob();
    bool readXML();
};


#endif //PROJECT_PROCESSXML_H
