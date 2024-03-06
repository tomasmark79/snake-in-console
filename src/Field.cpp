//MIT License
//
//Copyright (c) 2024 Tomas Mark
//

#include "Field.h"

Field::Field(short width, short height)
    : width(width), height(height)
{}

short Field::getFieldWidth() const
{
    return this->width;
}
short Field::getFieldHeight() const
{
    return this->height;
}
