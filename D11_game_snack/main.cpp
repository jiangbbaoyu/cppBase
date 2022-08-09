//
// Created by aaab on 11/12/20.
//

#include "wall.h"
#include "snake.h"
#include "food.h"
#include <unistd.h>
#include <curses.h>
int main(){
    srand((unsigned int)time(NULL) );
    Wall wall;
    wall.initWall();

    Food food(wall);
    Snake snake(wall,food);
    snake.initSnake();

    food.setFood();
//    snake.deletePoint();
//    snake.deletePoint();
//    snake.deletePoint();

    wall.drawWall();
    char op;
    bool isDie=false;
    while(!isDie){

        system("clear");
        isDie=snake.move(op);
        wall.drawWall();
        sleep(1);

    }
    cout<<"game over!!"<<endl;


//    snake.move('d');
//    snake.move('d');
//    snake.move('w');
//    snake.move('a');
    wall.drawWall();





//    wall.setContent(5,6,'=');
//    wall.setContent(5,7,'=');
//    wall.setContent(5,8,'@');






    return EXIT_SUCCESS;
}