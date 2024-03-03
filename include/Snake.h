#pragma once
#include "Field.h"

static const short MAX_SNAKE_LENGTH = 256+1;

class Snake
{
    Field* fie;
    int snakeLength;
    int snakeDirection;
    const int stepDivider = 1;
    int xArr[MAX_SNAKE_LENGTH];
    int yArr[MAX_SNAKE_LENGTH];
    int xTail[MAX_SNAKE_LENGTH];
    int yTail[MAX_SNAKE_LENGTH];
public:
    Snake(Field& field);
    const int* getSnakeX() const;
    const int* getSnakeY() const;
    const int getSnakeLength() const;
    const int getSnakeDirection() const;
    const int checkSnakeConflict() const;

    const void setSnakeWay(int direction);
    const void addTail();

    const int whichFruitSnakeEatten(const int* FruitX, const int* FruitY, int fruitCount ) const;
};

