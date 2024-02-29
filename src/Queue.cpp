#include "Queue.h"
#include <iostream>


bool Queue::isEmpty() {
    if (this->size ==0){
        return true;
    }else{
        return false;
    }
}

bool Queue::enqueue(Job* p) {
    QueueNode* newNode = new QueueNode(p);
    if (this->size == 0){
        this->head = newNode;
        this->tail = newNode;
        this->size += 1;
        return true;
    }else {
        this->tail->next = newNode;
        this->tail = newNode;
        this->size += 1;
        return true;
    }
}

Job* Queue::dequeue() {
    QueueNode* headNode = this->head;
    if (this->isEmpty()){
        cout << "error, queue is empty";
        return nullptr;
    }else if (this->size == 1){
        this->head = nullptr;
        this->tail = nullptr;
        this->size -= 1;
        return headNode->item;
    }else{
        this->head = headNode->next;
        this->head->prev = nullptr;
    }
    Job* j = headNode->item;
    this->size -= 1;
    return j;

}

Queue::~Queue() {
}
