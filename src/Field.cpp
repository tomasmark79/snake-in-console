#include "Field.h"

Field::Field(short width, short height)
    : width(width), height(height)
{}

const short Field::getFieldWidth() const
{
    return this->width;
}
const short Field::getFieldHeight() const
{
    return this->height;
}
