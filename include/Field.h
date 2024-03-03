#pragma once
#include <cstdlib>
class Field
{
    short width;
    short height;
public:
    Field(short width, short height);
    short getFieldWidth() const;
    short getFieldHeight() const;
};
