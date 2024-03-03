#include "Fruit.h"

Fruit::Fruit(Field& field)
    : fie(&field), fruitCount(0)
{
    this->addFruit();
}

int* Fruit::getFruitX() const
{
    return (int*)fruitXArr;
}

int* Fruit::getFruitY() const
{
    return (int*)fruitYArr;
}

int Fruit::getFruitCount() const
{
    return this->fruitCount;
}

const void Fruit::addFruit()
{
    int tempX = rand() % ( (this->fie->getFieldWidth()-2) +1);
    int tempY = rand() % ( (this->fie->getFieldHeight()-2) +1);
    this->fruitXArr[this->fruitCount] = tempX;
    this->fruitYArr[this->fruitCount] = tempY;
    this->fruitCount++;
}

const void Fruit::refreshFruit()
{
    int tempX = rand() % ( (this->fie->getFieldWidth()-2) +1);
    int tempY = rand() % ( (this->fie->getFieldHeight()-2) +1);
    this->fruitXArr[0] = tempX;
    this->fruitYArr[0] = tempY;
}
