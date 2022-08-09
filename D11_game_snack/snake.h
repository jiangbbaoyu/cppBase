//
// Created by aaab on 11/12/20.
//

#ifndef CPPBASIC_SNAKE_H
#define CPPBASIC_SNAKE_H

#include <iostream>
#include "wall.h"
#include "food.h"
class Food;
class Wall;

using namespace std;
class Food;
class Snake{
public:
    enum{
        UP='w',
        DOWN='s',
        LEFT='a',
        RIGHT='d'
    };

    Snake(Wall& wall,Food& food);
    void initSnake();
    void addPoint(int x,int y);
    void destory();
    void deletePoint();
    bool move(const char c);

    struct Point{
        int x;
        int y;
        Point* next;
    };
private:

    Point* head;
    Wall& wall;
    Food& food;




};

#endif //CPPBASIC_SNAKE_H
