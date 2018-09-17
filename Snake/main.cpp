//main.cpp
#include <iostream>
#include <string>
#include "board.h"
#include "point.h"

int main(int argc, char** argv) {
    Board game = Board(10,10,4);

    std::string cmdString;

    while (std::cin >> cmdString) {
        int dir = 4;
        
        switch (cmdString[0])
        {
            case 'w':
                dir = 0;
                break;
            case 'a':
                dir = 1;
                break;
            case 's':
                dir = 2;
                break;
            case 'd':
                dir = 3;
                break;
        
            default:
                break;
        }

        bool goodMove = game.move(dir);
        Point fruit = game.getFruit();
        Point head = game.getHead();

        std::cout << goodMove << std::endl;
        std::cout << "Fruit location: " << fruit.x << " " << fruit.y << std::endl;
        std::cout << "Head location: " << head.x << " " << head.y << std::endl;
        std::cout << "Current length: " << game.getSize() << std::endl;
        
    }

    return 0;
}
