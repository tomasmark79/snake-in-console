#pragma once

class Field
{
    int width;
    int height;

public:
    Field(int width, int height);
    const void setBorders();

    int getFieldWidth() const
    {
        return this->width;

    };
    int getFieldHeight() const
    {
        return this->height;
    };

    const void drawField();

};

