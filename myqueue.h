#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "point.h"

constexpr auto MAXSIZE = 10000;

class MyQueue
{
public:
    MyQueue();
    bool isEmpty();
    void push(Point * p);
    void pop();
    Point* frontPoint();
    Point ** queue;
    int front;
    int end;
};

#endif // MYQUEUE_H
