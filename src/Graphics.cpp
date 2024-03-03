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
    this->videoBuffer = new char*[ this->fie->getFieldHeight() ];
    for (int i = 0; i < this->fie->getFieldHeight(); i++)
    {
        this->videoBuffer[i] = new char[this->fie->getFieldWidth()];
    }
}
Graphics::~Graphics()
{
    for (int i = 0; i < this->fie->getFieldHeight(); i++)
    {
        delete videoBuffer[i];
    }
    delete [] videoBuffer;
}

const void Graphics::clearVideoBuffer() const
{
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
    for (int i = 0; i < this->fie->getFieldHeight(); i++)
    {
        for (int j = 0; j < this->fie->getFieldWidth(); j++)
        {
            this->videoBuffer[i][j] = ' ';
        }
        cout << endl;
    }
}

const void Graphics::addWallsToVideoBuffer() const
{
    const char wallVMaterial = '|';
    const char wallHMaterial = '-';
    //    const char wallCornerMaterialSlash = '\\';
    //    const char wallCornerMaterialBackSlash = '/';

    for (int row = 1; row < this->fie->getFieldWidth()-1; row++)
    {
        this->videoBuffer[0][row] = wallHMaterial; // left column
        this->videoBuffer[this->fie->getFieldHeight()-1][row] = wallHMaterial;
    }
    for (int col = 1; col < this->fie->getFieldHeight()-1; col++)
    {
        this->videoBuffer[col][0] = wallVMaterial; // top row
        this->videoBuffer[col][this->fie->getFieldWidth()-1] = wallVMaterial;
    }
}

const void Graphics::addSnakeToVideoBuffer(const int* x, const int* y, int snakeLength)
{
    for (int bodyElement = 0; bodyElement <= snakeLength; bodyElement++)
    {
        this->videoBuffer[y [bodyElement] ] [x [bodyElement] ] =
            bodyElement == 0 ? 'S' : '0';
    }
}

const void Graphics::addFruitToVideoBuffer(const int* x, const int* y, int totalFruits)
{
    for (int fruitElement = 0; fruitElement < totalFruits; fruitElement++)
    {
        this->videoBuffer[y [fruitElement] ] [x [fruitElement] ] = ':';
    }
}

const void Graphics::redrawVideoBuffer() const
{
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
    for (int y = 0; y < this->fie->getFieldHeight(); y++)
    {
        for (int x = 0; x < this->fie->getFieldWidth(); x++)
        {
            cout << this->videoBuffer[y][x];
        }
        cout << endl;
    }
}

const void Graphics::Cout(std::string msg) const
{
    cout << msg << endl;
}

const void Graphics::coutVCentered(std::string text) const
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
    int currentRow = consoleInfo.dwCursorPosition.Y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),COORD
    {
        (short)( (this->fie->getFieldWidth() / 2) - (text.length() / 2) ),
        currentRow
    }
    );
    cout << text << endl;
}

const void Graphics::coutVCAWCoo(short row, std::string text) const
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

const void Graphics::coutHelp() const
{
    Compiler compiler;

    system("cls");
    this->coutVCAWCoo(3, "Snake++");
    this->coutVCAWCoo(4, "0.0.1");
    this->coutVCAWCoo(5, "______________________________________");
    this->coutVCAWCoo(5, "Compiled with Gcc v. " + compiler.getCppCompilerV());
    this->coutVCAWCoo(6, "______________________________________");
    this->coutVCAWCoo(7, "Snake control");
    this->coutVCAWCoo(8, "by W A S D keys");
    this->coutVCAWCoo(9, "______________________________________");
    this->coutVCAWCoo(10, "in hope of educational purpose");
    this->coutVCAWCoo(11, "Copyright (c) 2024 Tomas Mark");
    this->coutVCAWCoo(14, "press ENTER");
    std::cin.clear();
    std::cin.get();
    system("cls");
}

const void Graphics::coutGOver(int reason) const
{
    system("cls");
    this->coutVCAWCoo(7, "Game Over");
    if (reason == 1)
        this->coutVCAWCoo(9, "You hit a wall!");
    if (reason == 2)
        this->coutVCAWCoo(9, "You ate yourself!");
    if (reason == 3)
        this->coutVCAWCoo(9, "You interrupted game by pressing key R!");
    this->coutVCAWCoo(14, "PRESS ENTER");
    std::cin.clear();
    std::cin.get();
    system("cls");
}

