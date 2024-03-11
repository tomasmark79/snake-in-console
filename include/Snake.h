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
    // std::shared_ptr<std::vector<std::shared_ptr<Snake>>> snakes;
    // int totalSnakes;
    int id;
    std::shared_ptr<Field> fie; // Field* fie;
    int length;
    bool isDead;
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
    bool amIDead() const;

    int getElementOfEattenFruit
    (
        const int* FruitX,
        const int* FruitY,
        int fruitCount
    ) const;
    void growUpSnake();

    const int* getSnakeX() const;
    const int* getSnakeY() const;

    int getSnakeLength() const;
    int getSnakeDirection() const;
    int getSnakeXHead() const;
    int getSnakeYHead() const;
};

