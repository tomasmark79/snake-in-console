#include "Fruit.h"

Fruit::Fruit(Field& field)
    : fie(&field), totalFruits(0)
{
    for (int i = 0; i < MAX_FRUITS; i ++)
        this->addFruitItem();
}

const int* Fruit::getFruitX() const
{
    return (int*)fruitXArr;
}

const int* Fruit::getFruitY() const
{
    return (int*)fruitYArr;
}

const int Fruit::getTotalFruit() const
{
    return this->totalFruits;
}

const int Fruit::getRandomFruitX() const
{
    return (rand() % (this->fie->getFieldWidth()-2) ) + 1;
}

const int Fruit::getRandomFruitY() const
{
    return (rand() % (this->fie->getFieldHeight()-2) ) + 1;
}

const void Fruit::addFruitItem()
{
    this->fruitXArr[this->totalFruits] = getRandomFruitX();
    this->fruitYArr[this->totalFruits] = getRandomFruitY();
    this->totalFruits++;
}

const void Fruit::refreshFruit(int refreshIndex)
{
    this->fruitXArr[refreshIndex] = getRandomFruitX();
    this->fruitYArr[refreshIndex] = getRandomFruitY();
}
