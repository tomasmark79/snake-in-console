//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Fruit.h"

Fruit::Fruit(double fruitEmptiness, Field& field)
    : fie(&field), totalFruits(0)
{

    int neededMemory =
          (double)field.getFieldWidth()
        * (double)field.getFieldHeight()
        / (double)fruitEmptiness;

    fruitXArr = new int[neededMemory];
    fruitYArr = new int[neededMemory];

    // seed fruit
    for (int i = 0; i < neededMemory; i ++)
        this->addFruitItem();
}

Fruit::~Fruit()
{
    delete [] fruitYArr;
    delete [] fruitXArr;
}

const int* Fruit::getFruitX() const
{
    return /*(int*)*/fruitXArr;
}

const int* Fruit::getFruitY() const
{
    return /*(int*)*/fruitYArr;
}

int Fruit::getTotalFruit() const
{
    return this->totalFruits;
}

int Fruit::getRandomFruitX() const
{
    return (rand() % (this->fie->getFieldWidth()-2) ) + 1;
}

int Fruit::getRandomFruitY() const
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
