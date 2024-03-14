#include "Queue.h"
#include <iostream>

Queue::Queue(){
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");
}

Queue::~Queue() {}

bool Queue::properlyInitialized() const {
    return initcheck == this;
}

bool Queue::isEmpty() {
    REQUIRE(properlyInitialized(), "Queue is not properly initialized");
    if (this->size == 0){
        return true;
    }
    return false;
}

bool Queue::enqueue(Job* p) {
    REQUIRE(properlyInitialized(), "Queue is not properly initialized");
    QueueNode* newNode = new QueueNode(p);
    if (this->size == 0){
        this->head = newNode;
        this->tail = newNode;
        this->size++;
        return true;
    }else {
        this->tail->next = newNode;
        this->tail = newNode;
        this->size++;
        return true;
    }
}

Job* Queue::dequeue() {
    REQUIRE(properlyInitialized(), "Queue is not properly initialized");
    REQUIRE(!isEmpty(), "Queue is empty");
    QueueNode* headNode = this->head;
    if (this->size == 1) {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        return headNode->item;
    }
    else{
        this->head = headNode->next;
        this->head->prev = nullptr;
    }
    Job* j = headNode->item;
    this->size -= 1;
    return j;

}

QueueNode* Queue::getHead(){
    REQUIRE(properlyInitialized(), "Queue is not properly initialized");
    return head;
}

int Queue::getSize() const {
    REQUIRE(properlyInitialized(), "Queue is not properly initialized");
    return size;
}

Job *Queue::getJob(int index) {
    REQUIRE(properlyInitialized(), "Queue is not properly initialized");
    REQUIRE(index < size, "Queue does not have an item with the given index");
    QueueNode* temp = this->head;
    for (int i = 0; i < index; i++){
        temp = temp->next;
    }
    return temp->item;
}
