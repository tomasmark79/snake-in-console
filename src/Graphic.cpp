//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include <exception>
#include "Graphic.h"
#include <iostream>
#include <windows.h> //SetConsoleCursorPosition
#include <string>
#include <limits>

using std::cout;
using std::endl;
using std::string;

Graphic::Graphic(Field& field)
    : fie(&field)
{
    this->clearScreen();
    this->videoBuffer = new char*[ this->fie->getFieldHeight() ];
    for (int i = 0; i < this->fie->getFieldHeight(); i++)
    {
        this->videoBuffer[i] = new char[this->fie->getFieldWidth()];
    }
}
Graphic::~Graphic()
{
    for (int i = 0; i < this->fie->getFieldHeight(); i++)
    {
        delete videoBuffer[i];
    }
    delete [] videoBuffer;
}

const void Graphic::clearScreen() const
{
    system("cls");
}

const void Graphic::clearVideoBuffer() const
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

const void Graphic::addWallsToVideoBuffer() const
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

const void Graphic::addSnakeToVideoBuffer(const int id, const int* x, const int* y, int snakeLength, bool isDie)
{
    for (int bodyElement = 0; bodyElement <= snakeLength; bodyElement++)
    {
        if (!isDie)
        {
            this->videoBuffer[y [bodyElement] ] [x [bodyElement] ] =
                bodyElement == 0 ? char(id+1) : '0';
        }
        else
        {
            this->videoBuffer[y [bodyElement] ] [x [bodyElement] ] =
                bodyElement == 0 ? char(id+1) : 'X';

        }
    }
}

const void Graphic::addFruitToVideoBuffer(const int* x, const int* y, int totalFruits)
{
    for (int fruitElement = 0; fruitElement < totalFruits; fruitElement++)
    {
        this->videoBuffer[y [fruitElement] ] [x [fruitElement] ] = ':';
    }
}

const void Graphic::redrawVideoBuffer() const
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

const void Graphic::Cout(std::string msg) const
{
    cout << msg << endl;
}

const void Graphic::coutVCentered(std::string text) const
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
    short currentRow = consoleInfo.dwCursorPosition.Y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),COORD
    {
        (short)( (this->fie->getFieldWidth() / 2) - (text.length() / 2) ),
        currentRow
    });

    // color == 0 ? (cout << text << endl) : (cout << dye::aqua_on_yellow(text) << endl);
    cout << text << endl;

}

const void Graphic::coutVCAWCoo(short row, std::string text) const
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

const void Graphic::coutHelp() const
{
    this->clearScreen();
    {
        this->coutVCAWCoo(3, "----------------------------------------");
        this->coutVCAWCoo(4, "Welcome to the game                     ");
        this->coutVCAWCoo(5, "   ___              _                   ");
        this->coutVCAWCoo(6, "  / __| _ _   __ _ | |_____             ");
        this->coutVCAWCoo(7, "\\__ \\| ' \\ / _` || / / -_)           ");
        this->coutVCAWCoo(8, "|___/|_||_|\\__/_||_\\_\\___| in console");
        this->coutVCAWCoo(9, "----------------------------------------");
        this->coutVCAWCoo(11, "Copyright (c) 2024 Tomas Mark");
        this->coutVCAWCoo(12, "Enjoy this example of OOP C++ code!");

        this->coutVCAWCoo(14, "Snake 1 - 'w' 's' 'a' 'd'");
        this->coutVCAWCoo(15, "Snake 2 - 'i' 'k' 'j' 'l'");
        this->coutVCAWCoo(16, "Snake 3 - '[' ''' ';' '\\'");
        this->coutVCAWCoo(17, "Snake 4 - '8' '5' '4' '3'");
        this->coutVCAWCoo(19, "PRESS ENTER TO CONTINUE");

    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->clearScreen();
}

const void Graphic::coutGOver(int reason) const
{
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
    // this->clearScreen();
}

