//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#pragma once
class Field
{
    int width;
    int height;
public:
    Field(short width, short height)
        : width(width), height(height) {};

    int  getFieldWidth() const
    {
        return this->width;
    };

    int getFieldHeight() const
    {
        return this->height;
    };

    int getAreaElements() const
    {
        return this->width * this->height;
    };
};
