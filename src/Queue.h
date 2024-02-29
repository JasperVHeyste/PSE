#ifndef UNTITLED_QUEUE_H
#define UNTITLED_QUEUE_H
#include "Node.h"
#include "Job.h"

class Queue {
public:
    int size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

    bool isEmpty();
    bool enqueue(Job* p);
    Job* dequeue();

    virtual ~Queue();

};


#endif //UNTITLED_QUEUE_H
