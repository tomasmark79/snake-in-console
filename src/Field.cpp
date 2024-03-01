#include "Field.h"
#include <iostream>
// #include <windows.h> // SetConsoleCursorPosition

Field::Field(int width, int height)
    :width(width), height(height)
{

}

const void Field::setBorders()
{

    char matrix[this->height][this->width];
    for (int i=0; i<this->height; i++)
        for (int j=0; j<this->width; j++)
            matrix[i][j]=' ';

    for (int i=0; i<this->height; i++)
    {
        // plnime vertikaly
        matrix[i][0]='#';
        matrix[i][this->width-1]='#';

        for (int j=0; j<this->width; j++)
        {
            // plnime horizontaly
            matrix[0][j]='#';
            matrix[this->height-1][j]='#';

            // kreslime buffer
            std::cout << matrix[i][j];

        }
        std::cout << std::endl;
    }
}


