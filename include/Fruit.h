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
    std::shared_ptr<Field> fie; // Field* fie;

    int totalFruits;
    int* fruitXArr;// [MAX_FRUITS+1];
    int* fruitYArr;// [MAX_FRUITS+1];
public:

    Fruit(double fruitEmptiness, std::shared_ptr<Field> field);

    ~Fruit();
    const int* getFruitX() const;
    const int* getFruitY() const;
    int getRandomFruitX() const;
    int getRandomFruitY() const;
    int getTotalFruit() const;

    void addFruitItem();
    void refreshFruit(int refreshIndex);
};
