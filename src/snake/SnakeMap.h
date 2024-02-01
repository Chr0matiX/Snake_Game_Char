//
// Created by 86188 on 2024/1/29.
//

#ifndef SNAKE_CHAR_SNAKEMAP_H
#define SNAKE_CHAR_SNAKEMAP_H

#include "../Util.h"

class SnakeMap {
private:
public:
    // 地图大小坐标（右下角坐标）
    Coord* mapCoord;

    // 空地图的图案
    const char* emptyMap = "  ";
    // 地图的边界
    const char* boundary = "MW";
    // 道具的图标
    const char* prop = "ZZ";

    // 构造函数
    SnakeMap(short int xValue, short int yValue);
    SnakeMap(const Coord* otherCoord);

    // 渲染地图（测试用）
    void paintAllMap_Test();
};


#endif //SNAKE_CHAR_SNAKEMAP_H
