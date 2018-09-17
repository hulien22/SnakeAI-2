//point.h
#ifndef _POINTH
#define _POINTH

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {};

    // overloading so we can use std::find
    bool operator==(const Point& p) {
        if (x == p.x && y == p.y) return true;
        else return false;
    }
};

#endif
