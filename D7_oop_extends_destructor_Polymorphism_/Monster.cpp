#include "Monster.h"
Monster::Monster() {
    this->hp=300;
    this->atk=70;
    this->def=40;
    this->isHolded=false;
    this->name="bikemowang";
}
void Monster::attack(Hero *hero) {
    if(this->isHolded){
        cout<<"monster is holded,this round "<<endl;
        return;
    }
    int damage=(this->atk-hero->def)?this->atk-hero->def:1;
    cout<<"monster attack hero ,cause damage "<<damage<<endl;
    hero->hp-=damage;
}

