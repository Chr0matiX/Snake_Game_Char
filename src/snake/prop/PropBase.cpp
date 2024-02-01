//
// Created by 86188 on 2024/1/29.
//

#include "PropBase.h"

PropBase::PropBase(Coord *propCoord, int propSize) : coord(new Coord(propCoord->getX(), propCoord->getY())), size(propSize) {}

PropBase::PropBase(short xValue, short yValue, int propSize) : coord(new Coord(xValue, yValue)), size(propSize) {}

PropBase::~PropBase() {
    delete coord;
    coord = nullptr;
}