//
// Created by 86188 on 2024/1/29.
//

#ifndef SNAKE_CHAR_UTIL_H
#define SNAKE_CHAR_UTIL_H


class Util {
public:
    enum Direction {
        T,
        B,
        L,
        R
    };
};

class Coord {
private:
    // X轴坐标
    short int X_Axis;

    // Y轴坐标
    short int Y_Axis;

public:
    // 构造函数
    Coord(short int xValue, short int yValue);
    // 拷贝构造函数
    Coord(const Coord& otherCoord);
    // 重载==比较符号
    bool operator==(const Coord& otherCoord) const;

    // 对X轴坐标的操作
    bool setX(short int value);
    short int getX();

    // 对Y轴坐标的操作
    bool setY(short int value);
    short int getY();
};

#endif //SNAKE_CHAR_UTIL_H
