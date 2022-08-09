//
// Created by aaab on 11/9/20.
//
#include "Hero.h"

Hero::Hero() {
    this->hp=500;
    this->atk=50;
    this->def=50;
    this->name="jax";
    this->weapon=NULL;

}
void Hero::attack(Monster *monster) {
    int damage=this->atk;
    int addHP=0;
    bool isHold=false;
    bool isCrit=false;
    if(this->weapon!=NULL){
        damage+=this->weapon->getBaseDamage();
        addHP+=this->weapon->getSuckBlood();
        if(addHP>0){
            cout<<"suck blood: "<<addHP<<endl;
        }
        isHold=this->weapon->getHold();
        isCrit=this->weapon->getCrit();
    }
    if(isCrit){
        damage*=2;
        cout<<"is crited ,double damage: "<<damage<<endl;
    }
    if(isHold){
        cout<<"monster is holded this round"<<endl;
    }

    monster->isHolded=isHold;
    int trueDamage=(damage-monster->def)>0?damage-monster->def:1;
    monster->hp-=trueDamage;
    this->hp+=addHP;
    cout<<"hero attack monster ,cause damage "<<trueDamage<<endl;
}
void Hero::equipWeapon(Weapon* weapon) {
    this->weapon=weapon;
    cout<<this->name<<" equip"<<weapon->m_name<<endl;
}
Hero::~Hero() {
    if(this->weapon!=NULL){
        delete this->weapon;
        cout<<"distroy weapon:"<<this->weapon<<endl;
        this->weapon=NULL;
    }
//    cout<<this->hp<<endl;
}

