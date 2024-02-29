//
// Created by student on 29/02/24.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H
#include <string>
#include "Job.h"
using namespace std;


class Node {
public:
    Job* item;
    Node* next = nullptr;
    Node* prev = nullptr;

    explicit Node(Job *item);
};


#endif //UNTITLED_NODE_H
