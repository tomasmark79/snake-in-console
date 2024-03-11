//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include "Fruit.h"

Fruit::Fruit(double fruitEmptiness, int totalW, int totalH)
    :totalW(totalW), totalH(totalH),
     fruitXArr(make_unique <int[]> (totalW*totalH)), // contain coords in array of int which mean ammount of fruits
     fruitYArr(make_unique <int[]> (totalW*totalH)), // contain coords in array of int which mean ammount of fruits
     totalFruits(0)
{
    int smartAlocMemory = totalW*totalH/fruitEmptiness;

    // seed fruit
    for (int i = 0; i < smartAlocMemory; i ++)
        this->addFruitItem();
}

Fruit::~Fruit()
{
    fruitXArr.reset();
    fruitYArr.reset();
}

const int* Fruit::getFruitX() const
{
    return fruitXArr.get();
}

const int* Fruit::getFruitY() const
{
    return fruitYArr.get();
}

int Fruit::getTotalFruit() const
{
    return this->totalFruits;
}

int Fruit::getRandomFruitX() const
{
    return (rand() % (totalW-2) ) + 1;
}

int Fruit::getRandomFruitY() const
{
    return (rand() % (totalH-2) ) + 1;
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
