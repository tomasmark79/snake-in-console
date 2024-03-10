//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Fruit.h"

Fruit::Fruit(double fruitEmptiness, std::shared_ptr<Field> field)
    :fie(field), totalFruits(0),
    fruitXArr(new int [fie->getAreaElements()]),
    fruitYArr(new int [fie->getAreaElements()])
{
    // count with double precission for fruit emptiness
    int smartAlocMemory =
        static_cast<double>(fie->getFieldWidth())
        * static_cast<double>(fie->getFieldHeight()) / fruitEmptiness;

//    fruitXArr = new int[smartAlocMemory];
//    fruitYArr = new int[smartAlocMemory];

    // seed fruit
    for (int i = 0; i < smartAlocMemory; i ++)
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

void Fruit::addFruitItem()
{
    this->fruitXArr[this->totalFruits] = getRandomFruitX();
    this->fruitYArr[this->totalFruits] = getRandomFruitY();
    this->totalFruits++;
}

void Fruit::refreshFruit(int refreshIndex)
{
    this->fruitXArr[refreshIndex] = getRandomFruitX();
    this->fruitYArr[refreshIndex] = getRandomFruitY();
}
