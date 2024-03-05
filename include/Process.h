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

#pragma once
#include "Field.h"
#include "Player.h"
#include "Snake.h"
#include "Fruit.h"
#include "Graphics.h"
#include "Keyboard.h"

#include <chrono>
#include <string>

static const short SCORE_MULTIPLIER = 11;
class Process
{

//    int totalPointsSnake1;
//    int totalPointsSnake2;
//
//    int gameOverReasonSnake1;
//    int gameOverReasonSnake2;
//
//    int totalCycles;

    Field* field;
    int totalPlayers;
    Player** players;
    Snake** snakes;
    Fruit* fruit;
    Graphics* graphics;
    Keyboard keyboard;

    std::string msg;
    bool isNextGameWantedValue;

        std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    std::chrono::duration<double, std::milli> elapsed_time;



public:
    Process(int width, int height, double fruitEmptiness, int totalPlayers, std::string* playerNames);
    ~Process();
    const void mainLoop();
    const bool isNextGameWanted() const;

};
