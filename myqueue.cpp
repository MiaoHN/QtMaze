#include "myqueue.h"

MyQueue::MyQueue()
{
    queue = new Point * [MAXSIZE];
    front = 0;
    end = 0;
}

bool MyQueue::isEmpty()
{
    if (front == end)return true;
    return false;
}

void MyQueue::push(Point *p)
{
    queue[end] = p;
    end++;
}

void MyQueue::pop()
{
    if (isEmpty()) return;
    front++;
}

Point *MyQueue::frontPoint()
{
    return queue[front];
}
