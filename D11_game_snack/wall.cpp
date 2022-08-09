//
// Created by aaab on 11/12/20.
//
#include "wall.h"

void Wall::initWall() {
    for (int i = 0; i <ROW; ++i) {
        for (int j = 0; j <COL+COL_INFO ; ++j) {

            if(i==0||i==ROW-1||j==0||j==COL-1||j==COL+COL_INFO-1){
                this->content[i][j]='*';
            }else{
                this->content[i][j]=' ';
            }
        }
    }
    setContentsX(4,COL+3,"author:aaab");
    setContentsX(6,COL+3,"a:left");
    setContentsX(7,COL+3,"w:top");
    setContentsX(8,COL+3,"d:right");
    setContentsX(9,COL+3,"s:down");
}

void Wall::drawWall() {

    for (int i = 0; i <ROW ; ++i) {
        for (int j = 0; j <COL+COL_INFO ; ++j) {
            if(j<COL-1){
                cout<<this->content[i][j]<<"  ";
            }else{
                cout<<this->content[i][j];
            }
        }


        cout<<endl;
    }
}

char Wall::getContent(int x, int y) {
    return this->content[x][y];
}
void Wall::setContent(int x, int y, char ele) {
    this->content[x][y]=ele;
}

void Wall::setContentsX(int start_x, int start_y, const string elements) {
    int current_row=start_y;
    for (int i = 0; i <elements.size() ; ++i) {
        this->content[start_x][current_row]=elements.at(i);
        current_row++;
    }
}