#include "Snake.h"
#include <iostream>
#include <windows.h> // Beep

Snake:: Snake(Field& field)
   : fie(&field)
{
    // snake baby will born here
    this->length = 0;
    this->xArr[this->length] = this->fie->getFieldWidth()/2;
    this->yArr[this->length] = this->fie->getFieldHeight()/2;

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

/** \brief
 *
 * \param
 * \param
 * \return > 0 ? index of eatten fruit
 *
 */

int Snake::whichFruitSnakeEatten(int* FruitX, int* FruitY, int fruitCount ) const
{
    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex ++)
    {
        if (xArr[0] ==  FruitX[fruitIndex] && yArr[0] == FruitY[fruitIndex])
            return fruitIndex + 1;
    }
    return 0;
}


/** \brief
 *
 * \return 1 wall conflic 2 self conflict
 *
 */
int Snake::getSnakeConflict() const
{
    if ((xArr[0] == 0 || xArr[0] == fie->getFieldWidth()-1) || (yArr[0] == 0 || yArr[0] == fie->getFieldHeight()-1))
    {
        {
            Beep(1900,50);
            Beep(1700,50);
            Beep(1500,50);
            Beep(1300,50);
        }
        return 1;
    }

    for (int tail = 0; tail < this->length; tail++)
    {
        if ( (xArr[0] == xTail[tail] && yArr[0] == yTail[tail]) )
        {
            {
                Beep(1900,50);
                Beep(1700,50);
                Beep(1500,50);
                Beep(1300,50);
            }
            return 2;
        }
    }
    return 0;
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
