//MIT License
//
//Copyright (c) 2024 Tomas Mark
//
#include <exception>
#include "Graphic.h"
#include <iostream>
#include <windows.h> //SetConsoleCursorPosition
#include <limits>
#include <Cpp.h>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

Graphic::Graphic(int totalW, int totalH)
    :totalW(totalW), totalH(totalH),
     videoBuffer(new char* [ totalH ])
{
    this->clearScreen();
    for (int i = 0; i < totalH; i++)
    {
        this->videoBuffer[i] = new char[ totalW ];
    }
}
Graphic::~Graphic()
{
    for (int i = 0; i < totalH; i++)
    {
        delete videoBuffer[i];
    }
    delete [] videoBuffer;
}

void Graphic::clearScreen() const
{
    system("cls");
}

void Graphic::clearVideoBuffer() const
{
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
    for (int i = 0; i < totalH; i++)
    {
        for (int j = 0; j < totalW; j++)
        {
            this->videoBuffer[i][j] = ' ';
        }
        cout << endl;
    }
}

void Graphic::addWallsToVideoBuffer() const
{
    const char wallVMaterial = '|';
    const char wallHMaterial = '-';
    //    const char wallCornerMaterialSlash = '\\';
    //    const char wallCornerMaterialBackSlash = '/';

    for (int row = 1; row < totalW-1; row++)
    {
        this->videoBuffer[0][row] = wallHMaterial; // left column
        this->videoBuffer[totalH-1][row] = wallHMaterial;
    }
    for (int col = 1; col < totalH-1; col++)
    {
        this->videoBuffer[col][0] = wallVMaterial; // top row
        this->videoBuffer[col][totalW-1] = wallVMaterial;
    }
}

void Graphic::addSnakeToVideoBuffer(const int id, const int* x, const int* y, int snakeLength, bool isDie)
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

void Graphic::addFruitToVideoBuffer(const int* x, const int* y, int totalFruits)
{
    for (int fruitElement = 0; fruitElement < totalFruits; fruitElement++)
    {
        this->videoBuffer[y [fruitElement] ] [x [fruitElement] ] = ':';
    }
}

void Graphic::redrawVideoBuffer() const
{
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
    for (int y = 0; y < totalH; y++)
    {
        for (int x = 0; x < totalW; x++)
        {
            cout << this->videoBuffer[y][x];
        }
        cout << endl;
    }
}

void Graphic::Cout(std::string msg) const
{
    cout << msg << endl;
}

void Graphic::coutVCentered(string text) const
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
    short currentRow = consoleInfo.dwCursorPosition.Y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),COORD
    {
        (short)( (totalW / 2) - (text.length() / 2) ),
        currentRow
    });

    // color == 0 ? (cout << text << endl) : (cout << dye::aqua_on_yellow(text) << endl);
    cout << text << endl;

}

void Graphic::coutVCAWCoo(short row, string text) const
{
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        COORD
    {
        (short)( (totalW / 2) - (text.length() / 2) ),
        row
    }
    );
    cout << text << endl;
}

void Graphic::coutVerticalCenteredMultilineString(int startAtRow, string multilineString) const
{
    std::istringstream iss(multilineString);
    string line;
    while (std::getline(iss, line))
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD
        { (short)( (totalW / 2) - (line.length() / 2) ), static_cast<short>(startAtRow++) } );
        cout << line << endl;
    }
}


void Graphic::coutHelp() const
{
    this->clearScreen();
    {
        std::cout << getAppBanner();
        this->coutVCAWCoo(13, "-------keyb control------");
        this->coutVCAWCoo(14, "Snake 1 - 'w' 's' 'a' 'd'");
        this->coutVCAWCoo(15, "Snake 2 - 'i' 'k' 'j' 'l'");
        this->coutVCAWCoo(16, "Snake 3 - '[' ''' ';' '\\'");
        this->coutVCAWCoo(17, "Snake 4 - '8' '5' '4' '3'");
        this->coutVCAWCoo(19, "PRESS ENTER TO CONTINUE");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->clearScreen();
}

void Graphic::coutGameOver() const
{
    coutVerticalCenteredMultilineString(9, getGameOverBanner());
    coutVerticalCenteredMultilineString(15, "\n\nPRESS ENTER TO CONTINUE\n\n");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->clearScreen();
}

string getGameOverBanner()
{
    return
        "_____ _____ _____ _____    _____ _____ _____ _____\n"
        "|   __|  _  |     |   __|  |     |  |  |   __| __  |\n"
        "|  |  |     | | | |   __|  |  |  |  |  |   __|    -|\n"
        "|_____|__|__|_|_|_|_____|  |_____|\\___/|_____|__|__|\n";
}

string getAppBanner()
{
    // 11 rows
    Cpp cpp;
    return
        "----------------------------------------\n"
        "Welcome to the game\n"
        " ___              _\n"
        "/ __| _ _   __ _ | |_____\n"
        "\\__ \\| ' \\ / _` || / / -_)\n"
        "|___/|_||_|\\__/_||_\\_\\___| in console\n"
        "----------------------------------------\n"
        "Copyright (c) 2024 Tomas Mark\n"
        "tomas@digitalspace.name\n"
        "Enjoy this example of OOP " + cpp.getCppV() + " code!\n"
        "build v0.0.3\n";
}
