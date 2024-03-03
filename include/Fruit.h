#pragma once
#include "Field.h"

static const int MAX_FRUITS = 50;

class Fruit
{
    Field* fie;
    int totalFruits;
    int fruitXArr[MAX_FRUITS+1];
    int fruitYArr[MAX_FRUITS+1];
public:
    Fruit(Field& field);
    const int* getFruitX() const;
    const int* getFruitY() const;
    const int getRandomFruitX() const;
    const int getRandomFruitY() const;
    const int getTotalFruit() const;

    const void addFruitItem();
    const void refreshFruit(int refreshIndex);
};
