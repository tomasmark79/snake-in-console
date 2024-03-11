#include "Animal.h"

Animal::Animal(
)
{
    //ctor
}

Animal::~Animal()
{
    //dtor
}

void Animal::addAnimal(int animalType)
{
    if (animalType = 0) // Snake
    {
        if (totalAnimals == 0)
        {
            snakes = make_shared<vector<shared_ptr<Snake>>>(1);
        }
        else
        {
            snakes->emplace_back(make_shared<Snake>());
        }
    }
    totalAnimals++;
}
