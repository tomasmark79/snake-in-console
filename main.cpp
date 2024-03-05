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

#include "Process.h"
#include <iostream>

// 4K screen
// #define WIDTH   (int)340
// #define HEIGHT  (int)75

#define WIDTH   (int)35
#define HEIGHT  (int)35
#define MAX_PLAYERS (int)4


//TO DO
// Pomer velikost
// Koeficient nasobku
// mnozstvi ovoce

int main()
{
    // Welcome to the Snake game

    int totalPlayers = 4;
    std::string playerNames[MAX_PLAYERS+1];
    playerNames[0] = "Snake 1";
    playerNames[1] = "Snake 2";
    playerNames[2] = "Snake 3";
    playerNames[3] = "Snake 4";

    // get total players
    do
    {
        std::cout << "Enter number of player 1-4? ";
        std::cin >> totalPlayers;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();

    }
    while(totalPlayers < 1 || totalPlayers > 4);

    // get player names
    for (int playerId = 0; playerId < totalPlayers; playerId++)
    {
        std::cout << "Enter name of Snake " << playerId + 1 << "? ";
        std::cin >> playerNames[playerId];
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // get field size
    int width;
    int height;

    std::cout << "Enter width of field. (recomended 80) ? ";
    std::cin >> width;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter width of heihgt. (recomended 40) ? ";
    std::cin >> height;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // fruit density
    int fruitEmptiness = 2.5;
    std::cout << "Enter fruit emptiness (recomended 2.5)? ";
    std::cin >> fruitEmptiness;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // start play the game
    while(true)
    {
        std::srand(std::time(0));
        Process gameSnake(width, height, fruitEmptiness, totalPlayers, playerNames);
        if (!gameSnake.isNextGameWanted())
            break;
    }
    return 0;
}


