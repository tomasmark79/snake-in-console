//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include <memory>

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
    int getRandomFruitX() const;
    int getRandomFruitY() const;
    int getTotalFruit() const;

    const void addFruitItem();
    const void refreshFruit(int refreshIndex);
};
