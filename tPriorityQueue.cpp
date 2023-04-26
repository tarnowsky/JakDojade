#include "tPriorityQueue.h"

void tPriorityQueue::push(Path &&path) {
    for (int i = 0; i < pathList.len(); i++)
        if (pathList[i].weight > path.weight) {
            pathList.insert(path, i);
            return;
        }
    pathList.push(path);
}

Path tPriorityQueue::pop() {
    return pathList.first();
}

int tPriorityQueue::len() {
    return pathList.len();
}

