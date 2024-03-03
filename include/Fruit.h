#ifndef FRUIT_H
#define FRUIT_H
#include "Field.h"

static const int MAX_FRUITS_IN_FIELD = 50;

class Fruit
{
    Field* fie;
    int fruitCount;

    int fruitXArr[MAX_FRUITS_IN_FIELD+1];
    int fruitYArr[MAX_FRUITS_IN_FIELD+1];

public:
    Fruit(Field& field);
    int* getFruitX() const;
    int* getFruitY() const;
    int getFruitCount() const;

    const void addFruit();
    const void refreshFruit(int refreshIndex);


};

#endif // FRUIT_H
