#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H
#include <string>
#include "Job.h"
using namespace std;


class QueueNode {
private:
    QueueNode* initcheck;
public:
    Job* item;
    QueueNode* next = nullptr;
    QueueNode* prev = nullptr;

    explicit QueueNode(Job *item);
    //ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");

    bool properlyInitialized() const;
};


#endif //UNTITLED_NODE_H
