//
// Created by student on 29/02/24.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H
#include <string>
#include "Job.h"
using namespace std;


class QueueNode {
public:
    Job* item;
    QueueNode* next = nullptr;
    QueueNode* prev = nullptr;

    explicit QueueNode(Job *item);
};


#endif //UNTITLED_NODE_H
