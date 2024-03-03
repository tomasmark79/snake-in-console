#include "Snake.h"
#include <iostream>
#include <windows.h> // Beep

Snake:: Snake(Field& field)
    : fie(&field), snakeLength(0)
{
    // snake baby will born here
    this->xArr[this->snakeLength] = this->fie->getFieldWidth()/2;
    this->yArr[this->snakeLength] = this->fie->getFieldHeight()/2;

    // random first direction of snake baby
    this->setSnakeWay(rand() % 3);
}

const int* Snake::getSnakeX() const
{
    return (int*)this->xArr;
}
const int* Snake::getSnakeY()  const
{
    return (int*)this->yArr;
}
const int Snake::getSnakeLength() const
{
    return this->snakeLength;
}
const int Snake::getSnakeDirection() const
{
    return this->snakeDirection;
}

const int Snake::whichFruitSnakeEatten(const int* FruitX, const int* FruitY, int fruitCount ) const
{
    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex ++)
    {
        if (xArr[0] ==  FruitX[fruitIndex] && yArr[0] == FruitY[fruitIndex])
            return fruitIndex + 1;
    }
    return 0;
}

const int Snake::checkSnakeConflict() const
{
    // hitting the wall check
    if ((xArr[0] == 0 || xArr[0] == fie->getFieldWidth()-1) ||
            (yArr[0] == 0 || yArr[0] == fie->getFieldHeight()-1))
    {
        Beep(1400,300);
        return 1;
    }

    // hitting self tail check
    for (int tail = 0; tail < this->snakeLength; tail++)
    {
        if ( (xArr[0] == xTail[tail] && yArr[0] == yTail[tail]) )
        {
            {
                Beep(1900,50);
            }
            return 2;
        }
    }
    return 0;
}

const void Snake::addTail()
{
    this->snakeLength+=1;
}

const void Snake::setSnakeWay(int directionTaken)
{
    if (directionTaken >=0 && directionTaken <= 3)
        this->snakeDirection = directionTaken;

    Beep(500,2);

    // store tail axis
    for (int i = 0; i < snakeLength; i ++)
    {
        xTail[i] = xArr[i];
        yTail[i] = yArr[i];
    }

    switch(this->snakeDirection)
    {
    case 0:
        // code for arrow up
        yArr[0] -=stepDivider;
        break;
    case 1:
        // code for arrow down
        yArr[0] +=stepDivider;
        break;
    case 2:
        // code for arrow left
        xArr[0] -=stepDivider;
        break;
    case 3:
        // code for arrow right
        xArr[0] +=stepDivider;
        break;
    default:
        // no movement
        break;
    }

    // restore tail axis
    for (int i = 0; i < snakeLength; i ++)
    {
        xArr[i+1] = xTail[i];
        yArr[i+1] = yTail[i];
    }
}
