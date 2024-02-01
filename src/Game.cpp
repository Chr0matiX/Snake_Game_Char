//
// Created by 86188 on 2024/1/30.
//

#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>
#include "Game.h"

// 用于在list中通过指针准确查找目标
struct listCompare {
    const Coord* targetCoord;
    listCompare(const Coord* p_targetCoord) : targetCoord(p_targetCoord) {}
    bool operator()(const Coord* otherCoord) const {
        return *targetCoord == *otherCoord;
    }
};

Game::Game() : end(false), snake(nullptr), snakeMap(nullptr), snakeLongerProp(nullptr) {}

Game::~Game() {
    delete snake; snake = nullptr;
    delete snakeMap; snakeMap = nullptr;
    if (snakeLongerProp != nullptr) {
        delete snakeLongerProp; snakeLongerProp = nullptr;
    }
    for (auto & it : list_EmptyMap) {
        delete it;
    }
}

void Game::startGame() {
    short int mapLong = 0;
    do {
        system("cls");
        std::cout << "[Map size (L2R) : ]";
    } while (!(std::cin >> mapLong) && mapLong <= 0);

    short int mapWide = 0;
    do {
        system("cls");
        std::cout << "[Map size (T2B) : ]";
    } while (!(std::cin >> mapWide) && mapWide <= 0);

    snakeMap = new SnakeMap(mapLong + 1, mapWide + 1);
    snake = new Snake(snakeMap->mapCoord);

    for (int r = 1; r <= snakeMap->mapCoord->getY() - 1; r++) {
        for (int c = 1; c <= snakeMap->mapCoord->getX() - 1; c++) {
            Coord *coord = new Coord(c, r);
            if (auto it = std::find_if(snake->list_Snake.begin(), snake->list_Snake.end(), listCompare(coord));
                    it == snake->list_Snake.end()) {
                list_EmptyMap.push_back(coord);
            } else {
                delete coord;
            }
        }
    }

    handleFrame();
}

void Game::handleFrame() {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::chrono::seconds loopDuration(1);
    std::chrono::duration<double> elapsed_time;

    while (!end && snake->alive) {
        Util::Direction input_dir = snake->headDirection;
        do {        // 输入循环
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            // w, a, s, d, q, r
            for (int key : {87, 65, 83, 68, 81, 82}) {
                if (GetAsyncKeyState(key) & 0x8001) {
                    // 如果键被按下
                    if (key == 87 && snake->headDirection != Util::Direction::B) {
                        input_dir = Util::Direction::T;
                    } else if (key == 65 && snake->headDirection != Util::Direction::R) {
                        input_dir = Util::Direction::L;
                    } else if (key == 83 && snake->headDirection != Util::Direction::T) {
                        input_dir = Util::Direction::B;
                    } else if (key == 68 && snake->headDirection != Util::Direction::L) {
                        input_dir = Util::Direction::R;
                    } else if (key == 81) {
                        end = true;
                        break;
                    } else if (key == 82) {
                        // 还妹写呢，不着急
                    }
                }
            }
            if (end) break;
            auto current_time = std::chrono::high_resolution_clock::now();
            elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start_time);
        } while (elapsed_time <= loopDuration);
        if (end) break;

        snake->headDirection = input_dir;

        // 蛇将要移动，先向空地图链表中添加蛇尾元素
        list_EmptyMap.push_back(new Coord(snake->list_Snake.back()->getX(), snake->list_Snake.back()->getY()));

        snake->move();      // 蛇移动一下
        if(!snake->alive) break;

        // 处理道具判定
        if (snakeLongerProp != nullptr && snakeLongerProp->alive && *snakeLongerProp->coord == *snake->list_Snake.front()) {
            snakeLongerProp->snakeLonger(snake);
            delete snakeLongerProp;
            snakeLongerProp = nullptr;
        }

        // 处理空地图链表
        if (snake->list_Snake.size() > 1) {
            if (auto it = std::find_if(list_EmptyMap.begin(), list_EmptyMap.end(),
                                       listCompare(snake->list_Snake.back())); it != list_EmptyMap.end()) {
                delete *it;
                list_EmptyMap.erase(it);
            }
        }
        auto deleteIt = std::find_if(list_EmptyMap.begin(), list_EmptyMap.end(), listCompare(snake->list_Snake.front()));
        delete *deleteIt;
        list_EmptyMap.erase(deleteIt);

        // 没有道具时生成道具
        if (snakeLongerProp == nullptr || !snakeLongerProp->alive) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distribution(0, list_EmptyMap.size() - 1);
            int randomNumber = distribution(gen);
            int rdmIndex = 0;
            for (auto it = list_EmptyMap.begin(); it != list_EmptyMap.end(); it++, rdmIndex++) {
                if (rdmIndex == randomNumber) {
                    if (snakeLongerProp != nullptr) {
                        delete snakeLongerProp;
                        snakeLongerProp = nullptr;
                    }
                    snakeLongerProp = new SnakeLongerProp(*it);
                    break;
                }
            }
        }

        paintFrame();
    }
}

void Game::paintFrame() {
    system("cls");
    char buffer[((snakeMap->mapCoord->getX() + 1) * 2 + 1) * (snakeMap->mapCoord->getY() + 1)];

    for (int r = 0; r <= snakeMap->mapCoord->getY(); r++) {
        for (int c = 0; c <= snakeMap->mapCoord->getX(); c++) {
            Coord nowCoord = Coord(c, r);
            int bufferIndex = c * 2 + r * ((snakeMap->mapCoord->getX() + 1) * 2 + 1);

            // 地图边界
            if (r == 0 || r == snakeMap->mapCoord->getY() || c == 0 || c == snakeMap->mapCoord->getX()) {
                buffer[bufferIndex] = snakeMap->boundary[0];
                buffer[bufferIndex + 1] = snakeMap->boundary[1];
                // 道具
            } else if (nowCoord == *(snakeLongerProp->coord)) {
                buffer[bufferIndex] = snakeLongerProp->icon[0];
                buffer[bufferIndex + 1] = snakeLongerProp->icon[1];
                // 蛇
            } else if (auto snakeIt = std::find_if(snake->list_Snake.begin(), snake->list_Snake.end(), listCompare(&nowCoord)); snakeIt != snake->list_Snake.end()) {
                // 蛇头
                if (*(*snakeIt) == *(snake->list_Snake.front())) {
                    buffer[bufferIndex] = snake->snakeHead[0];
                    buffer[bufferIndex + 1] = snake->snakeHead[1];
                    // 蛇身
                } else {
                    buffer[bufferIndex] = snake->snakeBody[0];
                    buffer[bufferIndex + 1] = snake->snakeBody[1];
                }
                // 空地图
            } else {
                buffer[bufferIndex] = snakeMap->emptyMap[0];
                buffer[bufferIndex + 1] = snakeMap->emptyMap[1];
            }
        }
        buffer[(r + 1) * ((snakeMap->mapCoord->getX() + 1) * 2 + 1) - 1] = '\n';
    }
    std::cout << buffer;
}

/*
for (int r = 0; r <= snakeMap->mapCoord->getY(); r++) {
for (int c = 0; c <= snakeMap->mapCoord->getX(); c++) {
Coord nowCoord = Coord(c, r);
// 地图边界
if (r == 0 || r == snakeMap->mapCoord->getY() || c == 0 || c == snakeMap->mapCoord->getX()) {
std::cout << snakeMap->boundary;
// 道具
} else if (nowCoord == *(snakeLongerProp->coord)) {
std::cout << snakeLongerProp->icon;
// 蛇
} else if (auto snakeIt = std::find_if(snake->list_Snake.begin(), snake->list_Snake.end(), listCompare(&nowCoord)); snakeIt != snake->list_Snake.end()) {
// 蛇头
if (*(*snakeIt) == *(snake->list_Snake.front())) {
std::cout << snake->snakeHead;
// 蛇身
} else {
std::cout << snake->snakeBody;
}
// 空地图
} else {
std::cout << snakeMap->emptyMap;
}
}
std::cout << std::endl;
}*/
