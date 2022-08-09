//
// Created by aaab on 11/9/20.
//
#include "DragonSword.h"
DragonSword::DragonSword() {
    this->m_name="DragonSword";
    this->base_demage=20;
    this->suckBloodRate=20;
    this->holdRate=90;
    this->critRate=50;

}
int DragonSword::getBaseDamage() {
    return this->base_demage;
}
bool DragonSword::getHold() {
    if(isTrigger(this->holdRate)){
        return true;
    }
    return false;
}
bool DragonSword::getCrit() {
    if(isTrigger(this->critRate)){
        return true;
    }
    return false;
}
int DragonSword::getSuckBlood() {
    if(isTrigger(this->suckBloodRate)){
        return this->base_demage*0.5;
    }
    return 0;
}
bool DragonSword::isTrigger(int rate) {
    int num=rand()%100+1; //1~100
    if(num<rate){
        return true;
    }
    return false;
}

