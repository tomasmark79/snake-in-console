//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"

static const short MAX_SNAKE_LENGTH = 256+1;
static const int stepDivider = 1;

class Snake
{
    int id;
    Field* fie;
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
    Snake(int id, Field& field);
    const void setSnakeDirectionAndShift(int direction);

    const void setSnakeDie();
    const bool isSnakeDie() const;

    const int isSnakeInConflict() const;
    const int getElementOfEattenFruit
    (
        const int* FruitX,
        const int* FruitY,
        int fruitCount
    ) const;
    const void growUpSnake();

    const int* getSnakeX() const;
    const int* getSnakeY() const;

    const int getSnakeLength() const;
    const int getSnakeDirection() const;



};

