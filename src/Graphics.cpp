#include "Graphics.h"
#include <iostream>
#include <windows.h> //SetConsoleCursorPosition
#include <string>
using std::cout;
using std::endl;
using std::string;

Graphics::Graphics(int width, int height)
    :width(width),height(height)
{
    this->buffer = new char*[ this->height];
    for (int i = 0; i < this->height; i++)
    {
        this->buffer[i] = new char[this->width];
    }
}
Graphics::~Graphics()
{
    for (int i = 0; i < height; i++)
    {
        delete buffer[i];
    }
    delete [] buffer;
}

const void Graphics::clearBuffer() const
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            this->buffer[i][j] = ' ';
        }
        cout << endl;
    }
}

const void Graphics::addWallsToBuffer() const
{
    for (int row = 0; row < this->width; row++)
    {
        this->buffer[0][row] = '#'; // left column
        this->buffer[this->height-1][row] = '#';
    }
    for (int col = 0; col < this->height; col++)
    {
        this->buffer[col][0] = '#'; // top row
        this->buffer[col][this->width-1] = '#';
    }
}

const void Graphics::addSnakeToBuffer(int* x, int* y, int length)
{
    for (int tail = 0; tail <= length; tail++)
    {
        this->buffer[y [tail] ] [x [tail] ] = '*';
    }
}

const void Graphics::redrawBuffer() const
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            cout << this->buffer[i][j];
        }
        cout << endl;
    }
}

const void Graphics::printInfo(std::string msg) const
{
    cout << msg;
}

