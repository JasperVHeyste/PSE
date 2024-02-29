//
// Created by student on 29/02/24.
//

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
    Node* newNode = new Node(p);
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
    Node* headNode = this->head;
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
