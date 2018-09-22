//Game.h
#ifndef _SNAKEGAMEH
#define _SNAKEGAMEH

#include "point.h"
#include <deque>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

enum DIR {
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3
};

class Game {
    int height;
    int width;

    // head is at front
    std::deque<Point> snake;
    int snakeSize;
    int facing;

    Point fruit = Point(0,0);

public:
    Game(int w, int h, int s);

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

    inline const std::deque<Point> &getSnake() {
        return snake;
    }

    std::vector<double> getInputVector() const;
private:
    void moveFruit();

};


#endif
