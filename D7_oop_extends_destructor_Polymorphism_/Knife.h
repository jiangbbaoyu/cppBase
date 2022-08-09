//
// Created by aaab on 11/9/20.
//
#pragma once
#include <iostream>
#include "Weapon.h"
using namespace std;
class Knife:public Weapon{

public:
    Knife();
    virtual int getBaseDamage();
    virtual int getSuckBlood();
    virtual bool getHold();
    virtual bool getCrit();

};

