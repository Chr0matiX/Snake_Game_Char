//
// Created by 86188 on 2024/1/29.
//

#ifndef SNAKE_CHAR_SNAKE_H
#define SNAKE_CHAR_SNAKE_H

#include "SnakeMap.h"
#include "../Util.h"
#include <list>

class Snake {
private:
    // 地图大小坐标
    Coord* mapCoord;

public:
    // 构造函数
    Snake(Coord* mapCoord);
    // 析构函数
    ~Snake();

    // 蛇所占格子的链表（可获取头尾）
    std::list<Coord*> list_Snake;
    // 让蛇朝指定方向前进一次，计算蛇的坐标
    void move();
    // 蛇头部的方向
    Util::Direction headDirection;

    // 蛇头的图案
    const char* snakeHead = "HH";

    // 蛇身体的图案
    const char* snakeBody = "OO";

    // 蛇是否还存活
    bool alive;
};


#endif //SNAKE_CHAR_SNAKE_H
