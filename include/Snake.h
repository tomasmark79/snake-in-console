#pragma once
#include "Field.h"

static const short MAX_SNAKE_LENGTH = 256+1;
static const int stepDivider = 1;

class Snake
{
    Field* fie;
    int snakeLength;
    int snakeDirection;
    int snakeCoosX[MAX_SNAKE_LENGTH];
    int snakeCoosY[MAX_SNAKE_LENGTH];
    int backupCoosX[MAX_SNAKE_LENGTH];
    int backupCoosY[MAX_SNAKE_LENGTH];

    const void backupSnakeCoordinates();
    const void restoreSnakeCoordinatesShifted();
    const bool isStepBack(int directionTaken) const;

public:
    Snake(Field& field);
    const void setSnakeDirectionAndShift(int direction);
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

