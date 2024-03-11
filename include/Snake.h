//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include <memory>
#include <vector>
#include <map>
#include <string>

static const short MAX_SNAKE_LENGTH = 256+1;

class Snake
{
    int id;
    int stepDivider;
    int length;
    int snakeDirection;
    bool isDead;
    int deadCode;
    const std::map<int, std::string> deadDescription { {1, "wall"}, {2, "self"}, {3, "another Snake"} };


    int snakeCoosX[MAX_SNAKE_LENGTH];
    int snakeCoosY[MAX_SNAKE_LENGTH];
    int backupCoosX[MAX_SNAKE_LENGTH];
    int backupCoosY[MAX_SNAKE_LENGTH];
    void inhumeSnake();
    void backupCoordinates();
    void restoreCoordinatesShifted();
    bool isStepBack(int direction) const;

public:
    Snake(int id, int stepDivider, int spawnX, int spawnY);

    void setMyDirectionAndShift(int direction);

    void setMeDead();
    void setDeadReason(int deadReason);
    int getDeadReason() const;
    bool amIDead() const;

    int getElementOfEattenFruit
    (
        const int* FruitX,
        const int* FruitY,
        int fruitCount
    ) const;
    void growUp();

    const int* getX() const;
    const int* getY() const;

    int getLength() const;
    int getDirection() const;
    int getXHead() const;
    int getYHead() const;
};

