//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Snake.h"
#include <iostream>

Snake::Snake(int id, int stepDivider, int spawnX, int spawnY):
    id(id), stepDivider(1), length(0), direction((rand() % 4)),isDead(false),deadCode(0)
{
    // snake baby will born here
    snakeCoosX[0] = spawnX;
    snakeCoosY[0] = spawnY;
}

void Snake::backupCoordinates()
{
    for (int bodyElement = 0; bodyElement < this->length; bodyElement ++)
    {
        backupCoosX[bodyElement] = snakeCoosX[bodyElement];
        backupCoosY[bodyElement] = snakeCoosY[bodyElement];
    }
}

void Snake::restoreCoordinatesShifted()
{
    for (int bodyElement = 0; bodyElement < this->length; bodyElement ++)
    {
        snakeCoosX[bodyElement+1] = backupCoosX[bodyElement];
        snakeCoosY[bodyElement+1] = backupCoosY[bodyElement];
    }
}

// step to back? - doesn't allow for Snake ;-)
bool Snake::isStepBack(int directionPassed) const
{
    if (this->isDead)
        return false;

    if (this->length > 0)
    {
        if (    (this->direction == 0 && directionPassed == 1) ||   // up can't down
                (this->direction == 1 && directionPassed == 0) ||   // down con't up
                (this->direction == 2 && directionPassed == 3) ||   // left can't right
                (this->direction == 3 && directionPassed == 2) )    // and vice versa
        {
            return true;
        }
    }
    return false;
}

void Snake::setMyDirectionAndShift(int directionPassed)
{
    if (this->isDead)
        return;

    if(this->isStepBack(directionPassed))
        return;

    if (directionPassed >= 0 && directionPassed <= 3) // allowed directions
        this->direction = directionPassed;

    this->backupCoordinates();

    if (this->direction == 0)
        snakeCoosY[0] -=stepDivider; // up
    else if (this->direction == 1)
        snakeCoosY[0] +=stepDivider; // down
    else if (this->direction == 2)
        snakeCoosX[0] -=stepDivider; // left
    else if (this->direction == 3)
        snakeCoosX[0] +=stepDivider; // right

    this->restoreCoordinatesShifted();
}

int Snake::getElementOfEattenFruit(const int* FruitX, const int* FruitY, int fruitCount ) const
{
    if (isDead)
        return 0;

    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex ++)
    {
        if (snakeCoosX[0] ==  FruitX[fruitIndex] && snakeCoosY[0] == FruitY[fruitIndex])
            return fruitIndex + 1;
    }
    return 0;
}

