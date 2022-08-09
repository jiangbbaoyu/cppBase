//
// Created by aaab on 11/12/20.
//
#include "snake.h"

Snake::Snake(Wall& wall,Food& food):wall(wall) ,food(food){
    head=NULL;
}

void Snake::destory() {
    Point* tmp=this->head;
    while(tmp!=NULL){
        tmp=head->next;
        delete head;
        head=tmp;
    }
}

void Snake::addPoint(int x, int y) {
    Point* p=new Point;
    p->x=x;
    p->y=y;


    if(head!=NULL){
        this->wall.setContent(head->x,head->y,'*');
    }
    p->next=head;
    head=p;
    this->wall.setContent(head->x,head->y,'@');
}
void Snake::deletePoint() {
    if(head!=NULL&&head->next!=NULL){
        Point* first=head;
        Point* second=head->next;
        while(second->next!=NULL){
            first=second;
            second=second->next;
        }
        wall.setContent(second->x,second->y,' ');
        first->next=NULL;
        delete second;
        second=NULL;
    }
}
void Snake::initSnake() {
    destory();
    addPoint(5,5);
    addPoint(6,5);
    addPoint(7,5);

}

bool Snake::move(const char c) {
    int x=this->head->x;
    int y=this->head->y;
    switch(c){
        case UP:
            --x;
            break;
        case DOWN:
            ++x;
            break;
        case RIGHT:
            ++y;
            break;
        case LEFT:
            --y;
            break;
        default:
            break;
    }

    if(this->wall.getContent(x,y)=='*'){
        return false;
    }

    if(wall.getContent(x,y)=='$'){
        addPoint(x,y);
        this->food.setFood();
    }else{
        addPoint(x,y);
        deletePoint();
    }
    return true;
}


