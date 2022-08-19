//
// Created by aaab on 8/17/22.
//

#ifndef CPPBASIC_WINDOW_MGR_H
#define CPPBASIC_WINDOW_MGR_H

#include <vector>
#include <string>

class Screen;

class Window_mgr{
public:
    void clear();
    std::vector<Screen> screens;
};

class Screen{
//    friend class Window_mgr;
    friend void Window_mgr::clear(); // 其他类的成员变量作为友元函数
public:
    typedef std::string::size_type t;
    Screen& set(t h,t w);
    t getHigh() const;
    t getWidth() const;
private:
    t high=1;
    t width=1;

};



#endif //CPPBASIC_WINDOW_MGR_H
