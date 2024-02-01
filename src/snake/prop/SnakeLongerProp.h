//
// Created by 86188 on 2024/1/30.
//

#ifndef SNAKE_CHAR_SNAKELONGERPROP_H
#define SNAKE_CHAR_SNAKELONGERPROP_H


#include "PropBase.h"
#include "../Snake.h"

class SnakeLongerProp : public PropBase{
private:

public:
    // 道具的图案
    const char* icon = "LL";

    // 构造函数
    SnakeLongerProp(short int xValue, short int yValue, int propSize = 1);
    SnakeLongerProp(Coord* propCoord, int propSize = 1);

    // 道具作用
    void snakeLonger(Snake* snake);

    // 道具是否还存在
    bool alive;
};


#endif //SNAKE_CHAR_SNAKELONGERPROP_H
