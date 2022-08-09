//
// Created by aaab on 11/12/20.
//

#ifndef CPPBASIC_WALL_H
#define CPPBASIC_WALL_H

#include <iostream>
#include <string>
using  namespace std;
class Wall{
public:
    enum {
        ROW=20,
        COL=20,
        COL_INFO=18

    };
    void initWall();
    void drawWall();
    void setContent(int x,int y,char ele);
    void setContentsX(int start_x,int start_y,const string elements);
    char getContent(int x,int y);

private:
    char content[ROW][COL+COL_INFO];


};


#endif //CPPBASIC_WALL_H
