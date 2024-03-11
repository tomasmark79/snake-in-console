//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include <map>
#include <string>
#include <memory>

using std::map;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;

static const short MAX_SNAKE_LENGTH = 256+1;

class Snake
{
    int id;
    int stepDivider;
    int length;
    int direction;
    bool isDead;
    int deadCode;

    const map<int, string> deadDescription
    {
        {0, "is living"}, {1, "wall"}, {2, "self"}, {3, "another Snake"}
    };

    shared_ptr<int[]> snakeCoosX;
    shared_ptr<int[]> snakeCoosY;
    shared_ptr<int[]> backupCoosX;
    shared_ptr<int[]> backupCoosY;

    void inhumeSnake();
    void backupCoordinates();
    void restoreCoordinatesShifted();
    bool isStepBack(int directionPassed) const;

public:
    Snake(int id, int stepDivider, int spawnX, int spawnY, int totalElements);
    ~Snake();
    void setMyDirectionAndShift(int directionPassed);

    int getDirection() const
    {
        return this->direction;
    };

    void setDeadAndCode(int deadCode)
    {
        this->deadCode = deadCode;
        this->isDead = true;
    };

    int getDeadCode() const
    {
        return this->deadCode;
    };

    bool getIsDead() const
    {
        return this->isDead;
    };

    string getDeadDescripion() const
    {
        return this->deadDescription.at(deadCode);
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
        this->length+=1;
    };

    int getLength() const
    {
        return this->length;
    };

    int getXHead() const
    {
        return this->snakeCoosX[0];
    };

    int getYHead() const
    {
        return this->snakeCoosY[0];
    }

    const int* getX() const
    {
        return this->snakeCoosX.get();
    };

    const int* getY() const
    {
        return this->snakeCoosY.get();
    };

    const int* getBackupX() const
    {
        return this->backupCoosX.get();
    };

    const int* getBackupY() const
    {
        return this->backupCoosY.get();
    };


};

