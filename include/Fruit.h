#ifndef FRUIT_H
#define FRUIT_H
#include "Field.h"

static const int MAX_FRUITS_IN_FIELD = 8;

class Fruit
{
    Field* fie;
    int fruitCount;

    int fruitXArr[MAX_FRUITS_IN_FIELD];
    int fruitYArr[MAX_FRUITS_IN_FIELD];

public:
    Fruit(Field& field);
    int* getFruitX() const;
    int* getFruitY() const;
    int getFruitCount() const;

    const void addFruit();
    const void refreshFruit();


};

#endif // FRUIT_H
