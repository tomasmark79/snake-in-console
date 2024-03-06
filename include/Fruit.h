//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"

static const int MAX_FRUITS = 1050;

class Fruit
{
    Field* fie;
    int totalFruits;
    int* fruitXArr;// [MAX_FRUITS+1];
    int* fruitYArr;// [MAX_FRUITS+1];
public:
    Fruit(double fruitEmptiness, Field& field);
    ~Fruit();
    const int* getFruitX() const;
    const int* getFruitY() const;
    const int getRandomFruitX() const;
    const int getRandomFruitY() const;
    const int getTotalFruit() const;

    const void addFruitItem();
    const void refreshFruit(int refreshIndex);
};
