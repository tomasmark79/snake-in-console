//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Animal.h"
#include "Field.h"
#include <memory>
#include <vector>

static const short MAX_SNAKE_LENGTH = 256+1;
static const int stepDivider = 1;

class Snake : public Animal
{
    std::shared_ptr<std::vector<std::shared_ptr<Snake>>> snakes;
    int totalSnakes;
    int id;
    std::shared_ptr<Field> fie; // Field* fie;
    int snakeLength;
    bool isDie;
    int dieReason;
    int snakeDirection;
    int snakeCoosX[MAX_SNAKE_LENGTH];
    int snakeCoosY[MAX_SNAKE_LENGTH];
    int backupCoosX[MAX_SNAKE_LENGTH];
    int backupCoosY[MAX_SNAKE_LENGTH];

    void inhumeSnake();
    void backupSnakeCoordinates();
    void restoreSnakeCoordinatesShifted();
    bool isStepBack(int directionTaken) const;

public:
    Snake(std::shared_ptr<std::vector<std::shared_ptr<Snake>>> snakes,
          int totalSnakes, int id, std::shared_ptr<Field> field);

    void setSnakeDirectionAndShift(int direction);

    void setSnakeDie();
    bool isSnakeDie() const;

    int isSnakeInConflict();
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
    int getSnakeDieReason() const;



};

