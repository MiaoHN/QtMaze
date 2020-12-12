#include "point.h"

Point::Point()
{
    this->x = -1;
    this->y = -1;
    this->status = 5;
    this->pioneer = -1;
}

Point::Point(int x, int y, int stat)
{
    this->x = x;
    this->y = y;
    this->status = stat;
    this->pioneer = -1;
}

bool Point::operator!=(const Point &p)
{
    if (this->x != p.x || this->y != p.y) {
        return true;
    }
    return false;
}
