//Game.cpp
#include "game.h"

Game::Game(int w, int h, int s) : height(h), width(w), snakeSize(s), facing(DIR::RIGHT) {

    //TODO initialize the snake (in different locations?)
    for (int i = 0; i < s; ++i) {
        snake.push_front(Point(i,height/2));
    }
    moveFruit();
}

void Game::reset(int s){
    snake.clear();
    snakeSize = s;
    for (int i = 0; i < s; ++i) {
        snake.push_front(Point(i,height/2));
    }
    facing = DIR::RIGHT;
    moveFruit();
}

void Game::moveFruit() {
    //TODO check if there is empty space
    if (snakeSize >= height * width) {
        //no more space
        return;
    }
    do {
        fruit.x = rand() % width;
        fruit.y = rand() % height;
    } while (std::find(snake.begin(), snake.end(), fruit) != snake.end());
}

bool Game::move(int dir) {
    // std::cout << dir << std::endl;
    Point head = snake.front();
    if (dir > DIR::RIGHT || dir < DIR::UP)
        dir = facing;

    switch (dir) {
        case DIR::UP:
            head.y -= 1;
            break;
        case DIR::LEFT:
            head.x -= 1;
            break;
        case DIR::DOWN:
            head.y += 1;
            break;
        case DIR::RIGHT:
            head.x += 1;
            break;
        default:
            return false;
    }

    // check if head is in a valid location
    if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) 
        return false;
    
    // ignore the tail
    if (std::find(snake.begin(), snake.end() - 1,head) != snake.end() - 1)
        return false;
    
    // valid location
    snake.push_front(head);
    if (fruit == head) {
        ++snakeSize;
        moveFruit();
    } else {
        snake.pop_back();
    }

    // update facing
    facing = dir;

    return true;
}

/*
 * Returns a vector of input values that can be fed into the neural network
 * How to calculate this vector?
 * First orient the head so that it is facing the same direction, all values
 *  are relative to the head's facing
 * Then assign the following indices values depending on what blocks are there:
 * 
 *    0  1  2  3  4
 *    5  6  7  8  9
 *    10 11 H  12 13    H is head
 *    14 15 B  16 17    B is body (this is guaranteed for length > 1)
 *    18 19 20 21 22
 * 
 * Wall        = -1
 * Body part   = -.5
 * Empty space = 0
 * Fruit       = 1
 * (If block is out of bounds, treat it the same as a wall)
 * 
 * In addition, there are also two additional indices to keep track of the fruits position
 * index 23 = 1 / (fruit x - head x)
 * index 24 = 1 / (fruit y - head y)
 * (Note: this is just how the calculation would be if the snake is facing left, these calculations
 *  are changed accordingly for each other direction)
 * 
 */

std::vector<double> Game::getInputVector() const {
    int xymod;
    double tempx, tempy;
    bool swap;
    
    switch (facing) {
        case DIR::UP:
            xymod = 1;
            swap = false;
            break;
        case DIR::LEFT:
            xymod = 1;
            swap = true;
            break;
        case DIR::DOWN:
            xymod = -1;
            swap = false;
            break;
        case DIR::RIGHT:
            xymod = -1;
            swap = true;
            break;
    }

    std::vector<double> vals(25);
    int count = 0;
    int headx = snake.front().x;
    int heady = snake.front().y;
    // std::cout << std::endl << "|| " << headx << " " << heady << " , " << swap << " " << xymod << " ||" << std::endl;
    for (int i=-2; i<3; ++i) {
        for (int j=-2; j<3; ++j) {
            if (i==0 && j==0) continue;
            else if (i==1 && j==0) continue;

            if (!swap) {
                tempx = (headx + xymod * j);
                tempy = (heady + xymod * i);
            } else {
                tempx = (headx + xymod * i);
                tempy = (heady + -1 * xymod * j);
            }

                // std::cout << tempx << " " << tempy << " | " << j << " " << i << std::endl;
            if (tempx < 0 || tempx >= width || tempy < 0 || tempy >= height) {
                vals[count++] = -1;
            } else if (std::find(snake.begin(), snake.end(), Point(tempx,tempy)) != snake.end()) {
                vals[count++] = -0.5;
            } else if (tempx == fruit.x && tempy == fruit.y) {
                vals[count++] = 1;
            } else {
                vals[count++] = 0;
            }
        }
    }

    if (!swap) {
        tempx = (fruit.x == headx) ? 1 : 1.0 / (2*xymod * (fruit.x - headx));
        tempy = (fruit.y == heady) ? 1 : 1.0 / (2*xymod * (fruit.y - heady));
    } else {
        tempx = (fruit.y == heady) ? 1 : 1.0 / (2*xymod * (fruit.y - heady));
        tempy = (fruit.x == headx) ? 1 : 1.0 / (2*xymod * (fruit.x - headx));
    }
    vals[23] = tempx;
    vals[24] = tempy;

    return vals;
}

std::string Game::toString() const {
    std::string out = "";
    for (int i=0; i<height; ++i) {
        for (int j=0; j<width; ++j) {
            if (fruit.x == j && fruit.y == i) out += "★";
            else if (snake.front().x == j && snake.front().y == i) out += "@";
            else if (std::find(snake.begin(), snake.end(), Point(j,i)) != snake.end()) out += "#";
            else out += "-";
        }
        out += "\n";
    }
    return out;
}

