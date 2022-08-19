//
// Created by aaab on 8/17/22.
//
#include "window_mgr.h"

void Window_mgr::clear() {
    for(auto &screen :screens){
        screen.width=0;
        screen.high=0;
    }
}
