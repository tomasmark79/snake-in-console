//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
#include "Field.h"
#include <memory>

class Fruit
{
    int totalW;
    int totalH;
    std::shared_ptr<int[]> fruitXArr;
    std::shared_ptr<int[]> fruitYArr;
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
