//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Snake.h"
#include <iostream>
#include <windows.h> // Beep

Snake::Snake(int id, int spawnX, int spawnY)
    :   id(id),
        length(0),
        isDie(false),
        snakeDirection((rand() % 4))
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
bool Snake::isStepBack(int directionTaken) const
{
    if (this->length > 0)
    {
        if (    (this->snakeDirection == 0 && directionTaken == 1) ||      // up can't down
                (this->snakeDirection == 1 && directionTaken == 0) ||   // down con't up
                (this->snakeDirection == 2 && directionTaken == 3) ||   // left can't right
                (this->snakeDirection == 3 && directionTaken == 2) )    // and vice versa
        {
            Beep(1700,20);
            Beep(1400,14);
            return true;
        }
    }
    return false;
}

void Snake::setMyDirectionAndShift(int directionTaken)
{
    if (this->isDie)
        return;

    Beep(500,2);

    if(this->isStepBack(directionTaken))
        return;

    if (directionTaken >= 0 && directionTaken <= 3) // allowed directions
        this->snakeDirection = directionTaken;

    this->backupCoordinates();

    if (this->snakeDirection == 0)
        snakeCoosY[0] -=stepDivider; // up
    else if (this->snakeDirection == 1)
        snakeCoosY[0] +=stepDivider; // down
    else if (this->snakeDirection == 2)
        snakeCoosX[0] -=stepDivider; // left
    else if (this->snakeDirection == 3)
        snakeCoosX[0] +=stepDivider; // right

    this->restoreCoordinatesShifted();
}

void Snake::setMeDead()
{
    this->isDie = true;
}
bool Snake::amIDead() const
{
    return this->isDie;
}

int Snake::getElementOfEattenFruit(const int* FruitX, const int* FruitY, int fruitCount ) const
{
    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex ++)
    {
        if (snakeCoosX[0] ==  FruitX[fruitIndex] && snakeCoosY[0] == FruitY[fruitIndex])
            return fruitIndex + 1;
    }
    return 0;
}

void Snake::growUpSnake()
{
    this->length+=1;
}

const int* Snake::getSnakeX() const
{
    return /*(int*)*/this->snakeCoosX;
}

const int* Snake::getSnakeY()  const
{
    return /*(int*)*/this->snakeCoosY;
}

int Snake::getSnakeLength() const
{
    return this->length;
}

int Snake::getSnakeDirection() const
{
    return this->snakeDirection;
}

int Snake::getSnakeXHead() const
{
    return this->snakeCoosX[0];
}

int Snake::getSnakeYHead() const
{
    return this->snakeCoosY[0];
}

