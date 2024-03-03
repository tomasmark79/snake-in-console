#include <exception>
#include "Graphics.h"
#include "Compiler.h"
#include <iostream>
#include <windows.h> //SetConsoleCursorPosition
#include <string>

using std::cout;
using std::endl;
using std::string;

Graphics::Graphics(Field& field)
    : fie(&field)
{
    this->buffer = new char*[ this->fie->getFieldHeight() ];
    for (int i = 0; i < this->fie->getFieldHeight(); i++)
    {
        this->buffer[i] = new char[this->fie->getFieldWidth()];
    }
}
Graphics::~Graphics()
{
    for (int i = 0; i < this->fie->getFieldHeight(); i++)
    {
        delete buffer[i];
    }
    delete [] buffer;
}

const void Graphics::clearBuffer() const
{
    for (int i = 0; i < this->fie->getFieldHeight(); i++)
    {
        for (int j = 0; j < this->fie->getFieldWidth(); j++)
        {
            this->buffer[i][j] = ' ';
        }
        cout << endl;
    }
}

const void Graphics::addWallsToBuffer() const
{
    for (int row = 0; row < this->fie->getFieldWidth(); row++)
    {
        this->buffer[0][row] = '#'; // left column
        this->buffer[this->fie->getFieldHeight()-1][row] = '#';
    }
    for (int col = 0; col < this->fie->getFieldHeight(); col++)
    {
        this->buffer[col][0] = '#'; // top row
        this->buffer[col][this->fie->getFieldWidth()-1] = '#';
    }
}

const void Graphics::addSnakeToBuffer(int* x, int* y, int length)
{
    for (int tail = 0; tail <= length; tail++)
    {
        this->buffer[y [tail] ] [x [tail] ] = '*';
    }
}

const void Graphics::addFruitToBuffer(int* x, int* y, int fruitCount)
{
    try
    {
        for (int i = 0; i < fruitCount; i++)
        {
            this->buffer[y [i] ] [x [i] ] = '@';
        }
    }
    catch (std::exception& e)
    {
        cout << e.what();
    }
}

const void Graphics::redrawBuffer() const
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
    for (int i = 0; i < this->fie->getFieldHeight(); i++)
    {
        for (int j = 0; j < this->fie->getFieldWidth(); j++)
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

const void Graphics::prntVrtCenText(short row, std::string text) const
{
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        COORD
    {
        (short)( (this->fie->getFieldWidth() / 2) - (text.length() / 2) ),
        row
    }
    );
    cout << text << endl;
}

const void Graphics::printHelp() const
{
    Compiler compiler;

    system("cls");
    this->prntVrtCenText(3, "Snake++");
    this->prntVrtCenText(4, "0.0.1");
    this->prntVrtCenText(5, "______________________________________");
    this->prntVrtCenText(5, "Compiled with Gcc v. " + compiler.getCppCompilerV());
    this->prntVrtCenText(6, "______________________________________");
    this->prntVrtCenText(7, "Snake control");
    this->prntVrtCenText(8, "by W A S D keys");
    this->prntVrtCenText(9, "______________________________________");
    this->prntVrtCenText(10, "for educational purpose");
    this->prntVrtCenText(11, "Copyright (c) 2024 Tomas Mark");
    this->prntVrtCenText(14, "press ENTER to go back to the game");
    std::cin.get();
}

const void Graphics::prntGameOver(int reason) const
{
    system("cls");
    this->prntVrtCenText(7, "Game Over");

    if (reason == 1)
        this->prntVrtCenText(9, "Wall conflict!");

    if (reason == 2)
        this->prntVrtCenText(9, "Self eating conflict!");

    if (reason == 3)
        this->prntVrtCenText(9, "Pressed key B!");

    this->prntVrtCenText(14, "press ENTER to start game again");
    std::cin.clear();
    std::cin.get();
}

int Graphics::getScreenWidth() const
{
    return this->fie->getFieldWidth();
}

int Graphics::getScreenHeight() const
{
    return this->fie->getFieldHeight();
}

