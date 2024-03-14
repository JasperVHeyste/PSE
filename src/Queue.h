#ifndef UNTITLED_QUEUE_H
#define UNTITLED_QUEUE_H
#include "QueueNode.h"
#include "Job.h"

class Queue {
private:
    int size = 0;
    QueueNode* head = nullptr;
    QueueNode* tail = nullptr;
    Queue* initcheck;

public:
    Queue();
    //ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");

    bool properlyInitialized() const;

    bool isEmpty();
    //REQUIRE(properlyInitialized(), "Queue is not properly initialized")

    bool enqueue(Job* p);
    //REQUIRE(properlyInitialized(), "Queue is not properly initialized")

    Job* dequeue();
    //REQUIRE(properlyInitialized(), "Queue is not properly initialized")
    //REQUIRE(!isEmpty(), "Queue is empty");

    QueueNode* getHead();
    //REQUIRE(properlyInitialized(), "Queue is not properly initialized")

    int getSize() const;
    //REQUIRE(properlyInitialized(), "Queue is not properly initialized")

    Job* getJob(int index);
    //REQUIRE(properlyInitialized(), "Queue is not properly initialized")
    //REQUIRE(index < size, "Queue does not have an item with the given index");

    virtual ~Queue();

};


#endif //UNTITLED_QUEUE_H
