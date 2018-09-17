//board.h
#ifndef _SNAKEBOARDH
#define _SNAKEBOARDH

#include "point.h"
#include <deque>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

enum DIR {
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3
};

class Board {
    int height;
    int width;

    // head is at front
    std::deque<Point> snake;
    int snakeSize;
    int facing;

    Point fruit = Point(0,0);

public:
    Board(int h, int w, int s);

    bool move(int dir);

    inline Point getFruit() {
        return fruit;
    }
    inline int getSize() {
        return snakeSize;
    }
    inline Point getHead() {
        return snake.front();
    }
private:
    void moveFruit();

};


#endif
