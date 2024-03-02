#include "Graphics.h"
#include "Compiler.h"
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

const void Graphics::printVerticallyCenteredText(int row, std::string text) const
{
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        COORD{ (this->width / 2) - (text.length() / 2), row });
    cout << text << endl;
}

const void Graphics::printHelp() const
{
    Compiler compiler;
    system("cls");
    this->printVerticallyCenteredText(4, "Help");
    this->printVerticallyCenteredText(5, "______________________________________");
    this->printVerticallyCenteredText(5, "Compiled with Gcc v. " + compiler.getCppCompilerV());
    this->printVerticallyCenteredText(6, "______________________________________");
    this->printVerticallyCenteredText(7, "Snake control");
    this->printVerticallyCenteredText(8, "by W A S D keys");
    this->printVerticallyCenteredText(9, "______________________________________");
    this->printVerticallyCenteredText(10, "for educational purpose");
    this->printVerticallyCenteredText(11, "Copyright (c) 2024 Tomas Mark");
    this->printVerticallyCenteredText(14, "press ENTER to go back to the game");

//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ this->width/2, this->height/2 });
//    cout << "Help" << endl;
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ this->width/2-9, this->height/2+1 });
//    cout << "Compiled with gnu gcc version " << compiler << endl;
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ this->width/2-9, this->height/2+2 });
//    cout << "---------------------------------------------" << endl;
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ this->width/2-9, this->height/2+3 });
//    cout << "Snake control is provided by W A S D keys" << endl;
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ this->width/2-9, this->height/2+4 });
//    cout << "---------------------------------------------" << endl;


    std::cin.get();
}
