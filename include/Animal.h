#pragma once
#include<memory>
#include<string>
#include<vector>
#include "Snake.h"

using std::shared_ptr;
using std::make_shared;
using std::vector;

class Animal
{
    int animalType;
    int totalAnimals;
    shared_ptr<vector<shared_ptr<Snake>>> snakes;


    // std::shared_ptr<Field> fie;
    public:
        Animal();
        virtual ~Animal();

        void addAnimal(int animalType);

};


