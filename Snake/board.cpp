//board.cpp
#include "board.h"

Board::Board(int h, int w, int s) : height(h), width(w), snakeSize(s), facing(DIR::RIGHT) {
    // initialize random seed
    srand (time(NULL));

    //TODO initialize the snake (in different locations?)
    for (int i = 0; i < s; ++i) {
        snake.push_front(Point(i,0));
    }
    moveFruit();
}

void Board::moveFruit() {
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

bool Board::move(int dir) {
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
    if (std::find(snake.begin(), --snake.end(),head) != --snake.end())
        return false;
    
    // valid location
    snake.push_front(head);
    if (fruit == head) {
        ++snakeSize;
        moveFruit();
    } else {
        snake.pop_back();
    }

    return true;
}

