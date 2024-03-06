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
#include <random>

//#define DEBUG

constexpr int               MAX_PLAYERS = 4;
int totalPlayers    =       MAX_PLAYERS;
std::string playerNames    [MAX_PLAYERS];
const int                   PLAYER_ANSWER_TRESHHOLD = 5; // give 5 attempts for user to enter right values
const char* userfailed =    "\n\nGame needs your correct inputs.\n\n";
int fieldWidth      = 80;
int fieldHeight     = 35;
int fruitEmptiness  = 2.5;  // more is less fruit
template<typename T1>
T1 getNumericAnswerFromPlayer(std::string_view question, int min, int max, int attemptTreshold);
std::string getStringAnswerFromPlayer(std::string_view question, int min, int max, int attemptTreshold);
void printHead();

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    printHead();

    playerNames[0] = "Tomas";
    playerNames[1] = "writed";
    playerNames[2] = "C++";
    playerNames[3] = "Snake";

#ifndef DEBUG

    // Question 0
    std::string yesOrNo = getStringAnswerFromPlayer("Start immediately with default settings yes/no ?", 1, 3, PLAYER_ANSWER_TRESHHOLD);

    // or user can create custom game
    if (yesOrNo.compare("yes") == 0 || yesOrNo.compare("y") == 0)
    {
        ;
    }
    else
    {
        // question 1
        totalPlayers = getNumericAnswerFromPlayer<int>("Enter number of player 1-4 ? ", 1, 4, PLAYER_ANSWER_TRESHHOLD);

        // question 2
        for (int playerId = 0; playerId < totalPlayers; playerId++)
            playerNames[playerId] = getStringAnswerFromPlayer("Enter name of Snake ? ", 2, 20, PLAYER_ANSWER_TRESHHOLD);

        // question 3
        fieldWidth = getNumericAnswerFromPlayer<int>("Enter width of field. (min 20 recomended 80) ? ", 20, 360, PLAYER_ANSWER_TRESHHOLD);

        // quesrion 4
        fieldHeight = getNumericAnswerFromPlayer<int>("Enter width of heihgt. (min 10 recomended 35) ? ", 10, 360, PLAYER_ANSWER_TRESHHOLD);

        // quesrion 5
        fruitEmptiness = getNumericAnswerFromPlayer<double>("Enter fruit emptiness (min 1 recomended 2.5) ? ", 1, 10, PLAYER_ANSWER_TRESHHOLD);
    }

#endif

    // Start Game
    while(true)
    {
        Process gameSnake(fieldWidth, fieldHeight, fruitEmptiness, totalPlayers, playerNames);

        if (!gameSnake.isNextGameWanted())
            break;
    }
    return 0;
}

template<typename T1>
T1 getNumericAnswerFromPlayer(std::string_view question, int min, int max, int attemptTreshold)
{
    T1 value = 0;
    int totalAnswers = 0;
    do
    {
        if (totalAnswers == attemptTreshold)
        {
            std::cout << userfailed;
            throw std::runtime_error("User failed to provide valid input.");
        }
        std::cout << question;
        std::cin >> value;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalAnswers++;
    }
    while(value < min || value > max);
    return value;
}

std::string getStringAnswerFromPlayer(std::string_view question, int min, int max, int attemptTreshold)
{
    std::string answer = "";
    int totalAnswers = 0;
    do
    {
        if (totalAnswers == attemptTreshold)
        {
            std::cout << userfailed;
            throw std::runtime_error("User failed to provide valid input.");
        }
        std::cout << question;
        std::cin >> answer;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalAnswers++;
    }
    while((int)answer.length() < min || (int)answer.length() > max);
    return answer;
}

void printHead()
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Welcome to the game" << std::endl;
    std::cout << " ___              _"           << std::endl;
    std::cout << "/ __| _ _   __ _ | |_____"    << std::endl;
    std::cout << "\\__ \\| ' \\ / _` || / / -_)"   << std::endl;
    std::cout << "|___/|_||_|\\__/_||_\\_\\___| in console"   << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Copyright (c) 2024 Tomas Mark" << std::endl;
    std::cout << "tomas@digitalspace.name" << std::endl;
    std::cout << "Enjoy this example of OOP C++ code!" << std::endl;
    std::cout << std::endl;
}
