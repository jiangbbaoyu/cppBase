//
// Created by aaab on 11/12/20.
//

#ifndef CPPBASIC_FOOD_H
#define CPPBASIC_FOOD_H

#include <iostream>
#include "snake.h"
class Snake;

using namespace std;
class Food{
public:
    Food(Wall& wall);
    void setFood();
private:
    Wall& wall;
    int x;
    int y;


};

#endif //CPPBASIC_FOOD_H
