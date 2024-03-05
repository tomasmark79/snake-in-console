//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#pragma once
#include "Field.h"

static const short MAX_SNAKE_LENGTH = 256+1;
static const int stepDivider = 1;

class Snake
{
    int id;
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
    Snake(int id, Field& field);
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

