//
// Created by aaab on 11/12/20.
//
#include "food.h"
#include "wall.h"


Food::Food(Wall &wall) :wall(wall){}
void Food::setFood() {
    this->x=rand()%(Wall::ROW-2)+1;
    this->y=rand()%(Wall::COL-2)+1;

    while(wall.getContent(this->x,this->y)!=' '){
        this->x=rand()%(Wall::ROW-2)+1;
        this->y=rand()%(Wall::COL-2)+1;
    }
    this->wall.setContent(this->x,this->y,'$');

}
