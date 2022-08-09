//
// Created by aaab on 11/9/20.
//

#ifndef CPPBASIC_DRAGONSWORD_H
#define CPPBASIC_DRAGONSWORD_H


#include "Weapon.h"

class DragonSword:public Weapon{
public:

    DragonSword();

    virtual int getBaseDamage();
    virtual int getSuckBlood();
    virtual bool getHold();
    virtual bool getCrit();

    int suckBloodRate;
    int holdRate;
    int critRate;
    bool isTrigger(int rate);
};

#endif //CPPBASIC_DRAGONSWORD_H