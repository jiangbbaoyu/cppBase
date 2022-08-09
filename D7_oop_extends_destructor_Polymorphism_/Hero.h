//
// Created by aaab on 11/9/20.
//
//#pragma once
#ifndef CPPBASIC_HERO_H
#define CPPBASIC_HERO_H

#include <iostream>
#include <string>
#include "Weapon.h"
#include "Monster.h"
using namespace std;
class Monster; // 将所有头文件需要用到的自定义类都在定义前声明一下,保证头文件引用的次序不会影响编译结果
class Hero{
public:
    string name;
    int atk;
    int def;
    int hp;
    Weapon* weapon;
    Hero();
    ~Hero();
    void equipWeapon(Weapon* weapon);
    void attack(Monster* monster);

};
#endif //CPPBASIC_HERO_H



