//
// Created by 86188 on 2024/1/30.
//

#ifndef SNAKE_CHAR_GAME_H
#define SNAKE_CHAR_GAME_H

#include "snake/SnakeMap.h"
#include "snake/Snake.h"
#include "snake/prop/SnakeLongerProp.h"

class Game {
private:
    // 地图指针
    SnakeMap* snakeMap;

    // 蛇指针
    Snake* snake;

    // 道具指针
    SnakeLongerProp* snakeLongerProp;

    // 游戏知否终止
    bool end;

    // 空地图的链表
    std::list<Coord*> list_EmptyMap;

    // 渲染一帧的画面
    void paintFrame();

    // 处理一帧的信息
    void handleFrame();

public:

    // 构造函数
    Game();

    // 析构函数
    ~Game();

    // 获取游戏开始的信息
    void startGame();
};


#endif //SNAKE_CHAR_GAME_H
