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

#define DEBUG

int main()
{
    const int               PLAYER_ANSWER_TRESHHOLD = 5;
    const int               MAX_PLAYERS = 4;
    int totalPlayers    =   MAX_PLAYERS;
    std::string playerNames[MAX_PLAYERS+1];

    playerNames[0] = "Tomas";
        playerNames[1] = "is";
            playerNames[2] = "c++";
                playerNames[3] = "developer";

    int totalAnswers    = 0;
    int fieldWidth      = 80;
    int fieldHeight     = 35;
    int fruitEmptiness  = 2.5;  // more is less fruit
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Welcome to the game" << std::endl;
    std::cout << " ___              _"           << std::endl;
    std::cout << "/ __| _ _   __ _ | |_____"    << std::endl;
    std::cout << "\\__ \\| ' \\ / _` || / / -_)"   << std::endl;
    std::cout << "|___/|_||_|\\__/_||_\\_\\___| in console"   << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << std::endl;

#ifndef DEBUG

    totalAnswers = 0;
    do
    {
        if (totalAnswers == PLAYER_ANSWER_TRESHHOLD)
        {
            std::cout << "Game needs your correct inputs.";
            exit(0);
        }

        std::cout << "Enter number of player 1-4? ";
        std::cin >> totalPlayers;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalAnswers++;
    }
    while(totalPlayers < 1 || totalPlayers > 4);

    for (int playerId = 0; playerId < totalPlayers; playerId++)
    {
        std::cout << "Enter name of Snake " << playerId + 1 << "? ";
        std::cin >> playerNames[playerId];
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalAnswers++;
    }

    totalAnswers = 0;
    do
    {
        if (totalAnswers == PLAYER_ANSWER_TRESHHOLD)
        {
            std::cout << "Game needs your correct inputs.";
            exit(0);
        }

        std::cout << "Enter width of field. (min 20 recomended 80) ? ";
        std::cin >> fieldWidth;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalAnswers++;
    }
    while(fieldWidth < 20 || fieldWidth > 360);

    totalAnswers = 0;
    do
    {
        if (totalAnswers == PLAYER_ANSWER_TRESHHOLD)
        {
            std::cout << "Game needs your correct inputs.";
            exit(0);
        }

        std::cout << "Enter width of heihgt. (min 10 recomended 35) ? ";
        std::cin >> fieldHeight;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalAnswers++;
    }
    while(fieldHeight < 10 || fieldHeight > 360);


    totalAnswers = 0;
    do
    {
        if (totalAnswers == PLAYER_ANSWER_TRESHHOLD)
        {
            std::cout << "Game needs your correct inputs.";
            exit(0);
        }
        std::cout << "Enter fruit emptiness (min 1 recomended 2.5)? ";
        std::cin >> fruitEmptiness;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalAnswers++;
    }
    while(fruitEmptiness < 1 || fruitEmptiness > 10);

#endif

    while(true)
    {
        std::srand(std::time(0));
        Process gameSnake(fieldWidth, fieldHeight, fruitEmptiness, totalPlayers, playerNames);
        if (!gameSnake.isNextGameWanted())
            break;
    }
    return 0;
}


