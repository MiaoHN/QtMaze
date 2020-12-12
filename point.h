#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point();
    Point(int x, int y, int stat);

    bool operator!=(const Point & p);
public:
    int x;
    int y;
    int status;
    int pioneer;
};

#endif // POINT_H
