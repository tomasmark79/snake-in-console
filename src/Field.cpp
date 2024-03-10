//MIT License
//
//Copyright (c) 2024 Tomas Mark
//

#include "Field.h"
#include <iostream>
Field::Field(short width, short height)
    : width(width), height(height)
{}

short Field::getFieldWidth() const
{
    // std::cout << this->width << std::endl;
    return this->width;
}

short Field::getFieldHeight() const
{
    // std::cout << this->height << std::endl;
    return this->height;
}

int Field::getAreaElements() const
{
    return  this->width * this->height;
}
