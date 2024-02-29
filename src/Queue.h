#ifndef UNTITLED_QUEUE_H
#define UNTITLED_QUEUE_H
#include "QueueNode.h"
#include "Job.h"

class Queue {
public:
    int size = 0;
    QueueNode* head = nullptr;
    QueueNode* tail = nullptr;

    bool isEmpty();
    bool enqueue(Job* p);
    Job* dequeue();

    virtual ~Queue();

};


#endif //UNTITLED_QUEUE_H
