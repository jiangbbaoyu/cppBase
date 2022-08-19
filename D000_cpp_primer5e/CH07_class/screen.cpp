//
// Created by aaab on 8/17/22.
//
#include "window_mgr.h"

Screen & Screen::set(Screen::t h, Screen::t w) {
    this->high=h;
    this->width=w;
}

Screen::t Screen::getHigh() const {
    return this->high;
}


Screen::t Screen::getWidth() const {
    return this->width;
}
