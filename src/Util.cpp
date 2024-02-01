//
// Created by 86188 on 2024/1/29.
//

#include "Util.h"
#include <exception>

/************************************************
 * Util
 ************************************************/

/************************************************
 * Coord
 ************************************************/
Coord::Coord(short int xValue, short int yValue) : X_Axis(xValue), Y_Axis(yValue) {}

Coord::Coord(const Coord& otherCoord) : X_Axis(otherCoord.X_Axis), Y_Axis(otherCoord.Y_Axis) {}

bool Coord::operator==(const Coord& otherCoord) const {
    if (X_Axis == otherCoord.X_Axis &&
    Y_Axis == otherCoord.Y_Axis) {
        return true;
    } else {
        return false;
    }
}

// 对X轴坐标的操作
bool Coord::setX(short int value) {
    X_Axis = value;
    return true;
}
short int Coord::getX() {
    return X_Axis;
}

// 对Y轴坐标的操作
bool Coord::setY(short int value) {
    Y_Axis = value;
    return true;
}
short int Coord::getY() {
    return Y_Axis;
}