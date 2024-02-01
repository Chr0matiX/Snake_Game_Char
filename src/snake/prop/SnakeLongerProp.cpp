//
// Created by 86188 on 2024/1/30.
//

#include "SnakeLongerProp.h"

SnakeLongerProp::SnakeLongerProp(Coord *propCoord, int propSize) : PropBase(propCoord, propSize), alive(true) {}

SnakeLongerProp::SnakeLongerProp(short xValue, short yValue, int propSize) : PropBase(xValue, yValue, propSize), alive(true) {}

void SnakeLongerProp::snakeLonger(Snake *snake) {
    alive = false;

    Util::Direction dir;
    Coord* last1 = snake->list_Snake.back();

    if (snake->list_Snake.size() <= 1) {
        switch (snake->headDirection) {
            case Util::Direction::T : {
                dir = Util::Direction::B;
                break;
            }
            case Util::Direction::B : {
                dir = Util::Direction::T;
                break;
            }
            case Util::Direction::L : {
                dir = Util::Direction::R;
                break;
            }
            case Util::Direction::R : {
                dir = Util::Direction::L;
                break;
            }
        }
    } else {
        auto last2 = *(std::prev(snake->list_Snake.end(), 2));

        if (last1->getX() == last2->getX()) {
            if (last1->getY() < last2->getY()) {
                if ((last1->getY() - last2->getY()) * (last1->getY() - last2->getY()) == 1) {
                    dir = Util::Direction::B;
                } else {
                    dir = Util::Direction::T;
                }
            } else {
                if ((last1->getY() - last2->getY()) * (last1->getY() - last2->getY()) == 1) {
                    dir = Util::Direction::T;
                } else {
                    dir = Util::Direction::B;
                }
            }
        } else {
            if (last1->getX() < last2->getX()) {
                if ((last1->getX() - last2->getX()) * (last1->getX() - last2->getX()) == 1) {
                    dir = Util::Direction::L;
                } else {
                    dir = Util::Direction::R;
                }
            } else {
                if ((last1->getX() - last2->getX()) * (last1->getX() - last2->getX()) == 1) {
                    dir = Util::Direction::R;
                } else {
                    dir = Util::Direction::L;
                }
            }
        }
    }

    switch (dir) {
        case Util::Direction::T :{
            snake->list_Snake.push_back(new Coord(last1->getX(), last1->getY() - 1));
            break;
        }
        case Util::Direction::B :{
            snake->list_Snake.push_back(new Coord(last1->getX(), last1->getY() + 1));
            break;
        }
        case Util::Direction::L :{
            snake->list_Snake.push_back(new Coord(last1->getX() - 1, last1->getY()));
            break;
        }
        case Util::Direction::R :{
            snake->list_Snake.push_back(new Coord(last1->getX() + 1, last1->getY()));
            break;
        }
    }


}