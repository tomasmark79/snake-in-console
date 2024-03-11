//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include <memory>

using std::shared_ptr;
using std::make_unique;

class Fruit
{
    int totalW;
    int totalH;
    shared_ptr<int[]> fruitXArr;
    shared_ptr<int[]> fruitYArr;
    int totalFruits;
public:
    Fruit(double fruitEmptiness, int totalW, int totalH);
    Fruit(const Fruit& fruit);
    Fruit& operator=(const Fruit& fruit);
    ~Fruit();
    const int* getFruitX() const;
    const int* getFruitY() const;
    int getRandomFruitX() const;
    int getRandomFruitY() const;
    int getTotalFruit() const;

    void addFruitItem();
    void refreshFruit(int refreshIndex);
};
