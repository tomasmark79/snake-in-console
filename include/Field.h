//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
class Field
{
    short width;
    short height;
public:
    Field(short width, short height)
    : width(width), height(height)
{}
;


    short getFieldWidth() const
    {
        return this->width;
    };
    short getFieldHeight() const
    {
        return this->height;
    };

    int getAreaElements() const
    {
    return  this->width * this->height;
    };
};
