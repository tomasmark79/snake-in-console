//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
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
