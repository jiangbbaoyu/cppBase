//
// Created by aaab on 11/9/20.
//

#ifndef CPPBASIC_WEAPON_H
#define CPPBASIC_WEAPON_H
#include <iostream>
#include <string>
using namespace std;
class Weapon{
public:
    string m_name;
    int base_demage;

    virtual int getBaseDamage()=0;
    virtual int getSuckBlood()=0;
    virtual bool getHold()=0;
    virtual bool getCrit()=0;
};

#endif //CPPBASIC_WEAPON_H
