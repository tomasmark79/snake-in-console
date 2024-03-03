//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include <exception>
#include "Graphics.h"
#include "Compiler.h"
#include <iostream>
#include <windows.h> //SetConsoleCursorPosition
#include <string>
#include <limits>

using std::cout;
using std::endl;
using std::string;

Graphics::Graphics(Field& field)
    : fie(&field)
{
    this->clearScreen();
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

const void Graphics::clearScreen() const
{
    system("cls");
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
    short currentRow = consoleInfo.dwCursorPosition.Y;

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

    this->clearScreen();
    {
        this->coutVCAWCoo(3, "Snake-In-Console");
        this->coutVCAWCoo(4, "0.0.2");
        this->coutVCAWCoo(5, "______________________________________");
        this->coutVCAWCoo(5, "Compiled with Gcc v. " + compiler.getCppCompilerV());
        this->coutVCAWCoo(6, "______________________________________");
        this->coutVCAWCoo(7, "Snake control");
        this->coutVCAWCoo(8, "by W A S D keys");
        this->coutVCAWCoo(9, "______________________________________");
        this->coutVCAWCoo(10, "for educational purpose");
        this->coutVCAWCoo(11, "Copyright (c) 2024 Tomas Mark");
        this->coutVCAWCoo(14, "press ENTER");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->clearScreen();
}

const void Graphics::coutGOver(int reason) const
{
    this->clearScreen();
    {
        this->coutVCAWCoo(7, "Game Over");
        if (reason == 1)
            this->coutVCAWCoo(9, "You hit a wall!");
        if (reason == 2)
            this->coutVCAWCoo(9, "You ate yourself!");
        if (reason == 3)
            this->coutVCAWCoo(9, "You interrupted game by pressing key R!");
        this->coutVCAWCoo(14, "PRESS ENTER");

    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->clearScreen();
}

