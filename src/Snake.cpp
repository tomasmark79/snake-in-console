#include "Snake.h"
#include <iostream>
#include <windows.h> // Beep

Snake:: Snake(Field& field)
    : fie(&field), snakeLength(0)
{
    // snake baby will born here
    this->snakeCoosX[this->snakeLength] = this->fie->getFieldWidth()/2;
    this->snakeCoosY[this->snakeLength] = this->fie->getFieldHeight()/2;

    // random first direction of snake baby
    this->setSnakeDirectionAndShift(rand() % 3);
}

const void Snake::backupSnakeCoordinates()
{
    for (int bodyElement = 0; bodyElement < this->snakeLength; bodyElement ++)
    {
        backupCoosX[bodyElement] = snakeCoosX[bodyElement];
        backupCoosY[bodyElement] = snakeCoosY[bodyElement];
    }
}

const void Snake::restoreSnakeCoordinatesShifted()
{
    for (int bodyElement = 0; bodyElement < this->snakeLength; bodyElement ++)
    {
        snakeCoosX[bodyElement+1] = backupCoosX[bodyElement];
        snakeCoosY[bodyElement+1] = backupCoosY[bodyElement];
    }
}

// step to back? - doesn't allow for Snake ;-)
const bool Snake::isStepBack(int directionTaken) const
{
    if (this->snakeLength > 0)
    {
        if (    (this->snakeDirection == 0 && directionTaken == 1) ||      // up can't down
                (this->snakeDirection == 1 && directionTaken == 0) ||   // down con't up
                (this->snakeDirection == 2 && directionTaken == 3) ||   // left can't right
                (this->snakeDirection == 3 && directionTaken == 2) )    // and vice versa
        {
            Beep(1700,75);
            Beep(1400,75);
            return true;
        }
    }
    return false;
}

const void Snake::setSnakeDirectionAndShift(int directionTaken)
{
    Beep(500,2);

    if(this->isStepBack(directionTaken))
        return;

    if (directionTaken >= 0 && directionTaken <= 3) // allowed directions
        this->snakeDirection = directionTaken;

    this->backupSnakeCoordinates();

    if (this->snakeDirection == 0)
        snakeCoosY[0] -=stepDivider; // up
    else if (this->snakeDirection == 1)
        snakeCoosY[0] +=stepDivider; // down
    else if (this->snakeDirection == 2)
        snakeCoosX[0] -=stepDivider; // left
    else if (this->snakeDirection == 3)
        snakeCoosX[0] +=stepDivider; // right

    this->restoreSnakeCoordinatesShifted();
}

const int Snake::isSnakeInConflict() const
{
    if ((snakeCoosX[0] == 0 || snakeCoosX[0] == fie->getFieldWidth()-1) ||
            (snakeCoosY[0] == 0 || snakeCoosY[0] == fie->getFieldHeight()-1))
    {
        Beep(1400,300);
        return 1; // hitting wall
    }

    for (int tail = 0; tail < this->snakeLength; tail++)
    {
        if ( (snakeCoosX[0] == backupCoosX[tail] &&
                snakeCoosY[0] == backupCoosY[tail]) )
        {
            {
                Beep(1900,50);
            }
            return 2; // eats itsefl
        }
    }
    return 0; // free way
}

const int Snake::getElementOfEattenFruit(const int* FruitX, const int* FruitY, int fruitCount ) const
{
    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex ++)
    {
        if (snakeCoosX[0] ==  FruitX[fruitIndex] && snakeCoosY[0] == FruitY[fruitIndex])
            return fruitIndex + 1;
    }
    return 0;
}

const void Snake::growUpSnake()
{
    this->snakeLength+=1;
}

const int* Snake::getSnakeX() const
{
    return (int*)this->snakeCoosX;
}

const int* Snake::getSnakeY()  const
{
    return (int*)this->snakeCoosY;
}

const int Snake::getSnakeLength() const
{
    return this->snakeLength;
}

const int Snake::getSnakeDirection() const
{
    return this->snakeDirection;
}


