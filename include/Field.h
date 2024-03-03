#pragma once
#include <cstdlib>
class Field
{
    short width;
    short height;
public:
    Field(short width, short height);
    const short getFieldWidth() const;
    const short getFieldHeight() const;
};
