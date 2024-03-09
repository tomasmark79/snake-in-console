//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include <memory>

static const short MAX_SNAKE_LENGTH = 256+1;
static const int stepDivider = 1;

class Snake
{
    int id;
    std::shared_ptr<Field> fie; // Field* fie;
    int snakeLength;
    bool isDie;
    int snakeDirection;
    int snakeCoosX[MAX_SNAKE_LENGTH];
    int snakeCoosY[MAX_SNAKE_LENGTH];
    int backupCoosX[MAX_SNAKE_LENGTH];
    int backupCoosY[MAX_SNAKE_LENGTH];

    const void inhumeSnake();
    const void backupSnakeCoordinates();
    const void restoreSnakeCoordinatesShifted();
    const bool isStepBack(int directionTaken) const;

public:
    Snake(int id, std::shared_ptr<Field> field);
    const void setSnakeDirectionAndShift(int direction);

    const void setSnakeDie();
    bool isSnakeDie() const;

    int isSnakeInConflict() const;
    int getElementOfEattenFruit
    (
        const int* FruitX,
        const int* FruitY,
        int fruitCount
    ) const;
    const void growUpSnake();

    const int* getSnakeX() const;
    const int* getSnakeY() const;

    int getSnakeLength() const;
    int getSnakeDirection() const;



};

