#include "Snake.h"
#include <iostream>
#include <windows.h> // Beep

Snake:: Snake(int width, int height)
    :width(width), height(height)
{
    // snake baby will born here
    this->length = 0;
    this->xArr[this->length] = this->width/2;
    this->yArr[this->length] = this->height/2;

    // random first direction of snake baby
    std::srand(std::time(0));
    this->setSnakeWay(rand() % 3);
}

int* Snake::getSnakeX() const
{
    return (int*)this->xArr;
}
int* Snake::getSnakeY()  const
{
    return (int*)this->yArr;
}
int Snake::getSnakeLength() const
{
    return this->length;
}
int Snake::getSnakeDirection() const
{
    return this->direction;
}

const void Snake::addTail()
{
    this->length+=1;
}

const void Snake::setSnakeWay(int direction)
{
    if (direction >=0 && direction <= 3)
        this->direction = direction;

    Beep(500,2);

    // store tail axis
    for (int i = 0; i < length; i ++)
    {
        xTail[i] = xArr[i];
        yTail[i] = yArr[i];
    }

    switch(this->direction)
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
    for (int i = 0; i < length; i ++)
    {
        xArr[i+1] = xTail[i];
        yArr[i+1] = yTail[i];
    }
}
