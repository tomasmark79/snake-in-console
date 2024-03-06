//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

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
