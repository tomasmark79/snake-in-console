//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Snake.h"

Snake::Snake(int id, int stepDivider, int spawnX, int spawnY, int totalElements):
    id(id), stepDivider(stepDivider), length(0), direction((rand() % 4)),isDead(false),deadCode(0)
{
    int possibleSnakeLength = totalElements / 2;
    snakeCoosX =  std::make_unique <int[]> (possibleSnakeLength);
    snakeCoosY =  std::make_unique <int[]> (possibleSnakeLength);
    backupCoosX = std::make_unique <int[]> (possibleSnakeLength);
    backupCoosY = std::make_unique <int[]> (possibleSnakeLength);

    // snake baby will born here
    snakeCoosX.get()[0] = spawnX;
    snakeCoosY.get()[0] = spawnY;

// TODO (tomas#1#): Direction must be fot every snake different
}

Snake::~Snake()
{

}

void Snake::backupCoordinates()
{
    for (int bodyElement = 0; bodyElement < this->length; bodyElement ++)
    {
        backupCoosX.get()[bodyElement] = snakeCoosX.get()[bodyElement];
        backupCoosY.get()[bodyElement] = snakeCoosY.get()[bodyElement];
    }
}

void Snake::restoreCoordinatesShifted()
{
    for (int bodyElement = 0; bodyElement < this->length; bodyElement ++)
    {
        snakeCoosX.get()[bodyElement+1] = backupCoosX.get()[bodyElement];
        snakeCoosY.get()[bodyElement+1] = backupCoosY.get()[bodyElement];
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
        this->snakeCoosY.get()[0] -= this->stepDivider; // up
    else if (this->direction == 1)
        this->snakeCoosY.get()[0] +=this->stepDivider; // down
    else if (this->direction == 2)
        this->snakeCoosX.get()[0] -=this->stepDivider; // left
    else if (this->direction == 3)
        this->snakeCoosX.get()[0] +=this->stepDivider; // right

    this->restoreCoordinatesShifted();
}

int Snake::getElementOfEattenFruit(const int* FruitX, const int* FruitY, int fruitCount ) const
{
    if (this->isDead)
        return 0;

    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex ++)
    {
        if (this->snakeCoosX.get()[0] ==  FruitX[fruitIndex] && this->snakeCoosY.get()[0] == FruitY[fruitIndex])
            return fruitIndex + 1;
    }
    return 0;
}

