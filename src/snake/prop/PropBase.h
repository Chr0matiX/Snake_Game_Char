//
// Created by 86188 on 2024/1/29.
//

#ifndef SNAKE_CHAR_PROPBASE_H
#define SNAKE_CHAR_PROPBASE_H


#include "../../Util.h"

class PropBase {
private:
public:
    // 构造函数
    PropBase(short int xValue, short int yValue, int propSize);
    PropBase(Coord* propCoord, int propSize);
    // 析构函数
    virtual ~PropBase();

    // 道具所占格子大小
    int size;

    // 道具左上角坐标
    Coord* coord;
};


#endif //SNAKE_CHAR_PROPBASE_H
