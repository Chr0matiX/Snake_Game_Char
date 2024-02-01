//
// Created by 86188 on 2024/1/29.
//

#include "SnakeMap.h"

#include <iostream>

SnakeMap::SnakeMap(short int xValue, short int yValue) {
    mapCoord = new Coord(xValue, yValue);
}

SnakeMap::SnakeMap(const Coord* otherCoord) {
    mapCoord = new Coord(*otherCoord);
}

void SnakeMap::paintAllMap_Test() {
    for (int r = 0; r <= mapCoord->getY(); ++r) {
        for (int c = 0; c <= mapCoord->getX(); ++c) {
            // 现在的坐标
            Coord nowCoord = Coord(c, r);

            if (nowCoord.getX() == 0 || nowCoord.getX() == mapCoord->getX() ||
            nowCoord.getY() == 0 || nowCoord.getY() == mapCoord->getY()){
                std::cout << boundary;
            } else {        // 空地图
                std::cout << emptyMap;
            }
        }
        std::cout << std::endl;
    }
}
