#pragma once
#include "Field.h"

static const short MAX_SNAKE_LENGTH = 256+1;

class Snake
{
    Field* fie;
    int length, direction;
    char character;
    const double stepDivider = 1;
    int xArr[MAX_SNAKE_LENGTH];
    int yArr[MAX_SNAKE_LENGTH];
    int xTail[MAX_SNAKE_LENGTH];
    int yTail[MAX_SNAKE_LENGTH];
public:
    Snake(Field& field);
    int* getSnakeX() const;
    int* getSnakeY() const;
    int getSnakeLength() const;
    int getSnakeDirection() const;
    int getSnakeConflict() const;
    const void setSnakeWay(int direction);
    const void addTail();
    int whichFruitSnakeEatten(int* FruitX, int* FruitY, int fruitCount ) const;
};

