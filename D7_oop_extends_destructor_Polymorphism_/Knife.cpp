//
// Created by aaab on 11/9/20.
//
#include "Knife.h"
Knife::Knife() {
    this->base_demage=10;
    this->m_name="Knife";
}
int Knife::getBaseDamage() {
    return this->base_demage;
}
int Knife::getSuckBlood() {
    return 0;
}
bool Knife::getCrit() {
    return false;
}
bool Knife::getHold() {
    return false;

}


