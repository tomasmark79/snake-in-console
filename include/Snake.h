//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include <map>
#include <string>

using std::map;
using std::string;

static const short MAX_SNAKE_LENGTH = 256+1;

class Snake
{
    int id;
    int stepDivider;
    int length;
    int direction;
    bool isDead;
    int deadCode;
    const map<int, string> deadDescription { {0, "living"}, {1, "wall"}, {2, "self"}, {3, "another Snake"} };

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


    void setMyDirectionAndShift(int directionTaken);
    int getDirection() const
    {
        return direction;
    };

    void setMeDead()
    {
        isDead = true;
    };

    void setDeadCode(int deadCode)
    {
        deadCode = deadCode;
        this->setMeDead();
    };

    int getDeadCode() const
    {
        return deadCode;
    };

    bool amIDead() const
    {
        return isDead;
    };

    string getDeadDescripion() const
    {
        return deadDescription.at(deadCode);
    };

    // eat fruit and grow up
    int getElementOfEattenFruit
    (
        const int* FruitX,
        const int* FruitY,
        int fruitCount
    ) const;

    void growUp()
    {
        length+=1;
    };

    int getLength() const
    {
        return length;
    };

    int getXHead() const
    {
        return snakeCoosX[0];
    };

    int getYHead() const
    {
        return snakeCoosY[0];
    }

    const int* getX() const
    {
        return snakeCoosX;
    };

    const int* getY() const
    {
        return snakeCoosY;
    };
};

