#ifndef JAKDOJADE_TPRIORITYQUEUE_H
#define JAKDOJADE_TPRIORITYQUEUE_H
#include "City.h"

struct Edge {
    tString city1, city2;
};

struct Path {
    City *from;
    City *to;
    int weight;
};

class tPriorityQueue {
private:
    tVector<Path> pathList;
public:
    void push(Path&& path);
    Path pop();
    int len();
};

#endif //JAKDOJADE_TPRIORITYQUEUE_H
