//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include <memory>
#include <vector>

static const short MAX_SNAKE_LENGTH = 256+1;
static const int stepDivider = 1;

class Snake
{
    int id;
    int length;
    bool isDead;
    int deadReason;
    int snakeDirection;
    int snakeCoosX[MAX_SNAKE_LENGTH];
    int snakeCoosY[MAX_SNAKE_LENGTH];
    int backupCoosX[MAX_SNAKE_LENGTH];
    int backupCoosY[MAX_SNAKE_LENGTH];

    void inhumeSnake();
    void backupCoordinates();
    void restoreCoordinatesShifted();
    bool isStepBack(int direction) const;

public:
    Snake(int id, int spawnX, int spawnY);

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

