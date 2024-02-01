//
// Created by 86188 on 2024/1/29.
//

#include "Snake.h"

Snake::Snake(Coord* mapCoord) : alive(true), mapCoord(new Coord(mapCoord->getX(), mapCoord->getY())), headDirection(Util::Direction::T) {
    list_Snake.push_front(new Coord(mapCoord->getX() / 2, mapCoord->getY() / 2));
}

Snake::~Snake() {
    for (auto& it : list_Snake) {
        delete it;
        it = nullptr;
    }
}

void Snake::move() {
    Coord*& headCoord = list_Snake.front();
    Coord* nowHeadCoord = nullptr;

    switch (headDirection) {
        case Util::Direction::T : {
            nowHeadCoord = new Coord(headCoord->getX(), headCoord->getY() - 1);
            break;
        }
        case Util::Direction::B : {
            nowHeadCoord = new Coord(headCoord->getX(), headCoord->getY() + 1);
            break;
        }
        case Util::Direction::L : {
            nowHeadCoord = new Coord(headCoord->getX() - 1, headCoord->getY());
            break;
        }
        case Util::Direction::R : {
            nowHeadCoord = new Coord(headCoord->getX() + 1, headCoord->getY());
            break;
        }
    }

    delete list_Snake.back();
    list_Snake.back() = nullptr;
    list_Snake.pop_back();

    if (nowHeadCoord->getX() == 0) {                                        // 脑袋在左边界
        nowHeadCoord->setX(mapCoord->getX() - 1);
    } else if (nowHeadCoord->getX() == mapCoord->getX()) {      // 脑袋在右边界
        nowHeadCoord->setX(1);
    } else if (nowHeadCoord->getY() == 0) {                                 // 脑袋在上边界
        nowHeadCoord->setY(mapCoord->getY() - 1);
    } else if (nowHeadCoord->getY() == mapCoord->getY()) {      // 脑袋在下边界
        nowHeadCoord->setY(1);
    }

    for (auto& it : list_Snake) {
        if (nowHeadCoord->getX() == it->getX() && nowHeadCoord->getY() == it->getY()) {     // 如果坐标重合，那就是撞上了
            alive = false;
            return;
        }
    }

    list_Snake.push_front(nowHeadCoord);
}