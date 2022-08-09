//
// Created by aaab on 11/9/20.
//

//#pragma once
#ifndef CPPBASIC_MONSTER_H
#define CPPBASIC_MONSTER_H
#include <iostream>
#include <string>
#include "Hero.h"
using namespace std;
class Hero;// 将所有头文件需要用到的自定义类都在定义前声明一下,保证头文件引用的次序不会影响编译结果
class Monster{
public:
    string name;
    int hp;
    int def;
    int atk;
    bool isHolded;
    void attack(Hero* hero);
    Monster();
};

#endif //CPPBASIC_MONSTER_H
