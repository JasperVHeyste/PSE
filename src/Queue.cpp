#include "Queue.h"
#include <iostream>


bool Queue::isEmpty() {
    if (this->size == 0){
        return true;
    }
    return false;
}

bool Queue::enqueue(Job* p) {
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
    QueueNode* headNode = this->head;
    if (this->isEmpty()){
        cout << "error, queue is empty"; //vervang door REQUIRE
        return nullptr;
    }else if (this->size == 1){
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
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

int Queue::getSize() const {
    return size;
}

Job *Queue::getJob(int index) {
    QueueNode* temp = this->head;
    for (int i = 0; i < index; i++){
        temp = temp->next;
    }
    return temp->item;
}
