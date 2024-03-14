#include "QueueNode.h"

QueueNode::QueueNode(Job *item) : item(item) {
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyinitialized state");
}

bool QueueNode::properlyInitialized() const {
    return initcheck == this;
}
